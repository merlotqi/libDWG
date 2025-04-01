

/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#include <algorithm>
#include <dwg/CadDocument.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/CRC32StreamHandler_p.h>
#include <dwg/io/dwg/DwgCheckSumCalculator_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC18_p.h>
#include <dwg/io/dwg/fileheaders/DwgLocalSectionMap_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDescriptor_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC18_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterBase_p.h>
#include <dwg/io/dwg/writers/DwgLZ77AC18Compressor_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/utils/EndianConverter.h>
#include <dwg/utils/StreamWrapper.h>

namespace dwg {

int DwgFileHeaderWriterAC18::handleSectionOffset() const { return 0; }

int DwgFileHeaderWriterAC18::fileHeaderSize() const { return 0x100; }

DwgFileHeaderWriterAC18::DwgFileHeaderWriterAC18(std::ofstream *stream, Encoding encoding, CadDocument *document)
    : DwgFileHeaderWriterBase(stream, encoding, document)
{
    _descriptors = _fileHeader->descriptors();
    _compressor = new DwgLZ77AC18Compressor();
    // File header info
    for (int i = 0; i < fileHeaderSize(); i++)
    {
        char b = 0;
        _stream->write(&b, sizeof(char));
    }
}

void DwgFileHeaderWriterAC18::writeFile()
{
    _fileHeader->setSectionArrayPageSize((unsigned int) (_localSectionsMaps.size() + 2));
    _fileHeader->setSectionPageMapId(_fileHeader->sectionArrayPageSize());
    _fileHeader->setSectionMapId(_fileHeader->sectionArrayPageSize() - 1);

    writeDescriptors();
    writeRecords();
    writeFileMetaData();
}

void DwgFileHeaderWriterAC18::addSection(const std::string &name, std::ostream *stream, bool isCompressed,
                                         int decompsize)
{
    DwgSectionDescriptor descriptor(name);
    _fileHeader->addSection(descriptor);
    descriptor.setDecompressedSize((unsigned long long) decompsize);

    OutputStreamWrapper stwrapper(stream);

    descriptor.setCompressedSize(stwrapper.length());
    descriptor.setCompressedCode(((!isCompressed) ? 1 : 2));

    int nlocalSections = (int) (stwrapper.length() / (int) descriptor.decompressedSize());

    std::vector<unsigned char> buffer = stwrapper.buffer();
    unsigned long long offset = 0ULL;
    for (int i = 0; i < nlocalSections; i++)
    {
        craeteLocalSection(descriptor, buffer, (int) descriptor.decompressedSize(), offset,
                           (int) descriptor.decompressedSize(), isCompressed);
        offset += (unsigned long long) descriptor.decompressedSize();
    }

    int spearBytes = (int) (stwrapper.length() % (int) descriptor.decompressedSize());
    if (spearBytes > 0 && !checkEmptyBytes(buffer, offset, (unsigned long long) spearBytes))
    {
        craeteLocalSection(descriptor, buffer, (int) descriptor.decompressedSize(), offset, spearBytes, isCompressed);
    }
}


void DwgFileHeaderWriterAC18::craeteLocalSection(DwgSectionDescriptor descriptor,
                                                 const std::vector<unsigned char> &buffer, int decompressedSize,
                                                 unsigned long long offset, int totalSize, bool isCompressed)
{
    std::ostringstream descriptorStream = applyCompression(buffer, decompressedSize, offset, totalSize, isCompressed);
    OutputStreamWrapper descriptorStream_wrapper(&descriptorStream);

    writeMagicNumber();

    //Save position for the local section
    unsigned long long position = descriptorStream.tellp();

    DwgLocalSectionMap localMap;
    localMap.setOffset(offset);
    localMap.setSeeker(position);
    localMap.setPageNumber(_localSectionsMaps.size() + 1);
    localMap.setODA(DwgCheckSumCalculator::Calculate(0U, descriptorStream_wrapper.buffer(), 0,
                                                     (int) descriptorStream_wrapper.length()));

    int compressDiff = DwgCheckSumCalculator::CompressionCalculator((int) descriptorStream_wrapper.length());
    localMap.setCompressedSize(descriptorStream_wrapper.length());
    localMap.setDecompressedSize((unsigned long long) totalSize);
    localMap.setPageSize((long) localMap.compressedSize() + 32 + compressDiff);
    localMap.setChecksum(0u);

    std::ostringstream checkSumStream(std::string(32, '\0'));
    OutputStreamWrapper checkSumStream_wrapper(&checkSumStream);
    writeDataSection(&checkSumStream, descriptor, localMap, (int) descriptor.pageType());
    localMap.setChecksum(DwgCheckSumCalculator::Calculate(localMap.ODA(), checkSumStream_wrapper.buffer(), 0,
                                                          (int) checkSumStream_wrapper.length()));
    checkSumStream.clear();
    checkSumStream.seekp(std::ios::beg);

    writeDataSection(&checkSumStream, descriptor, localMap, (int) descriptor.pageType());

    applyMask(checkSumStream_wrapper.buffer(), 0, (int) checkSumStream_wrapper.length());

    _stream->write(checkSumStream.str().c_str(), checkSumStream.str().length());
    _stream->write(descriptorStream.str().c_str(), descriptorStream.str().length());

    if (isCompressed)
    {
        _stream->write(reinterpret_cast<const char *>(&DwgCheckSumCalculator::MagicSequence), compressDiff);
    }
    else if (compressDiff != 0)
    {
        throw new std::exception();
    }

    if (localMap.pageNumber() > 0)
    {
        descriptor.setPageCount(descriptor.pageCount() + 1);
    }

    localMap.setSize((unsigned long long) _stream->tellp() - position);
    descriptor.localSections().push_back(localMap);
    _localSectionsMaps.push_back(localMap);
}

std::ostringstream DwgFileHeaderWriterAC18::applyCompression(const std::vector<unsigned char> &buffer,
                                                             int decompressedSize, unsigned long long offset,
                                                             int totalSize, bool isCompressed)
{
    std::ostringstream stream;
    OutputStreamWrapper stream_wrapper(&stream);
    if (isCompressed)
    {
        std::ostringstream holder(std::string(decompressedSize, '\0'));
        OutputStreamWrapper holder_wrapper(&holder);
        holder_wrapper.write(buffer, offset, totalSize);

        int diff = decompressedSize - totalSize;
        for (int i = 0; i < diff; i++)
        {
            holder_wrapper.writeByte((unsigned char) 0);
        }

        _compressor->compress(holder_wrapper.buffer(), 0, decompressedSize, &stream);
    }
    else
    {
        stream.seekp(offset);
        stream.write(reinterpret_cast<const char *>(buffer.data()), totalSize);
        int diff = decompressedSize - totalSize;
        for (int j = 0; j < diff; j++)
        {
            stream_wrapper.writeByte((unsigned char) 0);
        }
    }

    return stream;
}

void DwgFileHeaderWriterAC18::writeDescriptors()
{
    std::ostringstream stream;
    IDwgStreamWriter *swriter = DwgStreamWriterBase::GetStreamWriter(_version, &stream, _encoding);

    //0x00	4	Number of section descriptions(NumDescriptions)
    swriter->writeInt(_descriptors.size());

    //0x04	4	0x02 (long)
    swriter->writeInt(2);
    //0x08	4	0x00007400 (long)
    swriter->writeInt(0x7400);
    //0x0C	4	0x00 (long)
    swriter->writeInt(0);

    //0x10	4	Unknown (long), ODA writes NumDescriptions here.
    swriter->writeInt(_descriptors.size());
    for (auto it = _descriptors.begin(); it != _descriptors.end(); ++it)
    {
        auto &&descriptors = it->second;
        //0x00	8	Size of section(OdUInt64)
        swriter->writeBytes(LittleEndianConverter::instance()->bytes(descriptors.compressedSize()));
        /*0x08	4	Page count(PageCount). Note that there can be more pages than PageCount,
							as PageCount is just the number of pages written to file.
							If a page contains zeroes only, that page is not written to file.
							These “zero pages” can be detected by checking if the page’s start 
							offset is bigger than it should be based on the sum of previously read pages 
							decompressed size(including zero pages).After reading all pages, if the total 
							decompressed size of the pages is not equal to the section’s size, add more zero 
							pages to the section until this condition is met.
				*/
        swriter->writeInt(descriptors.pageCount());
        //0x0C	4	Max Decompressed Size of a section page of this type(normally 0x7400)
        swriter->writeInt((int) descriptors.decompressedSize());
        //0x10	4	Unknown(long)
        swriter->writeInt(1);
        //0x14	4	Compressed(1 = no, 2 = yes, normally 2)
        swriter->writeInt(descriptors.compressedCode());
        //0x18	4	Section Id(starts at 0). The first section(empty section) is numbered 0, consecutive sections are numbered descending from(the number of sections – 1) down to 1.
        swriter->writeInt(descriptors.sectionId());
        //0x1C	4	Encrypted(0 = no, 1 = yes, 2 = unknown)
        swriter->writeInt(descriptors.encrypted());

        //0x20	64	Section Name(string)
        std::vector<unsigned char> nameArr(64, 0);
        if (!descriptors.name().empty())
        {
            std::vector<unsigned char> bytes = Encoding(CodePage::Windows1252).bytes(descriptors.name());
            int length = std::min(bytes.size(), nameArr.size());
            for (int i = 0; i < length; i++)
            {
                nameArr[i] = bytes[i];
            }
        }
        stream.write(reinterpret_cast<const char *>(nameArr.data()), nameArr.size());

        for (auto &&localMap: descriptors.localSections())
        {
            if (localMap.pageNumber() > 0)
            {
                //0x00	4	Page number(index into SectionPageMap), starts at 1
                swriter->writeInt(localMap.pageNumber());
                //0x04	4	Data size for this page(compressed size).
                swriter->writeInt((int) localMap.compressedSize());
                //0x08	8	Start offset for this page(OdUInt64).If this start offset is smaller than the sum of the decompressed size of all previous pages, then this page is to be preceded by zero pages until this condition is met.
                swriter->writeBytes(LittleEndianConverter::instance()->bytes(localMap.offset()));
            }
        }
    }

    //Section map: 0x4163003b
    DwgLocalSectionMap sectionHolder = setSeeker(0x4163003B, &stream);
    int count = DwgCheckSumCalculator::CompressionCalculator((int) (_stream->tellp() - sectionHolder.seeker()));
    // Fill the gap
    _stream->write(reinterpret_cast<const char *>(&DwgCheckSumCalculator::MagicSequence), count);
    sectionHolder.setSize(_stream->tellp() - sectionHolder.seeker());

    addSection(sectionHolder);
}

void DwgFileHeaderWriterAC18::writeRecords()
{
    writeMagicNumber();

    //Section page map: 0x41630e3b
    DwgLocalSectionMap section;
    section.setSectionMap(0x41630E3B);

    addSection(section);

    int counter = _localSectionsMaps.size() * 8;
    section.setSeeker(_stream->tellp());
    int size = counter + DwgCheckSumCalculator::CompressionCalculator(counter);
    section.setSize(size);

    std::ostringstream stream;
    OutputStreamWrapper writer(&stream);

    for (auto &&item: _localSectionsMaps)
    {
        //0x00	4	Section page number, starts at 1, page numbers are unique per file.
        writer.write(item.pageNumber());
        //0x04	4	Section size
        writer.write((int) item.size());
    }

    compressChecksum(section, &stream);

    DwgLocalSectionMap last = _localSectionsMaps[_localSectionsMaps.size() - 1];
    _fileHeader->setGapAmount(0U);
    _fileHeader->setLastPageId(last.pageNumber());
    _fileHeader->setLastSectionAddr((unsigned long long) (last.seeker() + size - 256));
    _fileHeader->setSectionAmount((unsigned int) (_localSectionsMaps.size() - 1));
    _fileHeader->setPageMapAddress((unsigned long long) section.seeker());
}

void DwgFileHeaderWriterAC18::writeFileMetaData()
{
    OutputStreamWrapper writer(_stream);

    _fileHeader->setSecondHeaderAddr((unsigned long long) _stream->tellp());

    std::ostringstream stream;
    writeFileHeader(&stream);

    _stream->write(reinterpret_cast<const char *>(stream.str().c_str()), stream.str().length());

    ////0x00	6	“ACXXXX” version string
    _stream->seekp(std::ios::beg);
    Encoding encoding(CodePage::Windows1251);
    writer.write(encoding.bytes(_document->header()->versionString()), 0, 6);

    //5 bytes of 0x00
    writer.write({0x00, 0x00, 0x00, 0x00, 0x00}, 0, 5);

    //0x0B	1	Maintenance release version
    writer.write<unsigned char>(_document->header()->maintenanceVersion());

    //0x0C	1	Byte 0x00, 0x01, or 0x03
    writer.write<unsigned char>(3);

    //0x0D	4	Preview address(long), points to the image page + page header size(0x20).
    writer.write((unsigned int) ((int) _descriptors[DwgSectionDefinition::Preview].localSections().at(0).seeker() + 0x20));

    //0x11	1	Dwg version (Acad version that writes the file)
    writer.write<unsigned char>(33);
    //0x12	1	Application maintenance release version(Acad maintenance version that writes the file)
    writer.write<unsigned char>(-_document->header()->maintenanceVersion());

    //0x13	2	Codepage
    writer.write<unsigned short>(getFileCodePage());
    //0x15	3	3 0x00 bytes
    writer.write({0x00, 0x00, 0x00}, 0, 3);

    //TODO: Write SecurityType
    //0x18	4	SecurityType (long), see R2004 meta data, the definition is the same, paragraph 4.1.
    writer.write((int) 0);
    //0x1C	4	Unknown long
    writer.write(0);

    //0x20	4	Summary info Address in stream
    writer.write((unsigned int) ((int) _descriptors[DwgSectionDefinition::SummaryInfo].localSections().at(0).seeker() +
                                 0x20));

    //0x24	4	VBA Project Addr(0 if not present)
    writer.write(0u);

    //0x28	4	0x00000080
    writer.write<int>(0x00000080);

    //0x2C	4	App info Address in stream
    writer.write(
            (unsigned int) ((int) _descriptors[DwgSectionDefinition::AppInfo].localSections().at(0).seeker() + 0x20));

    //0x30	0x80	0x00 bytes
    std::vector<unsigned char> arr(80, 0);

    writer.write(arr, 0, 80);
    writer.write(stream.str());
    _stream.Write(DwgCheckSumCalculator::MagicSequence, 236, 20);
}

void DwgFileHeaderWriterAC18::writeFileHeader(std::ostringstream *stream)
{
    CRC32OutputStreamHandler swriter(stream);

    //0x00	12	“AcFssFcAJMB” file ID string
    Encoding encoding(CodePage::Windows1252);
    swriter.write(encoding.fromUtf8("AcFssFcAJMB"));
    swriter.writeByte(0);

    //0x0C	4	0x00(long)
    swriter.write<int>(0);
    //0x10	4	0x6c(long)
    swriter.write<int>(0x6C);
    //0x14	4	0x04(long)
    swriter.write<int>(0x04);
    //0x18	4	Root tree node gap
    swriter.write<int>(_fileHeader->rootTreeNodeGap());
    //0x1C	4	Lowermost left tree node gap
    swriter.write<int>(_fileHeader->leftGap());
    //0x20	4	Lowermost right tree node gap
    swriter.write<int>(_fileHeader->rigthGap());
    //0x24	4	Unknown long(ODA writes 1)
    swriter.write<int>(1);
    //0x28	4	Last section page Id
    swriter.write<int>(_fileHeader->lastPageId());

    //0x2C	8	Last section page end address
    swriter.write<unsigned long long>(_fileHeader->lastSectionAddr());
    //0x34	8	Second header data address pointing to the repeated header data at the end of the file
    swriter.write<unsigned long long>(_fileHeader->secondHeaderAddr());

    //0x3C	4	Gap amount
    swriter.write<unsigned int>(_fileHeader->gapAmount());
    //0x40	4	Section page amount
    swriter.write<unsigned int>(_fileHeader->sectionAmount());

    //0x44	4	0x20(long)
    swriter.write<int>(0x20);
    //0x48	4	0x80(long)
    swriter.write<int>(0x80);
    //0x4C	4	0x40(long)
    swriter.write<int>(0x40);

    //0x50	4	Section Page Map Id
    swriter.write(_fileHeader->sectionPageMapId());
    //0x54	8	Section Page Map address(add 0x100 to this value)
    swriter.write<unsigned long long>(_fileHeader->pageMapAddress() - 256);
    //0x5C	4	Section Map Id
    swriter.write<unsigned int>(_fileHeader->sectionMapId());
    //0x60	4	Section page array size
    swriter.write<unsigned int>(_fileHeader->sectionArrayPageSize());
    //0x64	4	Gap array size
    swriter.write<unsigned int>(_fileHeader->gapArraySize());

    long position = swriter.pos();
    swriter.write<unsigned int>(0u);

    unsigned int seed = swriter.seed();
    swriter.seek(position);
    //0x68	4	CRC32(long).See paragraph 2.14.2 for the 32 - bit CRC calculation,
    //			the seed is zero. Note that the CRC
    //			calculation is done including the 4 CRC bytes that are
    //			initially zero! So the CRC calculation takes into account
    //			all of the 0x6c bytes of the data in this table.
    swriter.write<unsigned int>(seed);

    swriter.flush();

    applyMagicSequence(stream);
}

void DwgFileHeaderWriterAC18::addSection(DwgLocalSectionMap section)
{
    section.setPageNumber(_localSectionsMaps.size() + 1);
    _localSectionsMaps.push_back(section);
}

DwgLocalSectionMap DwgFileHeaderWriterAC18::setSeeker(int map, std::ostringstream *stream)
{
    DwgLocalSectionMap holder;
    holder.setSectionMap(map);

    writeMagicNumber();

    holder.setSeeker(_stream->tellp());

    compressChecksum(holder, stream);

    return holder;
}

void DwgFileHeaderWriterAC18::compressChecksum(DwgLocalSectionMap &section, std::ostringstream *stream)
{
    OutputStreamWrapper wrapper(stream);
    //Compress the local map section and write the checksum once is done
    section.setDecompressedSize(wrapper.length());

    std::ostringstream main;
    OutputStreamWrapper main_wrapper(&main);
    _compressor->compress(main_wrapper.buffer(), 0, wrapper.length(), &main);

    section.setCompressedSize(main_wrapper.length());

    std::ostringstream checkSumHolder;
    writePageHeaderData(section, &checkSumHolder);
    OutputStreamWrapper checkSumHolder_wrapper(&checkSumHolder);
    section.setChecksum(DwgCheckSumCalculator::Calculate(0u, checkSumHolder_wrapper.buffer(), 0, (int) checkSumHolder_wrapper.length()));
    section.setChecksum(DwgCheckSumCalculator::Calculate((unsigned int) section.checksum(), main_wrapper.buffer(), 0, (int) main_wrapper.length()));

    writePageHeaderData(section, _stream);
    _stream->write(reinterpret_cast<const char *>(main.str().data()), main.str().length());
}

void DwgFileHeaderWriterAC18::writePageHeaderData(const DwgLocalSectionMap &section, std::ostream *stream)
{
    OutputStreamWrapper writer(stream);

    //0x00	4	Section page type:
    //Section page map: 0x41630e3b
    //Section map: 0x4163003b
    writer.write<int>(section.sectionMap());
    //0x04	4	Decompressed size of the data that follows
    writer.write<int>((int) section.decompressedSize());
    //0x08	4	Compressed size of the data that follows(CompDataSize)
    writer.write<int>((int) section.compressedSize());
    //0x0C	4	Compression type(0x02)
    writer.write<int>(section.compression());
    //0x10	4	Section page checksum
    writer.write<unsigned int>((unsigned int) section.checksum());
}

void DwgFileHeaderWriterAC18::writeDataSection(std::ostream *stream, const DwgSectionDescriptor &descriptor,
                                               const DwgLocalSectionMap &map, int size)
{
    OutputStreamWrapper writer(stream);

    //0x00	4	Section page type, since it’s always a data section: 0x4163043b
    writer.write(size);
    //0x04	4	Section number
    writer.write(descriptor.sectionId());
    //0x08	4	Data size (compressed)
    writer.write((int) map.compressedSize());
    //0x0C	4	Page Size (decompressed)
    writer.write((int) map.pageSize());
    //0x10	4	Start Offset (in the decompressed buffer)
    writer.write((long) map.offset());
    //0x18	4	Data Checksum (section page checksum calculated from compressed data bytes, with seed 0)
    writer.write((unsigned int) map.checksum());
    //0x1C	4	Unknown (ODA writes a 0)
    writer.write(map.ODA());
}

}// namespace dwg


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

#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC18_p.h>
#include <dwg/io/dwg/fileheaders/DwgLocalSectionMap_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDescriptor_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC18_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterBase_p.h>
#include <dwg/io/dwg/writers/DwgLZ77AC18Compressor_p.h>

namespace dwg {

int DwgFileHeaderWriterAC18::handleSectionOffset() const { return 0; }

int DwgFileHeaderWriterAC18::fileHeaderSize() const { return 0x100; }

DwgFileHeaderWriterAC18::DwgFileHeaderWriterAC18(std::ofstream *stream, Encoding encoding, CadDocument *document)
    : DwgFileHeaderWriterBase(stream, encoding, document)
{
    _descriptors = _fileHeader->Descriptors;
    compressor = new DwgLZ77AC18Compressor();
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

    descriptor.CompressedSize = (unsigned long long) ostream_length(stream);
    descriptor.CompressedCode = ((!isCompressed) ? 1 : 2);

    int nlocalSections = (int) (ostream_length(stream) / (int) descriptor.DecompressedSize);

    std::string buffer = stream->str();
    unsigned long long offset = 0uL;
    for (int i = 0; i < nlocalSections; i++)
    {
        craeteLocalSection(descriptor, buffer, (int) descriptor.DecompressedSize, offset,
                           (int) descriptor.DecompressedSize, isCompressed);
        offset += (unsigned long long) descriptor.DecompressedSize;
    }

    int spearBytes = (int) (stream.Length % (int) descriptor.DecompressedSize);
    if (spearBytes > 0 && !checkEmptyBytes(buffer, offset, (unsigned long long) spearBytes))
    {
        craeteLocalSection(descriptor, buffer, (int) descriptor.DecompressedSize, offset, spearBytes, isCompressed);
    }
}


void DwgFileHeaderWriterAC18::craeteLocalSection(DwgSectionDescriptor descriptor,
                                                 const std::vector<unsigned char> &buffer, int decompressedSize,
                                                 unsigned long long offset, int totalSize, bool isCompressed)
{
    MemoryStream descriptorStream = applyCompression(buffer, decompressedSize, offset, totalSize, isCompressed);

    writeMagicNumber();

    //Save position for the local section
    long position = _stream.Position;

    DwgLocalSectionMap localMap = new DwgLocalSectionMap();
    localMap.Offset = offset;
    localMap.Seeker = position;
    localMap.PageNumber = _localSectionsMaps.Count + 1;
    localMap.ODA = DwgCheckSumCalculator.Calculate(0u, descriptorStream.GetBuffer(), 0, (int) descriptorStream.Length);

    int compressDiff = DwgCheckSumCalculator.CompressionCalculator((int) descriptorStream.Length);
    localMap.CompressedSize = (unsigned long long) descriptorStream.Length;
    localMap.DecompressedSize = (unsigned long long) totalSize;
    localMap.PageSize = (long) localMap.CompressedSize + 32 + compressDiff;
    localMap.Checksum = 0u;

    MemoryStream checkSumStream = new MemoryStream(32);
    writeDataSection(checkSumStream, descriptor, localMap, (int) descriptor.PageType);
    localMap.Checksum =
            DwgCheckSumCalculator.Calculate(localMap.ODA, checkSumStream.GetBuffer(), 0, (int) checkSumStream.Length);
    checkSumStream.SetLength(0L);
    checkSumStream.Position = 0L;

    writeDataSection(checkSumStream, descriptor, localMap, (int) descriptor.PageType);

    applyMask(checkSumStream.GetBuffer(), 0, (int) checkSumStream.Length);

    _stream.Write(checkSumStream.GetBuffer(), 0, (int) checkSumStream.Length);
    _stream.Write(descriptorStream.GetBuffer(), 0, (int) descriptorStream.Length);

    if (isCompressed) { _stream.Write(DwgCheckSumCalculator.MagicSequence, 0, compressDiff); }
    else if (compressDiff != 0) { throw new Exception(); }

    if (localMap.PageNumber > 0) { descriptor.PageCount++; }

    localMap.Size = _stream.Position - position;
    descriptor.LocalSections.Add(localMap);
    _localSectionsMaps.Add(localMap);
}

std::ostringstream DwgFileHeaderWriterAC18::applyCompression(const std::vector<unsigned char> &buffer,
                                                             int decompressedSize, unsigned long long offset,
                                                             int totalSize, bool isCompressed)
{
    std::ostringstream stream;
    if (isCompressed)
    {
        MemoryStream holder = new MemoryStream(decompressedSize);
        holder.Write(buffer, (int) offset, totalSize);
        int diff = decompressedSize - totalSize;
        for (int i = 0; i < diff; i++) { holder.WriteByte(0); }

        compressor.Compress(holder.GetBuffer(), 0, decompressedSize, stream);
    }
    else
    {
        stream.seekp(offset);
        stream.write(buffer.data(), totalSize);
        int diff = decompressedSize - totalSize;
        for (int j = 0; j < diff; j++) { stream.WriteByte(0); }
    }

    return stream;
}

void DwgFileHeaderWriterAC18::writeDescriptors()
{
    MemoryStream stream = new MemoryStream();
    var swriter = DwgStreamWriterBase.GetStreamWriter(_version, stream, _encoding);

    //0x00	4	Number of section descriptions(NumDescriptions)
    swriter.WriteInt(_descriptors.Count);

    //0x04	4	0x02 (long)
    swriter.WriteInt(2);
    //0x08	4	0x00007400 (long)
    swriter.WriteInt(0x7400);
    //0x0C	4	0x00 (long)
    swriter.WriteInt(0);

    //0x10	4	Unknown (long), ODA writes NumDescriptions here.
    swriter.WriteInt(_descriptors.Count);
    for (var descriptors in _descriptors.Values)
    {
        //0x00	8	Size of section(OdUInt64)
        swriter.WriteBytes(LittleEndianConverter.Instance.GetBytes(descriptors.CompressedSize));
        /*0x08	4	Page count(PageCount). Note that there can be more pages than PageCount,
							as PageCount is just the number of pages written to file.
							If a page contains zeroes only, that page is not written to file.
							These “zero pages” can be detected by checking if the page’s start 
							offset is bigger than it should be based on the sum of previously read pages 
							decompressed size(including zero pages).After reading all pages, if the total 
							decompressed size of the pages is not equal to the section’s size, add more zero 
							pages to the section until this condition is met.
				*/
        swriter.WriteInt(descriptors.PageCount);
        //0x0C	4	Max Decompressed Size of a section page of this type(normally 0x7400)
        swriter.WriteInt((int) descriptors.DecompressedSize);
        //0x10	4	Unknown(long)
        swriter.WriteInt(1);
        //0x14	4	Compressed(1 = no, 2 = yes, normally 2)
        swriter.WriteInt(descriptors.CompressedCode);
        //0x18	4	Section Id(starts at 0). The first section(empty section) is numbered 0, consecutive sections are numbered descending from(the number of sections – 1) down to 1.
        swriter.WriteInt(descriptors.SectionId);
        //0x1C	4	Encrypted(0 = no, 1 = yes, 2 = unknown)
        swriter.WriteInt(descriptors.Encrypted);

        //0x20	64	Section Name(string)
        byte[] nameArr = new byte[64];
        if (!string.IsNullOrEmpty(descriptors.Name))
        {
            byte[] bytes = TextEncoding.Windows1252().GetBytes(descriptors.Name);
            int length = Math.Min(bytes.Length, nameArr.Length);
            for (int i = 0; i < length; i++) { nameArr[i] = bytes[i]; }
        }
        stream.Write(nameArr, 0, nameArr.Length);

        foreach (DwgLocalSectionMap localMap in descriptors.LocalSections)
        {
            if (localMap.PageNumber > 0)
            {
                //0x00	4	Page number(index into SectionPageMap), starts at 1
                swriter.WriteInt(localMap.PageNumber);
                //0x04	4	Data size for this page(compressed size).
                swriter.WriteInt((int) localMap.CompressedSize);
                //0x08	8	Start offset for this page(OdUInt64).If this start offset is smaller than the sum of the decompressed size of all previous pages, then this page is to be preceded by zero pages until this condition is met.
                swriter.WriteBytes(LittleEndianConverter.Instance.GetBytes(localMap.Offset));
            }
        }
    }

    //Section map: 0x4163003b
    DwgLocalSectionMap sectionHolder = setSeeker(0x4163003B, stream);
    int count = DwgCheckSumCalculator.CompressionCalculator((int) (_stream.Position - sectionHolder.Seeker));
    // Fill the gap
    _stream.Write(DwgCheckSumCalculator.MagicSequence, 0, count);
    sectionHolder.Size = _stream.Position - sectionHolder.Seeker;

    addSection(sectionHolder);
}

void DwgFileHeaderWriterAC18::writeRecords()
{
    writeMagicNumber();

    //Section page map: 0x41630e3b
    DwgLocalSectionMap section = new DwgLocalSectionMap{SectionMap = 0x41630E3B};

    addSection(section);

    int counter = _localSectionsMaps.Count * 8;
    section.Seeker = _stream.Position;
    int size = counter + DwgCheckSumCalculator.CompressionCalculator(counter);
    section.Size = size;

    MemoryStream stream = new MemoryStream();
    StreamIO writer = new StreamIO(stream);

    foreach (DwgLocalSectionMap item in _localSectionsMaps)
    {
        if (item != null)
        {
            //0x00	4	Section page number, starts at 1, page numbers are unique per file.
            writer.Write(item.PageNumber);
            //0x04	4	Section size
            writer.Write((int) item.Size);
        }
    }

    compressChecksum(section, stream);

    DwgLocalSectionMap last = _localSectionsMaps[_localSectionsMaps.Count - 1];
    _fileHeader.GapAmount = 0u;
    _fileHeader.LastPageId = last.PageNumber;
    _fileHeader.LastSectionAddr = (unsigned long long) (last.Seeker + size - 256);
    _fileHeader.SectionAmount = (uint) (_localSectionsMaps.Count - 1);
    _fileHeader.PageMapAddress = (unsigned long long) section.Seeker;
}

void DwgFileHeaderWriterAC18::writeFileMetaData()
{
    StreamIO writer = new StreamIO(_stream);

    _fileHeader.SecondHeaderAddr = (unsigned long long) _stream.Position;

    MemoryStream stream = new MemoryStream();
    writeFileHeader(stream);

    _stream.Write(stream.GetBuffer(), 0, (int) stream.Length);

    ////0x00	6	“ACXXXX” version string
    _stream.Position = 0L;
    _stream.Write(Encoding.ASCII.GetBytes(_document.Header.VersionString), 0, 6);

    //5 bytes of 0x00
    _stream.Write(new byte[5], 0, 5);

    //0x0B	1	Maintenance release version
    _stream.WriteByte((byte) _document.Header.MaintenanceVersion);

    //0x0C	1	Byte 0x00, 0x01, or 0x03
    _stream.WriteByte(3);

    //0x0D	4	Preview address(long), points to the image page + page header size(0x20).
    writer.Write((uint) ((int) _descriptors[DwgSectionDefinition.Preview].LocalSections[0].Seeker + 0x20));

    //0x11	1	Dwg version (Acad version that writes the file)
    _stream.WriteByte((byte) 33);
    //0x12	1	Application maintenance release version(Acad maintenance version that writes the file)
    _stream.WriteByte((byte) _document.Header.MaintenanceVersion);

    //0x13	2	Codepage
    writer.Write<ushort>(getFileCodePage());
    //0x15	3	3 0x00 bytes
    _stream.Write(new byte[3], 0, 3);

    //TODO: Write SecurityType
    //0x18	4	SecurityType (long), see R2004 meta data, the definition is the same, paragraph 4.1.
    writer.Write((int) 0);
    //0x1C	4	Unknown long
    writer.Write(0);

    //0x20	4	Summary info Address in stream
    writer.Write((uint) ((int) _descriptors[DwgSectionDefinition.SummaryInfo].LocalSections[0].Seeker + 0x20));

    //0x24	4	VBA Project Addr(0 if not present)
    writer.Write(0u);

    //0x28	4	0x00000080
    writer.Write<int>(0x00000080);

    //0x2C	4	App info Address in stream
    writer.Write((uint) ((int) _descriptors[DwgSectionDefinition.AppInfo].LocalSections[0].Seeker + 0x20));

    //0x30	0x80	0x00 bytes
    byte[] array = new byte[80];

    _stream.Write(array, 0, 80);
    _stream.Write(stream.GetBuffer(), 0, (int) stream.Length);
    _stream.Write(DwgCheckSumCalculator.MagicSequence, 236, 20);
}

void DwgFileHeaderWriterAC18::writeFileHeader(std::ostringstream *stream)
{
    CRC32StreamHandler crcStream = new CRC32StreamHandler(stream, 0u);
    StreamIO swriter = new StreamIO(crcStream);

    //0x00	12	“AcFssFcAJMB” file ID string
    crcStream.Write(TextEncoding.Windows1252().GetBytes("AcFssFcAJMB"), 0, 11);
    crcStream.WriteByte(0);

    //0x0C	4	0x00(long)
    swriter.Write<int>(0);
    //0x10	4	0x6c(long)
    swriter.Write<int>(0x6C);
    //0x14	4	0x04(long)
    swriter.Write<int>(0x04);
    //0x18	4	Root tree node gap
    swriter.Write<int>(_fileHeader.RootTreeNodeGap);
    //0x1C	4	Lowermost left tree node gap
    swriter.Write<int>(_fileHeader.LeftGap);
    //0x20	4	Lowermost right tree node gap
    swriter.Write<int>(_fileHeader.RigthGap);
    //0x24	4	Unknown long(ODA writes 1)
    swriter.Write<int>(1);
    //0x28	4	Last section page Id
    swriter.Write<int>(_fileHeader.LastPageId);

    //0x2C	8	Last section page end address
    swriter.Write<unsigned long long>(_fileHeader.LastSectionAddr);
    //0x34	8	Second header data address pointing to the repeated header data at the end of the file
    swriter.Write<unsigned long long>(_fileHeader.SecondHeaderAddr);

    //0x3C	4	Gap amount
    swriter.Write<uint>(_fileHeader.GapAmount);
    //0x40	4	Section page amount
    swriter.Write<uint>(_fileHeader.SectionAmount);

    //0x44	4	0x20(long)
    swriter.Write<int>(0x20);
    //0x48	4	0x80(long)
    swriter.Write<int>(0x80);
    //0x4C	4	0x40(long)
    swriter.Write<int>(0x40);

    //0x50	4	Section Page Map Id
    swriter.Write(_fileHeader.SectionPageMapId);
    //0x54	8	Section Page Map address(add 0x100 to this value)
    swriter.Write<unsigned long long>(_fileHeader.PageMapAddress - 256);
    //0x5C	4	Section Map Id
    swriter.Write<uint>(_fileHeader.SectionMapId);
    //0x60	4	Section page array size
    swriter.Write<uint>(_fileHeader.SectionArrayPageSize);
    //0x64	4	Gap array size
    swriter.Write<uint>(_fileHeader.GapArraySize);

    long position = crcStream.Position;
    swriter.Write<uint>(0u);

    uint seed = crcStream.Seed;
    crcStream.Position = position;
    //0x68	4	CRC32(long).See paragraph 2.14.2 for the 32 - bit CRC calculation,
    //			the seed is zero. Note that the CRC
    //			calculation is done including the 4 CRC bytes that are
    //			initially zero! So the CRC calculation takes into account
    //			all of the 0x6c bytes of the data in this table.
    swriter.Write<uint>(seed);

    crcStream.Flush();

    applyMagicSequence(stream);
}

void DwgFileHeaderWriterAC18::addSection(DwgLocalSectionMap section)
{
    section.PageNumber = _localSectionsMaps.Count + 1;
    _localSectionsMaps.Add(section);
}

DwgLocalSectionMap DwgFileHeaderWriterAC18::setSeeker(int map, std::ostringstream *stream)
{
    DwgLocalSectionMap holder = new DwgLocalSectionMap{SectionMap = map};

    writeMagicNumber();

    holder.Seeker = _stream.Position;

    compressChecksum(holder, stream);

    return holder;
}

void DwgFileHeaderWriterAC18::compressChecksum(DwgLocalSectionMap section, std::ostringstream *stream)
{
    //Compress the local map section and write the checksum once is done
    section.DecompressedSize = (unsigned long long) stream.Length;

    MemoryStream main = new MemoryStream();
    compressor.Compress(stream.GetBuffer(), 0, (int) stream.Length, main);

    section.CompressedSize = (unsigned long long) main.Length;

    MemoryStream checkSumHolder = new MemoryStream();
    writePageHeaderData(section, checkSumHolder);
    section.Checksum = DwgCheckSumCalculator.Calculate(0u, checkSumHolder.GetBuffer(), 0, (int) checkSumHolder.Length);
    section.Checksum = DwgCheckSumCalculator.Calculate((uint) section.Checksum, main.GetBuffer(), 0, (int) main.Length);

    writePageHeaderData(section, _stream);
    _stream.Write(main.GetBuffer(), 0, (int) main.Length);
}

void DwgFileHeaderWriterAC18::writePageHeaderData(DwgLocalSectionMap section, std::ostream *stream)
{
    StreamIO writer = new StreamIO(stream);

    //0x00	4	Section page type:
    //Section page map: 0x41630e3b
    //Section map: 0x4163003b
    writer.Write<int>(section.SectionMap);
    //0x04	4	Decompressed size of the data that follows
    writer.Write<int>((int) section.DecompressedSize);
    //0x08	4	Compressed size of the data that follows(CompDataSize)
    writer.Write<int>((int) section.CompressedSize);
    //0x0C	4	Compression type(0x02)
    writer.Write<int>(section.Compression);
    //0x10	4	Section page checksum
    writer.Write<uint>((uint) section.Checksum);
}

void DwgFileHeaderWriterAC18::writeDataSection(std::ostream *stream, DwgSectionDescriptor descriptor,
                                               DwgLocalSectionMap map, int size)
{
    StreamIO writer = new StreamIO(stream);

    //0x00	4	Section page type, since it’s always a data section: 0x4163043b
    writer.Write(size);
    //0x04	4	Section number
    writer.Write(descriptor.SectionId);
    //0x08	4	Data size (compressed)
    writer.Write((int) map.CompressedSize);
    //0x0C	4	Page Size (decompressed)
    writer.Write((int) map.PageSize);
    //0x10	4	Start Offset (in the decompressed buffer)
    writer.Write((long) map.Offset);
    //0x18	4	Data Checksum (section page checksum calculated from compressed data bytes, with seed 0)
    writer.Write((uint) map.Checksum);
    //0x1C	4	Unknown (ODA writes a 0)
    writer.Write(map.ODA);
}

}// namespace dwg
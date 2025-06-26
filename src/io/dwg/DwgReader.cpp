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

#include <dwg/CadDocument.h>
#include <dwg/CadSummaryInfo.h>
#include <dwg/CadUtils.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/CRC32StreamHandler_p.h>
#include <dwg/io/dwg/DwgDocumentBuilder_p.h>
#include <dwg/io/dwg/DwgReader.h>
#include <dwg/io/dwg/DwgSectionIO_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC15_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC18_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC21_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeader_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/readers/DwgClassesReader_p.h>
#include <dwg/io/dwg/readers/DwgHandleReader_p.h>
#include <dwg/io/dwg/readers/DwgLZ77AC18Decompressor_p.h>
#include <dwg/io/dwg/readers/DwgLZ77AC21Decompressor_p.h>
#include <dwg/io/dwg/readers/DwgObjectReader_p.h>
#include <dwg/io/dwg/readers/DwgPreviewReader_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderBase_p.h>
#include <dwg/io/dwg/readers/DwgSummaryInfoReader_p.h>
#include <dwg/utils/EndianConverter.h>
#include <dwg/utils/StreamWrapper.h>
#include <dwg/utils/StringHelp.h>
#include <fmt/core.h>
#include <memory>
#include <queue>
#include <stdexcept>

namespace dwg {

DwgReader::DwgReader(const std::string &name)
    : CadReaderBase<DwgReaderConfiguration>(name), _builder(nullptr), _fileHeader(nullptr)
{
}

DwgReader::DwgReader(std::fstream *stream)
    : CadReaderBase<DwgReaderConfiguration>(stream), _builder(nullptr), _fileHeader(nullptr)
{
}

DwgReader::~DwgReader() {}

CadDocument *DwgReader::read()
{
    _document = new CadDocument(false);

    //Read the file header
    _fileHeader = readFileHeader();

    _builder = new DwgDocumentBuilder(_fileHeader->version(), _document, *this);

    _document->setSummaryInfo(readSummaryInfo());

    _document->setHeader(readHeader());
    _document->header()->setDocument(_document);

    _document->setClasses(readClasses());

    readAppInfo();

    //Read all the objects in the file
    readObjects();

    //Build the document
    _builder->buildDocument();

    return _document;
}

CadHeader *DwgReader::readHeader()
{
    return nullptr;
}

CadSummaryInfo *DwgReader::readSummaryInfo()
{
    if (!_fileHeader)
    {
        _fileHeader = readFileHeader();
    }

    //Older versions than 2004 don't have summary info in it's file
    if (_fileHeader->version() < ACadVersion::AC1018 || !isReadSummaryInfo())
    {
        return new CadSummaryInfo();
    }

    IDwgStreamReader *reader = getSectionStream(DwgSectionDefinition::SummaryInfo);
    if (!reader)
        return new CadSummaryInfo();

    std::unique_ptr<DwgSummaryInfoReader> summaryReader =
            std::make_unique<DwgSummaryInfoReader>(_fileHeader->version(), reader);
    return summaryReader->read();
}

DwgPreview *DwgReader::readPreview()
{
    if (!_fileHeader)
    {
        _fileHeader = readFileHeader();
    }

    //Check if the preview exist
    if (_fileHeader->previewAddress() < 0)
        return nullptr;

    IDwgStreamReader *streamReader = getSectionStream(DwgSectionDefinition::Preview);
    if (!streamReader)
    {
        streamReader = DwgStreamReaderBase::GetStreamHandler(_fileHeader->version(), _fileStream);
        streamReader->setPosition(_fileHeader->previewAddress());
    }

    std::unique_ptr<DwgPreviewReader> reader =
            std::make_unique<DwgPreviewReader>(_fileHeader->version(), streamReader, _fileHeader->previewAddress());
    return reader->read();
}

DwgFileHeader *DwgReader::readFileHeader()
{
    //Reset the stream position at the beginning
    _fileStream->seekg(std::ios::beg);

    //0x00	6	"ACXXXX" version string
    char buffer[7] = {0};
    _fileStream->read(buffer, 6);
    ACadVersion version = CadUtils::GetVersionFromName(std::string(buffer));
    DwgFileHeader *fileHeader = DwgFileHeader::CreateFileHeader(version);

    // Get the stream reader
    IDwgStreamReader *sreader = DwgStreamReaderBase::GetStreamHandler(fileHeader->version(), _fileStream);

    // Read the file header
    switch (fileHeader->version())
    {
        case dwg::ACadVersion::Unknown:
            throw std::invalid_argument("Not support");
        case dwg::ACadVersion::MC0_0:
        case dwg::ACadVersion::AC1_2:
        case dwg::ACadVersion::AC1_4:
        case dwg::ACadVersion::AC1_50:
        case dwg::ACadVersion::AC2_10:
        case dwg::ACadVersion::AC1002:
        case dwg::ACadVersion::AC1003:
        case dwg::ACadVersion::AC1004:
        case dwg::ACadVersion::AC1006:
        case dwg::ACadVersion::AC1009:
            throw std::invalid_argument("Not support");
        case dwg::ACadVersion::AC1012:
        case dwg::ACadVersion::AC1014:
        case dwg::ACadVersion::AC1015:
            readFileHeaderAC15(dynamic_cast<DwgFileHeaderAC15 *>(fileHeader), sreader);
            break;
        case dwg::ACadVersion::AC1018:
            readFileHeaderAC18(dynamic_cast<DwgFileHeaderAC18 *>(fileHeader), sreader);
            break;
        case dwg::ACadVersion::AC1021:
            readFileHeaderAC21(dynamic_cast<DwgFileHeaderAC21 *>(fileHeader), sreader);
            break;
        case dwg::ACadVersion::AC1024:
        case dwg::ACadVersion::AC1027:
        case dwg::ACadVersion::AC1032:
            readFileHeaderAC18(dynamic_cast<DwgFileHeaderAC18 *>(fileHeader), sreader);
            break;
        default:
            break;
    }

    return fileHeader;
}

void DwgReader::readAppInfo() {}

DxfClassCollection *DwgReader::readClasses()
{
    if (!_fileHeader)
    {
        _fileHeader = readFileHeader();
    }
    IDwgStreamReader *sreader = getSectionStream(DwgSectionDefinition::Classes);

    std::unique_ptr<DwgClassesReader> reader =
            std::make_unique<DwgClassesReader>(_fileHeader->version(), sreader, _fileHeader);
    return reader->read();
}

std::map<unsigned long long, long long> DwgReader::readHandles()
{
    if (!_fileHeader)
    {
        _fileHeader = readFileHeader();
    }
    IDwgStreamReader *sreader = getSectionStream(DwgSectionDefinition::Handles);

    std::unique_ptr<DwgHandleReader> handleReader = std::make_unique<DwgHandleReader>(_fileHeader->version(), sreader);
    return handleReader->read();
}

unsigned int DwgReader::readObjFreeSpace()
{
    if (!_fileHeader)
    {
        _fileHeader = readFileHeader();
    }

    if (_fileHeader->version() < ACadVersion::AC1018)
        return 0;

    IDwgStreamReader *sreader = getSectionStream(DwgSectionDefinition::ObjFreeSpace);

    //Int32				4	0
    //UInt32			4	Approximate number of objects in the drawing(number of handles).
    //Julian datetime	8	If version > R14 then system variable TDUPDATE otherwise TDUUPDATE.
    sreader->advance(16);

    //UInt32	4	Offset of the objects section in the stream.
    return sreader->readUInt();
}

void DwgReader::readTemplate()
{
    if (!_fileHeader)
    {
        _fileHeader = readFileHeader();
    }

    IDwgStreamReader *sreader = getSectionStream(DwgSectionDefinition::Template);

    throw std::runtime_error("not implemented");
}

void DwgReader::readObjects()
{
    std::map<unsigned long long, long long> handles = readHandles();
    _document->setClasses(readClasses());

    IDwgStreamReader *sreader = nullptr;
    if (_fileHeader->version() <= ACadVersion::AC1015)
    {
        sreader = DwgStreamReaderBase::GetStreamHandler(_fileHeader->version(),
                                                        _fileStream);//Handles are in absolute offset for this versions
        sreader->setPosition(0LL);
    }
    else
    {
        sreader = getSectionStream(DwgSectionDefinition::AcDbObjects);
    }

    std::queue<unsigned long long> objectHandles;

    std::unique_ptr<DwgObjectReader> sectionReader = std::make_unique<DwgObjectReader>(
            _fileHeader->version(), _builder, sreader, objectHandles, handles, _document->classes());
    sectionReader->read();
}

void DwgReader::readFileHeaderAC15(DwgFileHeaderAC15 *fileheader, IDwgStreamReader *sreader)
{
    // The next 7 starting at offset 0x06 are to be six bytes of 0
    // (in R14, 5 0's and the ACADMAINTVER variable) and a byte of 1.
    sreader->readBytes(7);
    // At 0x0D is a seeker (4 byte long absolute address) for the beginning sentinel of the image data.
    fileheader->setPreviewAddress(sreader->readInt());

    // Undocumented Bytes at 0x11 and 0x12
    sreader->readBytes(2);

    // Bytes at 0x13 and 0x14 are a raw short indicating the value of the code page for this drawing file.
    fileheader->setDrawingCodePage(CadUtils::GetCodePageByIndex(sreader->readShort()));
    _encoding = getListedEncoding((int) fileheader->drawingCodePage());

    // At 0x15 is a long that tells how many sets of recno/seeker/length records follow.
    int nRecords = (int) sreader->readRawLong();
    for (int i = 0; i < nRecords; ++i)
    {
        // Record number (raw byte) | Seeker (raw long) | Size (raw long)
        DwgSectionLocatorRecord record;
        record.setNumber(sreader->readByte());
        record.setSeeker(sreader->readRawLong());
        record.setSize(sreader->readRawLong());
        fileheader->records().insert({record.number(), record});
    }

    // RS : CRC for BOF to this point.
    sreader->resetShift();

    auto sn = sreader->readSentinel();
    DwgSectionIO::CheckSentinel(sn, DwgFileHeaderAC15::EndSentinel);
}

void DwgReader::readFileHeaderAC18(DwgFileHeaderAC18 *fileheader, IDwgStreamReader *sreader)
{
    readFileMetaData(fileheader, sreader);

    //0x80	0x6C	Encrypted Data
    //Metadata:
    //The encrypted data at 0x80 can be decrypted by exclusive or'ing the 0x6c bytes of data
    //from the file with the following magic number sequence:

    //29 23 BE 84 E1 6C D6 AE 52 90 49 F1 F1 BB E9 EB
    //B3 A6 DB 3C 87 0C 3E 99 24 5E 0D 1C 06 B7 47 DE
    //B3 12 4D C8 43 BB 8B A6 1F 03 5A 7D 09 38 25 1F
    //5D D4 CB FC 96 F5 45 3B 13 0D 89 0A 1C DB AE 32
    //20 9A 50 EE 40 78 36 FD 12 49 32 F6 9E 7D 49 DC
    //AD 4F 14 F2 44 40 66 D0 6B C4 30 B7

    std::vector<unsigned char> arr = sreader->readBytes(0x6C);
    std::stringstream headerStream(std::string(arr.begin(), arr.end()));
    CRC32StreamHandler headerStreamWrapper(&headerStream, 0U);
    headerStreamWrapper.setEncoding(Encoding(CodePage::Windows1252));

    sreader->readBytes(20);//CHECK IF IS USEFUL

#pragma region Read header encrypted data
    {
        //0x00	12	"AcFssFcAJMB" file ID string
        std::string fileId = headerStreamWrapper.readString(12);
        if (fileId != "AcFssFcAJMB\0")
        {
            OnNotification(fmt::format("File validation failed, id should be : AcFssFcAJMB\0, but is : {}", fileId),
                           Notification::Warning);
        }

        //0x0C	4	0x00(long)
        headerStreamWrapper.readT<int, LittleEndianConverter>();
        //0x10	4	0x6c(long)
        headerStreamWrapper.readT<int, LittleEndianConverter>();
        //0x14	4	0x04(long)
        headerStreamWrapper.readT<int, LittleEndianConverter>();
        //0x18	4	Root tree node gap
        fileheader->setRootTreeNodeGap(headerStreamWrapper.readT<int, LittleEndianConverter>());
        //0x1C	4	Lowermost left tree node gap
        fileheader->setLeftGap(headerStreamWrapper.readT<int, LittleEndianConverter>());
        //0x20	4	Lowermost right tree node gap
        fileheader->setRigthGap(headerStreamWrapper.readT<int, LittleEndianConverter>());
        //0x24	4	Unknown long(ODA writes 1)
        headerStreamWrapper.readT<int, LittleEndianConverter>();
        //0x28	4	Last section page Id
        fileheader->setLastPageId(headerStreamWrapper.readT<int, LittleEndianConverter>());

        //0x2C	8	Last section page end address
        fileheader->setLastSectionAddr(headerStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
        //0x34	8	Second header data address pointing to the repeated header data at the end of the file
        fileheader->setSecondHeaderAddr(headerStreamWrapper.readT<unsigned long long, LittleEndianConverter>());

        //0x3C	4	Gap amount
        fileheader->setGapAmount(headerStreamWrapper.readT<unsigned int, LittleEndianConverter>());
        //0x40	4	Section page amount
        fileheader->setSectionAmount(headerStreamWrapper.readT<unsigned int, LittleEndianConverter>());
        //0x44	4	0x20(long)
        headerStreamWrapper.readT<int, LittleEndianConverter>();
        //0x48	4	0x80(long)
        headerStreamWrapper.readT<int, LittleEndianConverter>();
        //0x4C	4	0x40(long)
        headerStreamWrapper.readT<int, LittleEndianConverter>();
        //0x50	4	Section Page Map Id
        fileheader->setSectionPageMapId(headerStreamWrapper.readT<unsigned int, LittleEndianConverter>());
        //0x54	8	Section Page Map address(add 0x100 to this value)
        fileheader->setPageMapAddress(headerStreamWrapper.readT<unsigned long long, LittleEndianConverter>() + 256UL);
        //0x5C	4	Section Map Id
        fileheader->setSectionMapId(headerStreamWrapper.readT<unsigned int, LittleEndianConverter>());
        //0x60	4	Section page array size
        fileheader->setSectionArrayPageSize(headerStreamWrapper.readT<unsigned int, LittleEndianConverter>());
        //0x64	4	Gap array size
        fileheader->setGapArraySize(headerStreamWrapper.readT<unsigned int, LittleEndianConverter>());
        //0x68	4	CRC32(long).See paragraph 2.14.2 for the 32 - bit CRC calculation,
        //			the seed is zero. Note that the CRC
        //			calculation is done including the 4 CRC bytes that are
        //			initially zero! So the CRC calculation takes into account
        //			all of the 0x6c bytes of the data in this table.
        fileheader->setCRCSeed(headerStreamWrapper.readUInt());
    }
#pragma endregion


#pragma region Read page map of the file
    {
        sreader->setPosition((long) fileheader->pageMapAddress());

        //Get the page size
        int64_t sectionType;
        int64_t decompressedSize;
        int64_t compressedSize;
        int64_t compressionType;
        int64_t checksum;
        getPageHeaderData(sreader, sectionType, decompressedSize, compressedSize, compressionType, checksum);
        //Get the descompressed stream to read the records
        std::stringstream decompressed;
        DwgLZ77AC18Decompressor::Decompress(sreader->stream(), decompressedSize, &decompressed);
        StreamWrapper decompressedWrapper(&decompressed);

        //Section size
        int total = 0x100;
        while (decompressedWrapper.pos() < decompressedWrapper.length())
        {
            DwgSectionLocatorRecord record;
            //0x00	4	Section page number, starts at 1, page numbers are unique per file.
            record.setNumber(decompressedWrapper.readInt());
            //0x04	4	Section size
            record.setSize(decompressedWrapper.readInt());

            if (record.number() >= 0)
            {
                record.setSeeker(total);
                fileheader->records().insert({record.number(), record});
            }
            else
            {
                //If the section number is negative, this represents a gap in the sections (unused data).
                //For a negative section number, the following data will be present after the section size:

                //0x00	4	Parent
                decompressedWrapper.readInt();
                //0x04	4	Left
                decompressedWrapper.readInt();
                //0x08	4	Right
                decompressedWrapper.readInt();
                //0x0C	4	0x00
                decompressedWrapper.readInt();
            }

            total += (int) record.size();
        }
    }
#pragma endregion


#pragma region Read the data section map
    {
        //Set the positon of the map
        sreader->setPosition(fileheader->records()[(int) fileheader->sectionMapId()].seeker());
        //Get the page size
        int64_t sectionType;
        int64_t decompressedSize;
        int64_t compressedSize;
        int64_t compressionType;
        int64_t checksum;
        getPageHeaderData(sreader, sectionType, decompressedSize, compressedSize, compressionType, checksum);

        std::stringstream decompressed;
        DwgLZ77AC18Decompressor::Decompress(sreader->stream(), decompressedSize, &decompressed);
        StreamWrapper decompressedWrapper(&decompressed);
        decompressedWrapper.setEncoding(Encoding(CodePage::Windows1252));

        //0x00	4	Number of section descriptions(NumDescriptions)
        int ndescriptions = decompressedWrapper.readT<int, LittleEndianConverter>();
        //0x04	4	0x02 (long)
        decompressedWrapper.readT<int, LittleEndianConverter>();
        //0x08	4	0x00007400 (long)
        decompressedWrapper.readT<int, LittleEndianConverter>();
        //0x0C	4	0x00 (long)
        decompressedWrapper.readT<int, LittleEndianConverter>();
        //0x10	4	Unknown (long), ODA writes NumDescriptions here.
        decompressedWrapper.readT<int, LittleEndianConverter>();

        for (int i = 0; i < ndescriptions; ++i)
        {
            DwgSectionDescriptor descriptor;
            //0x00	8	Size of section(OdUInt64)
            descriptor.setCompressedSize(decompressedWrapper.readULong());
            /*0x08	4	Page count(PageCount). Note that there can be more pages than PageCount,
							as PageCount is just the number of pages written to file.
							If a page contains zeroes only, that page is not written to file.
							These "zero pages" can be detected by checking if the page's start 
							offset is bigger than it should be based on the sum of previously read pages 
							decompressed size(including zero pages).After reading all pages, if the total 
							decompressed size of the pages is not equal to the section's size, add more zero 
							pages to the section until this condition is met.
				*/
            descriptor.setPageCount(decompressedWrapper.readT<int, LittleEndianConverter>());
            //0x0C	4	Max Decompressed Size of a section page of this type(normally 0x7400)
            descriptor.setDecompressedSize(
                    (unsigned long long) decompressedWrapper.readT<int, LittleEndianConverter>());
            //0x10	4	Unknown(long)
            decompressedWrapper.readT<int, LittleEndianConverter>();
            //0x14	4	Compressed(1 = no, 2 = yes, normally 2)
            descriptor.setCompressedCode(decompressedWrapper.readT<int, LittleEndianConverter>());
            //0x18	4	Section Id(starts at 0). The first section(empty section) is numbered 0, consecutive sections are numbered descending from(the number of sections - 1) down to 1.
            descriptor.setSectionId(decompressedWrapper.readT<int, LittleEndianConverter>());
            //0x1C	4	Encrypted(0 = no, 1 = yes, 2 = unknown)
            descriptor.setEncrypted(decompressedWrapper.readT<int, LittleEndianConverter>());
            //0x20	64	Section Name(string)
            std::string name = decompressedWrapper.readString(64);
            descriptor.setName(StringHelp::split(name, '\0').at(0));

            //Following this, the following (local) section page map data will be present
            for (int j = 0; j < descriptor.pageCount(); ++j)
            {
                DwgLocalSectionMap localmap;
                //0x00	4	Page number(index into SectionPageMap), starts at 1
                localmap.setPageNumber(decompressedWrapper.readT<int, LittleEndianConverter>());
                //0x04	4	Data size for this page(compressed size).
                localmap.setCompressedSize(
                        (unsigned long long) decompressedWrapper.readT<int, LittleEndianConverter>());
                //0x08	8	Start offset for this page(OdUInt64).If this start offset is smaller than the sum of the decompressed size of all previous pages, then this page is to be preceded by zero pages until this condition is met.
                localmap.setOffset(decompressedWrapper.readULong());

                //same decompressed size and seeker (temporal values)
                localmap.setDecompressedSize(descriptor.decompressedSize());
                localmap.setSeeker(fileheader->records()[localmap.pageNumber()].seeker());

                //Maximum section page size appears to be 0x7400 bytes in the normal case.
                //If a logical section of the file (the database objects, for example) exceeds this size, then it is broken up into pages of size 0x7400.

                descriptor.localSections().push_back(localmap);
            }

            //Get the final size for the local section
            unsigned int sizeLeft = (unsigned int) (descriptor.compressedSize() % descriptor.decompressedSize());
            if (sizeLeft > 0U && descriptor.localSections().size() > 0)
                descriptor.localSections()[descriptor.localSections().size() - 1].setDecompressedSize(sizeLeft);

            fileheader->descriptors().insert({descriptor.name(), descriptor});
        }
    }
#pragma endregion
}

void DwgReader::readFileHeaderAC21(DwgFileHeaderAC21 *fileheader, IDwgStreamReader *sreader)
{
    readFileMetaData(fileheader, sreader);

    //The last 0x28 bytes of this section consists of check data,
    //containing 5 Int64 values representing CRC's and related numbers
    //(starting from 0x3D8 until the end). The first 0x3D8 bytes
    //should be decoded using Reed-Solomon (255, 239) decoding, with a factor of 3.
    std::vector<unsigned char> compressedData = sreader->readBytes(0x400);
    std::vector<unsigned char> decodedData(3 * 239, 0);//factor * blockSize
    reedSolomonDecoding(compressedData, decodedData, 3, 239);

    //0x00	8	CRC
    long long crc = LittleEndianConverter::instance()->toInt64(decodedData.data(), 0);
    //0x08	8	Unknown key
    long long unknownKey = LittleEndianConverter::instance()->toInt64(decodedData.data(), 8);
    //0x10	8	Compressed Data CRC
    long long compressedDataCRC = LittleEndianConverter::instance()->toInt64(decodedData.data(), 16);
    //0x18	4	ComprLen
    int comprLen = LittleEndianConverter::instance()->toInt32(decodedData.data(), 24);
    //0x1C	4	Length2
    int length2 = LittleEndianConverter::instance()->toInt32(decodedData.data(), 28);

    //The decompressed size is a fixed 0x110.
    std::vector<unsigned char> buffer(0x110, 0);
    //If ComprLen is negative, then Data is not compressed (and data length is ComprLen).
    if (comprLen < 0)
    {
        //buffer = decodedData
        throw std::runtime_error("not implemented");
    }
    //If ComprLen is positive, the ComprLen bytes of data are compressed
    else
    {
        DwgLZ77AC21Decompressor::Decompress(decodedData, 32U, (unsigned int) comprLen, buffer);
    }

    //Get the descompressed stream to read the records
    std::stringstream decompressed(std::string(buffer.begin(), buffer.end()));
    StreamWrapper decompressedWrapper(&decompressed);

    //Read the compressed data
    Dwg21CompressedMetadata metaData;
    {
        //0x00	8	Header size (normally 0x70)
        metaData.setHeaderSize(decompressedWrapper.readULong());
        //0x08	8	File size
        metaData.setFileSize(decompressedWrapper.readULong());
        //0x10	8	PagesMapCrcCompressed
        metaData.setPagesMapCrcCompressed(decompressedWrapper.readULong());
        //0x18	8	PagesMapCorrectionFactor
        metaData.setPagesMapCorrectionFactor(decompressedWrapper.readULong());
        //0x20	8	PagesMapCrcSeed
        metaData.setPagesMapCrcSeed(decompressedWrapper.readULong());
        //0x28	8	Pages map2offset(relative to data page map 1, add 0x480 to get stream position)
        metaData.setMap2Offset(decompressedWrapper.readULong());
        //0x30	8	Pages map2Id
        metaData.setMap2Id(decompressedWrapper.readULong());
        //0x38	8	PagesMapOffset(relative to data page map 1, add 0x480 to get stream position)
        metaData.setPagesMapOffset(decompressedWrapper.readULong());
        //0x40	8	PagesMapId
        metaData.setPagesMapId(decompressedWrapper.readULong());
        //0x48	8	Header2offset(relative to page map 1 address, add 0x480 to get stream position)
        metaData.setHeader2offset(decompressedWrapper.readULong());
        //0x50	8	PagesMapSizeCompressed
        metaData.setPagesMapSizeCompressed(decompressedWrapper.readULong());
        //0x58	8	PagesMapSizeUncompressed
        metaData.setPagesMapSizeUncompressed(decompressedWrapper.readULong());
        //0x60	8	PagesAmount
        metaData.setPagesAmount(decompressedWrapper.readULong());
        //0x68	8	PagesMaxId
        metaData.setPagesMaxId(decompressedWrapper.readULong());
        //0x70	8	Unknown(normally 0x20, 32)
        metaData.setUnknow0x20(decompressedWrapper.readULong());
        //0x78	8	Unknown(normally 0x40, 64)
        metaData.setUnknow0x40(decompressedWrapper.readULong());
        //0x80	8	PagesMapCrcUncompressed
        metaData.setPagesMapCrcUncompressed(decompressedWrapper.readULong());
        //0x88	8	Unknown(normally 0xf800, 63488)
        metaData.setUnknown0xF800(decompressedWrapper.readULong());
        //0x90	8	Unknown(normally 4)
        metaData.setUnknown4(decompressedWrapper.readULong());
        //0x98	8	Unknown(normally 1)
        metaData.setUnknown1(decompressedWrapper.readULong());
        //0xA0	8	SectionsAmount(number of sections + 1)
        metaData.setSectionsAmount(decompressedWrapper.readULong());
        //0xA8	8	SectionsMapCrcUncompressed
        metaData.setSectionsMapCrcUncompressed(decompressedWrapper.readULong());
        //0xB0	8	SectionsMapSizeCompressed
        metaData.setSectionsMapSizeCompressed(decompressedWrapper.readULong());
        //0xB8	8	SectionsMap2Id
        metaData.setSectionsMap2Id(decompressedWrapper.readULong());
        //0xC0	8	SectionsMapId
        metaData.setSectionsMapId(decompressedWrapper.readULong());
        //0xC8	8	SectionsMapSizeUncompressed
        metaData.setSectionsMapSizeUncompressed(decompressedWrapper.readULong());
        //0xD0	8	SectionsMapCrcCompressed
        metaData.setSectionsMapCrcCompressed(decompressedWrapper.readULong());
        //0xD8	8	SectionsMapCorrectionFactor
        metaData.setSectionsMapCorrectionFactor(decompressedWrapper.readULong());
        //0xE0	8	SectionsMapCrcSeed
        metaData.setSectionsMapCrcSeed(decompressedWrapper.readULong());
        //0xE8	8	StreamVersion(normally 0x60100)
        metaData.setStreamVersion(decompressedWrapper.readULong());
        //0xF0	8	CrcSeed
        metaData.setCrcSeed(decompressedWrapper.readULong());
        //0xF8	8	CrcSeedEncoded
        metaData.setCrcSeedEncoded(decompressedWrapper.readULong());
        //0x100	8	RandomSeed
        metaData.setRandomSeed(decompressedWrapper.readULong());
        //0x108	8	Header CRC64
        metaData.setHeaderCRC64(decompressedWrapper.readULong());
    }
    fileheader->setCompressedMetadata(metaData);

    //Prepare the page data stream to read
    std::vector<unsigned char> arr =
            getPageBuffer(fileheader->compressedMetadata().pagesMapOffset(),
                          fileheader->compressedMetadata().pagesMapSizeCompressed(),
                          fileheader->compressedMetadata().pagesMapSizeUncompressed(),
                          fileheader->compressedMetadata().pagesMapCorrectionFactor(), 0xEF, sreader->stream());

    //Read the page data
    std::stringstream pageDataStream(std::string(arr.begin(), arr.end()));
    StreamWrapper pageDataStreamWrapper(&pageDataStream);

    long long offset = 0;
    while (pageDataStreamWrapper.pos() < pageDataStreamWrapper.length())
    {
        long long size = pageDataStreamWrapper.readLong();
        long long id = std::fabs(pageDataStreamWrapper.readLong());
        fileheader->records().insert({(int) id, DwgSectionLocatorRecord((int) id, (int) offset, (int) size)});

        //Add the size to the current offset
        offset += size;
    }

    //Prepare the section map data stream to read
    arr = getPageBuffer(
            (unsigned long long) fileheader->records()[(int) fileheader->compressedMetadata().sectionsMapId()].seeker(),
            fileheader->compressedMetadata().sectionsMapSizeCompressed(),
            fileheader->compressedMetadata().sectionsMapSizeUncompressed(),
            fileheader->compressedMetadata().sectionsMapCorrectionFactor(), 239, sreader->stream());

    //Section map stream
    std::stringstream sectionMapStream(std::string(arr.begin(), arr.end()));
    StreamWrapper sectionMapStreamWrapper(&sectionMapStream);

    while (sectionMapStreamWrapper.pos() < sectionMapStreamWrapper.length())
    {
        DwgSectionDescriptor section;
        //0x00	8	Data size
        section.setCompressedSize(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
        //0x08	8	Max size
        section.setDecompressedSize(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
        //0x10	8	Encryption
        section.setEncrypted((int) sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
        //0x18	8	HashCode
        section.setHashCode(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
        //0x20	8	SectionNameLength
        int sectionNameLength((int) sectionMapStreamWrapper.readT<long long, LittleEndianConverter>());
        //0x28	8	Unknown
        sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>();
        //0x30	8	Encoding
        section.setEncoding(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
        //0x38	8	NumPages.This is the number of pages present
        //			in the file for the section, but this does not include
        //			pages that contain zeroes only.A page that contains zeroes
        //			only is not written to file.If a page's data offset is
        //			smaller than the sum of the decompressed size of all previous
        //			pages, then it is to be preceded by a zero page with a size
        //			that is equal to the difference between these two numbers.
        section.setPageCount((int) sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());

        //Read the name
        if (sectionNameLength > 0)
        {
            std::string name = sectionMapStreamWrapper.readString(sectionNameLength, Encoding());
            //Remove the empty characters
            section.setName(StringHelp::replace(name, "\0", ""));
        }

        unsigned currentOffset = 0;
        for (int i = 0; i < section.pageCount(); ++i)
        {
            DwgLocalSectionMap page;
            //8	Page data offset.If a page's data offset is
            //	smaller than the sum of the decompressed size
            //	of all previous pages, then it is to be preceded
            //	by a zero page with a size that is equal to the
            //	difference between these two numbers.
            page.setOffset(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
            //8	Page Size
            page.setSize(sectionMapStreamWrapper.readT<long long, LittleEndianConverter>());
            //8	Page Id
            page.setPageNumber((int) sectionMapStreamWrapper.readT<long long, LittleEndianConverter>());
            //8	Page Uncompressed Size
            page.setDecompressedSize(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
            //8	Page Compressed Size
            page.setCompressedSize(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
            //8	Page Checksum
            page.setChecksum(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());
            //8	Page CRC
            page.setCRC(sectionMapStreamWrapper.readT<unsigned long long, LittleEndianConverter>());

#if false
//this code it doesn't take any effect on the reading
					//Create an empty page to fill the gap
					if (currentOffset < page.Offset)
					{
						ulong decompressedSize = page.Offset - currentOffset;
						DwgLocalSectionMap emptyPage = new DwgLocalSectionMap();
						emptyPage.IsEmpty = true;
						emptyPage.Offset = currentOffset;
						emptyPage.CompressedSize = 0;
						emptyPage.DecompressedSize = decompressedSize;

						//Add the empty local section to the current descriptor
						section.LocalSections.Add(emptyPage);
					}
#endif
            //Add the page to the section
            section.localSections().push_back(page);
            //Move the offset
            currentOffset = page.offset() + page.decompressedSize();
        }
        if (sectionNameLength > 0)
            fileheader->descriptors().insert({section.name(), section});
    }
}

void DwgReader::readFileMetaData(DwgFileHeaderAC18 *fileheader, IDwgStreamReader *sreader)
{
    //5 bytes of 0x00
    sreader->advance(5);

    //0x0B	1	Maintenance release version
    fileheader->setAcadMaintenanceVersion(sreader->readByte());
    //0x0C	1	Byte 0x00, 0x01, or 0x03
    sreader->advance(1);
    //0x0D	4	Preview address(long), points to the image page + page header size(0x20).
    fileheader->setPreviewAddress(sreader->readRawLong());
    //0x11	1	Dwg version (Acad version that writes the file)
    fileheader->setDwgVersion(sreader->readByte());
    //0x12	1	Application maintenance release version(Acad maintenance version that writes the file)
    fileheader->setAppReleaseVersion(sreader->readByte());

    //0x13	2	Codepage
    fileheader->setDrawingCodePage(CadUtils::GetCodePageByIndex(sreader->readShort()));
    _encoding = getListedEncoding((int) fileheader->drawingCodePage());
    sreader->setEncoding(_encoding);

    //Advance empty bytes
    //0x15	3	3 0x00 bytes
    sreader->advance(3);

    //0x18	4	SecurityType (long), see R2004 meta data, the definition is the same, paragraph 4.1.
    fileheader->setSecurityType(sreader->readRawLong());
    //0x1C	4	Unknown long
    sreader->readRawLong();
    //0x20	4	Summary info Address in stream
    fileheader->setSummaryInfoAddr(sreader->readRawLong());
    //0x24	4	VBA Project Addr(0 if not present)
    fileheader->setVbaProjectAddr(sreader->readRawLong());

    //0x28	4	0x00000080
    sreader->readRawLong();

    //0x2C	4	App info Address in stream
    sreader->readRawLong();

    //Get to offset 0x80
    //0x30	0x80	0x00 bytes
    sreader->advance(80);
}

IDwgStreamReader *DwgReader::getSectionStream(const std::string &sectionName)
{
    std::iostream *sectionStream = nullptr;
    switch (_fileHeader->version())
    {
        case dwg::ACadVersion::Unknown:
            throw std::runtime_error("Not supported");
            break;
        case dwg::ACadVersion::MC0_0:
        case dwg::ACadVersion::AC1_2:
        case dwg::ACadVersion::AC1_4:
        case dwg::ACadVersion::AC1_50:
        case dwg::ACadVersion::AC2_10:
        case dwg::ACadVersion::AC1002:
        case dwg::ACadVersion::AC1003:
        case dwg::ACadVersion::AC1004:
        case dwg::ACadVersion::AC1006:
        case dwg::ACadVersion::AC1009:
            throw std::runtime_error("Not supported");
            break;
        case dwg::ACadVersion::AC1012:
        case dwg::ACadVersion::AC1014:
        case dwg::ACadVersion::AC1015:
            sectionStream = getSectionBuffer15(dynamic_cast<DwgFileHeaderAC15 *>(_fileHeader), sectionName);
            break;
        case dwg::ACadVersion::AC1018:
            sectionStream = getSectionBuffer18(dynamic_cast<DwgFileHeaderAC18 *>(_fileHeader), sectionName);
            break;
        case dwg::ACadVersion::AC1021:
            sectionStream = getSectionBuffer21(dynamic_cast<DwgFileHeaderAC21 *>(_fileHeader), sectionName);
            break;
        case dwg::ACadVersion::AC1024:
        case dwg::ACadVersion::AC1027:
        case dwg::ACadVersion::AC1032:
            sectionStream = getSectionBuffer18(dynamic_cast<DwgFileHeaderAC18 *>(_fileHeader), sectionName);
            break;
        default:
            break;
    }

    if (!sectionStream)
        return nullptr;

    IDwgStreamReader *streamHandler = DwgStreamReaderBase::GetStreamHandler(_fileHeader->version(), sectionStream);

    // Set the encoding if needed
    streamHandler->setEncoding(_encoding);
    return streamHandler;
}

void DwgReader::getPageHeaderData(IDwgStreamReader *sreader, int64_t &sectionType, int64_t &decompressedSize,
                                  int64_t &compressedSize, int64_t &compressionType, int64_t &checksum)
{
    //0x00	4	Section page type:
    //Section page map: 0x41630e3b
    //Section map: 0x4163003b
    sectionType = sreader->readRawLong();
    //0x04	4	Decompressed size of the data that follows
    decompressedSize = sreader->readRawLong();
    //0x04	4	Decompressed size of the data that follows
    decompressedSize = sreader->readRawLong();
    //0x08	4	Compressed size of the data that follows(CompDataSize)
    compressedSize = sreader->readRawLong();

    //0x0C	4	Compression type(0x02)
    compressionType = sreader->readRawLong();
    //0x10	4	Section page checksum
    checksum = sreader->readRawLong();
}

std::iostream *DwgReader::getSectionBuffer15(DwgFileHeaderAC15 *fileheader, const std::string &sectionName)
{
    std::iostream *stream = nullptr;

    //Get the section locator
    auto [sectionLocator, isNull] = DwgSectionDefinition::GetSectionLocatorByName(sectionName);

    if (!isNull)
        //There is no section for this version
        return nullptr;


    auto &&records = fileheader->records();
    auto it = records.find(sectionLocator);
    if (it != records.end())
    {
        //set the stream position
        stream = _fileStream;
        stream->seekg(it->second.seeker());
    }

    return stream;
}

std::iostream *DwgReader::getSectionBuffer18(DwgFileHeaderAC18 *fileheader, const std::string &sectionName)
{
    auto &&it = fileheader->descriptors().find(sectionName);
    if (it == fileheader->descriptors().end())
    {
        return nullptr;
    }

    DwgSectionDescriptor &descriptor = it->second;

    //get the total size of the page
    std::string ostr(descriptor.decompressedSize() * descriptor.localSections().size(), 0);
    std::stringstream memoryStream(ostr);
    memoryStream.seekp(std::ios::beg);
    StreamWrapper wrapper(&memoryStream);

    for (auto &&section: descriptor.localSections())
    {
        if (section.isEmpty())
        {
            //Page is empty, fill the gap with 0s
            for (int index = 0; index < (int) section.decompressedSize(); ++index)
            {
                wrapper.writeByte(0);
            }
        }
        else
        {
            //Get the page section header
            IDwgStreamReader *sreader = DwgStreamReaderBase::GetStreamHandler(fileheader->version(), _fileStream);
            sreader->setPosition(section.seeker());
            //Get the header data
            decryptDataSection(section, sreader);

            if (descriptor.isCompressed())
            {
                //Page is compressed
                DwgLZ77AC18Decompressor::DecompressToDest(_fileStream, &memoryStream);
            }
            else
            {
                //Read the stream normally
                std::vector<unsigned char> buffer(section.compressedSize(), 0);
                sreader->stream()->read(reinterpret_cast<char *>(buffer.data()), section.compressedSize());
                wrapper.write(buffer, 0, section.compressedSize());
            }
        }
    }
    //Reset the stream
    memoryStream.seekp(std::ios::beg);
    return new std::stringstream(ostr);
}

std::iostream *DwgReader::getSectionBuffer21(DwgFileHeaderAC21 *fileheader, const std::string &sectionName)
{
    std::iostream *stream = nullptr;

    auto it = fileheader->descriptors().find(sectionName);
    if (it == fileheader->descriptors().end())
        return nullptr;

    DwgSectionDescriptor &section = it->second;
    //Get the total lenght of all uncompressed pages
    unsigned long long totalLength = 0;
    for (auto &&page: section.localSections()) totalLength += page.decompressedSize();

    // Total buffer for the page
    std::vector<unsigned char> pagesBuffer(totalLength, 0);

    long long currOffset = 0;
    for (auto &&page: section.localSections())
    {
        if (page.isEmpty())
        {
            //Page is empty, fill the gap with 0s
            for (int i = 0; i < (int) page.decompressedSize(); ++i) pagesBuffer[(int) currOffset++] = 0;
        }
        else
        {
            //Get the page data
            const DwgSectionLocatorRecord pageData = fileheader->records()[page.pageNumber()];

            //Set the pointer on the current page
            _fileStream->seekg(pageData.seeker() + 0x480L);

            //Get the page data
            std::vector<unsigned char> pageBytes(pageData.size(), 0);
            _fileStream->read(reinterpret_cast<char *>(pageBytes.data()), pageData.size());

            if (section.encoding() == 4)
            {
                //Encoded page, use reed solomon

                //Avoid shifted bits
                unsigned long long v = page.compressedSize() + 7L;
                unsigned long long v1 = v & 0b11111111'11111111'11111111'11111000L;

                int alignedPageSize = (int) ((v1 + 251 - 1) / 251);
                std::vector<unsigned char> arr(alignedPageSize * 251, 0);

                reedSolomonDecoding(pageBytes, arr, alignedPageSize, 251);
                pageBytes = arr;
            }

            if (page.compressedSize() != page.decompressedSize())
            {
                //Page is compressed
                std::vector<unsigned char> arr(page.decompressedSize(), 0);
                DwgLZ77AC21Decompressor::Decompress(pageBytes, 0U, (unsigned int) page.compressedSize(), arr);
                pageBytes = arr;
            }

            for (int i = 0; i < (int) page.decompressedSize(); ++i) pagesBuffer[(int) currOffset++] = pageBytes[i];
        }
    }

    return nullptr;
}

void DwgReader::decryptDataSection(DwgLocalSectionMap &section, IDwgStreamReader *sreader)
{
    int secMask = 0x4164536B ^ (int) sreader->position();

    //0x00	4	Section page type, since it's always a data section: 0x4163043b
    auto pageType = sreader->readRawLong() ^ secMask;
    //0x04	4	Section number
    auto sectionNumber = sreader->readRawLong() ^ secMask;
    //0x08	4	Data size (compressed)
    section.setCompressedSize((unsigned long long) (sreader->readRawLong() ^ secMask));
    //0x0C	4	Page Size (decompressed)
    section.setPageSize(sreader->readRawLong() ^ secMask);
    //0x10	4	Start Offset (in the decompressed buffer)
    auto startOffset = sreader->readRawLong() ^ secMask;
    //0x14	4	Page header Checksum (section page checksum calculated from unencoded header bytes, with the data checksum as seed)
    auto checksum = sreader->readRawLong() ^ secMask;
    section.setOffset((unsigned long long) (checksum + startOffset));

    //0x18	4	Data Checksum (section page checksum calculated from compressed data bytes, with seed 0)
    section.setChecksum((unsigned int) (sreader->readRawLong() ^ secMask));
    //0x1C	4	Unknown (ODA writes a 0)
    auto oda = (unsigned int) (sreader->readRawLong() ^ secMask);
}

void DwgReader::reedSolomonDecoding(const std::vector<unsigned char> &encoded, std::vector<unsigned char> &buffer,
                                    int factor, int blockSize)
{
    int index = 0;
    int n = 0;
    int length = buffer.size();
    for (int i = 0; i < factor; ++i)
    {
        int cindex = n;
        if (n < encoded.size())
        {
            int size = std::min(length, blockSize);
            length -= size;
            int offset = index + size;
            while (index < offset)
            {
                buffer[index] = encoded[cindex];
                ++index;
                cindex += factor;
            }
        }
        ++n;
    }
}

std::vector<unsigned char> DwgReader::getPageBuffer(unsigned long long pageOffset, unsigned long long compressedSize,
                                                    unsigned long long uncompressedSize,
                                                    unsigned long long correctionFactor, int blockSize,
                                                    std::iostream *stream)
{
    //Avoid shifted bits
    unsigned long long v = compressedSize + 7L;
    unsigned long long v1 = v & 0b11111111'11111111'11111111'11111000L;

    unsigned int totalSize = (unsigned int) (v1 * correctionFactor);

    int factor = (int) (totalSize + blockSize - 1L) / blockSize;
    int length = factor * UCHAR_MAX;

    std::vector<unsigned char> buffer(length, 0);

    //Relative to data page map 1, add 0x480 to get stream position
    stream->seekg((std::streampos)(0x480 + pageOffset));
    stream->read(reinterpret_cast<char *>(buffer.data()), length);

    std::vector<unsigned char> compressedData(totalSize, 0);
    reedSolomonDecoding(buffer, compressedData, factor, blockSize);

    std::vector<unsigned char> decompressedData(uncompressedSize, 0);

    DwgLZ77AC21Decompressor::Decompress(compressedData, 0U, (unsigned int) compressedSize, decompressedData);

    return decompressedData;
}

}// namespace dwg
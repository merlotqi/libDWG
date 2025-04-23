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
#include <dwg/CadUtils.h>
#include <dwg/io/dwg/DwgReader.h>
#include <dwg/io/dwg/DwgSectionIO_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC15_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC18_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC21_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeader_p.h>
#include <dwg/io/dwg/readers/DwgLZ77AC21Decompressor_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderBase_p.h>
#include <stdexcept>


namespace dwg {

DwgReader::DwgReader(const std::string &name)
    : CadReaderBase<DwgReaderConfiguration>(name), _builder(nullptr), _fileHeader(nullptr)
{
}

DwgReader::DwgReader(std::ifstream *stream)
    : CadReaderBase<DwgReaderConfiguration>(stream), _builder(nullptr), _fileHeader(nullptr)
{
}

DwgReader::~DwgReader() {}

CadDocument *DwgReader::read()
{
    _document = new CadDocument(false);

    //Read the file header
    _fileHeader = readFileHeader();
    return nullptr;
}

CadHeader *DwgReader::readHeader()
{
    return nullptr;
}

CadSummaryInfo *DwgReader::readSummaryInfo()
{
    return nullptr;
}

DwgPreview *DwgReader::readPreview()
{
    return nullptr;
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
            throw std::invalid_argument("");
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

DxfClassCollection *DwgReader::readClasses()
{
    return nullptr;
}

std::map<unsigned long long, unsigned long long> DwgReader::readHandles()
{
    return std::map<unsigned long long, unsigned long long>();
}

unsigned int DwgReader::readObjFreeSpace()
{
    return 0UL;
}

void DwgReader::readTemplate() {}

void DwgReader::readObjects() {}

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
    //The encrypted data at 0x80 can be decrypted by exclusive or’ing the 0x6c bytes of data
    //from the file with the following magic number sequence:

    //29 23 BE 84 E1 6C D6 AE 52 90 49 F1 F1 BB E9 EB
    //B3 A6 DB 3C 87 0C 3E 99 24 5E 0D 1C 06 B7 47 DE
    //B3 12 4D C8 43 BB 8B A6 1F 03 5A 7D 09 38 25 1F
    //5D D4 CB FC 96 F5 45 3B 13 0D 89 0A 1C DB AE 32
    //20 9A 50 EE 40 78 36 FD 12 49 32 F6 9E 7D 49 DC
    //AD 4F 14 F2 44 40 66 D0 6B C4 30 B7
}

void DwgReader::readFileHeaderAC21(DwgFileHeaderAC21 *fileheader, IDwgStreamReader *sreader) {}

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
    std::istream *sectionStream = nullptr;
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

std::istream *DwgReader::getSectionBuffer15(DwgFileHeaderAC15 *fileheader, const std::string &section_name)
{
    return nullptr;
}

std::istream *DwgReader::getSectionBuffer18(DwgFileHeaderAC18 *fileheader, const std::string &section_name)
{
    return nullptr;
}

std::istream *DwgReader::getSectionBuffer21(DwgFileHeaderAC21 *fileheader, const std::string &sectionName)
{
    return nullptr;
}

void DwgReader::decryptDataSection(const DwgLocalSectionMap &section, IDwgStreamReader *sreader) {}

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
                                                    std::istream *stream)
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
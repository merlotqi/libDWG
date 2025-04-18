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

#include <dwg/io/dwg/DwgReader.h>

namespace dwg {

DwgReader::DwgReader(const std::string &name) : CadReaderBase<DwgReaderConfiguration>(name), _builder(nullptr), _fileHeader(nullptr) {}

DwgReader::DwgReader(std::ifstream *stream) : CadReaderBase<DwgReaderConfiguration>(stream), _builder(nullptr), _fileHeader(nullptr) {}

DwgReader::~DwgReader() {}

CadDocument *DwgReader::read() 
{
    _document = new CadDocument(false);
    _fileHeader = readFileHeader(); 
    return nullptr; 
}

CadHeader *DwgReader::readHeader() { return nullptr; }

CadSummaryInfo *DwgReader::readSummaryInfo() { return nullptr; }

DwgPreview *DwgReader::readPreview() { return nullptr; }

DwgFileHeader *DwgReader::readFileHeader() 
{
    //Reset the stream position at the beginning
    _fileStream->seekg(std::ios::beg);

    //0x00	6	“ACXXXX” version string

    char buffer[7] = {0};
    _fileStream->read(buffer, 6);
    ACadVersion version = CadUtils::GetVersionFromName(std::string(buffer));
    DwgFileHeader *fileHeader = DwgFileHeader::CreateFileHeader(version);
    
    return nullptr;
}

DxfClassCollection *DwgReader::readClasses() { return nullptr; }

std::map<unsigned long long, unsigned long long> DwgReader::readHandles() { return std::map<unsigned long long, unsigned long long>(); }

unsigned int DwgReader::readObjFreeSpace() { return 0UL; }

void DwgReader::readTemplate() {}

void DwgReader::readObjects() {}

void DwgReader::readFileHeaderAC15(DwgFileHeaderAC15 *fileheader, IDwgStreamReader *sender) {}

void DwgReader::readFileHeaderAC18(DwgFileHeaderAC18 *fileheader, IDwgStreamReader *sender) {}

void DwgReader::readFileHeaderAC21(DwgFileHeaderAC21 *fileheader, IDwgStreamReader *sreader) {}

void DwgReader::readFileMetaData(DwgFileHeaderAC18 *fileheader, IDwgStreamReader *sreader) {}

IDwgStreamReader *DwgReader::getSectionStream(const std::string &sectionName) { return nullptr; }

void DwgReader::getPageHeaderData(IDwgStreamReader *sender, int64_t &sectionType, int64_t &decompressedSize,
                       int64_t &compressedSize, int64_t &compressionType, int64_t &checksum) {}

std::ifstream *DwgReader::getSectionBuffer15(DwgFileHeaderAC15 *fileheader, const std::string &section_name) { return nullptr; }

std::ifstream *DwgReader::getSectionBuffer18(DwgFileHeaderAC18 *fileheader, const std::string &section_name) { return nullptr; }

void DwgReader::decryptDataSection(const DwgLocalSectionMap &section, IDwgStreamReader *sreader) {}

std::istringstream DwgReader::getSectionBuffer21(DwgFileHeaderAC21 *fileheader, const std::string &sectionName) 
{     
    std::istringstream iss;
    return iss; 
}

void DwgReader::reedSolomonDecoding(const std::vector<unsigned char> &encoded, std::vector<unsigned char> &buffer, int factor,
                         int blockSize) 
{}

std::vector<unsigned char> DwgReader::getPageBuffer(unsigned long long pageOffset, unsigned long long compressedSize,
                                         unsigned long long uncompressedSize, unsigned long long correctionFactor,
                                         int blockSize, std::istream *stream) 
{ 
    return std::vector<unsigned char>(); 
}

}// namespace dwg
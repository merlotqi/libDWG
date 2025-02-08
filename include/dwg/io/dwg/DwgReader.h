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

#pragma once

#include <dwg/io/CadReaderBase.h>
#include <dwg/io/dwg/DwgReaderConfiguration.h>

namespace dwg {

class DwgPreview;
class DwgDocumentBuilder;
class DwgFileHeader;
class IDwgStreamReader;
class DwgFileHeaderAC15;
class DwgFileHeaderAC18;
class DwgFileHeaderAC21;
class DwgLocalSectionMap;

class LIBDWG_API DwgReader : public CadReaderBase<DwgReaderConfiguration>
{
    DwgDocumentBuilder *_builder;
    DwgFileHeader *_fileHeader;

public:
    DwgReader(const std::string &name);
    
    DwgReader(std::ifsteam *stream);
    
    ~DwgReader();
    
    CadDoument *read() override;
    
    CadHeader *readHander() override;
    
    CadSummaryInfo *readSummaryInfo();

    DwgPreview* readPreview();


private:
    DwgFileHeader *readFileHeader();

    DxfClassCollection readClasses();

    std::map<unsigned long long, unsigned long long> readHandles();

    unsigned int readObjFreeSpace();

    void readTemplate();

    void readObjects();

    void readFileHeaderAC15(DwgFileHeaderAC15 *fileheader,
                            IDwgStreamReader *sender);
    
    void readFileHeaderAC18(DwgFileHeaderAC18 *fileheader,
                            IDwgStreamReader *sender);
    
    void readFileHeaderAC21(DwgFileHeaderAC21 *fileheader,
                            IDwgStreamReader *sreader);
    
    void readFileMetaData(DwgFileHeaderAC18 *fileheader,
                          IDwgStreamReader *sreader);
    
    IDwgStreamReader *getSectionStream(const std::string &sectionName);
    
    void getPageHeaderData(IDwgStreamReader *sender, int64_t &sectionType,
                           int64_t &decompressedSize, int64_t &compressedSize,
                           int64_t &compressionType, int64_t &checksum);

    std::ifstream *getSectionBuffer15(DwgFileHeaderAC15 *fileheader, const std::string &section_name); 
    
    std::ifstream *getSectionBuffer18(DwgFileHeaderAC18 *fileheader, const std::string &section_name); 
    
    void decryptDataSection(const DwgLocalSectionMap &section, IDwgStreamReader *sreader);
    
    std::istringstream getSectionBuffer21(DwgFileHeaderAC21* fileheader, const std::string &sectionName);
    
    void reedSolomonDecoding(const std::vector<unsigned char> &encoded, std::vector<unsigned char> &buffer, int factor, int blockSize);
    
    std::vector<unsigned char> getPageBuffer(unsigned long long pageOffset, unsigned long long compressedSize, 
                unsigned long long uncompressedSize, unsigned long long correctionFactor, int blockSize, std::istream* stream);
};

}// namespace dwg
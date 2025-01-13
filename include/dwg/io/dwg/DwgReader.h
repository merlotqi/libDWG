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

#include <dwg/io/ICadReader.h>

namespace dwg {
namespace io {
class DwgDocumentBuilder;
class DwgFileHeader;
class IDwgStreamReader;
class DwgFileHeaderAC15;
}// namespace io
}// namespace dwg

namespace dwg {
namespace io {

class DwgReaderConfiguration : public CadReaderConfiguration
{
    bool m_crcCheck;

public:
    DwgReaderConfiguration() : CadReaderConfiguration() { m_crcCheck = false; }

    bool CrcCheck() const { return m_crcCheck; }
    void CrcCheck(bool value) { m_crcCheck = value; }
};


class DwgReader : public CadReaderBase<DwgReaderConfiguration>
{
    DwgDocumentBuilder *m_builder;
    DwgFileHeader *m_fileHeader;

public:
    DwgReader(const CPL::String &name);

    CadDoument *Read();
    CadSummaryInfo *ReadSummaryInfo();
    CadHeader *ReadHander();

private:
    DwgFileHeader *readFileHeader();
    std::map<uint64_t, int64_t> readHandles();
    uint32_t readObjFreeSpace();
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
    IDwgStreamReader *getSectionStream(const CPL::String &sectionName);
    void getPageHeaderData(IDwgStreamReader *sender, int64_t &sectionType,
                           int64_t &decompressedSize, int64_t &compressedSize,
                           int64_t &compressionType, int64_t &checksum);
};

}// namespace io
}// namespace dwg
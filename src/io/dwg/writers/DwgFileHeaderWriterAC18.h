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

#include "../fileheaders/DwgFileHeaderAC18.h"
#include "../fileheaders/DwgLocalSectionMap.h"
#include "../fileheaders/DwgSectionDescriptor.h"
#include "DwgFileHeaderWriterBase.h"
#include "ICompressor.h"
#include <sstream>
#include <iostream>

namespace dwg {
namespace io {

class DwgFileHeaderWriterAC18 : public DwgFileHeaderWriterBase
{
public:
    DwgFileHeaderWriterAC18(std::ofstream *stream, Encoding encoding,
                            CadDocument *document);

    int HandleSectionOffset() const;
    void WriteFile() override;
    void AddSection(const CPL::String &name, std::ostringstream *stream,
                    bool isCompressed, int decompsize = 0x7400) override;


protected:
    int _fileHeaderSize() const override;
    virtual void craeteLocalSection(DwgSectionDescriptor descriptor,
                                    const std::vector<unsigned char> &buffer,
                                    int decompressedSize,
                                    unsigned long long offset, int totalSize,
                                    bool isCompressed);
    std::ostringstream
    applyCompression(const std::vector<unsigned char> &buffer,
                     int decompressedSize, unsigned long long offset,
                     int totalSize, bool isCompressed);

private:
    void writeRecords();
    void writeDescriptors();
    void writeFileMetaData();
    void writeFileHeader(std::ostringstream* stream);
    void addSection(DwgLocalSectionMap section);
    DwgLocalSectionMap setSeeker(int map, std::ostringstream* stream);
    void compressChecksum(DwgLocalSectionMap section, std::ostringstream* stream);
    void writePageHeaderData(DwgLocalSectionMap section, std::ostream* stream);
    void writeDataSection(std::ostream* stream, DwgSectionDescriptor descriptor,
                          DwgLocalSectionMap map, int size);

    std::vector<DwgLocalSectionMap> _localSectionsMaps;
    std::map<CPL::String, DwgSectionDescriptor> _descriptors;

protected:
    DwgFileHeaderAC18 *_fileHeader;
    ICompressor *compressor;
};

}// namespace io
}// namespace dwg

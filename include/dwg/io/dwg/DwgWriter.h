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

#include <dwg/ACadVersion.h>
#include <dwg/io/CadWriterBase.h>
#include <dwg/io/CadWriterConfiguration.h>

namespace dwg {
namespace io {

class DwgFileHeader;
class IDwgFileHeaderWriter;
class LIBDWG_API DwgWriter : public CadWriterBase<CadWriterConfiguration>
{
private:
    ACadVersion _version;
    DwgFileHeader *_fileHeader;
    IDwgFileHeaderWriter *_fileHeaderWriter;

public:
    DwgWriter(std::ofstream *stream, CadDocument *document);
    void Write() override;

private:
    void getFileHeaderWriter();
    void writeHeader();
    void writeClasses();
    void writeSummaryInfo();
    void writePreview();
    void writeAppInfo();
    void writeFileDepList();
    void writeRevHistory();
    void writeAuxHeader();
    void writeObjects();
    void writeObjFreeSpace();
    void writeTemplate();
    void writeHandles();
};


}// namespace io
}// namespace dwg
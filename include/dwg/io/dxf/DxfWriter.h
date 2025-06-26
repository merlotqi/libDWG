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

#include <dwg/io/CadWriterBase.h>
#include <dwg/io/dxf/DxfWriterConfiguration.h>

namespace dwg {

class IDxfStreamWriter;
class CadObjectHolder;
class LIBDWG_API DxfWriter : public CadWriterBase<DxfWriterConfiguration>
{
public:
    DxfWriter(const std::string &filename, CadDocument *document, bool binary);
    DxfWriter(std::fstream *stream, CadDocument *document, bool binary);
    ~DxfWriter();

    void write() override;
    bool isBinaray() const;

private:
    void createStreamWriter();
    void writeHeader();
    void writeDxfClasses();
    void writeTables();
    void writeBlocks();
    void writeEntities();
    void writeObjects();
    void writeACDSData();

private:
    bool _binary = false;
    IDxfStreamWriter *_writer;
    CadObjectHolder *_objectHolder;
};

}// namespace dwg
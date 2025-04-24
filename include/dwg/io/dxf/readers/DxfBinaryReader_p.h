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

#include <dwg/io/dxf/readers/DxfStreamReaderBase_p.h>
#include <dwg/utils/Encoding.h>

namespace dwg {

class DxfBinaryReader : public DxfStreamReaderBase
{
public:
    static std::string Sentinel;
    DxfBinaryReader(std::istream *stream);
    DxfBinaryReader(std::istream *stream, Encoding encoding);
    virtual ~DxfBinaryReader();

    void start() override;

    std::string readStringLine() const override;
    DxfCode readCode() const override;
    bool lineAsBool() const override;
    double lineAsDouble() const override;
    short lineAsShort() const override;
    int lineAsInt() const override;
    long long lineAsLong() const override;
    unsigned long long lineAsHandle() const override;
    std::vector<unsigned char> lineAsBinaryChunk() const override; 
};

}// namespace dwg
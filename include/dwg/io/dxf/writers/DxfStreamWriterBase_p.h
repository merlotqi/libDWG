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

#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>

namespace dwg {

class DxfStreamWriterBase : public IDxfStreamWriter
{
public:
    DxfStreamWriterBase();

    virtual ~DxfStreamWriterBase();

    bool writeOptional() const;

    void write(DxfCode code, DwgVariant value, DxfClassMap *clsmap = nullptr) override;

    void write(int code, DwgVariant value, DxfClassMap *clsmap = nullptr) override;

    void writeTrueColor(int code, const Color &color, DxfClassMap *clsmap = nullptr) override;

    void writeCmColor(int code, const Color &color, DxfClassMap *clsmap = nullptr) override;

    void writeHandle(int code, IHandledCadObject *value, DxfClassMap *clsmap = nullptr) override;

    void writeName(int code, INamedCadObject *value, DxfClassMap *clsmap = nullptr) override;

protected:
    virtual void writeDxfCode(int code) = 0;
    virtual void writeValue(int code, DwgVariant value) = 0;

private:
    bool _writeOptional = false;
};

}// namespace dwg
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

#include <dwg/DxfCode.h>
#include <dwg/DwgVariant.h>

namespace dwg {

class DxfClassMap;
class IHandledCadObject;
class INamedCadObject;
class IDxfStreamWriter
{
public:
    virtual ~IDxfStreamWriter() = default;
    
    virtual void write(DxfCode code, DwgVariant value, DxfClassMap *clsmap = nullptr) = 0;
    
    virtual void write(int code, DwgVariant value, DxfClassMap *clsmap = nullptr) = 0;
    
    virtual void writeTrueColor(int code, const Color &color, DxfClassMap *clsmap = nullptr) = 0;
    
    virtual void writeCmColor(int code, const Color &color, DxfClassMap *clsmap = nullptr) = 0;
    
    virtual void writeHandle(int code, IHandledCadObject *value, DxfClassMap *clsmap = nullptr) = 0;
    
    virtual void writeName(int code, INamedCadObject *value, DxfClassMap *clsmap = nullptr) = 0;
    
    virtual void flush() = 0;
    
    virtual void close() = 0;
};

}// namespace dwg
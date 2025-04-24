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
#include <dwg/GroupCodeValueType.h>
#include <dwg/utils/DwgVariant.h>

namespace dwg {

class IDxfStreamReader
{
public:
    virtual ~IDxfStreamReader() = default;

    virtual DxfCode dxfCode() const = 0;
    virtual GroupCodeValueType groupCodeValue() const = 0;

    virtual int code() const = 0;
    virtual DwgVariant value() const = 0;

    virtual size_t position() const = 0;

    virtual std::string valueAsString() const = 0;
    virtual std::string valueRaw() const = 0;
    virtual bool valueAsBool() const = 0;
    virtual short valueAsShort() const = 0;
    virtual unsigned short valueAsUShort() const = 0;
    virtual int valueAsInt() const = 0;
    virtual unsigned int valueAsUInt() const = 0;
    virtual long long valueAsLongLong() const = 0;
    virtual unsigned long long valueAsHandle() const = 0;
    virtual double valueAsDouble() const = 0;
    virtual double valueAsAngle() const = 0;
    virtual std::vector<unsigned char> valueAsBinaryChunk() const = 0;

    virtual bool find(const std::string &) = 0;

    virtual void start() = 0;
    virtual void readNext() = 0;
    virtual void expectedCode(int code) = 0;
};

}// namespace dwg
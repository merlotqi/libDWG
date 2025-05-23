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

#include <dwg/DxfFileToken_p.h>
#include <dwg/GroupCodeValue.h>
#include <dwg/io/dxf/readers/DxfStreamReaderBase_p.h>

namespace dwg {

DxfStreamReaderBase::DxfStreamReaderBase()
    : _dxfcode(DxfCode::Invalid), _groupCodeValue(GroupCodeValueType::None), _position(0)
{
}

DxfStreamReaderBase::~DxfStreamReaderBase() {}

DxfCode DxfStreamReaderBase::dxfCode() const
{
    return _dxfcode;
}

GroupCodeValueType DxfStreamReaderBase::groupCodeValue() const
{
    return _groupCodeValue;
}

int DxfStreamReaderBase::code() const
{
    return (int) _dxfcode;
}

DwgVariant DxfStreamReaderBase::value() const
{
    return DwgVariant();
}

size_t DxfStreamReaderBase::position() const
{
    return 0;
}

std::string DxfStreamReaderBase::valueRaw() const
{
    return std::string();
}

std::string DxfStreamReaderBase::valueAsString() const
{
    return std::string();
}

bool DxfStreamReaderBase::valueAsBool() const
{
    return false;
}

short DxfStreamReaderBase::valueAsShort() const
{
    return 0;
}

unsigned short DxfStreamReaderBase::valueAsUShort() const
{
    return 0;
}

int DxfStreamReaderBase::valueAsInt() const
{
    return 0;
}

unsigned int DxfStreamReaderBase::valueAsUInt() const
{
    return 0;
}

long long DxfStreamReaderBase::valueAsLongLong() const
{
    return 0;
}

unsigned long long DxfStreamReaderBase::valueAsHandle() const
{
    return 0;
}

double DxfStreamReaderBase::valueAsDouble() const
{
    return 0.0;
}

double DxfStreamReaderBase::valueAsAngle() const
{
    return 0.0;
}

std::vector<unsigned char> DxfStreamReaderBase::valueAsBinaryChunk() const
{
    return std::vector<unsigned char>();
}

void DxfStreamReaderBase::readNext()
{
    _dxfcode = readCode();
    _groupCodeValue = GroupCodeValue::transformValue(code());
    _value = transformValue(_groupCodeValue);
}

bool DxfStreamReaderBase::find(const std::string &dxfEntry)
{
    start();
    do
    {
        readNext();

    } while (valueAsString() != dxfEntry && (valueAsString() != DxfFileToken::EndOfFile));

    return valueAsString() == dxfEntry;
}

void DxfStreamReaderBase::expectedCode(int code) {}

std::string DxfStreamReaderBase::toString() const
{
    return std::string();
}

void DxfStreamReaderBase::start()
{
    _dxfcode = DxfCode::Invalid;
    _value = DwgVariant::Empty();
}

DwgVariant DxfStreamReaderBase::transformValue(GroupCodeValueType code)
{
    return DwgVariant();
}

void DxfStreamReaderBase::setDxfCode(DxfCode) {}

void DxfStreamReaderBase::setGroupCodeValue(GroupCodeValueType) {}

void DxfStreamReaderBase::setPosition(size_t) {}

void DxfStreamReaderBase::setValueRaw(const std::string &) {}

}// namespace dwg
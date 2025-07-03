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
#include <dwg/utils/StringHelp.h>

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
    return _value;
}

size_t DxfStreamReaderBase::position() const
{
    return _position;
}

std::string DxfStreamReaderBase::valueRaw() const
{
    return _valueRaw;
}

std::string DxfStreamReaderBase::valueAsString() const
{
    if (_value.isEmpty())
        return std::string();

    std::string str = _value.convert<std::string>();
    str = StringHelp::replace(str, "^J", "\n");
    str = StringHelp::replace(str, "^M", "\r");
    str = StringHelp::replace(str, "^I", "\t");
    str = StringHelp::replace(str, "^ ", "^");
    return str;
}

bool DxfStreamReaderBase::valueAsBool() const
{
    if (_value.isEmpty())
        return false;

    return (_value.convert<unsigned char>() > 0) ? true : false;
}

short DxfStreamReaderBase::valueAsShort() const
{
    if (_value.isEmpty())
        return 0;

    return _value.convert<short>();
}

unsigned short DxfStreamReaderBase::valueAsUShort() const
{
    if (_value.isEmpty())
        return 0;

    return _value.convert<unsigned short>();
}

int DxfStreamReaderBase::valueAsInt() const
{
    if (_value.isEmpty())
        return 0;

    return _value.convert<int>();
}

unsigned int DxfStreamReaderBase::valueAsUInt() const
{
    if (_value.isEmpty())
        return 0;

    return _value.convert<unsigned int>();
}

long long DxfStreamReaderBase::valueAsLongLong() const
{
    if (_value.isEmpty())
        return 0LL;

    return _value.convert<long long>();
}

unsigned long long DxfStreamReaderBase::valueAsHandle() const
{
    if (_value.isEmpty())
        return 0ULL;

    return _value.convert<unsigned long long>();
}

double DxfStreamReaderBase::valueAsDouble() const
{
    if (_value.isEmpty())
        return 0.0;

    return _value.convert<double>();
}

double DxfStreamReaderBase::valueAsAngle() const
{
    if (_value.isEmpty())
        return 0.0;

    return _value.convert<double>();
}

std::vector<unsigned char> DxfStreamReaderBase::valueAsBinaryChunk() const
{
    if (_value.isEmpty())
        return std::vector<unsigned char>();

    return _value.convert<std::vector<unsigned char>>();
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
    return fmt::format("{} | {}", code(), valueRaw());
}

void DxfStreamReaderBase::start()
{
    _dxfcode = DxfCode::Invalid;
    _value = DwgVariant();
}

DwgVariant DxfStreamReaderBase::transformValue(GroupCodeValueType code)
{
    switch (code)
    {
        case GroupCodeValueType::String:
        case GroupCodeValueType::Comment:
        case GroupCodeValueType::ExtendedDataString:
            return readStringLine();
        case GroupCodeValueType::Point3D:
        case GroupCodeValueType::Double:
        case GroupCodeValueType::ExtendedDataDouble:
            return lineAsDouble();
        case GroupCodeValueType::Byte:
        case GroupCodeValueType::Int16:
        case GroupCodeValueType::ExtendedDataInt16:
            return lineAsShort();
        case GroupCodeValueType::Int32:
        case GroupCodeValueType::ExtendedDataInt32:
            return lineAsInt();
        case GroupCodeValueType::Int64:
            return lineAsLong();
        case GroupCodeValueType::Handle:
        case GroupCodeValueType::ObjectId:
        case GroupCodeValueType::ExtendedDataHandle:
            return lineAsHandle();
        case GroupCodeValueType::Bool:
            return lineAsBool();
        case GroupCodeValueType::Chunk:
        case GroupCodeValueType::ExtendedDataChunk:
            return lineAsBinaryChunk();
        case GroupCodeValueType::None:
        default:
            throw std::runtime_error(
                    fmt::format("Invalid dxf code with value {code}, at line {line}.", (int) code, position()));
    }
}

void DxfStreamReaderBase::setDxfCode(DxfCode) {}

void DxfStreamReaderBase::setGroupCodeValue(GroupCodeValueType) {}

void DxfStreamReaderBase::setPosition(size_t) {}

void DxfStreamReaderBase::setValueRaw(const std::string &) {}

}// namespace dwg
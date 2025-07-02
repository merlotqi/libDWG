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

#include <dwg/io/dxf/readers/DxfTextReader_p.h>
#include <dwg/utils/StringHelp.h>

namespace dwg {

DxfTextReader::DxfTextReader(std::iostream *stream, Encoding encoding)
    : _stream(stream), _encoding(encoding), _wrapper(_stream)
{
    _stream->seekg(std::ios::beg);
    start();
}

DxfTextReader::~DxfTextReader() {}

void DxfTextReader::readNext()
{
    DxfStreamReaderBase::readNext();
    _position += 2;
}

std::string DxfTextReader::readStringLine()
{
    std::string str;
    std::getline(*_stream, str);
    _valueRaw = str;
    return _valueRaw;
}

DxfCode DxfTextReader::readCode()
{
    std::string line = readStringLine();
    int value;
    if (StringHelp::tryParse32(line, value))
    {
        return DxfCode(value);
    }
    _position++;
    return DxfCode::Invalid;
}

bool DxfTextReader::lineAsBool()
{
    std::string str = readStringLine();
    unsigned char value;
    if (StringHelp::tryParseUnsigned8(str, value))
    {
        return value > 0;
    }
    return false;
}

double DxfTextReader::lineAsDouble()
{
    std::string str = readStringLine();
    double value;
    if (StringHelp::tryParseFloat(str, value))
    {
        return value;
    }
    return 0.0;
}

short DxfTextReader::lineAsShort()
{
    std::string str = readStringLine();
    short value;
    if (StringHelp::tryParse16(str, value))
    {
        return value;
    }
    return 0;
}

int DxfTextReader::lineAsInt()
{
    std::string str = readStringLine();
    int value;
    if (StringHelp::tryParse32(str, value))
    {
        return value;
    }
    return 0;
}

long long DxfTextReader::lineAsLong()
{
    std::string str = readStringLine();
    long long value;
    if (StringHelp::tryParse64(str, value))
    {
        return value;
    }
    return 0LL;
}

unsigned long long DxfTextReader::lineAsHandle()
{
    std::string str = readStringLine();
    unsigned long long value;
    if (StringHelp::tryParseUnsigned64(str, value))
    {
        return value;
    }
    return 0ULL;
}

std::vector<unsigned char> DxfTextReader::lineAsBinaryChunk()
{
    std::string str = readStringLine();

    std::vector<unsigned char> bytes(str.length(), 0);
    for (int i = 0; i < str.length(); ++i)
    {
        //Create a byte value
        std::string hex = fmt::format("{}{}", str[i], str[++i]);
        unsigned char value;
        if (StringHelp::tryParseUnsigned8(hex, value))
        {
            bytes[i] = value;
        }
        else
        {
            return std::vector<unsigned char>();
        }
    }

    return bytes;
}

}// namespace dwg
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

#include <dwg/io/dxf/readers/DxfBinaryReader_p.h>

namespace dwg {

std::string DxfBinaryReader::Sentinel = "AutoCAD Binary DXF\r\n\u001a\0";

DxfBinaryReader::DxfBinaryReader(std::istream *stream) : DxfBinaryReader(stream, Encoding(CodePage::Usascii)) {}

DxfBinaryReader::DxfBinaryReader(std::istream *stream, Encoding encoding)
    : _stream(stream), _encoding(encoding), _wrapper(InputStreamWrapper(_stream))
{
    start();
}

DxfBinaryReader::~DxfBinaryReader() {}

void DxfBinaryReader::start() 
{
    DxfStreamReaderBase::start();
    auto sentinel = _wrapper.readBytes(22);
    //AutoCAD Binary DXF\r\n\u001a\0
}

std::string DxfBinaryReader::readStringLine() 
{ 
    unsigned char b = _wrapper.readByte();
    std::vector<unsigned char> bytes;

    while (b != 0)
    {
        bytes.push_back(b);
        b = _wrapper.readByte();
    }

    _valueRaw = _encoding.toUtf8(std::string(bytes.begin(), bytes.end()));
    return _valueRaw;
}

DxfCode DxfBinaryReader::readCode()
{
    return DxfCode(_wrapper.readShort());
}

bool DxfBinaryReader::lineAsBool()
{
    return _wrapper.readByte() > 0;
}


double DxfBinaryReader::lineAsDouble()
{
    return _wrapper.readDouble();
}

short DxfBinaryReader::lineAsShort()
{
    return _wrapper.readShort();
}

int DxfBinaryReader::lineAsInt()
{
    return _wrapper.readInt();
}

long long DxfBinaryReader::lineAsLong()
{
    return _wrapper.readLong();
}

unsigned long long DxfBinaryReader::lineAsHandle()
{
    return _wrapper.readULong();
}

std::vector<unsigned char> DxfBinaryReader::lineAsBinaryChunk()
{
    unsigned char length = _wrapper.readByte();
    return _wrapper.readBytes(length);
}

}// namespace dwg
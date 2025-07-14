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

#include <dwg/GroupCodeValue.h>
#include <dwg/io/dxf/writers/DxfBinaryWriter_p.h>
#include <fmt/core.h>

namespace dwg {

DxfBinaryWriter::DxfBinaryWriter(std::fstream *stream, Encoding encoding) : _stream(stream), _encoding(encoding)
{
    //string sentinel = "AutoCAD Binary DXF\r\n\0";
    std::vector<unsigned char> sentinel = {65, 117, 116, 111, 67, 65, 68, 32, 66, 105, 110,
                                           97, 114, 121, 32,  68, 88, 70, 13, 10, 26,  0};

    _stream->write(reinterpret_cast<const char *>(sentinel.data()), sentinel.size());
}

void DxfBinaryWriter::flush()
{
    _stream->flush();
}

void DxfBinaryWriter::close()
{
    _stream->close();
}

void DxfBinaryWriter::writeDxfCode(int code)
{
    short sc = (short) code;
    _stream->write((const char *) &sc, sizeof(short));
}

void DxfBinaryWriter::writeValue(int code, DwgVariant value)
{
    GroupCodeValueType groupCode = GroupCodeValue::transformValue(code);

    switch (groupCode)
    {
        case GroupCodeValueType::None:
            break;
        case GroupCodeValueType::String:
        case GroupCodeValueType::Comment:
        case GroupCodeValueType::ExtendedDataString:
            {
                std::string v = value.convert<std::string>();
                _stream->write(v.c_str(), v.size());
                char c = '\0';
                _stream->write(reinterpret_cast<const char *>(&c), sizeof(char));
                return;
            }
            return;
        case GroupCodeValueType::Point3D:
        case GroupCodeValueType::Double:
        case GroupCodeValueType::ExtendedDataDouble:
            {
                double v = value.convert<double>();
                _stream->write(reinterpret_cast<const char *>(&v), sizeof(double));
            }
        case GroupCodeValueType::Byte:
        case GroupCodeValueType::Int16:
        case GroupCodeValueType::ExtendedDataInt16:
            {
                short v = value.convert<short>();
                _stream->write(reinterpret_cast<const char *>(&v), sizeof(short));
            }
        case GroupCodeValueType::Int32:
        case GroupCodeValueType::ExtendedDataInt32:
            {
                int v = value.convert<int>();
                _stream->write(reinterpret_cast<const char *>(&v), sizeof(int));
            }
        case GroupCodeValueType::Int64:
            {
                long long v = value.convert<long long>();
                _stream->write(reinterpret_cast<const char *>(&v), sizeof(long long));
            }
        case GroupCodeValueType::Handle:
        case GroupCodeValueType::ObjectId:
        case GroupCodeValueType::ExtendedDataHandle:
            {
            }
        case GroupCodeValueType::Bool:
            {
                bool v = value.convert<bool>();
                _stream->write(reinterpret_cast<const char *>(&v), sizeof(bool));
            }
        case GroupCodeValueType::Chunk:
        case GroupCodeValueType::ExtendedDataChunk:
            {
                std::vector<unsigned char> v = value.convert<std::vector<unsigned char>>();
            }
    }
}

}// namespace dwg
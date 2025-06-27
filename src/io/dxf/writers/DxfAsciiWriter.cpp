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

#include <dwg/io/dxf/writers/DxfAsciiWriter_p.h>
#include <fmt/core.h>
#include <dwg/GroupCodeValue.h>

namespace dwg {

DxfAsciiWriter::DxfAsciiWriter(std::fstream *stream, Encoding encoding): _stream(stream), _encoding(encoding) {}

void DxfAsciiWriter::flush()
{
    _stream->flush();
}

void DxfAsciiWriter::close()
{
    _stream->close();
}

void DxfAsciiWriter::writeDxfCode(int code) 
{
    if (code < 10)
    {
        *_stream << fmt::format("  {}", code) << std::endl;
    }
    else if (code < 100)
    {
        *_stream << fmt::format(" {}", code) << std::endl;
    }
    else
    {
        *_stream << fmt::format("{}", code) << std::endl;
    }
}

void DxfAsciiWriter::writeValue(int code, DwgVariant value) 
{
    GroupCodeValueType groupCode = GroupCodeValue::transformValue(code);

    switch (groupCode)
    {
        case GroupCodeValueType::None:
            break;
        case GroupCodeValueType::String:
        case GroupCodeValueType::Comment:
        case GroupCodeValueType::ExtendedDataString:
            *_stream << value.asString() << std::endl;
            return;
        case GroupCodeValueType::Point3D:
        case GroupCodeValueType::Double:
        case GroupCodeValueType::ExtendedDataDouble:
            *_stream << fmt::format("{:.15g}", value.asDouble()) << std::endl;
            return;
        case GroupCodeValueType::Int32:
        case GroupCodeValueType::ExtendedDataInt32:
            *_stream << fmt::format("{}", value.asInt()) << std::endl;
            return;
        case GroupCodeValueType::Int64:
            *_stream << fmt::format("{}", value.asLongLong()) << std::endl;
            return;
        case GroupCodeValueType::Handle:
        case GroupCodeValueType::ObjectId:
        case GroupCodeValueType::ExtendedDataHandle:
            *_stream << fmt::format("{:X}", value.asULongLong()) << std::endl;
            return;
        case GroupCodeValueType::Bool:
            *_stream << fmt::format("{}", value.asShort()) << std::endl;
            return;
        case GroupCodeValueType::Chunk:
        case GroupCodeValueType::ExtendedDataChunk:
            {
                std::vector<unsigned char> arr = value.asBlob();
                for (auto &&v: arr)
                {
                    std::string str = fmt::format("{:02X}", v);
                    _stream->write(str.data(), str.size());
                }
                *_stream << std::endl;
                return;
            }
    }

    *_stream << value.asString();
}

}// namespace dwg
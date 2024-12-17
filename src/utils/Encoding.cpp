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

#include <dwg/utils/Encoding.h>
#include <iconv.h>

namespace dwg {


Encoding::Encoding(CodePage codepage)
{
    _codePage = codePage;
}

Encoding::~Encoding()
{

}

std::vector<unsigned char> Encoding::GetBytes(const std::string& str) const
{

}

std::string Encoding::GetString(const std::vector<unsigned char>& bytes) const
{

}

std::string Encoding::GetString(const unsigned char* bytes, size_t length) const
{

}

Encoding Encoding::UTF8()
{
    Encoding coding(Utf8);
    return coding;
}

Encoding Encoding::Default()
{
    Encoding coding(Utf8);
    return coding;
}

Encoding Encoding::ASCII()
{
    Encoding coding(Usascii);
    return coding;
}

Encoding Encoding::Windows1252()
{
    Encoding coding(Windows1252);
    return coding;
}

Encoding Encoding::GBK()
{
    Encoding coding(Gb2312);
    return coding;
}

Encoding Encoding::GB18030();
{
    Encoding coding(Gb18030);
    return coding;
}


}// namespace dwg


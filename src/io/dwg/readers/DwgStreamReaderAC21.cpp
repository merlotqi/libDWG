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

#include <dwg/io/dwg/readers/DwgStreamReaderAC21_p.h>
#include <dwg/utils/EndianConverter.h>
#include <dwg/utils/StringHelp.h>

namespace dwg {

DwgStreamReaderAC21::DwgStreamReaderAC21(std::iostream *stream, bool resetPosition)
    : DwgStreamReaderAC18(stream, resetPosition)
{
}

DwgStreamReaderAC21::~DwgStreamReaderAC21() {}

std::string DwgStreamReaderAC21::readTextUtf8()
{
    short textLength = readShortT<LittleEndianConverter>();
    std::string value;
    if (textLength == 0)
    {
        value = "";
    }
    else
    {
        //Correct the text length by shifting 1 bit
        short length = (short) (textLength << 1);
        //Read the string and get rid of the empty bytes
        value = readString(length, Encoding(CodePage::Utf8));
        value = StringHelp::replace(value, "\0", "");
    }
    return value;
}

std::string DwgStreamReaderAC21::readVariableText()
{
    int textLength = readBitShort();
    std::string value;
    if (textLength == 0)
    {
        value = "";
    }
    else
    {
        //Correct the text length by shifting 1 bit
        short length = (short) (textLength << 1);
        //Read the string and get rid of the empty bytes
        value = readString(length, Encoding(CodePage::Utf8));
        value = StringHelp::replace(value, "\0", "");
    }
    return value;
}

}// namespace dwg
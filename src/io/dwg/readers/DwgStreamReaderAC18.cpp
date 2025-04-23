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

#include <dwg/io/dwg/readers/DwgStreamReaderAC18_p.h>
#include <dwg/utils/EndianConverter.h>

namespace dwg {

DwgStreamReaderAC18::DwgStreamReaderAC18(std::istream *stream, bool resetPosition)
    : DwgStreamReaderAC15(stream, resetPosition)
{
}

DwgStreamReaderAC18::~DwgStreamReaderAC18() {}

Color DwgStreamReaderAC18::readCmColor()
{
    Color color = Color(short(0));

    //CMC:
    //BS: color index(always 0)
    short colorIndex = readBitShort();
    //BL: RGB value
    //Always negative
    unsigned int rgb = (unsigned int) readBitLong();

    auto arr = LittleEndianConverter::instance()->bytes(rgb);

    if ((rgb & 0b0000'0001'0000'0000'0000'0000'0000'0000) != 0)
    {
        //Indexed color
        color = Color(short(arr[0]));
    }
    else
    {
        //CECOLOR:
        //3221225472
        //0b11000000000000000000000000000000
        //0b1100_0000_0000_0000_0000_0000_0000_0000 --> this should be ByLayer
        //0xC0000000

        //True color
        color = Color(arr[2], arr[1], arr[0]);
    }

    //RC: Color Byte(&1 => color name follows(TV),
    unsigned char id = readByte();

    std::string colorName;
    //RC: Color Byte(&1 => color name follows(TV),
    if ((id & 1) == 1)
    {
        colorName = readVariableText();
    }

    std::string bookName;
    //&2 => book name follows(TV))
    if ((id & 2) == 2)
    {
        bookName = readVariableText();
    }

    return color;
}

Color DwgStreamReaderAC18::readEnColor(Transparency &transparency, bool &isBookColor)
{
    Color color(short(0));
    transparency = Transparency::ByLayer;
    isBookColor = false;

    //BS : color number: flags + color index
    short size = readBitShort();

    if (size != 0)
    {
        //color flags: first byte of the bitshort.
        unsigned short flags = (unsigned short) ((unsigned short) size & 0b1111111100000000);

        //0x4000: has AcDbColor reference (0x8000 is also set in this case).
        if ((flags & 0x4000) > 0)
        {
            color = Color::ByBlock;
            //The handle to the color is written in the handle stream.
            isBookColor = true;
        }
        //0x8000: complex color (rgb).
        else if ((flags & 0x8000) > 0)
        {
            //Next value is a BS containing the RGB value(last 24 bits).
            //flags: 0b1100_0010_0000_0000_0000_0000_0000_0000
            unsigned int rgb = (unsigned int) readBitLong();
            auto arr = LittleEndianConverter::instance()->bytes(rgb);
            color = Color(arr[2], arr[1], arr[0]);
        }
        else
        {
            //Color index: if no flags were set, the color is looked up by the color number (ACI color).
            color = Color((short) (size & 0b111111111111));
        }

        //0x2000: color is followed by a transparency BL
        if ((flags & 0x2000) > 0U)
        {

            //The first byte represents the transparency type:
            //0 = BYLAYER,
            //1 = BYBLOCK,
            //3 = the transparency value in the last byte.
            int value = readBitLong();
            transparency = Transparency::FromAlphaValue(value);
        }
        else
        {
            transparency = Transparency::ByLayer;
        }
    }
    else
    {
        color = Color::ByBlock;
        transparency = Transparency::Opaque;
    }

    return color;
}

}// namespace dwg
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

#include <dwg/io/dwg/writers/DwgStreamWriterAC18_p.h>
#include <dwg/utils/EndianConverter.h>

namespace dwg {

DwgStreamWriterAC18::DwgStreamWriterAC18(std::ostream *stream, Encoding encoding)
    : DwgStreamWriterAC15(stream, encoding)
{
}

DwgStreamWriterAC18::~DwgStreamWriterAC18() {}

void DwgStreamWriterAC18::writeCmColor(const Color &value) 
{
			//CMC:
			//BS: color index(always 0)
			writeBitShort(0);

			unsigned char arr[4] = {0};

			if (value.isTrueColor())
			{
				arr[2] = (unsigned char)value.red();
				arr[1] = (unsigned char)value.green();
				arr[0] = (unsigned char)value.blue();
				arr[3] = 0b1100'0010;
			}
			else if (value.isByLayer())
			{
				arr[3] = 0b11000000;
			}
			else
			{
				arr[3] = 0b1100'0011;
				arr[0] = (unsigned char)value.index();
			}

			//BL: RGB value
			writeBitLong(LittleEndianConverter::instance()->toInt32(arr));

			//RC: Color Byte
			writeByte(0);

			//(&1 => color name follows(TV),
			//&2 => book name follows(TV))
}

void DwgStreamWriterAC18::writeEnColor(const Color &color, const Transparency &transparency) 
{
			//BS : color number: flags + color index
			unsigned short size = 0;

			if (color.isByBlock() && transparency.isByLayer())
			{
				writeBitShort(0);
				return;
			}

			//0x2000: color is followed by a transparency BL
			if (!transparency.isByLayer())
			{
				size = (unsigned short)(size | 0b10000000000000);
            }

			//0x8000: complex color (rgb).
			if (color.isTrueColor())
			{
				size = (unsigned short)(size | 0x8000);
			}
			else
			{
				//Color index: if no flags were set, the color is looked up by the color number (ACI color).
				size = (unsigned short)(size | (unsigned short)color.index());
			}

			writeBitShort((short)size);

			if (color.isTrueColor())
			{
				unsigned char arr[4] = { color.blue(), color.green(), color.red(), 0b11000010 };
				unsigned int rgb = LittleEndianConverter::instance()->toUInt32(arr);
				writeBitLong((int)rgb);
			}

			if (!transparency.isByLayer())
			{
				//The first byte represents the transparency type:
				//0 = BYLAYER,
				//1 = BYBLOCK,
				//3 = the transparency value in the last byte.
				writeBitLong(Transparency::ToAlphaValue(transparency));
			}
}

void DwgStreamWriterAC18::writeEnColor(const Color &color, const Transparency &transparency, bool isBookColor) 
{
			//BS : color number: flags + color index
			unsigned short size = 0;

			if (color.isByBlock() && transparency.isByLayer() && !isBookColor)
			{
				writeBitShort(0);
				return;
			}

			//0x2000: color is followed by a transparency BL
			if (!transparency.isByLayer())
			{
				size = (unsigned short)(size | 0b10000000000000);
			}

			//0x4000: has AcDbColor reference (0x8000 is also set in this case).
			if (isBookColor)
			{
				size = (unsigned short)(size | 0x4000);
				size = (unsigned short)(size | 0x8000);
			}
			//0x8000: complex color (rgb).
			else if (color.isTrueColor())
			{
				size = (unsigned short)(size | 0x8000);
			}
			else
			{
				//Color index: if no flags were set, the color is looked up by the color number (ACI color).
				size = (unsigned short)(size | (unsigned short)color.index());
			}

			writeBitShort((short)size);

			if (color.isTrueColor())
			{
                unsigned char arr[4] = { color.blue(), color.green(), color.red(), 0b11000010 };
				unsigned int rgb = LittleEndianConverter::instance()->toUInt32(arr);
				writeBitLong((int)rgb);
			}

			if (!transparency.isByLayer())
			{
				//The first byte represents the transparency type:
				//0 = BYLAYER,
				//1 = BYBLOCK,
				//3 = the transparency value in the last byte.
				writeBitLong(Transparency::ToAlphaValue(transparency));
			}
}

}// namespace dwg
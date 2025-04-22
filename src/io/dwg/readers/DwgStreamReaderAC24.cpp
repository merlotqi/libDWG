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

#include <dwg/ObjectType.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC24_p.h>


namespace dwg {

DwgStreamReaderAC24::DwgStreamReaderAC24(std::istream *stream, bool resetPosition)
    : DwgStreamReaderAC21(stream, resetPosition)
{
}

DwgStreamReaderAC24::~DwgStreamReaderAC24() {}

ObjectType DwgStreamReaderAC24::readObjectType()
{
	//A bit pair, followed by either 1 or 2 bytes, depending on the bit pair value:
	unsigned char pair = read2Bits();
	short value = 0;
	switch (pair)
	{
		//Read the following byte
		case 0:
			value = readByte();
			break;
		//Read following byte and add 0x1f0.
		case 1:
			value = (short)(0x1F0 + readByte());
			break;
		//Read the following two bytes (raw short)
		case 2:
			value = readShort();
			break;
		//The value 3 should never occur, but interpret the same as 2 nevertheless.
		case 3:
			value = readShort();
			break;
	}
	return (ObjectType)value;
}

}// namespace dwg
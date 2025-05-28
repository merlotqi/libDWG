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

#include <dwg/io/dwg/writers/DwgStreamWriterAC24_p.h>
#include <dwg/utils/EndianConverter.h>

namespace dwg {

DwgStreamWriterAC24::DwgStreamWriterAC24(std::ostream *stream, Encoding encoding)
    : DwgStreamWriterAC21(stream, encoding)
{
}

DwgStreamWriterAC24::~DwgStreamWriterAC24() {}

void DwgStreamWriterAC24::writeObjectType(short value) 
{
			//A bit pair, followed by either 1 or 2 bytes
			//Amount of bytes depens on the value
			if (value <= 255)
			{
				//Read the following byte
				write2Bits(0);
				writeByte((unsigned char)value);
			}
			else if (value >= 0x1F0 && value <= 0x2EF)
			{
				//Read following byte and add 0x1f0.
				write2Bits(1);
				writeByte((unsigned char)(value - 0x1F0));
			}
			else
			{
				//Read the following two bytes (raw short)
				write2Bits(2);
				writeBytes(LittleEndianConverter::instance()->bytes(value));
			}
}

}// namespace dwg
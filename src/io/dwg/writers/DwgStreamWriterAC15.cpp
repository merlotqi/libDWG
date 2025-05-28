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

#include <dwg/io/dwg/writers/DwgStreamWriterAC15_p.h>

namespace dwg {

DwgStreamWriterAC15::DwgStreamWriterAC15(std::ostream *stream, Encoding encoding)
    : DwgStreamWriterAC12(stream, encoding)
{
}

DwgStreamWriterAC15::~DwgStreamWriterAC15() {}

void DwgStreamWriterAC15::writeBitExtrusion(const XYZ &normal) 
{
			//For R2000, this is a single bit, followed optionally by 3BD.
			if (normal == XYZ::AxisZ)
			{
				//If the single bit is 1, 
				//the extrusion value is assumed to be 0,0,1 and no explicit extrusion is stored.
				writeBit(true);
				return;
			}

			//If the single bit is 0, 
			writeBit(false);
			//then it will be followed by 3BD.
			write3BitDouble(normal);
}

void DwgStreamWriterAC15::writeBitThickness(double thickness) 
{
			//For R2000+, this is a single bit followed optionally by a BD. 
			//If the bit is one, the thickness value is assumed to be 0.0. 
			//If the bit is 0, then a BD that represents the thickness follows.
			if (thickness == 0.0)
			{
				writeBit(true);
				return;
			}

			writeBit( false);
			writeBitDouble(thickness);
}

}// namespace dwg
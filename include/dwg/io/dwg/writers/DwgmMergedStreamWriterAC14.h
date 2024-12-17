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

#pragma once

#include <dwg/io/dwg/writers/DwgMergedStreamWriter.h>

namespace dwg {
namespace io {

class DwgmMergedStreamWriterAC14 : public DwgMergedStreamWriter
{
	public DwgmMergedStreamWriterAC14(std::ostream* stream, IDwgStreamWriter* main, IDwgStreamWriter* handle)
		: DwgMergedStreamWriter(stream, main, main, handle)
	{
	}

	 void WriteSpearShift() override
	{
		int pos = (int)this.Main.PositionInBits;

		if (this._savedPosition)
		{
			this.Main.WriteSpearShift();
			this.Main.SetPositionInBits(this.PositionInBits);
			this.Main.WriteRawLong(pos);
			this.Main.WriteShiftValue();
			this.Main.SetPositionInBits(pos);
		}

		this.HandleWriter.WriteSpearShift();
		this.Main.WriteBytes(((MemoryStream)this.HandleWriter.Stream).GetBuffer(), 0, (int)this.HandleWriter.Stream.Length);
		this.Main.WriteSpearShift();
	}
};

}
}
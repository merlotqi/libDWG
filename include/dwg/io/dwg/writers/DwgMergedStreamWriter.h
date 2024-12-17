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

#include <dwg/io/dwg/writers/IDwgStreamWriter.h>

namespace dwg {
namespace io {

class DwgMergedStreamWriter : public IDwgStreamWriter
{
	Encoding Encoding { get { return this.Main.Encoding; } }

	IDwgStreamWriter Main { get; }
    IDwgStreamWriter TextWriter { get; }
    IDwgStreamWriter HandleWriter { get; }
	Stream Stream { get; }
	long SavedPositionInBits { get; private set; }
	long PositionInBits { get; private set; }
	protected bool _savedPosition;
public:
	DwgMergedStreamWriter(Stream stream, IDwgStreamWriter main, IDwgStreamWriter textwriter, IDwgStreamWriter handlewriter);
	void HandleReference(IHandledCadObject cadObject);
	void HandleReference(DwgReferenceType type, IHandledCadObject cadObject);
	void HandleReference(ulong handle);
	void HandleReference(DwgReferenceType type, ulong handle);
	void ResetStream();
	void SavePositonForSize();
	void Write2RawDouble(XY value);
	void Write2BitDouble(XY value);
	void Write3BitDouble(XYZ value);
	void WriteBit(bool value);
	void Write2Bits(byte value);
	void WriteBitDouble(double value);
	void Write2BitDoubleWithDefault(XY def, XY value);
	void Write3BitDoubleWithDefault(XYZ def, XYZ value);
	void WriteBitDoubleWithDefault(double def, double value);
	void WriteBitExtrusion(XYZ value);
	void WriteBitLong(int value);
	void WriteBitLongLong(long value);
	void WriteBitShort(short value);
	void WriteBitThickness(double value);
	void WriteByte(byte value);
	void WriteBytes(byte[] bytes);
	void WriteCmColor(Color value);
	void WriteEnColor(Color color, Transparency transparency);
	void WriteDateTime(DateTime value);
	void Write8BitJulianDate(DateTime value);
	void WriteInt(int value);
	void WriteObjectType(short value);
	void WriteObjectType(ObjectType value);
	void WriteRawDouble(double value);
	void WriteRawLong(long value);
	void WriteRawShort(short value);
	void WriteRawShort(ushort value);
	virtual void WriteSpearShift();
	void WriteTimeSpan(TimeSpan value);
	void WriteVariableText(string value);
	void WriteTextUnicode(string value);
	void SetPositionInBits(long posInBits);
	void SetPositionByFlag(long pos);
	void WriteShiftValue();
	void WriteBytes(byte[] bytes, int offset, int length);
	void WriteEnColor(Color color, Transparency transparency, bool isBookColor);
};

}
}
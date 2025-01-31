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

#include <base.h>
#include <dwg/Color.h>
#include <dwg/DwgReferenceType.h>
#include <dwg/IHandledCadObject.h>
#include <dwg/ObjectType.h>
#include <dwg/Transparency.h>

#include <iostream>
#include <string>
#include <vector>

namespace dwg {
namespace io {

class IDwgStreamWriter
{
public:
    virtual Encoding Encoding() const = 0;
    virtual IDwgStreamWriter *Main() const = 0;
    virtual std::ostream *Stream() const = 0;
    virtual long long SetPositionInBits() const = 0;
    virtual long long SavedPositionInBits() const = 0;
    virtual void WriteBytes(const std::vector<unsigned char> &bytes) = 0;
    virtual void WriteBytes(const std::vector<unsigned char> &bytes, int offset,
                            int length) = 0;
    virtual void WriteInt(int value) = 0;
    virtual void WriteObjectType(short value) = 0;
    virtual void WriteObjectType(ObjectType value) = 0;
    virtual void WriteRawLong(long long value) = 0;
    virtual void WriteBitDouble(double value) = 0;
    virtual void WriteBitLong(int value) = 0;
    virtual void WriteBitLongLong(long long value) = 0;
    virtual void WriteVariableText(const std::string &value) = 0;
    virtual void WriteTextUnicode(const std::string &value) = 0;
    virtual void WriteBit(bool value) = 0;
    virtual void Write2Bits(unsigned char value) = 0;
    virtual void WriteBitShort(short value) = 0;
    virtual void WriteDateTime(DateTime value) = 0;
    virtual void Write8BitJulianDate(DateTime value) = 0;
    virtual void WriteTimeSpan(TimeSpan value) = 0;
    virtual void WriteCmColor(Color value) = 0;
    virtual void WriteEnColor(Color color, Transparency transparency) = 0;
    virtual void WriteEnColor(Color color, Transparency transparency,
                              bool isBookColor) = 0;
    virtual void Write2BitDouble(XY value) = 0;
    virtual void Write3BitDouble(XYZ value) = 0;
    virtual void Write2RawDouble(XY value) = 0;
    virtual void WriteByte(unsigned char value) = 0;
    virtual void HandleReference(unsigned long long handle) = 0;
    virtual void HandleReference(DwgReferenceType type,
                                 unsigned long long handle) = 0;
    virtual void WriteSpearShift() = 0;
    virtual void WriteRawShort(short value) = 0;
    virtual void WriteRawShort(unsigned short value) = 0;
    virtual void WriteRawDouble(double value) = 0;
    virtual void WriteBitThickness(double thickness) = 0;
    virtual void WriteBitExtrusion(XYZ normal) = 0;
    virtual void WriteBitDoubleWithDefault(double def, double value) = 0;
    virtual void Write2BitDoubleWithDefault(XY def, XY value) = 0;
    virtual void Write3BitDoubleWithDefault(XYZ def, XYZ value) = 0;
    virtual void ResetStream() = 0;
    virtual void SavePositonForSize() = 0;
    virtual void SetPositionInBits(long long posInBits) = 0;
    virtual void SetPositionByFlag(long long pos) = 0;
    virtual void WriteShiftValue() = 0;
};

}// namespace io
}// namespace dwg
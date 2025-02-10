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

#include <dwg/Color.h>
#include <dwg/Transparency.h>
#include <dwg/DwgReference.h>

namespace dwg {

class IHandledCadObject;

class IDwgStreamWriter
{
public:
    virtual IDwgStreamWriter() = default;

    virtual Encoding encoding() = 0;

    virtual IDwgStreamWriter* main() const = 0;

    virtual long long positionInBits() const = 0;

    virtual long long savedPositionInBits() const = 0;

    virtual void writeBytes(const std::vector<unsigned char> &bytes) = 0;

    virtual void writeBytes(const std::vector<unsigned char> &bytes, int offset, int length) = 0;

    virtual void writeInt(int value) = 0;

    virtual void writeObjectType(short value) = 0;

    virtual void writeObjectType(ObjectType value) = 0;

    virtual void writeRawLong(long long value) = 0;

    virtual void writeBitDouble(double value) = 0;

    virtual void writeBitLong(int value) = 0;

    virtual void writeBitLong(int value) = 0;

    virtual void writeBitLongLong(long long value) = 0;

    virtual void writeVariableText(string value) = 0;

    virtual void writeTextUnicode(string value) = 0;

    virtual void writeBit(bool value) = 0;

    virtual void write2Bits(unsigned char value) = 0;

    virtual void writeBitShort(short value) = 0;

    virtual void writeDateTime(time_t value) = 0;

    virtual void write8BitJulianDate(time_t value) = 0;

    virtual void writeTimeSpan(double value) = 0;

    virtual void writeCmColor(const Color &value) = 0;

    virtual void writeEnColor(const Color &color, const Transparency &transparency) = 0;

    virtual void writeEnColor(const Color &color, const Transparency &transparency, bool isBookColor) = 0;

    virtual void write2BitDouble(const XY &value) = 0;

    virtual void write3BitDouble(const XYZ &value) = 0;

    virtual void write2RawDouble(const XY &value) = 0;

    virtual void writeByte(unsigned char value) = 0;

    virtual void handleReference(IHandledCadObject* cadObject) = 0;

    virtual void handleReference(DwgReferenceType type, IHandledCadObject* cadObject) = 0;

    virtual void handleReference(unsigned long long handle) = 0;

    virtual void handleReference(DwgReferenceType type, unsigned long long handle) = 0;

    virtual void writeSpearShift() = 0;

    virtual void writeRawShort(short value) = 0;

    virtual void writeRawShort(unsigned short value) = 0;

    virtual void writeRawDouble(double value) = 0;

    virtual void writeBitThickness(double thickness) = 0;

    virtual void writeBitExtrusion(const XYZ &normal) = 0;

    virtual void writeBitDoubleWithDefault(double def, double value) = 0;

    virtual void write2BitDoubleWithDefault(const XY &def, const XY &value) = 0;

    virtual void write3BitDoubleWithDefault(const XYZ &def, const XYZ &value) = 0;

    virtual void resetStream() = 0;

    virtual void savePositonForSize() = 0;

    virtual void setPositionInBits(long long posInBits) = 0;

    virtual void setPositionByFlag(long long pos) = 0;

    virtual void writeShiftValue() = 0;
};

}
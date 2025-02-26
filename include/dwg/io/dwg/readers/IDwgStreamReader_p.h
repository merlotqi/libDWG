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
#include <dwg/Coordinate.h>
#include <dwg/DwgReferenceType.h>
#include <dwg/ObjectType.h>
#include <dwg/Transparency.h>
#include <dwg/utils/Encoding.h>
#include <vector>


namespace dwg {

class IDwgStreamReader
{
public:
    virtual Encoding encoding() const = 0;

    virtual void setEncoding(Encoding value) = 0;

    virtual int bitShift() = 0;

    virtual long long position() = 0;

    virtual void setPosition(long long) = 0;

    virtual unsigned char readByte() = 0;

    virtual short readShort() = 0;

    virtual long long setPositionByFlag(long long) = 0;

    virtual int readInt() = 0;

    virtual unsigned int readUInt() = 0;

    virtual double readDouble() = 0;

    virtual std::vector<unsigned char> readBytes(int length) = 0;

    virtual bool readBit() = 0;

    virtual short readBitAsShort() = 0;

    virtual unsigned char read2Bits() = 0;

    virtual short readBitShort() = 0;

    virtual bool readBitShortAsBool() = 0;

    virtual int readBitLong() = 0;

    virtual long long readBitLongLong() = 0;

    virtual double readBitDouble() = 0;

    virtual XY read2BitDouble() = 0;

    virtual XYZ read3BitDouble() = 0;

    virtual char readRawChar() = 0;

    virtual long long readRawLong() = 0;

    virtual unsigned long long readRawULong() = 0;

    virtual XYZ read2RawDouble() = 0;

    virtual XYZ read3RawDouble() = 0;

    virtual unsigned long long readModularChar() = 0;

    virtual int readSignedModularChar() = 0;

    virtual int readModularShort() = 0;

    virtual unsigned long long handleReference(unsigned long long referenceHandle) = 0;

    virtual unsigned long long handleReference(unsigned long long referenceHandle, DwgReferenceType &reference) = 0;

    virtual std::string readTextUtf8() = 0;

    virtual std::string readVariableText() = 0;

    virtual std::vector<unsigned char> readSentinel() = 0;

    virtual XY read2BitDoubleWithDefault(const XY &) = 0;

    virtual XYZ read3BitDoubleWithDefault(const XYZ &) = 0;

    virtual Color readCmColor() = 0;

    virtual Color readEnColor(Transparency &, bool &flag) = 0;

    virtual Color readColorByIndex() = 0;

    virtual ObjectType readObjectType() = 0;

    virtual XYZ readBitExtrusion() = 0;

    virtual double readBitDoubleWithDefault(double def) = 0;

    virtual double readBitThickness() = 0;

    virtual time_t read8BitJulianDate() = 0;

    virtual time_t readDateTime() = 0;

    virtual double readTimeSpan() = 0;

    virtual long long positionInBits() = 0;

    virtual void setPositionInBits(long positon) = 0;

    virtual void advanceByte() = 0;

    virtual void advance(int offset) = 0;

    virtual unsigned short resetShit() = 0;
};

}// namespace dwg
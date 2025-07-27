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
#include <dwg/utils/DateTime.h>
#include <dwg/utils/Encoding.h>
#include <iostream>
#include <vector>


namespace dwg {
/*
 NOTE: Unless otherwise stated, all data in this manual is in little-endian order, 
		with the least significant byte first.
    
	B : bit (1 or 0)
	BB : special 2 bit code (entmode in entities, for instance)
	3B : bit triplet (1-3 bits) (R24)
	BS : bitshort (16 bits)
	BL : bitlong (32 bits)
	BLL : bitlonglong (64 bits) (R24)
	BD : bitdouble
	2BD : 2D point (2 bitdoubles)
	3BD : 3D point (3 bitdoubles)
	RC : raw char (not compressed)
	RS : raw short (not compressed)
	RD : raw double (not compressed)
	RL : raw long (not compressed)
	2RD : 2 raw doubles
	3RD : 3 raw doubles
	MC : modular char
	MS : modular short
	H : handle reference (see the HANDLE REFERENCES section)
	T : text (bitshort length, followed by the string).
	TU : Unicode text (bitshort character length, followed by Unicode string, 
		2 bytes per character). Unicode text is read from the "string stream" 
		within the object data, see the main Object description section for details.
	TV : Variable text, T for 2004 and earlier files, TU for 2007+ files.
	X : special form
	U : unknown
	SN : 16 byte sentinel
	BE : BitExtrusion
	DD : BitDouble With Default
	BT : BitThickness
	3DD : 3D point as 3 DD, needing 3 default values
	CMC : CmColor value
	TC : True Color: this is the same format as CMC in R2004+.
	OT : Object type
 */
class IDwgStreamReader
{
public:
    virtual Encoding encoding() const = 0;

    virtual void setEncoding(Encoding value) = 0;

    virtual std::iostream *stream() = 0;

    virtual int bitShift() const = 0;

    virtual long long position() const = 0;

    virtual void setPosition(long long) = 0;

    virtual unsigned char readByte() = 0;

    virtual short readShort() = 0;

    template<typename T>
    short readShortT()
    {
        short v = readShort();
        short rv = T::instance()->toInt16(reinterpret_cast<const unsigned char *>(&v));
        return rv;
    }

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

    virtual XY read2RawDouble() = 0;

    virtual XYZ read3RawDouble() = 0;

    virtual unsigned long long readModularChar() = 0;

    virtual int readSignedModularChar() = 0;

    virtual int readModularShort() = 0;

    virtual unsigned long long handleReference() = 0;

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

    virtual DateTime read8BitJulianDate() = 0;

    virtual DateTime readDateTime() = 0;

    virtual Timespan readTimeSpan() = 0;

    virtual long long positionInBits() = 0;

    virtual void setPositionInBits(long long positon) = 0;

    virtual void advanceByte() = 0;

    virtual void advance(int offset) = 0;

    virtual unsigned short resetShift() = 0;

    virtual std::string readString(size_t length, Encoding encoding) = 0;
};

}// namespace dwg
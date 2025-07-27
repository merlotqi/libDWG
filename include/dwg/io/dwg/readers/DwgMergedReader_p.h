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

#include <dwg/io/dwg/readers/IDwgStreamReader_p.h>

namespace dwg {

class DwgMergedReader : public IDwgStreamReader
{
public:
    DwgMergedReader(IDwgStreamReader *mainReader, IDwgStreamReader *textReader, IDwgStreamReader *handleReader);
    ~DwgMergedReader();

    void advance(int offset) override;
    void advanceByte() override;
    unsigned long long handleReference() override;
    unsigned long long handleReference(unsigned long long referenceHandle) override;
    unsigned long long handleReference(unsigned long long referenceHandle, DwgReferenceType &reference) override;
    long long positionInBits() override;
    unsigned char read2Bits() override;
    XY read2RawDouble() override;
    XYZ read3RawDouble() override;
    XYZ read3BitDouble() override;
    bool readBit() override;
    short readBitAsShort() override;
    double readBitDouble() override;
    XY read2BitDouble() override;
    int readBitLong() override;
    long long readBitLongLong() override;
    short readBitShort() override;
    bool readBitShortAsBool() override;
    unsigned char readByte() override;
    std::vector<unsigned char> readBytes(int length) override;
    XY read2BitDoubleWithDefault(const XY &defValue) override;
    XYZ read3BitDoubleWithDefault(const XYZ &defValue) override;
    Color readCmColor() override;
    Color readEnColor(Transparency &transparency, bool &flag) override;
    DateTime read8BitJulianDate() override;
    DateTime readDateTime() override;
    double readDouble() override;
    int readInt() override;
    unsigned long long readModularChar() override;
    int readSignedModularChar() override;
    int readModularShort() override;
    Color readColorByIndex() override;
    ObjectType readObjectType() override;
    XYZ readBitExtrusion() override;
    double readBitDoubleWithDefault(double def) override;
    double readBitThickness() override;
    char readRawChar() override;
    unsigned long long readRawULong() override;
    std::vector<unsigned char> readSentinel() override;
    short readShort() override;
    std::string readTextUtf8() override;
    Timespan readTimeSpan() override;
    unsigned int readUInt() override;
    std::string readVariableText() override;
    unsigned short resetShift() override;
    void setPositionInBits(long long position) override;
    long long setPositionByFlag(long long position) override;

private:
    IDwgStreamReader *_mainReader;
    IDwgStreamReader *_textReader;
    IDwgStreamReader *_handleReader;
};

}// namespace dwg
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

#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/ACadVersion.h>

namespace dwg {

class DwgStreamWriterBase : public IDwgStreamWriter
{
public:
    static IDwgStreamWriter *GetStreamWriter(ACadVersion version, std::ostream *stream, Encoding encoding);
    static IDwgStreamWriter *GetMergedWriter(ACadVersion version, std::ostream *stream, Encoding encoding);

public:
    Encoding encoding() override;

    IDwgStreamWriter *main() const override;

    long long positionInBits() const override;

    long long savedPositionInBits() const override;

    void writeBytes(const std::vector<unsigned char> &bytes) override;

    void writeBytes(const std::vector<unsigned char> &bytes, int offset, int length) override;

    void writeInt(int value) override;

    void writeObjectType(short value) override;

    void writeObjectType(ObjectType value) override;

    void writeRawLong(long long value) override;

    void writeBitDouble(double value) override;

    void writeBitLong(int value) override;

    void writeBitLongLong(long long value) override;

    void writeVariableText(const std::string &value) override;

    void writeTextUtf8(const std::string &value) override;

    void writeBit(bool value) override;

    void write2Bits(unsigned char value) override;

    void writeBitShort(short value) override;

    void writeDateTime(time_t value) override;

    void write8BitJulianDate(time_t value) override;

    void writeTimeSpan(double value) override;

    void writeCmColor(const Color &value) override;

    void writeEnColor(const Color &color, const Transparency &transparency) override;

    void writeEnColor(const Color &color, const Transparency &transparency, bool isBookColor) override;

    void write2BitDouble(const XY &value) override;

    void write3BitDouble(const XYZ &value) override;

    void write2RawDouble(const XY &value) override;

    void writeByte(unsigned char value) override;

    void handleReference(IHandledCadObject *cadObject) override;

    void handleReference(DwgReferenceType type, IHandledCadObject *cadObject) override;

    void handleReference(unsigned long long handle) override;

    void handleReference(DwgReferenceType type, unsigned long long handle) override;

    void writeSpearShift() override;

    void writeRawShort(short value) override;

    void writeRawUShort(unsigned short value) override;

    void writeRawDouble(double value) override;

    void writeBitThickness(double thickness) override;

    void writeBitExtrusion(const XYZ &normal) override;

    void writeBitDoubleWithDefault(double def, double value) override;

    void write2BitDoubleWithDefault(const XY &def, const XY &value) override;

    void write3BitDoubleWithDefault(const XYZ &def, const XYZ &value) override;

    void resetStream() override;

    void savePositonForSize() override;

    void setPositionInBits(long long posInBits) override;

    void setPositionByFlag(long long pos) override;

    void writeShiftValue() override;
};

}// namespace dwg
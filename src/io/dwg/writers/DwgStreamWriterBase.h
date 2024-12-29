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

#include "IDwgStreamWriter.h"
#include <dwg/base/DwgStream.h>
#include <dwg/base/Encoding.h>

namespace dwg {
namespace io {


class DwgStreamWriterBase : public OutputStream, IDwgStreamWriter
{
protected:
    dwg::Encoding _encoding;

public:
    DwgStreamWriterBase(std::ostream *stream, dwg::Encoding encoding)
        : OutputStream(stream, false, false)
    {
        _encoding = encoding;
    }

    static IDwgStreamWriter *GetStreamWriter(ACadVersion version,
                                             std::ostream *stream,
                                             dwg::Encoding encoding);
    static IDwgStreamWriter *GetMergedWriter(ACadVersion version,
                                             std::ostream *stream,
                                             dwg::Encoding encoding);
    void Write(int value);
    virtual void WriteObjectType(short value) override;
    void WriteObjectType(ObjectType value) override;
    void WriteRawLong(long long value) override;
    void WriteBytes(const std::vector<unsigned char> &arr) override;
    void WriteBytes(const std::vector<unsigned char> &arr, size_t initialIndex,
                    size_t length);
    void WriteBitShort(short value) override;
    void WriteBitDouble(double value) override;
    void WriteBitLong(int value) override;
    void WriteBitLongLong(long long value) override;
    virtual void WriteVariableText(const std::string &value) override;
    virtual void WriteTextUnicode(const std::string &value) override;
    void Write2Bits(unsigned char value) override;
    void WriteBit(bool value) override;
    void WriteByte(unsigned char value) override;
    void WriteDateTime(DateTime value) override;
    void WriteTimeSpan(Timespan value) override;
    void Write8BitJulianDate(DateTime value) override;
    virtual void WriteCmColor(Color color) override;
    virtual void WriteEnColor(Color color, Transparency transparency) override;
    virtual void WriteEnColor(Color color, Transparency transparency,
                              bool isBookColor) override;
    void Write2BitDouble(XY value) override;
    void Write3BitDouble(XYZ value) override;
    void Write2RawDouble(XY value) override;
    void WriteRawShort(short value) override;
    void WriteRawShort(unsigned short value) override;
    void WriteRawDouble(double value) override;
    void HandleReference(unsigned long long handle) override;
    void HandleReference(DwgReferenceType type,
                         unsigned long long handle) override;
    void WriteSpearShift() override;
    virtual void WriteBitThickness(double thickness) override;
    virtual void WriteBitExtrusion(XYZ normal) override;
    void Write2BitDoubleWithDefault(XY def, XY value) override;
    void Write3BitDoubleWithDefault(XYZ def, XYZ value) override;
    void WriteBitDoubleWithDefault(double def, double value) override;
    void ResetStream() override;
    void SavePositonForSize() override;
    void SetPositionByFlag(long long pos) override;
    void SetPositionInBits(long long posInBits) override;
    void WriteShiftValue() override;

private:
    void resetShift();
    void write3Bits(unsigned char value);
};

}// namespace io
}// namespace dwg

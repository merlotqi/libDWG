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
#include "../../../DwgStream.h"
#include <base.h>

namespace dwg {
namespace io {


class DwgStreamWriterBase : public OutputStream, IDwgStreamWriter
{
protected:
    Encoding _encoding;

public:
    DwgStreamWriterBase(std::ostream *stream, Encoding encoding)
        : OutputStream(stream)
    {
        _encoding = encoding;
    }

    static IDwgStreamWriter *GetStreamWriter(ACadVersion version,
                                             std::ostream *stream,
                                             Encoding encoding);
    static IDwgStreamWriter *GetMergedWriter(ACadVersion version,
                                             std::ostream *stream,
                                             Encoding encoding);
    void Write(int value);
    virtual void WriteObjectType(short value);
    void WriteObjectType(ObjectType value);
    void WriteRawLong(long long value);
    void WriteBytes(const std::vector<unsigned char> &arr) override;
    void WriteBytes(const std::vector<unsigned char> &arr, size_t initialIndex,
                    size_t length);
    void WriteBitShort(short value);
    void WriteBitDouble(double value);
    void WriteBitLong(int value);
    void WriteBitLongLong(long long value);
    virtual void WriteVariableText(const std::string &value);
    virtual void WriteTextUnicode(const std::string &value);
    void Write2Bits(unsigned char value);
    void WriteBit(bool value);
    void WriteByte(unsigned char value);
    void WriteDateTime(DateTime value);
    void WriteTimeSpan(TimeSpan value);
    void Write8BitJulianDate(DateTime value);
    virtual void WriteCmColor(Color color);
    virtual void WriteEnColor(Color color, Transparency transparency);
    virtual void WriteEnColor(Color color, Transparency transparency,
                              bool isBookColor);
    void Write2BitDouble(XY value);
    void Write3BitDouble(XYZ value);
    void Write2RawDouble(XY value);
    void WriteRawShort(short value);
    void WriteRawShort(ushort value);
    void WriteRawDouble(double value);
    void HandleReference(IHandledCadObject *cadObject);
    void HandleReference(DwgReferenceType type, IHandledCadObject *cadObject);
    void HandleReference(unsigned long long handle);
    void HandleReference(DwgReferenceType type, unsigned long long handle);
    void WriteSpearShift();
    virtual void WriteBitThickness(double thickness);
    virtual void WriteBitExtrusion(XYZ normal);
    void Write2BitDoubleWithDefault(XY def, XY value);
    void Write3BitDoubleWithDefault(XYZ def, XYZ value);
    void WriteBitDoubleWithDefault(double def, double value);
    void ResetStream();
    void SavePositonForSize();
    void SetPositionByFlag(long long pos);
    void SetPositionInBits(long long posInBits);
    void WriteShiftValue();

private:
    void resetShift();
    void write3Bits(unsigned char value);
};

}// namespace io
}// namespace dwg

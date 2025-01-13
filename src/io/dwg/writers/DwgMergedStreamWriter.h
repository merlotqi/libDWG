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
protected:
    std::ostream *_stream;
    IDwgStreamWriter *_main;
    IDwgStreamWriter *_textWriter;
    IDwgStreamWriter *_handleWriter;
    bool _savedPosition;
    int64_t _savedPositionInBits;
    int64_t _positionInBits;

protected:
    Encoding Encoding() const;
    IDwgStreamWriter *Main();
    IDwgStreamWriter *TextWriter();
    IDwgStreamWriter *HandleWriter();
    Stream Stream { get; }
    int64_t SavedPositionInBits() const;
    void SavedPositionInBits(int64_t value);
    int64_t PositionInBits() const;
    void PositionInBits(int64_t value);

public:
    DwgMergedStreamWriter(std::ostream *stream, IDwgStreamWriter *main,
                          IDwgStreamWriter *textwriter,
                          IDwgStreamWriter *handlewriter);
    void HandleReference(IHandledCadObject *cadObject);
    void HandleReference(DwgReferenceType type, IHandledCadObject *cadObject);
    void HandleReference(uint64_t handle);
    void HandleReference(DwgReferenceType type, uint64_t handle);
    void ResetStream();
    void SavePositonForSize();
    void Write2RawDouble(XY value);
    void Write2BitDouble(XY value);
    void Write3BitDouble(XYZ value);
    void WriteBit(bool value);
    void Write2Bits(unsigned char value);
    void WriteBitDouble(double value);
    void Write2BitDoubleWithDefault(XY def, XY value);
    void Write3BitDoubleWithDefault(XYZ def, XYZ value);
    void WriteBitDoubleWithDefault(double def, double value);
    void WriteBitExtrusion(XYZ value);
    void WriteBitLong(int value);
    void WriteBitLongLong(int64_t value);
    void WriteBitShort(short value);
    void WriteBitThickness(double value);
    void WriteByte(unsigned char value);
    void WriteBytes(unsigned char[] bytes);
    void WriteCmColor(const Color &value);
    void WriteEnColor(const Color &color, Transparency transparency);
    void WriteDateTime(DateTime value);
    void Write8BitJulianDate(DateTime value);
    void WriteInt(int value);
    void WriteObjectType(short value);
    void WriteObjectType(ObjectType value);
    void WriteRawDouble(double value);
    void WriteRawLong(int64_t value);
    void WriteRawShort(short value);
    void WriteRawShort(unsigned short value);
    virtual void WriteSpearShift();
    void WriteTimeSpan(TimeSpan value);
    void WriteVariableText(const CPL::String &value);
    void WriteTextUnicode(const CPL::String &value);
    void SetPositionInBits(int64_t posInBits);
    void SetPositionByFlag(int64_t pos);
    void WriteShiftValue();
    void WriteBytes(const std::vector<unsigned char> &bytes, size_t offset,
                    size_t length);
    void WriteEnColor(Color color, Transparency transparency, bool isBookColor);
};

}// namespace io
}// namespace dwg
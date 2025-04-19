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

#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>

namespace dwg {

DwgStreamWriterBase::DwgStreamWriterBase(std::ostream *stream, Encoding encoding) {}

IDwgStreamWriter *DwgStreamWriterBase::GetStreamWriter(ACadVersion version, std::ostream *stream, Encoding encoding)
{
    return nullptr;
}
IDwgStreamWriter *DwgStreamWriterBase::GetMergedWriter(ACadVersion version, std::ostream *stream, Encoding encoding)
{
    return nullptr;
}
Encoding DwgStreamWriterBase::encoding()
{
    return Encoding();
}

IDwgStreamWriter *DwgStreamWriterBase::main() const
{
    return nullptr;
}

long long DwgStreamWriterBase::positionInBits() const
{
    return 0LL;
}

long long DwgStreamWriterBase::savedPositionInBits() const
{
    return 0LL;
}

void DwgStreamWriterBase::writeBytes(const std::vector<unsigned char> &bytes) {}

void DwgStreamWriterBase::writeBytes(const std::vector<unsigned char> &bytes, int offset, int length) {}

void DwgStreamWriterBase::writeInt(int value) {}

void DwgStreamWriterBase::writeObjectType(short value) {}

void DwgStreamWriterBase::writeObjectType(ObjectType value) {}

void DwgStreamWriterBase::writeRawLong(long long value) {}

void DwgStreamWriterBase::writeBitDouble(double value) {}

void DwgStreamWriterBase::writeBitLong(int value) {}

void DwgStreamWriterBase::writeBitLongLong(long long value) {}

void DwgStreamWriterBase::writeVariableText(const std::string &value) {}

void DwgStreamWriterBase::writeTextUtf8(const std::string &value) {}

void DwgStreamWriterBase::writeBit(bool value) {}

void DwgStreamWriterBase::write2Bits(unsigned char value) {}

void DwgStreamWriterBase::writeBitShort(short value) {}

void DwgStreamWriterBase::writeDateTime(const DateTime &value) {}

void DwgStreamWriterBase::write8BitJulianDate(const DateTime &value) {}

void DwgStreamWriterBase::writeTimeSpan(double value) {}

void DwgStreamWriterBase::writeCmColor(const Color &value) {}

void DwgStreamWriterBase::writeEnColor(const Color &color, const Transparency &transparency) {}

void DwgStreamWriterBase::writeEnColor(const Color &color, const Transparency &transparency, bool isBookColor) {}

void DwgStreamWriterBase::write2BitDouble(const XY &value) {}

void DwgStreamWriterBase::write3BitDouble(const XYZ &value) {}

void DwgStreamWriterBase::write2RawDouble(const XY &value) {}

void DwgStreamWriterBase::writeByte(unsigned char value) {}

void DwgStreamWriterBase::handleReference(IHandledCadObject *cadObject) {}

void DwgStreamWriterBase::handleReference(DwgReferenceType type, IHandledCadObject *cadObject) {}

void DwgStreamWriterBase::handleReference(unsigned long long handle) {}

void DwgStreamWriterBase::handleReference(DwgReferenceType type, unsigned long long handle) {}

void DwgStreamWriterBase::writeSpearShift() {}

void DwgStreamWriterBase::writeRawShort(short value) {}

void DwgStreamWriterBase::writeRawUShort(unsigned short value) {}

void DwgStreamWriterBase::writeRawDouble(double value) {}

void DwgStreamWriterBase::writeBitThickness(double thickness) {}

void DwgStreamWriterBase::writeBitExtrusion(const XYZ &normal) {}

void DwgStreamWriterBase::writeBitDoubleWithDefault(double def, double value) {}

void DwgStreamWriterBase::write2BitDoubleWithDefault(const XY &def, const XY &value) {}

void DwgStreamWriterBase::write3BitDoubleWithDefault(const XYZ &def, const XYZ &value) {}

void DwgStreamWriterBase::resetStream() {}

void DwgStreamWriterBase::savePositonForSize() {}

void DwgStreamWriterBase::setPositionInBits(long long posInBits) {}

void DwgStreamWriterBase::setPositionByFlag(long long pos) {}

void DwgStreamWriterBase::writeShiftValue() {}

}// namespace dwg
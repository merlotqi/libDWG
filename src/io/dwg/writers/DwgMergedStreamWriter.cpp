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

#include <dwg/io/dwg/writers/DwgMergedStreamWriter_p.h>

namespace dwg {

DwgMergedStreamWriter::DwgMergedStreamWriter(std::ostream *stream, IDwgStreamWriter *main, IDwgStreamWriter *textwriter,
                                             IDwgStreamWriter *handlewriter)
    : _stream(stream), _main(main), _textWriter(textwriter), _handleWriter(handlewriter)
{
}

DwgMergedStreamWriter::~DwgMergedStreamWriter() {}

std::ostream *DwgMergedStreamWriter::stream()
{
    return nullptr;
}

Encoding DwgMergedStreamWriter::encoding()
{
    return Encoding(CodePage::Utf8);
}

IDwgStreamWriter *DwgMergedStreamWriter::main()
{
    return _main;
}

long long DwgMergedStreamWriter::positionInBits() const
{
    return 0LL;
}

long long DwgMergedStreamWriter::savedPositionInBits() const
{
    return 0LL;
}

void DwgMergedStreamWriter::writeBytes(const std::vector<unsigned char> &bytes)
{
    _main->writeBytes(bytes);
}

void DwgMergedStreamWriter::writeBytes(const std::vector<unsigned char> &bytes, int offset, int length)
{
    _main->writeBytes(bytes, offset, length);
}

void DwgMergedStreamWriter::writeInt(int value)
{
    _main->writeInt(value);
}

void DwgMergedStreamWriter::writeObjectType(short value)
{
    _main->writeObjectType(value);
}

void DwgMergedStreamWriter::writeObjectType(ObjectType value)
{
    _main->writeObjectType(value);
}

void DwgMergedStreamWriter::writeRawLong(long long value)
{
    _main->writeRawLong(value);
}

void DwgMergedStreamWriter::writeBitDouble(double value)
{
    _main->writeBitDouble(value);
}

void DwgMergedStreamWriter::writeBitLong(int value)
{
    _main->writeBitLong(value);
}

void DwgMergedStreamWriter::writeBitLongLong(long long value)
{
    _main->writeBitLongLong(value);
}

void DwgMergedStreamWriter::writeVariableText(const std::string &value)
{
    _main->writeVariableText(value);
}

void DwgMergedStreamWriter::writeTextUtf8(const std::string &value)
{
    _main->writeTextUtf8(value);
}

void DwgMergedStreamWriter::writeBit(bool value)
{
    _main->writeBit(value);
}

void DwgMergedStreamWriter::write2Bits(unsigned char value)
{
    _main->write2Bits(value);
}

void DwgMergedStreamWriter::writeBitShort(short value)
{
    _main->writeBitShort(value);
}

void DwgMergedStreamWriter::writeDateTime(const DateTime &value)
{
    _main->writeDateTime(value);
}

void DwgMergedStreamWriter::write8BitJulianDate(const DateTime &value)
{
    _main->write8BitJulianDate(value);
}

void DwgMergedStreamWriter::writeTimeSpan(const Timespan &value)
{
    _main->writeTimeSpan(value);
}

void DwgMergedStreamWriter::writeCmColor(const Color &value) {}

void DwgMergedStreamWriter::writeEnColor(const Color &color, const Transparency &transparency) {}

void DwgMergedStreamWriter::writeEnColor(const Color &color, const Transparency &transparency, bool isBookColor) {}

void DwgMergedStreamWriter::write2BitDouble(const XY &value) {}

void DwgMergedStreamWriter::write3BitDouble(const XYZ &value) {}

void DwgMergedStreamWriter::write2RawDouble(const XY &value) {}

void DwgMergedStreamWriter::writeByte(unsigned char value) {}

void DwgMergedStreamWriter::handleReference(IHandledCadObject *cadObject)
{
    _handleWriter->handleReference(cadObject);
}

void DwgMergedStreamWriter::handleReference(DwgReferenceType type, IHandledCadObject *cadObject)
{
    _handleWriter->handleReference(type, cadObject);
}

void DwgMergedStreamWriter::handleReference(unsigned long long handle)
{
    _handleWriter->handleReference(handle);
}

void DwgMergedStreamWriter::handleReference(DwgReferenceType type, unsigned long long handle)
{
    _handleWriter->handleReference(type, handle);
}

void DwgMergedStreamWriter::writeSpearShift() {}

void DwgMergedStreamWriter::writeRawShort(short value)
{
    _main->writeRawShort(value);
}

void DwgMergedStreamWriter::writeRawUShort(unsigned short value)
{
    _main->writeRawUShort(value);
}

void DwgMergedStreamWriter::writeRawDouble(double value) {}

void DwgMergedStreamWriter::writeBitThickness(double thickness) {}

void DwgMergedStreamWriter::writeBitExtrusion(const XYZ &normal) {}

void DwgMergedStreamWriter::writeBitDoubleWithDefault(double def, double value) {}

void DwgMergedStreamWriter::write2BitDoubleWithDefault(const XY &def, const XY &value) {}

void DwgMergedStreamWriter::write3BitDoubleWithDefault(const XYZ &def, const XYZ &value) {}

void DwgMergedStreamWriter::resetStream() {}

void DwgMergedStreamWriter::savePositonForSize() {}

void DwgMergedStreamWriter::setPositionInBits(long long posInBits) {}

void DwgMergedStreamWriter::setPositionByFlag(long long pos) {}

void DwgMergedStreamWriter::writeShiftValue() {}

}// namespace dwg
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

#include <dwg/CadUtils.h>
#include <dwg/io/dwg/writers/DwgMergedStreamWriterAC14_p.h>
#include <dwg/io/dwg/writers/DwgMergedStreamWriter_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC12_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC15_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC18_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC21_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC24_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/utils/EndianConverter.h>
#include <fmt/core.h>
#include <sstream>
#include <stdexcept>

namespace dwg {

DwgStreamWriterBase::DwgStreamWriterBase(std::ostream *stream, Encoding encoding) : _stream(stream), _lastByte(0) {}

IDwgStreamWriter *DwgStreamWriterBase::GetStreamWriter(ACadVersion version, std::ostream *stream, Encoding encoding)
{
    switch (version)
    {
        case dwg::ACadVersion::Unknown:
            throw std::exception();
        case dwg::ACadVersion::MC0_0:
        case dwg::ACadVersion::AC1_2:
        case dwg::ACadVersion::AC1_4:
        case dwg::ACadVersion::AC1_50:
        case dwg::ACadVersion::AC2_10:
        case dwg::ACadVersion::AC1002:
        case dwg::ACadVersion::AC1003:
        case dwg::ACadVersion::AC1004:
        case dwg::ACadVersion::AC1006:
        case dwg::ACadVersion::AC1009:
            throw std::runtime_error(fmt::format("Dwg version not supported: ", CadUtils::GetNameFromVersion(version)));
        case dwg::ACadVersion::AC1012:
        case dwg::ACadVersion::AC1014:
            return new DwgStreamWriterAC12(stream, encoding);
        case dwg::ACadVersion::AC1015:
            return new DwgStreamWriterAC15(stream, encoding);
        case dwg::ACadVersion::AC1018:
            return new DwgStreamWriterAC18(stream, encoding);
        case dwg::ACadVersion::AC1021:
            return new DwgStreamWriterAC21(stream, encoding);
        case dwg::ACadVersion::AC1024:
        case dwg::ACadVersion::AC1027:
        case dwg::ACadVersion::AC1032:
            return new DwgStreamWriterAC24(stream, encoding);
        default:
            throw std::runtime_error(fmt::format("Dwg version not supported: ", CadUtils::GetNameFromVersion(version)));
    }
    return nullptr;
}

IDwgStreamWriter *DwgStreamWriterBase::GetMergedWriter(ACadVersion version, std::ostream *stream, Encoding encoding)
{
    switch (version)
    {
        case ACadVersion::Unknown:
            throw std::exception();
        case ACadVersion::MC0_0:
        case ACadVersion::AC1_2:
        case ACadVersion::AC1_4:
        case ACadVersion::AC1_50:
        case ACadVersion::AC2_10:
        case ACadVersion::AC1002:
        case ACadVersion::AC1003:
        case ACadVersion::AC1004:
        case ACadVersion::AC1006:
        case ACadVersion::AC1009:
            throw std::runtime_error(fmt::format("Dwg version not supported: ", CadUtils::GetNameFromVersion(version)));
        case ACadVersion::AC1012:
        case ACadVersion::AC1014:
            return new DwgmMergedStreamWriterAC14(stream, new DwgStreamWriterAC12(stream, encoding),
                                                  new DwgStreamWriterAC12(new std::ostringstream(), encoding));
        case ACadVersion::AC1015:
            return new DwgmMergedStreamWriterAC14(stream, new DwgStreamWriterAC15(stream, encoding),
                                                  new DwgStreamWriterAC15(new std::ostringstream(), encoding));
        case ACadVersion::AC1018:
            return new DwgmMergedStreamWriterAC14(stream, new DwgStreamWriterAC18(stream, encoding),
                                                  new DwgStreamWriterAC18(new std::ostringstream(), encoding));
        case ACadVersion::AC1021:
            return new DwgMergedStreamWriter(stream, new DwgStreamWriterAC21(stream, encoding),
                                             new DwgStreamWriterAC21(new std::ostringstream(), encoding),
                                             new DwgStreamWriterAC21(new std::ostringstream(), encoding));
        case ACadVersion::AC1024:
        case ACadVersion::AC1027:
        case ACadVersion::AC1032:
            return new DwgMergedStreamWriter(stream, new DwgStreamWriterAC24(stream, encoding),
                                             new DwgStreamWriterAC24(new std::ostringstream(), encoding),
                                             new DwgStreamWriterAC24(new std::ostringstream(), encoding));
        default:
            throw std::runtime_error(fmt::format("Dwg version not supported: ", CadUtils::GetNameFromVersion(version)));
    }
}

std::ostream *DwgStreamWriterBase::stream()
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

void DwgStreamWriterBase::writeObjectType(short value)
{
    writeBitShort(value);
}

void DwgStreamWriterBase::writeObjectType(ObjectType value)
{
    writeObjectType((short) value);
}

void DwgStreamWriterBase::writeRawLong(long long value)
{
    writeBytes(LittleEndianConverter::instance()->bytes(value));
}

void DwgStreamWriterBase::writeBitDouble(double value) {}

void DwgStreamWriterBase::writeBitLong(int value) {}

void DwgStreamWriterBase::writeBitLongLong(long long value) {}

void DwgStreamWriterBase::writeVariableText(const std::string &value) {}

void DwgStreamWriterBase::writeTextUtf8(const std::string &value) {}

void DwgStreamWriterBase::writeBit(bool value) {}

void DwgStreamWriterBase::write2Bits(unsigned char value)
{
    if (_bitShift < 6)
    {
        _lastByte |= (unsigned char) (value << 6 - _bitShift);
        _bitShift += 2;
    }
    else if (_bitShift == 6)
    {
        _lastByte |= value;
        _stream->write(reinterpret_cast<const char *>(&_lastByte), 1);
        resetShift();
    }
    else
    {
        _lastByte |= (unsigned char) (value >> 1);
        _stream->write(reinterpret_cast<const char *>(&_lastByte), 1);
        _lastByte = (unsigned char) (value << 7);
        _bitShift = 1;
    }
}

void DwgStreamWriterBase::writeBitShort(short value)
{
    if (value == 0)
    {
        write2Bits(2);
    }
    else if (value > 0 && value < 256)
    {
        write2Bits(1);
        writeByte((unsigned char) value);
    }
    else if (value == 256)
    {
        write2Bits(3);
    }
    else
    {
        write2Bits(0);
        writeByte((unsigned char) value);
        writeByte((unsigned char) (value >> 8));
    }
}

void DwgStreamWriterBase::writeDateTime(const DateTime &value)
{
    int jdata;
    int miliseconds;
    CadUtils::DateToJulian(value, jdata, miliseconds);

    writeBitLong(jdata);
    writeBitLong(miliseconds);
}

void DwgStreamWriterBase::write8BitJulianDate(const DateTime &value)
{
    int jdata;
    int miliseconds;
    CadUtils::DateToJulian(value, jdata, miliseconds);

    writeRawLong(jdata);
    writeRawLong(miliseconds);
}

void DwgStreamWriterBase::writeTimeSpan(const Timespan &value)
{
    writeBitLong(value.days());
    writeBitLong(value.milliseconds());
}

void DwgStreamWriterBase::writeCmColor(const Color &value)
{
    //R15 and earlier: BS color index
    short index = 0;
    if (value.isTrueColor())
    {
        index = value.approxIndex();
    }
    else
    {
        index = value.index();
    }

    writeBitShort(index);
}

void DwgStreamWriterBase::writeEnColor(const Color &color, const Transparency &transparency)
{
    writeCmColor(color);
}

void DwgStreamWriterBase::writeEnColor(const Color &color, const Transparency &transparency, bool isBookColor)
{
    writeCmColor(color);
}

void DwgStreamWriterBase::write2BitDouble(const XY &value)
{
    writeBitDouble(value.X);
    writeBitDouble(value.Y);
}

void DwgStreamWriterBase::write3BitDouble(const XYZ &value)
{
    writeBitDouble(value.X);
    writeBitDouble(value.Y);
    writeBitDouble(value.Z);
}

void DwgStreamWriterBase::write2RawDouble(const XY &value)
{
    writeRawDouble(value.X);
    writeRawDouble(value.Y);
}

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

void DwgStreamWriterBase::writeBitDoubleWithDefault(double def, double value)
{
    if (def == value)
    {
        //00 No more data present, use the value of the default double.
        write2Bits(0);
        return;
    }

    std::vector<unsigned char> defBytes = LittleEndianConverter::instance()->bytes(def);
    std::vector<unsigned char> valueBytes = LittleEndianConverter::instance()->bytes(value);

    //Compare the 2 sets of bytes by it's simetry
    int first = 0;
    int last = 7;
    while (last >= 0 && defBytes[last] == valueBytes[last])
    {
        first++;
        last--;
    }

    if (first >= 4)
    {
        //01 4 bytes of data are present. The result is the default double, with the 4 data bytes patched in
        //replacing the first 4 bytes of the default double(assuming little endian).
        write2Bits(1);
        writeBytes(defBytes, 0, 4);
    }
    else if (first >= 2)
    {
        //10 6 bytes of data are present. The result is the default double, with the first 2 data bytes patched in
        //replacing bytes 5 and 6 of the default double, and the last 4 data bytes patched in replacing the first 4
        //bytes of the default double(assuming little endian).
        write2Bits(2);
        writeByte(defBytes[4]);
        writeByte(defBytes[5]);
        writeByte(defBytes[0]);
        writeByte(defBytes[1]);
        writeByte(defBytes[2]);
        writeByte(defBytes[3]);
    }
    else
    {
        //11 A full RD follows.
        write2Bits(3);
        writeBytes(defBytes);
    }
}

void DwgStreamWriterBase::write2BitDoubleWithDefault(const XY &def, const XY &value)
{
    writeBitDoubleWithDefault(def.X, value.X);
    writeBitDoubleWithDefault(def.Y, value.Y);
}

void DwgStreamWriterBase::write3BitDoubleWithDefault(const XYZ &def, const XYZ &value)
{
    writeBitDoubleWithDefault(def.X, value.X);
    writeBitDoubleWithDefault(def.Y, value.Y);
    writeBitDoubleWithDefault(def.Z, value.Z);
}

void DwgStreamWriterBase::resetStream() {}

void DwgStreamWriterBase::savePositonForSize()
{
    writeRawLong(0);
}

void DwgStreamWriterBase::setPositionInBits(long long posInBits) {}

void DwgStreamWriterBase::setPositionByFlag(long long pos)
{
    if (pos >= 0x8000)
    {
        if (pos >= 0x40000000)
        {
            writeBytes(LittleEndianConverter::instance()->bytes((unsigned short) ((pos >> 30) & 0xFFFF)));
            writeBytes(LittleEndianConverter::instance()->bytes((unsigned short) (((pos >> 15) & 0x7FFF) | 0x8000)));
        }
        else
        {
            writeBytes(LittleEndianConverter::instance()->bytes((unsigned short) ((pos >> 15) & 0xFFFF)));
        }

        writeBytes(LittleEndianConverter::instance()->bytes((unsigned short) ((pos & 0x7FFF) | 0x8000)));
    }
    else
    {
        writeBytes(LittleEndianConverter::instance()->bytes((unsigned short) pos));
    }
}

void DwgStreamWriterBase::writeShiftValue() {}

void DwgStreamWriterBase::resetShift() {}

}// namespace dwg
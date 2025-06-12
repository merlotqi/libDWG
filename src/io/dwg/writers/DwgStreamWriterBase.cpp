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
#include <dwg/IHandledCadObject.h>
#include <dwg/io/dwg/writers/DwgMergedStreamWriterAC14_p.h>
#include <dwg/io/dwg/writers/DwgMergedStreamWriter_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC12_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC15_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC18_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC21_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterAC24_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/utils/EndianConverter.h>
#include <dwg/utils/StreamWrapper.h>
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
    return _stream;
}

Encoding DwgStreamWriterBase::encoding()
{
    return _encoding;
}

IDwgStreamWriter *DwgStreamWriterBase::main()
{
    return this;
}

long long DwgStreamWriterBase::positionInBits() const
{
    return _stream->tellp() * 8 + _bitShift;
}

long long DwgStreamWriterBase::savedPositionInBits() const
{
    return _savedPositionInBits;
}

void DwgStreamWriterBase::writeBytes(const std::vector<unsigned char> &bytes)
{
    OutputStreamWrapper wrapper(_stream);
    if (_bitShift == 0)
    {
        for (int i = 0; i < bytes.size(); ++i)
        {
            wrapper.write(bytes.at(i));
        }
        return;
    }

    int num = 8 - _bitShift;
    for (auto &&b: bytes)
    {
        wrapper.write((unsigned char) (_lastByte | (b >> _bitShift)));
        _lastByte = (unsigned char) (b << num);
    }
}

void DwgStreamWriterBase::writeBytes(const std::vector<unsigned char> &bytes, int initialIndex, int length)
{
    OutputStreamWrapper wrapper(_stream);
    if (_bitShift == 0)
    {
        for (int i = 0, j = initialIndex; i < length; ++i, ++j)
        {
            wrapper.write(bytes.at(j));
        }
        return;
    }

    int num = 8 - _bitShift;
    for (int i = 0, j = initialIndex; i < length; i++, j++)
    {
        unsigned char b = bytes[j];
        wrapper.write((unsigned char) (_lastByte | (b >> _bitShift)));
        _lastByte = (unsigned char) (b << num);
    }
}

void DwgStreamWriterBase::writeInt(int value)
{
    std::vector<unsigned char> arr = LittleEndianConverter::instance()->bytes(value);
    _stream->write(reinterpret_cast<const char *>(arr.data()), arr.size());
}

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

void DwgStreamWriterBase::writeBitDouble(double value)
{
    if (value == 0.0)
    {
        write2Bits(2);
        return;
    }

    if (value == 1.0)
    {
        write2Bits(1);
        return;
    }

    write2Bits(0);
    writeBytes(LittleEndianConverter::instance()->bytes(value));
}

void DwgStreamWriterBase::writeBitLong(int value)
{
    if (value == 0)
    {
        write2Bits(2);
        return;
    }

    if (value > 0 && value < 256)
    {
        write2Bits(1);
        writeByte((unsigned char) value);
        return;
    }

    write2Bits(0);
    writeByte((unsigned char) value);
    writeByte((unsigned char) (value >> 8));
    writeByte((unsigned char) (value >> 16));
    writeByte((unsigned char) (value >> 24));
}

void DwgStreamWriterBase::writeBitLongLong(long long value)
{
    unsigned char size = 0;
    unsigned long long unsignedValue = (unsigned long long) value;

    unsigned long long hold = unsignedValue;
    while (hold != 0)
    {
        hold >>= 8;
        size = (unsigned char) (size + 1);
    }

    write3Bits(size);

    hold = unsignedValue;
    for (int i = 0; i < size; ++i)
    {
        writeByte((unsigned char) (hold & 0xFF));
        hold >>= 8;
    }
}

void DwgStreamWriterBase::writeVariableText(const std::string &value)
{
    if (value.empty())
    {
        writeBitShort(0);
        return;
    }

    std::vector<unsigned char> bytes = _encoding.bytes(value);
    writeBitShort((short) (bytes.size()));
    writeBytes(bytes);
}

void DwgStreamWriterBase::writeTextUtf8(const std::string &value)
{
    std::vector<unsigned char> bytes = _encoding.bytes(value);
    writeRawUShort((unsigned short) (bytes.size() + 1));
    _stream->write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    _stream->write(0, 1);
}

void DwgStreamWriterBase::writeBit(bool value)
{
    OutputStreamWrapper wrapper(_stream);
    if (_bitShift < 7)
    {
        if (value)
        {
            _lastByte |= (unsigned char) ((1 << 7) - _bitShift);
        }
        _bitShift++;
        return;
    }

    if (value)
    {
        _lastByte |= 1;
    }

    wrapper.write(_lastByte);
    resetShift();
}

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

void DwgStreamWriterBase::writeByte(unsigned char value)
{
    OutputStreamWrapper wrapper(_stream);
    if (_bitShift == 0)
    {
        wrapper.write(1);
        return;
    }

    int shift = 8 - _bitShift;
    wrapper.write((unsigned char) (_lastByte | (value >> shift)));
    _lastByte = (unsigned char) (value << shift);
}

void DwgStreamWriterBase::handleReference(IHandledCadObject *cadObject)
{
    handleReference(DwgReferenceType::Undefined, cadObject);
}

void DwgStreamWriterBase::handleReference(DwgReferenceType type, IHandledCadObject *cadObject)
{
    if (!cadObject)
    {
        handleReference(type, 0ULL);
    }
    else
    {
        handleReference(type, cadObject->handle());
    }
}

void DwgStreamWriterBase::handleReference(unsigned long long handle)
{
    handleReference(DwgReferenceType::Undefined, handle);
}

void DwgStreamWriterBase::handleReference(DwgReferenceType type, unsigned long long handle)
{
    unsigned char b = (unsigned char) ((unsigned int) type << 4);

    if (handle == 0)
    {
        writeByte(b);
    }
    else if (handle < 0x100)
    {
        writeByte((unsigned char) (b | 1U));
        writeByte((unsigned char) handle);
    }
    else if (handle < 0x10000)
    {
        writeByte((unsigned char) (b | 2u));
        writeByte((unsigned char) (handle >> 8));
        writeByte((unsigned char) handle);
    }
    else if (handle < 0x1000000)
    {
        writeByte((unsigned char) (b | 3u));
        writeByte((unsigned char) (handle >> 16));
        writeByte((unsigned char) (handle >> 8));
        writeByte((unsigned char) handle);
    }
    else if (handle < 0x100000000L)
    {
        writeByte((unsigned char) (b | 4u));
        writeByte((unsigned char) (handle >> 24));
        writeByte((unsigned char) (handle >> 16));
        writeByte((unsigned char) (handle >> 8));
        writeByte((unsigned char) handle);
    }
    else if (handle < 0x10000000000L)
    {
        writeByte((unsigned char) (b | 5u));
        writeByte((unsigned char) (handle >> 32));
        writeByte((unsigned char) (handle >> 24));
        writeByte((unsigned char) (handle >> 16));
        writeByte((unsigned char) (handle >> 8));
        writeByte((unsigned char) handle);
    }
    else if (handle < 0x1000000000000L)
    {
        writeByte((unsigned char) (b | 6u));
        writeByte((unsigned char) (handle >> 40));
        writeByte((unsigned char) (handle >> 32));
        writeByte((unsigned char) (handle >> 24));
        writeByte((unsigned char) (handle >> 16));
        writeByte((unsigned char) (handle >> 8));
        writeByte((unsigned char) handle);
    }
    else if (handle < 0x100000000000000L)
    {
        writeByte((unsigned char) (b | 7u));
        writeByte((unsigned char) (handle >> 48));
        writeByte((unsigned char) (handle >> 40));
        writeByte((unsigned char) (handle >> 32));
        writeByte((unsigned char) (handle >> 24));
        writeByte((unsigned char) (handle >> 16));
        writeByte((unsigned char) (handle >> 8));
        writeByte((unsigned char) handle);
    }
    else
    {
        writeByte((unsigned char) (b | 8u));
        writeByte((unsigned char) (handle >> 56));
        writeByte((unsigned char) (handle >> 48));
        writeByte((unsigned char) (handle >> 40));
        writeByte((unsigned char) (handle >> 32));
        writeByte((unsigned char) (handle >> 24));
        writeByte((unsigned char) (handle >> 16));
        writeByte((unsigned char) (handle >> 8));
        writeByte((unsigned char) handle);
    }
}

void DwgStreamWriterBase::writeSpearShift()
{
    if (_bitShift > 0)
    {
        for (int i = _bitShift; i < 8; ++i)
        {
            writeBit(false);
        }
    }
}

void DwgStreamWriterBase::writeRawShort(short value)
{
    writeBytes(LittleEndianConverter::instance()->bytes(value));
}

void DwgStreamWriterBase::writeRawUShort(unsigned short value)
{
    writeBytes(LittleEndianConverter::instance()->bytes(value));
}

void DwgStreamWriterBase::writeRawDouble(double value)
{
    writeBytes(LittleEndianConverter::instance()->bytes(value));
}

void DwgStreamWriterBase::writeBitThickness(double thickness)
{
    //For R13-R14, this is a BD.
    writeBitDouble(thickness);
}

void DwgStreamWriterBase::writeBitExtrusion(const XYZ &normal)
{
    //For R13-R14 this is 3BD.
    write3BitDouble(normal);
}

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

void DwgStreamWriterBase::resetStream()
{
    // _stream->seekp(std::ios::beg);
    // resetShift();
    // _stream->setLength(0);
}

void DwgStreamWriterBase::savePositonForSize()
{
    writeRawLong(0);
}

void DwgStreamWriterBase::setPositionInBits(long long posInBits)
{
    // long position = posInBits / 8;
    // _bitShift = (int) (posInBits % 8);
    // _stream->seekp(position);

    // if (_bitShift > 0)
    // {
    //     int value = this._stream.ReadByte();
    //     if (value < 0)
    //     {
    //         throw std::runtime_error("End of stream");
    //     }
    //     _lastByte = (unsigned char) value;
    // }
    // else
    // {
    //     _lastByte = 0;
    // }

    // _stream->seekp(position);
}

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

void DwgStreamWriterBase::writeShiftValue()
{
    // if (_bitShift > 0)
    // {
    //     long position = this._stream.Position;
    //     int lastValue = this._stream.ReadByte();
    //     unsigned char currValue = (unsigned char) (_lastByte | ((unsigned char) lastValue & (0b11111111 >> _bitShift)));
    //     _stream.Position = position;
    //     _stream.WriteByte(currValue);
    // }
}

void DwgStreamWriterBase::resetShift()
{
    _bitShift = 0;
    _lastByte = 0;
}


void DwgStreamWriterBase::write3Bits(unsigned char value)
{
    writeBit((value & 4) != 0);
    writeBit((value & 2) != 0);
    writeBit((value & 1) != 0);
}
}// namespace dwg
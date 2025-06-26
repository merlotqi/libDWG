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

#include <dwg/io/dwg/readers/DwgStreamReaderAC12_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC15_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC18_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC21_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC24_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderBase_p.h>
#include <stdexcept>

namespace dwg {

DwgStreamReaderBase::DwgStreamReaderBase(std::iostream *stream, bool resetPosition) : _stream(stream), _wrapper(_stream)
{
    if (resetPosition)
    {
        _wrapper.seek(std::ios::beg);
    }
}

DwgStreamReaderBase::~DwgStreamReaderBase() {}

IDwgStreamReader *DwgStreamReaderBase::GetStreamHandler(ACadVersion version, std::iostream *stream, Encoding encoding,
                                                        bool resetPosition)
{
    IDwgStreamReader *reader = nullptr;

    switch (version)
    {
        case ACadVersion::Unknown:
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
            throw std::runtime_error("Not supported DWG version");
        case ACadVersion::AC1012:
        case ACadVersion::AC1014:
            reader = new DwgStreamReaderAC12(stream, resetPosition);
            break;
        case ACadVersion::AC1015:
            reader = new DwgStreamReaderAC15(stream, resetPosition);
            break;
        case ACadVersion::AC1018:
            reader = new DwgStreamReaderAC18(stream, resetPosition);
            break;
        case ACadVersion::AC1021:
            reader = new DwgStreamReaderAC21(stream, resetPosition);
            break;
        case ACadVersion::AC1024:
        case ACadVersion::AC1027:
        case ACadVersion::AC1032:
            reader = new DwgStreamReaderAC24(stream, resetPosition);
            break;
        default:
            throw std::runtime_error("Not supported DWG version");
    }

    if (encoding.codePage() != CodePage::Unknown)
    {
        reader->setEncoding(encoding);
    }
    return reader;
}

Encoding DwgStreamReaderBase::encoding() const
{
    return _encoding;
}

void DwgStreamReaderBase::setEncoding(Encoding value)
{
    _encoding = value;
}

std::iostream *DwgStreamReaderBase::stream()
{
    return nullptr;
}

int DwgStreamReaderBase::bitShift() const
{
    return _bitShift;
}

long long DwgStreamReaderBase::position() const
{
    return 0LL;
}

void DwgStreamReaderBase::setBitShift(int value)
{
    _bitShift = value;
}

void DwgStreamReaderBase::setPosition(long long) {}

bool DwgStreamReaderBase::isEmpty() const
{
    return false;
}

void DwgStreamReaderBase::setEmpty(bool) {}

unsigned char DwgStreamReaderBase::readByte()
{
    return _wrapper.readByte();
}

short DwgStreamReaderBase::readShort()
{
    return _wrapper.readShort();
}

long long DwgStreamReaderBase::setPositionByFlag(long long)
{
    return 0LL;
}

int DwgStreamReaderBase::readInt()
{
    return _wrapper.readInt();
}

unsigned int DwgStreamReaderBase::readUInt()
{
    return _wrapper.readUInt();
}

double DwgStreamReaderBase::readDouble()
{
    return _wrapper.readDouble();
}

std::vector<unsigned char> DwgStreamReaderBase::readBytes(int length)
{
    return _wrapper.readBytes(length);
}

bool DwgStreamReaderBase::readBit()
{
    if (_bitShift == 0)
    {
        advanceByte();
        bool result = (_lastByte & 128) == 128;
        _bitShift = 1;
        return result;
    }

    bool value = (_lastByte << _bitShift & 128) == 128;

    ++_bitShift;
    _bitShift &= 7;

    return value;
}

short DwgStreamReaderBase::readBitAsShort()
{
    return readBit() ? short(1) : short(0);
}

unsigned char DwgStreamReaderBase::read2Bits()
{
    unsigned char value;
    if (_bitShift == 0)
    {
        advanceByte();
        value = (unsigned char) ((unsigned int) _lastByte >> 6);
        _bitShift = 2;
    }
    else if (_bitShift == 7)
    {
        unsigned char lastValue = (unsigned char) (_lastByte << 1 & 2);
        advanceByte();
        value = (unsigned char) (lastValue | (unsigned int) (unsigned char) ((unsigned int) _lastByte >> 7));
        _bitShift = 1;
    }
    else
    {
        value = (unsigned char) (_lastByte >> 6 - _bitShift & 3);
        ++_bitShift;
        ++_bitShift;
        _bitShift &= 7;
    }

    return value;
}

short DwgStreamReaderBase::readBitShort()
{
    short value;
    switch (read2Bits())
    {
        case 0:
            {
                //00 : A short (2 bytes) follows, little-endian order (LSB first)
                value = _wrapper.readT<short, LittleEndianConverter>();
                break;
            }
        case 1:
            {
                //01 : An unsigned char (1 byte) follows
                if (_bitShift == 0)
                {
                    advanceByte();
                    value = _lastByte;
                    break;
                }
                value = applyShiftToLasByte();
                break;
            }
        case 2:
            {
                //10 : 0
                value = 0;
                break;
            }
        case 3:
            {
                //11 : 256
                value = 256;
                break;
            }
        default:
            throw std::runtime_error("");
    }
    return value;
}

bool DwgStreamReaderBase::readBitShortAsBool()
{
    return false;
}

int DwgStreamReaderBase::readBitLong()
{
    return 0;
}

long long DwgStreamReaderBase::readBitLongLong()
{
    return 0LL;
}

double DwgStreamReaderBase::readBitDouble()
{
    return 0.0;
}

XY DwgStreamReaderBase::read2BitDouble()
{
    return XY(0, 0);
}

XYZ DwgStreamReaderBase::read3BitDouble()
{
    return XYZ(0, 0, 0);
}

char DwgStreamReaderBase::readRawChar()
{
    return char(0);
}

long long DwgStreamReaderBase::readRawLong()
{
    return 0LL;
}

unsigned long long DwgStreamReaderBase::readRawULong()
{
    return 0ULL;
}

XYZ DwgStreamReaderBase::read2RawDouble()
{
    return XYZ(0, 0, 0);
}

XYZ DwgStreamReaderBase::read3RawDouble()
{
    return XYZ(0, 0, 0);
}

unsigned long long DwgStreamReaderBase::readModularChar()
{
    return 0ULL;
}

int DwgStreamReaderBase::readSignedModularChar()
{
    return 0;
}

int DwgStreamReaderBase::readModularShort()
{
    return 0;
}

unsigned long long DwgStreamReaderBase::handleReference(unsigned long long referenceHandle)
{
    return 0ULL;
}

unsigned long long DwgStreamReaderBase::handleReference(unsigned long long referenceHandle, DwgReferenceType &reference)
{
    return 0ULL;
}

std::string DwgStreamReaderBase::readTextUtf8()
{
    return std::string();
}

std::string DwgStreamReaderBase::readVariableText()
{
    return std::string();
}

std::vector<unsigned char> DwgStreamReaderBase::readSentinel()
{
    return std::vector<unsigned char>();
}

XY DwgStreamReaderBase::read2BitDoubleWithDefault(const XY &)
{
    return XY(0, 0);
}

XYZ DwgStreamReaderBase::read3BitDoubleWithDefault(const XYZ &)
{
    return XYZ(0, 0, 0);
}

Color DwgStreamReaderBase::readCmColor()
{
    return Color(short(0));
}

Color DwgStreamReaderBase::readEnColor(Transparency &, bool &flag)
{
    return Color(short(0));
}

Color DwgStreamReaderBase::readColorByIndex()
{
    return Color(short(0));
}

ObjectType DwgStreamReaderBase::readObjectType()
{
    return ObjectType::UNLISTED;
}

XYZ DwgStreamReaderBase::readBitExtrusion()
{
    return XYZ(0, 0, 0);
}

double DwgStreamReaderBase::readBitDoubleWithDefault(double def)
{
    return 0.0;
}

double DwgStreamReaderBase::readBitThickness()
{
    return 0.0;
}

DateTime DwgStreamReaderBase::read8BitJulianDate()
{
    return DateTime();
}

DateTime DwgStreamReaderBase::readDateTime()
{
    return DateTime();
}

double DwgStreamReaderBase::readTimeSpan()
{
    return 0.0;
}

long long DwgStreamReaderBase::positionInBits()
{
    return 0LL;
}

void DwgStreamReaderBase::setPositionInBits(long long positon) {}

void DwgStreamReaderBase::advanceByte() {}

void DwgStreamReaderBase::advance(int offset)
{
    if (offset > 1)
        _wrapper.seek(offset - 1 + _wrapper.pos());

    readByte();
}

unsigned short DwgStreamReaderBase::resetShift()
{
    if ((unsigned int) bitShift() > 0U)
        setBitShift(0);

    advanceByte();
    unsigned short num = _lastByte;
    advanceByte();

    return (unsigned short) (num | (unsigned int) (unsigned short) ((unsigned int) _lastByte << 8));
}

std::string DwgStreamReaderBase::readString(size_t length, Encoding encoding)
{
    if (length == 0)
        return std::string();

    std::vector<unsigned char> numArray = readBytes(length);
    return _encoding.toUtf8(reinterpret_cast<const char *>(numArray.data()));
}

void DwgStreamReaderBase::applyFlagToPosition(long long lastPos, long long &length, long long &strDataSize) {}

unsigned char DwgStreamReaderBase::applyShiftToLasByte()
{
    return 0;
}

void DwgStreamReaderBase::applyShiftToArr(int length, std::vector<unsigned char> &arr) {}

unsigned char DwgStreamReaderBase::read3bits()
{
    return 0;
}

DateTime DwgStreamReaderBase::julianToDate(int jdata, int miliseconds)
{
    return DateTime();
}

}// namespace dwg
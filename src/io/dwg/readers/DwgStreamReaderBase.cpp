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
    return _isEmpty;
}

void DwgStreamReaderBase::setEmpty(bool v)
{
    _isEmpty = v;
}

unsigned char DwgStreamReaderBase::readByte()
{
    if (bitShift() == 0)
    {
        // No need to apply the shift
        _lastByte = _wrapper.readByte();

        return _lastByte;
    }

    // Get the last bits from the last readed byte
    unsigned char lastValues = (unsigned char) ((unsigned int) _lastByte << bitShift());

    _lastByte = _wrapper.readByte();

    return (unsigned char) (lastValues | (unsigned int) (unsigned char) ((unsigned int) _lastByte >> 8 - bitShift()));
}

short DwgStreamReaderBase::readShort()
{
    return _wrapper.readShort();
}

long long DwgStreamReaderBase::setPositionByFlag(long long position)
{
    setPositionInBits(position);

    //String stream present bit (last bit in pre-handles section).
    bool flag = readBit();

    long long startPosition = position;
    if (flag)
    {
        // String stream present

        //If 1, then the "endbit" location should be decremented by 16 bytes
        long long length = 0;
        long long size = 0;
        applyFlagToPosition(position, length, size);

        startPosition = length - size;

        setPositionInBits(startPosition);
    }
    else
    {
        // mark as empty
        setEmpty(true);
        // There is no information, set the position to the end
        setPosition(_wrapper.pos());
    }

    return startPosition;
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
    std::vector<unsigned char> numArray(length, 0);
    applyShiftToArr(length, numArray);
    return numArray;
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
    return (readBitShort() != 0);
}

int DwgStreamReaderBase::readBitLong()
{
    int value;
    auto t = read2Bits();
    switch (t)
    {
        case 0:
            // 00 : A long (4 bytes) follows, little-endian order (LSB first)
            {
                value = _wrapper.readT<int, LittleEndianConverter>();
                break;
            }
        case 1:
            // 01 : An unsigned char (1 byte) follows
            {
                if (bitShift() == 0)
                {
                    advanceByte();
                    value = _lastByte;
                    break;
                }
                value = applyShiftToLasByte();
                break;
            }
        case 2:
            // 10 : 0
            {
                value = 0;
                break;
            }
        default:
            // 11 : not used
            throw std::runtime_error("Failed to read ReadBitLong");
    }
    return value;
}

long long DwgStreamReaderBase::readBitLongLong()
{
    unsigned long long value = 0;
    unsigned char size = read3bits();

    for (int i = 0; i < size; ++i)
    {
        unsigned long b = readByte();
        value += b << (i << 3);
    }
    return (long long) value;
}

double DwgStreamReaderBase::readBitDouble()
{
    double value;
    auto t = read2Bits();
    switch (t)
    {
        case 0:
            {
                value = _wrapper.readT<double, LittleEndianConverter>();
                break;
            }
        case 1:
            {
                value = 1.0;
                break;
            }
        case 2:
            {
                value = 0.0;
                break;
            }
        default:
            throw std::runtime_error("");
    }
    return value;
}

XY DwgStreamReaderBase::read2BitDouble()
{
    return XY(readBitDouble(), readBitDouble());
}

XYZ DwgStreamReaderBase::read3BitDouble()
{
    return XYZ(readBitDouble(), readBitDouble(), readBitDouble());
}

char DwgStreamReaderBase::readRawChar()
{
    return (char) readByte();
}

long long DwgStreamReaderBase::readRawLong()
{
    return _wrapper.readT<int, LittleEndianConverter>();
}

unsigned long long DwgStreamReaderBase::readRawULong()
{
    return _wrapper.readT<unsigned long long, LittleEndianConverter>();
}

XY DwgStreamReaderBase::read2RawDouble()
{
    return XY(readDouble(), readDouble());
}

XYZ DwgStreamReaderBase::read3RawDouble()
{
    return XYZ(readDouble(), readDouble(), readDouble());
}

unsigned long long DwgStreamReaderBase::readModularChar()
{
    int shift = 0;
    unsigned char lastByte = readByte();

    // remove the flag
    unsigned long long value = (unsigned long long) (lastByte & 0b01111111);

    if ((lastByte & 0b10000000) != 0)
    {
        while (true)
        {
            shift += 7;
            unsigned char last = readByte();
            value |= (unsigned long long) (last & 0b01111111) << shift;

            // check flag
            if ((last & 0b10000000) == 0)
                break;
        }
    }

    return value;
}

int DwgStreamReaderBase::readSignedModularChar()
{
    //Modular characters are a method of storing compressed integer values. They are used in the object map to
    //indicate both handle offsets and file location offsets.They consist of a stream of bytes, terminating when
    //the high bit of the byte is 0.
    int value;

    if (bitShift() == 0)
    {
        //No shift, read normal
        advanceByte();

        //Check if the current byte
        if ((_lastByte & 0b10000000) == 0)//Check the flag
        {
            //Drop the flags
            value = _lastByte & 0b00111111;

            //Check the sign flag
            if ((_lastByte & 0b01000000) > 0U)
                value = -value;
        }
        else
        {
            int totalShift = 0;
            int sum = _lastByte & SCHAR_MAX;
            while (true)
            {
                //Shift to apply
                totalShift += 7;
                advanceByte();

                //Check if the highest byte is 0
                if ((_lastByte & 0b10000000) != 0)
                    sum |= (_lastByte & SCHAR_MAX) << totalShift;
                else
                    break;
            }

            //Drop the flags at the las byte, and add it's value
            value = sum | (_lastByte & 0b00111111) << totalShift;

            //Check the sign flag
            if ((_lastByte & 0b01000000) > 0U)
                value = -value;
        }
    }
    else
    {
        //Apply the shift to each byte
        unsigned char lastByte = applyShiftToLasByte();
        if ((lastByte & 0b10000000) == 0)
        {
            //Drop the flags
            value = lastByte & 0b00111111;

            //Check the sign flag
            if ((lastByte & 0b01000000) > 0U)
                value = -value;
        }
        else
        {
            int totalShift = 0;
            int sum = lastByte & SCHAR_MAX;
            unsigned char currByte;
            while (true)
            {
                //Shift to apply
                totalShift += 7;
                currByte = applyShiftToLasByte();

                //Check if the highest byte is 0
                if ((currByte & 0b10000000) != 0)
                    sum |= (currByte & SCHAR_MAX) << totalShift;
                else
                    break;
            }

            //Drop the flags at the las byte, and add it's value
            value = sum | (currByte & 0b00111111) << totalShift;

            //Check the sign flag
            if ((currByte & 0b01000000) > 0U)
                value = -value;
        }
    }
    return value;
}

int DwgStreamReaderBase::readModularShort()
{
    int shift = 0b1111;

    //Read the bytes that form the short
    unsigned char b1 = readByte();
    unsigned char b2 = readByte();

    bool flag = (b2 & 0b10000000) == 0;

    //Set the value in little endian
    int value = b1 | (b2 & 0b1111111) << 8;

    while (!flag)
    {
        //Read 2 more bytes
        b1 = readByte();
        b2 = readByte();

        //Check the flag
        flag = (b2 & 0b10000000) == 0;

        //Set the value in little endian
        value |= b1 << shift;
        shift += 8;
        value |= (b2 & 0b1111111) << shift;

        //Update the shift
        shift += 7;
    }

    return value;
}

unsigned long long DwgStreamReaderBase::handleReference()
{
    DwgReferenceType _;
    return handleReference(0ULL, _);
}

unsigned long long DwgStreamReaderBase::handleReference(unsigned long long referenceHandle)
{
    DwgReferenceType _;
    return handleReference(referenceHandle, _);
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
    //Get the bytes form the default value
    std::vector<unsigned char> arr = LittleEndianConverter::instance()->bytes(def);

    switch (read2Bits())
    {
        //00 No more data present, use the value of the default double.
        case 0:
            return def;
        //01 4 bytes of data are present. The result is the default double, with the 4 data bytes patched in
        //replacing the first 4 bytes of the default double(assuming little endian).
        case 1:
            if (bitShift() == 0)
            {
                advanceByte();
                arr[0] = _lastByte;
                advanceByte();
                arr[1] = _lastByte;
                advanceByte();
                arr[2] = _lastByte;
                advanceByte();
                arr[3] = _lastByte;
            }
            else
            {
                int shift = 8 - bitShift();
                arr[0] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[0] |= (unsigned char) ((unsigned int) _lastByte >> shift);
                arr[1] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[1] |= (unsigned char) ((unsigned int) _lastByte >> shift);
                arr[2] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[2] |= (unsigned char) ((unsigned int) _lastByte >> shift);
                arr[3] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[3] |= (unsigned char) ((unsigned int) _lastByte >> shift);
            }
            return LittleEndianConverter::instance()->toDouble(arr.data());
        //10 6 bytes of data are present. The result is the default double, with the first 2 data bytes patched in
        //replacing bytes 5 and 6 of the default double, and the last 4 data bytes patched in replacing the first 4
        //bytes of the default double(assuming little endian).
        case 2:
            if (bitShift() == 0)
            {
                advanceByte();
                arr[4] = _lastByte;
                advanceByte();
                arr[5] = _lastByte;
                advanceByte();
                arr[0] = _lastByte;
                advanceByte();
                arr[1] = _lastByte;
                advanceByte();
                arr[2] = _lastByte;
                advanceByte();
                arr[3] = _lastByte;
            }
            else
            {
                arr[4] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[4] |= (unsigned char) ((unsigned int) _lastByte >> 8 - bitShift());
                arr[5] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[5] |= (unsigned char) ((unsigned int) _lastByte >> 8 - bitShift());
                arr[0] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[0] |= (unsigned char) ((unsigned int) _lastByte >> 8 - bitShift());
                arr[1] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[1] |= (unsigned char) ((unsigned int) _lastByte >> 8 - bitShift());
                arr[2] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[2] |= (unsigned char) ((unsigned int) _lastByte >> 8 - bitShift());
                arr[3] = (unsigned char) ((unsigned int) _lastByte << bitShift());
                advanceByte();
                arr[3] |= (unsigned char) ((unsigned int) _lastByte >> 8 - bitShift());
            }
            return LittleEndianConverter::instance()->toDouble(arr.data());
        //11 A full RD follows.
        case 3:
            return readDouble();
        default:
            throw std::exception();
    }
}

double DwgStreamReaderBase::readBitThickness()
{
    return readBitDouble();
}

DateTime DwgStreamReaderBase::read8BitJulianDate()
{
    return julianToDate(readInt(), readInt());
}

DateTime DwgStreamReaderBase::readDateTime()
{
    return julianToDate(readBitLong(), readBitLong());
}

Timespan DwgStreamReaderBase::readTimeSpan()
{
    return Timespan();
}

long long DwgStreamReaderBase::positionInBits()
{
    return 0LL;
}

void DwgStreamReaderBase::setPositionInBits(long long positon) {}

void DwgStreamReaderBase::advanceByte()
{
    _lastByte = _wrapper.readByte();
}

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
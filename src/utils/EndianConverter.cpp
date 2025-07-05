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

#include <dwg/utils/EndianConverter.h>

namespace dwg {

std::vector<unsigned char> EndianConverter::bytes(char value)
{
    return bytesT<char>(value);
}

std::vector<unsigned char> EndianConverter::bytes(short value)
{
    return bytesT<short>(value);
}

std::vector<unsigned char> EndianConverter::bytes(unsigned short value)
{
    return bytesT<unsigned short>(value);
}

std::vector<unsigned char> EndianConverter::bytes(int value)
{
    return bytesT<int>(value);
}

std::vector<unsigned char> EndianConverter::bytes(unsigned int value)
{
    return bytesT<unsigned int>(value);
}

std::vector<unsigned char> EndianConverter::bytes(long long value)
{
    return bytesT<long long>(value);
}

std::vector<unsigned char> EndianConverter::bytes(unsigned long long value)
{
    return bytesT<unsigned long long>(value);
}

std::vector<unsigned char> EndianConverter::bytes(double value)
{
    return bytesT<double>(value);
}

std::vector<unsigned char> EndianConverter::bytes(float value)
{
    return bytesT<float>(value);
}

char EndianConverter::toChar(const unsigned char *bytes)
{
    return fromBytesT<char>(bytes);
}

int16_t EndianConverter::toInt16(const unsigned char *bytes)
{
    return fromBytesT<int16_t>(bytes);
}

uint16_t EndianConverter::toUInt16(const unsigned char *bytes)
{
    return fromBytesT<uint16_t>(bytes);
}

int32_t EndianConverter::toInt32(const unsigned char *bytes)
{
    return fromBytesT<int32_t>(bytes);
}

uint32_t EndianConverter::toUInt32(const unsigned char *bytes)
{
    return fromBytesT<uint32_t>(bytes);
}

int64_t EndianConverter::toInt64(const unsigned char *bytes)
{
    return fromBytesT<int64_t>(bytes);
}

uint64_t EndianConverter::toUInt64(const unsigned char *bytes)
{
    return fromBytesT<uint64_t>(bytes);
}

float EndianConverter::toFloat(const unsigned char *bytes)
{
    return fromBytesT<float>(bytes);
}

double EndianConverter::toDouble(const unsigned char *bytes)
{
    return fromBytesT<double>(bytes);
}

char EndianConverter::toChar(const unsigned char *bytes, std::size_t offset)
{
    return 0;
}

int16_t EndianConverter::toInt16(const unsigned char *bytes, std::size_t offset)
{
    return 0;
}

uint16_t EndianConverter::toUInt16(const unsigned char *bytes, std::size_t offset)
{
    return 0;
}

int32_t EndianConverter::toInt32(const unsigned char *bytes, std::size_t offset)
{
    return 0;
}
uint32_t EndianConverter::toUInt32(const unsigned char *bytes, std::size_t offset)
{
    return 0;
}

int64_t EndianConverter::toInt64(const unsigned char *bytes, std::size_t offset)
{
    return 0;
}

uint64_t EndianConverter::toUInt64(const unsigned char *bytes, std::size_t offset)
{
    return 0;
}

float EndianConverter::toFloat(const unsigned char *bytes, std::size_t offset)
{
    return 0.0;
}

double EndianConverter::toDouble(const unsigned char *bytes, std::size_t offset)
{
    return 0.0;
}

class DefaultEndianConverter : public EndianConverter
{
public:
    DefaultEndianConverter() = default;
    ~DefaultEndianConverter() = default;

protected:
    void byteswap(unsigned char *buffer, size_t length) override {}
};

class InverseConverter : public EndianConverter
{
public:
    InverseConverter() = default;
    ~InverseConverter() = default;

protected:
    void byteswap(unsigned char *buffer, size_t length) override
    {
        unsigned char *swap = new unsigned char[length];
        for (size_t i = 0; i < length; ++i)
        {
            swap[i] = buffer[length - 1 - i];
        }
        memcpy(buffer, swap, length);
        delete[] swap;
    }
};

std::unique_ptr<EndianConverter> BigEndianConverter::instance()
{
    if constexpr (is_little_endian)
    {
        return std::unique_ptr<EndianConverter>(new InverseConverter());
    }
    else
    {
        return std::unique_ptr<EndianConverter>(new DefaultEndianConverter());
    }
}

std::unique_ptr<EndianConverter> LittleEndianConverter::instance()
{
    if constexpr (is_little_endian)
    {
        return std::unique_ptr<EndianConverter>(new DefaultEndianConverter());
    }
    else
    {
        return std::unique_ptr<EndianConverter>(new InverseConverter());
    }
}

}// namespace dwg
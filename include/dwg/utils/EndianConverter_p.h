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

namespace dwg {

struct byte_order
{
    static constexpr unsigned short value = 0x0102;
    static constexpr auto is_little_endian = (value & 0xFF) == 0x02;
};

constexpr bool is_little_endian = byte_order::is_little_endian;
constexpr bool is_big_endian = !byte_order::is_little_endian;

class EndianConverter
{
public:
    EndianConverter() = default;
    std::vector<unsigned char> bytes(char value);
    std::vector<unsigned char> bytes(short value);
    std::vector<unsigned char> bytes(unsigned short value);
    std::vector<unsigned char> bytes(int value);
    std::vector<unsigned char> bytes(unsigned int value);
    std::vector<unsigned char> bytes(long long value);
    std::vector<unsigned char> bytes(unsigned long long value);
    std::vector<unsigned char> bytes(double value);
    std::vector<unsigned char> bytes(float value);
    char toChar(const unsigned char *bytes);
    int16_t toInt16(const unsigned char *bytes);
    uint16_t toUInt16(const unsigned char *bytes);
    int32_t toInt32(const unsigned char *bytes);
    uint32_t toUint32(const unsigned char *bytes);
    int64_t toInt64(const unsigned char *bytes);
    uint64_t toUInt64(const unsigned char *bytes);
    float toFloat(const unsigned char *bytes);
    double toDouble(const unsigned char *bytes);

    template<class T>
    std::vector<unsigned char> bytesT(T value)
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                      "T must be integral number or floating point number.");
        constexpr size_t sz = sizeof(T);
        std::vector<unsigned char> buffer;
        buffer.resize(sz);
        byteswap(buffer.data(), sz);
        memcpy(buffer.data(), &value, sz);
        return buffer;
    }

    template<class T>
    T fromBytesT(const unsigned char *bytes)
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                      "T must be integral number or floating point number.");
        constexpr size_t sz = sizeof(T);
        std::vector<unsigned char> buffer;
        buffer.resize(sz);
        std::memcpy(buffer.data(), bytes, sz);
        byteswap(buffer.data(), sz);
        T value;
        std::memcpy(&value, buffer.data(), sz);
        return value;
    }

protected:
    virtual void byteswap(unsigned char *buffer, size_t length) = 0;
};

class BigEndianConverter : public EndianConverter
{
public:
    BigEndianConverter() = default;
    ~BigEndianConverter() = default;
    static std::unique_ptr<EndianConverter> instance();
};

class LittleEndianConverter : public EndianConverter
{
public:
    LittleEndianConverter() = default;
    ~LittleEndianConverter() = default;
    static std::unique_ptr<EndianConverter> instance();
};

}// namespace dwg
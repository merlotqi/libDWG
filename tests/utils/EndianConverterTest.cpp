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
#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <cstring>

using namespace dwg;

class EndianConverterTest : public ::testing::Test 
{
protected:
    std::unique_ptr<EndianConverter> bigEndianConverter;
    std::unique_ptr<EndianConverter> littleEndianConverter;

    void SetUp() override {
        bigEndianConverter = BigEndianConverter::instance();
        littleEndianConverter = LittleEndianConverter::instance();
    }
};

// Test char conversion
TEST_F(EndianConverterTest, CharConversion) 
{
    char original = 'A';
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    char bigEndianResult = bigEndianConverter->toChar(bigEndianBytes.data());
    char littleEndianResult = littleEndianConverter->toChar(littleEndianBytes.data());

    EXPECT_EQ(original, bigEndianResult);
    EXPECT_EQ(original, littleEndianResult);
}

// Test short conversion
TEST_F(EndianConverterTest, ShortConversion) 
{
    short original = 12345;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    short bigEndianResult = bigEndianConverter->toInt16(bigEndianBytes.data());
    short littleEndianResult = littleEndianConverter->toInt16(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test unsigned short conversion
TEST_F(EndianConverterTest, UnsignedShortConversion) 
{
    unsigned short original = 12345;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    unsigned short bigEndianResult = bigEndianConverter->toUInt16(bigEndianBytes.data());
    unsigned short littleEndianResult = littleEndianConverter->toUInt16(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test int conversion
TEST_F(EndianConverterTest, IntConversion) 
{
    int original = 123456789;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    int bigEndianResult = bigEndianConverter->toInt32(bigEndianBytes.data());
    int littleEndianResult = littleEndianConverter->toInt32(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test unsigned int conversion
TEST_F(EndianConverterTest, UnsignedIntConversion) 
{
    unsigned int original = 123456789;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    unsigned int bigEndianResult = bigEndianConverter->toUInt32(bigEndianBytes.data());
    unsigned int littleEndianResult = littleEndianConverter->toUInt32(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test long long conversion
TEST_F(EndianConverterTest, LongLongConversion) 
{
    long long original = 123456789123456789;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    long long bigEndianResult = bigEndianConverter->toInt64(bigEndianBytes.data());
    long long littleEndianResult = littleEndianConverter->toInt64(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test unsigned long long conversion
TEST_F(EndianConverterTest, UnsignedLongLongConversion) 
{
    unsigned long long original = 123456789123456789;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    unsigned long long bigEndianResult = bigEndianConverter->toUInt64(bigEndianBytes.data());
    unsigned long long littleEndianResult = littleEndianConverter->toUInt64(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test float conversion
TEST_F(EndianConverterTest, FloatConversion) 
{
    float original = 123.456f;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    float bigEndianResult = bigEndianConverter->toFloat(bigEndianBytes.data());
    float littleEndianResult = littleEndianConverter->toFloat(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test double conversion
TEST_F(EndianConverterTest, DoubleConversion) 
{
    double original = 123.456789;
    auto bigEndianBytes = bigEndianConverter->bytes(original);
    auto littleEndianBytes = littleEndianConverter->bytes(original);

    double bigEndianResult = bigEndianConverter->toDouble(bigEndianBytes.data());
    double littleEndianResult = littleEndianConverter->toDouble(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test template-based byte conversion for integral types
TEST_F(EndianConverterTest, TemplateIntegralConversion) 
{
    int original = 123456789;
    auto bigEndianBytes = bigEndianConverter->bytesT(original);
    auto littleEndianBytes = littleEndianConverter->bytesT(original);

    int bigEndianResult = bigEndianConverter->fromBytesT<int>(bigEndianBytes.data());
    int littleEndianResult = littleEndianConverter->fromBytesT<int>(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}

// Test template-based byte conversion for floating point types
TEST_F(EndianConverterTest, TemplateFloatingPointConversion) 
{
    float original = 123.456f;
    auto bigEndianBytes = bigEndianConverter->bytesT(original);
    auto littleEndianBytes = littleEndianConverter->bytesT(original);

    float bigEndianResult = bigEndianConverter->fromBytesT<float>(bigEndianBytes.data());
    float littleEndianResult = littleEndianConverter->fromBytesT<float>(littleEndianBytes.data());

    if (is_little_endian)
    {
        EXPECT_NE(original, bigEndianResult);   
        EXPECT_EQ(original, littleEndianResult);
    }
    else
    {
        EXPECT_EQ(original, bigEndianResult);
        EXPECT_NE(original, littleEndianResult);
    }
}
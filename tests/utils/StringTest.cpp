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

#include <dwg/utils/StringHelp.h>
#include <gtest/gtest.h>

using namespace dwg;

TEST(StringTest, Replace) {
    EXPECT_EQ(StringHelp::replace("hello world", "world", "C++"), "hello C++");
    EXPECT_EQ(StringHelp::replace("hello world", "o", "O"), "hellO wOrld");
    EXPECT_EQ(StringHelp::replace("test", "no", "yes"), "test");
}

TEST(StringTest, Parse) {
    EXPECT_EQ(StringHelp::parse("123"), 123);
    EXPECT_EQ(StringHelp::parse("-456"), -456);
    EXPECT_EQ(StringHelp::parse("0"), 0);
}

TEST(StringTest, TryParse) {
    int value = 0;
    EXPECT_TRUE(StringHelp::tryParse("123", value));
    EXPECT_EQ(value, 123);
    EXPECT_FALSE(StringHelp::tryParse("abc", value));
}

TEST(StringTest, ParseUnsigned) {
    EXPECT_EQ(StringHelp::parseUnsigned("123"), 123u);
    EXPECT_EQ(StringHelp::parseUnsigned("0"), 0u);
}

TEST(StringTest, TryParseUnsigned) {
    unsigned int value = 0;
    EXPECT_TRUE(StringHelp::tryParseUnsigned("123", value));
    EXPECT_EQ(value, 123u);
    EXPECT_FALSE(StringHelp::tryParseUnsigned("-1", value));
}

TEST(StringTest, Parse64) {
    EXPECT_EQ(StringHelp::parse64("123456789012345"), 123456789012345LL);
    EXPECT_EQ(StringHelp::parse64("-9876543210"), -9876543210LL);
}

TEST(StringTest, TryParse64) {
    long long value = 0;
    EXPECT_TRUE(StringHelp::tryParse64("123456789012345", value));
    EXPECT_EQ(value, 123456789012345LL);
    EXPECT_FALSE(StringHelp::tryParse64("abc", value));
}

TEST(StringTest, ParseUnsigned64) {
    EXPECT_EQ(StringHelp::parseUnsigned64("123456789012345"), 123456789012345ULL);
}

TEST(StringTest, TryParseUnsigned64) {
    unsigned long long value = 0;
    EXPECT_TRUE(StringHelp::tryParseUnsigned64("123456789012345", value));
    EXPECT_EQ(value, 123456789012345ULL);
    EXPECT_FALSE(StringHelp::tryParseUnsigned64("-1", value));
}

TEST(StringTest, ParseHex64) {
    EXPECT_EQ(StringHelp::parseHex64("1A2B3C4D5E6F7A8"), 0x1A2B3C4D5E6F7A8ULL);
}

TEST(StringTest, TryParseHex64) {
    unsigned long long value = 0;
    EXPECT_TRUE(StringHelp::tryParseHex64("1A2B3C4D5E6F7A8", value));
    EXPECT_EQ(value, 0x1A2B3C4D5E6F7A8ULL);
    EXPECT_FALSE(StringHelp::tryParseHex64("G12345", value));
}

TEST(StringTest, ParseFloat) {
    EXPECT_EQ(StringHelp::parseFloat("123.45"), 123.45);
    EXPECT_EQ(StringHelp::parseFloat("-1.23"), -1.23);
}

TEST(StringTest, TryParseFloat) {
    double value = 0.0;
    EXPECT_TRUE(StringHelp::tryParseFloat("123.45", value));
    EXPECT_EQ(value, 123.45);
    EXPECT_FALSE(StringHelp::tryParseFloat("abc", value));
}

TEST(StringTest, ParseBool) {
    EXPECT_TRUE(StringHelp::parseBool("true"));
    EXPECT_FALSE(StringHelp::parseBool("false"));
}

TEST(StringTest, TryParseBool) {
    bool value = false;
    EXPECT_TRUE(StringHelp::tryParseBool("true", value));
    EXPECT_TRUE(value);
    EXPECT_FALSE(StringHelp::tryParseBool("notabool", value));
}

TEST(StringTest, ToLower) {
    EXPECT_EQ(StringHelp::tolower("Hello"), "hello");
    EXPECT_EQ(StringHelp::tolower("WORLD"), "world");
}

TEST(StringTest, ToUpper) {
    EXPECT_EQ(StringHelp::toupper("hello"), "HELLO");
    EXPECT_EQ(StringHelp::toupper("world"), "WORLD");
}

TEST(StringTest, TrimLeft) {
    EXPECT_EQ(StringHelp::trimLeft("  hello"), "hello");
    EXPECT_EQ(StringHelp::trimLeft("  "), "");
}

TEST(StringTest, TrimRight) {
    EXPECT_EQ(StringHelp::trimRight("hello  "), "hello");
    EXPECT_EQ(StringHelp::trimRight("  "), "");
}

TEST(StringTest, Trim) {
    EXPECT_EQ(StringHelp::trim("  hello  "), "hello");
    EXPECT_EQ(StringHelp::trim("  "), "");
}

TEST(StringTest, StartsWith) {
    EXPECT_TRUE(StringHelp::startsWith("hello", "he"));
    EXPECT_FALSE(StringHelp::startsWith("hello", "world"));
}

TEST(StringTest, EndsWith) {
    EXPECT_TRUE(StringHelp::endsWith("hello", "lo"));
    EXPECT_FALSE(StringHelp::endsWith("hello", "world"));
}

TEST(StringTest, ICompare) 
{
    EXPECT_EQ(StringHelp::icompare("hello", "HELLO"), 0);
    EXPECT_GT(StringHelp::icompare("hello", "abc"), 0);
    EXPECT_LT(StringHelp::icompare("abc", "hello"), 0);
}


TEST(StringTest, ICompareN) 
{
    EXPECT_EQ(StringHelp::icomparen("hello", "HELLO", 5), 0);
    EXPECT_GT(StringHelp::icomparen("hello", "abc", 3), 0);
    EXPECT_LT(StringHelp::icomparen("abc", "hello", 3), 0);
}
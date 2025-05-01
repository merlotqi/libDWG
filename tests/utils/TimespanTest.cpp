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

#include <dwg/utils/DateTime.h>
#include <gtest/gtest.h>
#include <time.h>

using namespace dwg;

TEST(TimespanTest, defaultConstructor)
{
    // Test default constructor initializes to zero
    Timespan ts;
    EXPECT_EQ(ts.totalMicroseconds(), 0);
}

TEST(TimespanTest, constructorFromMicroseconds)
{
    // Test constructor from microseconds
    Timespan ts(1000000);// 1 second
    EXPECT_EQ(ts.totalMicroseconds(), 1000000);
}

TEST(TimespanTest, constructorFromSecondsMicroseconds)
{
    // Test constructor from seconds and microseconds
    Timespan ts(2, 500000);// 2.5 seconds
    EXPECT_EQ(ts.totalMicroseconds(), 2500000);
}

TEST(TimespanTest, constructorFromDetailed)
{
    // Test constructor from days, hours, minutes, seconds, microseconds
    Timespan ts(1, 2, 3, 4, 500000);// 1 day 2 hours 3 minutes 4.5 seconds
    std::int64_t expected = (((((1 * 24 + 2) * 60 + 3) * 60) + 4) * 1000000LL) + 500000LL;
    EXPECT_EQ(ts.totalMicroseconds(), expected);
}

TEST(TimespanTest, copyConstructor)
{
    // Test copy constructor
    Timespan ts1(1234567);
    Timespan ts2(ts1);
    EXPECT_EQ(ts2.totalMicroseconds(), 1234567);
}

TEST(TimespanTest, assignmentOperatorFromTimespan)
{
    // Test assignment from another Timespan
    Timespan ts1(7654321);
    Timespan ts2;
    ts2 = ts1;
    EXPECT_EQ(ts2.totalMicroseconds(), 7654321);
}

TEST(TimespanTest, assignmentOperatorFromMicroseconds)
{
    // Test assignment from microseconds
    Timespan ts;
    ts = 5000000;
    EXPECT_EQ(ts.totalMicroseconds(), 5000000);
}

TEST(TimespanTest, assignFromSecondsAndMicroseconds)
{
    // Test assign method from seconds and microseconds
    Timespan ts;
    ts.assign(3, 250000);// 3.25 seconds
    EXPECT_EQ(ts.totalMicroseconds(), 3250000);
}

TEST(TimespanTest, assignFromDetailed)
{
    // Test assign method from days, hours, minutes, seconds, microseconds
    Timespan ts;
    ts.assign(0, 1, 1, 1, 100000);// 1 hour 1 minute 1.1 seconds
    std::int64_t expected = (((1 * 60 + 1) * 60 + 1) * 1000000LL) + 100000LL;
    EXPECT_EQ(ts.totalMicroseconds(), expected);
}

TEST(TimespanTest, swapFunction)
{
    // Test swap method
    Timespan ts1(1000000);// 1 second
    Timespan ts2(2000000);// 2 seconds
    ts1.swap(ts2);
    EXPECT_EQ(ts1.totalMicroseconds(), 2000000);
    EXPECT_EQ(ts2.totalMicroseconds(), 1000000);
}

TEST(TimespanTest, comparisonOperators)
{
    // Test comparison operators between Timespans and between Timespan and microseconds
    Timespan ts1(1000000);
    Timespan ts2(2000000);

    EXPECT_TRUE(ts1 < ts2);
    EXPECT_TRUE(ts2 > ts1);
    EXPECT_TRUE(ts1 <= ts2);
    EXPECT_TRUE(ts2 >= ts1);
    EXPECT_FALSE(ts1 == ts2);
    EXPECT_TRUE(ts1 != ts2);

    EXPECT_TRUE(ts1 == 1000000);
    EXPECT_TRUE(ts2 > 1000000);
    EXPECT_TRUE(ts1 <= 1000000);
    EXPECT_FALSE(ts1 != 1000000);
}

TEST(TimespanTest, additionSubtractionTimespan)
{
    // Test addition and subtraction between Timespans
    Timespan ts1(1000000);
    Timespan ts2(500000);

    Timespan sum = ts1 + ts2;
    Timespan diff = ts1 - ts2;

    EXPECT_EQ(sum.totalMicroseconds(), 1500000);
    EXPECT_EQ(diff.totalMicroseconds(), 500000);

    ts1 += ts2;
    EXPECT_EQ(ts1.totalMicroseconds(), 1500000);

    ts1 -= ts2;
    EXPECT_EQ(ts1.totalMicroseconds(), 1000000);
}

TEST(TimespanTest, additionSubtractionMicroseconds)
{
    // Test addition and subtraction with microseconds
    Timespan ts(1000000);

    Timespan sum = ts + 500000;
    Timespan diff = ts - 500000;

    EXPECT_EQ(sum.totalMicroseconds(), 1500000);
    EXPECT_EQ(diff.totalMicroseconds(), 500000);

    ts += 500000;
    EXPECT_EQ(ts.totalMicroseconds(), 1500000);

    ts -= 500000;
    EXPECT_EQ(ts.totalMicroseconds(), 1000000);
}

TEST(TimespanTest, timeComponentsExtraction)
{
    // Test extraction of time components
    Timespan ts(1, 2, 3, 4, 500000);// 1 day 2 hours 3 minutes 4.5 seconds

    EXPECT_EQ(ts.days(), 1);
    EXPECT_EQ(ts.hours(), 2);
    EXPECT_EQ(ts.totalHours(), 26);// 24 + 2
    EXPECT_EQ(ts.minutes(), 3);
    EXPECT_EQ(ts.totalMinutes(), 1563);// 26*60 + 3
    EXPECT_EQ(ts.seconds(), 4);
    EXPECT_EQ(ts.totalSeconds(), 93784);// (1563*60) + 4
    EXPECT_EQ(ts.milliseconds(), 500);
    EXPECT_EQ(ts.totalMillseconds(), 93784500);
    EXPECT_EQ(ts.microseconds(), 500000);
    EXPECT_EQ(ts.totalMicroseconds(), 93784500);
}

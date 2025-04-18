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

TEST(DateTimeTest, DefaultConstructor_IsCloseToNowUTC)
{
    DateTime now = DateTime::currentUtcDateTime();
    DateTime dt;

    Timespan diff = now - dt;
    EXPECT_LT(std::abs(diff.totalSeconds()), 1);
}

TEST(DateTimeTest, AssignConstructor_CorrectFields)
{
    DateTime dt(2024, 4, 17, 15, 30, 45, 123, 456);

    EXPECT_EQ(dt.year(), 2024);
    EXPECT_EQ(dt.month(), 4);
    EXPECT_EQ(dt.day(), 17);
    EXPECT_EQ(dt.hour(), 15);
    EXPECT_EQ(dt.minute(), 30);
    EXPECT_EQ(dt.second(), 45);
    EXPECT_EQ(dt.millisecond(), 123);
    EXPECT_EQ(dt.mircosecond(), 456);
}

TEST(DateTimeTest, IsLeapYearTest)
{
    EXPECT_TRUE(DateTime::isLeapYear(2024));
    EXPECT_FALSE(DateTime::isLeapYear(2023));
    EXPECT_TRUE(DateTime::isLeapYear(2000));
    EXPECT_FALSE(DateTime::isLeapYear(1900));
}

TEST(DateTimeTest, DaysOfMonthTest)
{
    EXPECT_EQ(DateTime::daysOfMonth(2024, 2), 29);
    EXPECT_EQ(DateTime::daysOfMonth(2023, 2), 28);
    EXPECT_EQ(DateTime::daysOfMonth(2023, 1), 31);
    EXPECT_EQ(DateTime::daysOfMonth(2023, 4), 30);
}

TEST(DateTimeTest, ComparisonOperators)
{
    DateTime dt1(2024, 4, 17, 12);
    DateTime dt2(2024, 4, 17, 13);

    EXPECT_TRUE(dt1 < dt2);
    EXPECT_TRUE(dt2 > dt1);
    EXPECT_TRUE(dt1 != dt2);

    DateTime dt3 = dt1;
    EXPECT_TRUE(dt1 == dt3);
}

TEST(DateTimeTest, AddSubtractTimespan)
{
    DateTime dt(2024, 4, 17, 10, 0, 0);
    Timespan ts = Timespan::fromMinutes(90);

    DateTime dt2 = dt + ts;
    EXPECT_EQ(dt2.hour(), 11);
    EXPECT_EQ(dt2.minute(), 30);

    DateTime dt3 = dt2 - ts;
    EXPECT_EQ(dt3, dt);
}

TEST(DateTimeTest, JulianDayConversion)
{
    DateTime dt(2024, 4, 17, 0, 0, 0);
    double jd = dt.julianDay();

    DateTime fromJD(jd);
    EXPECT_EQ(fromJD.year(), 2024);
    EXPECT_EQ(fromJD.month(), 4);
    EXPECT_EQ(fromJD.day(), 17);
}

TEST(DateTimeTest, ToUtcAndLocal)
{
    DateTime now = DateTime::currentLocalDateTime();
    DateTime utc = now.toUtcDateTime();
    DateTime local = utc.toLocalDateTime();

    Timespan diff = now - local;
    EXPECT_LT(std::abs(diff.totalSeconds()), 2);
}

TEST(DateTimeTest, IsValidDate)
{
    EXPECT_TRUE(DateTime::isValid(2024, 2, 29));
    EXPECT_FALSE(DateTime::isValid(2023, 2, 29));
    EXPECT_FALSE(DateTime::isValid(2023, 13, 1));
    EXPECT_FALSE(DateTime::isValid(2023, 0, 1));
    EXPECT_FALSE(DateTime::isValid(2023, 1, 32));
}
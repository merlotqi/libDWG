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

#include "Timespan.h"
#include "Timestamp.h"


struct tm;

class DateTime
{
public:
    enum Months
    {
        JANUARY = 1,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER
    };

    enum DaysOfWeek
    {
        SUNDAY = 0,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY
    };

    DateTime();
    DateTime(const tm &tmStruct);
    DateTime(const Timestamp &timestamp);
     DateTime(int year, int month, int day, int hour = 0, int minute = 0,
             int second = 0, int millisecond = 0, int microsecond = 0);
     DateTime(double julianDay);
    DateTime(Timestamp::UtcTimeVal utcTime, Timestamp::TimeDiff diff);
    DateTime(const DateTime &dateTime);
    ~DateTime();

    DateTime &operator=(const DateTime &dateTime);
    DateTime &operator=(const Timestamp &timestamp);
    DateTime &operator=(double julianDay);
    DateTime &assign(int year, int month, int day, int hour = 0, int minute = 0,
                     int second = 0, int millisecond = 0, int microseconds = 0);

    void swap(DateTime &dateTime) noexcept;
    int year() const;
    int month() const;
    int week(int firstDayOfWeek = MONDAY) const;
    int day() const;
    int dayOfWeek() const;
    int dayOfYear() const;
    int hour() const;
    int hourAMPM() const;
    bool isAM() const;
    bool isPM() const;
    int minute() const;
    int second() const;
    int millisecond() const;
    int microsecond() const;
    double julianDay() const;
    Timestamp timestamp() const;
    Timestamp::UtcTimeVal utcTime() const;

    bool operator==(const DateTime &dateTime) const;
    bool operator!=(const DateTime &dateTime) const;
    bool operator<(const DateTime &dateTime) const;
    bool operator<=(const DateTime &dateTime) const;
    bool operator>(const DateTime &dateTime) const;
    bool operator>=(const DateTime &dateTime) const;

    DateTime operator+(const Timespan &span) const;
    DateTime operator-(const Timespan &span) const;
    Timespan operator-(const DateTime &dateTime) const;
    DateTime &operator+=(const Timespan &span);
    DateTime &operator-=(const Timespan &span);

    tm makeTM() const;
    void makeUTC(int tzd);
    void makeLocal(int tzd);
    static bool isLeapYear(int year);
    static int daysOfMonth(int year, int month);
    static bool isValid(int year, int month, int day, int hour = 0,
                        int minute = 0, int second = 0, int millisecond = 0,
                        int microsecond = 0);

protected:
    void checkValid();
    static double toJulianDay(Timestamp::UtcTimeVal utcTime);

    static double toJulianDay(int year, int month, int day, int hour = 0,
                              int minute = 0, int second = 0,
                              int millisecond = 0, int microsecond = 0);
    static Timestamp::UtcTimeVal toUtcTime(double julianDay);
    void computeGregorian(double julianDay);
    void computeDaytime();

private:
    void checkLimit(short &lower, short &higher, short limit);
    void normalize();

    Timestamp::UtcTimeVal _utcTime;
    short _year;
    short _month;
    short _day;
    short _hour;
    short _minute;
    short _second;
    short _millisecond;
    short _microsecond;
};
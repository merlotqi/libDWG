
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

#include <ctime>
#include <dwg/exports.h>
#include <string>

namespace dwg {

class LIBDWG_API Timespan
{
public:
    using time_diff = std::int64_t;

    Timespan();
    Timespan(time_diff microseconds);
    Timespan(long seconds, long microseconds);
    Timespan(int days, int hours, int minutes, int seconds, int microseconds);
    Timespan(const Timespan &rhs);
    ~Timespan() = default;
    Timespan &operator=(const Timespan &rhs);
    Timespan &operator=(time_diff microseconds);
    Timespan &assign(long seconds, long microseconds);
    Timespan &assign(int days, int hours, int minutes, int seconds, int microseconds);
    void swap(Timespan &rhs);

    bool operator==(const Timespan &rhs) const;
    bool operator!=(const Timespan &rhs) const;
    bool operator>(const Timespan &rhs) const;
    bool operator>=(const Timespan &rhs) const;
    bool operator<(const Timespan &rhs) const;
    bool operator<=(const Timespan &rhs) const;

    bool operator==(time_diff microseconds) const;
    bool operator!=(time_diff microseconds) const;
    bool operator>(time_diff microseconds) const;
    bool operator>=(time_diff microseconds) const;
    bool operator<(time_diff microseconds) const;
    bool operator<=(time_diff microseconds) const;

    Timespan operator+(const Timespan &rhs) const;
    Timespan operator-(const Timespan &rhs) const;
    Timespan &operator+=(const Timespan &rhs);
    Timespan &operator-=(const Timespan &rhs);

    Timespan operator+(time_diff microseconds) const;
    Timespan operator-(time_diff microseconds) const;
    Timespan &operator+=(time_diff microseconds);
    Timespan &operator-=(time_diff microseconds);

    int days() const;
    int hours() const;
    int totalHours() const;
    int minutes() const;
    int totalMinutes() const;
    int seconds() const;
    int totalSeconds() const;
    int milliseconds() const;
    std::int64_t totalMillseconds() const;
    int microseconds() const;
    std::int64_t totalMicroseconds() const;

private:
    time_diff _timespan;
};


class LIBDWG_API Timestamp
{
public:
    using time_value = std::int64_t;    // base at 1970-01-01 00:00:00
    using utc_time_value = std::int64_t;// base at 1582-10-15 00:00:00
    using time_diff = std::int64_t;

    Timestamp();
    Timestamp(time_value tv);
    Timestamp(const Timestamp &rhs);
    Timestamp &operator=(const Timestamp &rhs);
    Timestamp &operator=(time_value tv);
    ~Timestamp() = default;
    void swap(Timestamp &rhs);
    void update();

    bool operator==(const Timestamp &rhs) const;
    bool operator!=(const Timestamp &rhs) const;
    bool operator>(const Timestamp &rhs) const;
    bool operator>=(const Timestamp &rhs) const;
    bool operator<(const Timestamp &rhs) const;
    bool operator<=(const Timestamp &rhs) const;

    Timestamp operator+(time_diff d) const;
    Timestamp operator+(const Timespan &span) const;
    Timestamp operator-(time_diff d) const;
    Timestamp operator-(const Timespan &span) const;
    time_diff operator-(const Timestamp &rhs) const;
    Timestamp &operator+=(time_diff d);
    Timestamp &operator+=(const Timespan &span);
    Timestamp &operator-=(time_diff d);
    Timestamp &operator-=(const Timespan &span);

    std::time_t epochTime() const;
    utc_time_value utcTime() const;
    time_value epochMicroseconds() const;
    time_diff elapsed() const;
    bool isElapsed(time_diff interval) const;
    time_value raw() const;

    static Timestamp fromEpochTime(std::time_t t);
    static Timestamp fromUtcTime(utc_time_value value);

private:
    time_value _timestamp;
};

class LIBDWG_API Timezone
{
public:
    static int utcOffset();
    static int dst();
    static int dst(const Timestamp &timestamp);
    static bool isDst(const Timestamp &timestamp);
    static int tzd();
    static std::string name();
    static std::string standardName();
    static std::string dstName();
};


enum class Month
{
    January = 1,
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December,
};

enum class Week
{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
};

class LIBDWG_API DateTime
{
public:
    DateTime();
    DateTime(const tm &t);
    DateTime(const Timestamp &timestamp);
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0,
             int microseconds = 0);
    DateTime(double julianDay);
    DateTime(Timestamp::utc_time_value utc, Timestamp::time_diff diff);
    DateTime(const DateTime &rhs);
    ~DateTime();
    DateTime &operator=(const DateTime &rhs);
    DateTime &operator=(const Timestamp &timestamp);
    DateTime &operator=(double julianDay);
    DateTime &assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0,
                     int microseconds = 0);
    void swap(DateTime &rhs);

    bool operator==(const DateTime &rhs) const;
    bool operator!=(const DateTime &rhs) const;
    bool operator<(const DateTime &rhs) const;
    bool operator<=(const DateTime &rhs) const;
    bool operator>(const DateTime &rhs) const;
    bool operator>=(const DateTime &rhs) const;

    DateTime operator+(const Timespan &span) const;
    DateTime operator-(const Timespan &span) const;
    Timespan operator-(const DateTime &rhs) const;
    DateTime &operator+=(const Timespan &span);
    DateTime &operator-=(const Timespan &span);

    int year() const;
    int month() const;
    int week() const;
    int day() const;
    Week dayOfWeek() const;
    int dayOfYear() const;
    int hour() const;
    int minute() const;
    int second() const;
    int millisecond() const;
    int mircosecond() const;
    double julianDay() const;
    Timestamp timestamp() const;
    Timestamp::utc_time_value utcTime() const;

    DateTime toUtcDateTime() const;
    DateTime toLocalDateTime() const;

    static DateTime currentDateTime();
    static DateTime currentLocalDateTime();
    static DateTime currentUtcDateTime();
    static bool isLeapYear(int year);
    static int daysOfMonth(int year, int month);
    static bool isValid(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0,
                        int microsecond = 0);

    enum class DateFormat
    {
        ISO8601,    // ISO 8601 format, e.g., 2005-01-01T12:00:00+01:00
        ISO8601Frac,// ISO 8601 format with fractional seconds, e.g., 2005-01-01T12:00:00.000000+01:00
        RFC822,     // RFC 822 format (obsoleted by RFC 1123), e.g., Sat, 1 Jan 05 12:00:00 +0100
        RFC1123,    // RFC 1123 format (obsoletes RFC 822), e.g., Sat, 1 Jan 2005 12:00:00 +0100
        HTTP,       // HTTP date format (RFC 2616), e.g., Sat, 01 Jan 2005 12:00:00 +0100
        RFC850,     // RFC 850 format (obsoleted by RFC 1036), e.g., Saturday, 1-Jan-05 12:00:00 +0100
        RFC1036,    // RFC 1036 format (obsoletes RFC 850), e.g., Saturday, 1 Jan 05 12:00:00 +0100
        Asctime,    // ANSI C asctime() format, e.g., Sat Jan  1 12:00:00 2005
        Sortable,   // Simple sortable format, e.g., 2005-01-01 12:00:00
        WeekdayName,// English names of week days (Sunday, Monday, etc.)
        MonthName   // English names of months (January, February, etc.)
    };

    /**
	 * Formats the given timestamp according to the given format.
	 * The format string is used as a template to format the date and
	 * is copied character by character except for the following special characters,
	 * which are replaced by the corresponding value.
	 *
	 *  %w - abbreviated weekday (Mon, Tue, ...)
	 *  %W - full weekday (Monday, Tuesday, ...)
	 *  %b - abbreviated month (Jan, Feb, ...)
	 *  %B - full month (January, February, ...)
	 *  %d - zero-padded day of month (01 .. 31)
	 *  %e - day of month (1 .. 31)
	 *  %f - space-padded day of month ( 1 .. 31)
	 *  %m - zero-padded month (01 .. 12)
	 *  %n - month (1 .. 12)
	 *  %o - space-padded month ( 1 .. 12)
	 *  %y - year without century (70)
	 *  %Y - year with century (1970)
	 *  %H - hour (00 .. 23)
	 *  %h - hour (00 .. 12)
	 *  %a - am/pm
	 *  %A - AM/PM
	 *  %M - minute (00 .. 59)
	 *  %S - second (00 .. 59)
	 *  %s - seconds and microseconds (equivalent to %S.%F)
	 *  %i - millisecond (000 .. 999)
	 *  %c - centisecond (0 .. 9)
	 *  %F - fractional seconds/microseconds (000000 - 999999)
	 *  %z - time zone differential in ISO 8601 format (Z or +NN.NN)
	 *  %Z - time zone differential in RFC format (GMT or +NNNN)
	 *  %% - percent sign
    */
    std::string toString(const std::string &fmt) const;
    std::string toString(DateFormat fmt) const;

private:
    void checkValid();
    static double toJulianDay(Timestamp::utc_time_value utcTime);
    static double toJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0,
                              int millisecond = 0, int microsecond = 0);
    static Timestamp::utc_time_value toUtcTime(double julianDay);
    void computeGregorian(double julianDay);
    void computeDaytime();
    void checkLimit(short &lower, short &higher, short limit);
    void normalize();

private:
    Timestamp::utc_time_value _utcTime;
    short _year;
    short _month;
    short _day;
    short _hour;
    short _minute;
    short _second;
    short _millisecond;
    short _microsecond;
};

}// namespace dwg
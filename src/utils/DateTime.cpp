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

#include <algorithm>
#include <cmath>
#include <ctime>
#include <dwg/utils/DateTime.h>
#include <fmt/core.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <mutex>
#include <unistd.h>
#endif

namespace dwg {

#ifdef _WIN32
static std::string WCHARToUTF8(const WCHAR *wstr)
{
    if (!wstr)
        return "";

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    if (sizeNeeded <= 0)
        return "";

    std::string utf8Str(sizeNeeded - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &utf8Str[0], sizeNeeded, nullptr, nullptr);

    return utf8Str;
}
#endif

static constexpr auto MILLISECONDS = 1'000;
static constexpr auto SECONDS = 1'000'000;
static constexpr auto MINUTES = 60'000'000;
static constexpr auto HOURS = 3'600'000'000;
static constexpr auto DAYS = 86'400'000'000;

Timespan::Timespan() : _timespan(0) {}

Timespan::Timespan(time_diff microseconds) : _timespan(microseconds) {}

Timespan::Timespan(long seconds, long microseconds) : _timespan(time_diff(seconds) * SECONDS + microseconds) {}

Timespan::Timespan(int days, int hours, int minutes, int seconds, int microseconds)
    : _timespan(time_diff(microseconds) + time_diff(seconds) * SECONDS + time_diff(minutes) * MINUTES +
                time_diff(hours) * HOURS + time_diff(days) * DAYS)
{
}

Timespan::Timespan(const Timespan &rhs) : _timespan(rhs._timespan) {}

Timespan &Timespan::operator=(const Timespan &rhs)
{
    _timespan = rhs._timespan;
    return *this;
}

Timespan &Timespan::operator=(time_diff microseconds)
{
    _timespan = microseconds;
    return *this;
}

Timespan &Timespan::assign(long seconds, long microseconds)
{
    _timespan = time_diff(seconds) * SECONDS + time_diff(microseconds);
    return *this;
}

Timespan &Timespan::assign(int days, int hours, int minutes, int seconds, int microseconds)
{
    _timespan = time_diff(microseconds) + time_diff(seconds) * SECONDS + time_diff(minutes) * MINUTES +
                time_diff(hours) * HOURS + time_diff(days) * DAYS;
    return *this;
}

void Timespan::swap(Timespan &rhs)
{
    std::swap(_timespan, rhs._timespan);
}

bool Timespan::operator==(const Timespan &rhs) const
{
    return _timespan == rhs._timespan;
}

bool Timespan::operator!=(const Timespan &rhs) const
{
    return _timespan != rhs._timespan;
}

bool Timespan::operator>(const Timespan &rhs) const
{
    return _timespan > rhs._timespan;
}

bool Timespan::operator>=(const Timespan &rhs) const
{
    return _timespan >= rhs._timespan;
}

bool Timespan::operator<(const Timespan &rhs) const
{
    return _timespan < rhs._timespan;
}

bool Timespan::operator<=(const Timespan &rhs) const
{
    return _timespan <= rhs._timespan;
}

bool Timespan::operator==(time_diff microseconds) const
{
    return _timespan == microseconds;
}

bool Timespan::operator!=(time_diff microseconds) const
{
    return _timespan != microseconds;
}

bool Timespan::operator>(time_diff microseconds) const
{
    return _timespan > microseconds;
}

bool Timespan::operator>=(time_diff microseconds) const
{
    return _timespan >= microseconds;
}

bool Timespan::operator<(time_diff microseconds) const
{
    return _timespan < microseconds;
}

bool Timespan::operator<=(time_diff microseconds) const
{
    return _timespan <= microseconds;
}

Timespan Timespan::operator+(const Timespan &rhs) const
{
    return Timespan(_timespan + rhs._timespan);
}

Timespan Timespan::operator-(const Timespan &rhs) const
{
    return Timespan(_timespan - rhs._timespan);
}

Timespan &Timespan::operator+=(const Timespan &rhs)
{
    _timespan += rhs._timespan;
    return *this;
}

Timespan &Timespan::operator-=(const Timespan &rhs)
{
    _timespan -= rhs._timespan;
    return *this;
}

Timespan Timespan::operator+(time_diff microseconds) const
{
    return Timespan(_timespan + microseconds);
}

Timespan Timespan::operator-(time_diff microseconds) const
{
    return Timespan(_timespan - microseconds);
}

Timespan &Timespan::operator+=(time_diff microseconds)
{
    _timespan += microseconds;
    return *this;
}

Timespan &Timespan::operator-=(time_diff microseconds)
{
    _timespan -= microseconds;
    return *this;
}

int Timespan::days() const
{
    return int(_timespan / DAYS);
}

int Timespan::hours() const
{
    return int((_timespan / HOURS) % 24);
}

int Timespan::totalHours() const
{
    return int(_timespan / HOURS);
}

int Timespan::minutes() const
{
    return int((_timespan / MINUTES) % 60);
}

int Timespan::totalMinutes() const
{
    return int(_timespan / MINUTES);
}

int Timespan::seconds() const
{
    return int((_timespan / SECONDS) % 60);
}

int Timespan::totalSeconds() const
{
    return int(_timespan / SECONDS);
}

int Timespan::milliseconds() const
{
    return int((_timespan / MILLISECONDS) % 1000);
}

std::int64_t Timespan::totalMillseconds() const
{
    return int(_timespan / MILLISECONDS);
}

int Timespan::microseconds() const
{
    return _timespan % 1000;
}

std::int64_t Timespan::totalMicroseconds() const
{
    return _timespan;
}


static constexpr auto TIMESTAMP_RESOLUTION = 1000000;

Timestamp::Timestamp()
{
    update();
}

Timestamp::Timestamp(Timestamp::time_value tv)
{
    _timestamp = tv;
}

Timestamp::Timestamp(const Timestamp &rhs)
{
    _timestamp = rhs._timestamp;
}

Timestamp &Timestamp::operator=(const Timestamp &rhs)
{
    _timestamp = rhs._timestamp;
    return *this;
}

Timestamp &Timestamp::operator=(Timestamp::time_value tv)
{
    _timestamp = tv;
    return *this;
}

void Timestamp::swap(Timestamp &rhs)
{
    std::swap(_timestamp, rhs._timestamp);
}

void Timestamp::update()
{
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULARGE_INTEGER epoch;
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.LowPart = ft.dwLowDateTime;
    ts.HighPart = ft.dwHighDateTime;
    ts.QuadPart -= epoch.QuadPart;
    _timestamp = ts.QuadPart / 10;
#else
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts))
        throw std::invalid_argument("cannot get time of day");
    _timestamp = time_value(ts.tv_sec) * TIMESTAMP_RESOLUTION + ts.tv_nsec / 1000;
#endif
}

bool Timestamp::operator==(const Timestamp &rhs) const
{
    return _timestamp == rhs._timestamp;
}

bool Timestamp::operator!=(const Timestamp &rhs) const
{
    return _timestamp != rhs._timestamp;
}

bool Timestamp::operator>(const Timestamp &rhs) const
{
    return _timestamp > rhs._timestamp;
}

bool Timestamp::operator>=(const Timestamp &rhs) const
{
    return _timestamp >= rhs._timestamp;
}

bool Timestamp::operator<(const Timestamp &rhs) const
{
    return _timestamp < rhs._timestamp;
}

bool Timestamp::operator<=(const Timestamp &rhs) const
{
    return _timestamp <= rhs._timestamp;
}

Timestamp Timestamp::operator+(Timestamp::time_diff d) const
{
    return Timestamp(_timestamp + d);
}

Timestamp Timestamp::operator+(const Timespan &span) const
{
    return *this + span.totalMicroseconds();
}

Timestamp Timestamp::operator-(Timestamp::time_diff d) const
{
    return Timestamp(_timestamp - d);
}

Timestamp Timestamp::operator-(const Timespan &span) const
{
    return *this - span.totalMicroseconds();
}

Timestamp::time_diff Timestamp::operator-(const Timestamp &rhs) const
{
    return _timestamp - rhs._timestamp;
}

Timestamp &Timestamp::operator+=(Timestamp::time_diff d)
{
    _timestamp += d;
    return *this;
}

Timestamp &Timestamp::operator+=(const Timespan &span)
{
    return *this += span.totalMicroseconds();
}

Timestamp &Timestamp::operator-=(Timestamp::time_diff d)
{
    _timestamp -= d;
    return *this;
}

Timestamp &Timestamp::operator-=(const Timespan &span)
{
    return *this -= span.totalMicroseconds();
}

std::time_t Timestamp::epochTime() const
{
    return std::time_t(_timestamp / TIMESTAMP_RESOLUTION);
}

Timestamp::utc_time_value Timestamp::utcTime() const
{
    return _timestamp * 10 + (time_diff(0x01b21dd2) << 32) + 0x13814000;
}

Timestamp::time_value Timestamp::epochMicroseconds() const
{
    return _timestamp;
}

Timestamp::time_diff Timestamp::elapsed() const
{
    Timestamp now;
    return now - *this;
}

bool Timestamp::isElapsed(Timestamp::time_diff interval) const
{
    Timestamp now;
    Timestamp::time_diff diff = now - *this;
    return diff >= interval;
}

Timestamp::time_value Timestamp::raw() const
{
    return _timestamp;
}

Timestamp Timestamp::fromEpochTime(std::time_t t)
{
    return Timestamp(Timestamp::time_value(t) * TIMESTAMP_RESOLUTION);
}

Timestamp Timestamp::fromUtcTime(Timestamp::utc_time_value value)
{
    value -= (time_diff(0x01b21dd2) << 32) + 0x13814000;
    value /= 10;
    return Timestamp(value);
}

/* -------------------------------- Timezone -------------------------------- */

#ifndef _WIN32
class TZInfo
{
    std::mutex _mtx;

public:
    TZInfo()
    {
        tzset();
    }

    int timeZone()
    {
        std::lock_guard<std::mutex> lock(_mtx);
#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || \
        POCO_OS == POCO_OS_ANDROID// no timezone global var
        std::time_t now = std::time(NULL);
        struct std::tm t;
        gmtime_r(&now, &t);
        std::time_t utc = std::mktime(&t);
        return now - utc;
#elif defined(__CYGWIN__)
        tzset();
        return -_timezone;
#else
        tzset();
        return -timezone;
#endif
    }

    const char *name(bool dst)
    {
        std::lock_guard<std::mutex> lock(_mtx);

        tzset();
        return tzname[dst ? 1 : 0];
    }
};

static TZInfo tzinfo;

#endif

int Timezone::utcOffset()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    return -tzInfo.Bias * 60;
#else
    return tzinfo.timeZone();
#endif
}

int Timezone::dst()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    return dstFlag == TIME_ZONE_ID_DAYLIGHT ? -tzInfo.DaylightBias * 60 : 0;
#else
    return dst(Timestamp());
#endif
}

int Timezone::dst(const Timestamp &timestamp)
{
#ifdef _WIN32
    if (isDst(timestamp))
    {
        TIME_ZONE_INFORMATION tzInfo;
        GetTimeZoneInformation(&tzInfo);
        return -tzInfo.DaylightBias * 60;
    }
    else
    {
        return 0;
    }
#else
    std::time_t time = timestamp.epochTime();
    struct std::tm local;
    if (!localtime_r(&time, &local))
        throw std::invalid_argument("cannot get local time DST offset");
    if (local.tm_isdst > 0)
    {
#if defined(__CYGWIN__)
        return local.__TM_GMTOFF - utcOffset();
#elif defined(__APPLE__) || defined(__FreeBSD__) || defined(__OpenBSD__) || POCO_OS == POCO_OS_LINUX || \
        POCO_OS == POCO_OS_ANDROID
        return local.tm_gmtoff - utcOffset();
#else
        return 3600;
#endif
    }
    else
        return 0;
#endif
}

bool Timezone::isDst(const Timestamp &timestamp)
{
#ifdef _WIN32
    std::time_t time = timestamp.epochTime();
    struct std::tm local;
    if (localtime_s(&local, &time))
        throw std::invalid_argument("cannot get local time DST flag");
    return local.tm_isdst > 0;
#else
    std::time_t time = timestamp.epochTime();
    struct std::tm *tms = std::localtime(&time);
    if (!tms)
        throw std::invalid_argument("cannot get local time DST flag");
    return tms->tm_isdst > 0;
#endif
}

int Timezone::tzd()
{
    return utcOffset() + dst();
}

std::string Timezone::name()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR *ptr = dstFlag == TIME_ZONE_ID_DAYLIGHT ? tzInfo.DaylightName : tzInfo.StandardName;
    return WCHARToUTF8(ptr);
#else
    return std::string(tzinfo.name(dst() != 0));
#endif
}

std::string Timezone::standardName()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR *ptr = tzInfo.StandardName;
    return WCHARToUTF8(ptr);
#else
    return std::string(tzinfo.name(false));
#endif
}

std::string Timezone::dstName()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
    WCHAR *ptr = tzInfo.DaylightName;
    return WCHARToUTF8(ptr);
#else
    return std::string(tzinfo.name(true));
#endif
}

/* -------------------------------- DateTime -------------------------------- */

DateTime::DateTime()
{
    Timestamp now;
    _utcTime = now.utcTime();
    computeGregorian(julianDay());
    computeDaytime();
    checkValid();
}

DateTime::DateTime(const tm &t)
    : _year(t.tm_year + 1900), _month(t.tm_mon + 1), _day(t.tm_mday), _hour(t.tm_hour), _minute(t.tm_min),
      _second(t.tm_sec), _millisecond(0), _microsecond(0)
{
    checkValid();
    _utcTime =
            toUtcTime(toJulianDay(_year, _month, _day)) + 10 * (_hour * HOURS + _minute * MINUTES + _second * SECONDS);
}

DateTime::DateTime(const Timestamp &timestamp) : _utcTime(timestamp.utcTime())
{
    computeGregorian(julianDay());
    computeDaytime();
    checkValid();
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
    : _year(year), _month(month), _day(day), _hour(hour), _minute(minute), _second(second), _millisecond(millisecond),
      _microsecond(microsecond)
{
    checkValid();
    _utcTime = toUtcTime(toJulianDay(year, month, day)) +
               10 * (hour * HOURS + minute * MINUTES + second * SECONDS + millisecond * MILLISECONDS + microsecond);
}

DateTime::DateTime(double julianDay) : _utcTime(toUtcTime(julianDay))
{
    computeGregorian(julianDay);
    checkValid();
}

DateTime::DateTime(Timestamp::utc_time_value utc, Timestamp::time_diff diff) : _utcTime(utc + diff * 10)
{
    computeGregorian(julianDay());
    computeDaytime();
    checkValid();
}


DateTime::DateTime(const DateTime &rhs)
    : _utcTime(rhs._utcTime), _year(rhs._year), _month(rhs._month), _day(rhs._day), _hour(rhs._hour),
      _minute(rhs._minute), _second(rhs._second), _millisecond(rhs._millisecond), _microsecond(rhs._microsecond)
{
}

DateTime::~DateTime() {}

DateTime &DateTime::operator=(const DateTime &rhs)
{
    if (&rhs != this)
    {
        _utcTime = rhs._utcTime;
        _year = rhs._year;
        _month = rhs._month;
        _day = rhs._day;
        _hour = rhs._hour;
        _minute = rhs._minute;
        _second = rhs._second;
        _millisecond = rhs._millisecond;
        _microsecond = rhs._microsecond;
    }
    return *this;
}

DateTime &DateTime::operator=(const Timestamp &timestamp)
{
    _utcTime = timestamp.utcTime();
    computeGregorian(julianDay());
    computeDaytime();
    checkValid();
    return *this;
}

DateTime &DateTime::operator=(double julianDay)
{
    _utcTime = toUtcTime(julianDay);
    computeGregorian(julianDay);
    checkValid();
    return *this;
}

DateTime &DateTime::assign(int year, int month, int day, int hour, int minute, int second, int millisecond,
                           int microsecond)
{
    _utcTime = toUtcTime(toJulianDay(year, month, day)) +
               10 * (hour * HOURS + minute * MINUTES + second * SECONDS + millisecond * MILLISECONDS + microsecond);
    _year = year;
    _month = month;
    _day = day;
    _hour = hour;
    _minute = minute;
    _second = second;
    _millisecond = millisecond;
    _microsecond = microsecond;
    checkValid();

    return *this;
}

void DateTime::swap(DateTime &rhs)
{
    std::swap(_utcTime, rhs._utcTime);
    std::swap(_year, rhs._year);
    std::swap(_month, rhs._month);
    std::swap(_day, rhs._day);
    std::swap(_hour, rhs._hour);
    std::swap(_minute, rhs._minute);
    std::swap(_second, rhs._second);
    std::swap(_millisecond, rhs._millisecond);
    std::swap(_microsecond, rhs._microsecond);
}

bool DateTime::operator==(const DateTime &rhs) const
{
    return _utcTime == rhs._utcTime;
}

bool DateTime::operator!=(const DateTime &rhs) const
{
    return _utcTime != rhs._utcTime;
}

bool DateTime::operator<(const DateTime &rhs) const
{
    return _utcTime < rhs._utcTime;
}

bool DateTime::operator<=(const DateTime &rhs) const
{
    return _utcTime <= rhs._utcTime;
}

bool DateTime::operator>(const DateTime &rhs) const
{
    return _utcTime > rhs._utcTime;
}

bool DateTime::operator>=(const DateTime &rhs) const
{
    return _utcTime >= rhs._utcTime;
}

DateTime DateTime::operator+(const Timespan &span) const
{
    return DateTime(_utcTime, span.totalMicroseconds());
}

DateTime DateTime::operator-(const Timespan &span) const
{
    return DateTime(_utcTime, -span.totalMicroseconds());
}

Timespan DateTime::operator-(const DateTime &rhs) const
{
    return Timespan((_utcTime - rhs._utcTime) / 10);
}

DateTime &DateTime::operator+=(const Timespan &span)
{
    _utcTime += span.totalMicroseconds() * 10;
    computeGregorian(julianDay());
    computeDaytime();
    checkValid();
    return *this;
}

DateTime &DateTime::operator-=(const Timespan &span)
{
    _utcTime -= span.totalMicroseconds() * 10;
    computeGregorian(julianDay());
    computeDaytime();
    checkValid();
    return *this;
}

Week DateTime::dayOfWeek() const
{
    return Week(int((std::floor(julianDay() + 1.5))) % 7);
}

int DateTime::dayOfYear() const
{
    int doy = 0;
    for (int month = 1; month < _month; ++month) doy += daysOfMonth(_year, month);
    doy += _day;
    return doy;
}

int DateTime::daysOfMonth(int year, int month)
{
    static int daysOfMonthTable[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (month == 2 && isLeapYear(year))
        return 29;
    else if (month < 1 || month > 12)
        return 0;
    return daysOfMonthTable[month];
}

bool DateTime::isLeapYear(int year)
{
    return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
}

int DateTime::year() const
{
    return _year;
}

int DateTime::month() const
{
    return _month;
}

int DateTime::week() const
{
    /// find the first firstDayOfWeek.
    int baseDay = 1;
    while (DateTime(_year, 1, baseDay).dayOfWeek() != Week::Monday) ++baseDay;

    int doy = dayOfYear();
    int offs = baseDay <= 4 ? 0 : 1;
    if (doy < baseDay)
        return offs;
    else
        return (doy - baseDay) / 7 + 1 + offs;
}

int DateTime::day() const
{
    return _day;
}

int DateTime::hour() const
{
    return _hour;
}

int DateTime::minute() const
{
    return _minute;
}

int DateTime::second() const
{
    return _second;
}

int DateTime::millisecond() const
{
    return _millisecond;
}

int DateTime::mircosecond() const
{
    return _microsecond;
}

double DateTime::julianDay() const
{
    return toJulianDay(_utcTime);
}

Timestamp DateTime::timestamp() const
{
    return Timestamp::fromUtcTime(_utcTime);
}

Timestamp::utc_time_value DateTime::utcTime() const
{
    return _utcTime;
}

DateTime DateTime::toUtcDateTime() const
{
    return DateTime(_utcTime);
}

DateTime DateTime::toLocalDateTime() const
{
    DateTime dateTime = *this;
    std::time_t epochTime = this->timestamp().epochTime();
#if defined(_WIN32)
    std::tm brokenBuf;
    std::tm *broken = &brokenBuf;
    errno_t err = localtime_s(broken, &epochTime);
    if (err)
        broken = nullptr;

    if (!broken)
        throw std::runtime_error("cannot get local time");
    int tzd = Timezone::utcOffset() + Timezone::dst(dateTime.timestamp());
#else
    std::tm broken;
    if (!localtime_r(&epochTime, &broken))
        throw std::runtime_error("cannot get local time");

    int tzd = Timezone::utcOffset() + Timezone::dst(dateTime.timestamp());
#endif
    dateTime += Timespan(((Timestamp::time_diff) tzd) * SECONDS);
    return dateTime;
}

DateTime DateTime::currentDateTime()
{
    return currentUtcDateTime();
}

DateTime DateTime::currentLocalDateTime()
{
    DateTime now;
    return now.toLocalDateTime();
}

DateTime DateTime::currentUtcDateTime()
{
    DateTime now;
    return now;
}

std::string DateTime::toString(const std::string &fmt) const
{
    return std::string();
}

std::string DateTime::toString(DateFormat fmt) const
{
    return std::string();
}

std::string DateTime::ToString(const DateTime &dt, const std::string &fmt)
{
    return std::string();
}

std::string DateTime::ToString(const DateTime &dt, DateFormat fmt)
{
    return std::string();
}

DateTime DateTime::FromString(const std::string &fmt, const std::string &str, int &timeZoneDifferential)
{
    return DateTime();
}

DateTime DateTime::FromString(DateFormat fmt, const std::string &str, int &timeZoneDifferential)
{
    return DateTime();
}

bool DateTime::FromString(const std::string &fmt, const std::string &str, DateTime &dt, int &timeZoneDifferential)
{
    return false;
}

bool DateTime::FromString(DateFormat fmt, const std::string &str, DateTime &dt, int &timeZoneDifferential)
{
    return false;
}

void DateTime::checkValid()
{
    if (!isValid(_year, _month, _day, _hour, _minute, _second, _millisecond, _microsecond))
        throw std::invalid_argument(fmt::format("Date time is %hd-%hd-%hdT%hd:%hd:%hd.%hd.%hd\n"
                                                "Valid values:\n"
                                                "-4713 <= year <= 9999\n"
                                                "1 <= month <= 12\n"
                                                "1 <= day <=  %d\n"
                                                "0 <= hour <= 23\n"
                                                "0 <= minute <= 59\n"
                                                "0 <= second <= 60\n"
                                                "0 <= millisecond <= 999\n"
                                                "0 <= microsecond <= 999",
                                                _year, _month, _day, _hour, _minute, _second, _millisecond,
                                                _microsecond, daysOfMonth(_year, _month)));
}

bool DateTime::isValid(int year, int month, int day, int hour, int minute, int second, int millisecond, int microsecond)
{
    return (year >= -4713 && year <= 9999) && (month >= 1 && month <= 12) &&
           (day >= 1 && day <= daysOfMonth(year, month)) && (hour >= 0 && hour <= 23) &&
           (minute >= 0 && minute <= 59) && (second >= 0 && second <= 60) && (millisecond >= 0 && millisecond <= 999) &&
           (microsecond >= 0 && microsecond <= 999);
}


double DateTime::toJulianDay(Timestamp::utc_time_value utcTime)
{
    double utcDays = double(utcTime) / 864000000000.0;
    return utcDays + 2299160.5;// first day of Gregorian reform (Oct 15 1582)
}

double DateTime::toJulianDay(int year, int month, int day, int hour, int minute, int second, int millisecond,
                             int microsecond)
{
    // lookup table for (153*month - 457)/5 - note that 3 <= month <= 14.
    static int lookup[] = {-91, -60, -30, 0, 31, 61, 92, 122, 153, 184, 214, 245, 275, 306, 337};

    // day to double
    double dday =
            double(day) +
            ((double((hour * 60 + minute) * 60 + second) * 1000 + millisecond) * 1000 + microsecond) / 86400000000.0;
    if (month < 3)
    {
        month += 12;
        --year;
    }
    double dyear = double(year);
    return dday + lookup[month] + 365 * year + std::floor(dyear / 4) - std::floor(dyear / 100) +
           std::floor(dyear / 400) + 1721118.5;
}

Timestamp::utc_time_value DateTime::toUtcTime(double julianDay)
{
    return Timestamp::utc_time_value((julianDay - 2299160.5) * 864000000000.0);
}

void DateTime::computeGregorian(double julianDay)
{
    double z = std::floor(julianDay - 1721118.5);
    double r = julianDay - 1721118.5 - z;
    double g = z - 0.25;
    double a = std::floor(g / 36524.25);
    double b = a - std::floor(a / 4);
    _year = short(std::floor((b + g) / 365.25));
    double c = b + z - std::floor(365.25 * _year);
    _month = short(std::floor((5 * c + 456) / 153));
    double dday = c - std::floor((153.0 * _month - 457) / 5) + r;
    _day = short(dday);
    if (_month > 12)
    {
        ++_year;
        _month -= 12;
    }
    r *= 24;
    _hour = short(std::floor(r));
    r -= std::floor(r);
    r *= 60;
    _minute = short(std::floor(r));
    r -= std::floor(r);
    r *= 60;
    _second = short(std::floor(r));
    r -= std::floor(r);
    r *= 1000;
    _millisecond = short(std::floor(r));
    r -= std::floor(r);
    r *= 1000;
    _microsecond = short(r + 0.5);

    normalize();
}

void DateTime::computeDaytime()
{
    Timestamp::utc_time_value ut(_utcTime);
    if (ut < 0)
    {
        // GH3723: UtcTimeVal is negative for pre-gregorian dates
        // move it 1600 years to the future
        // keeping hour, minute, second,... for corrections
        ut += 86400LL * 1000 * 1000 * 10 * 1600 * 365;
    }
    Timespan span(ut / 10);
    int hour = span.hours();
    // Due to double rounding issues, the previous call to computeGregorian()
    // may have crossed into the next or previous day. We need to correct that.
    if (hour == 23 && _hour == 0)
    {
        _day--;
        if (_day == 0)
        {
            _month--;
            if (_month == 0)
            {
                _month = 12;
                _year--;
            }
            _day = daysOfMonth(_year, _month);
        }
    }
    else if (hour == 0 && _hour == 23)
    {
        _day++;
        if (_day > daysOfMonth(_year, _month))
        {
            _month++;
            if (_month > 12)
            {
                _month = 1;
                _year++;
            }
            _day = 1;
        }
    }
    _hour = hour;
    _minute = span.minutes();
    _second = span.seconds();
    _millisecond = span.milliseconds();
    _microsecond = span.microseconds();
}

void DateTime::checkLimit(short &lower, short &higher, short limit)
{
    if (lower >= limit)
    {
        higher += short(lower / limit);
        lower = short(lower % limit);
    }
}

void DateTime::normalize()
{
    checkLimit(_microsecond, _millisecond, 1000);
    checkLimit(_millisecond, _second, 1000);
    checkLimit(_second, _minute, 60);
    checkLimit(_minute, _hour, 60);
    checkLimit(_hour, _day, 24);

    if (_day > daysOfMonth(_year, _month))
    {
        _day -= daysOfMonth(_year, _month);
        if (++_month > 12)
        {
            ++_year;
            _month -= 12;
        }
    }
}

}// namespace dwg
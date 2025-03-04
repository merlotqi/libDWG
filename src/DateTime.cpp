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

#include <dwg/DateTime.h>
#include <fmt/core.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace dwg {

/* -------------------------------- TimeSpan -------------------------------- */

TimeSpan::TimeSpan() : _timeSpan(0) {}

TimeSpan::TimeSpan(const TimeSpan &rhs) : _timeSpan(rhs._timeSpan) {}

TimeSpan::TimeSpan(long long span) : _timeSpan(span) {}

TimeSpan::TimeSpan(int day, int hour, int min, int sec)
{
    _timeSpan = (day * 86400LL) + (hour * 3600LL) + (min * 60LL) + sec;
}

int TimeSpan::days() const { return static_cast<int>(_timeSpan / 86400LL); }

int TimeSpan::totalHours() const { return static_cast<int>(_timeSpan / 3600LL); }

int TimeSpan::hours() const { return static_cast<int>((_timeSpan % 86400LL) / 3600LL); }

int TimeSpan::totalMinutes() const { return static_cast<int>(_timeSpan / 60LL); }

int TimeSpan::minutes() const { return static_cast<int>((_timeSpan % 3600LL) / 60LL); }

int TimeSpan::totalSeconds() const { return static_cast<int>(_timeSpan); }

int TimeSpan::seconds() const { return static_cast<int>(_timeSpan % 60LL); }

TimeSpan::operator long long() const { return _timeSpan; }

TimeSpan &TimeSpan::operator=(const TimeSpan &rhs)
{
    if (this != &rhs) { _timeSpan = rhs._timeSpan; }
    return *this;
}

TimeSpan &TimeSpan::operator=(const long long span)
{
    _timeSpan = span;
    return *this;
}

bool TimeSpan::operator==(const TimeSpan &rhs) const { return _timeSpan == rhs._timeSpan; }

bool TimeSpan::operator!=(const TimeSpan &rhs) const { return _timeSpan != rhs._timeSpan; }

bool TimeSpan::operator>(const TimeSpan &rhs) const { return _timeSpan > rhs._timeSpan; }

bool TimeSpan::operator<(const TimeSpan &rhs) const { return _timeSpan < rhs._timeSpan; }

bool TimeSpan::operator<=(const TimeSpan &rhs) const { return _timeSpan <= rhs._timeSpan; }

bool TimeSpan::operator>=(const TimeSpan &rhs) const { return _timeSpan >= rhs._timeSpan; }

TimeSpan TimeSpan::operator+(const TimeSpan &rhs) const { return TimeSpan(_timeSpan + rhs._timeSpan); }

TimeSpan TimeSpan::operator-(const TimeSpan &rhs) const { return TimeSpan(_timeSpan - rhs._timeSpan); }

TimeSpan &TimeSpan::operator+=(const TimeSpan &rhs)
{
    _timeSpan += rhs._timeSpan;
    return *this;
}

TimeSpan &TimeSpan::operator-=(const TimeSpan &rhs)
{
    _timeSpan -= rhs._timeSpan;
    return *this;
}

/* -------------------------------- DateTime -------------------------------- */

DateTime::DateTime() { _time = static_cast<long long>(time(nullptr)); }

DateTime::DateTime(const DateTime &rhs) : _time(rhs._time) {}

DateTime::DateTime(long long tm, bool bUTC)
{
    _time = tm;
    if (!bUTC) { _time -= timeZone(); }
}

DateTime::DateTime(int year, int mon, int day, int hour, int min, int sec)
{
    struct tm tm_time = {};
    tm_time.tm_year = year - 1900;
    tm_time.tm_mon = mon - 1;
    tm_time.tm_mday = day;
    tm_time.tm_hour = hour;
    tm_time.tm_min = min;
    tm_time.tm_sec = sec;

    _time = static_cast<long long>(mktime(&tm_time));
}

long long DateTime::timeZone()
{
#ifdef _WIN32
    TIME_ZONE_INFORMATION tzInfo;
    GetTimeZoneInformation(&tzInfo);
    long long offset = static_cast<long long>(tzInfo.Bias) * 60;
    if (tzInfo.DaylightDate.wYear != 0) { offset -= static_cast<long long>(tzInfo.DaylightBias) * 60; }
    return offset;
#else
    time_t t = time(nullptr);
    struct tm tm_time = *localtime(&t);
    return tm_time.tm_gmtoff;
#endif
}

DateTime DateTime::now() { return DateTime(); }

DateTime DateTime::toUTC() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    tm_time.tm_sec -= timeZone();
    return DateTime(mktime(&tm_time), true);
}

DateTime DateTime::toLocal() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *gmtime(&time_copy);
    tm_time.tm_sec += timeZone();
    return DateTime(mktime(&tm_time), false);
}

void DateTime::makeDateTime(int year, int mon, int day, int hour, int min, int sec)
{
    struct tm tm_time = {};
    tm_time.tm_year = year - 1900;
    tm_time.tm_mon = mon - 1;
    tm_time.tm_mday = day;
    tm_time.tm_hour = hour;
    tm_time.tm_min = min;
    tm_time.tm_sec = sec;
    _time = static_cast<long long>(mktime(&tm_time));
}

int DateTime::year() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    return tm_time.tm_year + 1900;
}

int DateTime::month() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    return tm_time.tm_mon + 1;
}

int DateTime::day() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    return tm_time.tm_mday;
}

int DateTime::hour() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    return tm_time.tm_hour;
}

int DateTime::minute() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    return tm_time.tm_min;
}

int DateTime::second() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    return tm_time.tm_sec;
}

WeekDay DateTime::dayOfWeek() const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);

    // tm_wday: 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    switch (tm_time.tm_wday)
    {
        case 0:
            return WeekDay::eSunday;
        case 1:
            return WeekDay::eMonday;
        case 2:
            return WeekDay::eTuesday;
        case 3:
            return WeekDay::eWednesday;
        case 4:
            return WeekDay::eThursday;
        case 5:
            return WeekDay::eFriday;
        case 6:
            return WeekDay::eSaturday;
        default:
            return WeekDay::eSunday;// default case should not be reached
    }
}

DateTime::operator time_t() const { return static_cast<time_t>(_time); }

DateTime &DateTime::operator=(const long long tim)
{
    _time = tim;
    return *this;
}

DateTime &DateTime::operator=(const DateTime &rhs)
{
    if (this != &rhs) { _time = rhs._time; }
    return *this;
}

bool DateTime::operator==(const DateTime &rhs) const { return _time == rhs._time; }

bool DateTime::operator!=(const DateTime &rhs) const { return _time != rhs._time; }

bool DateTime::operator>(const DateTime &rhs) const { return _time > rhs._time; }

bool DateTime::operator<(const DateTime &rhs) const { return _time < rhs._time; }

bool DateTime::operator<=(const DateTime &rhs) const { return _time <= rhs._time; }

bool DateTime::operator>=(const DateTime &rhs) const { return _time >= rhs._time; }

DateTime DateTime::operator+(const TimeSpan &rhs) const { return DateTime(_time + rhs); }

DateTime DateTime::operator-(const TimeSpan &rhs) const { return DateTime(_time - rhs); }

TimeSpan DateTime::operator-(const DateTime &rhs) const { return TimeSpan(_time - rhs._time); }

DateTime &DateTime::operator+=(const TimeSpan &rhs)
{
    _time += rhs;
    return *this;
}

DateTime &DateTime::operator-=(const TimeSpan &rhs)
{
    _time -= rhs;
    return *this;
}

std::string DateTime::toLongDateString() const { return fmt::format("{:04}-{:02}-{:02}", year(), month(), day()); }

std::string DateTime::toLongTimeString() const
{
    return fmt::format("{:04}-{:02}-{:02} {:02}:{:02}:{:02}", year(), month(), day(), hour(), minute(), second());
}

std::string DateTime::toShortDateString() const { return fmt::format("{:04}/{:02}/{:02}", year(), month(), day()); }

std::string DateTime::toShortTimeString() const
{
    return fmt::format("{:04}/{:02}/{:02} {:02}:{:02}", year(), month(), day(), hour(), minute());
}

std::string DateTime::toString() const { return toLongTimeString(); }

std::string DateTime::toString(const char *format) const
{
    time_t time_copy = static_cast<time_t>(_time);
    struct tm tm_time = *localtime(&time_copy);
    char buffer[100];
    strftime(buffer, sizeof(buffer), format, &tm_time);
    return std::string(buffer);
}

}// namespace dwg
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

#include "Timestamp.h"
#include "Timespan.h"
#include <algorithm>
#include <limits.h>
#if defined(__linux__)
#include <time.h>
#include <unistd.h>
#else
#include <Windows.h>
#endif

const Timestamp::TimeVal Timestamp::TIMEVAL_MIN = LLONG_MIN;
const Timestamp::TimeVal Timestamp::TIMEVAL_MAX = LLONG_MAX;

Timestamp::Timestamp() { update(); }

Timestamp::Timestamp(TimeVal tv) { _ts = tv; }

Timestamp::Timestamp(const Timestamp &other) { _ts = other._ts; }

Timestamp::~Timestamp() {}

Timestamp &Timestamp::operator=(const Timestamp &other)
{
    _ts = other._ts;
    return *this;
}

Timestamp &Timestamp::operator=(TimeVal tv)
{
    _ts = tv;
    return *this;
}

bool Timestamp::operator==(const Timestamp &ts) const { return _ts == ts._ts; }

bool Timestamp::operator!=(const Timestamp &ts) const { return _ts != ts._ts; }

bool Timestamp::operator>(const Timestamp &ts) const { return _ts > ts._ts; }

bool Timestamp::operator>=(const Timestamp &ts) const { return _ts >= ts._ts; }

bool Timestamp::operator<(const Timestamp &ts) const { return _ts < ts._ts; }

bool Timestamp::operator<=(const Timestamp &ts) const { return _ts <= ts._ts; }

Timestamp Timestamp::operator+(Timestamp::TimeDiff d) const
{
    return Timestamp(_ts + d);
}

Timestamp Timestamp::operator-(Timestamp::TimeDiff d) const
{
    return Timestamp(_ts - d);
}

Timestamp::TimeDiff Timestamp::operator-(const Timestamp &ts) const
{
    return _ts - ts._ts;
}

Timestamp &Timestamp::operator+=(Timestamp::TimeDiff d)
{
    _ts += d;
    return *this;
}

Timestamp &Timestamp::operator-=(Timestamp::TimeDiff d)
{
    _ts -= d;
    return *this;
}

std::time_t Timestamp::epochTime() const
{
    return std::time_t(_ts / resolution());
}

Timestamp::UtcTimeVal Timestamp::utcTime() const
{
    return _ts * 10 + (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
}

Timestamp::TimeVal Timestamp::epochMicroseconds() const { return _ts; }

Timestamp::TimeDiff Timestamp::elapsed() const
{
    Timestamp now;
    return now - *this;
}

bool Timestamp::isElapsed(Timestamp::TimeDiff interval) const
{
    Timestamp now;
    Timestamp::TimeDiff diff = now - *this;
    return diff >= interval;
}

constexpr Timestamp::TimeDiff Timestamp::resolution() { return 1000000; }

void swap(Timestamp &s1, Timestamp &s2) noexcept { s1.swap(s2); }

Timestamp::TimeVal Timestamp::raw() const { return _ts; }

void Timestamp::swap(Timestamp &timestamp) noexcept
{
    std::swap(_ts, timestamp._ts);
}

Timestamp Timestamp::fromEpochTime(std::time_t t)
{
    return Timestamp(TimeVal(t) * resolution());
}

Timestamp Timestamp::fromUtcTime(UtcTimeVal val)
{
    val -= (TimeDiff(0x01b21dd2) << 32) + 0x13814000;
    val /= 10;
    return Timestamp(val);
}

void Timestamp::update()
{
#if defined(_WIN32)

    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);

    ULARGE_INTEGER
    epoch;// UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.LowPart = ft.dwLowDateTime;
    ts.HighPart = ft.dwHighDateTime;
    ts.QuadPart -= epoch.QuadPart;
    _ts = ts.QuadPart / 10;

#else
    struct timeval tv;
    if (gettimeofday(&tv, nullptr))
        throw SystemException("cannot get time of day");
    _ts = TimeVal(tv.tv_sec) * resolution() + tv.tv_usec;

#endif
}

Timestamp Timestamp::operator+(const Timespan &span) const
{
    return *this + span.totalMicroseconds();
}

Timestamp Timestamp::operator-(const Timespan &span) const
{
    return *this - span.totalMicroseconds();
}

Timestamp &Timestamp::operator+=(const Timespan &span)
{
    return *this += span.totalMicroseconds();
}

Timestamp &Timestamp::operator-=(const Timespan &span)
{
    return *this -= span.totalMicroseconds();
}

#if defined(_WIN32)

Timestamp Timestamp::fromFileTimeNP(unsigned int fileTimeLow,
                                    unsigned int fileTimeHigh)
{
    ULARGE_INTEGER
    epoch;// UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.LowPart = fileTimeLow;
    ts.HighPart = fileTimeHigh;
    ts.QuadPart -= epoch.QuadPart;

    return Timestamp(ts.QuadPart / 10);
}


void Timestamp::toFileTimeNP(unsigned int &fileTimeLow,
                             unsigned int &fileTimeHigh) const
{
    ULARGE_INTEGER
    epoch;// UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
    epoch.LowPart = 0xD53E8000;
    epoch.HighPart = 0x019DB1DE;

    ULARGE_INTEGER ts;
    ts.QuadPart = _ts * 10;
    ts.QuadPart += epoch.QuadPart;
    fileTimeLow = ts.LowPart;
    fileTimeHigh = ts.HighPart;
}

#endif
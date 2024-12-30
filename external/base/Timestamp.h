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

class Timespan;
class Timestamp
{
public:
    using TimeVal = long long;
    using UtcTimeVal = long long;
    using TimeDiff = long long;

    static const TimeVal TIMEVAL_MIN;
    static const TimeVal TIMEVAL_MAX;

    Timestamp();
    Timestamp(TimeVal tv);
    Timestamp(const Timestamp &other);
    ~Timestamp();
    Timestamp &operator=(const Timestamp &other);
    Timestamp &operator=(TimeVal tv);

    void swap(Timestamp &timestamp) noexcept;
    void update();

    bool operator==(const Timestamp &ts) const;
    bool operator!=(const Timestamp &ts) const;
    bool operator>(const Timestamp &ts) const;
    bool operator>=(const Timestamp &ts) const;
    bool operator<(const Timestamp &ts) const;
    bool operator<=(const Timestamp &ts) const;

    Timestamp operator+(TimeDiff d) const;
    Timestamp operator+(const Timespan &span) const;
    Timestamp operator-(TimeDiff d) const;
    Timestamp operator-(const Timespan &span) const;
    TimeDiff operator-(const Timestamp &ts) const;
    Timestamp &operator+=(TimeDiff d);
    Timestamp &operator+=(const Timespan &span);
    Timestamp &operator-=(TimeDiff d);
    Timestamp &operator-=(const Timespan &span);

    std::time_t epochTime() const;
    UtcTimeVal utcTime() const;
    TimeVal epochMicroseconds() const;
    TimeDiff elapsed() const;
    bool isElapsed(TimeDiff interval) const;
    TimeVal raw() const;

    static Timestamp fromEpochTime(std::time_t t);
    static Timestamp fromUtcTime(UtcTimeVal val);

    static constexpr TimeDiff resolution();

#if defined(_WIN32)
    static Timestamp fromFileTimeNP(unsigned int fileTimeLow,
                                    unsigned int fileTimeHigh);
    void toFileTimeNP(unsigned int &fileTimeLow,
                      unsigned int &fileTimeHigh) const;
#endif

private:
    TimeVal _ts;
};

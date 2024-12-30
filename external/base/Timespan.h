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

#include <chrono>
#include "Timestamp.h"


class Timespan
{
public:
    using TimeDiff = Timestamp::TimeDiff;

    Timespan();
    Timespan(TimeDiff microseconds);
    Timespan(long seconds, long microseconds);
    Timespan(int days, int hours, int minutes, int seconds, int microSeconds);
    Timespan(const Timespan &timespan);

    template<class T, class Period>
    Timespan(const std::chrono::duration<T, Period> &dtime)
        : _span(std::chrono::duration_cast<std::chrono::microseconds>(dtime)
                        .count())
    {
    }

    ~Timespan();

    Timespan &operator=(const Timespan &timespan);
    Timespan &operator=(TimeDiff microseconds);
    Timespan &assign(int days, int hours, int minutes, int seconds,
                     int microSeconds);
    Timespan &assign(long seconds, long microseconds);

    template<class T, class Period>
    Timespan &assign(const std::chrono::duration<T, Period> &dtime)
    {
        _span = std::chrono::duration_cast<std::chrono::microseconds>(dtime)
                        .count();
        return *this;
    }

    void swap(Timespan &timespan) noexcept;

    bool operator==(const Timespan &ts) const;
    bool operator!=(const Timespan &ts) const;
    bool operator>(const Timespan &ts) const;
    bool operator>=(const Timespan &ts) const;
    bool operator<(const Timespan &ts) const;
    bool operator<=(const Timespan &ts) const;

    bool operator==(TimeDiff microSeconds) const;
    bool operator!=(TimeDiff microSeconds) const;
    bool operator>(TimeDiff microSeconds) const;
    bool operator>=(TimeDiff microSeconds) const;
    bool operator<(TimeDiff microSeconds) const;
    bool operator<=(TimeDiff microSeconds) const;

    Timespan operator+(const Timespan &d) const;
    Timespan operator-(const Timespan &d) const;
    Timespan &operator+=(const Timespan &d);
    Timespan &operator-=(const Timespan &d);

    Timespan operator+(TimeDiff microSeconds) const;
    Timespan operator-(TimeDiff microSeconds) const;
    Timespan &operator+=(TimeDiff microSeconds);
    Timespan &operator-=(TimeDiff microSeconds);

    int days() const;
    int hours() const;
    int totalHours() const;
    int minutes() const;
    int totalMinutes() const;
    int seconds() const;
    int totalSeconds() const;
    int milliseconds() const;
    TimeDiff totalMilliseconds() const;
    int microseconds() const;
    int useconds() const;
    TimeDiff totalMicroseconds() const;
    static const TimeDiff
            MILLISECONDS;
    static const TimeDiff SECONDS;
    static const TimeDiff MINUTES;
    static const TimeDiff HOURS;
    static const TimeDiff DAYS;

private:
    TimeDiff _span;
};
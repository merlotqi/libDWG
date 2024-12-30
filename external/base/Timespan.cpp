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


#include "Timespan.h"
#include <algorithm>

const Timespan::TimeDiff Timespan::MILLISECONDS = 1000;
const Timespan::TimeDiff Timespan::SECONDS = 1000 * Timespan::MILLISECONDS;
const Timespan::TimeDiff Timespan::MINUTES = 60 * Timespan::SECONDS;
const Timespan::TimeDiff Timespan::HOURS = 60 * Timespan::MINUTES;
const Timespan::TimeDiff Timespan::DAYS = 24 * Timespan::HOURS;

Timespan::Timespan() : _span(0) {}

Timespan::Timespan(TimeDiff microSeconds) : _span(microSeconds) {}

Timespan::Timespan(long seconds, long microSeconds)
    : _span(TimeDiff(seconds) * SECONDS + microSeconds)
{
}

Timespan::Timespan(int days, int hours, int minutes, int seconds,
                   int microSeconds)
    : _span(TimeDiff(microSeconds) + TimeDiff(seconds) * SECONDS +
            TimeDiff(minutes) * MINUTES + TimeDiff(hours) * HOURS +
            TimeDiff(days) * DAYS)
{
}

Timespan::Timespan(const Timespan &timespan) : _span(timespan._span) {}

Timespan::~Timespan() {}

Timespan &Timespan::operator=(const Timespan &timespan)
{
    _span = timespan._span;
    return *this;
}

Timespan &Timespan::operator=(TimeDiff microSeconds)
{
    _span = microSeconds;
    return *this;
}

int Timespan::days() const { return int(_span / DAYS); }

int Timespan::hours() const { return int((_span / HOURS) % 24); }

int Timespan::totalHours() const { return int(_span / HOURS); }

int Timespan::minutes() const { return int((_span / MINUTES) % 60); }

int Timespan::totalMinutes() const { return int(_span / MINUTES); }

int Timespan::seconds() const { return int((_span / SECONDS) % 60); }

int Timespan::totalSeconds() const { return int(_span / SECONDS); }

int Timespan::milliseconds() const
{
    return int((_span / MILLISECONDS) % 1000);
}

Timespan::TimeDiff Timespan::totalMilliseconds() const
{
    return _span / MILLISECONDS;
}

int Timespan::microseconds() const { return int(_span % 1000); }

int Timespan::useconds() const { return int(_span % 1000000); }

Timespan::TimeDiff Timespan::totalMicroseconds() const { return _span; }

bool Timespan::operator==(const Timespan &ts) const
{
    return _span == ts._span;
}

bool Timespan::operator!=(const Timespan &ts) const
{
    return _span != ts._span;
}

bool Timespan::operator>(const Timespan &ts) const { return _span > ts._span; }

bool Timespan::operator>=(const Timespan &ts) const
{
    return _span >= ts._span;
}

bool Timespan::operator<(const Timespan &ts) const { return _span < ts._span; }

bool Timespan::operator<=(const Timespan &ts) const
{
    return _span <= ts._span;
}

bool Timespan::operator==(TimeDiff microSeconds) const
{
    return _span == microSeconds;
}

bool Timespan::operator!=(TimeDiff microSeconds) const
{
    return _span != microSeconds;
}

bool Timespan::operator>(TimeDiff microSeconds) const
{
    return _span > microSeconds;
}

bool Timespan::operator>=(TimeDiff microSeconds) const
{
    return _span >= microSeconds;
}

bool Timespan::operator<(TimeDiff microSeconds) const
{
    return _span < microSeconds;
}

bool Timespan::operator<=(TimeDiff microSeconds) const
{
    return _span <= microSeconds;
}

void swap(Timespan &s1, Timespan &s2) noexcept { s1.swap(s2); }

Timespan &Timespan::assign(int days, int hours, int minutes, int seconds,
                           int microSeconds)
{
    _span = TimeDiff(microSeconds) + TimeDiff(seconds) * SECONDS +
            TimeDiff(minutes) * MINUTES + TimeDiff(hours) * HOURS +
            TimeDiff(days) * DAYS;
    return *this;
}

Timespan &Timespan::assign(long seconds, long microSeconds)
{
    _span = TimeDiff(seconds) * SECONDS + TimeDiff(microSeconds);
    return *this;
}

void Timespan::swap(Timespan &timespan) noexcept
{
    std::swap(_span, timespan._span);
}

Timespan Timespan::operator+(const Timespan &d) const
{
    return Timespan(_span + d._span);
}

Timespan Timespan::operator-(const Timespan &d) const
{
    return Timespan(_span - d._span);
}

Timespan &Timespan::operator+=(const Timespan &d)
{
    _span += d._span;
    return *this;
}

Timespan &Timespan::operator-=(const Timespan &d)
{
    _span -= d._span;
    return *this;
}

Timespan Timespan::operator+(TimeDiff microSeconds) const
{
    return Timespan(_span + microSeconds);
}

Timespan Timespan::operator-(TimeDiff microSeconds) const
{
    return Timespan(_span - microSeconds);
}

Timespan &Timespan::operator+=(TimeDiff microSeconds)
{
    _span += microSeconds;
    return *this;
}

Timespan &Timespan::operator-=(TimeDiff microSeconds)
{
    _span -= microSeconds;
    return *this;
}

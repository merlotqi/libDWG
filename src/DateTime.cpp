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

namespace dwg {

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

}// namespace dwg
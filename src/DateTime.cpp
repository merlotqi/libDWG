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

TimeSpan::TimeSpan() {}
TimeSpan::TimeSpan(const TimeSpan &rhs){}
TimeSpan::TimeSpan(long long span){}
TimeSpan::TimeSpan(int day, int hour, int min, int sec){}

int TimeSpan::days() const {return 0;}
int TimeSpan::totalHours() const{return 0;}

int TimeSpan::hours() const{return 0;}

int TimeSpan::totalMinutes() const{return 0;}

int TimeSpan::minutes() const {return 0;}

/**
 * @brief Gets the total number of seconds in the time span.
 * @return The total number of seconds.
 */
int totalSeconds() const;

/**
 * @brief Gets the number of seconds in the time span (excluding whole minutes).
 * @return The number of seconds.
 */
int seconds() const;

operator long long() const;

TimeSpan &operator=(const TimeSpan &rhs);
TimeSpan &operator=(const long long span);
bool operator==(const TimeSpan &rhs) const;
bool operator!=(const TimeSpan &rhs) const;
bool operator>(const TimeSpan &rhs) const;
bool operator<(const TimeSpan &rhs) const;
bool operator<=(const TimeSpan &rhs) const;
bool operator>=(const TimeSpan &rhs) const;
TimeSpan operator+(const TimeSpan &rhs) const;
TimeSpan operator-(const TimeSpan &rhs) const;
TimeSpan &operator+=(const TimeSpan &rhs);
TimeSpan &operator-=(const TimeSpan &rhs);

}// namespace dwg
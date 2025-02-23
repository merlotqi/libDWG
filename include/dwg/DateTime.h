
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

#include <dwg/exports.h>
#include <string>

namespace dwg {

class LIBDWG_API TimeSpan
{
    long long _timeSpan;

public:
    /**
     * @brief Default constructor.
     * Initializes the TimeSpan object with a time span of zero.
     */
    TimeSpan();

    /**
     * @brief Copy constructor.
     * @param rhs The TimeSpan object to copy from.
     */
    TimeSpan(const TimeSpan &rhs);

    /**
     * @brief Constructor initializing with a specific time span in seconds.
     * @param span The time span in seconds.
     */
    TimeSpan(long long span);

    /**
     * @brief Constructor initializing with days, hours, minutes, and seconds.
     * @param day The number of days.
     * @param hour The number of hours.
     * @param min The number of minutes.
     * @param sec The number of seconds.
     */
    TimeSpan(int day, int hour, int min, int sec);

    /**
     * @brief Gets the number of days in the time span.
     * @return The number of days.
     */
    int days() const;

    /**
     * @brief Gets the total number of hours in the time span.
     * @return The total number of hours.
     */
    int totalHours() const;

    /**
     * @brief Gets the number of hours in the time span (excluding whole days).
     * @return The number of hours.
     */
    int hours() const;

    /**
     * @brief Gets the total number of minutes in the time span.
     * @return The total number of minutes.
     */
    int totalMinutes() const;

    /**
     * @brief Gets the number of minutes in the time span (excluding whole hours).
     * @return The number of minutes.
     */
    int minutes() const;

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
};


enum class WeekDay
{
    eSunday,
    eMonday,
    eTuesday,
    eWednesday,
    eThursday,
    eFriday,
    eSaturday,
};

/**
 * @brief DateTime class represents date and time, default is in Coordinated Universal Time (UTC).
 * 
 * For more information, see: https://en.wikipedia.org/wiki/Coordinated_Universal_Time
 */
class LIBDWG_API DateTime
{
    /**
    * @brief Number of seconds passed since January 1, 1970.
    * 
    * @details The Unix epoch (January 1 1970 00:00:00 GMT) is equivalent to January 1 1970 08:00:00 local time in China.
    * @details 1: time_t type represents the actual timestamp. This is the long long Time stored in the kernel.
    * @details 2: time_t now = time(0), which verifies the concept of a timestamp. It returns the current timestamp.
    */
    long long _time;

public:
    /**
     * @brief Default constructor, initializes to the current UTC time.
     * 
     */
    DateTime();

    /**
     * @brief Copy constructor.
     * 
     * @param rhs The DateTime object to copy from.
     */
    DateTime(const DateTime &rhs);

    /**
     * @brief  Constructor initializing with the number of seconds passed since January 1, 1970.
     * 
     * @param tm The timestamp in seconds.
     * @param bUTC Indicates whether the timestamp is in UTC. Default is false.
     */
    DateTime(long long tm, bool bUTC = false);

    /**
     * @brief  Constructor initializing with year, month, day, hour, minute, and second.
     * 
     * @param year Four-digit year (yyyy).
     * @param mon Month [1-12].
     * @param day Day [1-31].
     * @param hour Hour [0-23].
     * @param min Minute [0-59].
     * @param sec Second [0-59].
     */
    DateTime(int year, int mon, int day, int hour, int min, int sec);

    /**
     * @brief  Gets the current time zone offset in seconds.
     * @details The time zone offset is the difference between UTC time and local time. For example, the offset for UTC+8 is -28800 (-8 * 60 * 60).
     * 
     * @return The time zone offset in seconds.
     */
    static long long timeZone();

    /**
     * @brief Gets the current local time.
     * 
     * @return DateTime
     */
    static DateTime now();
    /**
     * @brief Converts the current local time to UTC time.
     * @details Equivalent to subtracting the time zone offset from the current time.
     * 
     * @return DateTime 
     */
    DateTime toUTC() const;

    /**
     * @brief Converts the current UTC time to local time.
     * @details Equivalent to adding the time zone offset to the current time.
     * 
     * @return DateTime 
     */
    DateTime toLocal() const;

    /**
     * @brief Constructs a DateTime object based on year, month, day, hour, minute, and second (in Beijing time zone).
     * @details If the computed timestamp is less than 0, it uses 0.
     * 
     * @param year Four-digit year (yyyy).
     * @param mon Month [1-12].
     * @param day Day [1-31].
     * @param hour Hour [0-23].
     * @param min Minute [0-59].
     * @param sec Second [0-59].
     */
    void makeDateTime(int year, int mon, int day, int hour, int min, int sec);

    int year() const;
    int month() const;
    int day() const;
    int hour() const;
    int minute() const;
    int second() const;
    WeekDay dayOfWeek() const;

    operator time_t() const;

    DateTime &operator=(const long long tim);
    DateTime &operator=(const DateTime &rhs);
    bool operator==(const DateTime &rhs) const;
    bool operator!=(const DateTime &rhs) const;
    bool operator>(const DateTime &rhs) const;
    bool operator<(const DateTime &rhs) const;
    bool operator<=(const DateTime &rhs) const;
    bool operator>=(const DateTime &rhs) const;
    DateTime operator+(const TimeSpan &rhs) const;
    DateTime operator-(const TimeSpan &rhs) const;
    TimeSpan operator-(const DateTime &rhs) const;
    DateTime &operator+=(const TimeSpan &rhs);
    DateTime &operator-=(const TimeSpan &rhs);

    /**
     * @brief Converts the DateTime object to a long date string.
     * @details Format: %Y-%m-%d
     * 
     * @return std::string 
     */
    std::string toLongDateString() const;

    /**
     * @brief Converts the DateTime object to a long date and time string.
     * @details Format: %Y-%m-%d %H:%M:%S
     * 
     * @return std::string 
     */
    std::string toLongTimeString() const;

    /**
     * @brief Converts the DateTime object to a short date string.
     * @details Format: %Y/%m/%d
     * 
     * @return std::string 
     */
    std::string toShortDateString() const;

    /**
     * @brief Converts the DateTime object to a short date and time string.
     * @details Format: %Y/%m/%d %H:%M
     * 
     * @return std::string 
     */
    std::string toShortTimeString() const;

    /**
     * @brief Converts the DateTime object to a string.
     * @details Format: %Y-%m-%d %H:%M:%S
     * 
     * @return std::string 
     */
    std::string toString() const;

    /**
     * @brief Converts the DateTime object to a string based on the specified format.
     * @details Refer to strftime for format specifications: http://www.cplusplus.com/reference/ctime/strftime/
     * 
     * @param format  The format string.
     * @return std::string 
     */
    std::string toString(const char *format) const;
};

}// namespace dwg
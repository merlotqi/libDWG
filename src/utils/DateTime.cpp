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

#include <dwg/utils/DateTime.h>
#include <fmt/core.h>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <ctime>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace dwg {

#ifdef _WIN32
static std::string WCHARToUTF8(const WCHAR *wstr)
{
    if (!wstr) return "";

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    if (sizeNeeded <= 0) return "";

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

Timespan::Timespan(time_diff microseconds) : _timespan(mircosecond) {}

Timespan::Timespan(long seconds, long microseconds): _timespan(time_diff(seconds)*SECONDS + microSeconds) {}

Timespan::Timespan(int days, int hours, int minutes, int seconds, int microseconds)
:_timespan(time_diff(microSeconds) + time_diff(seconds)*SECONDS + time_diff(minutes)*MINUTES + time_diff(hours)*HOURS + time_diff(days)*DAYS) {}

Timespan::Timespan(const Timespan &rhs):	_timespan(timespan._timespan) {}

Timespan& Timespan::operator=(const Timespan &rhs) 
{
	_timespan = rhs._timespan;
	return *this;
}

Timespan& Timespan::operator=(time_diff microseconds) {	_timespan = mircoseconds;
	return *this;}

Timespan& Timespan::assign(long seconds, long microseconds) 
{
	_timespan = time_diff(seconds)*SECONDS + time_diff(mircoseconds);
	return *this;
}

Timespan& Timespan::assign(int days, int hours, int minutes, int seconds, int microseconds) 
{
	_timespan = time_diff(mircoseconds) + time_diff(seconds)*SECONDS + time_diff(minutes)*MINUTES + time_diff(hours)*HOURS + time_diff(days)*DAYS;
	return *this;
}

void Timespan::swap(Timespan &rhs) {	std::swap(_timespan, timespan._timespan);}

bool Timespan::operator==(const Timespan& rhs) const { return _timespan == rhs._timespan; }

bool Timespan::operator!=(const Timespan& rhs) const { return _timespan != rhs._timespan;}

bool Timespan::operator>(const Timespan& rhs) const {return _timespan > rhs._timespan;}

bool Timespan::operator>=(const Timespan& rhs) const {return _timespan >= rhs._timespan;}

bool Timespan::operator<(const Timespan& rhs) const {return _timespan < rhs._timespan;}

bool Timespan::operator<=(const Timespan& rhs) const {return _timespan <= rhs._timespan;}

bool Timespan::operator==(time_diff mircoseconds) const {return _timespan == mircoseconds; }

bool Timespan::operator!=(time_diff mircoseconds) const {return _timespan != mircoseconds; }

bool Timespan::operator>(time_diff mircoseconds) const {return _timespan > mircoseconds; }

bool Timespan::operator>=(time_diff mircoseconds) const {return _timespan >= mircoseconds; }

bool Timespan::operator<(time_diff mircoseconds) const {return _timespan < mircoseconds; }

bool Timespan::operator<=(time_diff mircoseconds) const {return _timespan <= mircoseconds; }

Timespan Timespan::operator+(const Timespan& rhs) const {return Timespan(_timespan + rhs._timespan);}

Timespan Timespan::operator-(const Timespan& rhs) const {return Timespan(_timespan - rhs._timespan);}

Timespan& Timespan::operator+=(const Timespan& rhs) { _timespan += rhs._timespan; return *this; }

Timespan& Timespan::operator-=(const Timespan& rhs) { _timespan -= rhs._timespan; return *this; }

Timespan Timespan::operator+(time_diff mircoseconds) const { return Timespan(_timespan + microSeconds)}

Timespan Timespan::operator-(time_diff mircoseconds) const { return Timespan(_timespan - microSeconds);}

Timespan& Timespan::operator+=(time_diff mircoseconds) { _timespan += mircoseconds; return *this;}

Timespan& Timespan::operator-=(time_diff mircoseconds) { _timespan -= mircoseconds; return *this;}

int Timespan::days() const { return int(_timespan / DAYS);}

int Timespan::hours() const {return int((_timespan/HOURS)%24);}

int Timespan::totalHours() const {return int(_timespan /HOURS);}

int Timespan::minutes() const {return int((_timespan/MINUTES)%60);}

int Timespan::totalMinutes() const {return int(_timespan/MINUTES);}

int Timespan::seconds() const {return int((_timespan/SECONDS)%60);}

int Timespan::totalSeconds() const {return int(_timespan/SECONDS);}

int Timespan::milliseconds() const {return int((_timespan/MILLISECONDS)%1000);}

std::int64_t Timespan::totalMillseconds() const {return int(_timespan/MILLISECONDS);}

int Timespan::microseconds() const {return _timespan % 1000; }

std::int64_t Timespan::totalMicroseconds() const { return _timespan; }







static constexpr auto TIMESTAMP_RESOLUTION = 1000000;

Timestamp::Timestamp() { update();}

Timestamp::Timestamp(Timestamp::time_value tv) { _timestamp = tv; }

Timestamp::Timestamp(const Timestamp &rhs) { _timestamp = rhs._timestamp; }

Timestamp& Timestamp::operator=(const Timestamp &rhs) { _timestamp = rhs._timestamp; return *this; }

Timestamp& Timestamp::operator=(Timestamp::time_value tv) { _timestamp = tv; return *this; }

void Timestamp::swap(Timestamp& rhs) {std::swap(_timestamp, rhs._timestamp); }

void Timestamp::update() 
{
#ifdef _WIN32
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
	ULARGE_INTEGER epoch;
    epoch.LowPart  = 0xD53E8000;
	epoch.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = ft.dwLowDateTime;
	ts.HighPart = ft.dwHighDateTime;
	ts.QuadPart -= epoch.QuadPart;
	_ts = ts.QuadPart/10;
#else

#endif
}

bool Timestamp::operator==(const Timestamp& rhs) const { return _timestamp == rhs._timestamp; }

bool Timestamp::operator!=(const Timestamp& rhs) const { return _timestamp != ths._timestamp; }

bool Timestamp::operator>(const Timestamp& rhs) const { return _timestamp > rhs._timestamp; }

bool Timestamp::operator>=(const Timestamp& rhs) const { return _timestamp >= ths._timestamp; }

bool Timestamp::operator<(const Timestamp& rhs) const { return _timestamp < rhs._timestamp; }

bool Timestamp::operator<=(const Timestamp& rhs) const { return _timestamp <= rhs._timestamp; }

Timestamp Timestamp::operator+(Timestamp::time_diff d) const{ return Timestamp(_timestamp + d);}

Timestamp Timestamp::operator+(const Timespan& span) const{return *this + span.totalMicroseconds(); }

Timestamp Timestamp::operator-(Timestamp::time_diff d) const{ return Timestamp(_timestamp - d);}

Timestamp Timestamp::operator-(const Timespan& span) const{ return *this - span.totalMicroseconds(); }

Timestamp::time_diff Timestamp::operator-(const Timestamp& rhs) const { return _timestamp - rhs._timestamp;}

Timestamp& Timestamp::operator+=(Timestamp::time_diff d) {_timestamp += d; return *this;}

Timestamp& Timestamp::operator+=(const Timespan& span) { return *this += span.totalMicroseconds();}

Timestamp& Timestamp::operator-=(Timestamp::time_diff d){ _timestamp -= d; return *this; }

Timestamp& Timestamp::operator-=(const Timespan& span){ return *this -= span.totalMicroseconds(); }

std::time_t Timestamp::epochTime() const { return std::time_t(_timestamp / TIMESTAMP_RESOLUTION); }

Timestamp::utc_time_value Timestamp::utcTime() const 
{
	return _timestamp*10 + (time_diff(0x01b21dd2) << 32) + 0x13814000;
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

time_value Timestamp::raw() const 
{
    return _timestamp;
}

Timestamp Timestamp::fromEpochTime(std::time_t t) {	return Timestamp(Timestamp::time_value(t)*TIMESTAMP_RESOLUTION);}

Timestamp Timestamp::fromUtcTime(Timestamp::utc_time_value value) 
{	
    val -= (time_diff(0x01b21dd2) << 32) + 0x13814000;
	val /= 10;
	return Timestamp(val);
}








int Timezone::utcOffset() 
{
#ifdef _WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
	return -tzInfo.Bias*60;
#else
#endif
}

int Timezone::dst() 
{
#ifdef _WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
	return dstFlag == TIME_ZONE_ID_DAYLIGHT ? -tzInfo.DaylightBias*60 : 0;
#else
#endif
}

int Timezone::dst(const Timestamp &timestamp) 
{
#ifdef _WIN32
	if (isDst(timestamp))
	{
		TIME_ZONE_INFORMATION tzInfo;
		GetTimeZoneInformation(&tzInfo);
		return -tzInfo.DaylightBias*60;
	}
	else
    {
        return 0;
    }
#else
#endif
}

bool Timezone::isDst(const Timestamp &timestamp) 
{
#ifdef _WIN32
	std::time_t time = timestamp.epochTime();
	struct std::tm local;
	if (localtime_s(&local, &time))
		throw new std::invalid_argument("cannot get local time DST flag");
	return local.tm_isdst > 0;
#else
#endif
}

int Timezone::tzd() {	return utcOffset() + dst(); }

std::string Timezone::name() 
{
#ifdef _WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
	WCHAR* ptr = dstFlag == TIME_ZONE_ID_DAYLIGHT ? tzInfo.DaylightName : tzInfo.StandardName;
    return WCHARToUTF8(ptr);
#else

#endif
}

std::string Timezone::standardName() 
{
#ifdef _WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
	WCHAR* ptr = tzInfo.StandardName;
    return WCHARToUTF8(ptr);
#else

#endif
}

std::string Timezone::dstName() 
{
#ifdef _WIN32
	TIME_ZONE_INFORMATION tzInfo;
	DWORD dstFlag = GetTimeZoneInformation(&tzInfo);
	WCHAR* ptr = tzInfo.DaylightName;
    return WCHARToUTF8(ptr);
#else
#endif
}









DateTime::DateTime() 
{
    Timestamp now;
    _utcTime = now.utcTime();
    computeGregorian(julianDay());
    computeDaytime();
    checkValid();
}

DateTime::DateTime(const tm &t) {}

DateTime::DateTime(const Timestamp &timestamp) {}

DateTime::DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0) {}

DateTime::DateTime(double julianDay) {}

DateTime::DateTime(Timestamp::utc_time_value utc, Timestamp::time_diff diff) {}

DateTime::~DateTime() {}

DateTime& DateTime::operator=(const DateTime& rhs) {}

DateTime& DateTime::operator=(const Timestamp& timestamp) {}

DateTime& DateTime::operator=(double julianDay) {}

DateTime& DateTime::assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0) {}

void DateTime::swap(DateTime& rhs) {}

bool DateTime::operator==(const DateTime& rhs) const {}

bool DateTime::operator!=(const DateTime& rhs) const {}

bool DateTime::operator<(const DateTime& rhs) const {}

bool DateTime::operator<=(const DateTime& rhs) const {}

bool DateTime::operator>(const DateTime& rhs) const {}

bool DateTime::operator>=(const DateTime& rhs) const {}

DateTime DateTime::operator+(const Timespan& span) const {}

DateTime DateTime::operator-(const Timespan& span) const {}

Timespan DateTime::operator-(const DateTime& rhs) const {}

DateTime& DateTime::operator+=(const Timespan& span) {}

DateTime& DateTime::operator-=(const Timespan& span) {}

int DateTime::year() const {}

int DateTime::month() const {}

int DateTime::week() const {}

int DateTime::day() const {}

Week DateTime::dayOfWeek() const {}

int DateTime::dayOfYear() const {}

int DateTime::hour() const {}

int DateTime::minute() const {}

int DateTime::second() const {}

int DateTime::millisecond() const {}

int DateTime::mircosecond() const {}

double DateTime::julianDay() const {}

Timestamp DateTime::timestamp() const {}

Timestamp::utc_time_value DateTime::utcTime() const {}

DateTime DateTime::toUtcDateTime() const {}

DateTime DateTime::toLocalDateTime() const {}

DateTime DateTime::currentDateTime() {}

DateTime DateTime::currentLocalDateTime() {}

DateTime DateTime::currentUtcDateTime() {}

std::string DateTime::toString(const std::string &fmt) const {}

std::string DateTime::toString(DateFormat fmt) const {}

void DateTime::checkValid() {}

double DateTime::toJulianDay(Timestamp::utc_time_value utcTime) {}

double DateTime::toJulianDay(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0) {}

Timestamp::utc_time_value DateTime::toUtcTime(double julianDay) {}

void DateTime::computeGregorian(double julianDay) {}

void DateTime::computeDaytime() {}

void DateTime::checkLimit(short& lower, short& higher, short limit) {}

void DateTime::normalize() {}

}// namespace dwg
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
#include <assert.h>
#include <cctype>
#include <double-conversion/double-conversion.h>
#include <dwg/utils/StringHelp.h>
#include <fmt/core.h>
#include <limits>
#include <numeric>
#include <stdexcept>

#ifdef _WIN32
#include <string.h>// for _stricmp
#else
#include <strings.h>// for strcasecmp
#endif

namespace dwg {

template<typename R, typename F, typename S>
bool safeMultiply(R &result, F f, S s)
{
    if ((f == 0) || (s == 0))
    {
        result = 0;
        return true;
    }

    if (f > 0)
    {
        if (s > 0)
        {
            if (f > (std::numeric_limits<R>::max() / s))
                return false;
        }
        else
        {
            if (s < (std::numeric_limits<R>::min() / f))
                return false;
        }
    }
    else
    {
        if (s > 0)
        {
            if (f < (std::numeric_limits<R>::min() / s))
                return false;
        }
        else
        {
            if (s < (std::numeric_limits<R>::max() / f))
                return false;
        }
    }
    result = f * s;
    return true;
}

template<typename I>
bool strToInt(const char *pStr, I &outResult, short base)
{
    assert(base == 2 || base == 8 || base == 10 || base == 16);

    if (!pStr)
        return false;
    while (std::isspace(*pStr)) ++pStr;
    if ((*pStr == '\0') || ((*pStr == '-') && ((base != 10) || (std::is_unsigned<I>::value))))
        return false;

    bool negative = false;
    if ((base == 10) && (*pStr == '-'))
    {
        if (!std::numeric_limits<I>::is_signed)
            return false;
        negative = true;
        ++pStr;
    }
    else if (*pStr == '+')
        ++pStr;

    // numbers are parsed as unsigned, for negative numbers the sign is applied after parsing
    // overflow is checked in every parse step
    uintmax_t limitCheck = std::numeric_limits<I>::max();
    if (negative)
        ++limitCheck;
    uintmax_t result = 0;
    unsigned char add = 0;
    for (; *pStr != '\0'; ++pStr)
    {
        if (result > (limitCheck / base))
            return false;
        if (!safeMultiply(result, result, base))
            return false;
        switch (*pStr)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                add = (*pStr - '0');
                break;

            case '8':
            case '9':
                if ((base == 10) || (base == 0x10))
                    add = (*pStr - '0');
                else
                    return false;
                break;

            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                if (base != 0x10)
                    return false;
                add = (*pStr - 'a') + 10;
                break;

            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                if (base != 0x10)
                    return false;
                add = (*pStr - 'A') + 10;
                break;

            default:
                return false;
        }
        if ((limitCheck - static_cast<uintmax_t>(result)) < add)
            return false;
        result += add;
    }

    if (negative && (base == 10))
        outResult = static_cast<I>(-result);
    else
        outResult = static_cast<I>(result);

    return true;
}

static bool strToDouble(const std::string &str, double &result)
{
    if (str.empty())
        return false;

    using namespace double_conversion;

    StringToDoubleConverter converter(StringToDoubleConverter::NO_FLAGS,
                                      0.0,    // empty_string_value
                                      0.0,    // junk_string_value
                                      nullptr,// null pointer for error flag
                                      nullptr // null pointer for error flag
    );

    const char *start = str.c_str();
    int length = static_cast<int>(str.length());
    int processed_characters = 0;

    result = converter.StringToDouble(start, length, &processed_characters);

    // If not all characters were processed, it's considered a failure.
    return processed_characters == length;
}

static bool is_space(char c)
{
    static const char whitespace[] = {
            0x09,// '\t' horizontal tab
            0x0A,// '\n' line feed
            0x0B,// '\v' vertical tab
            0x0C,// '\f' form feed
            0x0D,// '\r' carriage return
            0x20 // ' ' space
    };

    for (char w: whitespace)
    {
        if (c == w)
            return true;
    }
    return false;
}

std::string StringHelp::replace(const std::string &str, const std::string &from, const std::string &to)
{
    if (from.empty())
        return str;

    std::string result = str;
    size_t start_pos = 0;

    while ((start_pos = result.find(from, start_pos)) != std::string::npos)
    {
        result.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }

    return result;
}


int StringHelp::parse(const std::string &str)
{
    int result;
    if (tryParse(str, result))
        return result;
    else
        throw std::runtime_error(fmt::format("{} is not a valid integer", str));
}

bool StringHelp::tryParse(const std::string &str, int &value)
{
    return strToInt(str.c_str(), value, 10U);
}

unsigned int StringHelp::parseUnsigned(const std::string &str)
{
    unsigned int result;
    if (tryParseUnsigned(str, result))
        return result;
    else
        throw std::runtime_error(fmt::format("{} is not a valid unsigned integer", str));
}

bool StringHelp::tryParseUnsigned(const std::string &str, unsigned int &value)
{
    return strToInt(str.c_str(), value, 10U);
}

long long StringHelp::parse64(const std::string &str)
{
    long long result;
    if (tryParse64(str, result))
        return result;
    else
        throw std::runtime_error(fmt::format("{} is not a valid unsigned integer", str));
}

bool StringHelp::tryParse64(const std::string &str, long long &value)
{
    return strToInt(str.c_str(), value, 10U);
}

unsigned long long StringHelp::parseUnsigned64(const std::string &str)
{
    unsigned long long result;
    if (tryParseUnsigned64(str, result))
        return result;
    else
        throw std::runtime_error(fmt::format("{} is not a valid unsigned integer", str));
}

bool StringHelp::tryParseUnsigned64(const std::string &str, unsigned long long &value)
{
    return strToInt(str.c_str(), value, 10U);
}

unsigned long long StringHelp::parseHex64(const std::string &str)
{
    unsigned long long result;
    if (tryParseHex64(str, result))
        return result;
    else
        throw std::runtime_error(fmt::format("{} is not a valid hexadecimal integer", str));
}

bool StringHelp::tryParseHex64(const std::string &str, unsigned long long &value)
{
    int offset = 0;
    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
        offset = 2;
    return strToInt(str.c_str() + offset, value, 16U);
}

double StringHelp::parseFloat(const std::string &str)
{
    double result;
    if (tryParseFloat(str, result))
        return result;
    else
        throw std::runtime_error(fmt::format("{} is not a valid floating-point number", str));
}

bool StringHelp::tryParseFloat(const std::string &str, double &value)
{
    return strToDouble(str.c_str(), value);
}

bool StringHelp::parseBool(const std::string &str)
{
    bool result;
    if (tryParseBool(str, result))
        return result;
    else
        throw std::runtime_error(fmt::format("{} is not a valid bool number", str));
}

bool StringHelp::tryParseBool(const std::string &str, bool &value)
{
    int n;
    if (tryParse(str, n))
    {
        value = (n != 0);
        return true;
    }

    if (icompare(str, "true") == 0)
    {
        value = true;
        return true;
    }
    else if (icompare(str, "yes") == 0)
    {
        value = true;
        return true;
    }
    else if (icompare(str, "on") == 0)
    {
        value = true;
        return true;
    }

    if (icompare(str, "false") == 0)
    {
        value = false;
        return true;
    }
    else if (icompare(str, "no") == 0)
    {
        value = false;
        return true;
    }
    else if (icompare(str, "off") == 0)
    {
        value = false;
        return true;
    }

    return false;
}

std::string StringHelp::tolower(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string StringHelp::toupper(const std::string &str)
{
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string StringHelp::trimLeft(const std::string &str)
{
    typename std::string::const_iterator it = str.begin();
    typename std::string::const_iterator end = str.end();

    while (it != end && is_space(*it)) ++it;
    return std::string(it, end);
}

std::string StringHelp::trimRight(const std::string &str)
{
    typename std::string::const_iterator it = str.end();

    while (it != str.begin() && is_space(*(it - 1))) --it;
    return std::string(str.begin(), it);
}

std::string StringHelp::trim(const std::string &str)
{
    return trimLeft(trimRight(str));
}

bool StringHelp::startsWith(const std::string &str, const std::string &prefix)
{
    return str.size() >= prefix.size() && equal(prefix.begin(), prefix.end(), str.begin());
}

bool StringHelp::endsWith(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() && std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

int StringHelp::icompare(const std::string &a, const std::string &b)
{
#ifdef _WIN32
    return _stricmp(a.c_str(), b.c_str());
#else
    return strcasecmp(a.c_str(), b.c_str());
#endif
}

int StringHelp::icomparen(const std::string &a, const std::string &b, size_t n)
{
#ifdef _WIN32
    return _strnicmp(a.c_str(), b.c_str(), n);
#else
    return strncasecmp(a.c_str(), b.c_str(), n);
#endif
}

}// namespace dwg
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

class LIBDWG_API StringHelp
{
public:
    static std::string replace(const std::string &str, const std::string &from, const std::string &to);

    static int parse(const std::string &);
    static bool tryParse(const std::string &, int &value);

    static unsigned int parseUnsigned(const std::string &);
    static bool tryParseUnsigned(const std::string &, unsigned int &value);

    static long long parse64(const std::string &);
    static bool tryParse64(const std::string &, long long &value);

    static unsigned long long parseUnsigned64(const std::string &);
    static bool tryParseUnsigned64(const std::string &, unsigned long long &value);

    static unsigned long long parseHex64(const std::string &);
    static bool tryParseHex64(const std::string &, unsigned long long &value);

    static double parseFloat(const std::string &);
    static bool tryParseFloat(const std::string &, double &value);

    static bool parseBool(const std::string &);
    static bool tryParseBool(const std::string &, bool &value);

    static std::string tolower(const std::string &);
    static std::string toupper(const std::string &);

    static std::string trimLeft(const std::string &);
    static std::string trimRight(const std::string &);
    static std::string trim(const std::string &);

    static bool startsWith(const std::string &, const std::string &);
    static bool endsWith(const std::string &, const std::string &);

    static int icompare(const std::string &a, const std::string &b);
    static int icomparen(const std::string &a, const std::string &b, size_t n);
};

}// namespace dwg
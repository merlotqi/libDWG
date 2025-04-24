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

#include <string>

namespace dwg {
namespace StringHelp {

extern std::string replace(const std::string &str, const std::string &from, const std::string &to);

extern int parse(const std::string &, char thousandSeparator = ',');
extern bool tryParse(const std::string &, int& value, char thousandSeparator = ',');

extern unsigned int parseUnsigned(const std::string &, char thousandSeparator = ',');
extern bool tryParseUnsigned(const std::string &, unsigned int& value, char thousandSeparator = ',');

extern Int64 parse64(const std::string &, char thousandSeparator = ',');
extern bool tryParse64(const std::string &, Int64& value, char thousandSeparator = ',');

extern UInt64 parseUnsigned64(const std::string &, char thousandSeparator = ',');
extern bool tryParseUnsigned64(const std::string &, UInt64& value, char thousandSeparator = ',');

extern UInt64 parseHex64(const std::string &);
extern bool tryParseHex64(const std::string &, UInt64& value);

extern double parseFloat(const std::string &, char decimalSeparator = '.', char thousandSeparator = ',');
extern bool tryParseFloat(const std::string &, double& value, char decimalSeparator = '.', char thousandSeparator = ',');

extern bool parseBool(const std::string &);
extern bool tryParseBool(const std::string &, bool& value);

extern std::string tolower(const std::string &);
extern std::string toupper(const std::string &);

extern std::string trimLeft(const std::string &);
extern std::string trimRight(const std::string &);
extern std::string trim(const std::string &);

extern bool startsWith(const std::string &, const std::string &);
extern bool endsWith(const std::string &, const std::string &);

}// namespace StringHelp
}// namespace dwg
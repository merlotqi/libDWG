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
#include <dwg/utils/CodePages.h>
#include <vector>

namespace dwg {

class Encoding
{
    CodePage _codePage;
public:
    Encoding(CodePage codePage);
    virtual ~Encoding() = default;

    std::vector<unsigned char> GetBytes(const std::string& str) const;
    std::string GetString(const std::vector<unsigned char>& bytes) const;
    std::string GetString(const unsigned char* bytes, size_t length) const;

public:
    static Encoding UTF8();
    static Encoding Default();
    static Encoding ASCII();
    static Encoding Windows1252();
    static Encoding GBK();
    static Encoding GB18030();    
};


}// namespace dwg


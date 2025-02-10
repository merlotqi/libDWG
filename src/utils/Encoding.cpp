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

#include <dwg/utils/Encoding_p.h>
#include <iconv.h>
#include <map>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace dwg {

static std::map<CodePage, std::string> s_codepage_iconvid_mapping;

Encoding::Encoding()
    : cp(Utf8)
{}

Encoding::Encoding(CodePage codePage)
    : cp(codePage)
{}

std::string Encoding::toUtf8(const std::string& str)
{
    if(cp == Utf8)
    {
        return str;
    }
    else
    {
        return std::string();
    }
}

std::string Encoding::fromUtf8(const std::string &str)
{
    if(cp == Utf8)
    {
        return str;
    }
    else
    {
        return std::string();
    }
}

std::wstring Encoding::toUnicode(const std::string &wstr)
{
#ifdef _WIN32
#else
#endif
    return std::wstring();
}

std::string Encoding::fromUnicode(const std::wstring &wstr)
{
#ifdef _WIN32
#else
#endif
    return std::wstring();
}

CodePage Encoding::codePage() const
{
    return cp;
}

}// namespace dwg
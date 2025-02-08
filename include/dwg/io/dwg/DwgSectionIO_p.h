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

#include <dwg/ACadVersion.h>
#include <string>
#include <vector>

namespace dwg {

class DwgSectionIO
{
public:
    virtual std::string sectionName() const = 0;

    DwgSectionIO(ACadVersion version);
    
    static bool CheckSentinel(const std::vector<unsigned char> &actual, const std::vector<unsigned char> &expected);

protected:
    bool R13_14Only;
    bool R13_15Only;
    bool R2000Plus;
    bool R2004Pre;
    bool R2007Pre;
    bool R2004Plus;
    bool R2007Plus;
    bool R2010Plus;
    bool R2013Plus;
    bool R2018Plus;
    ACadVersion _version;
};

}// namespace dwg
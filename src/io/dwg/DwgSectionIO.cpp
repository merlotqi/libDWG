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

#include <dwg/io/dwg/DwgSectionIO_p.h>
#include <dwg/io/dwg/readers/IDwgStreamReader_p.h>
#include <fmt/format.h>
#include <string>
#include <vector>

namespace dwg {

DwgSectionIO::DwgSectionIO(ACadVersion version)
{
    _version = version;

    R13_14Only = version == ACadVersion::AC1014 || version == ACadVersion::AC1012;
    R13_15Only = version >= ACadVersion::AC1012 && version <= ACadVersion::AC1015;
    R2000Plus = version >= ACadVersion::AC1015;
    R2004Pre = version < ACadVersion::AC1018;
    R2007Pre = version <= ACadVersion::AC1021;
    R2004Plus = version >= ACadVersion::AC1018;
    R2007Plus = version >= ACadVersion::AC1021;
    R2010Plus = version >= ACadVersion::AC1024;
    R2013Plus = version >= ACadVersion::AC1027;
    R2018Plus = version >= ACadVersion::AC1032;
}

bool DwgSectionIO::CheckSentinel(const std::vector<unsigned char> &actual, const std::vector<unsigned char> &expected)
{
    if (expected.size() != actual.size())
        return false;

    for (int i = 0; i < expected.size(); i++)
    {
        if (actual[i] != expected[i])
        {
            return false;
        }
    }

    return true;
}

void DwgSectionIO::checkSentinel(IDwgStreamReader *sreader, const std::vector<unsigned char> &expected) 
{
    auto sn = sreader->readSentinel();
    if (!DwgSectionIO::CheckSentinel(sn, expected))
    {
        notify(fmt::format("Invalid section sentinel found in {}", sectionName()), Notification::Warning);
    }
}

void DwgSectionIO::notify(const std::string &message, Notification type) {}

}// namespace dwg
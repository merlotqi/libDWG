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

#include "DwgFileHeader.h"
#include "DwgFileHeaderAC15.h"
#include "DwgFileHeaderAC18.h"
#include "DwgFileHeaderAC21.h"
#include <stdexcept>

namespace dwg {
namespace io {


DwgFileHeader::DwgFileHeader(ACadVersion version) : Version(version) {}

DwgFileHeader *DwgFileHeader::CreateFileHeader(ACadVersion version)
{
    switch (version)
    {
        case ACadVersion::Unknown:
            throw new std::exception("not cupported");
        case ACadVersion::MC0_0:
        case ACadVersion::AC1_2:
        case ACadVersion::AC1_4:
        case ACadVersion::AC1_50:
        case ACadVersion::AC2_10:
        case ACadVersion::AC1002:
        case ACadVersion::AC1003:
        case ACadVersion::AC1004:
        case ACadVersion::AC1006:
        case ACadVersion::AC1009:
            throw new std::exception("not cupported");// version
        case ACadVersion::AC1012:
        case ACadVersion::AC1014:
        case ACadVersion::AC1015:
            return new DwgFileHeaderAC15(version);
        case ACadVersion::AC1018:
            return new DwgFileHeaderAC18(version);
        case ACadVersion::AC1021:
            return new DwgFileHeaderAC21(version);
        case ACadVersion::AC1024:
        case ACadVersion::AC1027:
        case ACadVersion::AC1032:
            //Check if it works...
            return new DwgFileHeaderAC18(version);
        default:
            break;
    };

    return nullptr;
}

}// namespace io
}// namespace dwg

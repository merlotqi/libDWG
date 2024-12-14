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

#include <dwg/tables/TableEntry.h>

namespace dwg {
namespace tables {

/// Display Ucs icon
enum UscIconType : short
{
    /// Off; No icon is displayed
    Off,
    /// On; the icon is displayed only in the lower-left corner of the current viewport or layout
    OnLower,
    /// Off; if the icon is turned on, it is displayed at the UCS origin, if possible
    OffOrigin,
    /// On; Displays the UCS icon at the origin, if possible.
    OnOrigin
};

/// Default lighting type
enum DefaultLightingType : short
{
    /// One distant light
    OneDistantLight,
    /// Two distant lights
    TwoDistantLights,
};

enum GridFlags : short
{
    _0 = 0,
    _1 = 1,
    _2 = 2,
    _3 = 4,
    _4 = 8,
};

class VPort : public TableEntry
{
};

class VPortsTable : public Table<VPort>
{
};

}// namespace tables
}// namespace dwg

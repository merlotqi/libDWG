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

namespace dwg {

/// Dimension type
enum DimensionType
{
    /// Rotated, horizontal, or vertical
    Linear = 0,

    /// Aligned
    Aligned = 1,

    /// Angular 2 lines
    Angular = 2,

    /// Diameter
    Diameter = 3,

    /// Radius
    Radius = 4,

    /// Angular 3 points
    Angular3Point = 5,

    /// Ordinate
    Ordinate = 6,

    /// Indicates that the block reference(group code 2) is referenced by this dimension only
    BlockReference = 32,

    /// Ordinate type. If set, ordinate is X-type; if not set, ordinate is Y-type
    OrdinateTypeX = 64,

    /// Indicates if the dimension text has been positioned at a user-defined location rather than at the default location
    TextUserDefinedLocation = 128
};
typedef int DimensionTypes;

}// namespace dwg

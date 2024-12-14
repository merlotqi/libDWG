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
namespace tables {
    
/// Controls the placement of dimension text.
enum DimensionTextVerticalAlignment
{
    /// Centers the dimension text between the two parts of the dimension line.
    Centered = 0,

    /// Places the dimension text above the dimension line except when the dimension
    /// line is not horizontal and text inside the extension lines is forced horizontal
    /// (<see cref="DimensionStyle.TextInsideHorizontal"/> = true). The distance from
    /// the dimension line to the baseline of the lowest line of text is the current
    /// <see cref="DimensionStyle.DimensionLineGap" /> value.
    Above = 1,

    /// Places the dimension text on the side of the dimension line farthest away from
    /// the first defining point.
    Outside = 2,

    /// Places the dimension text to conform to a Japanese Industrial Standards (JIS)
    /// representation.
    JIS = 3,

    /// Places the dimension text under the dimension line.
    Below = 4
};

}// namespace tables
}// namespace dwg

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

/// Bitmask flags to set the various object sorting types.
enum class ObjectSortingFlags : unsigned char
{
    /// Disables SORTENTS.
    Disabled = 0,
    /// Sorts for object selection.
    Selection = 1,
    /// Sorts for object snap.
    Snap = 2,
    /// Sorts for redraws.
    Redraw = 4,
    /// Sorts for MSLIDE command slide creation.
    Slide = 8,
    /// Sorts for REGEN commands.
    Regen = 16,// 0x10
    /// Sorts for plotting.
    Plotting = 32,// 0x20
    /// Sorts for PostScript output.
    Postscript = 64,// 0x40
    /// Enable all sorting methods.
    All = Postscript | Plotting | Regen | Slide | Redraw | Snap | Selection,// 0x7F
};

}// namespace dwg
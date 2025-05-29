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

/// How dimension text and arrows are arranged when space is not sufficient to place both within the extension lines.
enum class TextArrowFitType : unsigned char
{
    /// Places both text and arrows outside extension lines
    Both = 0,
    /// Moves arrows first, then text
    ArrowsFirst = 1,
    /// Moves text first, then arrows
    TextFirst = 2,
    /// Moves either text or arrows, whichever fits best
    BestFit = 3
};

}// namespace dwg
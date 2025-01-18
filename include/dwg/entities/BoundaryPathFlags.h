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

#include <cpl_ports.h>

namespace dwg {

/// Defines the boundary path type of the hatch.
/// \remarks Bit flag
enum BoundaryPathFlag
{
    /// Default.
    Default = 0,
    /// External.
    External = 1,
    /// Polyline.
    Polyline = 2,
    /// Derived.
    Derived = 4,
    /// Text box.
    Textbox = 8,
    /// Outermost.
    Outermost = 16,
    /// Loop is not closed.
    NotClosed = 32,
    /// Self-intersecting loop.
    SelfIntersecting = 64,
    /// Text loop surrounded by an even number of loops.
    TextIsland = 128,
    /// Duplicate loop.
    Duplicate = 256,
    /// The bounding area is an annotative block.
    IsAnnotative = 512,
    /// The bounding type does not support scaling.
    DoesNotSupportScale = 1024,
    /// Forces all annotatives to be visible.
    ForceAnnoAllVisible = 2048,
    /// Orients hatch loop to paper.
    OrientToPaper = 4096,
    /// Describes if the hatch is an annotative block.
    IsAnnotativeBlock = 8192,
};
CPL_DECLARE_FLAGS(BoundaryPathFlags, BoundaryPathFlag)

}// namespace dwg

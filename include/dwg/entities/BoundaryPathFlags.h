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

/**
 * @enum BoundaryPathFlag
 * @brief Defines the flags for boundary path types of a hatch in a DWG/DXF drawing.
 *
 * This enum specifies different properties and characteristics of a hatch boundary path.
 * The flags can be combined to describe multiple attributes of the boundary, such as 
 * whether it is external, a polyline, or self-intersecting, among others.
 * \remarks Bit flag
 */
enum BoundaryPathFlag
{
    Default = 0,               ///< Default boundary path.
    External = 1,              ///< External boundary path.
    Polyline = 2,              ///< Polyline boundary path.
    Derived = 4,               ///< Derived boundary path.
    Textbox = 8,               ///< Text box boundary path.
    Outermost = 16,            ///< Outermost boundary path.
    NotClosed = 32,            ///< Loop is not closed.
    SelfIntersecting = 64,     ///< Self-intersecting loop.
    TextIsland = 128,          ///< Text island boundary path.
    Duplicate = 256,           ///< Duplicate loop.
    IsAnnotative = 512,        ///< Annotative bounding area.
    DoesNotSupportScale = 1024,///< Bounding type does not support scaling.
    ForceAnnoAllVisible = 2048,///< Forces all annotatives to be visible.
    OrientToPaper = 4096,      ///< Orients hatch loop to paper.
    IsAnnotativeBlock = 8192,  ///< Annotative block boundary path.
};
typedef int BoundaryPathFlags;

}// namespace dwg

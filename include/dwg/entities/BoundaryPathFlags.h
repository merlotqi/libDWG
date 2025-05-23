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

#include <dwg/utils/QFlags.h>

namespace dwg {

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
Q_DECLARE_FLAGS(BoundaryPathFlags, BoundaryPathFlag);

}// namespace dwg

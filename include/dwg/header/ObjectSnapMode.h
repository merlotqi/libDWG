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

/// Object snap mode AcDb::OsnapMask
enum class ObjectSnapMode : unsigned short
{
    /// Switch off all snapping modes
    None = 0,
    /// Snap to end point of lines, arcs, and to polyline vertices
    EndPoint = 1,
    /// Snap to mid point of lines, arcs, and polyline segments
    MidPoint = 2,
    /// Snap to center of circles, arcs. and polyline arc segments
    Center = 4,
    /// Snap to the center of point objects
    Node = 8,
    /// Snap to circle quadrant points at 0°, 90°, 180°, and 270°.
    Quadrant = 16,// 0x0010
    /// Snap to intersections of any two drawing objects
    Intersection = 32,// 0x0020
    /// Snap to insertion points of blocks, texts, and images.
    Insertion = 64,// 0x0040
    /// Snap to points which form a perpendicular with the selected object.
    Perpendicular = 128,// 0x0080
    /// Snap to tangent points
    Tangent = 256,// 0x0100
    /// Snap to the nearest point on a drawing object
    Nearest = 512,// 0x0200
    /// Clears all object snaps
    ClearsAllObjectSnaps = 1024,// 0x0400
    /// Snap to apparent intersections in the view
    ApparentIntersection = 2048,// 0x0800
    /// Snap to extensions of lines
    Extension = 4096,// 0x1000
    /// Parallel lines
    Parallel = 8192,// 0x2000
    /// All snapping modes on
    AllModes = Parallel | Extension | ApparentIntersection | ClearsAllObjectSnaps | Nearest | Tangent | Perpendicular |
               Insertion | Intersection | Quadrant | Node | Center | MidPoint | EndPoint,// 0x3FFF
    /// Switch off snapping
    SwitchedOff = 16384,// 0x4000
};

}// namespace dwg

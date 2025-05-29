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

/// Defines the spline flags
enum class SplineFlag : unsigned short
{
    /// None
    None = 0,

    /// Closed
    Closed = 1,

    /// Periodic
    Periodic = 2,

    /// Rational
    Rational = 4,

    /// Planar
    Planar = 8,

    /// Linear (planar flag is also set)
    Linear = 16,
};
Q_DECLARE_FLAGS(SplineFlags, SplineFlag);

/// Defines the spline flags 1
enum class SplineFlag1 : unsigned short
{
    /// None
    None = 0,

    /// Method fit points
    MethodFitPoints = 1,

    /// CV frame show
    CVFrameShow = 2,

    /// Is closed
    IsClosed = 4,

    /// Use knot parameter
    UseKnotParameter = 8,
};
Q_DECLARE_FLAGS(SplineFlags1, SplineFlag1);

}// namespace dwg
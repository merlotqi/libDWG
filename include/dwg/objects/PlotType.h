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

/// Defines the portion of paper space to output to the media
enum class PlotType
{
    /// Last screen display
    LastScreenDisplay = 0,

    /// Drawing extents
    DrawingExtents = 1,

    /// Drawing limits
    DrawingLimits = 2,

    /// View specified by the plot view name
    View = 3,

    /// Window specified by the upper-right and bottom-left window corners
    Window = 4,

    /// Layout information
    LayoutInformation = 5
};

}// namespace dwg
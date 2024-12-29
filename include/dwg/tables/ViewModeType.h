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

enum ViewModeType
{
    /// Off
    Off = 0,
    /// Perspective view
    PerspectiveView = 1,
    /// Front clipping
    FrontClipping = 2,
    /// Back clipping
    BackClipping = 4,
    ///
    Follow = 8,
    /// Front clipping not at the camera
    /// <remarks>
    /// If turned on, FRONTZ determines the front clipping plane.
    /// If turned off, FRONTZ is ignored, and the front clipping plane passes through the camera point.
    /// This setting is ignored if the front-clipping bit 2 is turned off.
    /// </remarks>
    FrontClippingZ = 16,
};

}// namespace dwg

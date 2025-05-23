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

/// viewport status flags
enum class ViewportStatusFlag
{
    /// Enables perspective mode.
    PerspectiveMode = 1,

    /// Enables front clipping.
    FrontClipping = 2,

    /// Enables back clipping.
    BackClipping = 4,

    /// Enables UCS follow.
    UcsFollow = 8,

    /// Enables front clip not at eye.
    FrontClipNotAtEye = 16,

    /// Enables UCS icon visibility.
    UcsIconVisibility = 32,

    /// Enables UCS icon at origin.
    UcsIconAtOrigin = 64,

    /// Enables fast zoom.
    FastZoom = 128,

    /// Enables snap mode.
    SnapMode = 256,

    /// Enables grid mode.
    GridMode = 512,

    /// Enables isometric snap style.
    IsometricSnapStyle = 1024,

    /// Enables hide plot mode.
    HidePlotMode = 2048,

    /// If set and IsoPairRight is not set, then isopair top is enabled. If both IsoPairTop and IsoPairRight are set, then isopair left is enabled
    IsoPairTop = 4096,

    /// If set and IsoPairTop is not set, then isopair right is enabled.
    IsoPairRight = 8192,

    /// Enables viewport zoom locking.
    ViewportZoomLocking = 16384,

    /// Currently always enabled.
    CurrentlyAlwaysEnabled = 32768,

    /// Enables non-rectangular clipping.
    NonRectangularClipping = 65536,

    /// Turns the viewport off.
    ViewportOff = 131072,

    /// Enables the display of the grid beyond the drawing limits.
    DisplayGridBeyondDrawingLimits = 262144,

    /// Enable adaptive grid display.
    AdaptiveGridDisplay = 524288,

    /// Enables subdivision of the grid below the set grid spacing when the grid display is adaptive.
    SubdivisionGridBelowSpacing = 1048576
};
Q_DECLARE_FLAGS(ViewportStatusFlags, ViewportStatusFlag);

}// namespace dwg

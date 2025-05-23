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

/// Defines the plot settings flag.
enum class PlotFlag
{
    /// None
    None = 0,

    /// Plot viewport borders.
    PlotViewportBorders = 1,

    /// Show plot styles.
    ShowPlotStyles = 2,

    /// Plot centered.
    PlotCentered = 4,

    /// Plot hidden.
    PlotHidden = 8,

    /// Use standard scale.
    UseStandardScale = 16,

    /// Plot styles.
    PlotPlotStyles = 32,

    /// Scale line weights.
    ScaleLineweights = 64,

    /// Print line weights.
    PrintLineweights = 128,

    /// Draw viewports first.
    DrawViewportsFirst = 512,

    /// Model type.
    ModelType = 1024,

    /// Update paper.
    UpdatePaper = 2048,

    /// Soon to paper on update.
    ZoomToPaperOnUpdate = 4096,

    /// Initializing.
    Initializing = 8192,

    /// Preview plot initialization.
    PrevPlotInit = 16384
};
Q_DECLARE_FLAGS(PlotFlags, PlotFlag);

}// namespace dwg

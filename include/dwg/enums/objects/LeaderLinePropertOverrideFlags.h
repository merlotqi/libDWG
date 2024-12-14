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
namespace objects {

/// These flags specify whether properties of a leader line primarily defined by the object are overridden for an individual leader line.
enum LeaderLinePropertOverrideFlags : int
{
    /// No property to be overridden
    None = 0,

    /// <see cref="MultiLeaderAnnotContext.LeaderLine.PathType" /> property
    /// overrides settings from <see cref="MultiLeader"/> and <see cref="MultiLeaderStyle"/>.
    PathType = 1,

    /// <see cref="MultiLeaderAnnotContext.LeaderLine.LineColor" /> property
    /// overrides settings from <see cref="MultiLeader"/> and <see cref="MultiLeaderStyle"/>.
    LineColor = 2,

    /// <see cref="MultiLeaderAnnotContext.LeaderLine.LineType"/> property
    /// overrides settings from <see cref="MultiLeader"/> and <see cref="MultiLeaderStyle"/>.
    LineType = 4,

    /// <see cref="MultiLeaderAnnotContext.LeaderLine.LineWeight" /> property
    /// overrides settings from <see cref="MultiLeader"/> and <see cref="MultiLeaderStyle"/>.
    LineWeight = 8,

    /// <see cref="MultiLeaderAnnotContext.LeaderLine.ArrowheadSize" /> property
    /// overrides settings from <see cref="MultiLeader"/> and <see cref="MultiLeaderStyle"/>.
    ArrowheadSize = 16,

    /// <see cref="MultiLeaderAnnotContext.LeaderLine.Arrowhead" /> property
    /// overrides settings from <see cref="MultiLeader"/> and <see cref="MultiLeaderStyle"/>.
    Arrowhead = 32,
};

}// namespace objects
}// namespace dwg
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

/// Defines the vertex flags.
enum class VertexFlag
{
    /// Default.
    Default = 0,
    /// Extra vertex created by curve-fitting.
    CurveFittingExtraVertex = 1,
    /// Curve-fit tangent defined for this vertex.
    /// A curve-fit tangent direction of 0 may be omitted from DXF output but is significant if this bit is set.
    CurveFitTangent = 2,
    /// Not used.
    NotUsed = 4,
    /// Spline vertex created by spline-fitting.
    SplineVertexFromSplineFitting = 8,
    /// Spline frame control point.
    SplineFrameControlPoint = 16,
    /// 3D polyline vertex.
    PolylineVertex3D = 32,
    /// 3D polygon mesh.
    PolygonMesh3D = 64,
    /// Polyface mesh vertex.
    PolyfaceMeshVertex = 128
};
Q_DECLARE_FLAGS(VertexFlags, VertexFlag);

}// namespace dwg

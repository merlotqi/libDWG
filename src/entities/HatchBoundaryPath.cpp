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

#include "HatchBoundaryPath.h"
#include <dwg/entities/HatchBoundaryPath.h>

namespace dwg {

DG_HatchBoundaryPath::HBP_Edge::HBP_Edge() {}

DG_HatchBoundaryPath::HBP_Edge::~HBP_Edge() {}

DG_HatchBoundaryPath::HBP_Edge *DG_HatchBoundaryPath::HBP_Edge::Clone() const { return nullptr; }

DG_HatchBoundaryPath::DG_HatchBoundaryPath() {}

DG_HatchBoundaryPath::~DG_HatchBoundaryPath() {}

bool DG_HatchBoundaryPath::IsPolyline() const { return false; }

DG_BoundaryPathFlags DG_HatchBoundaryPath::Flags() const { return DG_BoundaryPathFlags(); }

void DG_HatchBoundaryPath::Flags(DG_BoundaryPathFlags) {}

std::vector<DG_HatchBoundaryPath::HBP_Edge *> DG_HatchBoundaryPath::Edges() const { return std::vector<HBP_Edge *>(); }

void DG_HatchBoundaryPath::Edges(const std::vector<HBP_Edge *> &edges) {}

std::vector<DG_Entity *> DG_HatchBoundaryPath::Entities() const { return std::vector<DG_Entity *>(); }

void DG_HatchBoundaryPath::Entities(const std::vector<DG_Entity *> &entities) {}

/* --------------------------------- HBP_Arc -------------------------------- */

DG_HatchBoundaryPath::HBP_Arc::HBP_Arc()
    : _center(XY::Zero), _radius(0.0), _startAngle(0.0), _endAngle(2 * M_PI), _counterClockWise(false)
{
}

DG_HatchBoundaryPath::HBP_Arc::~HBP_Arc() {}

DG_HatchBoundaryPath::HBP_EdgeType DG_HatchBoundaryPath::HBP_Arc::Type() const { return HBP_EdgeType::HBP_CircularArc; }

XY DG_HatchBoundaryPath::HBP_Arc::Center() const { return _center; }

void DG_HatchBoundaryPath::HBP_Arc::Center(const XY &center) { _center = center; }

double DG_HatchBoundaryPath::HBP_Arc::Radius() const { return _radius; }

void DG_HatchBoundaryPath::HBP_Arc::Radius(double radius) { _radius = radius; }

double dwg::DG_HatchBoundaryPath::HBP_Arc::StartAngle() const { return _startAngle; }

void dwg::DG_HatchBoundaryPath::HBP_Arc::StartAngle(double startAngle) { _startAngle = startAngle; }

double DG_HatchBoundaryPath::HBP_Arc::EndAngle() const { return _endAngle; }

void DG_HatchBoundaryPath::HBP_Arc::EndAngle(double endAngle) { _endAngle = endAngle; }

bool DG_HatchBoundaryPath::HBP_Arc::CounterClockWise() const { return _counterClockWise; }

void DG_HatchBoundaryPath::HBP_Arc::CounterClockWise(bool counterClockWise) { _counterClockWise = counterClockWise; }

/* ------------------------------- HBP_Ellipse ------------------------------ */

DG_HatchBoundaryPath::HBP_Ellipse::HBP_Ellipse()
    : _center(XY::Zero), _majorAxisEndPoint(XY::Zero), _minorToMajorRatio(0.0), _startAngle(0.0), _endAngle(2 * M_PI),
      _counterClockWise(false)
{
}

DG_HatchBoundaryPath::HBP_Ellipse::~HBP_Ellipse() {}

DG_HatchBoundaryPath::HBP_EdgeType DG_HatchBoundaryPath::HBP_Ellipse::Type() const
{
    return HBP_EdgeType::HBP_EllipticArc;
}

XY DG_HatchBoundaryPath::HBP_Ellipse::Center() const { return _center; }

void DG_HatchBoundaryPath::HBP_Ellipse::Center(const XY &center) { _center = center; }

XY DG_HatchBoundaryPath::HBP_Ellipse::MajorAxisEndPoint() const { return _majorAxisEndPoint; }

void DG_HatchBoundaryPath::HBP_Ellipse::MajorAxisEndPoint(const XY &majorAxisEndPoint)
{
    _majorAxisEndPoint = majorAxisEndPoint;
}

double DG_HatchBoundaryPath::HBP_Ellipse::MinorToMajorRatio() const { return _minorToMajorRatio; }

void DG_HatchBoundaryPath::HBP_Ellipse::MinorToMajorRatio(double minorToMajorRatio)
{
    _minorToMajorRatio = minorToMajorRatio;
}

double DG_HatchBoundaryPath::HBP_Ellipse::StartAngle() const { return _startAngle; }

void DG_HatchBoundaryPath::HBP_Ellipse::StartAngle(double startAngle) { _startAngle = startAngle; }

double DG_HatchBoundaryPath::HBP_Ellipse::EndAngle() const { return _endAngle; }

void DG_HatchBoundaryPath::HBP_Ellipse::EndAngle(double endAngle) { _endAngle = endAngle; }

bool DG_HatchBoundaryPath::HBP_Ellipse::CounterClockWise() const { return _counterClockWise; }

void DG_HatchBoundaryPath::HBP_Ellipse::CounterClockWise(bool counterClockWise)
{
    _counterClockWise = counterClockWise;
}

/* -------------------------------- HBP_Line -------------------------------- */

DG_HatchBoundaryPath::HBP_Line::HBP_Line() : _start(XY::Zero), _end(XY::Zero) {}

DG_HatchBoundaryPath::HBP_Line::~HBP_Line() {}

DG_HatchBoundaryPath::HBP_EdgeType DG_HatchBoundaryPath::HBP_Line::Type() const { return HBP_EdgeType::HBP_Line; }

XY DG_HatchBoundaryPath::HBP_Line::Start() const { return _start; }

void DG_HatchBoundaryPath::HBP_Line::Start(const XY &start) { _start = start; }

XY DG_HatchBoundaryPath::HBP_Line::End() const { return _end; }

void DG_HatchBoundaryPath::HBP_Line::End(const XY &end) { _end = end; }

/* ------------------------------ HBP_Polyline ------------------------------ */

DG_HatchBoundaryPath::HBP_Polyline::HBP_Polyline() {}

DG_HatchBoundaryPath::HBP_Polyline::~HBP_Polyline() {}

DG_HatchBoundaryPath::HBP_EdgeType DG_HatchBoundaryPath::HBP_Polyline::Type() const
{
    return HBP_EdgeType::HBP_Polyline;
}

bool DG_HatchBoundaryPath::HBP_Polyline::HasBulge() const
{
    auto itFind = std::find_if(_bulges.begin(), _bulges.end(), [](double bulge) { return bulge != 0.0; });
    return itFind != _bulges.end();
}

bool DG_HatchBoundaryPath::HBP_Polyline::IsClosed() const { return _closed; }

void DG_HatchBoundaryPath::HBP_Polyline::IsClosed(bool isClosed) { _closed = isClosed; }

std::vector<XYZ> DG_HatchBoundaryPath::HBP_Polyline::Vertices() const { return _vertices; }

void DG_HatchBoundaryPath::HBP_Polyline::Vertices(const std::vector<XYZ> &vertices) { _vertices = vertices; }

std::vector<double> DG_HatchBoundaryPath::HBP_Polyline::Bulges() const { return _bulges; }

void DG_HatchBoundaryPath::HBP_Polyline::Bulges(const std::vector<double> &bulges) { _bulges = bulges; }

/* ------------------------------- HBP_Spline ------------------------------- */

DG_HatchBoundaryPath::HBP_Spline::HBP_Spline() {}

DG_HatchBoundaryPath::HBP_Spline::~HBP_Spline() {}

DG_HatchBoundaryPath::HBP_EdgeType DG_HatchBoundaryPath::HBP_Spline::Type() const { return HBP_EdgeType::HBP_Spline; }

int DG_HatchBoundaryPath::HBP_Spline::Degree() const { return _degree; }

void DG_HatchBoundaryPath::HBP_Spline::Degree(int degree) { _degree = degree; }

bool DG_HatchBoundaryPath::HBP_Spline::Rational() const { return _rational; }

void DG_HatchBoundaryPath::HBP_Spline::Rational(bool rational) { _rational = rational; }

bool DG_HatchBoundaryPath::HBP_Spline::Periodic() const { return _periodic; }

void DG_HatchBoundaryPath::HBP_Spline::Periodic(bool periodic) { _periodic = periodic; }

std::vector<double> DG_HatchBoundaryPath::HBP_Spline::Knots() const { return _knots; }

void DG_HatchBoundaryPath::HBP_Spline::Knots(const std::vector<double> &knots) { _knots = knots; }

std::vector<XYZ> DG_HatchBoundaryPath::HBP_Spline::ControlPoints() const { return _controlPoints; }

void DG_HatchBoundaryPath::HBP_Spline::ControlPoints(const std::vector<XYZ> &controlPoints)
{
    _controlPoints = controlPoints;
}

std::vector<XY> DG_HatchBoundaryPath::HBP_Spline::FitPoints() const { return _fitPoints; }

void DG_HatchBoundaryPath::HBP_Spline::FitPoints(const std::vector<XY> &fitPoints) { _fitPoints = fitPoints; }

XY DG_HatchBoundaryPath::HBP_Spline::StartTangent() const { return _startTangent; }

void DG_HatchBoundaryPath::HBP_Spline::StartTangent(const XY &startTangent) { _startTangent = startTangent; }

XY DG_HatchBoundaryPath::HBP_Spline::EndTangent() const { return _endTangent; }

void DG_HatchBoundaryPath::HBP_Spline::EndTangent(const XY &endTangent) { _endTangent = endTangent; }

}// namespace dwg
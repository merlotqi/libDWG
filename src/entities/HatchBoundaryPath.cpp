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

HatchBoundaryPath::HBP_Edge::HBP_Edge() {}

HatchBoundaryPath::HBP_Edge::~HBP_Edge() {}

HatchBoundaryPath::HBP_Edge *HatchBoundaryPath::HBP_Edge::Clone() const { return nullptr; }

HatchBoundaryPath::HatchBoundaryPath() {}

HatchBoundaryPath::~HatchBoundaryPath() {}

bool HatchBoundaryPath::IsPolyline() const { return false; }

BoundaryPathFlags HatchBoundaryPath::Flags() const { return BoundaryPathFlags(); }

void HatchBoundaryPath::Flags(BoundaryPathFlags) {}

std::vector<HatchBoundaryPath::HBP_Edge *> HatchBoundaryPath::Edges() const { return std::vector<HBP_Edge *>(); }

void HatchBoundaryPath::Edges(const std::vector<HBP_Edge *> &edges) {}

std::vector<Entity *> HatchBoundaryPath::Entities() const { return std::vector<Entity *>(); }

void HatchBoundaryPath::Entities(const std::vector<Entity *> &entities) {}

/* --------------------------------- HBP_Arc -------------------------------- */

HatchBoundaryPath::HBP_Arc::HBP_Arc()
    : _center(XY::Zero), _radius(0.0), _startAngle(0.0), _endAngle(2 * M_PI), _counterClockWise(false)
{
}

HatchBoundaryPath::HBP_Arc::~HBP_Arc() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Arc::Type() const { return HBP_EdgeType::HBP_CircularArc; }

XY HatchBoundaryPath::HBP_Arc::Center() const { return _center; }

void HatchBoundaryPath::HBP_Arc::Center(const XY &center) { _center = center; }

double HatchBoundaryPath::HBP_Arc::Radius() const { return _radius; }

void HatchBoundaryPath::HBP_Arc::Radius(double radius) { _radius = radius; }

double dwg::HatchBoundaryPath::HBP_Arc::StartAngle() const { return _startAngle; }

void dwg::HatchBoundaryPath::HBP_Arc::StartAngle(double startAngle) { _startAngle = startAngle; }

double HatchBoundaryPath::HBP_Arc::EndAngle() const { return _endAngle; }

void HatchBoundaryPath::HBP_Arc::EndAngle(double endAngle) { _endAngle = endAngle; }

bool HatchBoundaryPath::HBP_Arc::CounterClockWise() const { return _counterClockWise; }

void HatchBoundaryPath::HBP_Arc::CounterClockWise(bool counterClockWise) { _counterClockWise = counterClockWise; }

/* ------------------------------- HBP_Ellipse ------------------------------ */

HatchBoundaryPath::HBP_Ellipse::HBP_Ellipse()
    : _center(XY::Zero), _majorAxisEndPoint(XY::Zero), _minorToMajorRatio(0.0), _startAngle(0.0), _endAngle(2 * M_PI),
      _counterClockWise(false)
{
}

HatchBoundaryPath::HBP_Ellipse::~HBP_Ellipse() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Ellipse::Type() const { return HBP_EdgeType::HBP_EllipticArc; }

XY HatchBoundaryPath::HBP_Ellipse::Center() const { return _center; }

void HatchBoundaryPath::HBP_Ellipse::Center(const XY &center) { _center = center; }

XY HatchBoundaryPath::HBP_Ellipse::MajorAxisEndPoint() const { return _majorAxisEndPoint; }

void HatchBoundaryPath::HBP_Ellipse::MajorAxisEndPoint(const XY &majorAxisEndPoint)
{
    _majorAxisEndPoint = majorAxisEndPoint;
}

double HatchBoundaryPath::HBP_Ellipse::MinorToMajorRatio() const { return _minorToMajorRatio; }

void HatchBoundaryPath::HBP_Ellipse::MinorToMajorRatio(double minorToMajorRatio)
{
    _minorToMajorRatio = minorToMajorRatio;
}

double HatchBoundaryPath::HBP_Ellipse::StartAngle() const { return _startAngle; }

void HatchBoundaryPath::HBP_Ellipse::StartAngle(double startAngle) { _startAngle = startAngle; }

double HatchBoundaryPath::HBP_Ellipse::EndAngle() const { return _endAngle; }

void HatchBoundaryPath::HBP_Ellipse::EndAngle(double endAngle) { _endAngle = endAngle; }

bool HatchBoundaryPath::HBP_Ellipse::CounterClockWise() const { return _counterClockWise; }

void HatchBoundaryPath::HBP_Ellipse::CounterClockWise(bool counterClockWise) { _counterClockWise = counterClockWise; }

/* -------------------------------- HBP_Line -------------------------------- */

HatchBoundaryPath::HBP_Line::HBP_Line() : _start(XY::Zero), _end(XY::Zero) {}

HatchBoundaryPath::HBP_Line::~HBP_Line() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Line::Type() const { return HBP_EdgeType::HBP_Line; }

XY HatchBoundaryPath::HBP_Line::Start() const { return _start; }

void HatchBoundaryPath::HBP_Line::Start(const XY &start) { _start = start; }

XY HatchBoundaryPath::HBP_Line::End() const { return _end; }

void HatchBoundaryPath::HBP_Line::End(const XY &end) { _end = end; }

/* ------------------------------ HBP_Polyline ------------------------------ */

HatchBoundaryPath::HBP_Polyline::HBP_Polyline() {}

HatchBoundaryPath::HBP_Polyline::~HBP_Polyline() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Polyline::Type() const { return HBP_EdgeType::HBP_Polyline; }

bool HatchBoundaryPath::HBP_Polyline::HasBulge() const
{
    auto itFind = std::find_if(_bulges.begin(), _bulges.end(), [](double bulge) { return bulge != 0.0; });
    return itFind != _bulges.end();
}

bool HatchBoundaryPath::HBP_Polyline::IsClosed() const { return _closed; }

void HatchBoundaryPath::HBP_Polyline::IsClosed(bool isClosed) { _closed = isClosed; }

std::vector<XYZ> HatchBoundaryPath::HBP_Polyline::Vertices() const { return _vertices; }

void HatchBoundaryPath::HBP_Polyline::Vertices(const std::vector<XYZ> &vertices) { _vertices = vertices; }

std::vector<double> HatchBoundaryPath::HBP_Polyline::Bulges() const { return _bulges; }

void HatchBoundaryPath::HBP_Polyline::Bulges(const std::vector<double> &bulges) { _bulges = bulges; }

/* ------------------------------- HBP_Spline ------------------------------- */

HatchBoundaryPath::HBP_Spline::HBP_Spline() {}

HatchBoundaryPath::HBP_Spline::~HBP_Spline() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Spline::Type() const { return HBP_EdgeType::HBP_Spline; }

int HatchBoundaryPath::HBP_Spline::Degree() const { return _degree; }

void HatchBoundaryPath::HBP_Spline::Degree(int degree) { _degree = degree; }

bool HatchBoundaryPath::HBP_Spline::Rational() const { return _rational; }

void HatchBoundaryPath::HBP_Spline::Rational(bool rational) { _rational = rational; }

bool HatchBoundaryPath::HBP_Spline::Periodic() const { return _periodic; }

void HatchBoundaryPath::HBP_Spline::Periodic(bool periodic) { _periodic = periodic; }

std::vector<double> HatchBoundaryPath::HBP_Spline::Knots() const { return _knots; }

void HatchBoundaryPath::HBP_Spline::Knots(const std::vector<double> &knots) { _knots = knots; }

std::vector<XYZ> HatchBoundaryPath::HBP_Spline::ControlPoints() const { return _controlPoints; }

void HatchBoundaryPath::HBP_Spline::ControlPoints(const std::vector<XYZ> &controlPoints)
{
    _controlPoints = controlPoints;
}

std::vector<XY> HatchBoundaryPath::HBP_Spline::FitPoints() const { return _fitPoints; }

void HatchBoundaryPath::HBP_Spline::FitPoints(const std::vector<XY> &fitPoints) { _fitPoints = fitPoints; }

XY HatchBoundaryPath::HBP_Spline::StartTangent() const { return _startTangent; }

void HatchBoundaryPath::HBP_Spline::StartTangent(const XY &startTangent) { _startTangent = startTangent; }

XY HatchBoundaryPath::HBP_Spline::EndTangent() const { return _endTangent; }

void HatchBoundaryPath::HBP_Spline::EndTangent(const XY &endTangent) { _endTangent = endTangent; }

}// namespace dwg
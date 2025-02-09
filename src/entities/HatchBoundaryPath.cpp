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

HatchBoundaryPath::HBP_Edge *HatchBoundaryPath::HBP_Edge::clone() const { return nullptr; }

HatchBoundaryPath::HatchBoundaryPath() {}

HatchBoundaryPath::~HatchBoundaryPath() {}

bool HatchBoundaryPath::isPolyline() const { return false; }

BoundaryPathFlags HatchBoundaryPath::flags() const { return BoundaryPathFlags(); }

void HatchBoundaryPath::setFlags(BoundaryPathFlags) {}

std::vector<HatchBoundaryPath::HBP_Edge *> HatchBoundaryPath::edges() const { return std::vector<HBP_Edge *>(); }

void HatchBoundaryPath::setEdges(const std::vector<HBP_Edge *> &edges) {}

std::vector<Entity *> HatchBoundaryPath::entities() const { return std::vector<Entity *>(); }

void HatchBoundaryPath::setEntities(const std::vector<Entity *> &entities) {}

/* --------------------------------- HBP_Arc -------------------------------- */

HatchBoundaryPath::HBP_Arc::HBP_Arc()
    : _center(XY::Zero), _radius(0.0), _startAngle(0.0), _endAngle(2 * M_PI), _counterClockWise(false)
{
}

HatchBoundaryPath::HBP_Arc::~HBP_Arc() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Arc::type() const { return HBP_EdgeType::HBP_CircularArc; }

XY HatchBoundaryPath::HBP_Arc::center() const { return _center; }

void HatchBoundaryPath::HBP_Arc::setCenter(const XY &center) { _center = center; }

double HatchBoundaryPath::HBP_Arc::radius() const { return _radius; }

void HatchBoundaryPath::HBP_Arc::setRadius(double radius) { _radius = radius; }

double dwg::HatchBoundaryPath::HBP_Arc::startAngle() const { return _startAngle; }

void dwg::HatchBoundaryPath::HBP_Arc::setStartAngle(double startAngle) { _startAngle = startAngle; }

double HatchBoundaryPath::HBP_Arc::endAngle() const { return _endAngle; }

void HatchBoundaryPath::HBP_Arc::setEndAngle(double endAngle) { _endAngle = endAngle; }

bool HatchBoundaryPath::HBP_Arc::counterClockWise() const { return _counterClockWise; }

void HatchBoundaryPath::HBP_Arc::setCounterClockWise(bool counterClockWise) { _counterClockWise = counterClockWise; }

/* ------------------------------- HBP_Ellipse ------------------------------ */

HatchBoundaryPath::HBP_Ellipse::HBP_Ellipse()
    : _center(XY::Zero), _majorAxisEndPoint(XY::Zero), _minorToMajorRatio(0.0), _startAngle(0.0), _endAngle(2 * M_PI),
      _counterClockWise(false)
{
}

HatchBoundaryPath::HBP_Ellipse::~HBP_Ellipse() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Ellipse::type() const { return HBP_EdgeType::HBP_EllipticArc; }

XY HatchBoundaryPath::HBP_Ellipse::center() const { return _center; }

void HatchBoundaryPath::HBP_Ellipse::setCenter(const XY &center) { _center = center; }

XY HatchBoundaryPath::HBP_Ellipse::majorAxisEndPoint() const { return _majorAxisEndPoint; }

void HatchBoundaryPath::HBP_Ellipse::setMajorAxisEndPoint(const XY &majorAxisEndPoint)
{
    _majorAxisEndPoint = majorAxisEndPoint;
}

double HatchBoundaryPath::HBP_Ellipse::minorToMajorRatio() const { return _minorToMajorRatio; }

void HatchBoundaryPath::HBP_Ellipse::setMinorToMajorRatio(double minorToMajorRatio)
{
    _minorToMajorRatio = minorToMajorRatio;
}

double HatchBoundaryPath::HBP_Ellipse::startAngle() const { return _startAngle; }

void HatchBoundaryPath::HBP_Ellipse::setStartAngle(double startAngle) { _startAngle = startAngle; }

double HatchBoundaryPath::HBP_Ellipse::endAngle() const { return _endAngle; }

void HatchBoundaryPath::HBP_Ellipse::setEndAngle(double endAngle) { _endAngle = endAngle; }

bool HatchBoundaryPath::HBP_Ellipse::counterClockWise() const { return _counterClockWise; }

void HatchBoundaryPath::HBP_Ellipse::setCounterClockWise(bool counterClockWise)
{
    _counterClockWise = counterClockWise;
}

/* -------------------------------- HBP_Line -------------------------------- */

HatchBoundaryPath::HBP_Line::HBP_Line() : _start(XY::Zero), _end(XY::Zero) {}

HatchBoundaryPath::HBP_Line::~HBP_Line() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Line::type() const { return HBP_EdgeType::HBP_Line; }

XY HatchBoundaryPath::HBP_Line::start() const { return _start; }

void HatchBoundaryPath::HBP_Line::setStart(const XY &start) { _start = start; }

XY HatchBoundaryPath::HBP_Line::end() const { return _end; }

void HatchBoundaryPath::HBP_Line::setEnd(const XY &end) { _end = end; }

/* ------------------------------ HBP_Polyline ------------------------------ */

HatchBoundaryPath::HBP_Polyline::HBP_Polyline() {}

HatchBoundaryPath::HBP_Polyline::~HBP_Polyline() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Polyline::type() const { return HBP_EdgeType::HBP_Polyline; }

bool HatchBoundaryPath::HBP_Polyline::hasBulge() const
{
    auto itFind = std::find_if(_bulges.begin(), _bulges.end(), [](double bulge) { return bulge != 0.0; });
    return itFind != _bulges.end();
}

bool HatchBoundaryPath::HBP_Polyline::isClosed() const { return _closed; }

void HatchBoundaryPath::HBP_Polyline::setIsClosed(bool isClosed) { _closed = isClosed; }

std::vector<XYZ> HatchBoundaryPath::HBP_Polyline::vertices() const { return _vertices; }

void HatchBoundaryPath::HBP_Polyline::setVertices(const std::vector<XYZ> &vertices) { _vertices = vertices; }

std::vector<double> HatchBoundaryPath::HBP_Polyline::bulges() const { return _bulges; }

void HatchBoundaryPath::HBP_Polyline::setBulges(const std::vector<double> &bulges) { _bulges = bulges; }

/* ------------------------------- HBP_Spline ------------------------------- */

HatchBoundaryPath::HBP_Spline::HBP_Spline() {}

HatchBoundaryPath::HBP_Spline::~HBP_Spline() {}

HatchBoundaryPath::HBP_EdgeType HatchBoundaryPath::HBP_Spline::type() const { return HBP_EdgeType::HBP_Spline; }

int HatchBoundaryPath::HBP_Spline::degree() const { return _degree; }

void HatchBoundaryPath::HBP_Spline::setDegree(int degree) { _degree = degree; }

bool HatchBoundaryPath::HBP_Spline::rational() const { return _rational; }

void HatchBoundaryPath::HBP_Spline::setRational(bool rational) { _rational = rational; }

bool HatchBoundaryPath::HBP_Spline::periodic() const { return _periodic; }

void HatchBoundaryPath::HBP_Spline::setPeriodic(bool periodic) { _periodic = periodic; }

std::vector<double> HatchBoundaryPath::HBP_Spline::knots() const { return _knots; }

void HatchBoundaryPath::HBP_Spline::setKnots(const std::vector<double> &knots) { _knots = knots; }

std::vector<XYZ> HatchBoundaryPath::HBP_Spline::controlPoints() const { return _controlPoints; }

void HatchBoundaryPath::HBP_Spline::setControlPoints(const std::vector<XYZ> &controlPoints)
{
    _controlPoints = controlPoints;
}

std::vector<XY> HatchBoundaryPath::HBP_Spline::fitPoints() const { return _fitPoints; }

void HatchBoundaryPath::HBP_Spline::setFitPoints(const std::vector<XY> &fitPoints) { _fitPoints = fitPoints; }

XY HatchBoundaryPath::HBP_Spline::startTangent() const { return _startTangent; }

void HatchBoundaryPath::HBP_Spline::setStartTangent(const XY &startTangent) { _startTangent = startTangent; }

XY HatchBoundaryPath::HBP_Spline::endTangent() const { return _endTangent; }

void HatchBoundaryPath::HBP_Spline::setEndTangent(const XY &endTangent) { _endTangent = endTangent; }

}// namespace dwg
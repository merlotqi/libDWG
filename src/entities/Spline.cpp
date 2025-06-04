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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/Spline.h>

namespace dwg {

Spline::Spline() {}

Spline::~Spline() {}

ObjectType Spline::objectType() const
{
    return ObjectType::SPLINE;
}

std::string Spline::objectName() const
{
    return DxfFileToken::EntitySpline;
}

std::string Spline::subclassMarker() const
{
    return DxfSubclassMarker::Spline;
}

XYZ Spline::normal() const
{
    return _normal;
}

void Spline::setNormal(const XYZ &value)
{
    _normal = value;
}

SplineFlags Spline::flags() const
{
    return _flags;
}

void Spline::setFlags(SplineFlags value)
{
    _flags = value;
}

int Spline::degree() const
{
    return _degree;
}

void Spline::setDegree(int value)
{
    _degree = value;
}

std::vector<double> Spline::knots() const
{
    return _knots;
}

std::vector<double> &Spline::knots()
{
    return _knots;
}

void Spline::setKnots(const std::vector<double> &value)
{
    _knots = value;
}

std::vector<XYZ> Spline::controlPoints() const
{
    return _controlPoints;
}

std::vector<XYZ> &Spline::controlPoints()
{
    return _controlPoints;
}

void Spline::setControlPoints(const std::vector<XYZ> &value)
{
    _controlPoints = value;
}

std::vector<XYZ> Spline::fitPoints() const
{
    return _fitPoints;
}

std::vector<XYZ> &Spline::fitPoints()
{
    return _fitPoints;
}

void Spline::setFitPoints(const std::vector<XYZ> &value)
{
    _fitPoints = value;
}

double Spline::knotTolerance() const
{
    return _knotTolerance;
}

void Spline::setKnotTolerance(double value)
{
    _knotTolerance = value;
}

double Spline::controlPointTolerance() const
{
    return _controlPointTolerance;
}

void Spline::setControlPointTolerance(double value)
{
    _controlPointTolerance = value;
}

double Spline::fitTolerance() const
{
    return _fitTolerance;
}

void Spline::setFitTolerance(double value)
{
    _fitTolerance = value;
}

XYZ Spline::startTangent() const
{
    return _startTangent;
}

void Spline::setStartTangent(const XYZ &value)
{
    _startTangent = value;
}

XYZ Spline::endTangent() const
{
    return _endTangent;
}

void Spline::setEndTangent(const XYZ &value)
{
    _endTangent = value;
}

std::vector<double> Spline::weights() const
{
    return _weights;
}

std::vector<double> &Spline::weights()
{
    return _weights;
}

void Spline::setWeights(const std::vector<double> &value)
{
    _weights = value;
}

SplineFlag1 Spline::flags1() const
{
    return _flags1;
}

void Spline::setFlags1(SplineFlag1 value)
{
    _flags1 = value;
}

KnotParameterization Spline::knotParameterization() const
{
    return _knotParameterization;
}

void Spline::setKnotParameterization(KnotParameterization value)
{
    _knotParameterization = value;
}

}// namespace dwg
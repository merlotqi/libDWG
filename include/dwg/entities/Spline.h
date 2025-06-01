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

#include <dwg/entities/Entity.h>
#include <dwg/entities/KnotParameterization.h>
#include <dwg/entities/SplineFlags.h>

namespace dwg {

class LIBDWG_API Spline : public Entity
{
    SplineFlag1 _flags1;
    KnotParameterization _knotParameterization;

    XYZ _normal;
    SplineFlags _flags;
    int _degree;
    std::vector<double> _knots;
    std::vector<XYZ> _controlPoints;
    std::vector<XYZ> _fitPoints;
    double _knotTolerance;
    double _controlPointTolerance;
    double _fitTolerance;
    XYZ _startTangent;
    XYZ _endTangent;
    std::vector<double> _weights;

public:
    Spline();
    virtual ~Spline();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    XYZ normal() const;
    void setNormal(const XYZ &);

    SplineFlags flags() const;
    void setFlags(SplineFlags);

    int degree() const;
    void setDegree(int);

    std::vector<double> knots() const;
    void setKnots(const std::vector<double> &);

    std::vector<XYZ> controlPoints() const;
    void setControlPoints(const std::vector<XYZ> &);

    std::vector<XYZ> fitPoints() const;
    void setFitPoints(const std::vector<XYZ> &);

    double knotTolerance() const;
    void setKnotTolerance(double);

    double controlPointTolerance() const;
    void setControlPointTolerance(double);

    double fitTolerance() const;
    void setFitTolerance(double);

    XYZ startTangent() const;
    void setStartTangent(const XYZ &);

    XYZ endTangent() const;
    void setEndTangent(const XYZ &);

    std::vector<double> weights() const;
    void setWeights(const std::vector<double> &);

    SplineFlag1 flags1() const;
    void setFlags1(SplineFlag1);

    KnotParameterization knotParameterization() const;
    void setKnotParameterization(KnotParameterization);
};

}// namespace dwg
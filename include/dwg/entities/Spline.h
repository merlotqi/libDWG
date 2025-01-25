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

class LIBDWG_API DG_Spline : public DG_Entity
{
    DG_SplineFlag1 _flags1;
    DG_KnotParameterization _knotParameterization;

    XYZ _normal;
    DG_SplineFlags _flags;
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
    DG_Spline();

    virtual ~DG_Spline();

    // Override to return the object type of the Arc
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    XYZ Normal() const;
    void Normal(const XYZ &);

    DG_SplineFlags Flags() const;
    void Flags(DG_SplineFlags);

    int Degree() const;
    void Degree(int);

    std::vector<double> Knots() const;
    void Knots(const std::vector<double> &);

    std::vector<XYZ> ControlPoints() const;
    void ControlPoints(const std::vector<XYZ> &);

    std::vector<XYZ> FitPoints() const;
    void FitPoints(const std::vector<XYZ> &);

    double KnotTolerance() const;
    void KnotTolerance(double);

    double ControlPointTolerance() const;
    void ControlPointTolerance(double);

    double FitTolerance() const;
    void FitTolerance(double);

    XYZ StartTangent() const;
    void StartTangent(const XYZ &);

    XYZ EndTangent() const;
    void EndTangent(const XYZ &);

    std::vector<double> Weights() const;
    void Weights(const std::vector<double> &);

protected:
    DG_SplineFlag1 Flags1() const;
    void Flags1(DG_SplineFlag1);

    DG_KnotParameterization KnotParameterization() const;
    void KnotParameterization(DG_KnotParameterization);
};
CPL_SMARTER_PTR(DG_Spline)

}// namespace dwg

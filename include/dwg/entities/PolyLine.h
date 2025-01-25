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

#include <dwg/CadObjectCollection.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/PolylineFlags.h>
#include <dwg/entities/SmoothSurfaceType.h>
#include <dwg/entities/Vertex.h>

namespace dwg {

class LIBDWG_API DG_Polyline : public DG_Entity
{
public:
    DG_Polyline();
    ~DG_Polyline();

    virtual CPL::String ObjectName() const override;

    double Elevation() const;
    void Elevation(double);

    double Thickness() const;
    void Thickness(double);

    XYZ Normal() const;
    void Normal(const XYZ &);

    DG_PolylineFlags Flags() const;
    void Flags(DG_PolylineFlags);

    double StartWidth() const;
    void StartWidth(double);

    double EndWidth() const;
    void EndWidth(double);

    DG_SmoothSurfaceType SmoothSurface() const;
    void SmoothSurface(DG_SmoothSurfaceType);
};
CPL_SMARTER_PTR(DG_Polyline)

class Polyline2D : public DG_Polyline
{
public:
    Polyline2D();
    ~Polyline2D();
};

class Polyline3D : public DG_Polyline
{
public:
    Polyline3D();
    ~Polyline3D();
};


}// namespace dwg

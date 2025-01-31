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
#include <dwg/entities/LwPolylineFlags.h>

namespace dwg {

class LIBDWG_API DG_LwPolyline : public DG_Entity
{
public:
    DG_LwPolyline();

    virtual ~DG_LwPolyline();

    struct Vertex
    {
        XY Location;
        double Bulge;
        double StartWidth;
        double EndWidth;
        DG_VertexFlags Flags;
        double CurveTangent;
        int Id;
    };

    DG_ObjectType ObjectType() const;

    std::string ObjectName() const;

    std::string SubclassMarker() const;

    DG_LwPolylineFlags Flags() const;
    void Flags(DG_LwPolylineFlags);

    double ConstantWidth() const;
    void ConstantWidth(double);

    double Elevation() const;
    void Elevation(double);

    double Thickness() const;
    void Thickness();

    XYZ Normal() const;
    void Normal(const XYZ &);

    std::vector<Vertex> Vertices() const;
    void Vertices(const std::vector<Vertex> &);

    bool IsClosed() const;
    void IsClosed(bool);
};

}// namespace dwg

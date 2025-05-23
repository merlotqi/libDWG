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
#include <dwg/SeqendCollection.h>
#include <initializer_list>

namespace dwg {

class LIBDWG_API Polyline : public Entity
{
public:
    Polyline();
    ~Polyline();

    virtual std::string objectName() const override;

    double elevation() const;
    void setElevation(double);

    double thickness() const;
    void setThickness(double);

    XYZ normal() const;
    void setNormal(const XYZ &);

    PolylineFlags flags() const;
    void setFlags(PolylineFlags);

    double startWidth() const;
    void setStartWidth(double);

    double endWidth() const;
    void setEndWidth(double);

    SmoothSurfaceType smoothSurface() const;
    void setSmoothSurface(SmoothSurfaceType);

    bool isClosed() const;
    void setIsClosed(bool);

    SeqendCollection<Vertex *> vertices();
};

class Polyline2D : public Polyline
{
public:
    Polyline2D();
    Polyline2D(const std::initializer_list<Vertex2D *> &vertices, bool isClosed);
    ~Polyline2D();

    ObjectType objectType() const override;
    std::string subclassMarker() const override;
};

class Polyline3D : public Polyline
{
public:
    Polyline3D();
    Polyline3D(const std::initializer_list<Vertex3D *> &vertices, bool isClosed);
    Polyline3D(const std::initializer_list<XYZ> &vertices, bool isClosed);
    ~Polyline3D();

    ObjectType objectType() const override;
    std::string subclassMarker() const override;
};

}// namespace dwg
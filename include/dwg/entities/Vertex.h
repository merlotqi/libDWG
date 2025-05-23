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
#include <dwg/entities/VertexFlags.h>

namespace dwg {

class Vertex : public Entity
{
public:
    Vertex();
    Vertex(const XYZ &);
    ~Vertex();

    std::string objectName() const override;

    double bulge() const;
    void setBulge(double);

    double curveTangent() const;
    void setCurveTangent(double);

    double endWidth() const;
    void setEndWidth(double);

    double startWidth() const;
    void setStartWidth(double);

    VertexFlags flags() const;
    void setFlags(VertexFlags);

    int id() const;
    void setId(int);

    XYZ location() const;
    void setLocation(const XYZ &);

private:
    double _bulge;
    double _curveTangent;
    double _endWidth;
    double _startWidth;
    VertexFlags _flags;
    int _id;
    XYZ _location;
};


class Vertex2D : public Vertex
{
public:
    Vertex2D();
    Vertex2D(const XY &);
    Vertex2D(const XYZ &);
    ObjectType objectType() const override;
    std::string subclassMarker() const override;
};

class Vertex3D : public Vertex
{
public:
    Vertex3D();
    ObjectType objectType() const override;
    std::string subclassMarker() const override;
};

class VertexFaceMesh : public Vertex
{
public:
    VertexFaceMesh();
    VertexFaceMesh(const XYZ &);
    ObjectType objectType() const override;
    std::string subclassMarker() const override;
};

class VertexFaceRecord : public Vertex
{
public:
    VertexFaceRecord();
    VertexFaceRecord(const XYZ &);
    ObjectType objectType() const override;
    std::string subclassMarker() const override;

    short index1() const;
    void setIndex1(short);

    short index2() const;
    void setIndex2(short);

    short index3() const;
    void setIndex3(short);

    short index4() const;
    void setIndex4(short);

private:
    int _index1;
    int _index2;
    int _index3;
    int _index4;
};

}// namespace dwg
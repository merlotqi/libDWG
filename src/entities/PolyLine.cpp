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
#include <dwg/entities/PolyLine.h>
#include <dwg/entities/collection/VertexSeqendCollection.h>

namespace dwg {
/* -------------------------------- Polyline -------------------------------- */
Polyline::Polyline() {}

Polyline::~Polyline() {}

std::string Polyline::objectName() const
{
    return DxfFileToken::EntityPolyline;
}

double Polyline::elevation() const { return _elevation; }

void Polyline::setElevation(double value) { _elevation = value; }

double Polyline::thickness() const { return _thickness; }

void Polyline::setThickness(double value) { _thickness = value; }

XYZ Polyline::normal() const { return _normal; }

void Polyline::setNormal(const XYZ &value) {_normal = value; }

PolylineFlags Polyline::flags() const { return _flags; }

void Polyline::setFlags(PolylineFlags value) { _flags = value; }

double Polyline::startWidth() const { return _startWidth; }

void Polyline::setStartWidth(double value) {_startWidth = value; }

double Polyline::endWidth() const { return _endWidth; }

void Polyline::setEndWidth(double value) {_endWidth = value; }

SmoothSurfaceType Polyline::smoothSurface() const { return _smoothSurface; }

void Polyline::setSmoothSurface(SmoothSurfaceType value) { _smoothSurface = value; }

bool Polyline::isClosed() const { return _isClosed; }

void Polyline::setIsClosed(bool value) { _isClosed = value; }

VertexSeqendCollection *Polyline::vertices()
{
    return _vertices;
}

/* ------------------------------- Polyline2D ------------------------------- */
Polyline2D::Polyline2D() {}

Polyline2D::Polyline2D(const std::initializer_list<Vertex2D *> &vertices, bool isClosed) {}

Polyline2D::~Polyline2D() {}

ObjectType Polyline2D::objectType() const { return ObjectType::POLYLINE_2D; }

std::string Polyline2D::subclassMarker() const { return DxfSubclassMarker::Polyline; }

/* ------------------------------- Polyline3D ------------------------------- */
Polyline3D::Polyline3D() {}

Polyline3D::Polyline3D(const std::initializer_list<Vertex3D *> &vertices, bool isClosed) {}

Polyline3D::Polyline3D(const std::initializer_list<XYZ> &vertices, bool isClosed) {}

Polyline3D::~Polyline3D() {}

ObjectType Polyline3D::objectType() const { return ObjectType::POLYLINE_3D; }

std::string Polyline3D::subclassMarker() const { return DxfSubclassMarker::Polyline3d; }

}// namespace dwg
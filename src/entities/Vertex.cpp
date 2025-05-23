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
#include <dwg/entities/Vertex.h>

namespace dwg {

/* --------------------------------- Vertex --------------------------------- */
Vertex::Vertex() {}

Vertex::Vertex(const XYZ & v) {}

Vertex::~Vertex() {}

std::string Vertex::objectName() const { return DxfFileToken::EntityVertex; }

double Vertex::bulge() const { return _bulge; }

void Vertex::setBulge(double v) { _bulge = v; }

double Vertex::curveTangent() const { return _curveTangent; }

void Vertex::setCurveTangent(double v) { _curveTangent = v; }

double Vertex::endWidth() const { return _endWidth; }

void Vertex::setEndWidth(double v) { _endWidth = v; }

double Vertex::startWidth() const { return _startWidth; }

void Vertex::setStartWidth(double v) { _startWidth = v; }

VertexFlags Vertex::flags() const { return _flags; }

void Vertex::setFlags(VertexFlags v) { _flags = v; }

int Vertex::id() const { return _id; }

void Vertex::setId(int v) { _id = v; }

XYZ Vertex::location() const { return _location; }

void Vertex::setLocation(const XYZ &v) { _location = v; }

/* -------------------------------- Vertex2D -------------------------------- */

Vertex2D::Vertex2D() : Vertex(XYZ::Zero) {}

Vertex2D::Vertex2D(const XY &v) : Vertex(v) {}

Vertex2D::Vertex2D(const XYZ &v) : Vertex(v) {}

ObjectType Vertex2D::objectType() const { return ObjectType::VERTEX_2D; }

std::string Vertex2D::subclassMarker() const { return DxfSubclassMarker::PolylineVertex; }

/* -------------------------------- Vertex3D -------------------------------- */

Vertex3D::Vertex3D() : Vertex(XYZ::Zero) {}

ObjectType Vertex3D::objectType() const { return ObjectType::VERTEX_3D; }

std::string Vertex3D::subclassMarker() const { return DxfSubclassMarker::Polyline3dVertex; }

/* ----------------------------- VertexFaceMesh ----------------------------- */

VertexFaceMesh::VertexFaceMesh() : Vertex(XYZ::Zero) {}

VertexFaceMesh::VertexFaceMesh(const XYZ &v) : Vertex(v) {}

ObjectType VertexFaceMesh::objectType() const { return ObjectType::VERTEX_PFACE; }

std::string VertexFaceMesh::subclassMarker() const { return DxfSubclassMarker::PolyfaceMeshVertex; }

/* ---------------------------- VertexFaceRecord ---------------------------- */

VertexFaceRecord::VertexFaceRecord() : Vertex(XYZ::Zero) {}

VertexFaceRecord::VertexFaceRecord(const XYZ &v) : Vertex(v) {}

ObjectType VertexFaceRecord::objectType() const { return ObjectType::VERTEX_PFACE_FACE; }

std::string VertexFaceRecord::subclassMarker() const { return DxfSubclassMarker::PolyfaceMeshFace; }

short VertexFaceRecord::index1() const { return _index1; }

void VertexFaceRecord::setIndex1(short v) { _index1 = v; }

short VertexFaceRecord::index2() const { return _index2; }

void VertexFaceRecord::setIndex2(short v) { _index2 = v; }

short VertexFaceRecord::index3() const { return _index3; }

void VertexFaceRecord::setIndex3(short v) { _index3 = v; }

short VertexFaceRecord::index4() const { return _index4; }

void VertexFaceRecord::setIndex4(short v) { _index4 = v; }   

}// namespace dwg
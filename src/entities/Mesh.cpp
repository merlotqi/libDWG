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
#include <dwg/entities/Mesh.h>

namespace dwg {

Mesh::Edge::Edge(int _start, int _end)
{
    start = _start;
    end = _end;
}

Mesh::Mesh() {}

Mesh::~Mesh() {}

ObjectType Mesh::objectType() const
{
    return ObjectType::UNLISTED;
}

std::string Mesh::objectName() const
{
    return DxfFileToken::EntityMesh;
}

std::string Mesh::subclassMarker() const
{
    return DxfSubclassMarker::Mesh;
}

short Mesh::version() const
{
    return _version;
}

void Mesh::setVersion(short value)
{
    _version = value;
}

bool Mesh::blendCrease() const
{
    return _blendCrease;
}

void Mesh::setBlendCrease(bool blend)
{
    _blendCrease = blend;
}

int Mesh::subdivisionLevel() const
{
    return _subdivisionLevel;
}

void Mesh::setSubdivisionLevel(int level)
{
    _subdivisionLevel = level;
}

std::vector<XYZ> Mesh::vertices() const
{
    return _vertices;
}

std::vector<XYZ> &Mesh::vertices()
{
    return _vertices;
}

std::vector<std::vector<int>> Mesh::faces() const
{
    return _faces;
}

std::vector<std::vector<int>> &Mesh::faces()
{
    return _faces;
}

std::vector<Mesh::Edge> Mesh::edges() const
{
    return _edges;
}

std::vector<Mesh::Edge> &Mesh::edges()
{
    return _edges;
}

}// namespace dwg
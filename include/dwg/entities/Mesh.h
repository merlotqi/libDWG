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

namespace dwg {

class LIBDWG_API Mesh : public Entity
{
public:
    struct Edge
    {
        int Start;    ///< Index of the starting vertex.
        int End;      ///< Index of the ending vertex.
        double Crease;///< Crease value for subdivision (default: 0.0).

        Edge(int start, int end);
    };

public:
    Mesh();
    virtual ~Mesh();

    short version() const;
    void setVersion(short version);

    bool blendCrease() const;
    void setBlendCrease(bool blend);

    int subdivisionLevel() const;
    void setSubdivisionLevel(int level);

    std::vector<XYZ> vertices() const;
    void setVertices(const std::vector<XYZ> &vertices);

    std::vector<std::vector<int>> faces() const;
    void setFaces(const std::vector<std::vector<int>> &faces);

    std::vector<Mesh::Edge> edges() const;
    void setEdges(const std::vector<Mesh::Edge> &edges);
};

}// namespace dwg

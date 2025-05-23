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
#include <optional>

namespace dwg {

class LIBDWG_API Mesh : public Entity
{
public:
    struct Edge
    {
        int start;                   ///< Index of the starting vertex.
        int end;                     ///< Index of the ending vertex.
        std::optional<double> crease;///< Crease value for subdivision (default: 0.0).

        Edge(int start, int end);
    };

public:
    Mesh();
    virtual ~Mesh();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    short version() const;
    void setVersion(short version);

    bool blendCrease() const;
    void setBlendCrease(bool blend);

    int subdivisionLevel() const;
    void setSubdivisionLevel(int level);

    std::vector<XYZ> vertices() const;
    std::vector<XYZ> &vertices();

    std::vector<std::vector<int>> faces() const;
    std::vector<std::vector<int>> &faces();

    std::vector<Edge> edges() const;
    std::vector<Edge> &edges();

private:
    short _version;
    bool _blendCrease;
    int _subdivisionLevel;
    std::vector<XYZ> _vertices;
    std::vector<std::vector<int>> _faces;
    std::vector<Mesh::Edge> _edges;
};

}// namespace dwg

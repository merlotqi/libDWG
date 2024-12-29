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


class Mesh : public Entity
{
public:
    Mesh();
    virtual ~Mesh();

    short version;       // 71
    bool blendCrease;    // 72
    int subdivisionLevel;// 91

    std::vector<XYZ> vertices;// 92;10,20,30

    /// @brief 93, count
    /// 90
    std::vector<std::vector<int>> faces;

    struct Edge
    {
        int Start;
        int End;
        double Crease;

        Edge(int start, int end) : Start(start), End(end), Crease(0.0) {}
    };


    std::vector<Mesh::Edge> edges;// 94, 90

    //90	Count of sub-entity which property has been overridden

    //91	Sub-entity marker

    //92	Count of property was overridden

    //90	Property type
    //0 = Color
    //1 = Material
    //2 = Transparency
    //3 = Material mapper
};


}// namespace dwg

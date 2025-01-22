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
#include <dwg/entities/MLineFlags.h>
#include <dwg/entities/MLineJustification.h>
#include <dwg/entities/Vertex.h>
#include <dwg/objects/MLineStyle.h>

namespace dwg {

class MLine : public Entity
{

public:
    MLine();
    ~MLine();

    MLineStyle *mLineStyle;// handle | name 340

    double scaleFactor;              // 40
    MLineJustification justification;// 70
    MLineFlags flags;                // 71
    XYZ startPoint;                  // 10, 20, 30
    XYZ normal;                      // 210, 220, 230

    class Vertex
    {
    public:
        struct Segment
        {
            std::vector<double> parameters;        // count 74; 41
            std::vector<double> areaFillParameters;// count 75; 42
        };

        XYZ position;                 // 11, 21, 31
        XYZ direction;                // 12, 22, 32
        XYZ miter;                    // 13, 23, 33
        std::vector<Segment> segments;// count,73
    };

    std::vector<Vertex> vertices;// count,72
};

}// namespace dwg

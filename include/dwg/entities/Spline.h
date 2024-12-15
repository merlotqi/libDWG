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

#include <dwg/enums/entities/SplineFlags.h>
#include <dwg/enums/entities/KnotParameterization.h>

namespace dwg {
namespace entities {

class Spline : public Entity
{
public:
    Spline();
    virtual ~Spline();

    XYZ normal;// 210, 220, 230

    SplineFlags flags;// 70

    int degree;// 71

    std::vector<double> knots;     // 72|40
    std::vector<XYZ> controlPoints;// 73|10, 20, 30

    std::vector<XYZ> fitPoints;    // 74|11, 21, 31

    double knotTolerance;// 42
    double controlPointTolerance;// 43
    double fitTolerance;// 44

    XYZ startTangent;// 12, 22, 32
    XYZ endTangent;// 13, 23, 33

    std::vector<double> weights; // 41


    SplineFlags1 flags1;
    KnotParameterization knotParameterization;
};

}// namespace entities
}// namespace dwg

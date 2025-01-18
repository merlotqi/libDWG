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

#include <dwg/Color.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/HatchBoundaryPath.h>
#include <dwg/entities/HatchGradientPattern.h>
#include <dwg/entities/HatchPattern.h>
#include <dwg/entities/HatchPatternType.h>
#include <dwg/entities/HatchStyleType.h>



namespace dwg {

class Hatch : public Entity
{
public:
    Hatch();
    ~Hatch();

    double elevation;// 30
    XYZ normal;      // 210, 220, 230

    HatchPattern pattern;        // 2, name
    bool isSolid;                // 70
    bool isAssociative;          // 71
    HatchStyleType style;        // 75
    HatchPatternType patternType;// 76

    // 52
    double patternAngle() const { return pattern.angle; }
    void patternAngle(double angle) { pattern.angle = angle; }

    // 41
    double patternScale() const { return pattern.scale; }
    void patternScale(double scale) { pattern.scale = scale; }

    //73	For MPolygon, boundary annotation flag:
    //0 = boundary is not an annotated boundary
    //1 = boundary is an annotated boundary

    //78	Number of pattern definition lines
    //varies
    //Pattern line data.Repeats number of times specified by code 78. See Pattern Data

    // 77
    bool isDouble;

    double pixelSize;//47

    //11	For MPolygon, offset vector

    //99	For MPolygon, number of degenerate boundary paths(loops), where a degenerate boundary path is a border that is ignored by the hatch

    std::vector<XY> seedPoints;// 98 count, 10, 20

    // 470, name
    HatchGradientPattern gradientColor;


    std::vector<HatchBoundaryPath> paths;// 91 count
};


}// namespace dwg

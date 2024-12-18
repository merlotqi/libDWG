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
#include <dwg/enums/entities/LeaderCreationType.h>
#include <dwg/enums/entities/LeaderPathType.h>
#include <dwg/tables/DimensionStyle.h>


namespace dwg {
namespace entities {

class Leader : public Entity
{
public:
    Leader();
    virtual ~Leader();
    tables::DimensionStyle *style;  // 3 name
    bool arrowHeadEnabled;          // 71
    LeaderPathType pathType;        // 72
    LeaderCreationType creationType;// 73
    bool hookLineDirection;         // 74
    bool hasHookline;               // 75
    double textHeight;              // 40

    double textWidth;// 41

    std::vector<XYZ> vertices;// 76; 10,20,30
    //77	Color to use if leader's DIMCLRD = BYBLOCK


    Entity *AssociatedAnnotation;// 340 handle

    XYZ normal;             // 210, 220, 230
    XYZ horizontalDirection;// 211, 221, 231
    XYZ blockOffset;        // 212, 222, 232
    XYZ annotationOffset;   // 213, 223, 233
};

}// namespace entities
}// namespace dwg

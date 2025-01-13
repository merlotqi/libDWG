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
#include <dwg/entities/TextHorizontalAlignment.h>
#include <dwg/entities/TextMirrorFlag.h>
#include <dwg/entities/TextVerticalAlignmentType.h>


namespace dwg {


class TextEntity : public Entity, IText
{
public:
    TextEntity();
    virtual ~TextEntity();

    double thickness;// 39
    XYZ insertPoint; //10, 20, 30
    double height;   // 40

    // 1
    CPL::String value() const;
    void setValue(const CPL::String &value);

    double rotation;// 50

    double widthFactor; // 41, optional
    double obliqueAngle;// 51

    // 7 name
    TextEntity *style() const;
    void setStyle(TextEntity *style);


    TextMirrorFlag mirror;                      // 71
    TextHorizontalAlignment horizontalAlignment;// 72
    XYZ alignmentPoint;                         // 11, 21, 31
    XYZ normal;                                 //210, 220, 230
    TextVerticalAlignmentType verticalAlignment;// 73
};


}// namespace dwg

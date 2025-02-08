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
#include <dwg/objects/MLineStyleFlags.h>
#include <dwg/objects/NonGraphicalObject.h>

namespace dwg {

class LIBDWG_API MLineStyle : public NonGraphicalObject
{
public:
    MLineStyle();
    MLineStyle(const std::string &name);

    static constexpr auto DefaultName = "Standard";
    static MLineStyle Default;

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;


    // 70
    MLineStyleFlags Flags;
    std::string Description;         // 3
    Color FillColor = Color::ByLayer;// 62
    double StartAngle = M_PI / 2.0;  // 51
    double EndAngle = M_PI / 2.0;    // 52


    struct Element
    {
        double Offset;               // 49
        Color Color = Color::ByBlock;// 62
        LineType LineType = LineType::ByLayer;
    };

    std::vector<Element> Elements;// count 71
};

MLineStyle MLineStyle::Default = MLineStyle(MLineStyle::DefaultName);

}// namespace dwg
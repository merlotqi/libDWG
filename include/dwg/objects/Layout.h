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

#include <dwg/OrthographicType.h>
#include <dwg/objects/LayoutFlags.h>
#include <dwg/objects/PlotSettings.h>

namespace dwg {

class DG_Layout : public DG_PlotSettings
{
public:
    DG_Layout(const std::string &name,
              const std::string &blockName = std::string())
    {
    }

    static constexpr auto ModelLayoutName = "Model";
    static constexpr auto PaperLayoutName = "Layout1";

    DG_ObjectType ObjectType() const override;
    std::string ObjectName() const override;
    std::string SubclassMarker() const override;

    // 70
    LayoutFlags LayoutFlags;
    // 71
    int TabOrder;
    XY MinLimites = XY(-20.0, -7.5);        // 10, 20
    XY MaxLimits = XY(277.0, 202.5);        // 11, 21
    XYZ InsertionBasePoint;                 // 12, 22, 32
    XYZ MinExtents = XYZ(25.7, 19.5, 0.0);  // 14, 24, 34
    XYZ MaxExtents = XYZ(231.3, 175.5, 0.0);// 15, 25, 35
    double Elevation;                       // 146
    XYZ Origin = XYZ::Zero;                 // 13, 23, 33
    XYZ XAxis = XYZ::AxisX;                 // 16, 26, 36
    XYZ YAxis = XYZ::AxisY;                 // 17, 27, 37
    OrthographicType UcsOrthographicType;   // 76

    /// The associated paper space block table record.
    unsigned long long AssociatedBlockHandle;
    ;// 330
    /// Viewport that was last active in this layout when the layout was current.
    unsigned long long ViewportHandle;// 331
    /// UCS Table Record if UCS is a named UCS.
    unsigned long long USCHandle;    // 345
    unsigned long long BaseUSCHandle;// 346


    bool IsPaperSpace() const;
};

}// namespace dwg
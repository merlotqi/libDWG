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
#include <dwg/Coordinate.h>
#include <dwg/OrthographicType.h>
#include <dwg/RenderMode.h>
#include <dwg/tables/DefaultLightingType.h>
#include <dwg/tables/GridFlags.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/UscIconType.h>
#include <dwg/tables/ViewModeType.h>


namespace dwg {

class LIBDWG_API DG_VPort : public DG_TableEntry
{
public:
    DG_VPort();
    DG_VPort(const char *name);

    static constexpr auto DefaultName = "*Active";
    static CPL::SmarterPtr<DG_VPort> Default();

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;


    XY BottomLeft = XY::Zero;
    XY TopRight = XY(1, 1);
    XY Center = XY::Zero;
    XY SnapBasePoint;
    XY SnapSpacing = XY(0.5, 0.5);
    XY GridSpacing = XY(10, 10);
    XYZ Direction;

    XYZ Target = XYZ::Zero;
    double ViewHeight = 10;
    double AspectRatio = 1.0;
    double LensLength = 50.0;
    double FrontClippingPlane = 0.0;
    double BackClippingPlane;
    double SnapRotation;
    double TwistAngle;
    short CircleZoomPercent = 1000;
    DG_RenderMode RenderMode;
    DG_ViewModeType ViewMode;
    DG_UscIconType UcsIconDisplay;
    bool SnapOn;
    bool ShowGrid = true;
    bool IsometricSnap;
    short SnapIsoPair;
    XYZ Origin = XYZ::Zero;
    XYZ XAxis = XYZ::AxisX;
    XYZ YAxis = XYZ::AxisY;
    unsigned long long NamedUcsHandle;
    unsigned long long BaseUcsHandle;
    DG_OrthographicType OrthographicType;
    double Elevation;
    DG_GridFlags GridFlags;//= GridFlags._1 | GridFlags._2;
    short MinorGridLinesPerMajorGridLine = 5;
    unsigned long long VisualStyleHandle;
    bool UseDefaultLighting = true;
    DG_DefaultLightingType DefaultLighting;
    double Brightness;
    double Contrast;
    DG_Color AmbientColor;
};


class LIBDWG_API DG_VPortsTable : public DG_Table
{
public:
    DG_VPortsTable();

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;

protected:
    std::vector<CPL::String> defaultEntries() const override;
};

}// namespace dwg

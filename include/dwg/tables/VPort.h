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
#include <dwg/OrthographicType.h>
#include <dwg/RenderMode.h>
#include <dwg/base/Coordinate.h>
#include <dwg/tables/DefaultLightingType.h>
#include <dwg/tables/GridFlags.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/UscIconType.h>
#include <dwg/tables/ViewModeType.h>



namespace dwg {

class VPort : public TableEntry
{
public:
    VPort() {}
    VPort(const CPL::String &name) : TableEntry(name) {}

    static constexpr auto DefaultName = "*Active";
    static VPort Default;

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::VPORT;
    }
    CPL::String ObjectName() const override { return DxfFileToken::TableVport; }
    CPL::String SubclassMarker() const override
    {
        return DxfSubclassMarker::VPort;
    }


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
    RenderMode RenderMode = RenderMode::Optimized2D;
    ViewModeType ViewMode = ViewModeType::FrontClippingZ;
    UscIconType UcsIconDisplay = UscIconType::OnOrigin;
    bool SnapOn;
    bool ShowGrid = true;
    bool IsometricSnap;
    short SnapIsoPair;
    XYZ Origin = XYZ::Zero;
    XYZ XAxis = XYZ::AxisX;
    XYZ YAxis = XYZ::AxisY;
    unsigned long long NamedUcsHandle;
    unsigned long long BaseUcsHandle;
    OrthographicType OrthographicType = OrthographicType::None;
    double Elevation;
    GridFlags GridFlags;//= GridFlags._1 | GridFlags._2;
    short MinorGridLinesPerMajorGridLine = 5;
    unsigned long long VisualStyleHandle;
    bool UseDefaultLighting = true;
    DefaultLightingType DefaultLighting = DefaultLightingType::TwoDistantLights;
    double Brightness;
    double Contrast;
    Color AmbientColor;
};

VPort VPort::Default = VPort(VPort::DefaultName);


class VPortsTable : public Table<VPort>
{
public:
    VPortsTable() = default;

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::VPORT_CONTROL_OBJ;
    }
    CPL::String ObjectName() const override { return DxfFileToken::TableVport; }

protected:
    std::vector<CPL::String> defaultEntries() const
    {
        return {VPort::DefaultName};
    }
};

}// namespace dwg

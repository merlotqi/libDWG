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

    XY BottomLeft() const;
    void BottomLeft(const XY &);

    XY TopRight() const;
    void TopRight(const XY &);

    XY Center() const;
    void Center(const XY &);

    XY SnapBasePoint() const;
    void SnapBasePoint(const XY &);

    XY SnapSpacing() const;
    void SnapSpacing(const XY &);

    XY GridSpacing() const;
    void GridSpacing(const XY &);

    XYZ Direction() const;
    void Direction(const XYZ &);

    XYZ Target() const;
    void Target(const XYZ &);

    double ViewHeight() const;
    void ViewHeight(double);

    double AspectRatio() const;
    void AspectRatio(double);

    double LensLength() const;
    void LensLength(double);

    double FrontClippingPlane() const;
    void FrontClippingPlane(double);

    double BackClippingPlane() const;
    void BackClippingPlane(double);

    double SnapRotation() const;
    void SnapRotation(double);

    double TwistAngle() const;
    void TwistAngle(double);

    short CircleZoomPercent() const;
    void CircleZoomPercent(short);

    DG_RenderMode RenderMode() const;
    void RenderMode(DG_RenderMode);

    DG_ViewModeType ViewMode() const;
    void ViewMode(DG_ViewModeType);

    DG_UscIconType UcsIconDisplay() const;
    void UcsIconDisplay(DG_UscIconType);

    bool SnapOn() const;
    void SnapOn(bool);

    bool ShowGrid() const;
    void ShowGrid(bool);

    bool IsometricSnap() const;
    void IsometricSnap(bool);

    short SnapIsoPair() const;
    void SnapIsoPair(short);

    XYZ Origin() const;
    void Origin(const XYZ &);

    XYZ XAxis() const;
    void XAxis(const XYZ &);

    XYZ YAxis() const;
    void YAxis(const XYZ &);

    DG_UCSPtr NamedUcs() const;
    void NamedUcs(DG_UCS *);

    DG_UCSPtr BaseUcs() const;
    void BaseUcs(BaseUcs *);
    
    DG_OrthographicType OrthographicType() const;
    void OrthographicType(DG_OrthographicType);

    double Elevation() const;
    void Elevation(double);

    DG_GridFlags GridFlags() const;
    void GridFlags(DG_GridFlags);
    
    short MinorGridLinesPerMajorGridLine() const;
    void MinorGridLinesPerMajorGridLine(short);

    DG_VisualStylePtr VisualStyle() const;
    void VisualStyle(DG_VisualStyle *);
    
    bool UseDefaultLighting() const;
    void UseDefaultLighting(bool);

    DG_DefaultLightingType DefaultLighting() const;
    void DefaultLighting(DG_DefaultLightingType);

    double Brightness() const;
    void Brightness(double);

    double Contrast() const;
    void Contrast(double);

    DG_Color AmbientColor() const;
    void AmbientColor(const DG_Color &);
};
CPL_SMARTER_PTR(DG_VPort)


class LIBDWG_API DG_VPortsTable : public DG_Table
{
public:
    DG_VPortsTable();

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;

protected:
    std::vector<CPL::String> defaultEntries() const override;
};
CPL_SMARTER_PTR(DG_VPortsTable)

}// namespace dwg

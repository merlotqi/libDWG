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

#include <dwg/Coordinate.h>
#include <dwg/OrthographicType.h>
#include <dwg/RenderMode.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/ViewModeType.h>

namespace dwg {

class LIBDWG_API DG_View : public DG_TableEntry
{
public:
    DG_View() = default;

    DG_View(const std::string &name);

    DG_ObjectType ObjectType() const override;

    std::string ObjectName() const override;

    std::string SubclassMarker() const override;

    double Height() const;
    void Height(double);

    double Width() const;
    void Width(double);

    double LensLength() const;
    void LensLength(double);

    double FrontClipping() const;
    void FrontClipping(double);

    double BackClipping() const;
    void BackClipping(double);

    double Angle() const;
    void Angle(double);

    DG_ViewModeType ViewMode() const;
    void ViewMode(DG_ViewModeType);

    bool IsUcsAssociated() const;
    void IsUcsAssociated(bool);

    bool IsPlottable() const;
    void IsPlottable(bool);

    DG_RenderMode RenderMode() const;
    void RenderMode(DG_RenderMode);

    XY Center() const;
    void Center(const XY &);

    XYZ Direction() const;
    void Direction(const XYZ &);

    XYZ Target() const;
    void Target(const XYZ &);

    DG_VisualStyle *VisualStyle() const;
    void VisualStyle(DG_VisualStyle *);

    XYZ UcsOrigin() const;
    void UcsOrigin(const XYZ &);

    XYZ UcsXAxis() const;
    void UcsXAxis(const XYZ &);

    XYZ UcsYAxis() const;
    void UcsYAxis(const XYZ &);

    double UcsElevation() const;
    void UcsElevation(double);

    DG_OrthographicType UcsOrthographicType() const;
    void UcsOrthographicType(DG_OrthographicType);
};

class LIBDWG_API DG_ViewsTable : public DG_Table
{
public:
    DG_ViewsTable() = default;
    DG_ObjectType ObjectType() const override;
    std::string ObjectName() const override;

protected:
    std::vector<std::string> defaultEntries() const override;
};

}// namespace dwg
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
    DG_View(const char *name);
    double Height;
    double Width;
    double LensLength;
    double FrontClipping;
    double BackClipping;
    double Angle;
    DG_ViewModeType ViewMode;
    bool IsUcsAssociated = false;
    bool IsPlottable;
    DG_RenderMode RenderMode;

    XY Center;
    XYZ Direction;
    XYZ Target;

    unsigned long long VisualStyleHandle;

    XYZ UcsOrigin;
    XYZ UcsXAxis;
    XYZ UcsYAxis;
    double UcsElevation;

    DG_OrthographicType UcsOrthographicType;
};

class LIBDWG_API DG_ViewsTable : public DG_Table
{
public:
    DG_ViewsTable() = default;
    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;

protected:
    std::vector<CPL::String> defaultEntries() const override;
};

}// namespace dwg
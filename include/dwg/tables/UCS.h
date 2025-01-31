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
#include <dwg/tables/TableEntry.h>

namespace dwg {

class LIBDWG_API DG_UCS : public DG_TableEntry
{
public:
    DG_UCS();

    DG_UCS(const std::string &name);

    DG_ObjectType ObjectType() const override;

    std::string ObjectName() const override;

    std::string SubclassMarker() const override;

    XYZ Origin() const;

    void Origin(const XYZ &);

    XYZ XAxis() const;

    void XAxis(const XYZ &);

    XYZ YAxis() const;

    void YAxis(const XYZ &);

    DG_OrthographicType OrthographicType() const;

    void OrthographicType(DG_OrthographicType);

    DG_OrthographicType OrthographicViewType() const;

    void OrthographicViewType(DG_OrthographicType);

    double Elevation() const;

    void Elevation(double);
};

class LIBDWG_API DG_UCSTable : public DG_Table
{
public:
    DG_UCSTable() = default;

    DG_ObjectType ObjectType() const override;

    std::string ObjectName() const override;

protected:
    std::vector<std::string> defaultEntries() const override;
};

}// namespace dwg
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

#include <dwg/tables/TableEntry.h>

namespace dwg {

class UCS : public TableEntry
{
public:
    UCS() {}
    UCS(const std::string &name) : TableEntry(name) {}

    dwg::ObjectType ObjectType() const override { return dwg::ObjectType::UCS; }
    std::string ObjectName() const override { return DxfFileToken::TableUcs; }
    std::string SubclassMarker() const override
    {
        return DxfSubclassMarker::Ucs;
    }

    XYZ Origin = XYZ::Zero;
    XYZ XAxis = XYZ::AxisX;
    XYZ YAxis = XYZ::AxisY;
    OrthographicType orthographicType;
    OrthographicType OrthographicViewType;
    double Elevation;
};

class UCSTable : public Table<UCS>
{
public:
    UCSTable() = default;
    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::UCS_CONTROL_OBJ;
    }
    std::string ObjectName() const override { return DxfFileToken::TableUcs; }

protected:
    std::vector<std::string> defaultEntries() const
    {
        return std::vector<std::string>();
    }
};

}// namespace dwg
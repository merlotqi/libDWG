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

#include <dwg/enums/LineweightType.h>
#include <dwg/enums/tables/LayerFlags.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/utils/Color.h>


namespace dwg {
namespace tables {


class Layer : public TableEntry
{
public:
    static constexpr auto DefaultName = "0";
    static Layer Default;

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::LAYER;
    }
    std::string ObjectName() const override { return DxfFileToken::TableLayer; }
    std::string SubclassMarker() const override
    {
        return DxfSubclassMarker::Layer;
    }

    LayerFlags Flags;
    Color color;                     // 62, 420, 430
    std::string LineTypeName;        // linetype Name
    LineType lineType;               // 6
    bool PlotFlag;                   // 200
    unsigned long long PlotStyleName;// 390
    // Material* material; // 347 handle
    bool IsOn;// Indicates if the Layer is visible in the model

    Layer() = default;
    Layer(const std::string &name) : TableEntry(name) {}
};

class LayersTable : public Table<Layer>
{
public:
    LayersTable() = default;
    std::string ObjectName() const { return DxfFileToken::TableLayer; }

public:
    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::APPID_CONTROL_OBJ;
    }

protected:
    std::vector<std::string> defaultEntries() const
    {
        return {Layer::DefaultName};
    }
};

}// namespace tables
}// namespace dwg
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

#include <dwg/tables/LinetypeShapeFlags.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/TextStyle.h>


namespace dwg {


class LineType : public TableEntry
{
public:
    LineType() = default;
    LineType(const CPL::String &name) : TableEntry(name) {}

    struct Segment
    {
        double Length;// 49
        LinetypeShapeFlags ShapeFlag;
        short ShapeNumber;
        XY Offset;
        double Rotation;
        double Scale;
        CPL::String Text;
        TextStyle Style;
    };

    static constexpr auto ByLayerName = "ByLayer";
    static constexpr auto ByBlockName = "ByBlock";
    static constexpr auto ContinuousName = "Continuous";

    static LineType ByLayer;
    static LineType ByBlock;
    static LineType Continuous;

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::LTYPE;
    }
    CPL::String ObjectName() const override
    {
        return DxfFileToken::TableLinetype;
    }
    CPL::String SubclassMarker() const override
    {
        return DxfSubclassMarker::Linetype;
    }

    CPL::String Description;  // 3
    double PatternLen() const;// 40
    char Alignment = 'A';     // 72

    void AddSegment(const Segment &segmnnt);

private:
    std::vector<Segment> _segments;
};

class LineTypesTable : public Table<LineType>
{
public:
    LineType ByLayer;
    LineType ByBlock;
    LineType Continuous;

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::APPID_CONTROL_OBJ;
    }

    LineTypesTable() = default;

protected:
    std::vector<CPL::String> defaultEntries() const
    {
        return {LineType::ByLayerName, LineType::ByBlockName,
                LineType::ContinuousName};
    }
};

}// namespace dwg

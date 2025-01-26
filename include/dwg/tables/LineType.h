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
#include <dwg/tables/LinetypeShapeFlags.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/TextStyle.h>


namespace dwg {

class DG_TextStyle;
CPL_SMARTER_PTR(DG_TextStyle)

class LIBDWG_API DG_LineType : public DG_TableEntry
{
public:
    struct Segment
    {
        double Length;
        DG_LinetypeShapeFlags ShapeFlag;
        short ShapeNumber;
        XY Offset;
        double Rotation;
        double Scale;
        CPL::String Text;
        DG_TextStyleWPtr Style;
    };

public:
    DG_LineType();

    DG_LineType(const char *name);

    static constexpr auto ByLayerName = "ByLayer";

    static constexpr auto ByBlockName = "ByBlock";

    static constexpr auto ContinuousName = "Continuous";

    static CPL::SmarterPtr<DG_LineType> ByLayer();

    static CPL::SmarterPtr<DG_LineType> ByBlock();

    static CPL::SmarterPtr<DG_LineType> Continuous();

    DG_ObjectType ObjectType() const override;
    
    CPL::String ObjectName() const override;

    CPL::String SubclassMarker() const override;

    CPL::String Description() const;

    void Description(const char *);

    double PatternLen() const;

    char Alignment() const;

    void Alignment(char);

    std::vector<Segment> Segments() const;

    void Segments(const std::vector<Segment> &);

    void AddSegment(const Segment &);
};
CPL_SMARTER_PTR(DG_LineType)

class LIBDWG_API DG_LineTypesTable : public DG_Table
{
public:
    CPL::SmarterPtr<DG_LineType> ByLayer;
    CPL::SmarterPtr<DG_LineType> ByBlock;
    CPL::SmarterPtr<DG_LineType> Continuous;

    DG_ObjectType ObjectType() const override;

    DG_LineTypesTable() = default;

protected:
    std::vector<CPL::String> defaultEntries() const;
};

}// namespace dwg

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

#include <dwg/entities/TextMirrorFlag.h>
#include <dwg/tables/FontFlags.h>
#include <dwg/tables/StyleFlags.h>
#include <dwg/tables/TableEntry.h>

namespace dwg {

class LIBDWG_API TextStyle : public TableEntry
{
public:
    static constexpr auto DefaultName = "Standard";
    static TextStyle Default;

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::STYLE;
    }
    CPL::String ObjectName() const override { return DxfFileToken::TableStyle; }
    CPL::String SubclassMarker() const override
    {
        return DxfSubclassMarker::TextStyle;
    }

    bool IsShapeFile() const { return false; }

    virtual CPL::String Name() const
    {
        if (IsShapeFile()) return Filename;
        else
            return _name;
    }
    virtual void Name(const CPL::String &value)
    {
        _name = value;
        if (IsShapeFile()) Filename = value;
    }

    StyleFlags Flags;

    CPL::String Filename;       // 3
    CPL::String BigFontFilename;// 4
    double Height;              // 40
    double Width = 1.0;         // 41

    double LastHeight;        // 42
    double ObliqueAngle = 0.0;// 50
    TextMirrorFlag MirrorFlag = TextMirrorFlag::None;
    FontFlags TrueType = FontFlag::Regular;

    TextStyle() {}
    TextStyle(const CPL::String &name) : TableEntry(name) {}
};

TextStyle TextStyle::Default = TextStyle(TextStyle::DefaultName);

class LIBDWG_API TextStylesTable : public Table
{
public:
    TextStylesTable() = default;
    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::APPID_CONTROL_OBJ;
    }

protected:
    std::vector<CPL::String> defaultEntries() const
    {
        return {TextStyle::DefaultName};
    }
};

}// namespace dwg

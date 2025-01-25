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

class LIBDWG_API DG_TextStyle : public DG_TableEntry
{
public:
    static constexpr auto DefaultName = "Standard";
    static DG_TextStyle Default;

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;
    bool IsShapeFile() const;
    virtual CPL::String Name() const;
    virtual void Name(const char *value);

    DG_StyleFlags Flags;

    CPL::String Filename;       // 3
    CPL::String BigFontFilename;// 4
    double Height;              // 40
    double Width = 1.0;         // 41

    double LastHeight;        // 42
    double ObliqueAngle = 0.0;// 50
    DG_TextMirrorFlag MirrorFlag;
    DG_FontFlags TrueType;

    DG_TextStyle() {}
    DG_TextStyle(const char *name);
};


class LIBDWG_API DG_TextStylesTable : public DG_Table
{
public:
    DG_TextStylesTable() = default;
    DG_ObjectType ObjectType() const override;

protected:
    std::vector<CPL::String> defaultEntries() const;
};

}// namespace dwg

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
    DG_TextStyle();

    DG_TextStyle(const char *);

    ~DG_TextStyle();

    static constexpr auto DefaultName = "Standard";

    static CPL::SmarterPtr<DG_TextStyle> Default();

    DG_ObjectType ObjectType() const override;

    CPL::String ObjectName() const override;

    CPL::String SubclassMarker() const override;

    DG_StyleFlags Flags() const;

    void Flags(DG_StyleFlags);

    CPL::String Filename() const;
    
    void Filename(const char *);

    CPL::String BigFontFilename() const;

    void BigFontFilename(const char *);
    
    double Height() const;

    void Height(double);

    double Width() const;

    void Width(double);

    double LastHeight() const;

    void LastHeight(double);

    double ObliqueAngle() const;

    void ObliqueAngle(double);

    DG_TextMirrorFlag MirrorFlag() const;

    void MirrorFlag(DG_TextMirrorFlag);

    DG_FontFlags TrueType() const;

    void TrueType(DG_FontFlags);

    bool IsShapeFile() const;
};
CPL_SMARTER_PTR(DG_TextStyle)

class LIBDWG_API DG_TextStylesTable : public DG_Table
{
public:
    DG_TextStylesTable() = default;
    DG_ObjectType ObjectType() const override;

protected:
    std::vector<CPL::String> defaultEntries() const;
};

}// namespace dwg

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
namespace tables {

/// Represent the font character formatting, such as italic, bold, or regular.
enum FontFlags
{
    /// Regular.
    Regular = 0,
    /// Italic or oblique.
    Italic = 1,
    /// Bold.
    Bold = 2
};

/// Standard layer flags (bit-coded values).
enum StyleFlags
{
    /// Default
    None = 0,
    /// If set, this entry describes a shape
    IsShape = 1,
    /// Vertical text
    VerticalText = 4,
    /// If set, table entry is externally dependent on an xRef.
    XrefDependent = 16,
    /// If both this bit and bit 16 are set, the externally dependent xRef has
    /// been successfully resolved.
    XrefResolved = 32,
    /// If set, the table entry was referenced by at least one entity in the
    /// drawing the last time the drawing was edited.
    Referenced = 64
};

class TextStyle : public TableEntry
{
};

class TextStylesTable : public Table<TextStyle>
{
};

}// namespace tables
}// namespace dwg

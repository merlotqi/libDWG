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

#include <dwg/DxfFileToken_p.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/collections/TextStylesTable.h>


namespace dwg {

TextStylesTable::TextStylesTable() {}

TextStylesTable::TextStylesTable(CadDocument *document) : TableCollection(document) {}

TextStylesTable::~TextStylesTable() {}

ObjectType TextStylesTable::objectType() const
{
    return ObjectType::STYLE_CONTROL_OBJ;
}

std::string TextStylesTable::objectName() const
{
    return DxfFileToken::TableStyle;
}

std::vector<std::string> TextStylesTable::defaultEntries() const
{
    return {TextStyle::DefaultName};
}

bool TextStylesTable::assertType(TableEntry *item) const
{
    if (!item)
        return false;

    auto text = dynamic_cast<TextStyle *>(item);
    return text ? true : false;
}

TableEntry *TextStylesTable::createEntry(const std::string &name)
{
    return new TextStyle(name);
}

}// namespace dwg
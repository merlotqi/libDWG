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
#include <dwg/tables/UCS.h>
#include <dwg/tables/collections/UCSTable.h>

namespace dwg {

UCSTable::UCSTable() {}

UCSTable::UCSTable(CadDocument *document) : Table(document) {}

UCSTable::~UCSTable() {}

ObjectType UCSTable::objectType() const
{
    return ObjectType::UCS_CONTROL_OBJ;
}

std::string UCSTable::objectName() const
{
    return DxfFileToken::TableUcs;
}

std::vector<std::string> UCSTable::defaultEntries() const
{
    return std::vector<std::string>();
}

TableEntry *UCSTable::createEntry(const std::string &name)
{
    return new UCS(name);
}

}// namespace dwg
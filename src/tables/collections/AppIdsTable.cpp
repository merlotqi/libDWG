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
#include <dwg/tables/AppId.h>
#include <dwg/tables/collections/AppIdsTable.h>

namespace dwg {

AppIdsTable::AppIdsTable() {}

AppIdsTable::AppIdsTable(CadDocument *document) : TableCollection(document) {}

AppIdsTable::~AppIdsTable() {}

ObjectType AppIdsTable::objectType() const
{
    return ObjectType::APPID_CONTROL_OBJ;
}

std::string AppIdsTable::objectName() const
{
    return DxfFileToken::TableAppId;
}

std::vector<std::string> AppIdsTable::defaultEntries() const
{
    return {AppId::DefaultName};
}

bool AppIdsTable::assertType(TableEntry *item) const
{
    if (!item)
        return false;

    auto appid = dynamic_cast<AppId *>(item);
    return appid ? true : false;
}

TableEntry *AppIdsTable::createEntry(const std::string &name)
{
    return new AppId(name);
}

}// namespace dwg
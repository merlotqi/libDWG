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
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/tables/AppId.h>
#include <stdexcept>


namespace dwg {

/* ----------------------------- AppId impls ----------------------------- */

std::string AppId::DefaultName = "libDWG";

AppId::AppId(const std::string &name) : TableEntry(name)
{
    if (name.empty())
        throw new std::invalid_argument("Application id must have a name.");
}

AppId::~AppId() {}

ObjectType AppId::objectType() const { return ObjectType::APPID; }

std::string AppId::objectName() const { return DxfFileToken::TableAppId; }

std::string AppId::subclassMarker() const { return DxfSubclassMarker::ApplicationId; }

AppId *AppId::Default() { return new AppId(DefaultName); }

/* -------------------------- AppIdsTable impls -------------------------- */

AppIdsTable::AppIdsTable() {}

ObjectType AppIdsTable::objectType() const { return ObjectType::APPID_CONTROL_OBJ; }

std::string AppIdsTable::objectName() const { return DxfFileToken::TableAppId; }

std::vector<std::string> AppIdsTable::defaultEntries() const { return {AppId::DefaultName}; }

}// namespace dwg
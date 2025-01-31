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

#include <dwg/tables/AppId.h>
#include <stdexcept>

namespace dwg {

/* ----------------------------- DG_AppId impls ----------------------------- */

std::string DG_AppId::DefaultName = "libDWG";

DG_AppId::DG_AppId(const std::string &name) : DG_TableEntry(name)
{
    if (CPL::StringHelp::IsNullOrEmpty(name.c_str()))
        throw new std::invalid_argument("Application id must have a name.");
}

DG_AppId::~DG_AppId() {}

DG_ObjectType DG_AppId::ObjectType() const { return DG_ObjectType::APPID; }

std::string DG_AppId::ObjectName() const { return DG_DxfFileToken::TableAppId; }

std::string DG_AppId::SubclassMarker() const
{
    return DG_DxfSubclassMarker::ApplicationId;
}

DG_AppId *DG_AppId::Default() { return new DG_AppId(DefaultName); }

/* -------------------------- DG_AppIdsTable impls -------------------------- */

DG_AppIdsTable::DG_AppIdsTable() {}

DG_ObjectType DG_AppIdsTable::ObjectType() const
{
    return DG_ObjectType::APPID_CONTROL_OBJ;
}

std::string DG_AppIdsTable::ObjectName() const
{
    return DG_DxfFileToken::TableAppId;
}

std::vector<std::string> DG_AppIdsTable::defaultEntries() const
{
    return {DG_AppId::DefaultName};
}

}// namespace dwg
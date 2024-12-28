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

#include <dwg/CadDocument.h>
#include <dwg/enums/ACadVersion.h>
#include <dwg/enums/classes/ProxyFlags.h>
#include <dwg/exports.h>
#include <map>
#include <string>

namespace dwg {

class LIBDWG_API DxfClass
{
public:
    std::string DxfName;
    std::string CppClassName;
    std::string ApplicationName = "ObjectDBX Classes";
    dwg::classes::ProxyFlags proxyFlags;
    int InstanceCount;
    bool WasZombie;
    bool IsAnEntity;
    short ClassNumber;
    short ItemClassId;
    ACadVersion DwgVersion;
    short MaintenanceVersion;


    DxfClass(const std::string &_cppClassName, short _classNumber,
             ACadVersion _version, const std::string &_dxfName,
             short _itemClassId, short _maintenanceVersion,
             classes::ProxyFlags _proxyFlags, bool _wasZombie);

    DxfClass(const std::string &_applicationName,
             const std::string &_cppClassName, short _classNumber,
             ACadVersion _version, const std::string &_dxfName,
             short _itemClassId, short _maintenanceVersion,
             classes::ProxyFlags _proxyFlags, bool _wasZombie);
};

class LIBDWG_API DxfClassCollection
{
    std::map<std::string, DxfClass> _entries;

public:
    DxfClassCollection() = default;
    static void UpdateDxfClasses(CadDocument *doc);
    void AddOrUpdate(DxfClass item);
    size_t Count() const;
};

}// namespace dwg
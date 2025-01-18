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

#include <dwg/ACadVersion.h>
#include <dwg/CadDocument.h>
#include <dwg/classes/ProxyFlags.h>
#include <dwg/exports.h>
#include <map>



namespace dwg {

class LIBDWG_API DxfClass
{
public:
    CPL::String DxfName;
    CPL::String CppClassName;
    CPL::String ApplicationName = "ObjectDBX Classes";
    dwg::ProxyFlags proxyFlags;
    int InstanceCount;
    bool WasZombie;
    bool IsAnEntity;
    short ClassNumber;
    short ItemClassId;
    ACadVersion DwgVersion;
    short MaintenanceVersion;


    DxfClass(const CPL::String &_cppClassName, short _classNumber,
             ACadVersion _version, const CPL::String &_dxfName,
             short _itemClassId, short _maintenanceVersion,
             ProxyFlags _proxyFlags, bool _wasZombie);

    DxfClass(const CPL::String &_applicationName,
             const CPL::String &_cppClassName, short _classNumber,
             ACadVersion _version, const CPL::String &_dxfName,
             short _itemClassId, short _maintenanceVersion,
             ProxyFlags _proxyFlags, bool _wasZombie);
};

class LIBDWG_API DxfClassCollection
{
    std::map<CPL::String, DxfClass> _entries;

public:
    DxfClassCollection() = default;
    static void UpdateDxfClasses(CadDocument *doc);
    void AddOrUpdate(DxfClass item);
    size_t Count() const;
};

}// namespace dwg
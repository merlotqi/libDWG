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
#include <dwg/classes/ProxyFlags.h>
#include <dwg/exports.h>
#include <string>

namespace dwg {

class LIBDWG_API DxfClass
{
public:
    DxfClass();
    DxfClass(const std::string &cppClassName, short classNumber, ACadVersion version, const std::string &dxfName,
             short itemClassId, short maintenanceVersion, ProxyFlags proxyFlags, bool wasZombie);
    DxfClass(const std::string &applicationName, const std::string &cppClassName, short classNumber,
             ACadVersion version, const std::string &dxfName, short itemClassId, short maintenanceVersion,
             ProxyFlags proxyFlags, bool wasZombie);

    std::string dxfName() const;
    void setDxfName(const std::string &dxfName);

    std::string cppClassName() const;
    void setCppClassName(const std::string &name);

    std::string applicationName() const;
    void setApplicationName(const std::string &applicationName);

    ProxyFlags proxyFlags() const;
    void setProxyFlags(ProxyFlags proxyFlags);

    int instanceCount() const;
    void setInstanceCount(int instanceCount);

    bool wasZombie() const;
    void setWasZombie(bool wasZombie);

    bool isAnEntity() const;
    void setIsAnEntity(bool isAnEntity);

    short classNumber() const;
    void setClassNumber(short classNumber);

    short itemClassId() const;
    void setItemClassId(short itemClassId);

    ACadVersion dwgVersion() const;
    void setDwgVersion(ACadVersion dwgVersion);

    short maintenanceVersion() const;
    void setMaintenanceVersion(short maintenanceVersion);

private:
    std::string _dxfName;
    std::string _cppClassName;
    std::string _applicationName;
    ProxyFlags _proxyFlags;
    int _instanceCount;
    bool _wasZombie;
    bool _isAnEntity;
    short _classNumber;
    short _itemClassId;
    ACadVersion _dwgVersion;
    short _maintenanceVersion;
};

}// namespace dwg
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

#include <dwg/classes/DxfClass.h>

namespace dwg {

/* -------------------------------- DxfClass -------------------------------- */

DxfClass::DxfClass() {}

DxfClass::DxfClass(const std::string &cppClassName, short classNumber, ACadVersion version, const std::string &dxfName,
                   short itemClassId, short maintenanceVersion, ProxyFlags proxyFlags, bool wasZombie)
{
    _cppClassName = cppClassName;
    _classNumber = classNumber;
    _dwgVersion = version;
    _dxfName = dxfName;
    _itemClassId = itemClassId;
    _maintenanceVersion = maintenanceVersion;
    _proxyFlags = proxyFlags;
    _wasZombie = wasZombie;
}

DxfClass::DxfClass(const std::string &applicationName, const std::string &cppClassName, short classNumber,
                   ACadVersion version, const std::string &dxfName, short itemClassId, short maintenanceVersion,
                   ProxyFlags proxyFlags, bool wasZombie)
{
    _cppClassName = cppClassName;
    _classNumber = classNumber;
    _dwgVersion = version;
    _dxfName = dxfName;
    _itemClassId = itemClassId;
    _maintenanceVersion = maintenanceVersion;
    proxyFlags = proxyFlags;
    _wasZombie = wasZombie;
}

std::string DxfClass::dxfName() const
{
    return _dxfName;
}

void DxfClass::setDxfName(const std::string &dxfName)
{
    _dxfName = dxfName;
}

std::string DxfClass::cppClassName() const
{
    return _cppClassName;
}

void DxfClass::setCppClassName(const std::string &className)
{
    _cppClassName = className;
}

std::string DxfClass::applicationName() const
{
    return _applicationName;
}

void DxfClass::setApplicationName(const std::string &applicationName)
{
    _applicationName = applicationName;
}

ProxyFlags DxfClass::proxyFlags() const
{
    return _proxyFlags;
}

void DxfClass::setProxyFlags(ProxyFlags proxyFlags)
{
    _proxyFlags = proxyFlags;
}

int DxfClass::instanceCount() const
{
    return _instanceCount;
}

void DxfClass::setInstanceCount(int instanceCount)
{
    _instanceCount = instanceCount;
}

bool DxfClass::wasZombie() const
{
    return _wasZombie;
}

void DxfClass::setWasZombie(bool wasZombie)
{
    _wasZombie = wasZombie;
}

bool DxfClass::isAnEntity() const
{
    return _isAnEntity;
}

void DxfClass::setIsAnEntity(bool isAnEntity)
{
    _isAnEntity = isAnEntity;
}

short DxfClass::classNumber() const
{
    return _classNumber;
}

void DxfClass::setClassNumber(short classNumber)
{
    _classNumber = classNumber;
}

short DxfClass::itemClassId() const
{
    return _itemClassId;
}

void DxfClass::setItemClassId(short itemClassId)
{
    _itemClassId = itemClassId;
}

ACadVersion DxfClass::dwgVersion() const
{
    return _dwgVersion;
}

void DxfClass::setDwgVersion(ACadVersion dwgVersion)
{
    _dwgVersion = dwgVersion;
}

short DxfClass::maintenanceVersion() const
{
    return _maintenanceVersion;
}

void DxfClass::setMaintenanceVersion(short maintenanceVersion)
{
    _maintenanceVersion = maintenanceVersion;
}

}// namespace dwg
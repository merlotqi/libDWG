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

#include <cpl_ports.h>
#include <dwg/ACadVersion.h>
#include <dwg/classes/ProxyFlags.h>
#include <dwg/exports.h>

namespace dwg {

/**
 * @class DG_DxfClass
 * @brief Represents a DXF class definition in a DWG/DXF drawing.
 *
 * DG_DxfClass encapsulates information related to a specific DXF class,
 * including its name, version, and various attributes like proxy flags, class number, 
 * and maintenance version. It is used to define the properties and behavior of
 * custom entities in AutoCAD or similar CAD applications that support DXF format.
 */
class LIBDWG_API DG_DxfClass
{
public:
    /**
     * @brief Constructs a DG_DxfClass with the specified parameters.
     * 
     * @param _cppClassName The C++ class name.
     * @param _classNumber The class number.
     * @param _version The AutoCAD version.
     * @param _dxfName The DXF name associated with this class.
     * @param _itemClassId The item class identifier.
     * @param _maintenanceVersion The maintenance version.
     * @param _proxyFlags Flags representing proxy status.
     * @param _wasZombie Whether the class was previously a zombie object.
     */
    DG_DxfClass(const std::string &_cppClassName, short _classNumber,
                DG_ACadVersion _version, const std::string &_dxfName,
                short _itemClassId, short _maintenanceVersion,
                DG_ProxyFlags _proxyFlags, bool _wasZombie);

    /**
     * @brief Constructs a DG_DxfClass for a specific application.
     * 
     * @param _applicationName The name of the application.
     * @param _cppClassName The C++ class name.
     * @param _classNumber The class number.
     * @param _version The AutoCAD version.
     * @param _dxfName The DXF name associated with this class.
     * @param _itemClassId The item class identifier.
     * @param _maintenanceVersion The maintenance version.
     * @param _proxyFlags Flags representing proxy status.
     * @param _wasZombie Whether the class was previously a zombie object.
     */
    DG_DxfClass(const std::string &_applicationName,
                const std::string &_cppClassName, short _classNumber,
                DG_ACadVersion _version, const std::string &_dxfName,
                short _itemClassId, short _maintenanceVersion,
                DG_ProxyFlags _proxyFlags, bool _wasZombie);

    /**
     * @brief Gets the DXF name of this class.
     * 
     * @return The DXF name.
     */
    std::string DxfName() const;

    /**
     * @brief Sets the DXF name of this class.
     * 
     * @param _dxfName The new DXF name.
     */
    void DxfName(const std::string &_dxfName);

    /**
     * @brief Gets the C++ class name.
     * 
     * @return The C++ class name.
     */
    std::string ClassName() const;

    /**
     * @brief Sets the C++ class name.
     * 
     * @param _className The new C++ class name.
     */
    void ClassName(const std::string &_className);

    /**
     * @brief Gets the application name associated with this class.
     * 
     * @return The application name.
     */
    std::string ApplicationName() const;

    /**
     * @brief Sets the application name associated with this class.
     * 
     * @param _applicationName The new application name.
     */
    void ApplicationName(const std::string &_applicationName);

    /**
     * @brief Gets the proxy flags for this class.
     * 
     * @return The proxy flags.
     */
    DG_ProxyFlags proxyFlags() const;

    /**
     * @brief Sets the proxy flags for this class.
     * 
     * @param _proxyFlags The new proxy flags.
     */
    void proxyFlags(DG_ProxyFlags _proxyFlags);

    /**
     * @brief Gets the instance count of this class.
     * 
     * @return The instance count.
     */
    int InstanceCount() const;

    /**
     * @brief Sets the instance count of this class.
     * 
     * @param _instanceCount The new instance count.
     */
    void InstanceCount(int _instanceCount);

    /**
     * @brief Checks if this class was a zombie object.
     * 
     * @return True if the class was a zombie, false otherwise.
     */
    bool WasZombie() const;

    /**
     * @brief Sets the zombie status for this class.
     * 
     * @param _wasZombie True if the class was a zombie object.
     */
    void WasZombie(bool _wasZombie);

    /**
     * @brief Checks if this class is an entity.
     * 
     * @return True if the class is an entity, false otherwise.
     */
    bool IsAnEntity() const;

    /**
     * @brief Sets whether this class is an entity.
     * 
     * @param _isAnEntity True if the class is an entity, false otherwise.
     */
    void IsAnEntity(bool _isAnEntity) const;

    /**
     * @brief Gets the class number of this class.
     * 
     * @return The class number.
     */
    short ClassNumber() const;

    /**
     * @brief Sets the class number for this class.
     * 
     * @param _classNumber The new class number.
     */
    void ClassNumber(short _classNumber);

    /**
     * @brief Gets the item class identifier.
     * 
     * @return The item class identifier.
     */
    short ItemClassId() const;

    /**
     * @brief Sets the item class identifier.
     * 
     * @param _itemClassId The new item class identifier.
     */
    void ItemClassId(short _itemClassId);

    /**
     * @brief Gets the AutoCAD version this class is associated with.
     * 
     * @return The AutoCAD version.
     */
    DG_ACadVersion DwgVersion() const;

    /**
     * @brief Sets the AutoCAD version for this class.
     * 
     * @param _dwgVersion The new AutoCAD version.
     */
    void DwgVersion(DG_ACadVersion _dwgVersion);

    /**
     * @brief Gets the maintenance version of this class.
     * 
     * @return The maintenance version.
     */
    short MaintenanceVersion() const;

    /**
     * @brief Sets the maintenance version of this class.
     * 
     * @param _maintenanceVersion The new maintenance version.
     */
    void MaintenanceVersion(short _maintenanceVersion);
};

}// namespace dwg
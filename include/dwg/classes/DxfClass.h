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

/**
 * @class DxfClass
 * @brief Represents a DXF class definition in a DWG/DXF drawing.
 *
 * DxfClass encapsulates information related to a specific DXF class,
 * including its name, version, and various attributes like proxy flags, class number, 
 * and maintenance version. It is used to define the properties and behavior of
 * custom entities in AutoCAD or similar CAD applications that support DXF format.
 */
class LIBDWG_API DxfClass
{
public:
    /**
     * @brief Constructs a DxfClass with the specified parameters.
     * 
     * @param cppClassName The C++ class name.
     * @param classNumber The class number.
     * @param version The AutoCAD version.
     * @param dxfName The DXF name associated with this class.
     * @param itemClassId The item class identifier.
     * @param maintenanceVersion The maintenance version.
     * @param proxyFlags Flags representing proxy status.
     * @param wasZombie Whether the class was previously a zombie object.
     */
    DxfClass(const std::string &cppClassName, short classNumber, ACadVersion version, const std::string &dxfName,
             short itemClassId, short maintenanceVersion, ProxyFlags proxyFlags, bool wasZombie);

    /**
     * @brief Constructs a DxfClass for a specific application.
     * 
     * @param applicationName The name of the application.
     * @param cppClassName The C++ class name.
     * @param classNumber The class number.
     * @param version The AutoCAD version.
     * @param dxfName The DXF name associated with this class.
     * @param itemClassId The item class identifier.
     * @param maintenanceVersion The maintenance version.
     * @param proxyFlags Flags representing proxy status.
     * @param wasZombie Whether the class was previously a zombie object.
     */
    DxfClass(const std::string &applicationName, const std::string &cppClassName, short classNumber,
             ACadVersion version, const std::string &dxfName, short itemClassId, short maintenanceVersion,
             ProxyFlags proxyFlags, bool wasZombie);

    /**
     * @brief Gets the DXF name of this class.
     * 
     * @return The DXF name.
     */
    std::string dxfName() const;

    /**
     * @brief Sets the DXF name of this class.
     * 
     * @param dxfName The new DXF name.
     */
    void setDxfName(const std::string &dxfName);

    /**
     * @brief Gets the C++ class name.
     * 
     * @return The C++ class name.
     */
    std::string cppClassName() const;

    /**
     * @brief Sets the C++ class name.
     * 
     * @param name The new C++ class name.
     */
    void setCppClassName(const std::string &name);

    /**
     * @brief Gets the application name associated with this class.
     * 
     * @return The application name.
     */
    std::string applicationName() const;

    /**
     * @brief Sets the application name associated with this class.
     * 
     * @param applicationName The new application name.
     */
    void setApplicationName(const std::string &applicationName);

    /**
     * @brief Gets the proxy flags for this class.
     * 
     * @return The proxy flags.
     */
    ProxyFlags proxyFlags() const;

    /**
     * @brief Sets the proxy flags for this class.
     * 
     * @param proxyFlags The new proxy flags.
     */
    void setProxyFlags(ProxyFlags proxyFlags);

    /**
     * @brief Gets the instance count of this class.
     * 
     * @return The instance count.
     */
    int instanceCount() const;

    /**
     * @brief Sets the instance count of this class.
     * 
     * @param instanceCount The new instance count.
     */
    void setInstanceCount(int instanceCount);

    /**
     * @brief Checks if this class was a zombie object.
     * 
     * @return True if the class was a zombie, false otherwise.
     */
    bool wasZombie() const;

    /**
     * @brief Sets the zombie status for this class.
     * 
     * @param wasZombie True if the class was a zombie object.
     */
    void setWasZombie(bool wasZombie);

    /**
     * @brief Checks if this class is an entity.
     * 
     * @return True if the class is an entity, false otherwise.
     */
    bool isAnEntity() const;

    /**
     * @brief Sets whether this class is an entity.
     * 
     * @param isAnEntity True if the class is an entity, false otherwise.
     */
    void setIsAnEntity(bool isAnEntity);

    /**
     * @brief Gets the class number of this class.
     * 
     * @return The class number.
     */
    short classNumber() const;

    /**
     * @brief Sets the class number for this class.
     * 
     * @param classNumber The new class number.
     */
    void setClassNumber(short classNumber);

    /**
     * @brief Gets the item class identifier.
     * 
     * @return The item class identifier.
     */
    short itemClassId() const;

    /**
     * @brief Sets the item class identifier.
     * 
     * @param itemClassId The new item class identifier.
     */
    void setItemClassId(short itemClassId);

    /**
     * @brief Gets the AutoCAD version this class is associated with.
     * 
     * @return The AutoCAD version.
     */
    ACadVersion dwgVersion() const;

    /**
     * @brief Sets the AutoCAD version for this class.
     * 
     * @param dwgVersion The new AutoCAD version.
     */
    void setDwgVersion(ACadVersion dwgVersion);

    /**
     * @brief Gets the maintenance version of this class.
     * 
     * @return The maintenance version.
     */
    short maintenanceVersion() const;

    /**
     * @brief Sets the maintenance version of this class.
     * 
     * @param maintenanceVersion The new maintenance version.
     */
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
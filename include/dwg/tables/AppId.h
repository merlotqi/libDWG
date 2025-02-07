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

#include <dwg/tables/TableEntry.h>

namespace dwg {

/**
 * @class DG_AppId
 * @brief Represents an application ID in a DWG/DXF drawing.
 *
 * An application ID associates an external application or database with the drawing.
 */
class LIBDWG_API DG_AppId : public DG_TableEntry
{
public:
    /**
     * @brief Constructs a DG_AppId with a given name.
     * 
     * @param name The name of the application ID.
     */
    DG_AppId(const std::string &name);

    /**
     * @brief Destructor for DG_AppId.
     */
    ~DG_AppId();

    /**
     * @brief Retrieves the object type for the application ID.
     * 
     * @return The object type.
     */
    DG_ObjectType objectType() const override;

    /**
     * @brief Retrieves the object name for the application ID.
     * 
     * @return The object name as a string.
     */
    std::string objectName() const override;

    /**
     * @brief Retrieves the subclass marker for the application ID.
     * 
     * @return A string representing the subclass marker.
     */
    std::string subclassMarker() const override;

public:
    /**
     * @brief Default name for the application ID.
     */
    static std::string DefaultName;

    /**
     * @brief Retrieves the default application ID.
     * 
     * @return A pointer to the default DG_AppId.
     */
    static DG_AppId *Default();
};

/**
 * @class DG_AppIdsTable
 * @brief Represents a table of application IDs in a DWG/DXF drawing.
 *
 * This table holds multiple application IDs that associate external applications with the drawing.
 */
class LIBDWG_API DG_AppIdsTable : public DG_Table
{
public:
    /**
     * @brief Constructs a DG_AppIdsTable object.
     */
    DG_AppIdsTable();

    /**
     * @brief Retrieves the object type for the application IDs table.
     * 
     * @return The object type.
     */
    DG_ObjectType objectType() const override;

    /**
     * @brief Retrieves the object name for the application IDs table.
     * 
     * @return The object name as a string.
     */
    std::string objectName() const override;

protected:
    /**
     * @brief Retrieves the default entries for the application IDs table.
     * 
     * @return A vector of strings representing the default entries.
     */
    std::vector<std::string> defaultEntries() const override;
};

}// namespace dwg
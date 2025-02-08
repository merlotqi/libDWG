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

#include <assert.h>
#include <dwg/CadObject.h>
#include <dwg/INamedCadObject.h>
#include <dwg/exports.h>
#include <dwg/tables/StandardFlags.h>

namespace dwg {

/**
 * @class TableEntry
 * @brief Represents a table entry in a DWG/DXF drawing.
 *
 * A table entry can store a name and flags associated with an object in the drawing.
 */
class LIBDWG_API TableEntry : public CadObject, INamedCadObject
{
public:
    /**
     * @brief Constructs a TableEntry with a given name.
     * 
     * @param name The name of the table entry.
     */
    TableEntry(const std::string &name);

    /**
     * @brief Destructor for TableEntry.
     */
    virtual ~TableEntry();

    /**
     * @brief Retrieves the subclass marker for the table entry.
     * 
     * @return A string representing the subclass marker.
     */
    std::string subclassMarker() const override;

    /**
     * @brief Gets the name of the table entry.
     * 
     * @return The name of the table entry.
     */
    virtual std::string name() const;

    /**
     * @brief Sets the name of the table entry.
     * 
     * @param value The new name to set.
     */
    virtual void setName(const std::string &value);

    /**
     * @brief Retrieves the flags associated with the table entry.
     * 
     * @return The flags for the table entry.
     */
    StandardFlags flags() const;

    /**
     * @brief Sets the flags for the table entry.
     * 
     * @param flags The flags to set.
     */
    void setFlags(StandardFlags flags);

protected:
    /**
     * @brief Default constructor for TableEntry.
     */
    TableEntry();

protected:
    StandardFlags _flags; /**< Flags associated with the table entry. */
    std::string _name;    /**< The name of the table entry. */
};

/**
 * @class Table
 * @brief Represents a table that holds entries in a DWG/DXF drawing.
 *
 * The table contains a collection of table entries, which can be added, retrieved, and modified.
 */
class LIBDWG_API Table : public CadObject
{
    std::map<std::string, TableEntry *> _entries; /**< Map of table entries, keyed by name. */

public:
    /**
     * @brief Constructs a Table object.
     */
    Table();

    /**
     * @brief Retrieves the object name for the table.
     * 
     * @return The object name as a string.
     */
    std::string objectName() const override;

    /**
     * @brief Retrieves the subclass marker for the table.
     * 
     * @return A string representing the subclass marker.
     */
    std::string subclassMarker() const override;

    /**
     * @brief Retrieves a table entry by its name.
     * 
     * @param key The name of the table entry.
     * @return A pointer to the corresponding TableEntry.
     */
    TableEntry *operator[](const std::string &key) const;

    /**
     * @brief Adds a new table entry to the table.
     * 
     * @param entry The table entry to add.
     */
    void ddd(TableEntry *entry);

    /**
     * @brief Checks if a table entry with the given name exists.
     * 
     * @param key The name of the table entry.
     * @return True if the entry exists, false otherwise.
     */
    bool contains(const std::string &key);

    /**
     * @brief Retrieves a table entry by its name.
     * 
     * @param key The name of the table entry.
     * @return A pointer to the corresponding TableEntry.
     */
    TableEntry *getValue(const std::string &key);

    /**
     * @brief Creates default entries in the table.
     */
    void createDefaultEntries();

protected:
    /**
     * @brief Adds a new table entry with a specified key.
     * 
     * @param key The key (name) for the table entry.
     * @param item The table entry to add.
     */
    void add(const std::string &key, TableEntry *item);

    /**
     * @brief Adds a handle prefix to the specified table entry.
     * 
     * @param item The table entry to modify.
     */
    void addHandlePrefix(TableEntry *item);

    /**
     * @brief Retrieves the default entries for the table.
     * 
     * @return A vector of strings representing the default entries.
     */
    virtual std::vector<std::string> defaultEntries() const = 0;
};

}// namespace dwg

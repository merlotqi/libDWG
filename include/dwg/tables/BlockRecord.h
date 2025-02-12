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

#include <dwg/CadObjectCollection.h>
#include <dwg/blocks/BlockTypeFlags.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/units/UnitsType.h>
#include <string>

namespace dwg {

class Layout;

/**
 * @class BlockRecord
 * @brief Represents a block record in a DWG/DXF drawing.
 *
 * A block record stores information about a block definition, including its properties, layout, and preview data.
 * Block records are essential for handling blocks, which are reusable collections of entities.
 */
class LIBDWG_API BlockRecord : public TableEntry
{
public:
    /**
     * @brief Constructs a BlockRecord with a given name.
     * 
     * @param name The name of the block record.
     */
    BlockRecord(const std::string &name) : TableEntry(name) {}

    /** @brief The name representing the model space block record. */
    static constexpr auto ModelSpaceName = "*Model_Space";
    /** @brief The name representing the paper space block record. */
    static constexpr auto PaperSpaceName = "*Paper_Space";

    /**
     * @brief Retrieves the model space block record.
     * 
     * @return A pointer to the model space block record.
     */
    static BlockRecord *ModelSpace();

    /**
     * @brief Retrieves the paper space block record.
     * 
     * @return A pointer to the paper space block record.
     */
    static BlockRecord *PaperSpace();

    /**
     * @brief Retrieves the object type for the block record.
     * 
     * @return The object type.
     */
    ObjectType objectType() const override;

    /**
     * @brief Retrieves the object name for the block record.
     * 
     * @return The object name as a string.
     */
    std::string objectName() const override;

    /**
     * @brief Retrieves the subclass marker for the block record.
     * 
     * @return A string representing the subclass marker.
     */
    std::string subclassMarker() const override;

    /**
     * @brief Retrieves the units type for the block record.
     * 
     * @return The units type.
     */
    UnitsType units() const;

    /**
     * @brief Sets the units type for the block record.
     * 
     * @param units The units type to set.
     */
    void setUnits(UnitsType units);

    /**
     * @brief Retrieves the flags associated with the block record.
     * 
     * @return The block record flags.
     */
    BlockTypeFlags flags() const;

    /**
     * @brief Sets the flags for the block record.
     * 
     * @param flags The flags to set.
     */
    void setFlags(BlockTypeFlags flags);

    /**
     * @brief Checks if the block record is explodable.
     * 
     * @return True if the block is explodable, false otherwise.
     */
    bool isExplodable() const;

    /**
     * @brief Sets whether the block record is explodable.
     * 
     * @param explodable True to mark as explodable, false otherwise.
     */
    void setIsExplodable(bool explodable);

    /**
     * @brief Checks if the block record can be scaled.
     * 
     * @return True if the block can be scaled, false otherwise.
     */
    bool canScale() const;

    /**
     * @brief Sets whether the block record can be scaled.
     * 
     * @param scaleable True to allow scaling, false otherwise.
     */
    void setCanScale(bool scaleable);

    /**
     * @brief Retrieves the preview data for the block record.
     * 
     * @return A vector of unsigned chars representing the preview data.
     */
    std::vector<unsigned char> preview() const;

    /**
     * @brief Sets the preview data for the block record.
     * 
     * @param preview A vector of unsigned chars representing the preview data.
     */
    void setPreview(const std::vector<unsigned char> &preview);

    /**
     * @brief Retrieves the layout associated with the block record.
     * 
     * @return A pointer to the Layout for the block record.
     */
    Layout *layout() const;

    /**
     * @brief Sets the layout for the block record.
     * 
     * @param layout A pointer to the Layout to set.
     */
    void setLayout(Layout *layout);
};

/**
 * @class BlockRecordsTable
 * @brief Represents a table of block records in a DWG/DXF drawing.
 *
 * This table holds multiple block records, each representing a block definition that can be reused in the drawing.
 */
class LIBDWG_API BlockRecordsTable : public Table
{
public:
    /**
     * @brief Retrieves the object type for the block records table.
     * 
     * @return The object type.
     */
    ObjectType objectType() const override;

protected:
    /**
     * @brief Retrieves the default entries for the block records table.
     * 
     * @return A vector of strings representing the default entries.
     */
    std::vector<std::string> defaultEntries() const;
};

}// namespace dwg

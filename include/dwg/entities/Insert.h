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

#include <dwg/entities/AttributeEntity.h>
#include <dwg/entities/Entity.h>

namespace dwg {

class DG_BlockRecord;
class DG_CadObjectCollection;
/**
 * @class DG_Insert
 * @brief Represents an insert entity in a DWG/DXF drawing.
 *
 * The DG_Insert entity is used to insert a block reference into the drawing.
 * It contains information about the block, its insertion point, scaling, 
 * rotation, and attributes.
 */
class LIBDWG_API DG_Insert : public DG_Entity
{
public:
    /**
     * @brief Constructs an insert entity with the given block record.
     * @param block The block record to insert.
     */
    DG_Insert(DG_BlockRecord *);

    /**
     * @brief Gets the object type of this entity.
     * @return The object type as DG_ObjectType.
     */
    virtual DG_ObjectType ObjectType() const override;

    /**
     * @brief Gets the name of this object.
     * @return The object name as a string.
     */
    virtual std::string ObjectName() const override;

    /**
     * @brief Gets the subclass marker associated with this object.
     * @return The subclass marker as a string.
     */
    virtual std::string SubclassMarker() const override;

    /**
     * @brief Gets the block record associated with this insert.
     * @return A pointer to the associated DG_BlockRecord.
     */
    DG_BlockRecord *Block() const;

    /**
     * @brief Sets the block record for this insert.
     * @param block A pointer to the block record.
     */
    void Block(DG_BlockRecord *);

    /**
     * @brief Gets the insertion point of the block.
     * @return The insertion point as an XYZ coordinate.
     */
    XYZ InsertPoint() const;

    /**
     * @brief Sets the insertion point of the block.
     * @param point The XYZ coordinate of the insertion point.
     */
    void InsertPoint(const XYZ &point);

    /**
     * @brief Gets the X-axis scale factor.
     * @return The X scale factor.
     */
    double XScale() const;

    /**
     * @brief Sets the X-axis scale factor.
     * @param scale The X scale factor.
     */
    void XScale(double scale);

    /**
     * @brief Gets the Y-axis scale factor.
     * @return The Y scale factor.
     */
    double YScale() const;

    /**
     * @brief Sets the Y-axis scale factor.
     * @param scale The Y scale factor.
     */
    void YScale(double scale);

    /**
     * @brief Gets the Z-axis scale factor.
     * @return The Z scale factor.
     */
    double ZScale() const;

    /**
     * @brief Sets the Z-axis scale factor.
     * @param scale The Z scale factor.
     */
    void ZScale(double scale);

    /**
     * @brief Gets the rotation angle of the block.
     * @return The rotation angle in degrees.
     */
    double Rotation() const;

    /**
     * @brief Sets the rotation angle of the block.
     * @param angle The rotation angle in degrees.
     */
    void Rotation(double angle);

    /**
     * @brief Gets the normal vector of the insert entity.
     * @return The normal vector as an XYZ coordinate.
     */
    XYZ Normal() const;

    /**
     * @brief Sets the normal vector of the insert entity.
     * @param normal The normal vector as an XYZ coordinate.
     */
    void Normal(const XYZ &normal);

    /**
     * @brief Gets the number of columns in the insert array.
     * @return The number of columns.
     */
    unsigned short ColumnCount() const;

    /**
     * @brief Sets the number of columns in the insert array.
     * @param count The number of columns.
     */
    void ColumnCount(unsigned short count);

    /**
     * @brief Gets the number of rows in the insert array.
     * @return The number of rows.
     */
    unsigned short RowCount() const;

    /**
     * @brief Sets the number of rows in the insert array.
     * @param count The number of rows.
     */
    void RowCount(unsigned short count);

    /**
     * @brief Gets the spacing between columns in the insert array.
     * @return The column spacing.
     */
    double ColumnSpacing() const;

    /**
     * @brief Sets the spacing between columns in the insert array.
     * @param spacing The column spacing.
     */
    void ColumnSpacing(double spacing);

    /**
     * @brief Gets the spacing between rows in the insert array.
     * @return The row spacing.
     */
    double RowSpacing() const;

    /**
     * @brief Sets the spacing between rows in the insert array.
     * @param spacing The row spacing.
     */
    void RowSpacing(double spacing);

    /**
     * @brief Checks if the insert has associated attributes.
     * @return True if attributes are present, false otherwise.
     */
    bool HasAttributes() const;

    /**
     * @brief Collection of attribute entities associated with this insert.
     */
    DG_CadObjectCollection *attributes;
};

}// namespace dwg

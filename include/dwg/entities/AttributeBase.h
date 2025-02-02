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

#include <dwg/entities/AttributeFlags.h>
#include <dwg/entities/TextEntity.h>
#include <dwg/entities/TextVerticalAlignment.h>

namespace dwg {

class DG_MText;

/**
 * @class DG_AttributeBase
 * @brief Represents an attribute definition in a DWG/DXF drawing.
 *
 * DG_AttributeBase is a base class for defining attributes, which are text-based data objects
 * attached to a drawing. It supports different types of attributes (single-line, multi-line),
 * provides properties for text alignment, versioning, flags, and locking status.
 * It also handles the creation and manipulation of multi-line text (MText) associated with attributes.
 */
class LIBDWG_API DG_AttributeBase : public DG_TextEntity
{
public:
    /**
     * @enum DG_AttributeType
     * @brief Defines the types of attributes in a drawing.
     *
     * The attribute types specify how the text is formatted:
     * - SingleLine: A single-line text.
     * - MultiLine: Multi-line text.
     * - ConstantMultiLine: Multi-line text that remains constant.
     */
    enum DG_AttributeType
    {
        SingleLine = 1,       ///< Single-line text.
        MultiLine = 2,        ///< Multi-line text.
        ConstantMultiLine = 4,///< Constant multi-line text.
    };

public:
    /**
     * @brief Default constructor for DG_AttributeBase.
     */
    DG_AttributeBase();

    /**
     * @brief Destructor for DG_AttributeBase.
     */
    virtual ~DG_AttributeBase();

    /**
     * @brief Gets the vertical alignment of the text.
     * 
     * @return The vertical alignment.
     */
    DG_TextVerticalAlignment VerticalAlignment() const;

    /**
     * @brief Sets the vertical alignment of the text.
     * 
     * @param alignment The vertical alignment.
     */
    void VerticalAlignment(DG_TextVerticalAlignment alignment);

    /**
     * @brief Gets the version of the attribute.
     * 
     * @return The version.
     */
    unsigned char Version() const;

    /**
     * @brief Sets the version of the attribute.
     * 
     * @param version The new version.
     */
    void Version(unsigned char version);

    /**
     * @brief Gets the tag associated with the attribute.
     * 
     * @return The tag.
     */
    std::string Tag() const;

    /**
     * @brief Sets the tag for the attribute.
     * 
     * @param tag The new tag.
     */
    void Tag(const std::string &tag);

    /**
     * @brief Gets the flags associated with the attribute.
     * 
     * @return The flags.
     */
    DG_AttributeFlags Flags() const;

    /**
     * @brief Sets the flags for the attribute.
     * 
     * @param flags The new flags.
     */
    void Flags(DG_AttributeFlags flags);

    /**
     * @brief Gets the type of the attribute (e.g., single-line, multi-line).
     * 
     * @return The attribute type.
     */
    DG_AttributeType AttributeType() const;

    /**
     * @brief Sets the type of the attribute.
     * 
     * @param attributeType The new attribute type.
     */
    void AttributeType(DG_AttributeType attributeType);

    /**
     * @brief Checks if the attribute is locked.
     * 
     * @return True if the attribute is locked, false otherwise.
     */
    bool IsReallyLocked() const;

    /**
     * @brief Sets the locked status of the attribute.
     * 
     * @param value True to lock the attribute, false to unlock.
     */
    void IsReallyLocked(bool value);

    /**
     * @brief Gets the multi-line text associated with this attribute.
     * 
     * @return A pointer to the DG_MText object.
     */
    DG_MText *MText() const;

    /**
     * @brief Sets the multi-line text for this attribute.
     * 
     * @param mtext A pointer to the DG_MText object.
     */
    void MText(DG_MText *mtext);

protected:
    /**
     * @brief Matches the properties of another attribute.
     * 
     * This function copies the properties from the source attribute to this instance.
     * 
     * @param src The source attribute to match properties from.
     */
    void matchAttributeProperties(DG_AttributeBase *src);

protected:
    unsigned char _version;         ///< The version of the attribute.
    std::string _tag;               ///< The tag associated with the attribute.
    DG_AttributeFlags _flags;       ///< The flags for the attribute.
    bool _isReallyLocked;           ///< The locked status of the attribute.
    DG_MText *_mtext;               ///< Pointer to multi-line text associated with the attribute.
    DG_AttributeType _attributeType;///< The type of the attribute (single-line, multi-line, etc.).
};

}// namespace dwg

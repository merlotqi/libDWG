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

class MText;

/**
 * @class AttributeBase
 * @brief Represents an attribute definition in a DWG/DXF drawing.
 *
 * AttributeBase is a base class for defining attributes, which are text-based data objects
 * attached to a drawing. It supports different types of attributes (single-line, multi-line),
 * provides properties for text alignment, versioning, flags, and locking status.
 * It also handles the creation and manipulation of multi-line text (MText) associated with attributes.
 */
class LIBDWG_API AttributeBase : public TextEntity
{
public:
    /**
     * @enum AttributeType
     * @brief Defines the types of attributes in a drawing.
     *
     * The attribute types specify how the text is formatted:
     * - SingleLine: A single-line text.
     * - MultiLine: Multi-line text.
     * - ConstantMultiLine: Multi-line text that remains constant.
     */
    enum AttributeType
    {
        SingleLine = 1,       ///< Single-line text.
        MultiLine = 2,        ///< Multi-line text.
        ConstantMultiLine = 4,///< Constant multi-line text.
    };

public:
    /**
     * @brief Default constructor for AttributeBase.
     */
    AttributeBase();

    /**
     * @brief Destructor for AttributeBase.
     */
    virtual ~AttributeBase();

    /**
     * @brief Gets the vertical alignment of the text.
     * 
     * @return The vertical alignment.
     */
    TextVerticalAlignment verticalAlignment() const;

    /**
     * @brief Sets the vertical alignment of the text.
     * 
     * @param alignment The vertical alignment.
     */
    void setVerticalAlignment(TextVerticalAlignment alignment);

    /**
     * @brief Gets the version of the attribute.
     * 
     * @return The version.
     */
    unsigned char version() const;

    /**
     * @brief Sets the version of the attribute.
     * 
     * @param version The new version.
     */
    void setVersion(unsigned char version);

    /**
     * @brief Gets the tag associated with the attribute.
     * 
     * @return The tag.
     */
    std::string tag() const;

    /**
     * @brief Sets the tag for the attribute.
     * 
     * @param tag The new tag.
     */
    void setTag(const std::string &tag);

    /**
     * @brief Gets the flags associated with the attribute.
     * 
     * @return The flags.
     */
    AttributeFlags flags() const;

    /**
     * @brief Sets the flags for the attribute.
     * 
     * @param flags The new flags.
     */
    void setFlags(AttributeFlags flags);

    /**
     * @brief Gets the type of the attribute (e.g., single-line, multi-line).
     * 
     * @return The attribute type.
     */
    AttributeType attributeType() const;

    /**
     * @brief Sets the type of the attribute.
     * 
     * @param attributeType The new attribute type.
     */
    void setAttributeType(AttributeType attributeType);

    /**
     * @brief Checks if the attribute is locked.
     * 
     * @return True if the attribute is locked, false otherwise.
     */
    bool isReallyLocked() const;

    /**
     * @brief Sets the locked status of the attribute.
     * 
     * @param value True to lock the attribute, false to unlock.
     */
    void setIsReallyLocked(bool value);

    /**
     * @brief Gets the multi-line text associated with this attribute.
     * 
     * @return A pointer to the MText object.
     */
    MText *mtext() const;

    /**
     * @brief Sets the multi-line text for this attribute.
     * 
     * @param mtext A pointer to the MText object.
     */
    void setMText(MText *mtext);

protected:
    /**
     * @brief Matches the properties of another attribute.
     * 
     * This function copies the properties from the source attribute to this instance.
     * 
     * @param src The source attribute to match properties from.
     */
    void matchAttributeProperties(AttributeBase *src);

protected:
    TextVerticalAlignment _verticalAlignment;
    unsigned char _version;      ///< The version of the attribute.
    std::string _tag;            ///< The tag associated with the attribute.
    AttributeFlags _flags;       ///< The flags for the attribute.
    bool _isReallyLocked;        ///< The locked status of the attribute.
    MText *_mtext;               ///< Pointer to multi-line text associated with the attribute.
    AttributeType _attributeType;///< The type of the attribute (single-line, multi-line, etc.).
};

}// namespace dwg

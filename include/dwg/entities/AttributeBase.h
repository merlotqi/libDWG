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

class LIBDWG_API AttributeBase : public TextEntity
{
    RTTR_ENABLE(TextEntity)
    
public:
    enum class AttributeType
    {
        SingleLine = 1,       ///< Single-line text.
        MultiLine = 2,        ///< Multi-line text.
        ConstantMultiLine = 4,///< Constant multi-line text.
    };

public:
    AttributeBase();
    virtual ~AttributeBase();

    TextVerticalAlignment verticalAlignment() const;
    void setVerticalAlignment(TextVerticalAlignment alignment);

    unsigned char version() const;
    void setVersion(unsigned char version);

    std::string tag() const;
    void setTag(const std::string &tag);

    AttributeFlags flags() const;
    void setFlags(AttributeFlags flags);

    AttributeType attributeType() const;
    void setAttributeType(AttributeType attributeType);

    bool isReallyLocked() const;
    void setIsReallyLocked(bool value);

    MText *mtext() const;
    void setMText(MText *mtext);

protected:
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
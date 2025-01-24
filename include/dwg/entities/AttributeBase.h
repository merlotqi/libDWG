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
#include <dwg/entities/TextVerticalAlignmentType.h>

namespace dwg {

class MText;
CPL_SMARTER_PTR(MText);

class LIBDWG_API AttributeBase : public TextEntity
{
public:
    enum AttributeType
    {
        SingleLine = 1,
        MultiLine = 2,
        ConstantMultiLine = 4,
    };

public:
    AttributeBase();
    virtual ~AttributeBase();

    TextVerticalAlignmentType VerticalAlignment() const;
    void VerticalAlignment(TextVerticalAlignmentType);
    
    unsigned char Version() const;
    void Version(unsigned char);
    
    CPL::String Tag() const;
    void Tag(const char*);
    
    AttributeFlags Flags() const;
    void Flags(AttributeFlags);

    AttributeType AttrType() const;
    void AttrType(AttributeType);

    bool IsReallyLocked() const;
    void IsReallyLocked(bool value);

    MTextPtr MText() const;
    void MText(dwg::MText *);

protected:
    void matchAttributeProperties(AttributeBase *src);

protected:
    unsigned char _version;
    CPL::String _tag;
    AttributeFlags _flags;
    bool _isReallyLocked;
    MTextWPtr _mtext;
    AttributeType _attributeType;
    MTextWPtr _mtext;
};
CPL_SMARTER_PTR(AttributeBase)

}// namespace dwg

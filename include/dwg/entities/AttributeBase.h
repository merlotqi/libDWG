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

class LIBDWG_API DG_AttributeBase : public DG_TextEntity
{
public:
    enum DG_AttributeType
    {
        SingleLine = 1,
        MultiLine = 2,
        ConstantMultiLine = 4,
    };

public:
    DG_AttributeBase();
    virtual ~DG_AttributeBase();

    DG_TextVerticalAlignment VerticalAlignment() const;
    void VerticalAlignment(DG_TextVerticalAlignment);

    unsigned char Version() const;
    void Version(unsigned char);

    std::string Tag() const;
    void Tag(const std::string &);

    DG_AttributeFlags Flags() const;
    void Flags(DG_AttributeFlags);

    DG_AttributeType AttributeType() const;
    void AttributeType(DG_AttributeType);

    bool IsReallyLocked() const;
    void IsReallyLocked(bool value);

    DG_MText *MText() const;
    void MText(DG_MText *);

protected:
    void matchAttributeProperties(DG_AttributeBase *src);

protected:
    unsigned char _version;
    std::string _tag;
    DG_AttributeFlags _flags;
    bool _isReallyLocked;
    DG_MText *_mtext;
    DG_AttributeType _attributeType;
};

}// namespace dwg

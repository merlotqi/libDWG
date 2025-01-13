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

#include <dwg/entities/MText.h>
#include <dwg/entities/TextEntity.h>
#include <dwg/entities/AttributeFlags.h>
#include <dwg/entities/TextVerticalAlignmentType.h>


namespace dwg {

enum AttributeType
{
    SingleLine = 1,
    MultiLine = 2,
    ConstantMultiLine = 4,
};
class AttributeBase : public TextEntity
{
public:
    TextVerticalAlignmentType verticalAlignment;// 74
    unsigned char version;                      // 280

    CPL::String tag;     // 2
    AttributeFlags flags;// 70

    AttributeType attributeType;// 71

public:
    bool IsReallyLocked() const;
    void IsReallyLocked(bool value);

    MText mtext() const;
    void mtext(const MText &value);

protected:
    void matchAttributeProperties(const AttributeBase &other);
};

}// namespace dwg

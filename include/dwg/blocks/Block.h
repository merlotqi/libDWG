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

#include <dwg/Coordinate.h>
#include <dwg/blocks/BlockTypeFlags.h>
#include <dwg/entities/Entity.h>


namespace dwg {

class BlockRecord;

class LIBDWG_API Block : public Entity
{
    std::string _name;
    BlockTypeFlags _flags;
    XYZ _base_point = XYZ::Zero;
    std::string _xrefPath;
    std::string _comments;

public:
    Block(BlockRecord *record);
    ~Block();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    BlockRecord *blockRecord() const;

    std::string name() const;
    void setName(const std::string &name);

    BlockTypeFlags flags() const;
    void setFlags(BlockTypeFlags flags);

    XYZ basePoint() const;
    void setBasePoint(const XYZ &);

    std::string xrefPath() const;
    void setXrefPath(const std::string &);

    std::string comments() const;
    void setComments(const std::string &);

protected:
    Block();
};

}// namespace dwg
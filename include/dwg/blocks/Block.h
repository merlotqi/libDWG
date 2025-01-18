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

#include <dwg/blocks/BlockTypeFlags.h>
#include <dwg/entities/Entity.h>

namespace dwg {

class BlockRecord;
CPL_SMARTER_PTR(BlockRecord);

class LIBDWG_API Block : public Entity
{
    // Block's name (string representation)
    CPL::String _name;

    // Flags associated with the block type
    BlockTypeFlags _flags;

    // Base point of the block, default initialized to zero
    XYZ _base_point = XYZ::Zero;

    // Path to the external reference (xref) associated with the block
    CPL::String _xrefPath;

    // Comments or description related to the block
    CPL::String _comments;

public:
    // Constructor accepting a BlockRecord pointer
    Block(BlockRecord *record);

    // Destructor
    ~Block();

    // Overrides the ObjectType method to return the type of object
    dwg::ObjectType ObjectType() const override;

    // Overrides the ObjectName method to return the object's name
    CPL::String ObjectName() const override;

    // Overrides the SubclassMarker method to return the subclass marker
    CPL::String SubclassMarker() const override;

    // Returns the associated BlockRecord pointer
    BlockRecordPtr BlockRecord() const;

    // Getter for the block's name
    CPL::String Name() const;

    // Setter for the block's name
    void Name(const CPL::String &name);

    // Getter for the block's flags
    BlockTypeFlags Flags() const;

    // Setter for the block's flags
    void Flags(BlockTypeFlags flags);

    // Getter for the block's base point
    XYZ BasePoint() const;

    // Setter for the block's base point
    void BasePoint(XYZ p);

    // Getter for the block's xref path
    CPL::String XrefPath() const;

    // Setter for the block's xref path
    void XrefPath(const CPL::String &value);

    // Getter for the block's comments
    CPL::String Comments() const;

    // Setter for the block's comments
    void Comments(const CPL::String &value);

protected:
    // Protected default constructor
    Block();
};
CPL_SMARTER_PTR(Block)

}// namespace dwg
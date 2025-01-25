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

class DG_BlockRecord;
CPL_SMARTER_PTR(DG_BlockRecord);

class LIBDWG_API DG_Block : public DG_Entity
{
    // Block's name (string representation)
    CPL::String _name;

    // Flags associated with the block type
    DG_BlockTypeFlags _flags;

    // Base point of the block, default initialized to zero
    XYZ _base_point = XYZ::Zero;

    // Path to the external reference (xref) associated with the block
    CPL::String _xrefPath;

    // Comments or description related to the block
    CPL::String _comments;

public:
    // Constructor accepting a BlockRecord pointer
    DG_Block(DG_BlockRecord *record);

    // Destructor
    ~DG_Block();

    // Overrides the ObjectType method to return the type of object
    DG_ObjectType ObjectType() const override;

    // Overrides the ObjectName method to return the object's name
    CPL::String ObjectName() const override;

    // Overrides the SubclassMarker method to return the subclass marker
    CPL::String SubclassMarker() const override;

    // Returns the associated BlockRecord pointer
    DG_BlockRecordPtr BlockRecord() const;

    // Getter for the block's name
    CPL::String Name() const;

    // Setter for the block's name
    void Name(const char *name);

    // Getter for the block's flags
    DG_BlockTypeFlags Flags() const;

    // Setter for the block's flags
    void Flags(DG_BlockTypeFlags flags);

    // Getter for the block's base point
    XYZ BasePoint() const;

    // Setter for the block's base point
    void BasePoint(XYZ p);

    // Getter for the block's xref path
    CPL::String XrefPath() const;

    // Setter for the block's xref path
    void XrefPath(const char *value);

    // Getter for the block's comments
    CPL::String Comments() const;

    // Setter for the block's comments
    void Comments(const char *value);

protected:
    // Protected default constructor
    DG_Block();
};
CPL_SMARTER_PTR(DG_Block)

}// namespace dwg
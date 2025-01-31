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

class LIBDWG_API DG_Block : public DG_Entity
{
    // Block's name (string representation)
    std::string _name;

    // Flags associated with the block type
    DG_BlockTypeFlags _flags;

    // Base point of the block, default initialized to zero
    XYZ _base_point = XYZ::Zero;

    // Path to the external reference (xref) associated with the block
    std::string _xrefPath;

    // Comments or description related to the block
    std::string _comments;

public:
    // Constructor accepting a BlockRecord pointer
    DG_Block(DG_BlockRecord *record);

    // Destructor
    ~DG_Block();

    // Overrides the ObjectType method to return the type of object
    DG_ObjectType ObjectType() const override;

    // Overrides the ObjectName method to return the object's name
    std::string ObjectName() const override;

    // Overrides the SubclassMarker method to return the subclass marker
    std::string SubclassMarker() const override;

    // Returns the associated BlockRecord pointer
    DG_BlockRecord *BlockRecord() const;

    // Getter for the block's name
    std::string Name() const;

    // Setter for the block's name
    void Name(const std::string &name);

    // Getter for the block's flags
    DG_BlockTypeFlags Flags() const;

    // Setter for the block's flags
    void Flags(DG_BlockTypeFlags flags);

    // Getter for the block's base point
    XYZ BasePoint() const;

    // Setter for the block's base point
    void BasePoint(const XYZ &);

    // Getter for the block's xref path
    std::string XrefPath() const;

    // Setter for the block's xref path
    void XrefPath(const std::string &);

    // Getter for the block's comments
    std::string Comments() const;

    // Setter for the block's comments
    void Comments(const std::string &);

protected:
    // Protected default constructor
    DG_Block();
};

}// namespace dwg
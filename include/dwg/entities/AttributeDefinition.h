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

#include <dwg/entities/AttributeBase.h>

namespace dwg {

class DG_AttributeEntity;

// DG_AttributeDefinition class represents a specific type of attribute that extends AttributeBase.
// It includes additional information such as a prompt message.
class LIBDWG_API DG_AttributeDefinition : public DG_AttributeBase
{
    // Private member to store the prompt string associated with the attribute definition.
    CPL::String _prompt;

public:
    // Default constructor for DG_AttributeDefinition.
    DG_AttributeDefinition();

    DG_AttributeDefinition(DG_AttributeEntity *);

    // Destructor for DG_AttributeDefinition.
    ~DG_AttributeDefinition();

    // Overrides the ObjectType method to return the specific object type for DG_AttributeDefinition.
    virtual DG_ObjectType ObjectType() const override;

    // Overrides the ObjectName method to return the name of the object (DG_AttributeDefinition).
    virtual CPL::String ObjectName() const override;

    // Overrides the SubclassMarker method to return the subclass marker associated with DG_AttributeDefinition.
    virtual CPL::String SubclassMarker() const override;

    // Getter method to retrieve the prompt string.
    CPL::String Prompt() const;

    // Setter method to update the prompt string.
    void Prompt(const char *);
};
CPL_SMARTER_PTR(DG_AttributeDefinition)

}// namespace dwg

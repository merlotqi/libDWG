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

/**
 * @class DG_AttributeDefinition
 * @brief Represents an attribute definition in a DWG/DXF drawing, extending DG_AttributeBase.
 *
 * DG_AttributeDefinition is a specific type of attribute that includes additional information,
 * such as a prompt message that can be displayed in the drawing for user input.
 * It inherits from DG_AttributeBase, providing functionalities for versioning, tagging, 
 * flags, and text alignment, while adding specific behavior related to prompt handling.
 */
class LIBDWG_API DG_AttributeDefinition : public DG_AttributeBase
{
    /**
     * @brief Private member to store the prompt string associated with the attribute definition.
     */
    std::string _prompt;

public:
    /**
     * @brief Default constructor for DG_AttributeDefinition.
     */
    DG_AttributeDefinition();

    /**
     * @brief Constructor that initializes DG_AttributeDefinition from a given DG_AttributeEntity.
     * 
     * @param entity A pointer to a DG_AttributeEntity that will be used to initialize this object.
     */
    DG_AttributeDefinition(DG_AttributeEntity *);

    /**
     * @brief Destructor for DG_AttributeDefinition.
     */
    ~DG_AttributeDefinition();

    /**
     * @brief Overrides the ObjectType method to return the specific object type for DG_AttributeDefinition.
     * 
     * @return The object type (DG_ObjectType) of DG_AttributeDefinition.
     */
    virtual DG_ObjectType ObjectType() const override;

    /**
     * @brief Overrides the ObjectName method to return the name of the object (DG_AttributeDefinition).
     * 
     * @return The name of the object as a string.
     */
    virtual std::string ObjectName() const override;

    /**
     * @brief Overrides the SubclassMarker method to return the subclass marker associated with DG_AttributeDefinition.
     * 
     * @return The subclass marker as a string.
     */
    virtual std::string SubclassMarker() const override;

    /**
     * @brief Gets the prompt string associated with the attribute definition.
     * 
     * @return The prompt string.
     */
    std::string Prompt() const;

    /**
     * @brief Sets the prompt string for the attribute definition.
     * 
     * @param prompt The new prompt string.
     */
    void Prompt(const std::string &prompt);
};

}// namespace dwg

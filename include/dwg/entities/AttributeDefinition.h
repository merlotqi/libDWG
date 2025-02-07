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

class AttributeEntity;

/**
 * @class AttributeDefinition
 * @brief Represents an attribute definition in a DWG/DXF drawing, extending AttributeBase.
 *
 * AttributeDefinition is a specific type of attribute that includes additional information,
 * such as a prompt message that can be displayed in the drawing for user input.
 * It inherits from AttributeBase, providing functionalities for versioning, tagging, 
 * flags, and text alignment, while adding specific behavior related to prompt handling.
 */
class LIBDWG_API AttributeDefinition : public AttributeBase
{
    /**
     * @brief Private member to store the prompt string associated with the attribute definition.
     */
    std::string _prompt;

public:
    /**
     * @brief Default constructor for AttributeDefinition.
     */
    AttributeDefinition();

    /**
     * @brief Constructor that initializes AttributeDefinition from a given AttributeEntity.
     * 
     * @param entity A pointer to a AttributeEntity that will be used to initialize this object.
     */
    AttributeDefinition(AttributeEntity *);

    /**
     * @brief Destructor for AttributeDefinition.
     */
    ~AttributeDefinition();

    /**
     * @brief Overrides the ObjectType method to return the specific object type for AttributeDefinition.
     * 
     * @return The object type (ObjectType) of AttributeDefinition.
     */
    virtual ObjectType objectType() const override;

    /**
     * @brief Overrides the ObjectName method to return the name of the object (AttributeDefinition).
     * 
     * @return The name of the object as a string.
     */
    virtual std::string objectName() const override;

    /**
     * @brief Overrides the SubclassMarker method to return the subclass marker associated with AttributeDefinition.
     * 
     * @return The subclass marker as a string.
     */
    virtual std::string subclassMarker() const override;

    /**
     * @brief Gets the prompt string associated with the attribute definition.
     * 
     * @return The prompt string.
     */
    std::string prompt() const;

    /**
     * @brief Sets the prompt string for the attribute definition.
     * 
     * @param prompt The new prompt string.
     */
    void setPrompt(const std::string &prompt);
};

}// namespace dwg

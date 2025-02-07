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

class DG_AttributeDefinition;
/**
 * @class DG_AttributeEntity
 * @brief Represents an attribute entity in a DWG/DXF drawing, extending DG_AttributeBase.
 *
 * DG_AttributeEntity is a class that represents an instance of an attribute in a DWG/DXF drawing.
 * It is derived from DG_AttributeBase and adds functionality related to specific object types 
 * and names for attribute entities. This class is used to handle individual attribute occurrences 
 * in the drawing, based on an attribute definition.
 */
class LIBDWG_API DG_AttributeEntity : public DG_AttributeBase
{
public:
    /**
     * @brief Default constructor for DG_AttributeEntity.
     */
    DG_AttributeEntity();

    /**
     * @brief Constructs a DG_AttributeEntity based on a given DG_AttributeDefinition.
     * 
     * @param definition A pointer to a DG_AttributeDefinition object to initialize this entity.
     */
    DG_AttributeEntity(DG_AttributeDefinition *);

    /**
     * @brief Destructor for DG_AttributeEntity.
     */
    ~DG_AttributeEntity();

    /**
     * @brief Overrides the ObjectType method to return the specific object type for DG_AttributeEntity.
     * 
     * @return The object type (DG_ObjectType) of DG_AttributeEntity.
     */
    virtual DG_ObjectType objectType() const override;

    /**
     * @brief Overrides the ObjectName method to return the name of the object (DG_AttributeEntity).
     * 
     * @return The name of the object as a string.
     */
    virtual std::string objectName() const override;

    /**
     * @brief Overrides the SubclassMarker method to return the subclass marker associated with DG_AttributeEntity.
     * 
     * @return The subclass marker as a string.
     */
    virtual std::string subclassMarker() const override;
};

}// namespace dwg

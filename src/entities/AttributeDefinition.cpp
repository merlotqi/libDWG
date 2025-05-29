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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/AttributeDefinition.h>
#include <dwg/entities/AttributeEntity.h>

namespace dwg {

AttributeDefinition::AttributeDefinition() {}

AttributeDefinition::AttributeDefinition(AttributeEntity *entity)
{
    matchAttributeProperties(entity);
}

AttributeDefinition::~AttributeDefinition() {}

ObjectType AttributeDefinition::objectType() const
{
    return ObjectType::ATTDEF;
}

std::string AttributeDefinition::objectName() const
{
    return DxfFileToken::EntityAttributeDefinition;
}

std::string AttributeDefinition::subclassMarker() const
{
    return DxfSubclassMarker::AttributeDefinition;
}

std::string AttributeDefinition::prompt() const
{
    return _prompt;
}

void AttributeDefinition::setPrompt(const std::string &prompt)
{
    _prompt = prompt;
}

}// namespace dwg
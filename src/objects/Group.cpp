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
#include <dwg/objects/Group.h>

namespace dwg {

Group::Group() {}

Group::~Group() {}

ObjectType Group::objectType() const
{
    return ObjectType::GROUP;
}

std::string Group::objectName() const
{
    return DxfFileToken::TableGroup;
}

std::string Group::subclassMarker() const
{
    return DxfSubclassMarker::Group;
}

std::string Group::description() const
{
    return _description;
}

void Group::setDescription(const std::string &value)
{
    _description = value;
}

bool Group::isUnnamed() const
{
    return _isUnnamed;
}

void Group::setIsUnnamed(bool value)
{
    _isUnnamed = value;
}

bool Group::selectable() const
{
    return _selectable;
}

void Group::setSelectable(bool value)
{
    _selectable = value;
}

std::vector<Entity *> Group::entities() const
{
    return _entities;
}

std::vector<Entity *> &Group::entities()
{
    return _entities;
}

}// namespace dwg
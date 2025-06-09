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

#include <dwg/entities/collection/EntityCollection.h>

namespace dwg {

EntityCollection::EntityCollection(CadObject *owner) : _owner(owner) 
{
}

EntityCollection::~EntityCollection() {}

CadObject *EntityCollection::owner() const
{
    return _owner;
}

size_t EntityCollection::size() const
{
    return _entities.size();
}

Entity *EntityCollection::at(size_t index)
{
    return _entities.at(index);
}

Entity *EntityCollection::operator[](size_t index)
{
    return _entities.operator[](index);
}

void EntityCollection::add(Entity *entity) {}

void EntityCollection::add(const std::initializer_list<Entity *> &entities) {}

Entity *EntityCollection::remove(Entity *entity)
{
    return entity;
}

void EntityCollection::clear() {}

}// namespace dwg
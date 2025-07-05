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

#include <algorithm>
#include <dwg/entities/Entity.h>
#include <dwg/entities/collection/EntityCollection.h>
#include <stdexcept>

namespace dwg {

EntityCollection::EntityCollection(CadObject *owner) : _owner(owner) {}

EntityCollection::~EntityCollection() {}

std::vector<CadObject *> EntityCollection::rawCadObjects() const
{
    std::vector<CadObject *> objects;
    for (auto &&ent: _entities)
    {
        objects.emplace_back(ent);
    }
    return objects;
}

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

void EntityCollection::add(Entity *entity)
{
    assert(entity);

    if (entity->owner() != nullptr)
        throw std::runtime_error("Item already has an owner");

    auto filter = [entity](Entity *ent) { return ent == entity; };
    auto itFind = std::find_if(_entities.begin(), _entities.end(), filter);
    if (itFind != _entities.end())
        throw std::runtime_error("Item is already in the collection");

    _entities.emplace_back(entity);
    entity->setOwner(_owner);
    OnAdd(entity);
}

void EntityCollection::add(const std::initializer_list<Entity *> &entities)
{
    for (auto &&entity: entities)
    {
        add(entity);
    }
}

Entity *EntityCollection::remove(Entity *entity)
{
    auto filter = [entity](Entity *ent) { return ent == entity; };
    auto itFind = std::find_if(_entities.begin(), _entities.end(), filter);
    if (itFind == _entities.end())
        return nullptr;

    _entities.erase(itFind);
    auto item = *itFind;
    item->setOwner(nullptr);
    OnRemove(item);
    return entity;
}

void EntityCollection::clear() {}

}// namespace dwg
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

#include <dwg/IObservableCadCollection.h>
#include <dwg/exports.h>
#include <vector>

namespace dwg {

class Entity;
class LIBDWG_API EntityCollection : public IObservableCadCollection
{
public:
    EntityCollection(CadObject *owner);
    ~EntityCollection();

    CadObject *owner() const;

    size_t size() const;
    Entity *at(size_t index);
    Entity *operator[](size_t index);

    void add(Entity *entity);
    void add(const std::initializer_list<Entity *> &entities);
    Entity *remove(Entity *entity);
    void clear();

public:
    using iterator = typename std::vector<Entity *>::iterator;
    using const_iterator = typename std::vector<Entity *>::const_iterator;

    // clang-format off
    inline bool empty() const noexcept { return _entities.empty(); }
    inline iterator begin() noexcept { return _entities.begin(); }
    inline iterator end() noexcept { return _entities.end(); }
    inline const_iterator begin() const noexcept { return _entities.cbegin(); }
    inline const_iterator end() const noexcept { return _entities.cend(); }
    inline const_iterator cbegin() const noexcept { return _entities.cbegin(); }
    inline const_iterator cend() const noexcept { return _entities.cend(); }
    inline Entity * front() noexcept { return _entities.front(); }
    inline Entity * back() noexcept { return _entities.back(); }
    // clang-format on

private:
    CadObject *_owner;
    std::vector<Entity *> _entities;
};

}// namespace dwg

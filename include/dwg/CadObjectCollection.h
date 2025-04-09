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

#include <dwg/CadObject.h>
#include <vector>

namespace dwg {

template<class T>
class CadObjectCollection
{
    static_assert(std::is_base_of<CadObject, T>::value, "T must be derived from CadObject");

public:
    using pointer = T *;
    using const_pointer = T *;
    using iterator = typename std::vector<pointer>::iterator;
    using const_iterator = typename std::vector<pointer>::const_iterator;

    CadObjectCollection(CadObject *owner) : _owner(owner) {}
    ~CadObjectCollection()
    {
        for (pointer i: _entries)
        {
            delete i;
            i = nullptr;
        }
    }

    CadObject *owner() const
    {
        return _owner;
    }

    size_t size() const
    {
        return _entries.size();
    }
    iterator begin()
    {
        return _entries.begin();
    }
    iterator end()
    {
        return _entries.end();
    }
    const_iterator cbegin()
    {
        return _entries.cbegin();
    }
    const_iterator cend()
    {
        return _entries.cend();
    }
    pointer operator[](size_t index) const
    {
        return _entries[index];
    }
    pointer &operator[](size_t index)
    {
        return _entries[index];
    }

    virtual void push_back(pointer item)
    {
        if (!item)
            return;
        if (item->owner())
            throw std::invalid_argument("item already has an owner");

        auto itFind = std::find_if(_entries.begin(), _entries.end(), item);
        if (itFind != _entries.end())
            throw std::invalid_argument("item is already in the collection");

        _entries.push_back(item);
        item->setOwner(_owner);

        OnAdd(item);
    }

    void clear()
    {
        for (pointer i: _entries)
        {
            delete i;
            i = nullptr;
        }
        _entries.clear();
    }

    pointer remove(pointer item)
    {
        auto itFind = std::find_if(_entries.begin(), _entries.end(), item);
        if (itFind == _entries.end())
            return nullptr;

        _entries.erase(itFind);
        item->setOwner(nullptr);
        OnRemove(item);
        return item;
    }

    Delegate<void(pointer)> OnAdd;
    Delegate<void(pointer)> OnRemove;

protected:
    CadObject *_owner;
    std::vector<pointer> _entries;
};

}// namespace dwg
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
#include <dwg/utils/Delegate.h>
#include <vector>
#include <algorithm>
#include <utility>
#include <iterator>
#include <initializer_list>

namespace dwg {

    template<typename T>
class CadObjectCollection
{
    static_assert(std::is_pointer<T>::value, "T must be a pointer type");
    static_assert(std::is_base_of<CadObject, std::remove_pointer_t<T>>::value,
                  "T must be a pointer to a class derived from CadObject");

    std::vector<T> _entries;
    CadObject *_owner;

    using pointer = T;
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

public:
    CadObjectCollection() noexcept = default;
    CadObjectCollection(const CadObjectCollection &other) = default;
    CadObjectCollection(CadObjectCollection &&other) noexcept = default;
    CadObjectCollection& operator=(const CadObjectCollection& other) = default;
    CadObjectCollection& operator=(CadObjectCollection&& other) noexcept = default;
    CadObjectCollection(std::initializer_list<T> initList) : _entries(initList) {}

    Delegate<void(pointer)> OnAdd;
    Delegate<void(pointer)> OnRemove;

public:
    void push_back(const T &value)
    {
        if (!value)
            return;
        if (value->owner())
            throw std::invalid_argument("value already has an owner");

        auto itFind = std::find_if(_entries.begin(), _entries.end(), [&](pointer i) { return i == value; });
        if (itFind != _entries.end())
            throw std::invalid_argument("value is already in the collection");

        _entries.push_back(value);
        value->setOwner(_owner);

        OnAdd(value);
    }

    void push_back(T&& value) noexcept(std::is_nothrow_move_constructible<T>::value) {
        if (!value)
            return;
        if (value->owner())
            throw std::invalid_argument("value already has an owner");

        auto itFind = std::find_if(_entries.begin(), _entries.end(), [&](pointer i) { return i == value; });
        if (itFind != _entries.end())
            throw std::invalid_argument("value is already in the collection");

        _entries.push_back(std::move(value));
        value->setOwner(_owner);

        OnAdd(value);
    }

    T removeOne(const T &value)
    {
        auto itFind = std::find_if(_entries.begin(), _entries.end(), [&](pointer i) { return i == value; });
        if (itFind == _entries.end())
            return nullptr;

        _entries.erase(itFind);
        value->setOwner(nullptr);
        OnRemove(value);
        return value;
    }

    CadObject *owner() const { return _owner; }
    void setOwner(CadObject *obj)
    {
        delete _owner;
        _owner = obj;
    }
    size_t size() const { return _entries.size(); }
    pointer at(size_t i) const { return _entries.at(i); }
    bool empty() const { return _entries.empty(); }

    iterator begin() { return _entries.begin(); }
    iterator end() { return _entries.end(); }

    const_iterator begin() const { return _entries.begin(); }
    const_iterator end() const { return _entries.end(); }

    const_iterator cbegin() const { return _entries.cbegin(); }
    const_iterator cend() const { return _entries.cend(); }

    pointer operator[](size_t index) const { return _entries[index]; }
    pointer &operator[](size_t index) { return _entries[index]; }

    template<typename Func>
    void forEach(Func &&f)
    {
        for(T& item : _entries)
        {
            f(item);
        }
    }

    template<typename Func>
    void forEach(Func &&f) const
    {
        for(const T& item : _entries)
        {
            f(item);
        }
    }
};



}// namespace dwg
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

namespace dwg {

/**
 * @class CadObjectCollection
 * @brief Manages a collection of CadObject-derived entities.
 *
 * This template class provides storage and management for a collection of 
 * objects that inherit from CadObject. It ensures ownership consistency
 * and provides mechanisms for adding and removing objects.
 *
 * @tparam T The type of objects stored in the collection, which must derive from CadObject.
 */
template<class T>
class CadObjectCollection
{
    static_assert(std::is_base_of<CadObject, T>::value, "T must be derived from CadObject");

protected:
    std::vector<T *> _entries;///< List of objects in the collection.
    CadObject *_owner;        ///< The owner of this collection.

public:
    /**
     * @brief Constructs a CadObjectCollection with a specified owner.
     * @param owner The owning CadObject.
     */
    CadObjectCollection(CadObject *owner) : _owner(owner) {}

    /**
     * @brief Destructor for CadObjectCollection.
     */
    virtual ~CadObjectCollection() {}

    /**
     * @brief Adds an item to the collection.
     * @param item The object to be added.
     * @throws std::invalid_argument If the item is null.
     * @throws std::runtime_error If the item already has an owner.
     */
    void add(T *item)
    {
        if (!item)
            throw std::invalid_argument("item is null");
        if (item->owner())
            throw std::runtime_error("item already has an owner");

        _entries.push_back(item);
        item->Owner(_owner);
        OnAdded(item);
    }

    /**
     * @brief Removes an item from the collection.
     * @param item The object to be removed.
     * @return A pointer to the removed object, or nullptr if not found.
     */
    T *remove(T *item)
    {
        auto it = std::find(_entries.begin(), _entries.end(), item);
        if (it == _entries.end())
            return nullptr;

        item->Owner(nullptr);
        OnRemoved(item);
        return _entries.erase(it);
    }

    /**
     * @brief Gets the number of objects in the collection.
     * @return The number of objects.
     */
    size_t count() const
    {
        return _entries.size();
    }

    /**
     * @brief Accesses an object by index.
     * @param index The index of the object.
     * @return A pointer to the object at the given index.
     */
    T *operator[](size_t index) const
    {
        return _entries[index];
    }

    /**
     * @brief Retrieves an object at a specified index.
     * @param index The index of the object.
     * @return A pointer to the object at the given index.
     */
    T *at(size_t index) const
    {
        return _entries[index];
    }

    /**
     * @brief Gets the owner of the collection.
     * @return A pointer to the owner.
     */
    CadObject *owner() const
    {
        return _owner;
    }

    /**
     * @brief Sets the owner of the collection.
     * @param owner A pointer to the new owner.
     */
    void setOwner(CadObject *owner)
    {
        _owner = owner;
    }

    /**
     * @brief Delegate triggered when an object is added.
     */
    Delegate<void(T *)> OnAdded;

    /**
     * @brief Delegate triggered when an object is removed.
     */
    Delegate<void(T *)> OnRemoved;
};

}// namespace dwg
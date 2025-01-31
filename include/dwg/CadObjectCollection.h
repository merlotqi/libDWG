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

/// \brief Collection of CAD objects with support for adding, removing, and event handling.
class LIBDWG_API DG_CadObjectCollection
{
protected:
    /// \brief Internal storage of CAD objects as a vector of smart pointers.
    std::vector<DG_CadObject *> _entries;

    /// \brief Pointer to the owning CAD object of this collection.
    DG_CadObject *_owner;

public:
    /// \brief Constructor to initialize the collection with an owner.
    /// \param owner Pointer to the owning CAD object.
    DG_CadObjectCollection(DG_CadObject *owner);

    /// \brief Destructor to clean up resources.
    ~DG_CadObjectCollection();

    /// \brief Add a CAD object to the collection.
    /// \param item Pointer to the CAD object to add.
    void Add(DG_CadObject *item);

    /// \brief Remove a CAD object from the collection.
    /// \param item Pointer to the CAD object to remove.
    void Remove(DG_CadObject *item);

    /// \brief Get the number of CAD objects in the collection.
    /// \return The count of objects in the collection.
    size_t Count() const;

    /// \brief Get the owning CAD object of the collection.
    /// \return Pointer to the owning CAD object.
    DG_CadObject *Owner() const;

    /// \brief Access a CAD object in the collection by its index.
    /// \param index The index of the CAD object to access.
    /// \return Smart pointer to the CAD object at the specified index.
    DG_CadObject operator[](int index);

    /// \brief CPL::Delegate triggered when a CAD object is added to the collection.
    /// \details This allows registering custom callbacks that will execute when an object is added.
    CPL::Delegate<void(DG_CadObject *)> OnAdd;

    /// \brief CPL::Delegate triggered when a CAD object is removed from the collection.
    /// \details This allows registering custom callbacks that will execute when an object is removed.
    CPL::Delegate<void(DG_CadObject *)> OnRemove;
};


}// namespace dwg
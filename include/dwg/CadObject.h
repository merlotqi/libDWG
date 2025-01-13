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

#include <dwg/exports.h>
#include <dwg/DxfFileToken.h>
#include <dwg/DxfSubclassMarker.h>
#include <dwg/IHandledCadObject.h>
#include <dwg/ObjectType.h>
#include <dwg/objects/CadDictionary.h>
#include <string>

namespace dwg {

/// \brief Base class representing a CAD object with support for handle-based identification
/// and ownership hierarchy.
class LIBDWG_API CadObject : public IHandledCadObject
{
protected:
    /// \brief Unique handle identifying the CAD object.
    unsigned long long _handle;

    /// \brief Weak pointer to the owning CAD object.
    WeakSmarterPtr<CadObject> _owner;

    CadDocumentWPtr _document;

public:
    /// \brief Default constructor.
    CadObject() = default;

    /// \brief Virtual destructor.
    virtual ~CadObject() = default;

    /// \brief Get the type of the CAD object.
    /// \details This method must be implemented by derived classes to return the specific
    /// type of the object.
    /// \return The type of the object as a value from the `dwg::ObjectType` enumeration.
    virtual dwg::ObjectType ObjectType() const = 0;

    /// \brief Get the name of the CAD object.
    /// \details This method must be implemented by derived classes to return the name
    /// associated with the object.
    /// \return A string representing the object's name.
    virtual std::string ObjectName() const = 0;

    /// \brief Get the subclass marker of the CAD object.
    /// \details This method must be implemented by derived classes to return a marker
    /// indicating the object's subclass.
    /// \return A string representing the subclass marker.
    virtual std::string SubclassMarker() const = 0;

    /// \brief Get the unique handle of the CAD object.
    /// \return The handle of the object as an unsigned long long value.
    unsigned long long Handle() const;

    /// \brief Get the owning CAD object of this object.
    /// \details The ownership establishes a hierarchical relationship between CAD objects.
    /// \return A smart pointer to the owning CAD object, or nullptr if no owner is set.
    SmarterPtr<CadObject> Owner();

    CadDocumentPtr Document();

    void Document(CadDocument*);

    virtual SmarterPtr<CadObject> Clone();

protected:
    /// \brief Set the unique handle of the CAD object.
    /// \param value The handle value to assign.
    void Handle(unsigned long long value);
    
    /// \brief Set the owning CAD object for this object.
    /// \param obj Pointer to the new owning CAD object.
    void Owner(CadObject *obj);

    virtual void AssignDocument(CadDocument* doc);
    virtual void UnassignDocument();

    template<class T>
    SmarterPtr<T> updateTable(T* entity, Table<T>* table)
    {
        return NULL;
    }

    Template<class T>
    SmarterPtr<T> updateCollection(T* entity, ObjectDictionaryCollection<T> * collection)
    {
        return NULL;
    }

};
SMARTER_PTR(CadObject)


}// namespace dwg

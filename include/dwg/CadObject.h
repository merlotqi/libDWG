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

#include <dwg/IHandledCadObject.h>
#include <dwg/ObjectType.h>
#include <dwg/exports.h>
#include <string>
#include <vector>

namespace dwg {

class Table;
class ObjectDictionaryCollection;
class CadDocument;
class CadDictionary;
class ExtendedDataDictionary;
class NonGraphicalObject;
class TableEntry;

class LIBDWG_API CadObject : public IHandledCadObject
{
protected:
    unsigned long long _handle;
    IHandledCadObject *_owner;
    CadDocument *_document;
    ExtendedDataDictionary *_extendedData;
    CadDictionary *_xdictionary;
    std::vector<CadObject *> _reactors;

public:
    CadObject();
    virtual ~CadObject();

    virtual ObjectType objectType() const = 0;
    virtual std::string objectName() const = 0;
    virtual std::string subclassMarker() const = 0;

    ExtendedDataDictionary *extendedData() const;
    unsigned long long handle() const override;
    IHandledCadObject *owner() const;
    CadDictionary *xdictionary() const;

    CadDocument *document() const;
    void setDocument(CadDocument *doc);

    virtual CadObject *clone();

    virtual bool hasDynamicSubclass() const;

    std::vector<CadObject *> reactors() const;
    std::vector<CadObject *> &reactors();
    void clearReactors();
    void addReactor(CadObject *);
    bool removeReactor(CadObject *);

    // that's should be private
public:
    void setHandle(unsigned long long value);
    void setOwner(IHandledCadObject *obj);
    void setExtendedData(ExtendedDataDictionary *);
    void setXDictionary(CadDictionary *);

    virtual void assignDocument(CadDocument *doc);
    virtual void unassignDocument();

    NonGraphicalObject *updateCollection(NonGraphicalObject *entry, ObjectDictionaryCollection *collection);
    template<typename T>
    T updateCollectionT(T entry, ObjectDictionaryCollection *collection)
    {
        static_assert(std::is_pointer<T>::value, "T must be a pointer type.");
        static_assert(std::is_base_of<NonGraphicalObject, std::remove_pointer_t<T>>::value,
                      "T must point to a type derived from NonGraphicalObject.");
        NonGraphicalObject *existing = updateCollection(entry, collection);
        return dynamic_cast<T>(existing);
    }

    TableEntry *updateTable(TableEntry *entry, Table *table);
    template<typename T>
    T updateTableT(T entry, Table *table)
    {
        static_assert(std::is_pointer<T>::value, "T must be a pointer type.");
        static_assert(std::is_base_of<TableEntry, std::remove_pointer_t<T>>::value,
                      "T must point to a type derived from TableEntry.");
    }

private:
    CadObject(const CadObject &) = delete;
    CadObject &operator=(const CadObject &) = delete;
};

}// namespace dwg
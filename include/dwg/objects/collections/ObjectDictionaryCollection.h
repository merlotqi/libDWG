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
#include <dwg/IObservableCadCollection.h>
#include <type_traits>

namespace dwg {

class NonGraphicalObject;
class CadDictionary;
class ObjectDictionaryCollection : public IHandledCadObject, public IObservableCadCollection
{
    CadDictionary *_dictionary;

public:
    ObjectDictionaryCollection(CadDictionary *dictionary);
    virtual ~ObjectDictionaryCollection();

    unsigned long long handle() const;
    NonGraphicalObject *operator[](const std::string &key);
    template<typename T>
    T operator[](const std::string &key)
    {
        static_assert(std::is_pointer<T>::value, "T must be a pointer type.");
        static_assert(std::is_base_of<NonGraphicalObject, std::remove_pointer_t<T>>::value,
                      "T must point to a type derived from NonGraphicalObject.");
        return dynamic_cast<T>(_dictionary->operator[](key));
    }

    virtual void add(NonGraphicalObject *v);

    virtual bool remove(const std::string &name, NonGraphicalObject **entry);
    virtual bool remove(const std::string &name);

    bool containsKey(const std::string &name) const;
    bool tryGetEntry(const std::string &name, NonGraphicalObject **e);

    void clear();
};

}// namespace dwg
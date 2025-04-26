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
#include <dwg/objects/CadDictionary.h>
#include <type_traits>

namespace dwg {

class NonGraphicalObject;

template<typename T>
class ObjectDictionaryCollection : public IHandledCadObject
{
    CadDictionary *_dictionary;

public:
    using pointer = std::remove_cv_t<T>;
    using pointee = std::remove_pointer_t<pointer>;

    static_assert(std::is_pointer<pointer>::value, "T must be a pointer type.");
    static_assert(std::is_base_of<NonGraphicalObject, pointee>::value,
                  "T must point to a type derived from NonGraphicalObject.");

    // clang-format off
    ObjectDictionaryCollection(CadDictionary *dictionary) : _dictionary(dictionary) {}
    virtual ~ObjectDictionaryCollection() {}

    unsigned long long handle() const { return _dictionary->handle(); }
    pointer operator[](const std::string &key) const { return dynamic_cast<pointer>(_dictionary->operator[](key)); }
    void add(pointer v) { _dictionary->add(v); }
    bool remove(const std::string &name, pointer *entry) 
    { 
        NonGraphicalObject* temp = nullptr;
        bool result = _dictionary->remove(name, &temp);
        *entry = dynamic_cast<pointer>(temp);
        return result;
    }
    bool remove(const std::string &name) { return _dictionary->remove(name); }
    bool containsKey(const std::string &name) const { return _dictionary->containsKey(name); }
    bool tryGetEntry(const std::string &name, pointer *e) 
    {
        NonGraphicalObject* temp = nullptr;
        bool result = _dictionary->tryGetEntry(name, &temp);
        *e = dynamic_cast<pointer>(temp);
        return result;
    }
    void clear() { _dictionary->clear(); }

    // clang-format on
};

}// namespace dwg
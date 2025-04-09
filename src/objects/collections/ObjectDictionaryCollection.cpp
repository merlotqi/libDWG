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

namespace dwg {

class NonGraphicalObject;
class LIBDWG_API ObjectDictionaryCollection : public IHandledCadObject
{
    CadDictionary *_dictionary;

public:
    ObjectDictionaryCollection(CadDictionary *dictionary);
    virtual ~ObjectDictionaryCollection();

    unsigned long long handle() const;

    NonGraphicalObject *operator[](const std::string &key) const;

    void add(NonGraphicalObject *);
    bool remove(const std::string &name, NonGraphicalObject **entry);
    bool remove(const std::string &name);
    bool containsKey(const std::string &) const;
    bool tryGetEntry(const std::string &name, NonGraphicalObject **);

    template<typename T>
    bool tryGetEntryT(const std::string &name, T **entry)
    {
        NonGraphicalObject *tmp = nullptr;
        if(tryGetEntry(name, &tmp))
        {
            if(dynamic_cast<T*>(tmp))
            {
                *entry = tmp;
                return true;
            }
        }
        return false;
    }

    void clear();

protected:
    virtual bool assertType(NonGraphicalObject *item);
    virtual bool beforeRemove(const std::string &name);
    virtual void beforeAdd(NonGraphicalObject *entry);

};

}// namespace dwg
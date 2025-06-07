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
#include <initializer_list>

namespace dwg {
class CadObject;

class LIBDWG_API CadObjectCollection : public IObservableCadCollection
{
public:
    CadObjectCollection(CadObject *owner);
    virtual ~CadObjectCollection() {}

    CadObject *owner() const;

    size_t size() const;

    virtual void add(CadObject *);
    void add(const std::initializer_list<CadObject *> &items);
    virtual CadObject *remove(CadObject *);

    void clear();

    CadObject *operator[](size_t index);

public:
    using iterator = std::vector<CadObject *>::iterator;
    using const_interator = std::vector<CadObject *>::const_iterator;
    iterator begin()
    {
        return _entries.begin();
    }
    iterator end()
    {
        return _entries.end();
    }
    const_interator begin() const
    {
        return _entries.cbegin();
    }
    const_interator end() const
    {
        return _entries.cend();
    }
    const_interator cbegin() const
    {
        return _entries.cbegin();
    }
    const_interator cend() const
    {
        return _entries.cend();
    }

protected:
    std::vector<CadObject *> _entries;
    CadObject *_owner;
};

}// namespace dwg

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

#include <dwg/CadObjectCollection.h>

namespace dwg {

CadObjectCollection::CadObjectCollection(CadObject *owner) : _owner(owner) {}

CadObjectCollection::~CadObjectCollection() { _owner = nullptr; }

void CadObjectCollection::Add(CadObject *item)
{
    if (!item) throw new std::invalid_argument("Item is null");

    if (item->Owner() != nullptr) throw new std::invalid_argument("Item is already has an owner");

    auto itFind = std::find_if(_entries.begin(), _entries.end(), item);
    if (itFind != _entries.end()) { throw new std::invalid_argument("Item is already in the collection"); }

    _entries.push_back(item);
    item->Owner(_owner);
}

void CadObjectCollection::Remove(CadObject *item)
{
    auto itFind = std::find_if(_entries.begin(), _entries.end(), item);
    if (itFind != _entries.end())
    {
        (*itFind)->Owner(nullptr);
        OnRemove(*itFind);
        _entries.erase(itFind);
    }
}

size_t CadObjectCollection::Count() const { return _entries.size(); }

CadObject *CadObjectCollection::Owner() const { return _owner; }

CadObjectPtr CadObjectCollection::operator[](int index) { return _entries.at(index); }

}// namespace dwg
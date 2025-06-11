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

#include <assert.h>
#include <dwg/CadObject.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/collections/ObjectDictionaryCollection.h>

namespace dwg {

ObjectDictionaryCollection::ObjectDictionaryCollection(CadDictionary *dictionary) : _dictionary(dictionary) {}

ObjectDictionaryCollection::~ObjectDictionaryCollection() {}

unsigned long long ObjectDictionaryCollection::handle() const
{
    assert(_dictionary);
    return _dictionary->handle();
}

std::vector<CadObject *> ObjectDictionaryCollection::rawCadObjects() const
{
    return _dictionary->rawCadObjects();
}

NonGraphicalObject *ObjectDictionaryCollection::operator[](const std::string &key)
{
    assert(_dictionary);
    auto obj = _dictionary->operator[](key);
    return obj ? dynamic_cast<NonGraphicalObject *>(obj) : nullptr;
}

void ObjectDictionaryCollection::add(NonGraphicalObject *v)
{
    assert(_dictionary);
    _dictionary->add(v);
}

bool ObjectDictionaryCollection::remove(const std::string &name, NonGraphicalObject **entry)
{
    assert(_dictionary);
    return _dictionary->remove(name, entry);
}

bool ObjectDictionaryCollection::remove(const std::string &name)
{
    assert(_dictionary);
    return _dictionary->remove(name);
}

bool ObjectDictionaryCollection::containsKey(const std::string &name) const
{
    assert(_dictionary);
    return _dictionary->containsKey(name);
}

NonGraphicalObject *ObjectDictionaryCollection::value(const std::string &name)
{
    return nullptr;
}

void ObjectDictionaryCollection::clear()
{
    assert(_dictionary);
    _dictionary->clear();
}

}// namespace dwg
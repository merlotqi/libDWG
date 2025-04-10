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

#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/collections/ObjectDictionaryCollection.h>
#include <assert.h>

namespace dwg {

ObjectDictionaryCollection::ObjectDictionaryCollection(CadDictionary *dictionary) : _dictionary(dictionary) {}

ObjectDictionaryCollection::~ObjectDictionaryCollection() {}

unsigned long long ObjectDictionaryCollection::handle() const
{
    assert(_dictionary);
    return _dictionary->handle();
}

NonGraphicalObject *ObjectDictionaryCollection::operator[](const std::string &key) const
{
    assert(_dictionary);
    NonGraphicalObject *obj = nullptr;
    _dictionary->tryGetEntry(key, &obj);
    return obj;
}

void ObjectDictionaryCollection::add(NonGraphicalObject *item)
{
    assert(_dictionary);
    beforeAdd(item);
    _dictionary->add(item);
}

bool ObjectDictionaryCollection::remove(const std::string &name, NonGraphicalObject **entry)
{
    assert(_dictionary);
    beforeRemove(name);
    return _dictionary->remove(name, entry);
}

bool ObjectDictionaryCollection::remove(const std::string &name)
{
    assert(_dictionary);
    beforeRemove(name);
    return _dictionary->remove(name);
}

bool ObjectDictionaryCollection::containsKey(const std::string &name) const
{
    assert(_dictionary);
    return _dictionary->containsKey(name);
}

bool ObjectDictionaryCollection::tryGetEntry(const std::string &name, NonGraphicalObject **entry)
{
    assert(_dictionary);
    return _dictionary->tryGetEntry(name, entry);
}

void ObjectDictionaryCollection::clear()
{
    assert(_dictionary);
    return _dictionary->clear();
}

bool ObjectDictionaryCollection::assertType(NonGraphicalObject *item) const
{
    return true;
}

bool ObjectDictionaryCollection::beforeRemove(const std::string &name)
{
    return true;
}

void ObjectDictionaryCollection::beforeAdd(NonGraphicalObject *entry)
{
}

}// namespace dwg
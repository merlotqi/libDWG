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
#include <dwg/objects/BookColor.h>
#include <dwg/objects/Group.h>
#include <dwg/objects/ImageDefinition.h>
#include <dwg/objects/Layout.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/objects/Scale.h>
#include <type_traits>

namespace dwg {


template<class T>
class ObjectDictionaryCollection : IHandledCadObject
{
    static_assert(std::is_base_of_v<T, NonGraphicalObject>,
                  "T must is base of NonGraphicalObject");

    CadDictionary _dictionary;

public:
    unsigned long long handle() const { return _dictionary.handle(); }

    T operator[](const std::string &name) const { return (T) _dictionary[key]; }

protected:
    ObjectDictionaryCollection(const CadDictionary &dictionary);

    virtual void Add(T entry);
    bool ContainsKey(const std::string &key);
    bool tryGetValue(const std::string &name, T &entry);
    bool Remove(const std::string &name);
    bool Remove(const std::string &name, T &entry);
    void Clear();
};


class ColorCollection : public ObjectDictionaryCollection<BookColor>
{
public:
    ColorCollection(const CadDictionary &dictionary);
};


class GroupCollection : public ObjectDictionaryCollection<Group>
{
public:
    GroupCollection(const CadDictionary &dictionary);
};

class ImageDefinitionCollection
    : public ObjectDictionaryCollection<ImageDefinition>
{
public:
    ImageDefinitionCollection(const CadDictionary &dictionary);
};


class LayoutCollection : public ObjectDictionaryCollection<Layout>
{
public:
    LayoutCollection(const CadDictionary &dictionary);
};


class MLineStyleCollection : public ObjectDictionaryCollection<MLineStyle>
{
public:
    MLineStyleCollection(const CadDictionary &dictionary);
};


class MLeaderStyleCollection
    : public ObjectDictionaryCollection<MultiLeaderStyle>
{
public:
    MLeaderStyleCollection(const CadDictionary &dictionary);
};


class ScaleCollection : public ObjectDictionaryCollection<Scale>
{
public:
    ScaleCollection(const CadDictionary &dictionary);
};


}// namespace dwg
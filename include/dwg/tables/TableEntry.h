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

#include <algorithm>
#include <dwg/CadObject.h>
#include <dwg/DxfFileToken.h>
#include <dwg/DxfSubclassMarker.h>
#include <dwg/INamedCadObject.h>
#include <dwg/tables/StandardFlags.h>
#include <dwg/exports.h>
#include <assert.h>

namespace dwg {

class LIBDWG_API TableEntry : public CadObject, INamedCadObject
{
public:
    TableEntry(const CPL::String &name);
    CPL::String SubclassMarker() const override;
    virtual CPL::String Name() const;
    virtual void Name(const CPL::String &value);
    // 70
    StandardFlags Flags() const;
    void Flags(StandardFlags flags);

protected:
    TableEntry();
    StandardFlags _flags;
    CPL::String _name;
};
CPL_SMARTER_PTR(TableEntry)


template<typename T>
class Table : public CadObject
{
    std::map<CPL::String, SmarterPtr<T>> _entries;

public:
    Table();
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;

    SmarterPtr<T> operator[](const CPL::String &key) const 
    {
        return _entries[key];
    }

    void Add(T *entry)
    {
        assert(entry);
        auto itFind = _entries.find(entry->Name());
        if(itFind != _entries.end())
        {
            // exist entry
            return;
        }
        _entries[entry->Name()] = entry;
    }

    bool Contains(const CPL::String &key);

    SmarterPtr<T> GetValue(const CPL::String& key)
    {
        if(!Contains(key))
            return NULL;

        return _entries[key];
    }

    void CreateDefaultEntries()
    {
        auto &&entris = defaultEntries();
        for (auto &&entry: entris)
        {
            if (Contains(entry)) continue;

            Add(new T(entry));
        }
    }

protected:
    void add(const CPL::String &key, T *item)
    {
        assert(item);
        _entries.insert({key, item});
        item->Owner(this);
    }

    void addHandlePrefix(T *item)
    {
        assert(item);
        item->Owner(this);
        CPL::String key = fmt::format("%llu:%s", item->Handle(), item->Name());
        _entries.insert({key, item});
    }

    virtual std::vector<CPL::String> defaultEntries() const = 0;
};


}// namespace dwg

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
    TableEntry(const std::string &name);
    std::string SubclassMarker() const override;
    virtual std::string Name() const;
    virtual void Name(const std::string &value);
    // 70
    StandardFlags Flags() const;
    void Flags(StandardFlags flags);

protected:
    TableEntry();
    StandardFlags _flags;
    std::string _name;
};
SMARTER_PTR(TableEntry)


template<typename T>
class Table : public CadObject
{
    std::map<std::string, SmarterPtr<T>> _entries;

public:
    Table();
    std::string ObjectName() const override;
    std::string SubclassMarker() const override;

    SmarterPtr<T> operator[](const std::string &key) const 
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

    bool Contains(const std::string &key);

    SmarterPtr<T> GetValue(const std::string& key)
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
    void add(const std::string &key, T *item)
    {
        assert(item);
        _entries.insert({key, item});
        item->Owner(this);
    }

    void addHandlePrefix(T *item)
    {
        assert(item);
        item->Owner(this);
        std::string key = fmt::format("%llu:%s", item->Handle(), item->Name());
        _entries.insert({key, item});
    }

    virtual std::vector<std::string> defaultEntries() const = 0;
};


}// namespace dwg

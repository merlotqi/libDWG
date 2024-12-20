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
#include <dwg/enums/tables/StandardFlags.h>
#include <dwg/exports.h>

namespace dwg {
namespace tables {


class TableEntry : public CadObject, INamedCadObject
{
public:
    TableEntry(const std::string &name) : _name(name) {}

    std::string SubclassMarker() const override
    {
        return DxfSubclassMarker::TableRecord;
    }

    virtual std::string Name() const { return _name; }
    virtual void Name(const std::string &value) { _name = value; }
    // 70
    StandardFlags Flags;

protected:
    TableEntry() {}

    std::string _name;
};


template<typename T>
class Table : public CadObject
{
    std::map<std::string, T> m_entries;

public:
    Table() = default;
    std::string ObjectName() const override { return DxfFileToken::TableEntry; }
    std::string SubclassMarker() const override
    {
        return DxfSubclassMarker::Table;
    }

    void Add(const T &entry)
    {
        if (m_entries.find(entry.Name()) != m_entries.end()) return;
        m_entries[entry.Name()] = entry;
    }

    bool Contains(const std::string &key)
    {
        if (m_entries.find(key) != m_entries.end()) return true;
        return false;
    }

    bool TryGetValue(const std::string &key, T &item)
    {
        if (!Contains(key)) return false;
        else
            item = m_entries[key];
        return true;
    }

    void CreateDefaultEntries()
    {
        auto &&entris = defaultEntries();
        for (auto &&entry: entris)
        {
            if (Contains(entry)) continue;

            Add(T(entry));
        }
    }

protected:
    void add(const std::string &key, const T &item)
    {
        m_entries.insert({key, item});
        item.Owner = this;
    }

    void addHandlePrefix(const T &item)
    {
        item.Owner = this;
        std::string key = str_format("%llu:%s", item.Handle, item.Name);
        m_entries.insert({key, item});
    }

    virtual std::vector<std::string> defaultEntries() const = 0;
};


}// namespace tables
}// namespace dwg

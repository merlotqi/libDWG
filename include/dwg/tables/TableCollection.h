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

#include <dwg/CadObject.h>
#include <fmt/core.h>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace dwg {

class TableEntry;
class CadDocument;

template<class T>
class Table : public CadObject
{
    static_assert(std::is_base_of_v<TableEntry, T>, "T must inherit from TableEntry.");

public:
    using pointer = T *;
    using const_pointer = T *;
    using iterator = typename std::map<std::string, pointer>::iterator;
    using const_iterator = typename std::map<std::string, pointer>::const_iterator;

    Table() = default;
    Table(CadDocument *document)   
    {
        _owner = document;
    }

    virtual ~Table()
    {
        for (auto &&entry: _entries)
        {
            delete entry.second;
        }
        _entries.clear();
    }

    size_t count() const
    {
        return _entries.size();
    }
    std::string objectName() const override
    {
        return "TableEntry";
    }
    std::string subclassMarker() const override
    {
        return "TABLE";
    }

    pointer operator[](const std::string &key) const
    {
        auto it = _entries.find(key);
        if (it != _entries.end())
            return it->second;
        return nullptr;
    }

    void add(pointer entry)
    {
        if (!entry)
            return;
        if (entry->name().empty())
            entry->setName(createName());
        add(entry->name(), entry);
    }

    bool contains(const std::string &key) const
    {
        auto it = _entries.find(key);
        return it != _entries.end();
    }

    pointer getValue(const std::string &key) const
    {
        auto it = _entries.find(key);
        if (it != _entries.end())
            return it->second;
        return nullptr;
    }

    void createDefaultEntries()
    {
        for (const auto &name: defaultEntries())
        {
            if (contains(name))
                continue;
            add(name, new T());
        }
    }

    iterator begin()
    {
        return _entries.begin();
    }
    iterator end()
    {
        return _entries.end();
    }

    const_iterator begin() const
    {
        return _entries.cbegin();
    }
    const_iterator end() const
    {
        return _entries.cend();
    }

protected:
    void add(const std::string &key, pointer item)
    {
        if (!item)
            return;
        _entries[key] = item;
        item->setOwner(this);
    }

    virtual std::vector<std::string> defaultEntries() const
    {
        return std::vector<std::string>();
    }

private:
    std::string createName() const
    {
        std::string name = "unamed";
        int i = 0;
        while (contains(fmt::format("{}_{}", name, i)))
        {
            i++;
        }

        return fmt::format("{}_{}", name, i);
    }

private:
    std::map<std::string, pointer> _entries;
};

}// namespace dwg
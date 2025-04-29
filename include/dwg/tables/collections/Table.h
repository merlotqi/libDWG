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

#include <dwg/CadDocument.h>
#include <dwg/CadObject.h>
#include <dwg/IObservableCadCollection.h>
#include <dwg/utils/Delegate.h>
#include <fmt/core.h>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace dwg {

template<typename _Ty, typename _Derived>
class Table : public CadObject, public IObservableCadCollection
{
public:
    using pointer = std::remove_cv_t<_Ty>;
    using pointee = std::remove_pointer_t<pointer>;
    using iterator = typename std::map<std::string, pointer>::iterator;
    using const_iterator = typename std::map<std::string, pointer>::const_iterator;

    static_assert(std::is_pointer<pointer>::value, "T must be a pointer type.");
    static_assert(std::is_base_of<TableEntry, pointee>::value, "T must point to a type derived from TableEntry.");

    Table() {}
    Table(CadDocument *document)
    {
        _owner = document;
        document->registerCollection(this);
    }
    ~Table() {}

    // clang-format off
    std::string objectName() const override { return "TABLE"; }
    std::string subclassMarker() const override { return "AcDbSymbolTable"; }
    std::size_t size() const { return _entries.size(); }
    pointer operator[](const std::string &key) const
    {
        auto _it = _entries.find(key);
        return (_it != _entries.end()) ? _it->second : nullptr;
    }
    void add(pointer v)
    {
        assert(v);
        if(v->name().empty())
            v->setName(createName());
        push_back(v->name(), v);
    }
    bool contains(const std::string &key) const
    {
        auto _it = _entries.find(key);
        return (_it != _entries.end()) ? true : false;
    }
    pointer value(const std::string &key) const
    {
        auto _it = _entries.find(key);
        return (_it != _entries.end()) ? _it->second : nullptr;
    }

    iterator begin() { return _entries.begin(); }
    iterator end() { return _entries.end(); }
    const_iterator begin() const { return _entries.begin(); }
    const_iterator end() const { return _entries.end(); }
    void createDefaultEntries() 
    {
        auto ns = static_cast<_Derived*>(this)->defaultEntries();
        for (auto&& entry : ns)
        {
            if(contains(entry))
                continue;

            push_back(entry, new pointee(entry));
        }
    }
    std::vector<std::string> defaultEntries() const
    {
        return std::vector<std::string>();
    }
    // clang-format on

protected:
    void addHandlePrefix(pointer v)
    {
        assert(v);
        v->setOwner(this);
        v->OnNameChanged.add(this, &Table<_Ty, _Derived>::onEntryNameChanged);

        OnAdd(v);

        std::string k = fmt::format("{}:{}", v->handle(), v->name());
        _entries.insert({k, v});
    }

    void push_back(const std::string &n, pointer v)
    {
        _entries.insert({n, v});
        v->setOwner(this);
        v->OnNameChanged.add(this, &Table<_Ty, _Derived>::onEntryNameChanged);
        OnAdd(v);
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

    void onEntryNameChanged(const std::string &oldname, const std::string &newname) {}

private:
    std::map<std::string, pointer> _entries;
};

}// namespace dwg
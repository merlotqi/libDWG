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
#include <dwg/IObservableCadCollection.h>
#include <dwg/utils/Delegate.h>
#include <map>
#include <string>
#include <type_traits>
#include <vector>

namespace dwg {

class LIBDWG_API Table : public CadObject, public IObservableCadCollection
{
public:
    using pointer = TableEntry *;
    using pointee = TableEntry;
    using iterator = typename std::map<std::string, pointer>::iterator;
    using const_iterator = typename std::map<std::string, pointer>::const_iterator;

    static_assert(std::is_pointer<pointer>::value, "T must be a pointer type.");
    static_assert(std::is_base_of<TableEntry, pointee>::value, "T must point to a type derived from TableEntry.");

    Table();
    Table(CadDocument *document);
    ~Table();

    std::string objectName() const override;
    std::string subclassMarker() const override;
    std::vector<CadObject *> rawCadObjects() const override;
    
    std::size_t size() const;
    pointer operator[](const std::string &key);
    void add(pointer v);
    bool contains(const std::string &key) const;
    pointer value(const std::string &key) const;
    template<typename T>
    T valueT(const std::string &key) const
    {
        pointer ptr = value(key);
        return dynamic_cast<T>(ptr);
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
        return _entries.begin();
    }
    const_iterator end() const
    {
        return _entries.end();
    }
    void createDefaultEntries();
    std::vector<std::string> defaultEntries() const;

protected:
    void addHandlePrefix(pointer v);
    void push_back(const std::string &n, pointer v);
    virtual TableEntry *createEntry(const std::string &name) = 0;

private:
    std::string createName() const;
    void onEntryNameChanged(const std::string &oldname, const std::string &newname);

private:
    std::map<std::string, pointer> _entries;
};

}// namespace dwg
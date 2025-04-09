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
#include <dwg/utils/Delegate.h>
#include <map>
#include <string>
#include <vector>

namespace dwg {

class TableEntry;
class CadDocument;

class LIBDWG_API TableCollection : public CadObject
{
public:
    using iterator = typename std::map<std::string, TableEntry *>::iterator;
    using const_iterator = typename std::map<std::string, TableEntry *>::const_iterator;

    TableCollection() = default;
    TableCollection(CadDocument *document);
    virtual ~TableCollection();
    size_t count() const;

    std::string objectName() const override;
    std::string subclassMarker() const override;

    TableEntry *operator[](const std::string &key) const;
    virtual void add(TableEntry *entry);
    bool contains(const std::string &key) const;
    TableEntry *value(const std::string &key) const;

    template<class T>
    T *valueT(const std::string &key) const
    {
        TableEntry *t = value(key);
        if (!t)
            return nullptr;
        return dynamic_cast<T *>(t);
    }

    void createDefaultEntries();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    Delegate<void(CadObject *)> OnAdd;
    Delegate<void(CadObject *)> OnRemove;

protected:
    void addPrivate(const std::string &key, TableEntry *item);
    void addHandlePrefix(TableEntry *item);
    virtual std::vector<std::string> defaultEntries() const;
    virtual bool assertType(TableEntry *item) const;
    virtual TableEntry *createEntry(const std::string &name) = 0;

private:
    std::string createName() const;
    void onEntryNameChanged(const std::string &oldname, const std::string &newname);

protected:
    std::map<std::string, TableEntry *> _entries;
};

}// namespace dwg
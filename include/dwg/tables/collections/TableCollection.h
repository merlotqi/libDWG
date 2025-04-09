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
#include <map>
#include <string>
#include <vector>

namespace dwg {

class TableEntry;
class CadDocument;

class LIBDWG_API TableCollection : public CadObject
{
public:
    using pointer = TableEntry *;
    using iterator = typename std::map<std::string, pointer>::iterator;
    using const_iterator = typename std::map<std::string, pointer>::const_iterator;

    TableCollection() = default;
    TableCollection(CadDocument *document);
    virtual ~TableCollection();
    size_t count() const;
    
    std::string objectName() const override;
    std::string subclassMarker() const override;

    pointer operator[](const std::string &key) const;
    void add(pointer entry);
    bool contains(const std::string &key) const;
    pointer getValue(const std::string &key) const;
    void createDefaultEntries();

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

protected:
    void add(const std::string &key, pointer item);
    virtual std::vector<std::string> defaultEntries() const;
    virtual bool assertType(pointer item) const;

private:
    std::string createName() const;

private:
    std::map<std::string, pointer> _entries;
};

}// namespace dwg
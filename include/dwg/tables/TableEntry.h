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
#include <dwg/INamedCadObject.h>
#include <dwg/exports.h>
#include <dwg/tables/StandardFlags.h>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

namespace dwg {
namespace tables {


class TableEntry : public CadObject, INamedCadObject
{
protected:
    std::string m_Name;
    TableEntry();

public:
    TableEntry(const std::string &name);

    std::string SubclassMarker() const;

    virtual std::string Name() const;
    void Name(const std::string name);
    StandardFlags Flags() const;
    void Flags(StandardFlags flags);
};


template<typename T>
class Table : public CadObject
{
    std::map<std::string, T> m_entries;

public:
    Table();
    std::string ObjectName() const override { return DxfFileToken::TableEntry; }
    void Add(const T &entry)
    {
        if (m_entries.find(entry.Name()) != m_entries.end()) return;
        m_entries[entry.Name()] = entry;
    }
};


}// namespace tables
}// namespace dwg

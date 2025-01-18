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

#include <assert.h>
#include <dwg/CadObject.h>
#include <dwg/DxfFileToken.h>
#include <dwg/DxfSubclassMarker.h>
#include <dwg/INamedCadObject.h>
#include <dwg/exports.h>
#include <dwg/tables/StandardFlags.h>

namespace dwg {

class LIBDWG_API TableEntry : public CadObject, INamedCadObject
{
public:
    TableEntry(const CPL::String &name);
    ~TableEntry();
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

class Table : public CadObject
{
    std::map<CPL::String, TableEntryPtr> _entries;

public:
    Table();
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;
    TableEntryPtr operator[](const CPL::String &key) const;
    void Add(TableEntry *entry);
    bool Contains(const CPL::String &key);
    TableEntryPtr GetValue(const CPL::String &key);
    void CreateDefaultEntries();

protected:
    void add(const CPL::String &key, TableEntry *item);
    void addHandlePrefix(TableEntry *item);
    virtual std::vector<CPL::String> defaultEntries() const = 0;
};
CPL_SMARTER_PTR(Table)


}// namespace dwg

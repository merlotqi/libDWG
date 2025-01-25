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

class LIBDWG_API DG_TableEntry : public DG_CadObject, DG_INamedCadObject
{
public:
    DG_TableEntry(const char *name);

    virtual ~DG_TableEntry();

    CPL::String SubclassMarker() const override;

    virtual CPL::String Name() const;

    virtual void Name(const char *value);

    DG_StandardFlags Flags() const;

    void Flags(DG_StandardFlags flags);

protected:
    DG_TableEntry();

protected:
    DG_StandardFlags _flags;
    CPL::String _name;
};
CPL_SMARTER_PTR(DG_TableEntry)

class LIBDWG_API DG_Table : public DG_CadObject
{
    std::map<CPL::String, DG_TableEntryPtr> _entries;

public:
    DG_Table();
    
    CPL::String ObjectName() const override;
    
    CPL::String SubclassMarker() const override;
    
    DG_TableEntryPtr operator[](const char *key) const;
    
    void Add(DG_TableEntry *entry);
    
    bool Contains(const char *key);
    
    DG_TableEntryPtr GetValue(const char *key);
    
    void CreateDefaultEntries();

protected:
    void add(const char *key, DG_TableEntry *item);
    
    void addHandlePrefix(DG_TableEntry *item);
    
    virtual std::vector<CPL::String> defaultEntries() const = 0;
};
CPL_SMARTER_PTR(DG_Table)

}// namespace dwg

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

#include <dwg/CadObjectCollection.h>
#include <dwg/blocks/BlockTypeFlags.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/units/UnitsType.h>

namespace dwg {

class LIBDWG_API DG_BlockRecord : public DG_TableEntry
{
public:
    DG_BlockRecord(const char *name) : DG_TableEntry(name) {}

    static constexpr auto ModelSpaceName = "*Model_Space";
    static constexpr auto PaperSpaceName = "*Paper_Space";

    static CPL::SmarterPtr<DG_BlockRecord> ModelSpace();

    static CPL::SmarterPtr<DG_BlockRecord> PaperSpace();

    DG_ObjectType ObjectType() const override;

    CPL::String ObjectName() const override;

    CPL::String SubclassMarker() const override;
};
CPL_SMARTER_PTR(DG_BlockRecord)

class LIBDWG_API DG_BlockRecordsTable : public DG_Table
{
public:
    DG_ObjectType ObjectType() const override;

protected:
    std::vector<CPL::String> defaultEntries() const;
};

}// namespace dwg

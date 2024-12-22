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
#include <dwg/blocks/Block.h>
#include <dwg/blocks/BlockEnd.h>
#include <dwg/entities/Viewport.h>
#include <dwg/enums/blocks/BlockTypeFlags.h>
#include <dwg/enums/units/UnitsType.h>
#include <dwg/objects/Layout.h>
#include <dwg/tables/TableEntry.h>

namespace dwg {
namespace tables {

class BlockRecord : public TableEntry
{
public:
    BlockRecord(const std::string &name) : TableEntry(name) {}

    static constexpr auto ModelSpaceName = "*Model_Space";
    static constexpr auto PaperSpaceName = "*Paper_Space";

    static BlockRecord *ModelSpace()
    {
        BlockRecord *record = new BlockRecord(ModelSpaceName);
        // objects::Layout *layout = new objects::Layout();
        // layout->Name = Layout::ModelLayoutName;
        // layout->AssociatedBlock(record);
        return record;
    }

    static BlockRecord *PaperSpace()
    {
        BlockRecord *record = new BlockRecord(PaperSpaceName);
        // objects::Layout *layout = new objects::Layout();
        // layout->Name = Layout::PaperLayoutName;
        // layot->AssociatedBlock(record);
        return record;
    }

    dwg::ObjectType ObjectType() const override
    {
        return ObjectType::BLOCK_HEADER;
    }
    std::string ObjectName() const override
    {
        return DxfFileToken::TableBlockRecord;
    }
    std::string SubclassMarker() const override
    {
        return DxfSubclassMarker::BlockRecord;
    }

    units::UnitsType Units;

    blocks::BlockTypeFlags Flags;

    bool IsExplodable;                 // 280
    bool CanScale;                     // 281
    std::vector<unsigned char> Preview;// 310
    objects::Layout *Layout;           // handle 340
    unsigned long long LayoutHandle;   // 340

    bool HasAttributes;
    std::vector<entities::Viewport> Viewports;
    CadObjectCollection<entities::Entity *> Entities;

    blocks::Block BlockEntity;
    blocks::BlockEnd BlockEnd;
};

class BlockRecordsTable : public Table<BlockRecord>
{
public:
    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::APPID_CONTROL_OBJ;
    }

protected:
    std::vector<std::string> defaultEntries() const
    {
        return {BlockRecord::ModelSpaceName, BlockRecord::PaperSpaceName};
    }
};

}// namespace tables
}// namespace dwg

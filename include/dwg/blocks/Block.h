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

#include <dwg/entities/Entity.h>
#include <dwg/enums/blocks/BlockTypeFlags.h>
#include <dwg/tables/BlockRecord.h>

namespace dwg {
namespace blocks {

class Block : public entities::Entity
{
public:
    Block();
    virtual ~Block();

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::BLOCK;
    }
    std::string ObjectName() const override { return DxfFileToken::Block; }
    std::string SubclassMarker() const override
    {
        return DxfSubclassMarker::BlockBegin;
    }

    tables::BlockRecord *BlockRecord() const;
    std::string Name;         // 2, 3
    BlockTypeFlags Flags;     // 70
    XYZ BasePoint = XYZ::Zero;// 10, 20, 30
    std::string XrefPath;     // 1
    std::string Comments;     // 4

    Block(tables::BlockRecord *record) {}
};


}// namespace blocks
}// namespace dwg
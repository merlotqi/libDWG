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

#include <dwg/blocks/Block.h>
#include <dwg/tables/BlockRecord.h>

namespace dwg {

DG_Block::DG_Block(DG_BlockRecord *record) { _owner = record; }

DG_Block::DG_Block() {}

DG_Block::~DG_Block() {}

DG_ObjectType DG_Block::ObjectType() const { return DG_ObjectType::BLOCK; }

std::string DG_Block::ObjectName() const { return DG_DxfFileToken::Block; }

std::string DG_Block::SubclassMarker() const
{
    return DG_DxfSubclassMarker::BlockBegin;
}

DG_BlockRecord *DG_Block::BlockRecord() const
{
    return dynamic_cast<DG_BlockRecord *>(_owner);
}

std::string DG_Block::Name() const { return _name; }

void DG_Block::Name(const std::string &name) { _name = name; }

DG_BlockTypeFlags DG_Block::Flags() const { return _flags; }

void DG_Block::Flags(DG_BlockTypeFlags flags) { _flags = flags; }

XYZ DG_Block::BasePoint() const { return _base_point; }

void DG_Block::BasePoint(const XYZ &value) { _base_point = value; }

std::string DG_Block::XrefPath() const { return _xrefPath; }

void DG_Block::XrefPath(const std::string &value) { _xrefPath = value; }

std::string DG_Block::Comments() const { return _comments; }

void DG_Block::Comments(const std::string &value) { _comments = value; }

}// namespace dwg
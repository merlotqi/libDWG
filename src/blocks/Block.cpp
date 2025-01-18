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

Block::Block(BlockRecord *record) { _owner = record; }

Block::Block() {}

Block::~Block() {}

dwg::ObjectType Block::ObjectType() const { return dwg::ObjectType::BLOCK; }

CPL::String Block::ObjectName() const { return DxfFileToken::Block; }

CPL::String Block::SubclassMarker() const
{
    return DxfSubclassMarker::BlockBegin;
}

BlockRecordPtr Block::BlockRecord() const
{
    return dynamic_cast<BlockRecord *>(_owner);
}

CPL::String Block::Name() const { return _name; }

void Block::Name(const CPL::String &name) { _name = name; }

BlockTypeFlags Block::Flags() const { return _flags; }

void Block::Flags(BlockTypeFlags flags) { _flags = flags; }

XYZ Block::BasePoint() const { return _base_point; }

void Block::BasePoint(XYZ p) { _base_point = p; }

CPL::String Block::XrefPath() const { return _xrefPath; }

void Block::XrefPath(const CPL::String &value) { _xrefPath = value; }

CPL::String Block::Comments() const { return _comments; }

void Block::Comments(const CPL::String &value) { _comments = value; }

}// namespace dwg
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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/blocks/Block.h>
#include <dwg/tables/BlockRecord.h>


namespace dwg {

Block::Block(BlockRecord *record)
{
    _owner = record;
}

Block::Block() {}

Block::~Block() {}

ObjectType Block::objectType() const
{
    return ObjectType::BLOCK;
}

std::string Block::objectName() const
{
    return DxfFileToken::Block;
}

std::string Block::subclassMarker() const
{
    return DxfSubclassMarker::BlockBegin;
}

BlockRecord *Block::blockRecord() const
{
    return dynamic_cast<BlockRecord *>(_owner);
}

std::string Block::name() const
{
    return _name;
}

void Block::setName(const std::string &name)
{
    _name = name;
}

BlockTypeFlags Block::flags() const
{
    return _flags;
}

void Block::setFlags(BlockTypeFlags flags)
{
    _flags = flags;
}

XYZ Block::basePoint() const
{
    return _base_point;
}

void Block::setBasePoint(const XYZ &value)
{
    _base_point = value;
}

std::string Block::xrefPath() const
{
    return _xrefPath;
}

void Block::setXrefPath(const std::string &value)
{
    _xrefPath = value;
}

std::string Block::comments() const
{
    return _comments;
}

void Block::setComments(const std::string &value)
{
    _comments = value;
}

}// namespace dwg
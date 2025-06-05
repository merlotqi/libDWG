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
#include <dwg/objects/SortEntitiesTable.h>

namespace dwg {

SortEntitiesTable::Sorter::Sorter(Entity *_entity, unsigned long long _handle) : entity(_entity), handle(_handle) {}

    SortEntitiesTable::SortEntitiesTable() {}
    
    SortEntitiesTable::SortEntitiesTable(BlockRecord *owner) : _blockOwner(owner) {}
    
    SortEntitiesTable::~SortEntitiesTable() {}

    ObjectType SortEntitiesTable::objectType() const { return ObjectType::UNLISTED; }

    std::string SortEntitiesTable::objectName() const { return DxfFileToken::ObjectSortEntsTable; }
    
    std::string SortEntitiesTable::subclassMarker() const { return DxfSubclassMarker::SortentsTable; }

    BlockRecord *SortEntitiesTable::blockOwner() const { return _blockOwner; }
    
    void SortEntitiesTable::setBlockOwner(BlockRecord *value) { _blockOwner = value; }

    std::vector<SortEntitiesTable::Sorter> SortEntitiesTable::sorters() const { return _sorters; }
    
    void SortEntitiesTable::setAddEntity(Entity *, unsigned long long sorterHandle) {}

}// namespace dwg
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
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/tables/BlockRecord.h>
#include <vector>

namespace dwg {
namespace objects {

class SortEntitiesTable : NonGraphicalObject
{
public:
    struct Sorter
    {
        entities::Entity *Entity;
        unsigned long long _handle;
        Sorter(entities::Entity *entity, unsigned long long handle)
        {
            Entity = entity;
            _handle = handle;
        }
    };

    static constexpr auto DictionaryEntryName = "ACAD_SORTENTS";


    dwg::ObjectType ObjectType() const { return ObjectType::UNLISTED; }
    std::string ObjectName() const { return DxfFileToken::ObjectSortEntsTable; }
    std::string SubclassMarker() const
    {
        return DxfSubclassMarker::SortentsTable;
    }

    // (330)]
    tables::BlockRecord BlockOwner;


    std::vector<Sorter> Sorters;
};

}// namespace objects
}// namespace dwg
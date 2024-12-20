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

#include <dwg/CadObject.h>
#include <dwg/entities/Entity.h>
#include <dwg/utils/Coordinate.h>
#include <vector>

namespace dwg {
namespace objects {


class BlockVisibilityParameter : public CadObject
{
public:
    BlockVisibilityParameter();
    dwg::ObjectType ObjectType() const { return ObjectType::UNLISTED; }
    std::string ObjectName() const
    {
        return DxfFileToken::ObjectBlockVisibilityParameter;
    }
    std::string SubclassMarker() const
    {
        return DxfSubclassMarker::BlockVisibilityParameter;
    }


    struct SubBlock
    {
        std::string Name;
        std::vector<entities::Entity *> Entities;
    };

    std::vector<entities::Entity *> Entities;
    std::vector<SubBlock> SubBlocks;
    // 1010, 1020, 1030
    XYZ BasePosition;
    // 300
    std::string ParameterType;
    // 301
    std::string Name;
    // 302
    std::string Description;
    // 91
    int L91;
};

}// namespace objects
}// namespace dwg
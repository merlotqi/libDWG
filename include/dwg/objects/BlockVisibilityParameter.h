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
#include <dwg/Coordinate.h>
#include <dwg/entities/Entity.h>
#include <vector>

namespace dwg {


class DG_BlockVisibilityParameter : public DG_CadObject
{
public:
    DG_BlockVisibilityParameter();
    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;
    struct DG_SubBlock
    {
        CPL::String Name;
        std::vector<DG_Entity *> Entities;
    };

    std::vector<DG_Entity *> Entities;
    std::vector<DG_SubBlock> SubBlocks;
    // 1010, 1020, 1030
    XYZ BasePosition;
    // 300
    CPL::String ParameterType;
    // 301
    CPL::String Name;
    // 302
    CPL::String Description;
    // 91
    int L91;
};

}// namespace dwg
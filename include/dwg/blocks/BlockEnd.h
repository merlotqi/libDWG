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

namespace dwg {

class BlockRecord;
class LIBDWG_API BlockEnd : public Entity
{
public:
    // Constructor accepting a BlockRecord pointer
    BlockEnd(BlockRecord *record);

    // Default destructor (since no specific cleanup is needed)
    ~BlockEnd() = default;

    // Overrides the ObjectName method to return the name of the object
    std::string objectName() const override;

    // Overrides the ObjectType method to return the type of object
    ObjectType objectType() const override;

    // Overrides the SubclassMarker method to return the subclass marker
    std::string subclassMarker() const override;
};

}// namespace dwg
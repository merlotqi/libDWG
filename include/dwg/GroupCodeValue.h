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

#include <dwg/GroupCodeValueType.h>
#include <dwg/exports.h>


namespace dwg {

/**
 * @brief Represents a value associated with a group code in the DWG format.
 * 
 * This class provides a static method to transform an integer code into a
 * corresponding `DG_GroupCodeValueType`.
 */
class LIBDWG_API GroupCodeValue
{
public:
    /**
     * @brief Transforms an integer group code into a corresponding `DG_GroupCodeValueType`.
     * 
     * This static method maps a given group code (integer) to the appropriate
     * `DG_GroupCodeValueType`.
     * 
     * @param code The group code to be transformed.
     * @return The corresponding `DG_GroupCodeValueType`.
     */
    static GroupCodeValueType transformValue(int code);
};


}// namespace dwg
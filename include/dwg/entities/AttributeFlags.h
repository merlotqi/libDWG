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

#include <cpl_ports.h>

namespace dwg {

/**
 * @enum DG_AttributeFlag
 * @brief Defines the flags for attributes in a DWG/DXF drawing.
 *
 * The flags specify various attributes of an attribute entity, such as visibility,
 * constant value, verification requirements, and preset status.
 */
enum DG_AttributeFlag
{
    None = 0,    ///< No flags.
    Hidden = 1,  ///< Attribute is hidden.
    Constant = 2,///< Attribute is constant.
    Verify = 4,  ///< Attribute requires verification on input.
    Preset = 8   ///< Attribute is preset, no user prompt.
};

/**
 * @typedef DG_AttributeFlags
 * @brief Represents a set of flags that can be applied to an attribute entity.
 *
 * This type is a bitmask representing multiple `DG_AttributeFlag` values, allowing
 * for efficient storage and manipulation of attribute properties in a single variable.
 */
CPL_DECLARE_FLAGS(DG_AttributeFlags, DG_AttributeFlag)


}// namespace dwg

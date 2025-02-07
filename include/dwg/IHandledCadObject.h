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

namespace dwg {

/**
 * @brief Interface for CAD objects that have a handle.
 * 
 * This class provides a mechanism to retrieve the handle of a CAD object.
 */
class IHandledCadObject
{
public:
    /**
     * @brief Default constructor.
     */
    IHandledCadObject() = default;

    /**
     * @brief Virtual destructor with no exception guarantee.
     */
    virtual ~IHandledCadObject() noexcept {}

    /**
     * @brief Gets the handle of the CAD object.
     * @return The handle of the object as an unsigned long long.
     */
    virtual unsigned long long handle() const = 0;
};

}// namespace dwg

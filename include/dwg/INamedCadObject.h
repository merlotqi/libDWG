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

#include <functional>
#include <string>

namespace dwg {

/**
 * @brief Interface for CAD objects with a name property.
 * 
 * This class provides a mechanism to get the name of a CAD object
 * and a delegate for name change notifications.
 */
class INamedCadObject
{
public:
    /**
     * @brief Default constructor.
     */
    INamedCadObject() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~INamedCadObject() {}

    /**
     * @brief Gets the name of the CAD object.
     * @return The name of the object as a string.
     */
    virtual std::string name() const = 0;

    /**
     * @brief Event triggered when the object's name changes.
     * 
     * This delegate is invoked with the old and new names when the name is updated.
     */
    std::function<void(const std::string &, const std::string &)> OnNameChanged;
};

}// namespace dwg

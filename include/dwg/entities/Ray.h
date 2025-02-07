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

/**
 * @class DG_Ray
 * @brief Represents a ray entity in a DWG/DXF drawing.
 *
 * A ray is a linear infinite construction line that starts at a point and extends in a specified direction.
 * It inherits from DG_Entity and contains a start point and a direction vector.
 */
class LIBDWG_API DG_Ray : public DG_Entity
{
    XYZ _startPoint;///< The starting point of the ray.
    XYZ _direction; ///< The direction vector of the ray.

public:
    /**
     * @brief Constructs a DG_Ray object with default values.
     */
    DG_Ray();

    /**
     * @brief Destroys the DG_Ray object.
     */
    ~DG_Ray();

    /**
     * @brief Gets the object type of the ray.
     * @return The object type as DG_ObjectType.
     */
    virtual DG_ObjectType objectType() const override;

    /**
     * @brief Gets the name of the ray object.
     * @return The object name as a string.
     */
    virtual std::string objectName() const override;

    /**
     * @brief Gets the subclass marker associated with this ray.
     * @return The subclass marker as a string.
     */
    virtual std::string subclassMarker() const override;

    /**
     * @brief Gets the start point of the ray.
     * @return The start point as an XYZ object.
     */
    XYZ StartPoint() const;

    /**
     * @brief Sets the start point of the ray.
     * @param point The new start point.
     */
    void StartPoint(const XYZ &point);

    /**
     * @brief Gets the direction vector of the ray.
     * @return The direction vector as an XYZ object.
     */
    XYZ Direction() const;

    /**
     * @brief Sets the direction vector of the ray.
     * @param direction The new direction vector.
     */
    void Direction(const XYZ &direction);
};

}// namespace dwg

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

#include <dwg/entities/Circle.h>

namespace dwg {

/**
 * @class DG_Arc
 * @brief Represents an arc entity in a DWG/DXF drawing.
 *
 * An arc is a portion of a circle defined by a start angle and an end angle.
 * It inherits from DG_Circle, sharing properties such as center, radius, and normal.
 */
class LIBDWG_API DG_Arc : public DG_Circle
{
    /// Start angle of the arc (in degrees)
    double _startangle;

    /// End angle of the arc (in degrees)
    double _endangle;

public:
    /**
     * @brief Default constructor.
     */
    DG_Arc();

    /**
     * @brief Destructor.
     */
    ~DG_Arc();

    /**
     * @brief Gets the object type of this entity.
     * @return The object type identifier.
     */
    virtual DG_ObjectType ObjectType() const override;

    /**
     * @brief Gets the name of this object.
     * @return The object name as a string.
     */
    virtual std::string ObjectName() const override;

    /**
     * @brief Gets the subclass marker for this object.
     * @return The subclass marker string.
     */
    virtual std::string SubclassMarker() const override;

    /**
     * @brief Gets the start angle of the arc.
     * @return The start angle in degrees.
     */
    double StartAngle() const;

    /**
     * @brief Gets the end angle of the arc.
     * @return The end angle in degrees.
     */
    double EndAngle() const;

    /**
     * @brief Sets the start angle of the arc.
     * @param angle The new start angle in degrees.
     */
    void StartAngle(double angle);

    /**
     * @brief Sets the end angle of the arc.
     * @param angle The new end angle in degrees.
     */
    void EndAngle(double angle);
};

}// namespace dwg

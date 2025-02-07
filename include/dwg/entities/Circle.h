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
 * @class Circle
 * @brief Represents a circle entity in a DWG/DXF drawing.
 *
 * Circle is a class that represents a circle in a CAD drawing. It is derived from 
 * DG_Entity and provides the necessary functionality to handle the properties of a circle, 
 * such as its center, radius, and any transformations that may be applied. Circles are 
 * fundamental geometric entities in CAD systems and are used to represent circular shapes.
 */
class LIBDWG_API Circle : public DG_Entity
{
    /// The center of the circle (in 3D space).
    XYZ _center;

    /// The normal vector to the plane of the circle (default is the Z-axis).
    XYZ _normal;

    /// The thickness of the circle (for 3D circles or discs).
    double _thickness;

    /// The radius of the circle.
    double _radius;

public:
    /**
     * @brief Default constructor.
     */
    Circle();

    /**
     * @brief Destructor.
     */
    virtual ~Circle();

    /**
     * @brief Gets the object type of the circle.
     * @return The object type.
     */
    virtual DG_ObjectType objectType() const override;

    /**
     * @brief Gets the name of the object.
     * @return The object name.
     */
    virtual std::string objectName() const override;

    /**
     * @brief Gets the subclass marker associated with this object.
     * @return The subclass marker.
     */
    virtual std::string subclassMarker() const override;

    /**
     * @brief Gets the normal vector of the circle's plane.
     * @return The normal vector.
     */
    XYZ normal() const;

    /**
     * @brief Gets the center of the circle.
     * @return The center point.
     */
    XYZ center() const;

    /**
     * @brief Gets the thickness of the circle.
     * @return The thickness value.
     */
    double thickness() const;

    /**
     * @brief Gets the radius of the circle.
     * @return The radius value.
     */
    double radius() const;

    /**
     * @brief Sets the normal vector of the circle's plane.
     * @param normal The new normal vector.
     */
    void setNormal(const XYZ &normal);

    /**
     * @brief Sets the center of the circle.
     * @param center The new center point.
     */
    void setCenter(const XYZ &center);

    /**
     * @brief Sets the thickness of the circle.
     * @param thickness The new thickness value.
     */
    void setThickness(double thickness);

    /**
     * @brief Sets the radius of the circle.
     * @param radius The new radius value.
     */
    void setRadius(double radius);
};

}// namespace dwg

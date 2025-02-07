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
 * @class Line
 * @brief Represents a line entity in a DWG/DXF drawing.
 *
 * A line is a straight segment defined by a start point and an end point.
 * It can have a thickness and is positioned in 3D space with a normal vector.
 */
class LIBDWG_API Line : public Entity
{
    XYZ _normal = XYZ::AxisZ;   ///< Normal vector defining the plane of the line.
    XYZ _startPoint = XYZ::Zero;///< Start point of the line.
    XYZ _endPoint = XYZ::Zero;  ///< End point of the line.
    double _thickness = 0.0;    ///< Thickness of the line.

public:
    /**
     * @brief Constructs a Line object.
     */
    Line();

    /**
     * @brief Destroys the Line object.
     */
    ~Line();

    /**
     * @brief Returns the object type of the line.
     * @return The object type as ObjectType.
     */
    ObjectType objectType() const override;

    /**
     * @brief Returns the name of the object.
     * @return The name as a string.
     */
    std::string objectName() const override;

    /**
     * @brief Returns the subclass marker associated with this object.
     * @return The subclass marker as a string.
     */
    std::string subclassMarker() const override;

    /**
     * @brief Gets the normal vector of the line.
     * @return The normal vector as XYZ.
     */
    XYZ normal() const;

    /**
     * @brief Sets the normal vector of the line.
     * @param normal The normal vector as XYZ.
     */
    void setNormal(const XYZ &normal);

    /**
     * @brief Gets the start point of the line.
     * @return The start point as XYZ.
     */
    XYZ startPoint() const;

    /**
     * @brief Sets the start point of the line.
     * @param point The start point as XYZ.
     */
    void setStartPoint(const XYZ &point);

    /**
     * @brief Gets the end point of the line.
     * @return The end point as XYZ.
     */
    XYZ endPoint() const;

    /**
     * @brief Sets the end point of the line.
     * @param point The end point as XYZ.
     */
    void setEndPoint(const XYZ &point);

    /**
     * @brief Gets the thickness of the line.
     * @return The thickness as a double.
     */
    double thickness() const;

    /**
     * @brief Sets the thickness of the line.
     * @param thickness The thickness as a double.
     */
    void setThickness(double thickness);
};

}// namespace dwg

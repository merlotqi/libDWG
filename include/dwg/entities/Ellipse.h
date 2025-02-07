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
 * @class Ellipse
 * @brief Represents an ellipse entity in a DWG/DXF drawing.
 *
 * The Ellipse class defines an ellipse with properties such as center, normal vector, radius ratio,
 * start and end parameters, and thickness. This class allows manipulation of ellipse geometries in a DWG/DXF drawing.
 */
class LIBDWG_API Ellipse : public Entity
{
    XYZ _normal;           ///< The normal vector of the ellipse (default is Z-axis)
    XYZ _center;           ///< The center point of the ellipse (default is the origin)
    XYZ _endPoint;         ///< A point on the ellipse (default is on the X-axis)
    double _radiusRatio;   ///< The ratio of the radii (default is 0)
    double _startParameter;///< The start parameter for the ellipse (default is 0)
    double _endParameter;  ///< The end parameter for the ellipse (default is 2π)
    double _thickness;     ///< The thickness of the ellipse (default is 0)

public:
    /**
     * @brief Default constructor
     *
     * Initializes an ellipse with default values (center at origin, normal along Z-axis, and other default properties).
     */
    Ellipse();

    /**
     * @brief Destructor
     */
    ~Ellipse();

    /**
     * @brief Get the object type of the ellipse
     * 
     * @return ObjectType The object type of the ellipse.
     */
    ObjectType objectType() const override;

    /**
     * @brief Get the object name of the ellipse
     * 
     * @return std::string The name of the ellipse object.
     */
    std::string objectName() const override;

    /**
     * @brief Get the subclass marker of the ellipse
     * 
     * @return std::string The subclass marker associated with the ellipse.
     */
    std::string subclassMarker() const override;

    /**
     * @brief Get the normal vector of the ellipse
     * 
     * @return XYZ The normal vector of the ellipse.
     */
    XYZ normal() const;

    /**
     * @brief Get the center of the ellipse
     * 
     * @return XYZ The center of the ellipse.
     */
    XYZ center() const;

    /**
     * @brief Get a point on the ellipse
     * 
     * @return XYZ A point on the ellipse.
     */
    XYZ endPoint() const;

    /**
     * @brief Get the thickness of the ellipse
     * 
     * @return double The thickness of the ellipse.
     */
    double thickness() const;

    /**
     * @brief Get the radius ratio of the ellipse
     * 
     * @return double The radius ratio of the ellipse.
     */
    double radiusRatio() const;

    /**
     * @brief Get the start parameter of the ellipse
     * 
     * @return double The start parameter of the ellipse.
     */
    double startParameter() const;

    /**
     * @brief Get the end parameter of the ellipse
     * 
     * @return double The end parameter of the ellipse.
     */
    double endParameter() const;

    /**
     * @brief Set the normal vector of the ellipse
     * 
     * @param normal The normal vector to set for the ellipse.
     */
    void setNormal(const XYZ &normal);

    /**
     * @brief Set the center of the ellipse
     * 
     * @param center The center point to set for the ellipse.
     */
    void setCenter(const XYZ &center);

    /**
     * @brief Set a point on the ellipse
     * 
     * @param endPoint The point to set on the ellipse.
     */
    void setEndPoint(const XYZ &endPoint);

    /**
     * @brief Set the thickness of the ellipse
     * 
     * @param thickness The thickness to set for the ellipse.
     */
    void setThickness(double thickness);

    /**
     * @brief Set the radius ratio of the ellipse
     * 
     * @param radiusRatio The radius ratio to set for the ellipse.
     */
    void setRadiusRatio(double radiusRatio);

    /**
     * @brief Set the start parameter of the ellipse
     * 
     * @param startParam The start parameter to set for the ellipse.
     */
    void setStartParameter(double startParam);

    /**
     * @brief Set the end parameter of the ellipse
     * 
     * @param endParam The end parameter to set for the ellipse.
     */
    void setEndParameter(double endParam);
};

}// namespace dwg

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

class LIBDWG_API Ellipse : public Entity
{
    RTTR_ENABLE(Entity)

public:
    Ellipse();
    ~Ellipse();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    XYZ center() const;
    void setCenter(const XYZ &center);

    double endParameter() const;
    void setEndParameter(double endParam);

    XYZ endPoint() const;
    void setEndPoint(const XYZ &endPoint);

    bool isFullEllipse() const;

    double majorAxis() const;
    double minorAxis() const;

    XYZ normal() const;
    void setNormal(const XYZ &normal);

    double radiusRatio() const;
    void setRadiusRatio(double radiusRatio);

    double startParameter() const;
    void setStartParameter(double startParam);

    double thickness() const;
    void setThickness(double thickness);

private:
    XYZ _normal;           ///< The normal vector of the ellipse (default is Z-axis)
    XYZ _center;           ///< The center point of the ellipse (default is the origin)
    XYZ _endPoint;         ///< A point on the ellipse (default is on the X-axis)
    double _radiusRatio;   ///< The ratio of the radii (default is 0)
    double _startParameter;///< The start parameter for the ellipse (default is 0)
    double _endParameter;  ///< The end parameter for the ellipse (default is 2π)
    double _thickness;     ///< The thickness of the ellipse (default is 0)
};

}// namespace dwg
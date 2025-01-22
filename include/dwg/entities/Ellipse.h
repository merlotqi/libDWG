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
    XYZ _normal =
            XYZ::AxisZ;// The normal vector of the ellipse (default is Z-axis)
    XYZ _center =
            XYZ::Zero;// The center point of the ellipse (default is the origin)
    XYZ _endPoint =
            XYZ::AxisX;// A point on the ellipse (default is on the X-axis)
    double _radiusRatio = 0.0;// The ratio of the radii (default is 0)
    double _startParameter =
            0.0;// The start parameter for the ellipse (default is 0)
    double _endParameter =
            2 * M_PI;// The end parameter for the ellipse (default is 2π)

public:
    // Default constructor
    Ellipse();

    // Destructor
    ~Ellipse();

    // Get the object type of the ellipse
    dwg::ObjectType ObjectType() const override;

    // Get the object name of the ellipse
    CPL::String ObjectName() const override;

    // Get the subclass marker of the ellipse
    CPL::String SubclassMarker() const override;

    // Get the normal vector of the ellipse
    XYZ Normal() const;

    // Get the center of the ellipse
    XYZ Center() const;

    // Get a point on the ellipse
    XYZ EndPoint() const;

    // Get the thickness of the ellipse
    double Thickness() const;

    // Get the radius ratio of the ellipse
    double RadiusRatio() const;

    // Get the start parameter of the ellipse
    double StartParameter() const;

    // Get the end parameter of the ellipse
    double EndParameter() const;

    // Set the normal vector of the ellipse
    void Normal(const XYZ &);

    // Set the center of the ellipse
    void Center(const XYZ &);

    // Set a point on the ellipse
    void EndPoint(const XYZ &);

    // Set the thickness of the ellipse
    void Thickness(double);

    // Set the radius ratio of the ellipse
    void RadiusRatio(double);

    // Set the start parameter of the ellipse
    void StartParameter(double);

    // Set the end parameter of the ellipse
    void EndParameter(double);
};
CPL_SMARTER_PTR(Ellipse)

}// namespace dwg

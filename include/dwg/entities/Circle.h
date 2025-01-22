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

class LIBDWG_API Circle : public Entity
{
    // The center of the circle (in 3D space)
    XYZ _center = XYZ::Zero;

    // The normal vector to the plane of the circle (default is the Z-axis)
    XYZ _normal = XYZ::AxisZ;

    // The thickness of the circle (for 3D circles or discs)
    double _thickness = 0.0;

    // The radius of the circle
    double _radius = 1.0;

public:
    // Default constructor
    Circle();

    // Destructor
    virtual ~Circle();

    // Override to return the object type of the Circle
    virtual dwg::ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    // Getter for the normal vector
    XYZ Normal() const;

    // Getter for the center of the circle
    XYZ Center() const;

    // Getter for the thickness of the circle
    double Thickness() const;

    // Getter for the radius of the circle
    double Radius() const;

    // Setter for the normal vector
    void Normal(const XYZ &);

    // Setter for the center of the circle
    void Center(const XYZ &);

    // Setter for the thickness of the circle
    void Thickness(double);

    // Setter for the radius of the circle
    void Radius(double);
};

CPL_SMARTER_PTR(Circle)

}// namespace dwg

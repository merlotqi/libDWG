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

#include <dwg/entities/Dimension.h>

namespace dwg {

// The DG_DimensionAngular2Line class represents an angular dimension between two lines
// defined by three points: two points on the lines and the vertex at the angle.
class LIBDWG_API DG_DimensionAngular2Line : public DG_Dimension
{
    XYZ _firstPoint;// The first point on the first line that defines the angle
    XYZ _secondPoint;// The second point on the second line that defines the angle
    XYZ _angleVertex; // The vertex where the two lines meet (angle vertex)
    XYZ _dimensionArc;// The arc that represents the angular dimension

public:
    // Default constructor for the DG_DimensionAngular2Line class
    DG_DimensionAngular2Line();

    // Destructor for the DG_DimensionAngular2Line class
    ~DG_DimensionAngular2Line();

    // Override to return the object type of the Circle
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual std::string ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string SubclassMarker() const override;

    // Getter and setter for the first point defining the angle
    XYZ FirstPoint() const;
    void FirstPoint(const XYZ &value);

    // Getter and setter for the second point defining the angle
    XYZ SecondPoint() const;
    void SecondPoint(const XYZ &value);

    // Getter and setter for the angle vertex (the point where the lines meet)
    XYZ AngleVertex() const;
    void AngleVertex(const XYZ &value);

    // Getter and setter for the dimension arc (the arc showing the angle)
    XYZ DimensionArc() const;
    void DimensionArc(const XYZ &value);

    // Override the Measurement method to calculate the angular dimension between the two lines
    virtual double Measurement() const override;
};

}// namespace dwg
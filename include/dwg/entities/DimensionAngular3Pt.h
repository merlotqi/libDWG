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

// The DimensionAngular3Pt class represents an angular dimension defined by three points:
// two points on the dimension lines and the vertex where the angle is formed.
class LIBDWG_API DimensionAngular3Pt : public Dimension
{
    XYZ _firstPoint;// The first point on the first line that defines the angle
    XYZ _secondPoint;// The second point on the second line that defines the angle
    XYZ _angleVertex;// The vertex where the two lines meet (angle vertex)

public:
    // Default constructor for the DimensionAngular3Pt class
    DimensionAngular3Pt();

    // Destructor for the DimensionAngular3Pt class
    ~DimensionAngular3Pt();

    // Getter and setter for the first point defining the angle
    XYZ FirstPoint() const;
    void FirstPoint(const XYZ &value);

    // Getter and setter for the second point defining the angle
    XYZ SecondPoint() const;
    void SecondPoint(const XYZ &value);

    // Getter and setter for the angle vertex (the point where the lines meet)
    XYZ AngleVertex() const;
    void AngleVertex(const XYZ &value);

    // Override the Measurement method to calculate the angular dimension between the two lines
    virtual double Measurement() const override;
};
CPL_SMARTER_PTR(DimensionAngular3Pt)

}// namespace dwg

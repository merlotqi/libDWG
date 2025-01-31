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
class LIBDWG_API DG_DimensionRadius : public DG_Dimension
{
    XYZ _angleVertex;// The vertex of the angle (used for radius dimension)
    double _leaderLength;// The length of the leader line (connection to the dimension line)

public:
    // Default constructor
    DG_DimensionRadius();

    // Destructor
    ~DG_DimensionRadius();

    // Override to return the object type of the Circle
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual std::string ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string SubclassMarker() const override;

    // Get the angle vertex value
    XYZ AngleVertex() const;

    // Set the angle vertex value
    void AngleVertex(const XYZ &value);

    // Get the leader length value
    double LeaderLength() const;

    // Set the leader length value
    void LeaderLength(double value);

    // Override the Measurement method to calculate and return the radius measurement
    virtual double Measurement() const override;
};

}// namespace dwg

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

class LIBDWG_API DimensionOrdinate : public Dimension
{
    XYZ _featureLocation;// The location of the feature being dimensioned (typically a coordinate)
    XYZ _leaderEndpoint; // The endpoint of the leader line (connection point for the dimension)

public:
    // Default constructor
    DimensionOrdinate();

    // Destructor
    ~DimensionOrdinate();

    // Override to return the object type of the Circle
    virtual ObjectType objectType() const override;

    // Override to return the name of the object
    virtual std::string objectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string subclassMarker() const override;

    // Get the feature location (coordinate point of the feature)
    XYZ featureLocation() const;

    // Set the feature location (coordinate point of the feature)
    void setFeatureLocation(const XYZ &value);

    // Get the leader endpoint location
    XYZ leaderEndpoint() const;

    // Set the leader endpoint location
    void setLeaderEndpoint(const XYZ &value);

    // Override the Measurement method to calculate and return the ordinate measurement
    virtual double measurement() const override;

    // Check if the ordinate type is X (for dimensioning along the X-axis)
    bool isOrdinateTypeX() const;

    // Set whether the ordinate type is X (for dimensioning along the X-axis)
    void setIsOrdinateTypeX(bool value);
};

}// namespace dwg

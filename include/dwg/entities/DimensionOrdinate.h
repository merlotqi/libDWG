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
    DimensionOrdinate();
    ~DimensionOrdinate();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    XYZ featureLocation() const;
    void setFeatureLocation(const XYZ &value);

    XYZ leaderEndpoint() const;
    void setLeaderEndpoint(const XYZ &value);

    bool isOrdinateTypeX() const;
    void setIsOrdinateTypeX(bool value);

    virtual double measurement() const override;
};

}// namespace dwg
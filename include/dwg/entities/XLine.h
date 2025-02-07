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

class LIBDWG_API DG_XLine : public DG_Entity
{
    XYZ _firstPoint;// The first point defining the DG_XLine.
    XYZ _direction; // The direction vector defining the DG_XLine.

public:
    // Default constructor for DG_XLine. Initializes the first point and direction.
    DG_XLine();

    // Destructor for DG_XLine.
    ~DG_XLine();

    // Overrides the ObjectType method to return the specific object type for DG_XLine.
    virtual DG_ObjectType objectType() const override;

    // Overrides the ObjectName method to return the name of the object (DG_XLine).
    virtual std::string objectName() const override;

    // Overrides the SubclassMarker method to return the subclass marker associated with DG_XLine.
    virtual std::string subclassMarker() const override;

    // Getter for the first point of the DG_XLine.
    XYZ FirstPoint() const;

    // Setter for the first point of the DG_XLine.
    void FirstPoint(const XYZ &);

    // Getter for the direction of the DG_XLine.
    XYZ Direction() const;

    // Setter for the direction of the DG_XLine.
    void Direction(const XYZ &);
};

}// namespace dwg

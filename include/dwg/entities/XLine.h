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

class LIBDWG_API XLine : public Entity
{
    XYZ _firstPoint;  // The first point defining the XLine.
    XYZ _direction;   // The direction vector defining the XLine.

public:
    // Default constructor for XLine. Initializes the first point and direction.
    XLine();

    // Destructor for XLine.
    ~XLine();

    // Overrides the ObjectType method to return the specific object type for XLine.
    virtual dwg::ObjectType ObjectType() const override;

    // Overrides the ObjectName method to return the name of the object (XLine).
    virtual CPL::String ObjectName() const override;

    // Overrides the SubclassMarker method to return the subclass marker associated with XLine.
    virtual CPL::String SubclassMarker() const override;

    // Getter for the first point of the XLine.
    XYZ FirstPoint() const;

    // Setter for the first point of the XLine.
    void FirstPoint(const XYZ &);

    // Getter for the direction of the XLine.
    XYZ Direction() const;

    // Setter for the direction of the XLine.
    void Direction(const XYZ &);
};
CPL_SMARTER_PTR(XLine)

}// namespace dwg

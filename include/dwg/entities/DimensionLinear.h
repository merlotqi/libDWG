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

#include <dwg/entities/DimensionAligned.h>

namespace dwg {

class LIBDWG_API DG_DimensionLinear : public DG_DimensionAligned
{
    double _rotation;// The rotation angle of the linear dimension (in degrees or radians)

public:
    // Default constructor
    DG_DimensionLinear();

    // Destructor
    ~DG_DimensionLinear();

    // Override to return the object type of the Circle
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    // Get the rotation angle value
    double Rotation() const;

    // Set the rotation angle value
    void SetRotation(double rotation);
};
CPL_SMARTER_PTR(DG_DimensionLinear)


}// namespace dwg

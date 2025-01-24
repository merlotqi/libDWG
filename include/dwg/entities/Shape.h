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

class TextStyle;
CPL_SMARTER_PTR(TextStyle)

class LIBDWG_API Shape : public Entity
{
public:
    Shape();

    ~Shape();

    // Override to return the object type of the Arc
    virtual dwg::ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    double Thickness() const;
    void Thickness(double);

    XYZ InsertPoint() const;
    void InsertPoint(const XYZ &);

    double Size() const;
    void Size(double);

    TextStylePtr ShapeStyle() const;
    void ShapeStyle(TextStyle *);

    double Rotation() const;
    void Rotation(double);

    double RelativeXScale() const;
    void RelativeXScale(double);

    double ObliqueAngle() const;
    void ObliqueAngle(double);

    XYZ Normal() const;
    void Normal(const XYZ &);

    unsigned short ShapeIndex() const;
    void ShapeIndex(unsigned short);
};
CPL_SMARTER_PTR(Shape)

}// namespace dwg

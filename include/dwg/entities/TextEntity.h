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
#include <dwg/entities/TextHorizontalAlignment.h>
#include <dwg/entities/TextMirrorFlag.h>
#include <dwg/entities/TextVerticalAlignmentType.h>


namespace dwg {

class LIBDWG_API TextEntity : public Entity
{
    double _thickness;
    XYZ _insertPoint;
    double _height;
    CPL::String _value;
    double _rotation;
    double _widthFactor;
    double _obliqueAngle;
    TextStyleWPtr _style;
    TextMirrorFlag _mirror;
    TextHorizontalAlignment _horizontalAlignment;
    XYZ _alignmentPoint;
    XYZ _normal;
    TextVerticalAlignmentType _verticalAlignment;

public:
    TextEntity();
    virtual ~TextEntity();

    // Override to return the object type of the Arc
    virtual dwg::ObjectType ObjectType() const;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const;

    double Thickness() const;
    void Thickness(double);

    XYZ InsertPoint() const;
    void InsertPoint(XYZ);

    double Height() const;
    void Height(double);

    CPL::String Value() const;
    void Value(const char *);

    double Rotation() const;
    void Rotation(double);

    double WidthFactor() const;
    void WidthFactor(double);

    double ObliqueAngle() const;
    void ObliqueAngle(double);

    TextStylePtr Style() const;
    void Style(TextStyle *);

    TextMirrorFlag Mirror() const;
    void Mirror(TextMirrorFlag);

    TextHorizontalAlignment HorizontalAlignment() const;
    void HorizontalAlignment(TextHorizontalAlignment);

    XYZ AlignmentPoint() const;
    void AlignmentPoint(const XYZ &);

    XYZ Normal() const;
    void Normal(const XYZ &);

    TextVerticalAlignmentType VerticalAlignment() const;
    void VerticalAlignment(TextVerticalAlignmentType);
};
CPL_SMARTER_PTR(TextEntity)

}// namespace dwg
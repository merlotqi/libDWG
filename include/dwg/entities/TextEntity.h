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
#include <dwg/entities/TextVerticalAlignment.h>


namespace dwg {

class DG_TextStyle;

class LIBDWG_API DG_TextEntity : public DG_Entity
{
    double _thickness;
    XYZ _insertPoint;
    double _height;
    std::string _value;
    double _rotation;
    double _widthFactor;
    double _obliqueAngle;
    DG_TextStyle* _style;
    DG_TextMirrorFlag _mirror;
    DG_TextHorizontalAlignment _horizontalAlignment;
    XYZ _alignmentPoint;
    XYZ _normal;
    DG_TextVerticalAlignment _verticalAlignment;

public:
    DG_TextEntity();
    virtual ~DG_TextEntity();

    // Override to return the object type of the Arc
    virtual DG_ObjectType objectType() const;

    // Override to return the name of the object
    virtual std::string objectName() const;

    // Override to return the subclass marker associated with this object
    virtual std::string subclassMarker() const;

    double Thickness() const;
    void Thickness(double);

    XYZ InsertPoint() const;
    void InsertPoint(XYZ);

    double Height() const;
    void Height(double);

    std::string Value() const;
    void Value(const std::string &);

    double Rotation() const;
    void Rotation(double);

    double WidthFactor() const;
    void WidthFactor(double);

    double ObliqueAngle() const;
    void ObliqueAngle(double);

    DG_TextStyle *Style() const;
    void Style(DG_TextStyle *);

    DG_TextMirrorFlag Mirror() const;
    void Mirror(DG_TextMirrorFlag);

    DG_TextHorizontalAlignment HorizontalAlignment() const;
    void HorizontalAlignment(DG_TextHorizontalAlignment);

    XYZ AlignmentPoint() const;
    void AlignmentPoint(const XYZ &);

    XYZ Normal() const;
    void Normal(const XYZ &);

    DG_TextVerticalAlignment VerticalAlignment() const;
    void VerticalAlignment(DG_TextVerticalAlignment);
};

}// namespace dwg
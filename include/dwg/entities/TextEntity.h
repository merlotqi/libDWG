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

class TextStyle;

class LIBDWG_API TextEntity : public Entity
{
public:
    TextEntity();
    virtual ~TextEntity();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    double thickness() const;
    void setThickness(double);

    XYZ insertPoint() const;
    void setInsertPoint(const XYZ &);

    double height() const;
    void setHeight(double);

    std::string value() const;
    void setValue(const std::string &);

    double rotation() const;
    void setRotation(double);

    double widthFactor() const;
    void setWidthFactor(double);

    double obliqueAngle() const;
    void setObliqueAngle(double);

    TextStyle *style() const;
    void setStyle(TextStyle *);

    TextMirrorFlag mirror() const;
    void setMirror(TextMirrorFlag);

    TextHorizontalAlignment horizontalAlignment() const;
    void setHorizontalAlignment(TextHorizontalAlignment);

    XYZ alignmentPoint() const;
    void setAlignmentPoint(const XYZ &);

    XYZ normal() const;
    void setNormal(const XYZ &);

    TextVerticalAlignment verticalAlignment() const;
    void setVerticalAlignment(TextVerticalAlignment);

    void assignDocument(CadDocument *doc) override;
    void unassignDocument() override;

private:
    double _thickness;
    XYZ _insertPoint;
    double _height;
    std::string _value;
    double _rotation;
    double _widthFactor;
    double _obliqueAngle;
    TextStyle *_style;
    TextMirrorFlag _mirror;
    TextHorizontalAlignment _horizontalAlignment;
    XYZ _alignmentPoint;
    XYZ _normal;
    TextVerticalAlignment _verticalAlignment;
};

}// namespace dwg
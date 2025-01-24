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
#include <dwg/entities/LeaderCreationType.h>
#include <dwg/entities/LeaderPathType.h>

namespace dwg {

class DimensionStyle;
CPL_SMARTER_PTR(DimensionStyle)

class LIBDWG_API Leader : public Entity
{
public:
    Leader();

    ~Leader();

    // Override to return the object type of the Arc
    virtual dwg::ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    DimensionStylePtr Style() const;
    void Style(DimensionStyle *);

    bool ArrowHeadEnabled() const;
    void ArrowHeadEnabled(bool);

    LeaderPathType PathType() const;
    void PathType(LeaderPathType);

    LeaderCreationType CreationType() const;
    void CreationType(LeaderCreationType);

    bool HookLineDirection() const;
    void HookLineDirection(bool);

    bool HasHookline() const;
    void HasHookline(bool);

    double TextHeight() const;
    void TextHeight(double);

    double TextWidth() const;
    void TextWidth(double);

    std::vector<XYZ> Vertices() const;
    void Vertices(const std::vector<XYZ> &);

    CPL::SmarterPtr<Entity> AssociatedAnnotation() const;
    void AssociatedAnnotation(Entity *);

    XYZ Normal() const;
    void Normal(const XYZ &);

    XYZ HorizontalDirection() const;
    void HorizontalDirection(const XYZ &);

    XYZ BlockOffset() const;
    void BlockOffset(const XYZ &);

    XYZ AnnotationOffset() const;
    void AnnotationOffset(const XYZ &);
};

}// namespace dwg

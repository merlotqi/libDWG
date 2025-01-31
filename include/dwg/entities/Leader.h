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

class DG_DimensionStyle;

class LIBDWG_API DG_Leader : public DG_Entity
{
public:
    DG_Leader();

    ~DG_Leader();

    // Override to return the object type of the Arc
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual std::string ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string SubclassMarker() const override;

    DG_DimensionStyle *Style() const;
    void Style(DG_DimensionStyle *);

    bool ArrowHeadEnabled() const;
    void ArrowHeadEnabled(bool);

    DG_LeaderPathType PathType() const;
    void PathType(DG_LeaderPathType);

    DG_LeaderCreationType CreationType() const;
    void CreationType(DG_LeaderCreationType);

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

    DG_Entity* AssociatedAnnotation() const;
    void AssociatedAnnotation(DG_Entity *);

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

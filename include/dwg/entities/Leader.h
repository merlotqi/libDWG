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
#include <dwg/entities/HookLineDirection.h>
#include <dwg/entities/LeaderCreationType.h>
#include <dwg/entities/LeaderPathType.h>

namespace dwg {

class DimensionStyle;

class LIBDWG_API Leader : public Entity
{
    RTTR_ENABLE(Entity)

public:
    Leader();
    ~Leader();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    DimensionStyle *style() const;
    void setStyle(DimensionStyle *style);

    bool arrowHeadEnabled() const;
    void setArrowHeadEnabled(bool enabled);

    LeaderPathType pathType() const;
    void setPathType(LeaderPathType type);

    LeaderCreationType creationType() const;
    void setCreationType(LeaderCreationType type);

    HookLineDirection hookLineDirection() const;
    void setHookLineDirection(HookLineDirection direction);

    bool hasHookline() const;
    void setHasHookline(bool hasHookline);

    double textHeight() const;
    void setTextHeight(double height);

    double textWidth() const;
    void setTextWidth(double width);

    std::vector<XYZ> vertices() const;
    void setVertices(const std::vector<XYZ> &vertices);

    Entity *associatedAnnotation() const;
    void setAssociatedAnnotation(Entity *annotation);

    XYZ normal() const;
    void setNormal(const XYZ &normal);

    XYZ horizontalDirection() const;
    void setHorizontalDirection(const XYZ &direction);

    XYZ blockOffset() const;
    void setBlockOffset(const XYZ &offset);

    XYZ annotationOffset() const;
    void setAnnotationOffset(const XYZ &offset);

    void assignDocument(CadDocument *doc) override;
    void unassignDocument() override;

private:
    DimensionStyle *_style;              ///< Dimension style associated with the leader.
    bool _arrowHeadEnabled;              ///< Indicates whether the arrowhead is enabled.
    LeaderPathType _pathType;            ///< Path type of the leader (e.g., straight or spline).
    LeaderCreationType _creationType;    ///< Creation type of the leader.
    HookLineDirection _hookLineDirection;///< Direction of the hook line, if applicable.
    bool _hasHookline;                   ///< Indicates whether the leader has a hook line.
    double _textHeight;                  ///< Height of the text associated with the leader.
    double _textWidth;                   ///< Width of the text associated with the leader.
    std::vector<XYZ> _vertices;          ///< List of vertex points defining the leader path.
    Entity *_associatedAnnotation;       ///< Associated annotation entity.
    XYZ _normal;                         ///< Normal vector defining the plane of the leader.
    XYZ _horizontalDirection;            ///< Horizontal direction vector.
    XYZ _blockOffset;                    ///< Offset of the block reference.
    XYZ _annotationOffset;               ///< Offset of the annotation.
};

}// namespace dwg

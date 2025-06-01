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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/Leader.h>
#include <dwg/tables/DimensionStyle.h>

namespace dwg {

Leader::Leader()
    : _style(DimensionStyle::Default()), _arrowHeadEnabled(false), _pathType(LeaderPathType::Spline),
      _creationType(LeaderCreationType::CreatedWithBlockReferenceAnnotation), _hookLineDirection(HookLineDirection::Opposite),
      _hasHookline(false), _textHeight(0.0), _textWidth(0.0), _associatedAnnotation(nullptr), _normal(XYZ::AxisZ),
      _horizontalDirection(XYZ::AxisX), _blockOffset(XYZ::Zero), _annotationOffset(XYZ::Zero)
{
}

Leader::~Leader() {}

ObjectType Leader::objectType() const
{
    return ObjectType::LEADER;
}

std::string Leader::objectName() const
{
    return DxfFileToken::EntityLeader;
}

std::string Leader::subclassMarker() const
{
    return DxfSubclassMarker::Leader;
}

DimensionStyle *Leader::style() const
{
    return _style;
}

void Leader::setStyle(DimensionStyle *style)
{
    _style = style;
}

bool Leader::arrowHeadEnabled() const
{
    return _arrowHeadEnabled;
}

void Leader::setArrowHeadEnabled(bool arrowHeadEnabled)
{
    _arrowHeadEnabled = arrowHeadEnabled;
}

LeaderPathType Leader::pathType() const
{
    return _pathType;
}

void Leader::setPathType(LeaderPathType pathType)
{
    _pathType = pathType;
}

LeaderCreationType Leader::creationType() const
{
    return _creationType;
}

void Leader::setCreationType(LeaderCreationType creationType)
{
    _creationType = creationType;
}

HookLineDirection Leader::hookLineDirection() const
{
    return _hookLineDirection;
}

void Leader::setHookLineDirection(HookLineDirection hookLineDirection)
{
    _hookLineDirection = hookLineDirection;
}

bool Leader::hasHookline() const
{
    return _hasHookline;
}

void Leader::setHasHookline(bool hasHookline)
{
    _hasHookline = hasHookline;
}

double Leader::textHeight() const
{
    return _textHeight;
}

void Leader::setTextHeight(double textHeight)
{
    _textHeight = textHeight;
}

double Leader::textWidth() const
{
    return _textWidth;
}

void Leader::setTextWidth(double textWidth)
{
    _textWidth = textWidth;
}

std::vector<XYZ> Leader::vertices() const
{
    return _vertices;
}

void Leader::setVertices(const std::vector<XYZ> &vertices)
{
    _vertices = vertices;
}

Entity *Leader::associatedAnnotation() const
{
    return _associatedAnnotation;
}

void Leader::setAssociatedAnnotation(Entity *associatedAnnotation)
{
    _associatedAnnotation = associatedAnnotation;
}

XYZ Leader::normal() const
{
    return _normal;
}

void Leader::setNormal(const XYZ &normal)
{
    _normal = normal;
}

XYZ Leader::horizontalDirection() const
{
    return _horizontalDirection;
}

void Leader::setHorizontalDirection(const XYZ &horizontalDirection)
{
    _horizontalDirection = horizontalDirection;
}

XYZ Leader::blockOffset() const
{
    return _blockOffset;
}

void Leader::setBlockOffset(const XYZ &blockOffset)
{
    _blockOffset = blockOffset;
}

XYZ Leader::annotationOffset() const
{
    return _annotationOffset;
}

void Leader::setAnnotationOffset(const XYZ &annotationOffset)
{
    _annotationOffset = annotationOffset;
}

}// namespace dwg
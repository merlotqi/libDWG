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

#include "Leader.h"
#include <dwg/entities/Leader.h>

namespace dwg {

Leader::Leader() {}

Leader::~Leader() {}

ObjectType Leader::objectType() const { return ObjectType::LEADER; }

std::string Leader::objectName() const { return DxfFileToken::EntityLeader; }

std::string Leader::subclassMarker() const { return DxfSubclassMarker::Leader; }

DimensionStyle *Leader::Style() const { return _style; }

void Leader::Style(DimensionStyle *style) { _style = style; }

bool Leader::ArrowHeadEnabled() const { return _arrowHeadEnabled; }

void Leader::ArrowHeadEnabled(bool arrowHeadEnabled) { _arrowHeadEnabled = arrowHeadEnabled; }

LeaderPathType Leader::PathType() const { return _pathType; }

void Leader::PathType(LeaderPathType pathType) { _pathType = pathType; }

LeaderCreationType Leader::CreationType() const { return _creationType; }

void Leader::CreationType(LeaderCreationType creationType) { _creationType = creationType; }

bool Leader::HookLineDirection() const { return _hookLineDirection; }

void Leader::HookLineDirection(bool hookLineDirection) { _hookLineDirection = hookLineDirection; }

bool Leader::HasHookline() const { return _hasHookline; }

void Leader::HasHookline(bool hasHookline) { _hasHookline = hasHookline; }

double Leader::TextHeight() const { return _textHeight; }

void Leader::TextHeight(double textHeight) { _textHeight = textHeight; }

double Leader::TextWidth() const { return _textWidth; }

void Leader::TextWidth(double textWidth) { _textWidth = textWidth; }

std::vector<XYZ> Leader::Vertices() const { return _vertices; }

void Leader::Vertices(const std::vector<XYZ> &vertices) { _vertices = vertices; }

Entity *Leader::AssociatedAnnotation() const { return _associatedAnnotation; }

void Leader::AssociatedAnnotation(Entity *associatedAnnotation) { _associatedAnnotation = associatedAnnotation; }

XYZ Leader::Normal() const { return _normal; }

void Leader::Normal(const XYZ &normal) { _normal = normal; }

XYZ Leader::HorizontalDirection() const { return _horizontalDirection; }

void Leader::HorizontalDirection(const XYZ &horizontalDirection) { _horizontalDirection = horizontalDirection; }

XYZ Leader::BlockOffset() const { return _blockOffset; }

void Leader::BlockOffset(const XYZ &blockOffset) { _blockOffset = blockOffset; }

XYZ Leader::AnnotationOffset() const { return _annotationOffset; }

void Leader::AnnotationOffset(const XYZ &annotationOffset) { _annotationOffset = annotationOffset; }

}// namespace dwg

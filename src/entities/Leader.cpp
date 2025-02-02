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

DG_Leader::DG_Leader() {}

DG_Leader::~DG_Leader() {}

DG_ObjectType DG_Leader::ObjectType() const { return DG_ObjectType::LEADER; }

std::string DG_Leader::ObjectName() const { return DG_DxfFileToken::EntityLeader; }

std::string DG_Leader::SubclassMarker() const { return DG_DxfSubclassMarker::Leader; }

DG_DimensionStyle *DG_Leader::Style() const { return _style; }

void DG_Leader::Style(DG_DimensionStyle *style) { _style = style; }

bool DG_Leader::ArrowHeadEnabled() const { return _arrowHeadEnabled; }

void DG_Leader::ArrowHeadEnabled(bool arrowHeadEnabled) { _arrowHeadEnabled = arrowHeadEnabled; }

DG_LeaderPathType DG_Leader::PathType() const { return _pathType; }

void DG_Leader::PathType(DG_LeaderPathType pathType) { _pathType = pathType; }

DG_LeaderCreationType DG_Leader::CreationType() const { return _creationType; }

void DG_Leader::CreationType(DG_LeaderCreationType creationType) { _creationType = creationType; }

bool DG_Leader::HookLineDirection() const { return _hookLineDirection; }

void DG_Leader::HookLineDirection(bool hookLineDirection) { _hookLineDirection = hookLineDirection; }

bool DG_Leader::HasHookline() const { return _hasHookline; }

void DG_Leader::HasHookline(bool hasHookline) { _hasHookline = hasHookline; }

double DG_Leader::TextHeight() const { return _textHeight; }

void DG_Leader::TextHeight(double textHeight) { _textHeight = textHeight; }

double DG_Leader::TextWidth() const { return _textWidth; }

void DG_Leader::TextWidth(double textWidth) { _textWidth = textWidth; }

std::vector<XYZ> DG_Leader::Vertices() const { return _vertices; }

void DG_Leader::Vertices(const std::vector<XYZ> &vertices) { _vertices = vertices; }

DG_Entity *DG_Leader::AssociatedAnnotation() const { return _associatedAnnotation; }

void DG_Leader::AssociatedAnnotation(DG_Entity *associatedAnnotation) { _associatedAnnotation = associatedAnnotation; }

XYZ DG_Leader::Normal() const { return _normal; }

void DG_Leader::Normal(const XYZ &normal) { _normal = normal; }

XYZ DG_Leader::HorizontalDirection() const { return _horizontalDirection; }

void DG_Leader::HorizontalDirection(const XYZ &horizontalDirection) { _horizontalDirection = horizontalDirection; }

XYZ DG_Leader::BlockOffset() const { return _blockOffset; }

void DG_Leader::BlockOffset(const XYZ &blockOffset) { _blockOffset = blockOffset; }

XYZ DG_Leader::AnnotationOffset() const { return _annotationOffset; }

void DG_Leader::AnnotationOffset(const XYZ &annotationOffset) { _annotationOffset = annotationOffset; }

}// namespace dwg

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

#include "Circle.h"
#include <dwg/entities/Circle.h>

namespace dwg {

DG_Circle::DG_Circle() : _center(XYZ::Zero), _normal(XYZ::AxisZ), _thickness(0.0), _radius(0.0) {}

DG_Circle::~DG_Circle() {}

DG_ObjectType DG_Circle::ObjectType() const { return DG_ObjectType::CIRCLE; }

std::string DG_Circle::ObjectName() const { return DG_DxfFileToken::EntityCircle; }

std::string DG_Circle::SubclassMarker() const { return DG_DxfSubclassMarker::Circle; }

XYZ DG_Circle::Normal() const { return _normal; }

XYZ DG_Circle::Center() const { return _center; }

double DG_Circle::Thickness() const { return _thickness; }

double DG_Circle::Radius() const { return _radius; }

void DG_Circle::Normal(const XYZ &normal) { _normal = normal; }

void DG_Circle::Center(const XYZ &center) { _center = center; }

void DG_Circle::Thickness(double thickness) { _thickness = thickness; }

void DG_Circle::Radius(double radius) { _radius = radius; }

}// namespace dwg

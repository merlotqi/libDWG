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

#include "Ellipse.h"
#include <dwg/entities/Ellipse.h>

namespace dwg {

DG_Ellipse::DG_Ellipse()
    : _normal(XYZ::AxisZ), _center(XYZ::Zero), _endPoint(XYZ::AxisX), _radiusRatio(0.0), _startParameter(0.0),
      _endParameter(2 * M_PI), _thickness(0.0)
{
}

DG_Ellipse::~DG_Ellipse() {}

DG_ObjectType DG_Ellipse::ObjectType() const { return DG_ObjectType::ELLIPSE; }

std::string DG_Ellipse::ObjectName() const { return DG_DxfFileToken::EntityEllipse; }

std::string DG_Ellipse::SubclassMarker() const { return DG_DxfSubclassMarker::Ellipse; }

XYZ DG_Ellipse::Normal() const { return _normal; }

XYZ DG_Ellipse::Center() const { return _center; }

XYZ DG_Ellipse::EndPoint() const { return _endPoint; }

double DG_Ellipse::Thickness() const { return _thickness; }

double DG_Ellipse::RadiusRatio() const { return _radiusRatio; }

double DG_Ellipse::StartParameter() const { return _startParameter; }

double DG_Ellipse::EndParameter() const { return _endParameter; }

void DG_Ellipse::Normal(const XYZ &normal) { _normal = normal; }

void DG_Ellipse::Center(const XYZ &center) { _center = center; }

void DG_Ellipse::EndPoint(const XYZ &endPoint) { _endPoint = endPoint; }

void DG_Ellipse::Thickness(double thickness) { _thickness = thickness; }

void DG_Ellipse::RadiusRatio(double radiusRatio) { _radiusRatio = radiusRatio; }

void DG_Ellipse::StartParameter(double startParam) { _startParameter = startParam; }

void DG_Ellipse::EndParameter(double endParam) { _endParameter = endParam; }

}// namespace dwg
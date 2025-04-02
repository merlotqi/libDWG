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
#include <dwg/entities/Line.h>

namespace dwg {

Line::Line() : _normal(XYZ::AxisZ), _startPoint(XYZ::Zero), _endPoint(XYZ::Zero), _thickness(0.0) {}

Line::~Line() {}

ObjectType Line::objectType() const
{
    return ObjectType::LINE;
}

std::string Line::objectName() const
{
    return DxfFileToken::EntityLine;
}

std::string Line::subclassMarker() const
{
    return DxfSubclassMarker::Line;
}

XYZ Line::normal() const
{
    return _normal;
}

void Line::setNormal(const XYZ &normal)
{
    _normal = normal;
}

XYZ Line::startPoint() const
{
    return _startPoint;
}

void Line::setStartPoint(const XYZ &point)
{
    _startPoint = point;
}

XYZ Line::endPoint() const
{
    return _endPoint;
}

void Line::setEndPoint(const XYZ &point)
{
    _endPoint = point;
}

double Line::thickness() const
{
    return _thickness;
}

void Line::setThickness(double thickness)
{
    _thickness = thickness;
}

}// namespace dwg
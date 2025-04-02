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
#include <dwg/entities/Point.h>

namespace dwg {

Point::Point() : _location(XYZ::Zero), _normal(XYZ::Zero), _thickness(0.0), _rotation(0.0) {}

Point::~Point() {}

ObjectType Point::objectType() const
{
    return ObjectType::POINT;
}

std::string Point::objectName() const
{
    return DxfFileToken::EntityPoint;
}

std::string Point::subclassMarker() const
{
    return DxfSubclassMarker::Point;
}

XYZ Point::location() const
{
    return _location;
}

void Point::setLocation(const XYZ &value)
{
    _location = value;
}

XYZ Point::normal() const
{
    return _normal;
}

void Point::setNormal(const XYZ &value)
{
    _normal = value;
}

double Point::thickness() const
{
    return _thickness;
}

void Point::setThickness(double value)
{
    _thickness = value;
}

double Point::rotation() const
{
    return _rotation;
}

void Point::setRotation(double value)
{
    _rotation = value;
}

}// namespace dwg
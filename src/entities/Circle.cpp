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
#include <dwg/attributes/DxfCodeValueAttribute_p.h>
#include <dwg/attributes/DxfSubClassAttribute_p.h>
#include <dwg/entities/Circle.h>
#include <stdexcept>

namespace dwg {

Circle::Circle() : _center(XYZ::Zero), _normal(XYZ::AxisZ), _thickness(0.0), _radius(0.0) {}

Circle::~Circle() {}

ObjectType Circle::objectType() const
{
    return ObjectType::CIRCLE;
}

std::string Circle::objectName() const
{
    return DxfFileToken::EntityCircle;
}

std::string Circle::subclassMarker() const
{
    return DxfSubclassMarker::Circle;
}

XYZ Circle::normal() const
{
    return _normal;
}

XYZ Circle::center() const
{
    return _center;
}

double Circle::thickness() const
{
    return _thickness;
}

double Circle::radius() const
{
    return _radius;
}

void Circle::setNormal(const XYZ &normal)
{
    _normal = normal;
}

void Circle::setCenter(const XYZ &center)
{
    _center = center;
}

void Circle::setThickness(double thickness)
{
    _thickness = thickness;
}

void Circle::setRadius(double radius)
{
    if (radius <= 0)
        throw std::invalid_argument("Radius must be greater than 0");
    _radius = radius;
}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<Circle>("Circle")(metadata("DxfName", DxfFileToken::EntityArc),
                                           metadata("DxfSubClass", DxfSubClassAttribute(DxfSubclassMarker::Arc)))
            .constructor()
            .property("center", &Circle::center, &Circle::setCenter);
}

}// namespace dwg
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
#include <dwg/entities/XLine.h>

namespace dwg {

XLine::XLine() : Entity() {}

XLine::~XLine() {}

ObjectType XLine::objectType() const
{
    return ObjectType::XLINE;
}

std::string XLine::objectName() const
{
    return DxfFileToken::EntityXline;
}

std::string XLine::subclassMarker() const
{
    return DxfSubclassMarker::XLine;
}

XYZ XLine::firstPoint() const
{
    return _firstPoint;
}

void XLine::setFirstPoint(const XYZ &value)
{
    _firstPoint = value;
}

XYZ XLine::direction() const
{
    return _direction;
}

void XLine::setDirection(const XYZ &value)
{
    _direction = value;
}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<XLine>("XLine")(metadata("DxfName", DxfFileToken::EntityXline),
                                         (metadata("DxfSubClass", DxfSubclassMarker::XLine)))
            .constructor()
            .property("firstPoint", &XLine::firstPoint,
                      &XLine::setFirstPoint)(metadata("DxfCode", DxfCodeValueAttribute({10, 20, 30})))
            .property("direction", &XLine::direction,
                      &XLine::setDirection)(metadata("DxfCode", DxfCodeValueAttribute({11, 21, 31})));
}

}// namespace dwg
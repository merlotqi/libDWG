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
#include <dwg/entities/Solid.h>

namespace dwg {

Solid::Solid() {}

Solid::~Solid() {}

ObjectType Solid::objectType() const
{
    return ObjectType::SOLID;
}

std::string Solid::objectName() const
{
    return DxfFileToken::EntitySolid;
}

std::string Solid::subclassMarker() const
{
    return DxfSubclassMarker::Solid;
}

XYZ Solid::firstCorner() const
{
    return _firstCorner;
}

void Solid::setFirstCorner(const XYZ &value)
{
    _firstCorner = value;
}

XYZ Solid::secondCorner() const
{
    return _secondCorner;
}

void Solid::setSecondCorner(const XYZ &value)
{
    _secondCorner = value;
}

XYZ Solid::thirdCorner() const
{
    return _thirdCorner;
}

void Solid::setThirdCorner(const XYZ &value)
{
    _thirdCorner = value;
}

XYZ Solid::fourthCorner() const
{
    return _fourthCorner;
}

void Solid::setFourthCorner(const XYZ &value)
{
    _fourthCorner = value;
}

double Solid::thickness() const
{
    return _thickness;
}

void Solid::setThickness(double value)
{
    _thickness = value;
}

XYZ Solid::normal() const
{
    return _normal;
}

void Solid::setNormal(const XYZ &value)
{
    _normal = value;
}

}// namespace dwg
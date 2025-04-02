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
#include <dwg/entities/Face3D.h>

namespace dwg {

Face3D::Face3D()
    : _firstCorner(XYZ::Zero), _secondCorner(XYZ::Zero), _thirdCorner(XYZ::Zero), _fourthCorner(XYZ::Zero),
      _flags(InvisibleEdgeFlag::None)
{
}

Face3D::~Face3D() {}

ObjectType Face3D::objectType() const
{
    return ObjectType::FACE3D;
}

std::string Face3D::objectName() const
{
    return DxfFileToken::Entity3DFace;
}

std::string Face3D::subclassMarker() const
{
    return DxfSubclassMarker::Face3d;
}

XYZ Face3D::firstCorner() const
{
    return _firstCorner;
}

void Face3D::setFirstCorner(const XYZ &value)
{
    _firstCorner = value;
}

XYZ Face3D::secondCorner() const
{
    return _secondCorner;
}

void Face3D::setSecondCorner(const XYZ &value)
{
    _secondCorner = value;
}

XYZ Face3D::thirdCorner() const
{
    return _thirdCorner;
}

void Face3D::setThirdCorner(const XYZ &value)
{
    _thirdCorner = value;
}

XYZ Face3D::fourthCorner() const
{
    return _fourthCorner;
}

void Face3D::setFourthCorner(const XYZ &value)
{
    _fourthCorner = value;
}

InvisibleEdgeFlags Face3D::flags() const
{
    return _flags;
}

void Face3D::setFlags(InvisibleEdgeFlags value)
{
    _flags = value;
}

}// namespace dwg
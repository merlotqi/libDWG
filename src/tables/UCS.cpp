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
#include <dwg/tables/UCS.h>


namespace dwg {

UCS::UCS() {}

UCS::UCS(const std::string &name) : TableEntry(name) {}

UCS::~UCS() {}

ObjectType UCS::objectType() const
{
    return ObjectType::UCS;
}

std::string UCS::objectName() const
{
    return DxfFileToken::TableUcs;
}

std::string UCS::subclassMarker() const
{
    return DxfSubclassMarker::Ucs;
}

XYZ UCS::origin() const
{
    return _origin;
}

void UCS::setOrigin(const XYZ &value)
{
    _origin = value;
}

XYZ UCS::xAxis() const
{
    return _xAxis;
}

void UCS::setXAxis(const XYZ &value)
{
    _xAxis = value;
}

XYZ UCS::yAxis() const
{
    return _yAxis;
}

void UCS::setYAxis(const XYZ &value)
{
    _yAxis = value;
}

OrthographicType UCS::orthographicType() const
{
    return _orthographicType;
}

void UCS::setOrthographicType(OrthographicType value)
{
    _orthographicType = value;
}

OrthographicType UCS::orthographicViewType() const
{
    return _orthographicViewType;
}

void UCS::setOrthographicViewType(OrthographicType value)
{
    _orthographicViewType = value;
}

double UCS::elevation() const
{
    return _elevation;
}

void UCS::setElevation(double value)
{
    _elevation = value;
}

}// namespace dwg
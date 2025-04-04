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
#include <dwg/objects/Scale.h>

namespace dwg {
Scale::Scale(const std::string &name) : NonGraphicalObject(name) {}

Scale::Scale(const std::string &name, double paperUnits, double drawingUnits, bool isUnitScale)
    : NonGraphicalObject(name), _paperUnits(paperUnits), _drawingUnits(drawingUnits), _isUnitScale(isUnitScale)
{
}

Scale::~Scale() {}

Scale *Scale::Default()
{
    return new Scale("1:1", 1.0, 1.0, true);
}

ObjectType Scale::objectType() const
{
    return ObjectType::UNLISTED;
}

std::string Scale::objectName() const
{
    return DxfFileToken::ObjectScale;
}

std::string Scale::subclassMarker() const
{
    return DxfSubclassMarker::Scale;
}

double Scale::paperUnits() const
{
    return _paperUnits;
}

void Scale::setPaperUnits(double value)
{
    _paperUnits = value;
}

double Scale::drawingUnits() const
{
    return _drawingUnits;
}

void Scale::setDrawingUnits(double value)
{
    _drawingUnits = value;
}

bool Scale::isUnitScale() const
{
    return _isUnitScale;
}

void Scale::setIsUnitScale(bool value)
{
    _isUnitScale = value;
}

double Scale::scaleFactor() const
{
    return _paperUnits / _drawingUnits;
}

double Scale::applyTo(double value)
{
    return value * scaleFactor();
}

XYZ Scale::applyTo(const XYZ &value)
{
    return XYZ(applyTo(value.X), applyTo(value.Y), applyTo(value.Z));
}

XY Scale::applyTo(const XY &value)
{

    return XY(applyTo(value.X), applyTo(value.Y));
}

}// namespace dwg
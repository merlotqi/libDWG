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

#include <dwg/CadDocument.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/Tolerance.h>
#include <dwg/tables/DimensionStyle.h>

namespace dwg {

Tolerance::Tolerance() {}

Tolerance::~Tolerance() {}

ObjectType Tolerance::objectType() const
{
    return ObjectType::TOLERANCE;
}

std::string Tolerance::objectName() const
{
    return DxfFileToken::EntityTolerance;
}

std::string Tolerance::subclassMarker() const
{
    return DxfSubclassMarker::Tolerance;
}

DimensionStyle *Tolerance::style() const
{
    return _style;
}

void Tolerance::setStyle(DimensionStyle *value)
{
    if (!value)
        throw std::runtime_error("Tolerance::setStyle: style is null");

    if (document())
    {
        //_style = updateTable(value, document->dimensionStyles());
    }
    else
    {
        _style = value;
    }
}

XYZ Tolerance::insertionPoint() const
{
    return _insertionPoint;
}

void Tolerance::setInsertionPoint(const XYZ &value)
{
    _insertionPoint = value;
}

XYZ Tolerance::direction() const
{
    return _direction;
}

void Tolerance::setDirection(const XYZ &value)
{
    _direction = value;
}

XYZ Tolerance::normal() const
{
    return _normal;
}

void Tolerance::setNormal(const XYZ &value)
{
    _normal = value;
}

std::string Tolerance::text() const
{
    return _text;
}

void Tolerance::setText(const std::string &value)
{
    _text = value;
}

}// namespace dwg
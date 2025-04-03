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
#include <dwg/entitites/Shape.h>

namespace dwg {

Shape::Shape() {}

Shape::~Shape() {}

ObjectType Shape::objectType() const { return ObjectType::SHAPE; }

std::string Shape::objectName() const { return DxfFileToken::EntityShape; }

std::string Shape::subclassMarker() const { return DxfSubclassMarker::Shape; }

double Shape::thickness() const { return _thickness; }

void Shape::setThickness(double value) { _thickness = value; }

XYZ Shape::insertionPoint() const { return _insertionPoint; }

void Shape::setInsertionPoint(const XYZ &value) { _insertionPoint = value; }

double Shape::size() const { return _size; }

void Shape::setSize(double value) { _size = value; }

TextStyle *Shape::shapeStyle() const
{
    return _shapeStyle;
}

void Shape::setShapeStyle(TextStyle *value)
{
    if(!value || !value->isShapeFile())
    {
        throw new std::invalid_argument("invalid value");
    }
    if(document())
    {
        _shapeStyle = updateTable(value, document()->textStyles());
    }
    {
        _shapeStyle = value;
    }
}

double Shape::rotation() const { return _rotation; }

void Shape::setRotation(double value) { _rotation = value; }

double Shape::relativeXScale() const { return _relativeXScale ;}

void Shape::setRelativeXScale(double value) { _relativeXScale = value; }

double Shape::obliqueAngle() const { return _obliqueAngle; }

void Shape::setObliqueAngle(double value) { _obliqueAngle = value; }

XYZ Shape::normal() const { return _normal; }

void Shape::setNormal(const XYZ &value) { _normal = value; }

unsigned short Shape::shapeIndex() const { return _shapeIndex; }

void Shape::setShapeIndex(unsigned short value) { _shapeIndex = value; }

}// namespace
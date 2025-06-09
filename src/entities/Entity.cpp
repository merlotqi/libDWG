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
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/Entity.h>
#include <dwg/objects/BookColor.h>
#include <dwg/objects/collections/ColorCollection.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>

namespace dwg {

Entity::Entity()
    : _layer(Layer::Default()), _color(Color::ByLayer), _lineweight(LineweightType::ByLayer), _linetypeScale(1.0),
      _isInvisible(false), _transparency(Transparency::ByLayer), _linetype(LineType::ByLayer()), _material(nullptr),
      _bookColor(nullptr)
{
}

Entity::~Entity() {}

std::string Entity::subclassMarker() const
{
    return DxfSubclassMarker::Entity;
}

Layer *Entity::layer() const
{
    return _layer;
}

void Entity::setLayer(Layer *value)
{
    _layer = value;
}

Color Entity::color() const
{
    return _color;
}

void Entity::setColor(const Color &value)
{
    _color = value;
}

LineweightType Entity::lineweight() const
{
    return _lineweight;
}

void Entity::setLineweight(LineweightType value)
{
    _lineweight = value;
}

double Entity::linetypeScale() const
{
    return _linetypeScale;
}

void Entity::setLinetypeScale(double value)
{
    _linetypeScale = value;
}

bool Entity::isInvisible() const
{
    return _isInvisible;
}

void Entity::setIsInvisible(bool value)
{
    _isInvisible = value;
}

Transparency Entity::transparency() const
{
    return _transparency;
}

void Entity::setTransparency(const Transparency &value)
{
    _transparency = value;
}

LineType *Entity::lineType() const
{
    return _linetype;
}

void Entity::setLineType(LineType *value)
{
    _linetype = value;
}

Material *Entity::material() const
{
    return _material;
}

void Entity::setMaterial(Material *value)
{
    _material = value;
}

BookColor *Entity::bookColor() const
{
    return _bookColor;
}

void Entity::setBookColor(BookColor *value)
{
    if (_document)
    {
        _bookColor = updateCollectionT<BookColor *>(value, _document->colors());
    }
    else
    {
        _bookColor = value;
    }
}

void Entity::matchProperties(Entity *entity) {}

}// namespace dwg
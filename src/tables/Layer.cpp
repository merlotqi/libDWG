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
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>


namespace dwg {

Layer::Layer()
    : _flags(0), _color(Color((short) 7)), _lineType(LineType::Continuous()), _plotFlag(true),
      _lineweight(LineweightType::Default), _plotStyleName(0ULL), _material(nullptr), _isOn(true)
{
}

Layer::Layer(const std::string &name)
    : TableEntry(name), _flags(0), _color(Color((short) 7)), _lineType(LineType::Continuous()), _plotFlag(true),
      _lineweight(LineweightType::Default), _plotStyleName(0ULL), _material(nullptr), _isOn(true)
{
}

Layer::~Layer() {}

Layer *Layer::Default()
{
    return new Layer(DefaultName);
}

ObjectType Layer::objectType() const
{
    return ObjectType::LAYER;
}

std::string Layer::objectName() const
{
    return DxfFileToken::TableLayer;
}

std::string Layer::subclassMarker() const
{
    return DxfSubclassMarker::Layer;
}

LayerFlags Layer::flags() const
{
    return _flags;
}

void Layer::setFlags(LayerFlags value)
{
    _flags = value;
}

Color Layer::color() const
{
    return _color;
}

void Layer::setColor(const Color &value)
{
    if (value.isByLayer() || value.isByBlock())
    {
        throw new std::invalid_argument("The layer color cannot be ByLayer or ByBlock");
    }
    _color = value;
}

LineType *Layer::lineType() const
{
    return _lineType;
}

void Layer::setLineType(LineType *value)
{
    _lineType = value;
}

bool Layer::plotFlag() const
{
    return _plotFlag;
}

void Layer::setPlotFlag(bool value)
{
    _plotFlag = value;
}

LineweightType Layer::lineWeight() const
{
    return _lineweight;
}

void Layer::setLineWeight(LineweightType value)
{
    _lineweight = value;
}

unsigned long long Layer::plotStyleName() const
{
    return _plotStyleName;
}

void Layer::setPlotStyleName(unsigned long long value)
{
    _plotStyleName = value;
}

Material *Layer::material() const
{
    return _material;
}

void Layer::setMaterial(Material *value)
{
    _material = value;
}

bool Layer::isOn() const
{
    return _isOn;
}

void Layer::setIsOn(bool value)
{
    _isOn = value;
}

}// namespace dwg
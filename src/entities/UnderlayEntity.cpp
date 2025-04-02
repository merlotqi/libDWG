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

#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/UnderlayEntity.h>
#include <fmt/core.h>

namespace dwg {

UnderlayEntity::UnderlayEntity()
    : _normal(XYZ::AxisZ), _insertPoint(XYZ::Zero), _xscale(1.0), _yscale(1.0), _zscale(1.0), _rotation(0.0),
      _flags(UnderlayDisplayFlag::ClippingOn), _contrast(50), _fade(0), _definition(nullptr)
{
}

UnderlayEntity::~UnderlayEntity() {}

std::string UnderlayEntity::subclassMarker() const
{
    return DxfSubclassMarker::Underlay;
}

XYZ UnderlayEntity::normal() const
{
    return _normal;
}

void UnderlayEntity::setNormal(const XYZ &value)
{
    _normal = value;
}

XYZ UnderlayEntity::insertPoint() const
{
    return _insertPoint;
}

void UnderlayEntity::setInsertPoint(const XYZ &value)
{
    _insertPoint = value;
}

double UnderlayEntity::xScale() const
{
    return _xscale;
}

void UnderlayEntity::setXScale(double value)
{
    _xscale = value;
}

double UnderlayEntity::yScale() const
{
    return _yscale;
}

void UnderlayEntity::setYScale(double value)
{
    _yscale = value;
}

double UnderlayEntity::zScale() const
{
    return _zscale;
}

void UnderlayEntity::setZScale(double value)
{
    _zscale = value;
}

double UnderlayEntity::rotation() const
{
    return _rotation;
}

void UnderlayEntity::setRotation(double value)
{
    _rotation = value;
}

UnderlayDisplayFlags UnderlayEntity::flags() const
{
    return _flags;
}

void UnderlayEntity::setFlags(UnderlayDisplayFlags value)
{
    _flags = value;
}

unsigned char UnderlayEntity::contrast() const
{
    return _contrast;
}

void UnderlayEntity::setContrast(unsigned char value)
{
    if (value < 0 || value > 100)
        throw new std::out_of_range(fmt::format("Invalid Contrast value: {}, must be in range 0-100", value));
    _contrast = value;
}

unsigned char UnderlayEntity::fade() const
{
    return _fade;
}

void UnderlayEntity::setFade(unsigned char value)
{
    if (value < 0 || value > 100)
        throw new std::out_of_range(fmt::format("Invalid Fade value: {}, must be in range 0-100", value));
    _fade = value;
}

UnderlayDefinition *UnderlayEntity::definition() const
{
    return _definition;
}

void UnderlayEntity::setDefinition(UnderlayDefinition *value)
{
    _definition = value;
}

}// namespace dwg
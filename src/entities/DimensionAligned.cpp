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
#include <dwg/entities/DimensionAligned.h>

namespace dwg {

DimensionAligned::DimensionAligned() : Dimension(DimensionType::Aligned) {}

DimensionAligned::~DimensionAligned() {}

ObjectType DimensionAligned::objectType() const
{
    return ObjectType::DIMENSION_ALIGNED;
}

std::string DimensionAligned::objectName() const
{
    return DxfFileToken::EntityDimension;
}

std::string DimensionAligned::subclassMarker() const
{
    return DxfSubclassMarker::AlignedDimension;
}

XYZ DimensionAligned::firstPoint() const
{
    return _firstPoint;
}

void DimensionAligned::setFirstPoint(const XYZ &value)
{
    _firstPoint = value;
}

XYZ DimensionAligned::secondPoint() const
{
    return _secondPoint;
}

void DimensionAligned::setSecondPoint(const XYZ &value)
{
    _secondPoint = value;
}

double DimensionAligned::extLineRotation() const
{
    return _extLineRotation;
}

void DimensionAligned::setExtLineRotation(double value)
{
    _extLineRotation = value;
}

double DimensionAligned::measurement() const
{
    return _firstPoint.distanceToPoint(_secondPoint);
}

DimensionAligned::DimensionAligned(DimensionType type) : Dimension(type) {}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<DimensionAligned>("DimensionAligned")(metadata("DxfName", DxfFileToken::EntityDimension),
                                                               metadata("DxfSubClass", DxfSubClassAttribute(DxfSubclassMarker::AlignedDimension)))
            .constructor()
            .property("extLineRotation", &DimensionAligned::extLineRotation, &DimensionAligned::setExtLineRotation)(metadata("DxfCodeValue", DxfCodeValueAttribute(DxfReferenceType::Optional, {52})))
            .property("firstPoint", &DimensionAligned::firstPoint, &DimensionAligned::setFirstPoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({13, 23, 33})))
            .property("secondPoint", &DimensionAligned::secondPoint, &DimensionAligned::setSecondPoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({14, 24, 34})));
}

}// namespace dwg
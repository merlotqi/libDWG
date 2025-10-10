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
#include <dwg/entities/DimensionDiameter.h>

namespace dwg {

DimensionDiameter::DimensionDiameter() : Dimension(DimensionType::Diameter) {}

DimensionDiameter::~DimensionDiameter() {}

ObjectType DimensionDiameter::objectType() const
{
    return ObjectType::DIMENSION_DIAMETER;
}

std::string DimensionDiameter::objectName() const
{
    return DxfFileToken::EntityDimension;
}

std::string DimensionDiameter::subclassMarker() const
{
    return DxfSubclassMarker::DiametricDimension;
}

const XYZ &DimensionDiameter::angleVertex() const
{
    return _angleVertex;
}

void DimensionDiameter::setAngleVertex(const XYZ &value)
{
    _angleVertex = value;
}

XYZ DimensionDiameter::center() const
{
    return XYZ::Zero;
}

double DimensionDiameter::leaderLength() const
{
    return _leaderLength;
}

void DimensionDiameter::setLeaderLength(double value)
{
    _leaderLength = value;
}

double DimensionDiameter::measurement() const
{
    return 0.0;
}

void DimensionDiameter::updateBlock() {}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<DimensionDiameter>("DimensionDiameter")(
            metadata("DxfName", DxfFileToken::EntityDimension),
            metadata("DxfSubClass", DxfSubClassAttribute(DxfSubclassMarker::DiametricDimension)))
            .constructor()
            .property("angleVertex", &DimensionDiameter::angleVertex,
                      &DimensionDiameter::setAngleVertex)(metadata("DxfCodeValue", DxfCodeValueAttribute({15, 25, 35})))
            .property("leaderLength", &DimensionDiameter::leaderLength,
                      &DimensionDiameter::setLeaderLength)(metadata("DxfCodeValue", DxfCodeValueAttribute({40})));
}

}// namespace dwg
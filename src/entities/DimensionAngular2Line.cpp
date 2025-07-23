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
#include <dwg/entities/DimensionAngular2Line.h>

namespace dwg {

DimensionAngular2Line::DimensionAngular2Line() : Dimension(DimensionType::Angular) {}

DimensionAngular2Line::~DimensionAngular2Line() {}

ObjectType DimensionAngular2Line::objectType() const
{
    return ObjectType::DIMENSION_ANG_2_Ln;
}

std::string DimensionAngular2Line::objectName() const
{
    return DxfFileToken::EntityDimension;
}

std::string DimensionAngular2Line::subclassMarker() const
{
    return DxfSubclassMarker::Angular2LineDimension;
}

XYZ DimensionAngular2Line::firstPoint() const
{
    return _firstPoint;
}

void DimensionAngular2Line::setFirstPoint(const XYZ &value)
{
    _firstPoint = value;
}

XYZ DimensionAngular2Line::secondPoint() const
{
    return _secondPoint;
}

void DimensionAngular2Line::setSecondPoint(const XYZ &value)
{
    _secondPoint = value;
}

XYZ DimensionAngular2Line::angleVertex() const
{
    return _angleVertex;
}

void DimensionAngular2Line::setAngleVertex(const XYZ &value)
{
    _angleVertex = value;
}

XYZ DimensionAngular2Line::dimensionArc() const
{
    return _dimensionArc;
}

void DimensionAngular2Line::setDimensionArc(const XYZ &value)
{
    _dimensionArc = value;
}

double DimensionAngular2Line::measurement() const
{
    XY v1 = (_firstPoint - _secondPoint).to2D();
    XY v2 = (_angleVertex - _dimensionArc).to2D();
    return 0.0;
    //return v1.angleTo(v2);
}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<DimensionAngular2Line>("DimensionAngular2Line")(metadata("DxfName", DxfFileToken::EntityDimension),
                                                                         metadata("DxfSubClass", DxfSubClassAttribute(DxfSubclassMarker::Angular2LineDimension)))
            .constructor()
            .property("angleVertex", &DimensionAngular2Line::angleVertex, &DimensionAngular2Line::setAngleVertex)(metadata("DxfCodeValue", DxfCodeValueAttribute({15, 25, 35})))
            .property("dimensionArc", &DimensionAngular2Line::dimensionArc, &DimensionAngular2Line::setDimensionArc)(metadata("DxfCodeValue", DxfCodeValueAttribute({16, 26, 36})))
            .property("firstPoint", &DimensionAngular2Line::firstPoint, &DimensionAngular2Line::setFirstPoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({13, 23, 33})))
            .property("secondPoint", &DimensionAngular2Line::secondPoint, &DimensionAngular2Line::setSecondPoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({14, 24, 34})));
}

}// namespace dwg
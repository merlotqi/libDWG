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
#include <dwg/entities/DimensionAngular3Pt.h>

namespace dwg {

DimensionAngular3Pt::DimensionAngular3Pt() : Dimension(DimensionType::Angular3Point) {}

DimensionAngular3Pt::~DimensionAngular3Pt() {}

ObjectType DimensionAngular3Pt::objectType() const { return ObjectType::DIMENSION_ANG_3_Pt; }

std::string DimensionAngular3Pt::objectName() const { return DxfFileToken::EntityDimension; }

std::string DimensionAngular3Pt::subclassMarker() const { return DxfSubclassMarker::Angular3PointDimension; }

XYZ DimensionAngular3Pt::firstPoint() const { return _firstPoint; }

void DimensionAngular3Pt::setFirstPoint(const XYZ &value) { _firstPoint = value; }

XYZ DimensionAngular3Pt::secondPoint() const { return _secondPoint; }

void DimensionAngular3Pt::setSecondPoint(const XYZ &value) { _secondPoint = value; }

XYZ DimensionAngular3Pt::angleVertex() const { return _angleVertex; }

void DimensionAngular3Pt::setAngleVertex(const XYZ &value) { _angleVertex = value; }

double DimensionAngular3Pt::measurement() const
{
    //XY v1 = (_firstPoint - _secondPoint).to2D();
    //XY v2 = (_secondPoint - _angleVertex).to2D();

    //if (v1.fuzzyEqual(v2)) { return 0.0; }

    //if (v1.isParallel(v2)) { return M_PI; }

    //return v1.angleTo(v2);

    return 0.0;
}

}// namespace dwg
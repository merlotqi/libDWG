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
#include <dwg/entities/DimensionOrdinate.h>

namespace dwg {

DimensionOrdinate::DimensionOrdinate() : Dimension(DimensionType::Ordinate) {}

DimensionOrdinate::~DimensionOrdinate() {}

ObjectType DimensionOrdinate::objectType() const { return ObjectType::DIMENSION_ORDINATE; }

std::string DimensionOrdinate::objectName() const { return DxfFileToken::EntityDimension; }

std::string DimensionOrdinate::subclassMarker() const { return DxfSubclassMarker::OrdinateDimension; }

XYZ DimensionOrdinate::featureLocation() const { return _featureLocation; }

void DimensionOrdinate::setFeatureLocation(const XYZ &value) { _featureLocation = value; }

XYZ DimensionOrdinate::leaderEndpoint() const { return _leaderEndpoint; }

void DimensionOrdinate::setLeaderEndpoint(const XYZ &value) { _leaderEndpoint = value; }

double DimensionOrdinate::measurement() const { return 0.0; }

bool DimensionOrdinate::isOrdinateTypeX() const { return _flags & DimensionType::OrdinateTypeX; }

void DimensionOrdinate::setIsOrdinateTypeX(bool value)
{
    if (value) { _flags |= DimensionType::OrdinateTypeX; }
    else { _flags &= ~DimensionType::OrdinateTypeX; }
}

}// namespace dwg
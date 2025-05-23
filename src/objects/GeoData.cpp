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
#include <dwg/objects/GeoData.h>

namespace dwg {

GeoData::GeoData() {}

GeoData::~GeoData() {}

ObjectType GeoData::objectType() const
{
    return ObjectType::UNLISTED;
}

std::string GeoData::objectName() const
{
    return DxfFileToken::ObjectGeoData;
}

std::string GeoData::subclassMarker() const
{
    return DxfSubclassMarker::GeoData;
}

GeoDataVersion GeoData::version() const
{
    return _version;
}

void GeoData::setVersion(GeoDataVersion value)
{
    _version = value;
}

DesignCoordinatesType GeoData::coordinatesType() const
{
    return _coordinatesType;
}

void GeoData::setCoordinatesType(DesignCoordinatesType value)
{
    _coordinatesType = value;
}

BlockRecord *GeoData::hostBlock() const
{
    return _hostBlock;
}

void GeoData::setHostBlock(BlockRecord *value)
{
    _hostBlock = value;
}

XYZ GeoData::designPoint() const
{
    return _designPoint;
}

void GeoData::setDesignPoint(const XYZ &value)
{
    _designPoint = value;
}

XYZ GeoData::referencePoint() const
{
    return _referencePoint;
}

void GeoData::setReferencePoint(const XYZ &value)
{
    _referencePoint = value;
}

XY GeoData::northDirection() const
{
    return _northDirection;
}

void GeoData::setNorthDirection(const XY &value)
{
    _northDirection = value;
}

double GeoData::horizontalUnitScale() const
{
    return _horizontalUnitScale;
}

void GeoData::setHorizontalUnitScale(double value)
{
    _horizontalUnitScale = value;
}

double GeoData::verticalUnitScale() const
{
    return _verticalUnitScale;
}

void GeoData::setVerticalUnitScale(double value)
{
    _verticalUnitScale = value;
}

UnitsType GeoData::horizontalUnits() const
{
    return _horizontalUnits;
}

void GeoData::setHorizontalUnits(UnitsType value)
{
    _horizontalUnits = value;
}

UnitsType GeoData::verticalUnits() const
{
    return _verticalUnits;
}

void GeoData::setVerticalUnits(UnitsType value)
{
    _verticalUnits = value;
}

XYZ GeoData::upDirection() const
{
    return _upDirection;
}

void GeoData::setUpDirection(const XYZ &value)
{
    _upDirection = value;
}

ScaleEstimationType GeoData::scaleEstimationMethod() const
{
    return _scaleEstimationMethod;
}

void GeoData::setScaleEstimationMethod(ScaleEstimationType value)
{
    _scaleEstimationMethod = value;
}

bool GeoData::enableSeaLevelCorrection() const
{
    return _enableSeaLevelCorrection;
}

void GeoData::setEnableSeaLevelCorrection(bool value)
{
    _enableSeaLevelCorrection = value;
}

double GeoData::userSpecifiedScaleFactor() const
{
    return _userSpecifiedScaleFactor;
}

void GeoData::setUserSpecifiedScaleFactor(double value)
{
    _userSpecifiedScaleFactor = value;
}

double GeoData::seaLevelElevation() const
{
    return _seaLevelElevation;
}

void GeoData::setSeaLevelElevation(double value)
{
    _seaLevelElevation = value;
}

double GeoData::coordinateProjectionRadius() const
{
    return _coordinateProjectionRadius;
}

void GeoData::setCoordinateProjectionRadius(double value)
{
    _coordinateProjectionRadius = value;
}

std::string GeoData::coordinateSystemDefinition() const
{
    return _coordinateSystemDefinition;
}

void GeoData::setCoordinateSystemDefinition(const std::string &value)
{
    _coordinateSystemDefinition = value;
}

std::string GeoData::geoRssTag() const
{
    return _geoRssTag;
}

void GeoData::setGeoRssTag(const std::string &value)
{
    _geoRssTag = value;
}

std::string GeoData::observationFromTag() const
{
    return _observationFromTag;
}

void GeoData::setObservationFromTag(const std::string &value)
{
    _observationFromTag = value;
}

std::string GeoData::observationToTag() const
{
    return _observationToTag;
}

void GeoData::setObservationToTag(const std::string &value)
{
    _observationToTag = value;
}

std::vector<GeoData::GeoMeshPoint> GeoData::points() const
{
    return _points;
}

std::vector<GeoData::GeoMeshPoint> &GeoData::points()
{
    return _points;
}

std::vector<GeoData::GeoMeshFace> GeoData::faces() const
{
    return _faces;
}

std::vector<GeoData::GeoMeshFace> &GeoData::faces()
{
    return _faces;
}

}// namespace dwg
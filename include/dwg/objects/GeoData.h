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

#pragma once

#include <dwg/Coordinate.h>
#include <dwg/objects/DesignCoordinatesType.h>
#include <dwg/objects/GeoDataVersion.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/objects/ScaleEstimationType.h>
#include <dwg/units/UnitsType.h>

namespace dwg {

class BlockRecord;
class LIBDWG_API GeoData : public NonGraphicalObject
{
public:
    struct GeoMeshFace
    {
        int index1;
        int index2;
        int index3;
    };

    struct GeoMeshPoint
    {
        XY source;
        XY destination;
    };

public:
    GeoData();
    ~GeoData();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    GeoDataVersion version() const;
    void setVersion(GeoDataVersion);

    DesignCoordinatesType coordinatesType() const;
    void setCoordinatesType(DesignCoordinatesType);

    BlockRecord *hostBlock() const;
    void setHostBlock(BlockRecord *);

    XYZ designPoint() const;
    void setDesignPoint(const XYZ &);

    XYZ referencePoint() const;
    void setReferencePoint(const XYZ &);

    XY northDirection() const;
    void setNorthDirection(const XY &);

    double horizontalUnitScale() const;
    void setHorizontalUnitScale(double);

    double verticalUnitScale() const;
    void setVerticalUnitScale(double);

    UnitsType horizontalUnits() const;
    void setHorizontalUnits(UnitsType);

    UnitsType verticalUnits() const;
    void setVerticalUnits(UnitsType);

    XYZ upDirection() const;
    void setUpDirection(const XYZ &);

    ScaleEstimationType scaleEstimationMethod() const;
    void setScaleEstimationMethod(ScaleEstimationType);

    bool enableSeaLevelCorrection() const;
    void setEnableSeaLevelCorrection(bool);

    double userSpecifiedScaleFactor() const;
    void setUserSpecifiedScaleFactor(double);

    double seaLevelElevation() const;
    void setSeaLevelElevation(double);

    double coordinateProjectionRadius() const;
    void setCoordinateProjectionRadius(double);

    std::string coordinateSystemDefinition() const;
    void setCoordinateSystemDefinition(const std::string &);

    std::string geoRssTag() const;
    void setGeoRssTag(const std::string &);

    std::string observationFromTag() const;
    void setObservationFromTag(const std::string &);

    std::string observationToTag() const;
    void setObservationToTag(const std::string &);

    std::string observationCoverageTag() const;
    void setObservationCoverageTag(const std::string &);

    std::vector<GeoMeshPoint> points() const;
    std::vector<GeoMeshPoint> &points();

    std::vector<GeoMeshFace> faces() const;
    std::vector<GeoMeshFace> &faces();

private:
    GeoDataVersion _version;
    DesignCoordinatesType _coordinatesType;
    BlockRecord *_hostBlock;
    XYZ _designPoint;
    XYZ _referencePoint;
    XY _northDirection;
    double _horizontalUnitScale;
    double _verticalUnitScale;
    UnitsType _horizontalUnits;
    UnitsType _verticalUnits;
    XYZ _upDirection;
    ScaleEstimationType _scaleEstimationMethod;
    bool _enableSeaLevelCorrection;
    double _userSpecifiedScaleFactor;
    double _seaLevelElevation;
    double _coordinateProjectionRadius;
    std::string _coordinateSystemDefinition;
    std::string _geoRssTag;
    std::string _observationFromTag;
    std::string _observationToTag;
    std::string _observationCoverageTag;
    std::vector<GeoMeshPoint> _points;
    std::vector<GeoMeshFace> _faces;
};

}// namespace dwg
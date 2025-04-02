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
 #include <dwg/CadUtils_p.h>
 #include <dwg/header/CadHeader.h>
 #include <dwg/tables/DimensionStyle.h>
 #include <dwg/tables/TextStyle.h>
 #include <dwg/tables/UCS.h>
#include <stdexcept>

#ifdef _WIN32
#include <Windows.h>
#else

#endif

namespace dwg {

CadHeader::CadHeader()
{
#ifdef _WIN32
#else
#endif
    // _fingerPrintGuid = GUID;
}

CadHeader::CadHeader(CadDocument *document) {}

CadHeader::CadHeader(ACadVersion version) : _version(version) { setVersion(version); }

std::string CadHeader::versionString() const { return CadUtils::GetNameFromVersion(_version); }

void CadHeader::setVersionString(const std::string &value) { _version = CadUtils::GetVersionFromName(value); }

ACadVersion CadHeader::version() const { return _version; }

void CadHeader::setVersion(ACadVersion value)
{
    _version = value;
    switch (_version)
    {
        case ACadVersion::AC1015:
            _maintenanceVersion = 20;
            break;
        case ACadVersion::AC1018:
            _maintenanceVersion = 104;
            break;
        case ACadVersion::AC1021:
            _maintenanceVersion = 50;
            break;
        case ACadVersion::AC1024:
            _maintenanceVersion = 226;
            break;
        case ACadVersion::AC1027:
            _maintenanceVersion = 125;
            break;
        case ACadVersion::AC1032:
            _maintenanceVersion = 228;
            break;
        default:
            _maintenanceVersion = 0;
            break;
    };
}

short CadHeader::maintenanceVersion() const { return _maintenanceVersion; }

void CadHeader::setMaintenanceVersion(short value) { _maintenanceVersion = value; }

std::string CadHeader::codePage() const { return _codePage; }

void CadHeader::setCodePage(const std::string &value) { _codePage = value; }

std::string CadHeader::lastSavedBy() const { return _lastSavedBy; }

void CadHeader::setLastSavedBy(const std::string &value) { _lastSavedBy = value; }

bool CadHeader::associatedDimensions() const { return _associatedDimensions; }

void CadHeader::setAssociatedDimensions(bool value) { _associatedDimensions = value; }

bool CadHeader::updateDimensionsWhileDragging() const { return _updateDimensionsWhileDragging; }

void CadHeader::setUpdateDimensionsWhileDragging(bool value) { _updateDimensionsWhileDragging = value; }

bool CadHeader::DIMSAV() const { return _DIMSAV; }

void CadHeader::setDIMSAV(bool value) { _DIMSAV = value; }

MeasurementUnits CadHeader::measurementUnits() const { return _measurementUnits; }

void CadHeader::setMeasurementUnits(MeasurementUnits value) { _measurementUnits = value; }

bool CadHeader::polylineLineTypeGeneration() const { return _polylineLineTypeGeneration; }

void CadHeader::setPolylineLineTypeGeneration(bool value) { _polylineLineTypeGeneration = value; }

bool CadHeader::orthoMode() const { return _orthoMode; }

void CadHeader::setOrthoMode(bool value) { _orthoMode = value; }

bool CadHeader::regenerationMode() const { return _regenerationMode; }

void CadHeader::setRegenerationMode(bool value) { _regenerationMode = value; }

bool CadHeader::fillMode() const { return _fillMode; }

void CadHeader::setFillMode(bool value) { _fillMode = value; }

bool CadHeader::quickTextMode() const { return _quickTextMode; }

void CadHeader::setQuickTextMode(bool value) { _quickTextMode = value; }

SpaceLineTypeScaling CadHeader::paperSpaceLineTypeScaling() const { return _paperSpaceLineTypeScaling; }

void CadHeader::setPaperSpaceLineTypeScaling(SpaceLineTypeScaling value) { _paperSpaceLineTypeScaling = value; }

bool CadHeader::limitCheckingOn() const { return _limitCheckingOn; }

void CadHeader::setLimitCheckingOn(bool value) { _limitCheckingOn = value; }

bool CadHeader::blipMode() const { return _blipMode; }

void CadHeader::setBlipMode(bool value) { _blipMode = value; }

bool CadHeader::userTimer() const { return _userTimer; }

void CadHeader::setUserTimer(bool value) { _userTimer = value; }

bool CadHeader::sketchPolylines() const { return _sketchPolylines; }

void CadHeader::setSketchPolylines(bool value) { _sketchPolylines = value; }

AngularDirection CadHeader::angularDirection() const { return _angularDirection; }

void CadHeader::setAngularDirection(AngularDirection value) { _angularDirection = value; }

bool CadHeader::showSplineControlPoints() const { return _showSplineControlPoints; }

void CadHeader::setShowSplineControlPoints(bool value) { _showSplineControlPoints = value; }

bool CadHeader::mirrorText() const { return _mirrorText; }

void CadHeader::setMirrorText(bool value) { _mirrorText = value; }

bool CadHeader::worldView() const { return _worldView; }

void CadHeader::setWorldView(bool value) { _worldView = value; }

bool CadHeader::showModelSpace() const { return _showModelSpace; }

void CadHeader::setShowModelSpace(bool value) { _showModelSpace = value; }

bool CadHeader::paperSpaceLimitsChecking() const { return _paperSpaceLimitsChecking; }

void CadHeader::setPaperSpaceLimitsChecking(bool value) { _paperSpaceLimitsChecking = value; }

bool CadHeader::retainXRefDependentVisibilitySettings() const { return _retainXRefDependentVisibilitySettings; }

void CadHeader::setRetainXRefDependentVisibilitySettings(bool value) { _retainXRefDependentVisibilitySettings = value; }

bool CadHeader::displaySilhouetteCurves() const { return _displaySilhouetteCurves; }

void CadHeader::setDisplaySilhouetteCurves(bool value) { _displaySilhouetteCurves = value; }

bool CadHeader::createEllipseAsPolyline() const { return _createEllipseAsPolyline; }

void CadHeader::setCreateEllipseAsPolyline(bool value) { _createEllipseAsPolyline = value; }

bool CadHeader::proxyGraphics() const { return _proxyGraphics; }

void CadHeader::setProxyGraphics(bool value) { _proxyGraphics = value; }

short CadHeader::spatialIndexMaxTreeDepth() const { return _spatialIndexMaxTreeDepth; }

void CadHeader::setSpatialIndexMaxTreeDepth(short value) { _spatialIndexMaxTreeDepth = value; }

LinearUnitFormat CadHeader::linearUnitFormat() const { return _linearUnitFormat; }

void CadHeader::setLinearUnitFormat(LinearUnitFormat value) { _linearUnitFormat = value; }

short CadHeader::linearUnitPrecision() const { return _linearUnitPrecision; }

void CadHeader::setLinearUnitPrecision(short value) { _linearUnitPrecision = value; }

AngularUnitFormat CadHeader::angularUnit() const { return _angularUnit; }

void CadHeader::setAngularUnit(AngularUnitFormat value) { _angularUnit = value; }

short CadHeader::angularUnitPrecision() const { return _angularUnitPrecision; }

void CadHeader::setAngularUnitPrecision(short value) { _angularUnitPrecision = value; }

ObjectSnapMode CadHeader::objectSnapMode() const { return _objectSnapMode; }

void CadHeader::setObjectSnapMode(ObjectSnapMode value) { _objectSnapMode = value; }

AttributeVisibilityMode CadHeader::attributeVisibility() const { return _attributeVisibility; }

void CadHeader::setAttributeVisibility(AttributeVisibilityMode value) { _attributeVisibility = value; }

short CadHeader::pointDisplayMode() const { return _pointDisplayMode; }

void CadHeader::setPointDisplayMode(short value) { _pointDisplayMode = value; }

short CadHeader::userShort1() const { return _userShort1; }

void CadHeader::setUserShort1(short value) { _userShort1 = value; }

short CadHeader::userShort2() const { return _userShort2; }

void CadHeader::setUserShort2(short value) { _userShort2 = value; }

short CadHeader::userShort3() const { return _userShort3; }

void CadHeader::setUserShort3(short value) { _userShort3 = value; }

short CadHeader::userShort4() const { return _userShort4; }

void CadHeader::setUserShort4(short value) { _userShort4 = value; }

short CadHeader::userShort5() const { return _userShort5; }

void CadHeader::setUserShort5(short value) { _userShort5 = value; }

short CadHeader::numberOfSplineSegments() const { return _numberOfSplineSegments; }

void CadHeader::setNumberOfSplineSegments(short value) { _numberOfSplineSegments = value; }

short CadHeader::surfaceDensityU() const { return _surfaceDensityU; }

void CadHeader::setSurfaceDensityU(short value) { _surfaceDensityU = value; }

short CadHeader::surfaceDensityV() const { return _surfaceDensityV; }

void CadHeader::setSurfaceDensityV(short value) { _surfaceDensityV = value; }

short CadHeader::surfaceType() const { return _surfaceType; }

void CadHeader::setSurfaceType(short value) { _surfaceType = value; }

short CadHeader::surfaceMeshTabulationCount1() const { return _surfaceMeshTabulationCount1; }

void CadHeader::setSurfaceMeshTabulationCount1(short value) { _surfaceMeshTabulationCount1 = value; }

short CadHeader::surfaceMeshTabulationCount2() const { return _surfaceMeshTabulationCount2; }

void CadHeader::setSurfaceMeshTabulationCount2(short value) { _surfaceMeshTabulationCount2 = value; }

SplineType CadHeader::splineType() const { return _splineType; }

void CadHeader::setSplineType(SplineType value) { _splineType = value; }

ShadeEdgeType CadHeader::shadeEdge() const { return _shadeEdge; }

void CadHeader::setShadeEdge(ShadeEdgeType value) { _shadeEdge = value; }

short CadHeader::shadeDiffuseToAmbientPercentage() const { return _shadeDiffuseToAmbientPercentage; }

void CadHeader::setShadeDiffuseToAmbientPercentage(short value) { _shadeDiffuseToAmbientPercentage = value; }

short CadHeader::unitMode() const { return _unitMode; }

void CadHeader::setUnitMode(short value) { _unitMode = value; }

short CadHeader::maxViewportCount() const { return _maxViewportCount; }

void CadHeader::setMaxViewportCount(short value) { _maxViewportCount = value; }

short CadHeader::surfaceIsolineCount() const { return _surfaceIsolineCount; }

void CadHeader::setSurfaceIsolineCount(short value)
{
    if (value < 0 || value > 2047)
        throw new std::out_of_range("ISOLINES valid values are from 0 to 2047");
    _surfaceIsolineCount = value;
}

VerticalAlignmentType CadHeader::currentMultilineJustification() const { return _currentMultilineJustification; }

void CadHeader::setCurrentMultilineJustification(VerticalAlignmentType value)
{
    _currentMultilineJustification = value;
}

short CadHeader::textQuality() const { return _textQuality; }

void CadHeader::setTextQuality(short value)
{
    if (value < 0 || value > 100)
        throw new std::out_of_range("TEXTQLTY valid values are from 0 to 100");
    _textQuality = value;
}

double CadHeader::lineTypeScale() const { return _lineTypeScale; }

void CadHeader::setLineTypeScale(double value) { _lineTypeScale = value; }

double CadHeader::textHeightDefault() const { return _textHeightDefault; }

void CadHeader::setTextHeightDefault(double value) { _textHeightDefault = value; }

std::string CadHeader::textStyleName() const { return std::string(); }

void CadHeader::setTextStyleName(const std::string &value)
{
    // TODO
}

std::string CadHeader::currentLayerName() const { return std::string(); }

void CadHeader::setCurrentLayerName(const std::string &value) {}

std::string CadHeader::currentLineTypeName() const { return std::string(); }

void CadHeader::setCurrentLineTypeName(const std::string &value) {}

std::string CadHeader::multiLineStyleName() const { return std::string(); }

void CadHeader::setMultiLineStyleName(const std::string &value) {}

double CadHeader::traceWidthDefault() const { return _traceWidthDefault; }

void CadHeader::setTraceWidthDefault(double value) { _traceWidthDefault = value; }

double CadHeader::sketchIncrement() const { return _sketchIncrement; }

void CadHeader::setSketchIncrement(double value) { _sketchIncrement = value; }

double CadHeader::filletRadius() const { return _filletRadius; }

void CadHeader::setFilletRadius(double value) { _filletRadius = value; }

double CadHeader::thicknessDefault() const { return _thicknessDefault; }

void CadHeader::setThicknessDefault(double value) { _thicknessDefault = value; }

double CadHeader::angleBase() const { return _angleBase; }

void CadHeader::setAngleBase(double value) { _angleBase = value; }

double CadHeader::pointDisplaySize() const { return _pointDisplaySize; }

void CadHeader::setPointDisplaySize(double value) { _pointDisplaySize = value; }

double CadHeader::polylineWidthDefault() const { return _polylineWidthDefault; }

void CadHeader::setPolylineWidthDefault(double value) { _polylineWidthDefault = value; }

double CadHeader::userDouble1() const { return _userDouble1; }

void CadHeader::setUserDouble1(double value) { _userDouble1 = value; }

double CadHeader::userDouble2() const { return _userDouble2; }

void CadHeader::setUserDouble2(double value) { _userDouble2 = value; }

double CadHeader::userDouble3() const { return _userDouble3; }

void CadHeader::setUserDouble3(double value) { _userDouble3 = value; }

double CadHeader::userDouble4() const { return _userDouble4; }

void CadHeader::setUserDouble4(double value) { _userDouble4 = value; }

double CadHeader::userDouble5() const { return _userDouble5; }

void CadHeader::setUserDouble5(double value) { _userDouble5 = value; }

double CadHeader::chamferDistance1() const { return _chamferDistance1; }

void CadHeader::setChamferDistance1(double value) { _chamferDistance1 = value; }

double CadHeader::chamferDistance2() const { return _chamferDistance2; }

void CadHeader::setChamferDistance2(double value) { _chamferDistance2 = value; }

double CadHeader::chamferLength() const { return _chamferLength; }

void CadHeader::setChamferLength(double value) { _chamferLength = value; }

double CadHeader::chamferAngle() const { return _chamferAngle; }

void CadHeader::setChamferAngle(double value) { _chamferAngle = value; }

double CadHeader::facetResolution() const { return _facetResolution; }

void CadHeader::setFacetResolution(double value)
{
    if (value < 0.01 || value > 10)
        throw new std::out_of_range("FACETRES valid values are from 0.01 to 10.0");
    _facetResolution = value;
}

double CadHeader::currentMultilineScale() const { return _currentMultilineScale; }

void CadHeader::setCurrentMultilineScale(double value) { _currentMultilineScale = value; }

double CadHeader::currentEntityLinetypeScale() const { return _currentEntityLinetypeScale; }

void CadHeader::setCurrentEntityLinetypeScale(double value) { _currentEntityLinetypeScale = value; }

std::string CadHeader::menuFileName() const { return _menuFileName; }

void CadHeader::setMenuFileName(const std::string &value) { _menuFileName = value; }

unsigned long long CadHeader::handleSeed() const { return _handleSeed; }

void CadHeader::setHandleSeed(unsigned long long value) { _handleSeed = value; }

DateTime CadHeader::createDateTime() const { return _createDateTime; }

void CadHeader::setCreateDateTime(const DateTime &value) { _createDateTime = value; }

DateTime CadHeader::universalCreateDateTime() const { return _universalCreateDateTime; }

void CadHeader::setUniversalCreateDateTime(const DateTime &value) { _universalCreateDateTime = value; }

DateTime CadHeader::updateDateTime() const { return _updateDateTime; }

void CadHeader::setUpdateDateTime(const DateTime &value) { _updateDateTime = value; }

DateTime CadHeader::universalUpdateDateTime() const { return _universalUpdateDateTime; }

void CadHeader::setUniversalUpdateDateTime(const DateTime &value) { _universalUpdateDateTime = value; }

double CadHeader::totalEditingTime() const { return _totalEditingTime; }

void CadHeader::setTotalEditingTime(double value) { _totalEditingTime = value; }

double CadHeader::userElapsedTimeSpan() const { return _userElapsedTimeSpan; }

void CadHeader::setUserElapsedTimeSpan(double value) { _userElapsedTimeSpan = value; }

Color CadHeader::currentEntityColor() const { return _currentEntityColor; }

void CadHeader::setCurrentEntityColor(const Color &value) { _currentEntityColor = value; }

double CadHeader::viewportDefaultViewScaleFactor() const { return _viewportDefaultViewScaleFactor; }

void CadHeader::setViewportDefaultViewScaleFactor(double value) { _viewportDefaultViewScaleFactor = value; }

XYZ CadHeader::paperSpaceInsertionBase() const { return _paperSpaceInsertionBase; }

void CadHeader::setPaperSpaceInsertionBase(const XYZ &value) { _paperSpaceInsertionBase = value; }

XYZ CadHeader::paperSpaceExtMin() const { return _paperSpaceExtMin; }

void CadHeader::setPaperSpaceExtMin(const XYZ &value) { _paperSpaceExtMin = value; }

XYZ CadHeader::paperSpaceExtMax() const { return _paperSpaceExtMax; }

void CadHeader::setPaperSpaceExtMax(const XYZ &value) { _paperSpaceExtMax = value; }

XY CadHeader::paperSpaceLimitsMin() const { return _paperSpaceLimitsMin; }

void CadHeader::setPaperSpaceLimitsMin(const XY &value) { _paperSpaceLimitsMin = value; }

XY CadHeader::paperSpaceLimitsMax() const { return _paperSpaceLimitsMax; }

void CadHeader::setPaperSpaceLimitsMax(const XY &value) { _paperSpaceLimitsMax = value; }

double CadHeader::paperSpaceElevation() const
{
    if (_paperSpaceUcs)
    {
        return _paperSpaceUcs->elevation();
    }
    return 0.0;
}

void CadHeader::setPaperSpaceElevation(double value)
{
    if (_paperSpaceUcs)
    {
        _paperSpaceUcs->setElevation(value);
    }
}

std::string CadHeader::paperSpaceBaseName() const
{
    if (_paperSpaceUcsBase)
    {
        return _paperSpaceUcsBase->name();
    }
    return std::string();
}

void CadHeader::setPaperSpaceBaseName(const std::string &value)
{
    if (_paperSpaceUcsBase)
    {
        _paperSpaceUcsBase->setName(value);
    }
}

std::string CadHeader::paperSpaceName() const
{
    if (_paperSpaceUcs)
    {
        return _paperSpaceUcs->name();
    }
    return std::string();
}

void CadHeader::setPaperSpaceName(const std::string &value)
{
    if (_paperSpaceUcs)
    {
        return _paperSpaceUcs->setName(value);
    }
}

XYZ CadHeader::paperSpaceUcsOrigin() const
{
    if (_paperSpaceUcs)
    {
        return _paperSpaceUcs->origin();
    }
    return XYZ::Zero;
}

void CadHeader::setPaperSpaceUcsOrigin(const XYZ &value)
{
    if (_paperSpaceUcs)
    {
        return _paperSpaceUcs->setOrigin(value);
    }
}

XYZ CadHeader::paperSpaceUcsXAxis() const
{
    if (_paperSpaceUcs)
    {
        return _paperSpaceUcs->xAxis();
    }
    return XYZ::Zero;
}

void CadHeader::setPaperSpaceUcsXAxis(const XYZ &value)
{
    if (_paperSpaceUcs)
    {
        _paperSpaceUcs->setXAxis(value);
    }
}

XYZ CadHeader::paperSpaceUcsYAxis() const
{
    if (_paperSpaceUcs)
    {
        return _paperSpaceUcs->yAxis();
    }
    return XYZ::Zero;
}

void CadHeader::setPaperSpaceUcsYAxis(const XYZ &value)
{
    if (_paperSpaceUcs)
    {
        _paperSpaceUcs->setXAxis(value);
    }
}

XYZ CadHeader::paperSpaceOrthographicTopDOrigin() const { return _paperSpaceOrthographicTopDOrigin; }

void CadHeader::setPaperSpaceOrthographicTopDOrigin(const XYZ &value) { _paperSpaceOrthographicTopDOrigin = value; }

XYZ CadHeader::paperSpaceOrthographicBottomDOrigin() const { return _paperSpaceOrthographicBottomDOrigin; }

void CadHeader::setPaperSpaceOrthographicBottomDOrigin(const XYZ &value)
{
    _paperSpaceOrthographicBottomDOrigin = value;
}

XYZ CadHeader::paperSpaceOrthographicLeftDOrigin() const { return _paperSpaceOrthographicLeftDOrigin; }

void CadHeader::setPaperSpaceOrthographicLeftDOrigin(const XYZ &value) { _paperSpaceOrthographicLeftDOrigin = value; }

XYZ CadHeader::paperSpaceOrthographicRightDOrigin() const { return _paperSpaceOrthographicRightDOrigin; }

void CadHeader::setPaperSpaceOrthographicRightDOrigin(const XYZ &value) { _paperSpaceOrthographicRightDOrigin = value; }

XYZ CadHeader::paperSpaceOrthographicFrontDOrigin() const { return _paperSpaceOrthographicFrontDOrigin; }

void CadHeader::setPaperSpaceOrthographicFrontDOrigin(const XYZ &value) { _paperSpaceOrthographicFrontDOrigin = value; }

XYZ CadHeader::paperSpaceOrthographicBackDOrigin() const { return _paperSpaceOrthographicBackDOrigin; }

void CadHeader::setPaperSpaceOrthographicBackDOrigin(const XYZ &value) { _paperSpaceOrthographicBackDOrigin = value; }

XYZ CadHeader::modelSpaceOrthographicTopDOrigin() const { return _modelSpaceOrthographicTopDOrigin; }

void CadHeader::setModelSpaceOrthographicTopDOrigin(const XYZ &value) { _modelSpaceOrthographicTopDOrigin = value; }

XYZ CadHeader::modelSpaceOrthographicBottomDOrigin() const { return _modelSpaceOrthographicBottomDOrigin; }

void CadHeader::setModelSpaceOrthographicBottomDOrigin(const XYZ &value)
{
    _modelSpaceOrthographicBottomDOrigin = value;
}

XYZ CadHeader::modelSpaceOrthographicLeftDOrigin() const { return _modelSpaceOrthographicLeftDOrigin; }

void CadHeader::setModelSpaceOrthographicLeftDOrigin(const XYZ &value) { _modelSpaceOrthographicLeftDOrigin = value; }

XYZ CadHeader::modelSpaceOrthographicRightDOrigin() const { return _modelSpaceOrthographicRightDOrigin; }

void CadHeader::setModelSpaceOrthographicRightDOrigin(const XYZ &value) { _modelSpaceOrthographicRightDOrigin = value; }

XYZ CadHeader::modelSpaceOrthographicFrontDOrigin() const { return _modelSpaceOrthographicFrontDOrigin; }

void CadHeader::setModelSpaceOrthographicFrontDOrigin(const XYZ &value) { _modelSpaceOrthographicFrontDOrigin = value; }

XYZ CadHeader::modelSpaceOrthographicBackDOrigin() const { return _modelSpaceOrthographicBackDOrigin; }

void CadHeader::setModelSpaceOrthographicBackDOrigin(const XYZ &value) { _modelSpaceOrthographicBackDOrigin = value; }

XYZ CadHeader::modelSpaceInsertionBase() const { return _modelSpaceInsertionBase; }

void CadHeader::setModelSpaceInsertionBase(const XYZ &value) { _modelSpaceInsertionBase = value; }

XYZ CadHeader::modelSpaceExtMin() const { return _modelSpaceExtMin; }

void CadHeader::setModelSpaceExtMin(const XYZ &value) { _modelSpaceExtMin = value; }

XYZ CadHeader::modelSpaceExtMax() const { return _modelSpaceExtMax; }

void CadHeader::setModelSpaceExtMax(const XYZ &value) { _modelSpaceExtMax = value; }

XY CadHeader::modelSpaceLimitsMin() const { return _modelSpaceLimitsMin; }

void CadHeader::setModelSpaceLimitsMin(const XY &value) { _modelSpaceLimitsMin = value; }

XY CadHeader::modelSpaceLimitsMax() const { return _modelSpaceLimitsMax; }

void CadHeader::setModelSpaceLimitsMax(const XY &value) { _modelSpaceLimitsMax = value; }

std::string CadHeader::ucsBaseName() const
{
    if (_modelSpaceUcsBase)
    {
        return _modelSpaceUcsBase->name();
    }
    return std::string();
}

void CadHeader::setUcsBaseName(const std::string &value)
{
    if (_modelSpaceUcsBase)
    {
        _modelSpaceUcsBase->setName(value);
    }
}

std::string CadHeader::ucsName() const
{
    if (_modelSpaceUcs)
    {
        return _modelSpaceUcs->name();
    }
    return std::string();
}

void CadHeader::setUcsName(const std::string &value)
{
    if (_modelSpaceUcs)
    {
        _modelSpaceUcs->setName(value);
    }
}

double CadHeader::elevation() const
{
    if (_modelSpaceUcs)
    {
        return _modelSpaceUcs->elevation();
    }
    return 0.0;
}

void CadHeader::setElevation(double value)
{
    if (_modelSpaceUcs)
    {
        _modelSpaceUcs->setElevation(value);
    }
}

XYZ CadHeader::modelSpaceOrigin() const
{
    if (_modelSpaceUcs)
    {
        return _modelSpaceUcs->origin();
    }
    return XYZ::Zero;
}

void CadHeader::setModelSpaceOrigin(const XYZ &value)
{
    if (_modelSpaceUcs)
    {
        _modelSpaceUcs->setOrigin(value);
    }
}

XYZ CadHeader::modelSpaceXAxis() const
{
    if (_modelSpaceUcs)
    {
        return _modelSpaceUcs->xAxis();
    }
    return XYZ::Zero;
}

void CadHeader::setModelSpaceXAxis(const XYZ &value)
{
    if (_modelSpaceUcs)
    {
        _modelSpaceUcs->setXAxis(value);
    }
}

XYZ CadHeader::modelSpaceYAxis() const
{
    if (_modelSpaceUcs)
    {
        return _modelSpaceUcs->yAxis();
    }
    return XYZ::Zero;
}

void CadHeader::setModelSpaceYAxis(const XYZ &value)
{
    if (_modelSpaceUcs)
    {
        _modelSpaceUcs->setYAxis(value);
    }
}

std::string CadHeader::dimensionBlockName() const { return _dimensionBlockName; }

void CadHeader::setDimensionBlockName(const std::string &value) { _dimensionBlockName = value; }

std::string CadHeader::arrowBlockName() const { return _arrowBlockName; }

void CadHeader::setArrowBlockName(const std::string &value) { _arrowBlockName = value; }

std::string CadHeader::dimensionBlockNameFirst() const { return _dimensionBlockNameFirst; }

void CadHeader::setDimensionBlockNameFirst(const std::string &value) { _dimensionBlockNameFirst = value; }

std::string CadHeader::dimensionBlockNameSecond() const { return _dimensionBlockNameSecond; }

void CadHeader::setDimensionBlockNameSecond(const std::string &value) { _dimensionBlockNameSecond = value; }

short CadHeader::stackedTextAlignment() const { return _stackedTextAlignment; }

void CadHeader::setStackedTextAlignment(short value) { _stackedTextAlignment = value; }

short CadHeader::stackedTextSizePercentage() const { return _stackedTextSizePercentage; }

void CadHeader::setStackedTextSizePercentage(short value) { _stackedTextSizePercentage = value; }

std::string CadHeader::hyperLinkBase() const { return _hyperLinkBase; }

void CadHeader::setHyperLinkBase(const std::string &value) { _hyperLinkBase = value; }

LineweightType CadHeader::currentEntityLineWeight() const { return _currentEntityLineWeight; }

void CadHeader::setCurrentEntityLineWeight(LineweightType value) { _currentEntityLineWeight = value; }

short CadHeader::endCaps() const { return _endCaps; }

void CadHeader::setEndCaps(short value) { _endCaps = value; }

short CadHeader::joinStyle() const { return _joinStyle; }

void CadHeader::setJoinStyle(short value) { _joinStyle = value; }

bool CadHeader::displayLineWeight() const { return _displayLineWeight; }

void CadHeader::setDisplayLineWeight(bool value) { _displayLineWeight = value; }

bool CadHeader::xedit() const { return _xedit; }

void CadHeader::setXEdit(bool value) { _xedit = value; }

bool CadHeader::extendedNames() const { return _extendedNames; }

void CadHeader::setExtendedNames(bool value) { _extendedNames = value; }

short CadHeader::plotStyleMode() const { return _plotStyleMode; }

void CadHeader::setPlotStyleMode(short value) { _plotStyleMode = value; }

bool CadHeader::loadOLEObject() const { return _loadOLEObject; }

void CadHeader::setLoadOLEObject(bool value) { _loadOLEObject = value; }

UnitsType CadHeader::insUnits() const { return _insUnits; }

void CadHeader::setInsUnits(UnitsType value) { _insUnits = value; }

EntityPlotStyleType CadHeader::currentEntityPlotStyle() const { return _currentEntityPlotStyle; }

void CadHeader::setCurrentEntityPlotStyle(EntityPlotStyleType value) { _currentEntityPlotStyle = value; }

std::string CadHeader::fingerPrintGuid() const { return _fingerPrintGuid; }

void CadHeader::setFingerPrintGuid(const std::string &value) { _fingerPrintGuid = value; }

std::string CadHeader::versionGuid() const { return _versionGuid; }

void CadHeader::setVersionGuid(const std::string &value) { _versionGuid = value; }

ObjectSortingFlags CadHeader::entitySortingFlags() const { return _entitySortingFlags; }

void CadHeader::setEntitySortingFlags(ObjectSortingFlags value) { _entitySortingFlags = value; }

IndexCreationFlags CadHeader::indexCreationFlags() const { return _indexCreationFlags; }

void CadHeader::setIndexCreationFlags(IndexCreationFlags value) { _indexCreationFlags = value; }

unsigned char CadHeader::hideText() const { return _hideText; }

void CadHeader::setHideText(unsigned char value) { _hideText = value; }

unsigned char CadHeader::externalReferenceClippingBoundaryType() const
{
    return _externalReferenceClippingBoundaryType;
}

void CadHeader::setExternalReferenceClippingBoundaryType(unsigned char value)
{
    _externalReferenceClippingBoundaryType = value;
}

DimensionAssociation CadHeader::dimensionAssociativity() const { return _dimensionAssociativity; }

void CadHeader::setDimensionAssociativity(DimensionAssociation value) { _dimensionAssociativity = value; }

unsigned char CadHeader::haloGapPercentage() const { return _haloGapPercentage; }

void CadHeader::setHaloGapPercentage(unsigned char value) { _haloGapPercentage = value; }

Color CadHeader::obscuredColor() const { return _obscuredColor; }

void CadHeader::setObscuredColor(const Color &value) { _obscuredColor = value; }

Color CadHeader::interfereColor() const { return _interfereColor; }

void CadHeader::setInterfereColor(const Color &value) { _interfereColor = value; }

unsigned char CadHeader::obscuredType() const { return _obscuredType; }

void CadHeader::setObscuredType(unsigned char value) { _obscuredType = value; }

unsigned char CadHeader::intersectionDisplay() const { return _intersectionDisplay; }

void CadHeader::setIntersectionDisplay(unsigned char value) { _intersectionDisplay = value; }

std::string CadHeader::projectName() const { return _projectName; }

void CadHeader::setProjectName(const std::string &value) { _projectName = value; }

bool CadHeader::cameraDisplayObjects() const { return _cameraDisplayObjects; }

void CadHeader::setCameraDisplayObjects(bool value) { _cameraDisplayObjects = value; }

double CadHeader::stepsPerSecond() const { return _stepsPerSecond; }

void CadHeader::setStepsPerSecond(double value)
{
    if (value < 1 || value > 30)
        throw new std::out_of_range("FACETRES valid values are from 1 to 30");
    _stepsPerSecond = value;
}

double CadHeader::stepSize() const { return _stepSize; }

void CadHeader::setStepSize(double value) { _stepSize = value; }

double CadHeader::dw3DPrecision() const { return _dw3DPrecision; }

void CadHeader::setDw3DPrecision(double value) { _dw3DPrecision = value; }

double CadHeader::lensLength() const { return _lensLength; }

void CadHeader::setLensLength(double value) { _lensLength = value; }

double CadHeader::cameraHeight() const { return _cameraHeight; }

void CadHeader::setCameraHeight(double value) { _cameraHeight = value; }

char CadHeader::solidsRetainHistory() const { return _solidsRetainHistory; }

void CadHeader::setSolidsRetainHistory(char value) { _solidsRetainHistory = value; }

char CadHeader::showSolidsHistory() const { return _showSolidsHistory; }

void CadHeader::setShowSolidsHistory(char value) { _showSolidsHistory = value; }

double CadHeader::sweptSolidWidth() const { return _sweptSolidWidth; }

void CadHeader::setSweptSolidWidth(double value) { _sweptSolidWidth = value; }

double CadHeader::sweptSolidHeight() const { return _sweptSolidHeight; }

void CadHeader::setSweptSolidHeight(double value) { _sweptSolidHeight = value; }

double CadHeader::draftAngleFirstCrossSection() const { return _draftAngleFirstCrossSection; }

void CadHeader::setDraftAngleFirstCrossSection(double value) { _draftAngleFirstCrossSection = value; }

double CadHeader::draftAngleSecondCrossSection() const { return _draftAngleSecondCrossSection; }

void CadHeader::setDraftAngleSecondCrossSection(double value) { _draftAngleSecondCrossSection = value; }

double CadHeader::draftMagnitudeFirstCrossSection() const { return _draftMagnitudeFirstCrossSection; }

void CadHeader::setDraftMagnitudeFirstCrossSection(double value) { _draftMagnitudeFirstCrossSection = value; }

double CadHeader::draftMagnitudeSecondCrossSection() const { return _draftMagnitudeSecondCrossSection; }

void CadHeader::setDraftMagnitudeSecondCrossSection(double value) { _draftMagnitudeSecondCrossSection = value; }

short CadHeader::solidLoftedShape() const { return _solidLoftedShape; }

void CadHeader::setSolidLoftedShape(short value) { _solidLoftedShape = value; }

char CadHeader::loftedObjectNormals() const { return _loftedObjectNormals; }

void CadHeader::setLoftedObjectNormals(char value) { _loftedObjectNormals = value; }

double CadHeader::latitude() const { return _latitude; }

void CadHeader::setLatitude(double value) { _latitude = value; }

double CadHeader::longitude() const { return _longitude; }

void CadHeader::setLongitude(double value) { _longitude = value; }

double CadHeader::northDirection() const { return _northDirection; }

void CadHeader::setNorthDirection(double value) { _northDirection = value; }

int CadHeader::timeZone() const { return _timeZone; }

void CadHeader::setTimeZone(int value) { _timeZone = value; }

char CadHeader::displayLightGlyphs() const { return _displayLightGlyphs; }

void CadHeader::setDisplayLightGlyphs(char value) { _displayLightGlyphs = value; }

char CadHeader::dwgUnderlayFramesVisibility() const { return _dwgUnderlayFramesVisibility; }

void CadHeader::setDwgUnderlayFramesVisibility(char value) { _dwgUnderlayFramesVisibility = value; }

char CadHeader::dgnUnderlayFramesVisibility() const { return _dgnUnderlayFramesVisibility; }

void CadHeader::setDgnUnderlayFramesVisibility(char value) { _dgnUnderlayFramesVisibility = value; }

ShadowMode CadHeader::shadowMode() const { return _shadowMode; }

void CadHeader::setShadowMode(ShadowMode value) { _shadowMode = value; }

double CadHeader::shadowPlaneLocation() const { return _shadowPlaneLocation; }

void CadHeader::setShadowPlaneLocation(double value) { _shadowPlaneLocation = value; }

std::string CadHeader::styleSheetName() const { return _styleSheetName; }

void CadHeader::setStyleSheetName(const std::string &value) { _styleSheetName = value; }

std::string CadHeader::dimensionTextStyleName() const
{
    return _dimensionTextStyle->name();
}

void CadHeader::setDimensionTextStyleName(const std::string &value)
{
    if (_document)
    {
        _dimensionTextStyle = _document->textStyles()->getValue(value);
    }
    else
    {
        delete _dimensionTextStyle;
        _dimensionTextStyle = new TextStyle(value);
    }
}

std::string CadHeader::dimensionStyleOverridesName() const
{
    // TODO
    return std::string();
}

void CadHeader::setDimensionStyleOverridesName(const std::string &value)
{
    return _dimensionStyleOverrides->angularDimensionDecimalPlaces();
}

short CadHeader::dimensionAngularDimensionDecimalPlaces() const
{
    _dimensionStyleOverrides->setAngularDimensionDecimalPlaces(value);
}

void CadHeader::setDimensionAngularDimensionDecimalPlaces(short value)
{
    return _dimensionStyleOverrides->decimalPlaces();
}

short CadHeader::dimensionDecimalPlaces() const
{
    _dimensionStyleOverrides->setDecimalPlaces(value);
}

void CadHeader::setDimensionDecimalPlaces(short value)
{
    return _dimensionStyleOverrides->toleranceDecimalPlaces();
}

short CadHeader::dimensionToleranceDecimalPlaces() const
{
    _dimensionStyleOverrides->setToleranceDecimalPlaces(value);
}

void CadHeader::setDimensionToleranceDecimalPlaces(short value)
{
    _dimensionStyleOverrides->setToleranceDecimalPlaces(value);
}

bool CadHeader::dimensionAlternateUnitDimensioning() const
{
    return _dimensionStyleOverrides->alternateUnitDimensioning();
}

void CadHeader::setDimensionAlternateUnitDimensioning(bool value)
{
    _dimensionStyleOverrides->setAlternateUnitDimensioning(value);
}

LinearUnitFormat CadHeader::dimensionAlternateUnitFormat() const
{
    return _dimensionStyleOverrides->alternateUnitFormat();
}

void CadHeader::setDimensionAlternateUnitFormat(LinearUnitFormat value) 
{
    _dimensionStyleOverrides->setAlternateUnitFormat(value);
}

double CadHeader::dimensionAlternateUnitScaleFactor() const
{
    return _dimensionStyleOverrides->alternateUnitScaleFactor();
}

void CadHeader::setDimensionAlternateUnitScaleFactor(double value) 
{
    _dimensionStyleOverrides->setAlternateUnitScaleFactor(value);
}

double CadHeader::dimensionExtensionLineOffset() const 
{    
    return _dimensionStyleOverrides->extensionLineOffset(); 
}

void CadHeader::setDimensionExtensionLineOffset(double value) 
{
    _dimensionStyleOverrides->setExtensionLineOffset(value); 
}

double CadHeader::dimensionScaleFactor() const { return _dimensionStyleOverrides->scaleFactor(); }

void CadHeader::setDimensionScaleFactor(double value) { _dimensionStyleOverrides->setScaleFactor(value); }

short CadHeader::dimensionAlternateUnitDecimalPlaces() const { return _dimensionStyleOverrides->alternateUnitDecimalPlaces(); }

void CadHeader::setDimensionAlternateUnitDecimalPlaces(short value) { _dimensionStyleOverrides->setAlternateUnitDecimalPlaces(value); }

short CadHeader::dimensionAlternateUnitToleranceDecimalPlaces() const { return _dimensionStyleOverrides->alternateUnitToleranceDecimalPlaces(); }

void CadHeader::setDimensionAlternateUnitToleranceDecimalPlaces(short value) { _dimensionStyleOverrides->setAlternateUnitToleranceDecimalPlaces(value); }

AngularUnitFormat CadHeader::dimensionAngularUnit() const { return _dimensionStyleOverrides->angularUnit(); }

void CadHeader::setDimensionAngularUnit(AngularUnitFormat value) { _dimensionStyleOverrides->setAngularUnit(value); }

FractionFormat CadHeader::dimensionFractionFormat() const { return _dimensionStyleOverrides->fractionFormat(); }

void CadHeader::setDimensionFractionFormat(FractionFormat value) { _dimensionStyleOverrides->setFractionFormat(value); }

LinearUnitFormat CadHeader::dimensionLinearUnitFormat() const { return _dimensionStyleOverrides->linearUnitFormat(); }

void CadHeader::setDimensionLinearUnitFormat(LinearUnitFormat value) { _dimensionStyleOverrides->setLinearUnitFormat(value); }

char CadHeader::dimensionDecimalSeparator() const { return _dimensionStyleOverrides->decimalSeparator(); }

void CadHeader::setDimensionDecimalSeparator(char value) { _dimensionStyleOverrides->setDecimalSeparator(value); }

TextMovement CadHeader::dimensionTextMovement() const { return _dimensionStyleOverrides->textMovement(); }

void CadHeader::setDimensionTextMovement(TextMovement value) { _dimensionStyleOverrides->setTextMovement(value); }

DimensionTextHorizontalAlignment CadHeader::dimensionTextHorizontalAlignment() const { return _dimensionStyleOverrides->textHorizontalAlignment(); }

void CadHeader::setDimensionTextHorizontalAlignment(DimensionTextHorizontalAlignment value) { _dimensionStyleOverrides->setTextHorizontalAlignment(value); }

bool CadHeader::dimensionSuppressFirstDimensionLine() const { return _dimensionStyleOverrides->suppressFirstDimensionLine(); }

void CadHeader::setDimensionSuppressFirstDimensionLine(bool value) { _dimensionStyleOverrides->setSuppressFirstDimensionLine(value); }

bool CadHeader::dimensionSuppressSecondDimensionLine() const { return _dimensionStyleOverrides->suppressSecondDimensionLine(); }

void CadHeader::setDimensionSuppressSecondDimensionLine(bool value) { _dimensionStyleOverrides->setSuppressSecondDimensionLine(value); }

bool CadHeader::dimensionGenerateTolerances() const { return _dimensionStyleOverrides->generateTolerances(); }

void CadHeader::setDimensionGenerateTolerances(bool value) { _dimensionStyleOverrides->setGenerateTolerances(value); }

ToleranceAlignment CadHeader::dimensionToleranceAlignment() const { return _dimensionStyleOverrides->toleranceAlignment(); }

void CadHeader::setDimensionToleranceAlignment(ToleranceAlignment value) { _dimensionStyleOverrides->setToleranceAlignment(value); }

ZeroHandling CadHeader::dimensionZeroHandling() const { return _dimensionStyleOverrides->zeroHandling(); }

void CadHeader::setDimensionZeroHandling(ZeroHandling value) { _dimensionStyleOverrides->setZeroHandling(value); }

ZeroHandling CadHeader::dimensionToleranceZeroHandling() const { return _dimensionStyleOverrides->toleranceZeroHandling(); }

void CadHeader::setDimensionToleranceZeroHandling(ZeroHandling value) { _dimensionStyleOverrides->setToleranceZeroHandling(value); }

short CadHeader::dimensionFit() const { return _dimensionStyleOverrides->dimensionFit(); }

void CadHeader::setDimensionFit(short value) { _dimensionStyleOverrides->setDimensionFit(value); }

ZeroHandling CadHeader::dimensionAlternateUnitZeroHandling() const { return _dimensionStyleOverrides->alternateUnitZeroHandling(); }

void CadHeader::setDimensionAlternateUnitZeroHandling(ZeroHandling value) { _dimensionStyleOverrides->setAlternateUnitZeroHandling(value); }

ZeroHandling CadHeader::dimensionAlternateUnitToleranceZeroHandling() const { return _dimensionStyleOverrides->alternateUnitToleranceZeroHandling(); }

void CadHeader::setDimensionAlternateUnitToleranceZeroHandling(ZeroHandling value) { _dimensionStyleOverrides->setAlternateUnitToleranceZeroHandling(value); }

bool CadHeader::dimensionCursorUpdate() const { return _dimensionStyleOverrides->cursorUpdate(); }

void CadHeader::setDimensionCursorUpdate(bool value) { _dimensionStyleOverrides->setCursorUpdate(value); }

TextArrowFitType CadHeader::dimensionDimensionTextArrowFit() const { return _dimensionStyleOverrides->dimensionTextArrowFit(); }

void CadHeader::setDimensionDimensionTextArrowFit(TextArrowFitType value) { _dimensionStyleOverrides->setDimensionTextArrowFit(value); }

double CadHeader::dimensionAlternateUnitRounding() const { return _dimensionStyleOverrides->alternateUnitRounding(); }

void CadHeader::setDimensionAlternateUnitRounding(double value) { _dimensionStyleOverrides->setAlternateUnitRounding(value); }

std::string CadHeader::dimensionAlternateDimensioningSuffix() const { return _dimensionStyleOverrides->alternateDimensioningSuffix(); }

void CadHeader::setDimensionAlternateDimensioningSuffix(const std::string &value) { _dimensionStyleOverrides->setAlternateDimensioningSuffix(value); }

double CadHeader::dimensionArrowSize() const { return _dimensionStyleOverrides->arrowSize(); }

void CadHeader::setDimensionArrowSize(double value) { _dimensionStyleOverrides->setArrowSize(value); }

ZeroHandling CadHeader::dimensionAngularZeroHandling() const { return _dimensionStyleOverrides->angularZeroHandling(); }

void CadHeader::setDimensionAngularZeroHandling(ZeroHandling value) { _dimensionStyleOverrides->setAngularZeroHandling(value); }

ArcLengthSymbolPosition CadHeader::dimensionArcLengthSymbolPosition() const { return _dimensionStyleOverrides->arcLengthSymbolPosition(); }

void CadHeader::setDimensionArcLengthSymbolPosition(ArcLengthSymbolPosition value) { _dimensionStyleOverrides->setArcLengthSymbolPosition(value); }

bool CadHeader::dimensionSeparateArrowBlocks() const { return _dimensionStyleOverrides->separateArrowBlocks(); }

void CadHeader::setDimensionSeparateArrowBlocks(bool value) { _dimensionStyleOverrides->setSeparateArrowBlocks(value); }

double CadHeader::dimensionCenterMarkSize() const { return _dimensionStyleOverrides->centerMarkSize(); }

void CadHeader::setDimensionCenterMarkSize(double value) { _dimensionStyleOverrides->setCenterMarkSize(value); }

double CadHeader::dimensionTickSize() const { return _dimensionStyleOverrides->tickSize(); }

void CadHeader::setDimensionTickSize(double value) { _dimensionStyleOverrides->setTickSize(value); }

Color CadHeader::dimensionLineColor() const { return _dimensionStyleOverrides->dimensionLineColor(); }

void CadHeader::setDimensionLineColor(const Color &value) { _dimensionStyleOverrides->setDimensionLineColor(value); }

Color CadHeader::dimensionExtensionLineColor() const { return _dimensionStyleOverrides->extensionLineColor(); }

void CadHeader::setDimensionExtensionLineColor(const Color &value) { _dimensionStyleOverrides->setExtensionLineColor(value); }

Color CadHeader::dimensionTextColor() const { return _dimensionStyleOverrides->textColor(); }

void CadHeader::setDimensionTextColor(const Color &value) { _dimensionStyleOverrides->setTextColor(value); }

double CadHeader::dimensionLineExtension() const { return _dimensionStyleOverrides->dimensionLineExtension(); }

void CadHeader::setDimensionLineExtension(double value) { _dimensionStyleOverrides->setDimensionLineExtension(value); }

double CadHeader::dimensionLineIncrement() const { return _dimensionStyleOverrides->dimensionLineIncrement(); }

void CadHeader::setDimensionLineIncrement(double value) { _dimensionStyleOverrides->setDimensionLineIncrement(value); }

double CadHeader::dimensionExtensionLineExtension() const { return _dimensionStyleOverrides->extensionLineExtension(); }

void CadHeader::setDimensionExtensionLineExtension(double value) { _dimensionStyleOverrides->setExtensionLineExtension(value); }

bool CadHeader::dimensionIsExtensionLineLengthFixed() const { return _dimensionStyleOverrides->isExtensionLineLengthFixed(); }

void CadHeader::setDimensionIsExtensionLineLengthFixed(bool value) { _dimensionStyleOverrides->setIsExtensionLineLengthFixed(value); }

double CadHeader::dimensionFixedExtensionLineLength() const { return _dimensionStyleOverrides->fixedExtensionLineLength(); }

void CadHeader::setDimensionFixedExtensionLineLength(double value) { _dimensionStyleOverrides->setFixedExtensionLineLength(value); }

double CadHeader::dimensionJoggedRadiusDimensionTransverseSegmentAngle() const { return _dimensionStyleOverrides->joggedRadiusDimensionTransverseSegmentAngle(); }

void CadHeader::setDimensionJoggedRadiusDimensionTransverseSegmentAngle(double value) { _dimensionStyleOverrides->setJoggedRadiusDimensionTransverseSegmentAngle(value); }

DimensionTextBackgroundFillMode CadHeader::dimensionTextBackgroundFillMode() const { return _dimensionStyleOverrides->textBackgroundFillMode(); }

void CadHeader::setDimensionTextBackgroundFillMode(DimensionTextBackgroundFillMode value) { _dimensionStyleOverrides->setTextBackgroundFillMode(value); }

Color CadHeader::dimensionTextBackgroundColor() const { return _dimensionStyleOverrides->textBackgroundColor(); }

void CadHeader::setDimensionTextBackgroundColor(const Color &value) { _dimensionStyleOverrides->setTextBackgroundColor(value); }

double CadHeader::dimensionLineGap() const { return _dimensionStyleOverrides->dimensionLineGap(); }

void CadHeader::setDimensionLineGap(double value) { _dimensionStyleOverrides->setDimensionLineGap(value); }

double CadHeader::dimensionLinearScaleFactor() const { return _dimensionStyleOverrides->linearScaleFactor(); }

void CadHeader::setDimensionLinearScaleFactor(double value) { _dimensionStyleOverrides->setLinearScaleFactor(value); }

double CadHeader::dimensionTextVerticalPosition() const { return _dimensionStyleOverrides->textVerticalPosition(); }

void CadHeader::setDimensionTextVerticalPosition(double value) { _dimensionStyleOverrides->setTextVerticalPosition(value); }

LineweightType CadHeader::dimensionLineWeight() const { return _dimensionStyleOverrides->dimensionLineWeight(); }

void CadHeader::setDimensionLineWeight(LineweightType value) { _dimensionStyleOverrides->setimensionLineWeight(value); }

LineweightType CadHeader::extensionLineWeight() const { return _dimensionStyleOverrides->extensionLineWeight(); }

void CadHeader::setExtensionLineWeight(LineweightType value) { _dimensionStyleOverrides->setExtensionLineWeight(value); }

std::string CadHeader::dimensionPostFix() const { return _dimensionStyleOverrides->postFix(); }

void CadHeader::setDimensionPostFix(const std::string &value) { _dimensionStyleOverrides->setPostFix(value); }

double CadHeader::dimensionRounding() const { return _dimensionStyleOverrides->rounding(); }

void CadHeader::setDimensionRounding(double value) { _dimensionStyleOverrides->setRounding(value); }

bool CadHeader::dimensionSuppressFirstExtensionLine() const { return _dimensionStyleOverrides->suppressFirstExtensionLine(); }

void CadHeader::setDimensionSuppressFirstExtensionLine(bool value) { _dimensionStyleOverrides->setSuppressFirstExtensionLine(value); }

bool CadHeader::dimensionSuppressSecondExtensionLine() const { return _dimensionStyleOverrides->suppressSecondExtensionLine(); }

void CadHeader::setDimensionSuppressSecondExtensionLine(bool value) { _dimensionStyleOverrides->setSuppressSecondExtensionLine(value); }

bool CadHeader::dimensionSuppressOutsideExtensions() const { return _dimensionStyleOverrides->suppressOutsideExtensions(); }

void CadHeader::setDimensionSuppressOutsideExtensions(bool value) { _dimensionStyleOverrides->setSuppressOutsideExtensions(value); }

DimensionTextVerticalAlignment CadHeader::dimensionTextVerticalAlignment() const
{
    return _dimensionStyleOverrides->textVerticalAlignment();
}

void CadHeader::setDimensionTextVerticalAlignment(DimensionTextVerticalAlignment value) { _dimensionStyleOverrides->setTextVerticalAlignment(value); }

short CadHeader::dimensionUnit() const { return _dimensionStyleOverrides->dimensionUnit(); }

void CadHeader::setDimensionUnit(short value) { _dimensionStyleOverrides->setDimensionUnit(value); }

double CadHeader::dimensionToleranceScaleFactor() const { return _dimensionStyleOverrides->toleranceScaleFactor(); }

void CadHeader::setDimensionToleranceScaleFactor(double value) { _dimensionStyleOverrides->setToleranceScaleFactor(value); }

bool CadHeader::dimensionTextInsideHorizontal() const { return _dimensionStyleOverrides->textInsideHorizontal(); }

void CadHeader::setDimensionTextInsideHorizontal(bool value) { _dimensionStyleOverrides->setTextInsideHorizontal(value); }

bool CadHeader::dimensionTextInsideExtensions() const { return _dimensionStyleOverrides->textInsideExtensions(); }

void CadHeader::setDimensionTextInsideExtensions(bool value) { _dimensionStyleOverrides->setTextInsideExtensions(value); }

double CadHeader::dimensionMinusTolerance() const { return _dimensionStyleOverrides->minusTolerance(); }

void CadHeader::setDimensionMinusTolerance(double value) { _dimensionStyleOverrides->setMinusTolerance(value); }

bool CadHeader::dimensionTextOutsideExtensions() const { return _dimensionStyleOverrides->textOutsideExtensions(); }

void CadHeader::setDimensionTextOutsideExtensions(bool value) { _dimensionStyleOverrides->setTextOutsideExtensions(value); }

bool CadHeader::dimensionTextOutsideHorizontal() const { return _dimensionStyleOverrides->textOutsideHorizontal(); }

void CadHeader::setDimensionTextOutsideHorizontal(bool value) { _dimensionStyleOverrides->setTextOutsideHorizontal(value); }

bool CadHeader::dimensionLimitsGeneration() const { return _dimensionStyleOverrides->limitsGeneration(); }

void CadHeader::setDimensionLimitsGeneration(bool value) { _dimensionStyleOverrides->setLimitsGeneration(value); }

double CadHeader::dimensionPlusTolerance() const { return _dimensionStyleOverrides->plusTolerance(); }

void CadHeader::setDimensionPlusTolerance(double value) { _dimensionStyleOverrides->setPlusTolerance(value); }

double CadHeader::dimensionTextHeight() const { return _dimensionStyleOverrides->textHeight(); }

void CadHeader::setDimensionTextHeight(double value) { _dimensionStyleOverrides->textHeight(value); }

TextDirection CadHeader::dimensionTextDirection() const { return _dimensionStyleOverrides->textDirection(); }

void CadHeader::setDimensionTextDirection(TextDirection value) { _dimensionStyleOverrides->textDirection(value); }

double CadHeader::dimensionAltMzf() const { return _dimensionStyleOverrides->altMzf(); }

void CadHeader::setDimensionAltMzf(double value) { _dimensionStyleOverrides->setAltMzf(value); }

std::string CadHeader::dimensionAltMzs() const { return _dimensionStyleOverrides->altMzs(); }

void CadHeader::setDimensionAltMzs(const std::string &value) { _dimensionStyleOverrides->setAltMzs(value); }

double CadHeader::dimensionMzf() const { return _dimensionStyleOverrides->mzf(); }

void CadHeader::setDimensionMzf(double value) { _dimensionStyleOverrides->setMzf(value); }

std::string CadHeader::dimensionMzs() const { return _dimensionStyleOverrides->mzs(); }

void CadHeader::setDimensionMzs(const std::string &value) { _dimensionStyleOverrides->setMzs(value); }

std::string CadHeader::dimensionLineType() const { return _dimensionLineType; }

void CadHeader::setDimensionLineType(const std::string &value) { _dimensionLineType = value; }

std::string CadHeader::dimensionTex1() const { return _dimensionTex1; }

void CadHeader::setDimensionTex1(const std::string &value) {}

std::string CadHeader::dimensionTex2() const { return _dimensionTex2; }

void CadHeader::setDimensionTex2(const std::string &value) {}

Layer *CadHeader::currentLayer() const 
{ 
    if (!_document)
    {
        return _currentLayer;
    }
    else
    {
        return _document->layers()->getValue(currentLayerName());
    }
}

void CadHeader::setCurrentLayer(Layer *value) 
{
    delete _currentLayer;
    _currentLayer = value;
}

LineType *CadHeader::currentLineType() const { return _currentLineType; }

void CadHeader::setCurrentLineType(LineType *) {}

TextStyle *CadHeader::currentTextStyle() const { return _currentTextStyle; }

void CadHeader::setTextStyle(TextStyle *) {}

TextStyle *CadHeader::dimensionTextStyle() const 
{
    if(!_document)
    {
        return _dimensionTextStyle;
    } 
    else
    {
        return _document->textStyles()->getValue(dimensionTextStyleName());
    }
}

void CadHeader::setDimensionTextStyle(TextStyle *value) 
{
    delete _dimensionTextStyle;
    _dimensionTextStyle = value;
}

DimensionStyle *CadHeader::dimensionStyleOverrides() const { return _dimensionStyleOverrides; }

UCS *CadHeader::modelSpaceUcs() const { return _modelSpaceUcs; }

void CadHeader::setModelSpaceUcs(UCS *value) 
{
    delete _modelSpaceUcs;
    _modelSpaceUcs = value;
}

UCS *CadHeader::modelSpaceUcsBase() const { return _modelSpaceUcsBase; }

void CadHeader::setModelSpaceUcsBase(UCS *value) 
{
    delete _modelSpaceUcsBase;
    _modelSpaceUcsBase = value;
}

UCS *CadHeader::paperSpaceUcs() const { return _paperSpaceUcs; }

void CadHeader::setPaperSpaceUcs(UCS *value) 
{
    delete _paperSpaceUcs;
    _paperSpaceUcs = value;
}

UCS *CadHeader::paperSpaceUcsBase() const { return _paperSpaceUcsBase; }

void CadHeader::setPaperSpaceUcsBase(UCS *value) 
{
    delete _paperSpaceUcsBase;
    _paperSpaceUcsBase = value;
}

}// namespace dwg
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

#include <dwg/header/CadHeader.h>
#include <stdexcept>

namespace dwg {

CadHeader::CadHeader() {}

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

void CadHeader::setPolylineLineTypeGeneration(bool value) { _polylineLineTypeGeneration = value;}

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
    if(value < 0 || value > 2047)
        throw new std::out_of_range("ISOLINES valid values are from 0 to 2047");
    _surfaceIsolineCount = value;
}

VerticalAlignmentType CadHeader::currentMultilineJustification() const { return _currentMultilineJustification; }

void CadHeader::setCurrentMultilineJustification(VerticalAlignmentType value) { _currentMultilineJustification = value; }

short CadHeader::textQuality() const { return _textQuality; }

void CadHeader::setTextQuality(short value) 
{
    if(value < 0 || value > 100)
        throw new std::out_of_range("TEXTQLTY valid values are from 0 to 100");
        _textQuality = value; 
}

double CadHeader::lineTypeScale() const { return _lineTypeScale; }

void CadHeader::setLineTypeScale(double value) { _lineTypeScale = value; }

double CadHeader::textHeightDefault() const { return _textHeightDefault; }

void CadHeader::setTextHeightDefault(double value) { _textHeightDefault = value; }

std::string CadHeader::textStyleName() const 
{
    return std::string();
}

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
    if(value < 0.01 || value > 10)
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

time_t CadHeader::createDateTime() const { return _createDateTime; }

void CadHeader::setCreateDateTime(time_t value) { _createDateTime = value; }

time_t CadHeader::universalCreateDateTime() const { return _universalCreateDateTime; }

void CadHeader::setUniversalCreateDateTime(time_t value) { _universalCreateDateTime = value; }

time_t CadHeader::updateDateTime() const { return _updateDateTime; }

void CadHeader::setUpdateDateTime(time_t value) { _updateDateTime = value; }

time_t CadHeader::universalUpdateDateTime() const { return _universalUpdateDateTime; }

void CadHeader::setUniversalUpdateDateTime(time_t value) { _universalUpdateDateTime = value; }

double CadHeader::totalEditingTime() const { return _totalEditingTime; }

void CadHeader::setTotalEditingTime(double value) { _totalEditingTime = value; }

double CadHeader::userElapsedTimeSpan() const { return _userElapsedTimeSpan; }

void CadHeader::setUserElapsedTimeSpan(double value) { _userElapsedTimeSpan = value; }

Color CadHeader::currentEntityColor() const { return _currentEntityColor; }

void CadHeader::setCurrentEntityColor(const Color & value) { _currentEntityColor = value; }

double CadHeader::viewportDefaultViewScaleFactor() const { return _viewportDefaultViewScaleFactor; }

void CadHeader::setViewportDefaultViewScaleFactor(double value) { _viewportDefaultViewScaleFactor = value; }

XYZ CadHeader::paperSpaceInsertionBase() const { return _paperSpaceInsertionBase; }

void CadHeader::setPaperSpaceInsertionBase(const XYZ &value) { _paperSpaceInsertionBase = value; }

XYZ CadHeader::paperSpaceExtMin() const { return _paperSpaceExtMin; }

void CadHeader::setPaperSpaceExtMin(const XYZ &value) { _paperSpaceExtMin = value; }

XYZ CadHeader::paperSpaceExtMax() const { return _paperSpaceExtMax; }

void CadHeader::setPaperSpaceExtMax(const XYZ &value) { _paperSpaceExtMax = value; }

XY CadHeader::paperSpaceLimitsMin() const { return _paperSpaceLimitsMin; }

void CadHeader::setPaperSpaceLimitsMin(const XYZ &value) { _paperSpaceLimitsMin = value; }

XY CadHeader::paperSpaceLimitsMax() const { return _paperSpaceLimitsMax; }

void CadHeader::setPaperSpaceLimitsMax(const XY &value) { _paperSpaceLimitsMax = value; }

double CadHeader::paperSpaceElevation() const 
{
    if(_paperSpaceUcs)
    {
        return _paperSpaceUcs->elevation();
    }
    return 0.0;
}

void CadHeader::setPaperSpaceElevation(double value) 
{
    if(_paperSpaceUcs)
    {
        _paperSpaceUcs->setElevation(value);
    }
}

std::string CadHeader::paperSpaceBaseName() const 
{
    if(_paperSpaceUcsBase)
    {
        return _paperSpaceUcsBase->name();
    }
    return std::string();
}

void CadHeader::setPaperSpaceBaseName(const std::string &value) 
{
    if(_paperSpaceUcsBase)
    {
        _paperSpaceUcsBase->setName(value);
    }
}

std::string CadHeader::paperSpaceName() const 
{
    if(_paperSpaceUcs)
    {
        return _paperSpaceUcs->name();
    }
    return std::string();
}

void CadHeader::setPaperSpaceName(const std::string &value) 
{
    if(_paperSpaceUcs)
    {
        return _paperSpaceUcs->setName(value);
    }
}

XYZ CadHeader::paperSpaceUcsOrigin() const 
{
    if(_paperSpaceUcs)
    {
        return _paperSpaceUcs->origin();
    }
    return XYZ::Zero;
}

void CadHeader::setPaperSpaceUcsOrigin(const XYZ &value) 
{

    if(_paperSpaceUcs)
    {
        return _paperSpaceUcs->setOrigin(value);
    }
}

XYZ CadHeader::paperSpaceUcsXAxis() const {}

void CadHeader::setPaperSpaceUcsXAxis(const XYZ &) {}

XYZ CadHeader::paperSpaceUcsYAxis() const {}

void CadHeader::setPaperSpaceUcsYAxis(const XYZ &) {}

XYZ CadHeader::paperSpaceOrthographicTopDOrigin() const {}

void CadHeader::setPaperSpaceOrthographicTopDOrigin(const XYZ &) {}

XYZ CadHeader::paperSpaceOrthographicBottomDOrigin() const {}

void CadHeader::setPaperSpaceOrthographicBottomDOrigin(const XYZ &) {}

XYZ CadHeader::paperSpaceOrthographicLeftDOrigin() const {}

void CadHeader::setPaperSpaceOrthographicLeftDOrigin(const XYZ &) {}

XYZ CadHeader::paperSpaceOrthographicRightDOrigin() const {}

void CadHeader::setPaperSpaceOrthographicRightDOrigin(const XYZ &) {}

XYZ CadHeader::paperSpaceOrthographicFrontDOrigin() const {}

void CadHeader::setPaperSpaceOrthographicFrontDOrigin(const XYZ &) {}

XYZ CadHeader::paperSpaceOrthographicBackDOrigin() const {}

void CadHeader::setPaperSpaceOrthographicBackDOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceOrthographicTopDOrigin() const {}

void CadHeader::setModelSpaceOrthographicTopDOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceOrthographicBottomDOrigin() const {}

void CadHeader::setModelSpaceOrthographicBottomDOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceOrthographicLeftDOrigin() const {}

void CadHeader::setModelSpaceOrthographicLeftDOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceOrthographicRightDOrigin() const {}

void CadHeader::setModelSpaceOrthographicRightDOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceOrthographicFrontDOrigin() const {}

void CadHeader::setModelSpaceOrthographicFrontDOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceOrthographicBackDOrigin() const {}

void CadHeader::setModelSpaceOrthographicBackDOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceInsertionBase() const {}

void CadHeader::setModelSpaceInsertionBase(const XYZ &) {}

XYZ CadHeader::modelSpaceExtMin() const {}

void CadHeader::setModelSpaceExtMin(const XYZ &) {}

XYZ CadHeader::modelSpaceExtMax() const {}

void CadHeader::setModelSpaceExtMax(const XYZ &) {}

XY CadHeader::modelSpaceLimitsMin() const {}

void CadHeader::setModelSpaceLimitsMin(const XY &) {}

XY CadHeader::modelSpaceLimitsMax() const {}

void CadHeader::setModelSpaceLimitsMax(const XY &) {}

std::string CadHeader::ucsBaseName() const {}

void CadHeader::setUcsBaseName(const std::string &value) {}

std::string CadHeader::ucsName() const {}

void CadHeader::setUcsName(const std::string &value) {}

double CadHeader::elevation() const {}

void CadHeader::setElevation(double) {}

XYZ CadHeader::modelSpaceOrigin() const {}

void CadHeader::setModelSpaceOrigin(const XYZ &) {}

XYZ CadHeader::modelSpaceXAxis() const {}

void CadHeader::setModelSpaceXAxis(const XYZ &) {}

XYZ CadHeader::modelSpaceYAxis() const {}

void CadHeader::setModelSpaceYAxis(const XYZ &) {}

std::string CadHeader::dimensionBlockName() const {}

void CadHeader::setDimensionBlockName(const std::string &value) {}

std::string CadHeader::arrowBlockName() const {}

void CadHeader::setArrowBlockName(const std::string &value) {}

std::string CadHeader::dimensionBlockNameFirst() const {}

void CadHeader::setDimensionBlockNameFirst(const std::string &value) {}

std::string CadHeader::dimensionBlockNameSecond() const {}

void CadHeader::setDimensionBlockNameSecond(const std::string &value) {}

short CadHeader::stackedTextAlignment() const {}

void CadHeader::setStackedTextAlignment(short) {}

short CadHeader::stackedTextSizePercentage() const {}

void CadHeader::setStackedTextSizePercentage(short) {}

std::string CadHeader::hyperLinkBase() const {}

void CadHeader::setHyperLinkBase(const std::string &value) {}

LineweightType CadHeader::currentEntityLineWeight() const {}

void CadHeader::setCurrentEntityLineWeight(LineweightType) {}

short CadHeader::endCaps() const {}

void CadHeader::setEndCaps(short) {}

short CadHeader::joinStyle() const {}

void CadHeader::setJoinStyle(short) {}

bool CadHeader::displayLineWeight() const {}

void CadHeader::setDisplayLineWeight(bool) {}

bool CadHeader::xedit() const {}

void CadHeader::setXEdit(bool) {}

bool CadHeader::extendedNames() const {}

void CadHeader::setExtendedNames(bool) {}

short CadHeader::plotStyleMode() const {}

void CadHeader::setPlotStyleMode(short) {}

bool CadHeader::loadOLEObject() const {}

void CadHeader::setLoadOLEObject(bool) {}

UnitsType CadHeader::insUnits() const {}

void CadHeader::setInsUnits(UnitsType) {}

EntityPlotStyleType CadHeader::currentEntityPlotStyle() const {}

void CadHeader::setCurrentEntityPlotStyle(EntityPlotStyleType) {}

std::string CadHeader::fingerPrintGuid() const {}

void CadHeader::setFingerPrintGuid(const std::string &value) {}

std::string CadHeader::versionGuid() const {}

void CadHeader::setVersionGuid(const std::string &value) {}

ObjectSortingFlags CadHeader::entitySortingFlags() const {}

void CadHeader::setEntitySortingFlags(ObjectSortingFlags) {}

IndexCreationFlags CadHeader::indexCreationFlags() const {}

void CadHeader::setIndexCreationFlags(IndexCreationFlags) {}

unsigned char CadHeader::hideText() const {}

void CadHeader::setHideText(unsigned char) {}

unsigned char CadHeader::externalReferenceClippingBoundaryType() const {}

void CadHeader::setExternalReferenceClippingBoundaryType(unsigned char) {}

DimensionAssociation CadHeader::dimensionAssociativity() const {}

void CadHeader::setDimensionAssociativity(DimensionAssociation) {}

unsigned char CadHeader::haloGapPercentage() const {}

void CadHeader::setHaloGapPercentage(unsigned char) {}

Color CadHeader::obscuredColor() const {}

void CadHeader::setObscuredColor(const Color &) {}

Color CadHeader::interfereColor() const {}

void CadHeader::setInterfereColor(const Color &) {}

unsigned char CadHeader::obscuredType() const {}

void CadHeader::setObscuredType(unsigned char) {}

unsigned char CadHeader::intersectionDisplay() const {}

void CadHeader::setIntersectionDisplay(unsigned char) {}

std::string CadHeader::projectName() const {}

void CadHeader::setProjectName(const std::string &value) {}

bool CadHeader::cameraDisplayObjects() const {}

void CadHeader::setCameraDisplayObjects(bool) {}

double CadHeader::stepsPerSecond() const {}

void CadHeader::setStepsPerSecond(double) {}

double CadHeader::stepSize() const {}

void CadHeader::setStepSize(double) {}

double CadHeader::dw3DPrecision() const {}

void CadHeader::setDw3DPrecision(double) {}

double CadHeader::lensLength() const {}

void CadHeader::setLensLength(double) {}

double CadHeader::cameraHeight() const {}

void CadHeader::setCameraHeight(double) {}

char CadHeader::solidsRetainHistory() const {}

void CadHeader::setSolidsRetainHistory(char) {}

char CadHeader::showSolidsHistory() const {}

void CadHeader::setShowSolidsHistory(char) {}

double CadHeader::sweptSolidWidth() const {}

void CadHeader::setSweptSolidWidth(double) {}

double CadHeader::sweptSolidHeight() const {}

void CadHeader::setSweptSolidHeight(double) {}

double CadHeader::draftAngleFirstCrossSection() const {}

void CadHeader::setDraftAngleFirstCrossSection(double) {}

double CadHeader::draftAngleSecondCrossSection() const {}

void CadHeader::setDraftAngleSecondCrossSection(double) {}

double CadHeader::draftMagnitudeFirstCrossSection() const {}

void CadHeader::setDraftMagnitudeFirstCrossSection(double) {}

double CadHeader::draftMagnitudeSecondCrossSection() const {}

void CadHeader::setDraftMagnitudeSecondCrossSection(double) {}

short CadHeader::solidLoftedShape() const {}

void CadHeader::setSolidLoftedShape(short) {}

char CadHeader::loftedObjectNormals() const {}

void CadHeader::setLoftedObjectNormals(char) {}

double CadHeader::latitude() const {}

void CadHeader::setLatitude(double) {}

double CadHeader::longitude() const {}

void CadHeader::setLongitude(double) {}

double CadHeader::northDirection() const {}

void CadHeader::setNorthDirection(double) {}

int CadHeader::timeZone() const {}

void CadHeader::setTimeZone(int) {}

char CadHeader::displayLightGlyphs() const {}

void CadHeader::setDisplayLightGlyphs(char) {}

char CadHeader::dwgUnderlayFramesVisibility() const {}

void CadHeader::setDwgUnderlayFramesVisibility(char) {}

char CadHeader::dgnUnderlayFramesVisibility() const {}

void CadHeader::setDgnUnderlayFramesVisibility(char) {}

ShadowMode CadHeader::shadowMode() const {}

void CadHeader::setShadowMode(ShadowMode) {}

double CadHeader::shadowPlaneLocation() const {}

void CadHeader::setShadowPlaneLocation(double) {}

std::string CadHeader::styleSheetName() const {}

void CadHeader::setStyleSheetName(const std::string &value) {}

std::string CadHeader::dimensionTextStyleName() const {}

void CadHeader::setDimensionTextStyleName(const std::string &value) {}

std::string CadHeader::dimensionStyleOverridesName() const {}

void CadHeader::setDimensionStyleOverridesName(const std::string &value) {}

short CadHeader::dimensionAngularDimensionDecimalPlaces() const {}

void CadHeader::setDimensionAngularDimensionDecimalPlaces(short) {}

short CadHeader::dimensionDecimalPlaces() const {}

void CadHeader::setDimensionDecimalPlaces(short) {}

short CadHeader::dimensionToleranceDecimalPlaces() const {}

void CadHeader::setDimensionToleranceDecimalPlaces(short) {}

bool CadHeader::dimensionAlternateUnitDimensioning() const {}

void CadHeader::setDimensionAlternateUnitDimensioning(bool) {}

LinearUnitFormat CadHeader::dimensionAlternateUnitFormat() const {}

void CadHeader::setDimensionAlternateUnitFormat(LinearUnitFormat) {}

double CadHeader::dimensionAlternateUnitScaleFactor() const {}

void CadHeader::setDimensionAlternateUnitScaleFactor(double) {}

double CadHeader::dimensionExtensionLineOffset() const {}

void CadHeader::setDimensionExtensionLineOffset(double) {}

double CadHeader::dimensionScaleFactor() const {}

void CadHeader::setDimensionScaleFactor(double) {}

short CadHeader::dimensionAlternateUnitDecimalPlaces() const {}

void CadHeader::setDimensionAlternateUnitDecimalPlaces(short) {}

short CadHeader::dimensionAlternateUnitToleranceDecimalPlaces() const {}

void CadHeader::setDimensionAlternateUnitToleranceDecimalPlaces(short) {}

AngularUnitFormat CadHeader::dimensionAngularUnit() const {}

void CadHeader::setDimensionAngularUnit(AngularUnitFormat) {}

FractionFormat CadHeader::dimensionFractionFormat() const {}

void CadHeader::setDimensionFractionFormat(FractionFormat) {}

LinearUnitFormat CadHeader::dimensionLinearUnitFormat() const {}

void CadHeader::setDimensionLinearUnitFormat(LinearUnitFormat) {}

char CadHeader::dimensionDecimalSeparator() const {}

void CadHeader::setDimensionDecimalSeparator(char) {}

TextMovement CadHeader::dimensionTextMovement() const {}

void CadHeader::setDimensionTextMovement(TextMovement) {}

DimensionTextHorizontalAlignment CadHeader::dimensionTextHorizontalAlignment() const {}

void CadHeader::setDimensionTextHorizontalAlignment(DimensionTextHorizontalAlignment) {}

bool CadHeader::dimensionSuppressFirstDimensionLine() const {}

void CadHeader::setDimensionSuppressFirstDimensionLine(bool) {}

bool CadHeader::dimensionSuppressSecondDimensionLine() const {}

void CadHeader::setDimensionSuppressSecondDimensionLine(bool) {}

bool CadHeader::dimensionGenerateTolerances() const {}

void CadHeader::setDimensionGenerateTolerances(bool) {}

ToleranceAlignment CadHeader::dimensionToleranceAlignment() const {}

void CadHeader::setDimensionToleranceAlignment(ToleranceAlignment) {}

ZeroHandling CadHeader::dimensionZeroHandling() const {}

void CadHeader::setDimensionZeroHandling(ZeroHandling) {}

ZeroHandling CadHeader::dimensionToleranceZeroHandling() const {}

void CadHeader::setDimensionToleranceZeroHandling(ZeroHandling) {}

short CadHeader::dimensionFit() const {}

void CadHeader::setDimensionFit(short) {}

ZeroHandling CadHeader::dimensionAlternateUnitZeroHandling() const {}

void CadHeader::setDimensionAlternateUnitZeroHandling(ZeroHandling) {}

ZeroHandling CadHeader::dimensionAlternateUnitToleranceZeroHandling() const {}

void CadHeader::setDimensionAlternateUnitToleranceZeroHandling(ZeroHandling) {}

bool CadHeader::dimensionCursorUpdate() const {}

void CadHeader::setDimensionCursorUpdate(bool) {}

TextArrowFitType CadHeader::dimensionDimensionTextArrowFit() const {}

void CadHeader::setDimensionDimensionTextArrowFit(TextArrowFitType) {}

double CadHeader::dimensionAlternateUnitRounding() const {}

void CadHeader::setDimensionAlternateUnitRounding(double) {}

std::string CadHeader::dimensionAlternateDimensioningSuffix() const {}

void CadHeader::setDimensionAlternateDimensioningSuffix(const std::string &value) {}

double CadHeader::dimensionArrowSize() const {}

void CadHeader::setDimensionArrowSize(double) {}

ZeroHandling CadHeader::dimensionAngularZeroHandling() const {}

void CadHeader::setDimensionAngularZeroHandling(ZeroHandling) {}

ArcLengthSymbolPosition CadHeader::dimensionArcLengthSymbolPosition() const {}

void CadHeader::setDimensionArcLengthSymbolPosition(ArcLengthSymbolPosition) {}

bool CadHeader::dimensionSeparateArrowBlocks() const {}

void CadHeader::setDimensionSeparateArrowBlocks(bool) {}

double CadHeader::dimensionCenterMarkSize() const {}

void CadHeader::setDimensionCenterMarkSize(double) {}

double CadHeader::dimensionTickSize() const {}

void CadHeader::setDimensionTickSize(double) {}

Color CadHeader::dimensionLineColor() const {}

void CadHeader::setDimensionLineColor(const Color &) {}

Color CadHeader::dimensionExtensionLineColor() const {}

void CadHeader::setDimensionExtensionLineColor(const Color &) {}

Color CadHeader::dimensionTextColor() const {}

void CadHeader::setDimensionTextColor(const Color &) {}

double CadHeader::dimensionLineExtension() const {}

void CadHeader::setDimensionLineExtension(double) {}

double CadHeader::dimensionLineIncrement() const {}

void CadHeader::setDimensionLineIncrement(double) {}

double CadHeader::dimensionExtensionLineExtension() const {}

void CadHeader::setDimensionExtensionLineExtension(double) {}

bool CadHeader::dimensionIsExtensionLineLengthFixed() const {}

void CadHeader::setDimensionIsExtensionLineLengthFixed(bool) {}

double CadHeader::dimensionFixedExtensionLineLength() const {}

void CadHeader::setDimensionFixedExtensionLineLength(double) {}

double CadHeader::dimensionJoggedRadiusDimensionTransverseSegmentAngle() const {}

void CadHeader::setDimensionJoggedRadiusDimensionTransverseSegmentAngle(double) {}

DimensionTextBackgroundFillMode CadHeader::dimensionTextBackgroundFillMode() const {}

void CadHeader::setDimensionTextBackgroundFillMode(DimensionTextBackgroundFillMode) {}

Color CadHeader::dimensionTextBackgroundColor() const {}

void CadHeader::setDimensionTextBackgroundColor(const Color &) {}

double CadHeader::dimensionLineGap() const {}

void CadHeader::setDimensionLineGap(double) {}

double CadHeader::dimensionLinearScaleFactor() const {}

void CadHeader::setDimensionLinearScaleFactor(double) {}

double CadHeader::dimensionTextVerticalPosition() const {}

void CadHeader::setDimensionTextVerticalPosition(double) {}

LineweightType CadHeader::dimensionLineWeight() const {}

void CadHeader::setDimensionLineWeight(LineweightType) {}

LineweightType CadHeader::extensionLineWeight() const {}

void CadHeader::setExtensionLineWeight(LineweightType) {}

std::string CadHeader::dimensionPostFix() const {}

void CadHeader::setDimensionPostFix(const std::string &value) {}

double CadHeader::dimensionRounding() const {}

void CadHeader::setDimensionRounding(double) {}

bool CadHeader::dimensionSuppressFirstExtensionLine() const {}

void CadHeader::setDimensionSuppressFirstExtensionLine(bool) {}

bool CadHeader::dimensionSuppressSecondExtensionLine() const {}

void CadHeader::setDimensionSuppressSecondExtensionLine(bool) {}

bool CadHeader::dimensionSuppressOutsideExtensions() const {}

void CadHeader::setDimensionSuppressOutsideExtensions(bool) {}

DimensionTextVerticalAlignment CadHeader::dimensionTextVerticalAlignment() const {}

void CadHeader::setDimensionTextVerticalAlignment(DimensionTextVerticalAlignment) {}

short CadHeader::dimensionUnit() const {}

void CadHeader::setDimensionUnit(short) {}

double CadHeader::dimensionToleranceScaleFactor() const {}

void CadHeader::setDimensionToleranceScaleFactor(double) {}

bool CadHeader::dimensionTextInsideHorizontal() const {}

void CadHeader::setDimensionTextInsideHorizontal(bool) {}

bool CadHeader::dimensionTextInsideExtensions() const {}

void CadHeader::setDimensionTextInsideExtensions(bool) {}

double CadHeader::dimensionMinusTolerance() const {}

void CadHeader::setDimensionMinusTolerance(double) {}

bool CadHeader::dimensionTextOutsideExtensions() const {}

void CadHeader::setDimensionTextOutsideExtensions(bool) {}

bool CadHeader::dimensionTextOutsideHorizontal() const {}

void CadHeader::setDimensionTextOutsideHorizontal(bool) {}

bool CadHeader::dimensionLimitsGeneration() const {}

void CadHeader::setDimensionLimitsGeneration() {}

double CadHeader::dimensionPlusTolerance() const {}

void CadHeader::setDimensionPlusTolerance(double) {}

double CadHeader::dimensionTextHeight() const {}

void CadHeader::setDimensionTextHeight(double) {}

TextDirection CadHeader::dimensionTextDirection() const {}

void CadHeader::setDimensionTextDirection(TextDirection) {}

double CadHeader::dimensionAltMzf() const {}

void CadHeader::setDimensionAltMzf(double) {}

std::string CadHeader::dimensionAltMzs() const {}

void CadHeader::setDimensionAltMzs(const std::string &value) {}

double CadHeader::dimensionMzf() const {}

void CadHeader::setDimensionMzf(double) {}

std::string CadHeader::dimensionMzs() const {}

void CadHeader::setDimensionMzs(const std::string &value) {}

std::string CadHeader::dimensionLineType() const {}

void CadHeader::setDimensionLineType(const std::string &value) {}

std::string CadHeader::dimensionTex1() const {}

void CadHeader::setDimensionTex1(const std::string &value) {}

std::string CadHeader::dimensionTex2() const {}

void CadHeader::setDimensionTex2(const std::string &value) {}

Layer *CadHeader::currentLayer() const {}

void CadHeader::setCurrentLayer(Layer *) {}

LineType *CadHeader::currentLineType() const {}

void CadHeader::setCurrentLineType(LineType *) {}

TextStyle *CadHeader::currentTextStyle() const {}

void CadHeader::setTextStyle(TextStyle *) {}

TextStyle *CadHeader::dimensionTextStyle() const {}

void CadHeader::setDimensionTextStyle(TextStyle *) {}

DimensionStyle *CadHeader::dimensionStyleOverrides() const {}

void CadHeader::setDimensionStyleOverrides(DimensionStyle *) {}

UCS *CadHeader::modelSpaceUcs() const {}

void CadHeader::setModelSpaceUcs(UCS *) {}

UCS *CadHeader::modelSpaceUcsBase() const {}

void CadHeader::setModelSpaceUcsBase(UCS *) {}

UCS *CadHeader::paperSpaceUcs() const {}

void CadHeader::setPaperSpaceUcs(UCS *) {}

UCS *CadHeader::paperSpaceUcsBase() const {}

void CadHeader::setPaperSpaceUcsBase(UCS *) {}

}// namespace dwg
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
#include <dwg/CadSystemVariables_p.h>
#include <dwg/CadUtils.h>
#include <dwg/Registrar.h>
#include <dwg/attributes/CadSystemVariableAttribute_p.h>
#include <dwg/header/CadHeader.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/collections/DimensionStylesTable.h>
#include <dwg/tables/collections/LayersTable.h>
#include <dwg/tables/collections/LineTypesTable.h>
#include <dwg/tables/collections/TextStylesTable.h>
#include <dwg/tables/collections/UCSTable.h>
#include <stdexcept>

#ifdef _WIN32
#include <Windows.h>
#else
#include <uuid/uuid.h>
#endif

namespace dwg {

CadHeader::CadHeader() : CadHeader(ACadVersion::AC1032) {}

CadHeader::CadHeader(CadDocument *document) : CadHeader(ACadVersion::AC1032)
{
    _document = document;
}

CadDocument *CadHeader::document()
{
    return _document;
}

void CadHeader::setDocument(CadDocument *document) {}

CadHeader::CadHeader(ACadVersion version) : _version(version)
{
    setVersion(version);
#ifdef _WIN32
    GUID guid;
    HRESULT res = CoCreateGuid(&guid);
    char guidStr[39];
    unsigned long long last6 = 0;
    for (int i = 2; i < 8; ++i) last6 = (last6 << 8) | guid.Data4[i];

    sprintf_s(guidStr, sizeof(guidStr), "{%08lX-%04X-%04X-%02X%02X-%012llX}", guid.Data1, guid.Data2, guid.Data3,
              guid.Data4[0], guid.Data4[1], last6);

    _fingerPrintGuid = guidStr;
#else
    uuid_t uuid;
    char guid_str[37];
    uuid_generate(uuid);
    uuid_unparse_lower(uuid, guid_str);
    _fingerPrintGuid = std::string(guid_str);
#endif

    _currentLayer = Layer::Default();
    _currentLineType = LineType::ByLayer();
    _currentMLineStyle = MLineStyle::Default();
    _currentTextStyle = TextStyle::Default();
    _dimensionStyleOverrides = new DimensionStyle("override");
    _currentDimensionStyle = DimensionStyle::Default();
    _dimensionTextStyle = TextStyle::Default();
}

std::string CadHeader::versionString() const
{
    return CadUtils::GetNameFromVersion(_version);
}

void CadHeader::setVersionString(const std::string &value)
{
    _version = CadUtils::GetVersionFromName(value);
}

ACadVersion CadHeader::version() const
{
    return _version;
}

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

short CadHeader::maintenanceVersion() const
{
    return _maintenanceVersion;
}

void CadHeader::setMaintenanceVersion(short value)
{
    _maintenanceVersion = value;
}

std::string CadHeader::codePage() const
{
    return _codePage;
}

void CadHeader::setCodePage(const std::string &value)
{
    _codePage = value;
}

std::string CadHeader::lastSavedBy() const
{
    return _lastSavedBy;
}

void CadHeader::setLastSavedBy(const std::string &value)
{
    _lastSavedBy = value;
}

bool CadHeader::associatedDimensions() const
{
    return _associatedDimensions;
}

void CadHeader::setAssociatedDimensions(bool value)
{
    _associatedDimensions = value;
}

bool CadHeader::updateDimensionsWhileDragging() const
{
    return _updateDimensionsWhileDragging;
}

void CadHeader::setUpdateDimensionsWhileDragging(bool value)
{
    _updateDimensionsWhileDragging = value;
}

bool CadHeader::DIMSAV() const
{
    return _DIMSAV;
}

void CadHeader::setDIMSAV(bool value)
{
    _DIMSAV = value;
}

MeasurementUnits CadHeader::measurementUnits() const
{
    return _measurementUnits;
}

void CadHeader::setMeasurementUnits(MeasurementUnits value)
{
    _measurementUnits = value;
}

bool CadHeader::polylineLineTypeGeneration() const
{
    return _polylineLineTypeGeneration;
}

void CadHeader::setPolylineLineTypeGeneration(bool value)
{
    _polylineLineTypeGeneration = value;
}

bool CadHeader::orthoMode() const
{
    return _orthoMode;
}

void CadHeader::setOrthoMode(bool value)
{
    _orthoMode = value;
}

bool CadHeader::regenerationMode() const
{
    return _regenerationMode;
}

void CadHeader::setRegenerationMode(bool value)
{
    _regenerationMode = value;
}

bool CadHeader::fillMode() const
{
    return _fillMode;
}

void CadHeader::setFillMode(bool value)
{
    _fillMode = value;
}

bool CadHeader::quickTextMode() const
{
    return _quickTextMode;
}

void CadHeader::setQuickTextMode(bool value)
{
    _quickTextMode = value;
}

SpaceLineTypeScaling CadHeader::paperSpaceLineTypeScaling() const
{
    return _paperSpaceLineTypeScaling;
}

void CadHeader::setPaperSpaceLineTypeScaling(SpaceLineTypeScaling value)
{
    _paperSpaceLineTypeScaling = value;
}

bool CadHeader::limitCheckingOn() const
{
    return _limitCheckingOn;
}

void CadHeader::setLimitCheckingOn(bool value)
{
    _limitCheckingOn = value;
}

bool CadHeader::blipMode() const
{
    return _blipMode;
}

void CadHeader::setBlipMode(bool value)
{
    _blipMode = value;
}

bool CadHeader::userTimer() const
{
    return _userTimer;
}

void CadHeader::setUserTimer(bool value)
{
    _userTimer = value;
}

bool CadHeader::sketchPolylines() const
{
    return _sketchPolylines;
}

void CadHeader::setSketchPolylines(bool value)
{
    _sketchPolylines = value;
}

AngularDirection CadHeader::angularDirection() const
{
    return _angularDirection;
}

void CadHeader::setAngularDirection(AngularDirection value)
{
    _angularDirection = value;
}

bool CadHeader::showSplineControlPoints() const
{
    return _showSplineControlPoints;
}

void CadHeader::setShowSplineControlPoints(bool value)
{
    _showSplineControlPoints = value;
}

bool CadHeader::mirrorText() const
{
    return _mirrorText;
}

void CadHeader::setMirrorText(bool value)
{
    _mirrorText = value;
}

bool CadHeader::worldView() const
{
    return _worldView;
}

void CadHeader::setWorldView(bool value)
{
    _worldView = value;
}

bool CadHeader::showModelSpace() const
{
    return _showModelSpace;
}

void CadHeader::setShowModelSpace(bool value)
{
    _showModelSpace = value;
}

bool CadHeader::paperSpaceLimitsChecking() const
{
    return _paperSpaceLimitsChecking;
}

void CadHeader::setPaperSpaceLimitsChecking(bool value)
{
    _paperSpaceLimitsChecking = value;
}

bool CadHeader::retainXRefDependentVisibilitySettings() const
{
    return _retainXRefDependentVisibilitySettings;
}

void CadHeader::setRetainXRefDependentVisibilitySettings(bool value)
{
    _retainXRefDependentVisibilitySettings = value;
}

bool CadHeader::displaySilhouetteCurves() const
{
    return _displaySilhouetteCurves;
}

void CadHeader::setDisplaySilhouetteCurves(bool value)
{
    _displaySilhouetteCurves = value;
}

bool CadHeader::createEllipseAsPolyline() const
{
    return _createEllipseAsPolyline;
}

void CadHeader::setCreateEllipseAsPolyline(bool value)
{
    _createEllipseAsPolyline = value;
}

bool CadHeader::proxyGraphics() const
{
    return _proxyGraphics;
}

void CadHeader::setProxyGraphics(bool value)
{
    _proxyGraphics = value;
}

short CadHeader::spatialIndexMaxTreeDepth() const
{
    return _spatialIndexMaxTreeDepth;
}

void CadHeader::setSpatialIndexMaxTreeDepth(short value)
{
    _spatialIndexMaxTreeDepth = value;
}

LinearUnitFormat CadHeader::linearUnitFormat() const
{
    return _linearUnitFormat;
}

void CadHeader::setLinearUnitFormat(LinearUnitFormat value)
{
    _linearUnitFormat = value;
}

short CadHeader::linearUnitPrecision() const
{
    return _linearUnitPrecision;
}

void CadHeader::setLinearUnitPrecision(short value)
{
    _linearUnitPrecision = value;
}

AngularUnitFormat CadHeader::angularUnit() const
{
    return _angularUnit;
}

void CadHeader::setAngularUnit(AngularUnitFormat value)
{
    _angularUnit = value;
}

short CadHeader::angularUnitPrecision() const
{
    return _angularUnitPrecision;
}

void CadHeader::setAngularUnitPrecision(short value)
{
    _angularUnitPrecision = value;
}

ObjectSnapMode CadHeader::objectSnapMode() const
{
    return _objectSnapMode;
}

void CadHeader::setObjectSnapMode(ObjectSnapMode value)
{
    _objectSnapMode = value;
}

AttributeVisibilityMode CadHeader::attributeVisibility() const
{
    return _attributeVisibility;
}

void CadHeader::setAttributeVisibility(AttributeVisibilityMode value)
{
    _attributeVisibility = value;
}

short CadHeader::pointDisplayMode() const
{
    return _pointDisplayMode;
}

void CadHeader::setPointDisplayMode(short value)
{
    _pointDisplayMode = value;
}

short CadHeader::userShort1() const
{
    return _userShort1;
}

void CadHeader::setUserShort1(short value)
{
    _userShort1 = value;
}

short CadHeader::userShort2() const
{
    return _userShort2;
}

void CadHeader::setUserShort2(short value)
{
    _userShort2 = value;
}

short CadHeader::userShort3() const
{
    return _userShort3;
}

void CadHeader::setUserShort3(short value)
{
    _userShort3 = value;
}

short CadHeader::userShort4() const
{
    return _userShort4;
}

void CadHeader::setUserShort4(short value)
{
    _userShort4 = value;
}

short CadHeader::userShort5() const
{
    return _userShort5;
}

void CadHeader::setUserShort5(short value)
{
    _userShort5 = value;
}

short CadHeader::numberOfSplineSegments() const
{
    return _numberOfSplineSegments;
}

void CadHeader::setNumberOfSplineSegments(short value)
{
    _numberOfSplineSegments = value;
}

short CadHeader::surfaceDensityU() const
{
    return _surfaceDensityU;
}

void CadHeader::setSurfaceDensityU(short value)
{
    _surfaceDensityU = value;
}

short CadHeader::surfaceDensityV() const
{
    return _surfaceDensityV;
}

void CadHeader::setSurfaceDensityV(short value)
{
    _surfaceDensityV = value;
}

short CadHeader::surfaceType() const
{
    return _surfaceType;
}

void CadHeader::setSurfaceType(short value)
{
    _surfaceType = value;
}

short CadHeader::surfaceMeshTabulationCount1() const
{
    return _surfaceMeshTabulationCount1;
}

void CadHeader::setSurfaceMeshTabulationCount1(short value)
{
    _surfaceMeshTabulationCount1 = value;
}

short CadHeader::surfaceMeshTabulationCount2() const
{
    return _surfaceMeshTabulationCount2;
}

void CadHeader::setSurfaceMeshTabulationCount2(short value)
{
    _surfaceMeshTabulationCount2 = value;
}

SplineType CadHeader::splineType() const
{
    return _splineType;
}

void CadHeader::setSplineType(SplineType value)
{
    _splineType = value;
}

ShadeEdgeType CadHeader::shadeEdge() const
{
    return _shadeEdge;
}

void CadHeader::setShadeEdge(ShadeEdgeType value)
{
    _shadeEdge = value;
}

short CadHeader::shadeDiffuseToAmbientPercentage() const
{
    return _shadeDiffuseToAmbientPercentage;
}

void CadHeader::setShadeDiffuseToAmbientPercentage(short value)
{
    _shadeDiffuseToAmbientPercentage = value;
}

short CadHeader::unitMode() const
{
    return _unitMode;
}

void CadHeader::setUnitMode(short value)
{
    _unitMode = value;
}

short CadHeader::maxViewportCount() const
{
    return _maxViewportCount;
}

void CadHeader::setMaxViewportCount(short value)
{
    _maxViewportCount = value;
}

short CadHeader::surfaceIsolineCount() const
{
    return _surfaceIsolineCount;
}

void CadHeader::setSurfaceIsolineCount(short value)
{
    if (value < 0 || value > 2047)
        throw std::out_of_range("ISOLINES valid values are from 0 to 2047");
    _surfaceIsolineCount = value;
}

VerticalAlignmentType CadHeader::currentMultilineJustification() const
{
    return _currentMultilineJustification;
}

void CadHeader::setCurrentMultilineJustification(VerticalAlignmentType value)
{
    _currentMultilineJustification = value;
}

short CadHeader::textQuality() const
{
    return _textQuality;
}

void CadHeader::setTextQuality(short value)
{
    if (value < 0 || value > 100)
        throw std::out_of_range("TEXTQLTY valid values are from 0 to 100");
    _textQuality = value;
}

double CadHeader::lineTypeScale() const
{
    return _lineTypeScale;
}

void CadHeader::setLineTypeScale(double value)
{
    _lineTypeScale = value;
}

double CadHeader::textHeightDefault() const
{
    return _textHeightDefault;
}

void CadHeader::setTextHeightDefault(double value)
{
    _textHeightDefault = value;
}

std::string CadHeader::textStyleName() const
{
    return std::string();
}

void CadHeader::setTextStyleName(const std::string &value)
{
    // TODO
}

std::string CadHeader::currentLayerName() const
{
    return std::string();
}

void CadHeader::setCurrentLayerName(const std::string &value) {}

std::string CadHeader::currentLineTypeName() const
{
    return std::string();
}

void CadHeader::setCurrentLineTypeName(const std::string &value) {}

double CadHeader::traceWidthDefault() const
{
    return _traceWidthDefault;
}

void CadHeader::setTraceWidthDefault(double value)
{
    _traceWidthDefault = value;
}

double CadHeader::sketchIncrement() const
{
    return _sketchIncrement;
}

void CadHeader::setSketchIncrement(double value)
{
    _sketchIncrement = value;
}

double CadHeader::filletRadius() const
{
    return _filletRadius;
}

void CadHeader::setFilletRadius(double value)
{
    _filletRadius = value;
}

double CadHeader::thicknessDefault() const
{
    return _thicknessDefault;
}

void CadHeader::setThicknessDefault(double value)
{
    _thicknessDefault = value;
}

double CadHeader::angleBase() const
{
    return _angleBase;
}

void CadHeader::setAngleBase(double value)
{
    _angleBase = value;
}

double CadHeader::pointDisplaySize() const
{
    return _pointDisplaySize;
}

void CadHeader::setPointDisplaySize(double value)
{
    _pointDisplaySize = value;
}

double CadHeader::polylineWidthDefault() const
{
    return _polylineWidthDefault;
}

void CadHeader::setPolylineWidthDefault(double value)
{
    _polylineWidthDefault = value;
}

double CadHeader::userDouble1() const
{
    return _userDouble1;
}

void CadHeader::setUserDouble1(double value)
{
    _userDouble1 = value;
}

double CadHeader::userDouble2() const
{
    return _userDouble2;
}

void CadHeader::setUserDouble2(double value)
{
    _userDouble2 = value;
}

double CadHeader::userDouble3() const
{
    return _userDouble3;
}

void CadHeader::setUserDouble3(double value)
{
    _userDouble3 = value;
}

double CadHeader::userDouble4() const
{
    return _userDouble4;
}

void CadHeader::setUserDouble4(double value)
{
    _userDouble4 = value;
}

double CadHeader::userDouble5() const
{
    return _userDouble5;
}

void CadHeader::setUserDouble5(double value)
{
    _userDouble5 = value;
}

double CadHeader::chamferDistance1() const
{
    return _chamferDistance1;
}

void CadHeader::setChamferDistance1(double value)
{
    _chamferDistance1 = value;
}

double CadHeader::chamferDistance2() const
{
    return _chamferDistance2;
}

void CadHeader::setChamferDistance2(double value)
{
    _chamferDistance2 = value;
}

double CadHeader::chamferLength() const
{
    return _chamferLength;
}

void CadHeader::setChamferLength(double value)
{
    _chamferLength = value;
}

double CadHeader::chamferAngle() const
{
    return _chamferAngle;
}

void CadHeader::setChamferAngle(double value)
{
    _chamferAngle = value;
}

double CadHeader::facetResolution() const
{
    return _facetResolution;
}

void CadHeader::setFacetResolution(double value)
{
    if (value < 0.01 || value > 10)
        throw std::out_of_range("FACETRES valid values are from 0.01 to 10.0");
    _facetResolution = value;
}

double CadHeader::currentMultilineScale() const
{
    return _currentMultilineScale;
}

void CadHeader::setCurrentMultilineScale(double value)
{
    _currentMultilineScale = value;
}

std::string CadHeader::currentMultiLineStyleName() const
{
    return std::string();
}

void CadHeader::setCurrentMultiLineStyleName(const std::string &value) {}

std::string CadHeader::currentDimensionStyleName() const
{
    return std::string();
}

void CadHeader::setCurrentDimensionStyleName(const std::string &value) {}

long long CadHeader::requiredVersions() const
{
    return 0;
}

void CadHeader::setRequiredVersions(long long value) {}

double CadHeader::currentEntityLinetypeScale() const
{
    return _currentEntityLinetypeScale;
}

void CadHeader::setCurrentEntityLinetypeScale(double value)
{
    _currentEntityLinetypeScale = value;
}

std::string CadHeader::menuFileName() const
{
    return _menuFileName;
}

void CadHeader::setMenuFileName(const std::string &value)
{
    _menuFileName = value;
}

unsigned long long CadHeader::handleSeed() const
{
    return _handleSeed;
}

void CadHeader::setHandleSeed(unsigned long long value)
{
    _handleSeed = value;
}

DateTime CadHeader::createDateTime() const
{
    return _createDateTime;
}

void CadHeader::setCreateDateTime(const DateTime &value)
{
    _createDateTime = value;
}

DateTime CadHeader::universalCreateDateTime() const
{
    return _universalCreateDateTime;
}

void CadHeader::setUniversalCreateDateTime(const DateTime &value)
{
    _universalCreateDateTime = value;
}

DateTime CadHeader::updateDateTime() const
{
    return _updateDateTime;
}

void CadHeader::setUpdateDateTime(const DateTime &value)
{
    _updateDateTime = value;
}

DateTime CadHeader::universalUpdateDateTime() const
{
    return _universalUpdateDateTime;
}

void CadHeader::setUniversalUpdateDateTime(const DateTime &value)
{
    _universalUpdateDateTime = value;
}

Timespan CadHeader::totalEditingTime() const
{
    return _totalEditingTime;
}

void CadHeader::setTotalEditingTime(const Timespan &value)
{
    _totalEditingTime = value;
}

double CadHeader::userElapsedTimeSpan() const
{
    return _userElapsedTimeSpan;
}

void CadHeader::setUserElapsedTimeSpan(double value)
{
    _userElapsedTimeSpan = value;
}

Color CadHeader::currentEntityColor() const
{
    return _currentEntityColor;
}

void CadHeader::setCurrentEntityColor(const Color &value)
{
    _currentEntityColor = value;
}

double CadHeader::viewportDefaultViewScaleFactor() const
{
    return _viewportDefaultViewScaleFactor;
}

void CadHeader::setViewportDefaultViewScaleFactor(double value)
{
    _viewportDefaultViewScaleFactor = value;
}

XYZ CadHeader::paperSpaceInsertionBase() const
{
    return _paperSpaceInsertionBase;
}

void CadHeader::setPaperSpaceInsertionBase(const XYZ &value)
{
    _paperSpaceInsertionBase = value;
}

XYZ CadHeader::paperSpaceExtMin() const
{
    return _paperSpaceExtMin;
}

void CadHeader::setPaperSpaceExtMin(const XYZ &value)
{
    _paperSpaceExtMin = value;
}

XYZ CadHeader::paperSpaceExtMax() const
{
    return _paperSpaceExtMax;
}

void CadHeader::setPaperSpaceExtMax(const XYZ &value)
{
    _paperSpaceExtMax = value;
}

XY CadHeader::paperSpaceLimitsMin() const
{
    return _paperSpaceLimitsMin;
}

void CadHeader::setPaperSpaceLimitsMin(const XY &value)
{
    _paperSpaceLimitsMin = value;
}

XY CadHeader::paperSpaceLimitsMax() const
{
    return _paperSpaceLimitsMax;
}

void CadHeader::setPaperSpaceLimitsMax(const XY &value)
{
    _paperSpaceLimitsMax = value;
}

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

XYZ CadHeader::paperSpaceOrthographicTopDOrigin() const
{
    return _paperSpaceOrthographicTopDOrigin;
}

void CadHeader::setPaperSpaceOrthographicTopDOrigin(const XYZ &value)
{
    _paperSpaceOrthographicTopDOrigin = value;
}

XYZ CadHeader::paperSpaceOrthographicBottomDOrigin() const
{
    return _paperSpaceOrthographicBottomDOrigin;
}

void CadHeader::setPaperSpaceOrthographicBottomDOrigin(const XYZ &value)
{
    _paperSpaceOrthographicBottomDOrigin = value;
}

XYZ CadHeader::paperSpaceOrthographicLeftDOrigin() const
{
    return _paperSpaceOrthographicLeftDOrigin;
}

void CadHeader::setPaperSpaceOrthographicLeftDOrigin(const XYZ &value)
{
    _paperSpaceOrthographicLeftDOrigin = value;
}

XYZ CadHeader::paperSpaceOrthographicRightDOrigin() const
{
    return _paperSpaceOrthographicRightDOrigin;
}

void CadHeader::setPaperSpaceOrthographicRightDOrigin(const XYZ &value)
{
    _paperSpaceOrthographicRightDOrigin = value;
}

XYZ CadHeader::paperSpaceOrthographicFrontDOrigin() const
{
    return _paperSpaceOrthographicFrontDOrigin;
}

void CadHeader::setPaperSpaceOrthographicFrontDOrigin(const XYZ &value)
{
    _paperSpaceOrthographicFrontDOrigin = value;
}

XYZ CadHeader::paperSpaceOrthographicBackDOrigin() const
{
    return _paperSpaceOrthographicBackDOrigin;
}

void CadHeader::setPaperSpaceOrthographicBackDOrigin(const XYZ &value)
{
    _paperSpaceOrthographicBackDOrigin = value;
}

XYZ CadHeader::modelSpaceOrthographicTopDOrigin() const
{
    return _modelSpaceOrthographicTopDOrigin;
}

void CadHeader::setModelSpaceOrthographicTopDOrigin(const XYZ &value)
{
    _modelSpaceOrthographicTopDOrigin = value;
}

XYZ CadHeader::modelSpaceOrthographicBottomDOrigin() const
{
    return _modelSpaceOrthographicBottomDOrigin;
}

void CadHeader::setModelSpaceOrthographicBottomDOrigin(const XYZ &value)
{
    _modelSpaceOrthographicBottomDOrigin = value;
}

XYZ CadHeader::modelSpaceOrthographicLeftDOrigin() const
{
    return _modelSpaceOrthographicLeftDOrigin;
}

void CadHeader::setModelSpaceOrthographicLeftDOrigin(const XYZ &value)
{
    _modelSpaceOrthographicLeftDOrigin = value;
}

XYZ CadHeader::modelSpaceOrthographicRightDOrigin() const
{
    return _modelSpaceOrthographicRightDOrigin;
}

void CadHeader::setModelSpaceOrthographicRightDOrigin(const XYZ &value)
{
    _modelSpaceOrthographicRightDOrigin = value;
}

XYZ CadHeader::modelSpaceOrthographicFrontDOrigin() const
{
    return _modelSpaceOrthographicFrontDOrigin;
}

void CadHeader::setModelSpaceOrthographicFrontDOrigin(const XYZ &value)
{
    _modelSpaceOrthographicFrontDOrigin = value;
}

XYZ CadHeader::modelSpaceOrthographicBackDOrigin() const
{
    return _modelSpaceOrthographicBackDOrigin;
}

void CadHeader::setModelSpaceOrthographicBackDOrigin(const XYZ &value)
{
    _modelSpaceOrthographicBackDOrigin = value;
}

XYZ CadHeader::modelSpaceInsertionBase() const
{
    return _modelSpaceInsertionBase;
}

void CadHeader::setModelSpaceInsertionBase(const XYZ &value)
{
    _modelSpaceInsertionBase = value;
}

XYZ CadHeader::modelSpaceExtMin() const
{
    return _modelSpaceExtMin;
}

void CadHeader::setModelSpaceExtMin(const XYZ &value)
{
    _modelSpaceExtMin = value;
}

XYZ CadHeader::modelSpaceExtMax() const
{
    return _modelSpaceExtMax;
}

void CadHeader::setModelSpaceExtMax(const XYZ &value)
{
    _modelSpaceExtMax = value;
}

XY CadHeader::modelSpaceLimitsMin() const
{
    return _modelSpaceLimitsMin;
}

void CadHeader::setModelSpaceLimitsMin(const XY &value)
{
    _modelSpaceLimitsMin = value;
}

XY CadHeader::modelSpaceLimitsMax() const
{
    return _modelSpaceLimitsMax;
}

void CadHeader::setModelSpaceLimitsMax(const XY &value)
{
    _modelSpaceLimitsMax = value;
}

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

std::string CadHeader::dimensionBlockName() const
{
    return _dimensionBlockName;
}

void CadHeader::setDimensionBlockName(const std::string &value)
{
    _dimensionBlockName = value;
}

std::string CadHeader::arrowBlockName() const
{
    return _arrowBlockName;
}

void CadHeader::setArrowBlockName(const std::string &value)
{
    _arrowBlockName = value;
}

std::string CadHeader::dimensionBlockNameFirst() const
{
    return _dimensionBlockNameFirst;
}

void CadHeader::setDimensionBlockNameFirst(const std::string &value)
{
    _dimensionBlockNameFirst = value;
}

std::string CadHeader::dimensionBlockNameSecond() const
{
    return _dimensionBlockNameSecond;
}

void CadHeader::setDimensionBlockNameSecond(const std::string &value)
{
    _dimensionBlockNameSecond = value;
}

short CadHeader::stackedTextAlignment() const
{
    return _stackedTextAlignment;
}

void CadHeader::setStackedTextAlignment(short value)
{
    _stackedTextAlignment = value;
}

short CadHeader::stackedTextSizePercentage() const
{
    return _stackedTextSizePercentage;
}

void CadHeader::setStackedTextSizePercentage(short value)
{
    _stackedTextSizePercentage = value;
}

std::string CadHeader::hyperLinkBase() const
{
    return _hyperLinkBase;
}

void CadHeader::setHyperLinkBase(const std::string &value)
{
    _hyperLinkBase = value;
}

LineweightType CadHeader::currentEntityLineWeight() const
{
    return _currentEntityLineWeight;
}

void CadHeader::setCurrentEntityLineWeight(LineweightType value)
{
    _currentEntityLineWeight = value;
}

short CadHeader::endCaps() const
{
    return _endCaps;
}

void CadHeader::setEndCaps(short value)
{
    _endCaps = value;
}

short CadHeader::joinStyle() const
{
    return _joinStyle;
}

void CadHeader::setJoinStyle(short value)
{
    _joinStyle = value;
}

bool CadHeader::displayLineWeight() const
{
    return _displayLineWeight;
}

void CadHeader::setDisplayLineWeight(bool value)
{
    _displayLineWeight = value;
}

bool CadHeader::xedit() const
{
    return _xedit;
}

void CadHeader::setXEdit(bool value)
{
    _xedit = value;
}

bool CadHeader::extendedNames() const
{
    return _extendedNames;
}

void CadHeader::setExtendedNames(bool value)
{
    _extendedNames = value;
}

short CadHeader::plotStyleMode() const
{
    return _plotStyleMode;
}

void CadHeader::setPlotStyleMode(short value)
{
    _plotStyleMode = value;
}

bool CadHeader::loadOLEObject() const
{
    return _loadOLEObject;
}

void CadHeader::setLoadOLEObject(bool value)
{
    _loadOLEObject = value;
}

UnitsType CadHeader::insUnits() const
{
    return _insUnits;
}

void CadHeader::setInsUnits(UnitsType value)
{
    _insUnits = value;
}

EntityPlotStyleType CadHeader::currentEntityPlotStyle() const
{
    return _currentEntityPlotStyle;
}

void CadHeader::setCurrentEntityPlotStyle(EntityPlotStyleType value)
{
    _currentEntityPlotStyle = value;
}

std::string CadHeader::fingerPrintGuid() const
{
    return _fingerPrintGuid;
}

void CadHeader::setFingerPrintGuid(const std::string &value)
{
    _fingerPrintGuid = value;
}

std::string CadHeader::versionGuid() const
{
    return _versionGuid;
}

void CadHeader::setVersionGuid(const std::string &value)
{
    _versionGuid = value;
}

ObjectSortingFlags CadHeader::entitySortingFlags() const
{
    return _entitySortingFlags;
}

void CadHeader::setEntitySortingFlags(ObjectSortingFlags value)
{
    _entitySortingFlags = value;
}

IndexCreationFlags CadHeader::indexCreationFlags() const
{
    return _indexCreationFlags;
}

void CadHeader::setIndexCreationFlags(IndexCreationFlags value)
{
    _indexCreationFlags = value;
}

unsigned char CadHeader::hideText() const
{
    return _hideText;
}

void CadHeader::setHideText(unsigned char value)
{
    _hideText = value;
}

unsigned char CadHeader::externalReferenceClippingBoundaryType() const
{
    return _externalReferenceClippingBoundaryType;
}

void CadHeader::setExternalReferenceClippingBoundaryType(unsigned char value)
{
    _externalReferenceClippingBoundaryType = value;
}

DimensionAssociation CadHeader::dimensionAssociativity() const
{
    return _dimensionAssociativity;
}

void CadHeader::setDimensionAssociativity(DimensionAssociation value)
{
    _dimensionAssociativity = value;
}

unsigned char CadHeader::haloGapPercentage() const
{
    return _haloGapPercentage;
}

void CadHeader::setHaloGapPercentage(unsigned char value)
{
    _haloGapPercentage = value;
}

Color CadHeader::obscuredColor() const
{
    return _obscuredColor;
}

void CadHeader::setObscuredColor(const Color &value)
{
    _obscuredColor = value;
}

Color CadHeader::interfereColor() const
{
    return _interfereColor;
}

void CadHeader::setInterfereColor(const Color &value)
{
    _interfereColor = value;
}

unsigned char CadHeader::obscuredType() const
{
    return _obscuredType;
}

void CadHeader::setObscuredType(unsigned char value)
{
    _obscuredType = value;
}

unsigned char CadHeader::intersectionDisplay() const
{
    return _intersectionDisplay;
}

void CadHeader::setIntersectionDisplay(unsigned char value)
{
    _intersectionDisplay = value;
}

std::string CadHeader::projectName() const
{
    return _projectName;
}

void CadHeader::setProjectName(const std::string &value)
{
    _projectName = value;
}

bool CadHeader::cameraDisplayObjects() const
{
    return _cameraDisplayObjects;
}

void CadHeader::setCameraDisplayObjects(bool value)
{
    _cameraDisplayObjects = value;
}

double CadHeader::stepsPerSecond() const
{
    return _stepsPerSecond;
}

void CadHeader::setStepsPerSecond(double value)
{
    if (value < 1 || value > 30)
        throw std::out_of_range("FACETRES valid values are from 1 to 30");
    _stepsPerSecond = value;
}

double CadHeader::stepSize() const
{
    return _stepSize;
}

void CadHeader::setStepSize(double value)
{
    _stepSize = value;
}

double CadHeader::dw3DPrecision() const
{
    return _dw3DPrecision;
}

void CadHeader::setDw3DPrecision(double value)
{
    _dw3DPrecision = value;
}

double CadHeader::lensLength() const
{
    return _lensLength;
}

void CadHeader::setLensLength(double value)
{
    _lensLength = value;
}

double CadHeader::cameraHeight() const
{
    return _cameraHeight;
}

void CadHeader::setCameraHeight(double value)
{
    _cameraHeight = value;
}

char CadHeader::solidsRetainHistory() const
{
    return _solidsRetainHistory;
}

void CadHeader::setSolidsRetainHistory(char value)
{
    _solidsRetainHistory = value;
}

char CadHeader::showSolidsHistory() const
{
    return _showSolidsHistory;
}

void CadHeader::setShowSolidsHistory(char value)
{
    _showSolidsHistory = value;
}

double CadHeader::sweptSolidWidth() const
{
    return _sweptSolidWidth;
}

void CadHeader::setSweptSolidWidth(double value)
{
    _sweptSolidWidth = value;
}

double CadHeader::sweptSolidHeight() const
{
    return _sweptSolidHeight;
}

void CadHeader::setSweptSolidHeight(double value)
{
    _sweptSolidHeight = value;
}

double CadHeader::draftAngleFirstCrossSection() const
{
    return _draftAngleFirstCrossSection;
}

void CadHeader::setDraftAngleFirstCrossSection(double value)
{
    _draftAngleFirstCrossSection = value;
}

double CadHeader::draftAngleSecondCrossSection() const
{
    return _draftAngleSecondCrossSection;
}

void CadHeader::setDraftAngleSecondCrossSection(double value)
{
    _draftAngleSecondCrossSection = value;
}

double CadHeader::draftMagnitudeFirstCrossSection() const
{
    return _draftMagnitudeFirstCrossSection;
}

void CadHeader::setDraftMagnitudeFirstCrossSection(double value)
{
    _draftMagnitudeFirstCrossSection = value;
}

double CadHeader::draftMagnitudeSecondCrossSection() const
{
    return _draftMagnitudeSecondCrossSection;
}

void CadHeader::setDraftMagnitudeSecondCrossSection(double value)
{
    _draftMagnitudeSecondCrossSection = value;
}

short CadHeader::solidLoftedShape() const
{
    return _solidLoftedShape;
}

void CadHeader::setSolidLoftedShape(short value)
{
    _solidLoftedShape = value;
}

char CadHeader::loftedObjectNormals() const
{
    return _loftedObjectNormals;
}

void CadHeader::setLoftedObjectNormals(char value)
{
    _loftedObjectNormals = value;
}

double CadHeader::latitude() const
{
    return _latitude;
}

void CadHeader::setLatitude(double value)
{
    _latitude = value;
}

double CadHeader::longitude() const
{
    return _longitude;
}

void CadHeader::setLongitude(double value)
{
    _longitude = value;
}

double CadHeader::northDirection() const
{
    return _northDirection;
}

void CadHeader::setNorthDirection(double value)
{
    _northDirection = value;
}

int CadHeader::timeZone() const
{
    return _timeZone;
}

void CadHeader::setTimeZone(int value)
{
    _timeZone = value;
}

char CadHeader::displayLightGlyphs() const
{
    return _displayLightGlyphs;
}

void CadHeader::setDisplayLightGlyphs(char value)
{
    _displayLightGlyphs = value;
}

char CadHeader::dwgUnderlayFramesVisibility() const
{
    return _dwgUnderlayFramesVisibility;
}

void CadHeader::setDwgUnderlayFramesVisibility(char value)
{
    _dwgUnderlayFramesVisibility = value;
}

char CadHeader::dgnUnderlayFramesVisibility() const
{
    return _dgnUnderlayFramesVisibility;
}

void CadHeader::setDgnUnderlayFramesVisibility(char value)
{
    _dgnUnderlayFramesVisibility = value;
}

ShadowMode CadHeader::shadowMode() const
{
    return _shadowMode;
}

void CadHeader::setShadowMode(ShadowMode value)
{
    _shadowMode = value;
}

double CadHeader::shadowPlaneLocation() const
{
    return _shadowPlaneLocation;
}

void CadHeader::setShadowPlaneLocation(double value)
{
    _shadowPlaneLocation = value;
}

std::string CadHeader::styleSheetName() const
{
    return _styleSheetName;
}

void CadHeader::setStyleSheetName(const std::string &value)
{
    _styleSheetName = value;
}

std::string CadHeader::dimensionTextStyleName() const
{
    return _dimensionTextStyle->name();
}

void CadHeader::setDimensionTextStyleName(const std::string &value)
{
    if (_document)
    {
        _dimensionTextStyle = _document->textStyles()->valueT<TextStyle *>(value);
    }
    else
    {
        delete _dimensionTextStyle;
        _dimensionTextStyle = new TextStyle(value);
    }
}

short CadHeader::dimensionAngularDimensionDecimalPlaces() const
{
    return _dimensionStyleOverrides->angularDecimalPlaces();
}

void CadHeader::setDimensionAngularDimensionDecimalPlaces(short value)
{
    _dimensionStyleOverrides->setAngularDecimalPlaces(value);
}

short CadHeader::dimensionDecimalPlaces() const
{
    return _dimensionStyleOverrides->decimalPlaces();
}

void CadHeader::setDimensionDecimalPlaces(short value)
{
    _dimensionStyleOverrides->setDecimalPlaces(value);
}

short CadHeader::dimensionToleranceDecimalPlaces() const
{
    return _dimensionStyleOverrides->toleranceDecimalPlaces();
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

double CadHeader::dimensionScaleFactor() const
{
    return _dimensionStyleOverrides->scaleFactor();
}

void CadHeader::setDimensionScaleFactor(double value)
{
    _dimensionStyleOverrides->setScaleFactor(value);
}

short CadHeader::dimensionAlternateUnitDecimalPlaces() const
{
    return _dimensionStyleOverrides->alternateUnitDecimalPlaces();
}

void CadHeader::setDimensionAlternateUnitDecimalPlaces(short value)
{
    _dimensionStyleOverrides->setAlternateUnitDecimalPlaces(value);
}

short CadHeader::dimensionAlternateUnitToleranceDecimalPlaces() const
{
    return _dimensionStyleOverrides->alternateUnitToleranceDecimalPlaces();
}

void CadHeader::setDimensionAlternateUnitToleranceDecimalPlaces(short value)
{
    _dimensionStyleOverrides->setAlternateUnitToleranceDecimalPlaces(value);
}

AngularUnitFormat CadHeader::dimensionAngularUnit() const
{
    return _dimensionStyleOverrides->angularUnit();
}

void CadHeader::setDimensionAngularUnit(AngularUnitFormat value)
{
    _dimensionStyleOverrides->setAngularUnit(value);
}

FractionFormat CadHeader::dimensionFractionFormat() const
{
    return _dimensionStyleOverrides->fractionFormat();
}

void CadHeader::setDimensionFractionFormat(FractionFormat value)
{
    _dimensionStyleOverrides->setFractionFormat(value);
}

LinearUnitFormat CadHeader::dimensionLinearUnitFormat() const
{
    return _dimensionStyleOverrides->linearUnitFormat();
}

void CadHeader::setDimensionLinearUnitFormat(LinearUnitFormat value)
{
    _dimensionStyleOverrides->setLinearUnitFormat(value);
}

char CadHeader::dimensionDecimalSeparator() const
{
    return _dimensionStyleOverrides->decimalSeparator();
}

void CadHeader::setDimensionDecimalSeparator(char value)
{
    _dimensionStyleOverrides->setDecimalSeparator(value);
}

TextMovement CadHeader::dimensionTextMovement() const
{
    return _dimensionStyleOverrides->textMovement();
}

void CadHeader::setDimensionTextMovement(TextMovement value)
{
    _dimensionStyleOverrides->setTextMovement(value);
}

DimensionTextHorizontalAlignment CadHeader::dimensionTextHorizontalAlignment() const
{
    return _dimensionStyleOverrides->textHorizontalAlignment();
}

void CadHeader::setDimensionTextHorizontalAlignment(DimensionTextHorizontalAlignment value)
{
    _dimensionStyleOverrides->setTextHorizontalAlignment(value);
}

bool CadHeader::dimensionSuppressFirstDimensionLine() const
{
    return _dimensionStyleOverrides->suppressFirstDimensionLine();
}

void CadHeader::setDimensionSuppressFirstDimensionLine(bool value)
{
    _dimensionStyleOverrides->setSuppressFirstDimensionLine(value);
}

bool CadHeader::dimensionSuppressSecondDimensionLine() const
{
    return _dimensionStyleOverrides->suppressSecondDimensionLine();
}

void CadHeader::setDimensionSuppressSecondDimensionLine(bool value)
{
    _dimensionStyleOverrides->setSuppressSecondDimensionLine(value);
}

bool CadHeader::dimensionGenerateTolerances() const
{
    return _dimensionStyleOverrides->generateTolerances();
}

void CadHeader::setDimensionGenerateTolerances(bool value)
{
    _dimensionStyleOverrides->setGenerateTolerances(value);
}

ToleranceAlignment CadHeader::dimensionToleranceAlignment() const
{
    return _dimensionStyleOverrides->toleranceAlignment();
}

void CadHeader::setDimensionToleranceAlignment(ToleranceAlignment value)
{
    _dimensionStyleOverrides->setToleranceAlignment(value);
}

ZeroHandling CadHeader::dimensionZeroHandling() const
{
    return _dimensionStyleOverrides->zeroHandling();
}

void CadHeader::setDimensionZeroHandling(ZeroHandling value)
{
    _dimensionStyleOverrides->setZeroHandling(value);
}

ZeroHandling CadHeader::dimensionToleranceZeroHandling() const
{
    return _dimensionStyleOverrides->toleranceZeroHandling();
}

void CadHeader::setDimensionToleranceZeroHandling(ZeroHandling value)
{
    _dimensionStyleOverrides->setToleranceZeroHandling(value);
}

short CadHeader::dimensionFit() const
{
    return _dimensionStyleOverrides->dimensionFit();
}

void CadHeader::setDimensionFit(short value)
{
    _dimensionStyleOverrides->setDimensionFit(value);
}

ZeroHandling CadHeader::dimensionAlternateUnitZeroHandling() const
{
    return _dimensionStyleOverrides->alternateUnitZeroHandling();
}

void CadHeader::setDimensionAlternateUnitZeroHandling(ZeroHandling value)
{
    _dimensionStyleOverrides->setAlternateUnitZeroHandling(value);
}

ZeroHandling CadHeader::dimensionAlternateUnitToleranceZeroHandling() const
{
    return _dimensionStyleOverrides->alternateUnitToleranceZeroHandling();
}

void CadHeader::setDimensionAlternateUnitToleranceZeroHandling(ZeroHandling value)
{
    _dimensionStyleOverrides->setAlternateUnitToleranceZeroHandling(value);
}

bool CadHeader::dimensionCursorUpdate() const
{
    return _dimensionStyleOverrides->cursorUpdate();
}

void CadHeader::setDimensionCursorUpdate(bool value)
{
    _dimensionStyleOverrides->setCursorUpdate(value);
}

TextArrowFitType CadHeader::dimensionDimensionTextArrowFit() const
{
    return _dimensionStyleOverrides->dimensionTextArrowFit();
}

void CadHeader::setDimensionDimensionTextArrowFit(TextArrowFitType value)
{
    _dimensionStyleOverrides->setDimensionTextArrowFit(value);
}

double CadHeader::dimensionAlternateUnitRounding() const
{
    return _dimensionStyleOverrides->alternateUnitRounding();
}

void CadHeader::setDimensionAlternateUnitRounding(double value)
{
    _dimensionStyleOverrides->setAlternateUnitRounding(value);
}

std::string CadHeader::dimensionAlternateDimensioningSuffix() const
{
    return _dimensionStyleOverrides->alternateDimensioningSuffix();
}

void CadHeader::setDimensionAlternateDimensioningSuffix(const std::string &value)
{
    _dimensionStyleOverrides->setAlternateDimensioningSuffix(value);
}

double CadHeader::dimensionArrowSize() const
{
    return _dimensionStyleOverrides->arrowSize();
}

void CadHeader::setDimensionArrowSize(double value)
{
    _dimensionStyleOverrides->setArrowSize(value);
}

ZeroHandling CadHeader::dimensionAngularZeroHandling() const
{
    return _dimensionStyleOverrides->angularZeroHandling();
}

void CadHeader::setDimensionAngularZeroHandling(ZeroHandling value)
{
    _dimensionStyleOverrides->setAngularZeroHandling(value);
}

ArcLengthSymbolPosition CadHeader::dimensionArcLengthSymbolPosition() const
{
    return _dimensionStyleOverrides->arcLengthSymbolPosition();
}

void CadHeader::setDimensionArcLengthSymbolPosition(ArcLengthSymbolPosition value)
{
    _dimensionStyleOverrides->setArcLengthSymbolPosition(value);
}

bool CadHeader::dimensionSeparateArrowBlocks() const
{
    return _dimensionStyleOverrides->separateArrowBlocks();
}

void CadHeader::setDimensionSeparateArrowBlocks(bool value)
{
    _dimensionStyleOverrides->setSeparateArrowBlocks(value);
}

double CadHeader::dimensionCenterMarkSize() const
{
    return _dimensionStyleOverrides->centerMarkSize();
}

void CadHeader::setDimensionCenterMarkSize(double value)
{
    _dimensionStyleOverrides->setCenterMarkSize(value);
}

double CadHeader::dimensionTickSize() const
{
    return _dimensionStyleOverrides->tickSize();
}

void CadHeader::setDimensionTickSize(double value)
{
    _dimensionStyleOverrides->setTickSize(value);
}

Color CadHeader::dimensionLineColor() const
{
    return _dimensionStyleOverrides->dimensionLineColor();
}

void CadHeader::setDimensionLineColor(const Color &value)
{
    _dimensionStyleOverrides->setDimensionLineColor(value);
}

Color CadHeader::dimensionExtensionLineColor() const
{
    return _dimensionStyleOverrides->extensionLineColor();
}

void CadHeader::setDimensionExtensionLineColor(const Color &value)
{
    _dimensionStyleOverrides->setExtensionLineColor(value);
}

Color CadHeader::dimensionTextColor() const
{
    return _dimensionStyleOverrides->textColor();
}

void CadHeader::setDimensionTextColor(const Color &value)
{
    _dimensionStyleOverrides->setTextColor(value);
}

double CadHeader::dimensionLineExtension() const
{
    return _dimensionStyleOverrides->dimensionLineExtension();
}

void CadHeader::setDimensionLineExtension(double value)
{
    _dimensionStyleOverrides->setDimensionLineExtension(value);
}

double CadHeader::dimensionLineIncrement() const
{
    return _dimensionStyleOverrides->dimensionLineIncrement();
}

void CadHeader::setDimensionLineIncrement(double value)
{
    _dimensionStyleOverrides->setDimensionLineIncrement(value);
}

double CadHeader::dimensionExtensionLineExtension() const
{
    return _dimensionStyleOverrides->extensionLineExtension();
}

void CadHeader::setDimensionExtensionLineExtension(double value)
{
    _dimensionStyleOverrides->setExtensionLineExtension(value);
}

bool CadHeader::dimensionIsExtensionLineLengthFixed() const
{
    return _dimensionStyleOverrides->isExtensionLineLengthFixed();
}

void CadHeader::setDimensionIsExtensionLineLengthFixed(bool value)
{
    _dimensionStyleOverrides->setIsExtensionLineLengthFixed(value);
}

double CadHeader::dimensionFixedExtensionLineLength() const
{
    return _dimensionStyleOverrides->fixedExtensionLineLength();
}

void CadHeader::setDimensionFixedExtensionLineLength(double value)
{
    _dimensionStyleOverrides->setFixedExtensionLineLength(value);
}

double CadHeader::dimensionJoggedRadiusDimensionTransverseSegmentAngle() const
{
    return _dimensionStyleOverrides->joggedRadiusDimensionTransverseSegmentAngle();
}

void CadHeader::setDimensionJoggedRadiusDimensionTransverseSegmentAngle(double value)
{
    _dimensionStyleOverrides->setJoggedRadiusDimensionTransverseSegmentAngle(value);
}

DimensionTextBackgroundFillMode CadHeader::dimensionTextBackgroundFillMode() const
{
    return _dimensionStyleOverrides->textBackgroundFillMode();
}

void CadHeader::setDimensionTextBackgroundFillMode(DimensionTextBackgroundFillMode value)
{
    _dimensionStyleOverrides->setTextBackgroundFillMode(value);
}

Color CadHeader::dimensionTextBackgroundColor() const
{
    return _dimensionStyleOverrides->textBackgroundColor();
}

void CadHeader::setDimensionTextBackgroundColor(const Color &value)
{
    _dimensionStyleOverrides->setTextBackgroundColor(value);
}

double CadHeader::dimensionLineGap() const
{
    return _dimensionStyleOverrides->dimensionLineGap();
}

void CadHeader::setDimensionLineGap(double value)
{
    _dimensionStyleOverrides->setDimensionLineGap(value);
}

double CadHeader::dimensionLinearScaleFactor() const
{
    return _dimensionStyleOverrides->linearScaleFactor();
}

void CadHeader::setDimensionLinearScaleFactor(double value)
{
    _dimensionStyleOverrides->setLinearScaleFactor(value);
}

double CadHeader::dimensionTextVerticalPosition() const
{
    return _dimensionStyleOverrides->textVerticalPosition();
}

void CadHeader::setDimensionTextVerticalPosition(double value)
{
    _dimensionStyleOverrides->setTextVerticalPosition(value);
}

LineweightType CadHeader::dimensionLineWeight() const
{
    return _dimensionStyleOverrides->dimensionLineWeight();
}

void CadHeader::setDimensionLineWeight(LineweightType value)
{
    _dimensionStyleOverrides->setDimensionLineWeight(value);
}

LineweightType CadHeader::extensionLineWeight() const
{
    return _dimensionStyleOverrides->extensionLineWeight();
}

void CadHeader::setExtensionLineWeight(LineweightType value)
{
    _dimensionStyleOverrides->setExtensionLineWeight(value);
}

std::string CadHeader::dimensionPostFix() const
{
    return _dimensionStyleOverrides->postFix();
}

void CadHeader::setDimensionPostFix(const std::string &value)
{
    _dimensionStyleOverrides->setPostFix(value);
}

double CadHeader::dimensionRounding() const
{
    return _dimensionStyleOverrides->rounding();
}

void CadHeader::setDimensionRounding(double value)
{
    _dimensionStyleOverrides->setRounding(value);
}

bool CadHeader::dimensionSuppressFirstExtensionLine() const
{
    return _dimensionStyleOverrides->suppressFirstExtensionLine();
}

void CadHeader::setDimensionSuppressFirstExtensionLine(bool value)
{
    _dimensionStyleOverrides->setSuppressFirstExtensionLine(value);
}

bool CadHeader::dimensionSuppressSecondExtensionLine() const
{
    return _dimensionStyleOverrides->suppressSecondExtensionLine();
}

void CadHeader::setDimensionSuppressSecondExtensionLine(bool value)
{
    _dimensionStyleOverrides->setSuppressSecondExtensionLine(value);
}

bool CadHeader::dimensionSuppressOutsideExtensions() const
{
    return _dimensionStyleOverrides->suppressOutsideExtensions();
}

void CadHeader::setDimensionSuppressOutsideExtensions(bool value)
{
    _dimensionStyleOverrides->setSuppressOutsideExtensions(value);
}

DimensionTextVerticalAlignment CadHeader::dimensionTextVerticalAlignment() const
{
    return _dimensionStyleOverrides->textVerticalAlignment();
}

void CadHeader::setDimensionTextVerticalAlignment(DimensionTextVerticalAlignment value)
{
    _dimensionStyleOverrides->setTextVerticalAlignment(value);
}

short CadHeader::dimensionUnit() const
{
    return _dimensionStyleOverrides->dimensionUnit();
}

void CadHeader::setDimensionUnit(short value)
{
    _dimensionStyleOverrides->setDimensionUnit(value);
}

double CadHeader::dimensionToleranceScaleFactor() const
{
    return _dimensionStyleOverrides->toleranceScaleFactor();
}

void CadHeader::setDimensionToleranceScaleFactor(double value)
{
    _dimensionStyleOverrides->setToleranceScaleFactor(value);
}

bool CadHeader::dimensionTextInsideHorizontal() const
{
    return _dimensionStyleOverrides->textInsideHorizontal();
}

void CadHeader::setDimensionTextInsideHorizontal(bool value)
{
    _dimensionStyleOverrides->setTextInsideHorizontal(value);
}

bool CadHeader::dimensionTextInsideExtensions() const
{
    return _dimensionStyleOverrides->textInsideExtensions();
}

void CadHeader::setDimensionTextInsideExtensions(bool value)
{
    _dimensionStyleOverrides->setTextInsideExtensions(value);
}

double CadHeader::dimensionMinusTolerance() const
{
    return _dimensionStyleOverrides->minusTolerance();
}

void CadHeader::setDimensionMinusTolerance(double value)
{
    _dimensionStyleOverrides->setMinusTolerance(value);
}

bool CadHeader::dimensionTextOutsideExtensions() const
{
    return _dimensionStyleOverrides->textOutsideExtensions();
}

void CadHeader::setDimensionTextOutsideExtensions(bool value)
{
    _dimensionStyleOverrides->setTextOutsideExtensions(value);
}

bool CadHeader::dimensionTextOutsideHorizontal() const
{
    return _dimensionStyleOverrides->textOutsideHorizontal();
}

void CadHeader::setDimensionTextOutsideHorizontal(bool value)
{
    _dimensionStyleOverrides->setTextOutsideHorizontal(value);
}

bool CadHeader::dimensionLimitsGeneration() const
{
    return _dimensionStyleOverrides->limitsGeneration();
}

void CadHeader::setDimensionLimitsGeneration(bool value)
{
    _dimensionStyleOverrides->setLimitsGeneration(value);
}

double CadHeader::dimensionPlusTolerance() const
{
    return _dimensionStyleOverrides->plusTolerance();
}

void CadHeader::setDimensionPlusTolerance(double value)
{
    _dimensionStyleOverrides->setPlusTolerance(value);
}

double CadHeader::dimensionTextHeight() const
{
    return _dimensionStyleOverrides->textHeight();
}

void CadHeader::setDimensionTextHeight(double value)
{
    _dimensionStyleOverrides->setTextHeight(value);
}

TextDirection CadHeader::dimensionTextDirection() const
{
    return _dimensionStyleOverrides->textDirection();
}

void CadHeader::setDimensionTextDirection(TextDirection value)
{
    _dimensionStyleOverrides->setTextDirection(value);
}

double CadHeader::dimensionAltMzf() const
{
    return _dimensionStyleOverrides->altMzf();
}

void CadHeader::setDimensionAltMzf(double value)
{
    _dimensionStyleOverrides->setAltMzf(value);
}

std::string CadHeader::dimensionAltMzs() const
{
    return _dimensionStyleOverrides->altMzs();
}

void CadHeader::setDimensionAltMzs(const std::string &value)
{
    _dimensionStyleOverrides->setAltMzs(value);
}

double CadHeader::dimensionMzf() const
{
    return _dimensionStyleOverrides->mzf();
}

void CadHeader::setDimensionMzf(double value)
{
    _dimensionStyleOverrides->setMzf(value);
}

std::string CadHeader::dimensionMzs() const
{
    return _dimensionStyleOverrides->mzs();
}

void CadHeader::setDimensionMzs(const std::string &value)
{
    _dimensionStyleOverrides->setMzs(value);
}

std::string CadHeader::dimensionLineType() const
{
    return _dimensionLineType;
}

void CadHeader::setDimensionLineType(const std::string &value)
{
    _dimensionLineType = value;
}

std::string CadHeader::dimensionTex1() const
{
    return _dimensionTex1;
}

void CadHeader::setDimensionTex1(const std::string &value) {}

std::string CadHeader::dimensionTex2() const
{
    return _dimensionTex2;
}

void CadHeader::setDimensionTex2(const std::string &value) {}

Layer *CadHeader::currentLayer() const
{
    if (!_document)
    {
        return _currentLayer;
    }
    else
    {
        return _document->layers()->valueT<Layer *>(currentLayerName());
    }
}

void CadHeader::setCurrentLayer(Layer *value)
{
    delete _currentLayer;
    _currentLayer = value;
}

LineType *CadHeader::currentLineType() const
{
    return _currentLineType;
}

void CadHeader::setCurrentLineType(LineType *) {}

TextStyle *CadHeader::currentTextStyle() const
{
    return _currentTextStyle;
}

void CadHeader::setTextStyle(TextStyle *) {}

TextStyle *CadHeader::dimensionTextStyle() const
{
    if (!_document)
    {
        return _dimensionTextStyle;
    }
    else
    {
        return _document->textStyles()->valueT<TextStyle *>(dimensionTextStyleName());
    }
}

void CadHeader::setDimensionTextStyle(TextStyle *value)
{
    delete _dimensionTextStyle;
    _dimensionTextStyle = value;
}

DimensionStyle *CadHeader::dimensionStyleOverrides() const
{
    return _dimensionStyleOverrides;
}

UCS *CadHeader::modelSpaceUcs() const
{
    return _modelSpaceUcs;
}

void CadHeader::setModelSpaceUcs(UCS *value)
{
    delete _modelSpaceUcs;
    _modelSpaceUcs = value;
}

UCS *CadHeader::modelSpaceUcsBase() const
{
    return _modelSpaceUcsBase;
}

void CadHeader::setModelSpaceUcsBase(UCS *value)
{
    delete _modelSpaceUcsBase;
    _modelSpaceUcsBase = value;
}

UCS *CadHeader::paperSpaceUcs() const
{
    return _paperSpaceUcs;
}

void CadHeader::setPaperSpaceUcs(UCS *value)
{
    delete _paperSpaceUcs;
    _paperSpaceUcs = value;
}

UCS *CadHeader::paperSpaceUcsBase() const
{
    return _paperSpaceUcsBase;
}

void CadHeader::setPaperSpaceUcsBase(UCS *value)
{
    delete _paperSpaceUcsBase;
    _paperSpaceUcsBase = value;
}

MLineStyle *CadHeader::currentMLineStyle() const
{
    return _currentMLineStyle;
}

void CadHeader::setCurrentMLineStyle(MLineStyle *value) {}

DimensionStyle *CadHeader::currentDimensionStyle() const
{
    return _currentDimensionStyle;
}

void CadHeader::setCurrentDimensionStyle(DimensionStyle *value) {}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<CadHeader>("CadHeader")
            .constructor<>()
            .property("angleBase", &CadHeader::angleBase, &CadHeader::setAngleBase)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::ANGBASE, {50})))
            .property("angularDirection", &CadHeader::angularDirection, &CadHeader::setAngularDirection)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::ANGDIR, {70})))
            .property("angularUnit", &CadHeader::angularUnit, &CadHeader::setAngularUnit)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::AUNITS, {70})))
            .property("angularUnitPrecision", &CadHeader::angularUnitPrecision, &CadHeader::setAngularUnitPrecision)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::AUPREC, {70})))
            .property("arrowBlockName", &CadHeader::arrowBlockName, &CadHeader::setArrowBlockName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLDRBLK, {1})))
            .property("associatedDimensions", &CadHeader::associatedDimensions, &CadHeader::setAssociatedDimensions)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMASO, {70})))
            .property("attributeVisibility", &CadHeader::attributeVisibility, &CadHeader::setAttributeVisibility)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::ATTMODE, {70})))
            .property("blipMode", &CadHeader::blipMode, &CadHeader::setBlipMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::BLIPMODE, {70})))
            .property("cameraDisplayObjects", &CadHeader::cameraDisplayObjects, &CadHeader::setCameraDisplayObjects)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CAMERADISPLAY, {290})))
            .property("cameraHeight", &CadHeader::cameraHeight, &CadHeader::setCameraHeight)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CAMERAHEIGHT, {40})))
            .property("chamferAngle", &CadHeader::chamferAngle, &CadHeader::setChamferAngle)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CHAMFERD, {40})))
            .property("chamferDistance1", &CadHeader::chamferDistance1, &CadHeader::setChamferDistance1)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CHAMFERA, {40})))
            .property("chamferDistance2", &CadHeader::chamferDistance2, &CadHeader::setChamferDistance2)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CHAMFERB, {40})))
            .property("chamferLength", &CadHeader::chamferLength, &CadHeader::setChamferLength)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CHAMFERC, {40})))
            .property("codePage", &CadHeader::codePage, &CadHeader::setCodePage)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DWGCODEPAGE, {3})))
            .property("createDateTime", &CadHeader::createDateTime, &CadHeader::setCreateDateTime)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TDCREATE, {40})))
            .property("createEllipseAsPolyline", &CadHeader::createEllipseAsPolyline, &CadHeader::setCreateEllipseAsPolyline)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PELLIPSE, {70})))
            .property("currentEntityColor", &CadHeader::currentEntityColor, &CadHeader::setCurrentEntityColor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CECOLOR, {62})))
            .property("currentEntityLinetypeScale", &CadHeader::currentEntityLinetypeScale, &CadHeader::setCurrentEntityLinetypeScale)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CELTSCALE, {40})))
            .property("currentEntityLineWeight", &CadHeader::currentEntityLineWeight, &CadHeader::setCurrentEntityLineWeight)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CELWEIGHT, {370})))
            .property("currentEntityPlotStyle", &CadHeader::currentEntityPlotStyle, &CadHeader::setCurrentEntityPlotStyle)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CEPSNTYPE, {380})))
            .property("currentLayerName", &CadHeader::currentLayerName, &CadHeader::setCurrentLayerName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CLAYER, {8})))
            .property("currentLineTypeName", &CadHeader::currentLineTypeName, &CadHeader::setCurrentLineTypeName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CELTYPE, true, {6})))
            .property("currentMultilineJustification", &CadHeader::currentMultilineJustification, &CadHeader::setCurrentMultilineJustification)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CMLJUST, {70})))
            .property("currentMultilineScale", &CadHeader::currentMultilineScale, &CadHeader::setCurrentMultilineScale)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CMLSCALE, {40})))
            .property("currentMultiLineStyleName", &CadHeader::currentMultiLineStyleName, &CadHeader::setCurrentMultiLineStyleName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CMLSTYLE, true, {2})))
            .property("dgnUnderlayFramesVisibility", &CadHeader::dgnUnderlayFramesVisibility, &CadHeader::setDgnUnderlayFramesVisibility)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DGNFRAME, {200})))
            .property("dimensionAlternateDimensioningSuffix", &CadHeader::dimensionAlternateDimensioningSuffix, &CadHeader::setDimensionAlternateDimensioningSuffix)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMAPOST, {1})))
            .property("dimensionAlternateUnitDecimalPlaces", &CadHeader::dimensionAlternateUnitDecimalPlaces, &CadHeader::setDimensionAlternateUnitDecimalPlaces)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTD, {70})))
            .property("dimensionAlternateUnitDimensioning", &CadHeader::dimensionAlternateUnitDimensioning, &CadHeader::setDimensionAlternateUnitDimensioning)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALT, {70})))
            .property("dimensionAlternateUnitFormat", &CadHeader::dimensionAlternateUnitFormat, &CadHeader::setDimensionAlternateUnitFormat)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTU, {70})))
            .property("dimensionAlternateUnitRounding", &CadHeader::dimensionAlternateUnitRounding, &CadHeader::setDimensionAlternateUnitRounding)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTRND, {40})))
            .property("dimensionAlternateUnitScaleFactor", &CadHeader::dimensionAlternateUnitScaleFactor, &CadHeader::setDimensionAlternateUnitScaleFactor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTF, {40})))
            .property("dimensionAlternateUnitToleranceDecimalPlaces", &CadHeader::dimensionAlternateUnitToleranceDecimalPlaces, &CadHeader::setDimensionAlternateUnitToleranceDecimalPlaces)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTTD, {70})))
            .property("dimensionAlternateUnitToleranceZeroHandling", &CadHeader::dimensionAlternateUnitToleranceZeroHandling, &CadHeader::setDimensionAlternateUnitToleranceZeroHandling)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTTZ, {70})))
            .property("dimensionAlternateUnitZeroHandling", &CadHeader::dimensionAlternateUnitZeroHandling, &CadHeader::setDimensionAlternateUnitZeroHandling)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTZ, {70})))
            .property("dimensionAltMzf", &CadHeader::dimensionAltMzf, &CadHeader::setDimensionAltMzf)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTMZF, {40})))
            .property("dimensionAltMzs", &CadHeader::dimensionAltMzs, &CadHeader::setDimensionAltMzs)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMALTMZS, {6})))
            .property("dimensionAngularDimensionDecimalPlaces", &CadHeader::dimensionAngularDimensionDecimalPlaces, &CadHeader::setDimensionAngularDimensionDecimalPlaces)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMADEC, {70})))
            .property("dimensionAngularUnit", &CadHeader::dimensionAngularUnit, &CadHeader::setDimensionAngularUnit)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMAUNIT, {70})))
            .property("dimensionAngularZeroHandling", &CadHeader::dimensionAngularZeroHandling, &CadHeader::setDimensionAngularZeroHandling)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMAZIN, {70})))
            .property("dimensionArcLengthSymbolPosition", &CadHeader::dimensionArcLengthSymbolPosition, &CadHeader::setDimensionArcLengthSymbolPosition)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMARCSYM, {70})))
            .property("dimensionArrowSize", &CadHeader::dimensionArrowSize, &CadHeader::setDimensionArrowSize)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMASZ, {40})))
            .property("dimensionAssociativity", &CadHeader::dimensionAssociativity, &CadHeader::setDimensionAssociativity)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMASSOC, {280})))
            .property("dimensionBlockName", &CadHeader::dimensionBlockName, &CadHeader::setDimensionBlockName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMBLK, {1})))
            .property("dimensionBlockNameFirst", &CadHeader::dimensionBlockNameFirst, &CadHeader::setDimensionBlockNameFirst)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMBLK1, {1})))
            .property("dimensionBlockNameSecond", &CadHeader::dimensionBlockNameSecond, &CadHeader::setDimensionBlockNameSecond)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMBLK2, {1})))
            .property("dimensionCenterMarkSize", &CadHeader::dimensionCenterMarkSize, &CadHeader::setDimensionCenterMarkSize)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMCEN, {40})))
            .property("dimensionCursorUpdate", &CadHeader::dimensionCursorUpdate, &CadHeader::setDimensionCursorUpdate)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMUPT, {70})))
            .property("dimensionDecimalPlaces", &CadHeader::dimensionDecimalPlaces, &CadHeader::setDimensionDecimalPlaces)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMDEC, {70})))
            .property("dimensionDecimalSeparator", &CadHeader::dimensionDecimalSeparator, &CadHeader::setDimensionDecimalSeparator)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMDSEP, {70})))
            .property("dimensionDimensionTextArrowFit", &CadHeader::dimensionDimensionTextArrowFit, &CadHeader::setDimensionDimensionTextArrowFit)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMATFIT, {70})))
            .property("dimensionExtensionLineColor", &CadHeader::dimensionExtensionLineColor, &CadHeader::setDimensionExtensionLineColor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMCLRE, {70})))
            .property("dimensionExtensionLineExtension", &CadHeader::dimensionExtensionLineExtension, &CadHeader::setDimensionExtensionLineExtension)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMEXE, {40})))
            .property("dimensionExtensionLineOffset", &CadHeader::dimensionExtensionLineOffset, &CadHeader::setDimensionExtensionLineOffset)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMEXO, {40})))
            .property("dimensionFit", &CadHeader::dimensionFit, &CadHeader::setDimensionFit)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMFIT, {40})))
            .property("dimensionFixedExtensionLineLength", &CadHeader::dimensionFixedExtensionLineLength, &CadHeader::setDimensionFixedExtensionLineLength)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMFXL, {40})))
            .property("dimensionFractionFormat", &CadHeader::dimensionFractionFormat, &CadHeader::setDimensionFractionFormat)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMFRAC, {70})))
            .property("dimensionGenerateTolerances", &CadHeader::dimensionGenerateTolerances, &CadHeader::setDimensionGenerateTolerances)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTOL, {70})))
            .property("dimensionIsExtensionLineLengthFixed", &CadHeader::dimensionIsExtensionLineLengthFixed, &CadHeader::setDimensionIsExtensionLineLengthFixed)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMFXLON, {70})))
            .property("dimensionJoggedRadiusDimensionTransverseSegmentAngle", &CadHeader::dimensionJoggedRadiusDimensionTransverseSegmentAngle, &CadHeader::setDimensionJoggedRadiusDimensionTransverseSegmentAngle)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMJOGANG, {40})))
            .property("dimensionLimitsGeneration", &CadHeader::dimensionLimitsGeneration, &CadHeader::setDimensionLimitsGeneration)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLIM, {70})))
            .property("dimensionLinearScaleFactor", &CadHeader::dimensionLinearScaleFactor, &CadHeader::setDimensionLinearScaleFactor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLFAC, {40})))
            .property("dimensionLinearUnitFormat", &CadHeader::dimensionLinearUnitFormat, &CadHeader::setDimensionLinearUnitFormat)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLUNIT, {70})))
            .property("dimensionLineColor", &CadHeader::dimensionLineColor, &CadHeader::setDimensionLineColor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMCLRD, {70})))
            .property("dimensionLineExtension", &CadHeader::dimensionLineExtension, &CadHeader::setDimensionLineExtension)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMDLE, {40})))
            .property("dimensionLineGap", &CadHeader::dimensionLineGap, &CadHeader::setDimensionLineGap)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMGAP, {40})))
            .property("dimensionLineIncrement", &CadHeader::dimensionLineIncrement, &CadHeader::setDimensionLineIncrement)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMDLI, {40})))
            .property("dimensionLineType", &CadHeader::dimensionLineType, &CadHeader::setDimensionLineType)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLTYPE, {6})))
            .property("dimensionLineWeight", &CadHeader::dimensionLineWeight, &CadHeader::setDimensionLineWeight)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLWD, {70})))
            .property("dimensionMinusTolerance", &CadHeader::dimensionMinusTolerance, &CadHeader::setDimensionMinusTolerance)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTM, {40})))
            .property("dimensionMzf", &CadHeader::dimensionMzf, &CadHeader::setDimensionMzf)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMMZF, {40})))
            .property("dimensionMzs", &CadHeader::dimensionMzs, &CadHeader::setDimensionMzs)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMMZS, {6})))
            .property("dimensionPlusTolerance", &CadHeader::dimensionPlusTolerance, &CadHeader::setDimensionPlusTolerance)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTP, {40})))
            .property("dimensionPostFix", &CadHeader::dimensionPostFix, &CadHeader::setDimensionPostFix)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMPOST, {1})))
            .property("dimensionRounding", &CadHeader::dimensionRounding, &CadHeader::setDimensionRounding)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMRND, {40})))
            .property("dimensionScaleFactor", &CadHeader::dimensionScaleFactor, &CadHeader::setDimensionScaleFactor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSCALE, {40})))
            .property("dimensionSeparateArrowBlocks", &CadHeader::dimensionSeparateArrowBlocks, &CadHeader::setDimensionSeparateArrowBlocks)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSAH, {70})))
            .property("currentDimensionStyleName", &CadHeader::currentDimensionStyleName, &CadHeader::setCurrentDimensionStyleName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSTYLE, true, {2})))
            .property("dimensionSuppressFirstDimensionLine", &CadHeader::dimensionSuppressFirstDimensionLine, &CadHeader::setDimensionSuppressFirstDimensionLine)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSD1, {70})))
            .property("dimensionSuppressFirstExtensionLine", &CadHeader::dimensionSuppressFirstExtensionLine, &CadHeader::setDimensionSuppressFirstExtensionLine)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSE1, {70})))
            .property("dimensionSuppressOutsideExtensions", &CadHeader::dimensionSuppressOutsideExtensions, &CadHeader::setDimensionSuppressOutsideExtensions)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSOXD, {70})))
            .property("dimensionSuppressSecondDimensionLine", &CadHeader::dimensionSuppressSecondDimensionLine, &CadHeader::setDimensionSuppressSecondDimensionLine)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSD2, {70})))
            .property("dimensionSuppressSecondExtensionLine", &CadHeader::dimensionSuppressSecondExtensionLine, &CadHeader::setDimensionSuppressSecondExtensionLine)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSE2, {70})))
            .property("dimensionTex1", &CadHeader::dimensionTex1, &CadHeader::setDimensionTex1)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLTEX1, {6})))
            .property("dimensionTex2", &CadHeader::dimensionTex2, &CadHeader::setDimensionTex2)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLTEX2, {6})))
            .property("dimensionTextBackgroundColor", &CadHeader::dimensionTextBackgroundColor, &CadHeader::setDimensionTextBackgroundColor)(metadata("CadSystemVariable", CadSystemVariableAttribute(DxfReferenceType::Ignored, CadSystemVariables::DIMTFILLCLR, {62})))
            .property("dimensionTextBackgroundFillMode", &CadHeader::dimensionTextBackgroundFillMode, &CadHeader::setDimensionTextBackgroundFillMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTFILL, {70})))
            .property("dimensionTextColor", &CadHeader::dimensionTextColor, &CadHeader::setDimensionTextColor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMCLRT, {70})))
            .property("dimensionTextDirection", &CadHeader::dimensionTextDirection, &CadHeader::setDimensionTextDirection)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTXTDIRECTION, {70})))
            .property("dimensionTextHeight", &CadHeader::dimensionTextHeight, &CadHeader::setDimensionTextHeight)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTXT, {40})))
            .property("dimensionTextHorizontalAlignment", &CadHeader::dimensionTextHorizontalAlignment, &CadHeader::setDimensionTextHorizontalAlignment)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMJUST, {70})))
            .property("dimensionTextInsideExtensions", &CadHeader::dimensionTextInsideExtensions, &CadHeader::setDimensionTextInsideExtensions)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTIX, {70})))
            .property("dimensionTextInsideHorizontal", &CadHeader::dimensionTextInsideHorizontal, &CadHeader::setDimensionTextInsideHorizontal)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTIH, {70})))
            .property("dimensionTextMovement", &CadHeader::dimensionTextMovement, &CadHeader::setDimensionTextMovement)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTMOVE, {70})))
            .property("dimensionTextOutsideExtensions", &CadHeader::dimensionTextOutsideExtensions, &CadHeader::setDimensionTextOutsideExtensions)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTOFL, {70})))
            .property("dimensionTextOutsideHorizontal", &CadHeader::dimensionTextOutsideHorizontal, &CadHeader::setDimensionTextOutsideHorizontal)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTOH, {70})))
            .property("dimensionTextStyleName", &CadHeader::dimensionTextStyleName, &CadHeader::setDimensionTextStyleName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTXSTY, true, {7})))
            .property("dimensionTextVerticalAlignment", &CadHeader::dimensionTextVerticalAlignment, &CadHeader::setDimensionTextVerticalAlignment)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTAD, {70})))
            .property("dimensionTextVerticalPosition", &CadHeader::dimensionTextVerticalPosition, &CadHeader::setDimensionTextVerticalPosition)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTVP, {40})))
            .property("dimensionTickSize", &CadHeader::dimensionTickSize, &CadHeader::setDimensionTickSize)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTSZ, {40})))
            .property("dimensionToleranceAlignment", &CadHeader::dimensionToleranceAlignment, &CadHeader::setDimensionToleranceAlignment)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTOLJ, {70})))
            .property("dimensionToleranceDecimalPlaces", &CadHeader::dimensionToleranceDecimalPlaces, &CadHeader::setDimensionToleranceDecimalPlaces)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTDEC, {70})))
            .property("dimensionToleranceScaleFactor", &CadHeader::dimensionToleranceScaleFactor, &CadHeader::setDimensionToleranceScaleFactor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTFAC, {40})))
            .property("dimensionToleranceZeroHandling", &CadHeader::dimensionToleranceZeroHandling, &CadHeader::setDimensionToleranceZeroHandling)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMTZIN, {70})))
            .property("dimensionUnit", &CadHeader::dimensionUnit, &CadHeader::setDimensionUnit)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMUNIT, {70})))
            .property("dimensionZeroHandling", &CadHeader::dimensionZeroHandling, &CadHeader::setDimensionZeroHandling)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMZIN, {70})))
            .property("displayLightGlyphs", &CadHeader::displayLightGlyphs, &CadHeader::setDisplayLightGlyphs)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LIGHTGLYPHDISPLAY, {280})))
            .property("displayLineWeight", &CadHeader::displayLineWeight, &CadHeader::setDisplayLineWeight)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LWDISPLAY, {290})))
            .property("displaySilhouetteCurves", &CadHeader::displaySilhouetteCurves, &CadHeader::setDisplaySilhouetteCurves)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DISPSILH, {70})))
            .property("draftAngleFirstCrossSection", &CadHeader::draftAngleFirstCrossSection, &CadHeader::setDraftAngleFirstCrossSection)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LOFTANG1, {40})))
            .property("draftAngleSecondCrossSection", &CadHeader::draftAngleSecondCrossSection, &CadHeader::setDraftAngleSecondCrossSection)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LOFTANG2, {40})))
            .property("draftMagnitudeFirstCrossSection", &CadHeader::draftMagnitudeFirstCrossSection, &CadHeader::setDraftMagnitudeFirstCrossSection)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LOFTMAG1, {40})))
            .property("draftMagnitudeSecondCrossSection", &CadHeader::draftMagnitudeSecondCrossSection, &CadHeader::setDraftMagnitudeSecondCrossSection)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LOFTMAG2, {40})))
            .property("dw3DPrecision", &CadHeader::dw3DPrecision, &CadHeader::setDw3DPrecision)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::_3DDWFPREC, {40})))
            .property("dwgUnderlayFramesVisibility", &CadHeader::dwgUnderlayFramesVisibility, &CadHeader::setDwgUnderlayFramesVisibility)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DWFFRAME, {280})))
            .property("elevation", &CadHeader::elevation, &CadHeader::setElevation)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::ELEVATION, {40})))
            .property("endCaps", &CadHeader::endCaps, &CadHeader::setEndCaps)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::ENDCAPS, {280})))
            .property("entitySortingFlags", &CadHeader::entitySortingFlags, &CadHeader::setEntitySortingFlags)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SORTENTS, {280})))
            .property("extendedNames", &CadHeader::extendedNames, &CadHeader::setExtendedNames)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::EXTNAMES, {290})))
            .property("extensionLineWeight", &CadHeader::extensionLineWeight, &CadHeader::setExtensionLineWeight)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMLWE, {70})))
            .property("externalReferenceClippingBoundaryType", &CadHeader::externalReferenceClippingBoundaryType, &CadHeader::setExternalReferenceClippingBoundaryType)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::XCLIPFRAME, {280})))
            .property("facetResolution", &CadHeader::facetResolution, &CadHeader::setFacetResolution)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::FACETRES, {40})))
            .property("filletRadius", &CadHeader::filletRadius, &CadHeader::setFilletRadius)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::FILLETRAD, {40})))
            .property("fillMode", &CadHeader::fillMode, &CadHeader::setFillMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::FILLMODE, {70})))
            .property("fingerPrintGuid", &CadHeader::fingerPrintGuid, &CadHeader::setFingerPrintGuid)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::FINGERPRINTGUID, {2})))
            .property("haloGapPercentage", &CadHeader::haloGapPercentage, &CadHeader::setHaloGapPercentage)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::HALOGAP, {280})))
            .property("handleSeed", &CadHeader::handleSeed, &CadHeader::setHandleSeed)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::HANDSEED, {5})))
            .property("hideText", &CadHeader::hideText, &CadHeader::setHideText)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::HIDETEXT, {280})))
            .property("hyperLinkBase", &CadHeader::hyperLinkBase, &CadHeader::setHyperLinkBase)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::HYPERLINKBASE, {1})))
            .property("indexCreationFlags", &CadHeader::indexCreationFlags, &CadHeader::setIndexCreationFlags)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::INDEXCTL, {280})))
            .property("insUnits", &CadHeader::insUnits, &CadHeader::setInsUnits)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::INSUNITS, {70})))
            .property("interfereColor", &CadHeader::interfereColor, &CadHeader::setInterfereColor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::INTERFERECOLOR, {62})))
            .property("joinStyle", &CadHeader::joinStyle, &CadHeader::setJoinStyle)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::JOINSTYLE, {280})))
            .property("lastSavedBy", &CadHeader::lastSavedBy, &CadHeader::setLastSavedBy)(metadata("CadSystemVariable", CadSystemVariableAttribute(DxfReferenceType::Ignored, CadSystemVariables::LASTSAVEDBY, {3})))
            .property("latitude", &CadHeader::latitude, &CadHeader::setLatitude)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LATITUDE, {40})))
            .property("lensLength", &CadHeader::lensLength, &CadHeader::setLensLength)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LENSLENGTH, {40})))
            .property("limitCheckingOn", &CadHeader::limitCheckingOn, &CadHeader::setLimitCheckingOn)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LIMCHECK, {70})))
            .property("linearUnitFormat", &CadHeader::linearUnitFormat, &CadHeader::setLinearUnitFormat)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LUNITS, {70})))
            .property("linearUnitPrecision", &CadHeader::linearUnitPrecision, &CadHeader::setLinearUnitPrecision)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LUPREC, {70})))
            .property("lineTypeScale", &CadHeader::lineTypeScale, &CadHeader::setLineTypeScale)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LTSCALE, {40})))
            .property("loftedObjectNormals", &CadHeader::loftedObjectNormals, &CadHeader::setLoftedObjectNormals)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LOFTNORMALS, {280})))
            .property("longitude", &CadHeader::longitude, &CadHeader::setLongitude)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LONGITUDE, {40})))
            .property("maintenanceVersion", &CadHeader::maintenanceVersion, &CadHeader::setMaintenanceVersion)(metadata("CadSystemVariable", CadSystemVariableAttribute(DxfReferenceType::Ignored, CadSystemVariables::ACADMAINTVER, {70})))
            .property("maxViewportCount", &CadHeader::maxViewportCount, &CadHeader::setMaxViewportCount)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::MAXACTVP, {70})))
            .property("measurementUnits", &CadHeader::measurementUnits, &CadHeader::setMeasurementUnits)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::MEASUREMENT, {70})))
            .property("menuFileName", &CadHeader::menuFileName, &CadHeader::setMenuFileName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::MENU, {1})))
            .property("mirrorText", &CadHeader::mirrorText, &CadHeader::setMirrorText)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::MIRRTEXT, {70})))
            .property("modelSpaceExtMax", &CadHeader::modelSpaceExtMax, &CadHeader::setModelSpaceExtMax)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::EXTMAX, {10, 20, 30})))
            .property("modelSpaceExtMin", &CadHeader::modelSpaceExtMin, &CadHeader::setModelSpaceExtMin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::EXTMIN, {10, 20, 30})))
            .property("modelSpaceInsertionBase", &CadHeader::modelSpaceInsertionBase, &CadHeader::setModelSpaceInsertionBase)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::INSBASE, {10, 20, 30})))
            .property("modelSpaceLimitsMax", &CadHeader::modelSpaceLimitsMax, &CadHeader::setModelSpaceLimitsMax)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LIMMAX, {10, 20})))
            .property("modelSpaceLimitsMin", &CadHeader::modelSpaceLimitsMin, &CadHeader::setModelSpaceLimitsMin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LIMMIN, {10, 20})))
            .property("modelSpaceOrigin", &CadHeader::modelSpaceOrigin, &CadHeader::setModelSpaceOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSORG, {10, 20, 30})))
            .property("modelSpaceOrthographicBackDOrigin", &CadHeader::modelSpaceOrthographicBackDOrigin, &CadHeader::setModelSpaceOrthographicBackDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSORGBACK, {10, 20, 30})))
            .property("modelSpaceOrthographicBottomDOrigin", &CadHeader::modelSpaceOrthographicBottomDOrigin, &CadHeader::setModelSpaceOrthographicBottomDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSORGBOTTOM, {10, 20, 30})))
            .property("modelSpaceOrthographicFrontDOrigin", &CadHeader::modelSpaceOrthographicFrontDOrigin, &CadHeader::setModelSpaceOrthographicFrontDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSORGFRONT, {10, 20, 30})))
            .property("modelSpaceOrthographicLeftDOrigin", &CadHeader::modelSpaceOrthographicLeftDOrigin, &CadHeader::setModelSpaceOrthographicLeftDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSORGLEFT, {10, 20, 30})))
            .property("modelSpaceOrthographicRightDOrigin", &CadHeader::modelSpaceOrthographicRightDOrigin, &CadHeader::setModelSpaceOrthographicRightDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSORGRIGHT, {10, 20, 30})))
            .property("modelSpaceOrthographicTopDOrigin", &CadHeader::modelSpaceOrthographicTopDOrigin, &CadHeader::setModelSpaceOrthographicTopDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSORGTOP, {10, 20, 30})))
            .property("modelSpaceXAxis", &CadHeader::modelSpaceXAxis, &CadHeader::setModelSpaceXAxis)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSXDIR, {10, 20, 30})))
            .property("modelSpaceYAxis", &CadHeader::modelSpaceYAxis, &CadHeader::setModelSpaceYAxis)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSYDIR, {10, 20, 30})))
            .property("northDirection", &CadHeader::northDirection, &CadHeader::setNorthDirection)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::NORTHDIRECTION, {40})))
            .property("numberOfSplineSegments", &CadHeader::numberOfSplineSegments, &CadHeader::setNumberOfSplineSegments)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SPLINESEGS, {70})))
            .property("objectSnapMode", &CadHeader::objectSnapMode, &CadHeader::setObjectSnapMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::OSMODE, {70})))
            .property("orthoMode", &CadHeader::orthoMode, &CadHeader::setOrthoMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::ORTHOMODE, {70})))
            .property("paperSpaceBaseName", &CadHeader::paperSpaceBaseName, &CadHeader::setPaperSpaceBaseName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSBASE, true, {2})))
            .property("paperSpaceElevation", &CadHeader::paperSpaceElevation, &CadHeader::setPaperSpaceElevation)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PELEVATION, {40})))
            .property("paperSpaceExtMax", &CadHeader::paperSpaceExtMax, &CadHeader::setPaperSpaceExtMax)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PEXTMAX, {10, 20, 30})))
            .property("paperSpaceExtMin", &CadHeader::paperSpaceExtMin, &CadHeader::setPaperSpaceExtMin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PEXTMIN, {10, 20, 30})))
            .property("paperSpaceInsertionBase", &CadHeader::paperSpaceInsertionBase, &CadHeader::setPaperSpaceInsertionBase)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PINSBASE, {10, 20, 30})))
            .property("paperSpaceLimitsChecking", &CadHeader::paperSpaceLimitsChecking, &CadHeader::setPaperSpaceLimitsChecking)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PLIMCHECK, {70})))
            .property("paperSpaceLimitsMax", &CadHeader::paperSpaceLimitsMax, &CadHeader::setPaperSpaceLimitsMax)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PLIMMAX, {10, 20})))
            .property("paperSpaceLimitsMin", &CadHeader::paperSpaceLimitsMin, &CadHeader::setPaperSpaceLimitsMin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PLIMMIN, {10, 20})))
            .property("paperSpaceLineTypeScaling", &CadHeader::paperSpaceLineTypeScaling, &CadHeader::setPaperSpaceLineTypeScaling)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PSLTSCALE, {70})))
            .property("paperSpaceName", &CadHeader::paperSpaceName, &CadHeader::setPaperSpaceName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSNAME, true, {2})))
            .property("paperSpaceOrthographicBackDOrigin", &CadHeader::paperSpaceOrthographicBackDOrigin, &CadHeader::setPaperSpaceOrthographicBackDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSORGBACK, {10, 20, 30})))
            .property("paperSpaceOrthographicBottomDOrigin", &CadHeader::paperSpaceOrthographicBottomDOrigin, &CadHeader::setPaperSpaceOrthographicBottomDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSORGBOTTOM, {10, 20, 30})))
            .property("paperSpaceOrthographicFrontDOrigin", &CadHeader::paperSpaceOrthographicFrontDOrigin, &CadHeader::setPaperSpaceOrthographicFrontDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSORGFRONT, {10, 20, 30})))
            .property("paperSpaceOrthographicLeftDOrigin", &CadHeader::paperSpaceOrthographicLeftDOrigin, &CadHeader::setPaperSpaceOrthographicLeftDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSORGLEFT, {10, 20, 30})))
            .property("paperSpaceOrthographicRightDOrigin", &CadHeader::paperSpaceOrthographicRightDOrigin, &CadHeader::setPaperSpaceOrthographicRightDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSORGRIGHT, {10, 20, 30})))
            .property("paperSpaceOrthographicTopDOrigin", &CadHeader::paperSpaceOrthographicTopDOrigin, &CadHeader::setPaperSpaceOrthographicTopDOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSORGTOP, {10, 20, 30})))
            .property("paperSpaceUcsOrigin", &CadHeader::paperSpaceUcsOrigin, &CadHeader::setPaperSpaceUcsOrigin)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSORG, {10, 20, 30})))
            .property("paperSpaceUcsXAxis", &CadHeader::paperSpaceUcsXAxis, &CadHeader::setPaperSpaceUcsXAxis)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSXDIR, {10, 20, 30})))
            .property("paperSpaceUcsYAxis", &CadHeader::paperSpaceUcsYAxis, &CadHeader::setPaperSpaceUcsYAxis)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PUCSYDIR, {10, 20, 30})))
            .property("plotStyleMode", &CadHeader::plotStyleMode, &CadHeader::setPlotStyleMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PSTYLEMODE, {290})))
            .property("pointDisplayMode", &CadHeader::pointDisplayMode, &CadHeader::setPointDisplayMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PDMODE, {70})))
            .property("pointDisplaySize", &CadHeader::pointDisplaySize, &CadHeader::setPointDisplaySize)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PDSIZE, {40})))
            .property("polylineLineTypeGeneration", &CadHeader::polylineLineTypeGeneration, &CadHeader::setPolylineLineTypeGeneration)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PLINEGEN, {70})))
            .property("polylineWidthDefault", &CadHeader::polylineWidthDefault, &CadHeader::setPolylineWidthDefault)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PLINEWID, {40})))
            .property("projectName", &CadHeader::projectName, &CadHeader::setProjectName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PROJECTNAME, {1})))
            .property("proxyGraphics", &CadHeader::proxyGraphics, &CadHeader::setProxyGraphics)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PROXYGRAPHICS, {70})))
            .property("quickTextMode", &CadHeader::quickTextMode, &CadHeader::setQuickTextMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::QTEXTMODE, {70})))
            .property("regenerationMode", &CadHeader::regenerationMode, &CadHeader::setRegenerationMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::REGENMODE, {70})))
            .property("requiredVersions", &CadHeader::requiredVersions, &CadHeader::setRequiredVersions)(metadata("CadSystemVariable", CadSystemVariableAttribute(DxfReferenceType::Ignored, CadSystemVariables::REQUIREDVERSIONS, {70})))
            .property("retainXRefDependentVisibilitySettings", &CadHeader::retainXRefDependentVisibilitySettings, &CadHeader::setRetainXRefDependentVisibilitySettings)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::VISRETAIN, {70})))
            .property("shadeDiffuseToAmbientPercentage", &CadHeader::shadeDiffuseToAmbientPercentage, &CadHeader::setShadeDiffuseToAmbientPercentage)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SHADEDIF, {70})))
            .property("shadeEdge", &CadHeader::shadeEdge, &CadHeader::setShadeEdge)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SHADEDGE, {70})))
            .property("shadowMode", &CadHeader::shadowMode, &CadHeader::setShadowMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::CSHADOW, {280})))
            .property("shadowPlaneLocation", &CadHeader::shadowPlaneLocation, &CadHeader::setShadowPlaneLocation)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SHADOWPLANELOCATION, {40})))
            .property("showModelSpace", &CadHeader::showModelSpace, &CadHeader::setShowModelSpace)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TILEMODE, {70})))
            .property("showSolidsHistory", &CadHeader::showSolidsHistory, &CadHeader::setShowSolidsHistory)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SHOWHIST, {280})))
            .property("showSplineControlPoints", &CadHeader::showSplineControlPoints, &CadHeader::setShowSplineControlPoints)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SPLFRAME, {70})))
            .property("sketchIncrement", &CadHeader::sketchIncrement, &CadHeader::setSketchIncrement)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SKETCHINC, {70})))
            .property("sketchPolylines", &CadHeader::sketchPolylines, &CadHeader::setSketchPolylines)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SKPOLY, {70})))
            .property("solidLoftedShape", &CadHeader::solidLoftedShape, &CadHeader::setSolidLoftedShape)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::LOFTPARAM, {70})))
            .property("solidsRetainHistory", &CadHeader::solidsRetainHistory, &CadHeader::setSolidsRetainHistory)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SOLIDHIST, {280})))
            .property("spatialIndexMaxTreeDepth", &CadHeader::spatialIndexMaxTreeDepth, &CadHeader::setSpatialIndexMaxTreeDepth)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TREEDEPTH, {70})))
            .property("splineType", &CadHeader::splineType, &CadHeader::setSplineType)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SPLINETYPE, {70})))
            .property("stepSize", &CadHeader::stepSize, &CadHeader::setStepSize)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::STEPSIZE, {40})))
            .property("stepsPerSecond", &CadHeader::stepsPerSecond, &CadHeader::setStepsPerSecond)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::STEPSPERSEC, {40})))
            .property("styleSheetName", &CadHeader::styleSheetName, &CadHeader::setStyleSheetName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::STYLESHEET, {1})))
            .property("surfaceDensityU", &CadHeader::surfaceDensityU, &CadHeader::setSurfaceDensityU)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SURFU, {70})))
            .property("surfaceDensityV", &CadHeader::surfaceDensityV, &CadHeader::setSurfaceDensityV)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SURFV, {70})))
            .property("surfaceMeshTabulationCount1", &CadHeader::surfaceMeshTabulationCount1, &CadHeader::setSurfaceMeshTabulationCount1)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SURFTAB1, {70})))
            .property("surfaceMeshTabulationCount2", &CadHeader::surfaceMeshTabulationCount2, &CadHeader::setSurfaceMeshTabulationCount2)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SURFTAB2, {70})))
            .property("surfaceType", &CadHeader::surfaceType, &CadHeader::setSurfaceType)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::SURFTYPE, {70})))
            .property("sweptSolidHeight", &CadHeader::sweptSolidHeight, &CadHeader::setSweptSolidHeight)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PSOLHEIGHT, {40})))
            .property("sweptSolidWidth", &CadHeader::sweptSolidWidth, &CadHeader::setSweptSolidWidth)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PSOLWIDTH, {40})))
            .property("textHeightDefault", &CadHeader::textHeightDefault, &CadHeader::setTextHeightDefault)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TEXTSIZE, {40})))
            .property("textStyleName", &CadHeader::textStyleName, &CadHeader::setTextStyleName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TEXTSTYLE, true, {7})))
            .property("thicknessDefault", &CadHeader::thicknessDefault, &CadHeader::setThicknessDefault)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::THICKNESS, {40})))
            .property("timeZone", &CadHeader::timeZone, &CadHeader::setTimeZone)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TIMEZONE, {70})))
            .property("TotalEditingTime", &CadHeader::totalEditingTime, &CadHeader::setTotalEditingTime)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TDINDWG, {40})))
            .property("traceWidthDefault", &CadHeader::traceWidthDefault, &CadHeader::setTraceWidthDefault)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TRACEWID, {40})))
            .property("ucsBaseName", &CadHeader::ucsBaseName, &CadHeader::setUcsBaseName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSBASE, true, {2})))
            .property("ucsName", &CadHeader::ucsName, &CadHeader::setUcsName)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UCSNAME, true, {2})))
            .property("unitMode", &CadHeader::unitMode, &CadHeader::setUnitMode)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::UNITMODE, {70})))
            .property("universalCreateDateTime", &CadHeader::universalCreateDateTime, &CadHeader::setUniversalCreateDateTime)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TDUCREATE, {40})))
            .property("universalUpdateDateTime", &CadHeader::universalUpdateDateTime, &CadHeader::setUniversalUpdateDateTime)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TDUUPDATE, {40})))
            .property("updateDateTime", &CadHeader::updateDateTime, &CadHeader::setUpdateDateTime)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TDUPDATE, {40})))
            .property("updateDimensionsWhileDragging", &CadHeader::updateDimensionsWhileDragging, &CadHeader::setUpdateDimensionsWhileDragging)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::DIMSHO, {40})))
            .property("userDouble1", &CadHeader::userDouble1, &CadHeader::setUserDouble1)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERR1, {40})))
            .property("userDouble2", &CadHeader::userDouble2, &CadHeader::setUserDouble2)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERR2, {40})))
            .property("userDouble3", &CadHeader::userDouble3, &CadHeader::setUserDouble3)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERR3, {40})))
            .property("userDouble4", &CadHeader::userDouble4, &CadHeader::setUserDouble4)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERR4, {40})))
            .property("userDouble5", &CadHeader::userDouble5, &CadHeader::setUserDouble5)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERR5, {40})))
            .property("userElapsedTimeSpan", &CadHeader::userElapsedTimeSpan, &CadHeader::setUserElapsedTimeSpan)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::TDUSRTIMER, {40})))
            .property("userShort1", &CadHeader::userShort1, &CadHeader::setUserShort1)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERI1, {70})))
            .property("userShort2", &CadHeader::userShort2, &CadHeader::setUserShort2)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERI2, {70})))
            .property("userShort3", &CadHeader::userShort3, &CadHeader::setUserShort3)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERI3, {70})))
            .property("userShort4", &CadHeader::userShort4, &CadHeader::setUserShort4)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERI4, {70})))
            .property("userShort5", &CadHeader::userShort5, &CadHeader::setUserShort5)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USERI5, {70})))
            .property("userTimer", &CadHeader::userTimer, &CadHeader::setUserTimer)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::USRTIMER, {70})))
            .property("versionGuid", &CadHeader::versionGuid, &CadHeader::setVersionGuid)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::VERSIONGUID, {2})))
            .property("versionString", &CadHeader::versionString, &CadHeader::setVersionString)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::ACADVER, {1})))
            .property("viewportDefaultViewScaleFactor", &CadHeader::viewportDefaultViewScaleFactor, &CadHeader::setViewportDefaultViewScaleFactor)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::PSVPSCALE, {40})))
            .property("worldView", &CadHeader::worldView, &CadHeader::setWorldView)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::WORLDVIEW, {70})))
            .property("xedit", &CadHeader::xedit, &CadHeader::setXEdit)(metadata("CadSystemVariable", CadSystemVariableAttribute(CadSystemVariables::XEDIT, {290})));
}

}// namespace dwg
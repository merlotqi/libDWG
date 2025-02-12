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

namespace dwg {

/* --------------------------- CadHeaderPrivate -------------------------- */

class CadHeaderPrivate
{
public:
    CadHeaderPrivate();
    ~CadHeaderPrivate();

    std::string _versionString;
    ACadVersion _version;
    short _maintenanceVersion;
    std::string _codePage;
    std::string _lastSavedBy;
    bool _associatedDimensions;
    bool _updateDimensionsWhileDragging;
    bool _DIMSAV;
    MeasurementUnits _measurementUnits;
    bool _polylineLineTypeGeneration;
    bool _orthoMode;
    bool _regenerationMode;
    bool _fillMode;
    bool _quickTextMode;
    SpaceLineTypeScaling _paperSpaceLineTypeScaling;
    bool _limitCheckingOn;
    bool _blipMode;
    bool _userTimer;
    bool _sketchPolylines;
    AngularDirection _angularDirection;
    bool _showSplineControlPoints;
    bool _mirrorText;
    bool _worldView;
    bool _showModelSpace;
    bool _paperSpaceLimitsChecking;
    bool _retainXRefDependentVisibilitySettings;
    bool _displaySilhouetteCurves;
    bool _createEllipseAsPolyline;
    bool _proxyGraphics;
    short _spatialIndexMaxTreeDepth;
    LinearUnitFormat _linearUnitFormat;
    short _linearUnitPrecision;
    AngularUnitFormat _angularUnit;
    short _angularUnitPrecision;
    ObjectSnapMode _objectSnapMode;
    AttributeVisibilityMode _attributeVisibility;
    short _pointDisplayMode;
    short _userShort1;
    short _userShort2;
    short _userShort3;
    short _userShort4;
    short _userShort5;
    short _numberOfSplineSegments;
    short _surfaceDensityU;
    short _surfaceDensityV;
    short _surfaceType;
    short _surfaceMeshTabulationCount1;
    short _surfaceMeshTabulationCount2;
    SplineType _splineType;
    ShadeEdgeType _shadeEdge;
    short _shadeDiffuseToAmbientPercentage;
    short _unitMode;
    short _maxViewportCount;
    short _surfaceIsolineCount;
    VerticalAlignmentType _currentMultilineJustification;
    short _textQuality;
    double _lineTypeScale;
    double _textHeightDefault;
    std::string _textStyleName;
    std::string _currentLayerName;
    std::string _currentLineTypeName;
    std::string _multiLineStyleName;
    double _traceWidthDefault;
    double _sketchIncrement;
    double _filletRadius;
    double _thicknessDefault;
    double _angleBase;
    double _pointDisplaySize;
    double _polylineWidthDefault;
    double _userDouble1;
    double _userDouble2;
    double _userDouble3;
    double _userDouble4;
    double _userDouble5;
    double _chamferDistance1;
    double _chamferDistance2;
    double _chamferLength;
    double _chamferAngle;
    double _facetResolution;
    double _currentMultilineScale;
    double _currentEntityLinetypeScale;
    std::string _menuFileName;
    unsigned long long _handleSeed;
    time_t _createDateTime;
    time_t _universalCreateDateTime;
    time_t _updateDateTime;
    time_t _universalUpdateDateTime;
    double _totalEditingTime;
    double _userElapsedTimeSpan;
    Color _currentEntityColor;
    double _viewportDefaultViewScaleFactor;
    XYZ _paperSpaceInsertionBase;
    XYZ _paperSpaceExtMin;
    XYZ _paperSpaceExtMax;
    XY _paperSpaceLimitsMin;
    XY _paperSpaceLimitsMax;
    double _paperSpaceElevation;
    std::string _paperSpaceBaseName;
    std::string _paperSpaceName;
    XYZ _paperSpaceUcsOrigin;
    XYZ _paperSpaceUcsXAxis;
    XYZ _paperSpaceUcsYAxis;
    XYZ _paperSpaceOrthographicTopDOrigin;
    XYZ _paperSpaceOrthographicBottomDOrigin;
    XYZ _paperSpaceOrthographicLeftDOrigin;
    XYZ _paperSpaceOrthographicRightDOrigin;
    XYZ _paperSpaceOrthographicFrontDOrigin;
    XYZ _paperSpaceOrthographicBackDOrigin;
    XYZ _modelSpaceOrthographicTopDOrigin;
    XYZ _modelSpaceOrthographicBottomDOrigin;
    XYZ _modelSpaceOrthographicLeftDOrigin;
    XYZ _modelSpaceOrthographicRightDOrigin;
    XYZ _modelSpaceOrthographicFrontDOrigin;
    XYZ _modelSpaceOrthographicBackDOrigin;
    XYZ _modelSpaceInsertionBase;
    XYZ _modelSpaceExtMin;
    XYZ _modelSpaceExtMax;
    XY _modelSpaceLimitsMin;
    XY _modelSpaceLimitsMax;
    std::string _ucsBaseName;
    std::string _ucsName;
    double _elevation;
    XYZ _modelSpaceOrigin;
    XYZ _modelSpaceXAxis;
    XYZ _modelSpaceYAxis;
    std::string _dimensionBlockName;
    std::string _arrowBlockName;
    std::string _dimensionBlockNameFirst;
    std::string _dimensionBlockNameSecond;
    short _stackedTextAlignment;
    short _stackedTextSizePercentage;
    std::string _hyperLinkBase;
    LineweightType _currentEntityLineWeight;
    short _endCaps;
    short _joinStyle;
    bool _displayLineWeight;
    bool _xedit;
    bool _extendedNames;
    short _plotStyleMode;
    bool _loadOLEObject;
    UnitsType _dinsUnits;
    EntityPlotStyleType _currentEntityPlotStyle;
    std::string _fingerPrintGuid;
    std::string _versionGuid;
    ObjectSortingFlags _entitySortingFlags;
    IndexCreationFlags _indexCreationFlags;
    unsigned char _hideText;
    unsigned char _externalReferenceClippingBoundaryType;
    DimensionAssociation _dimensionAssociativity;
    unsigned char _haloGapPercentage;
    Color _obscuredColor;
    Color _interfereColor;
    unsigned char _obscuredType;
    unsigned char _intersectionDisplay;
    std::string _projectName;
    bool _cameraDisplayObjects;
    double _stepsPerSecond;
    double _stepSize;
    double _dw3DPrecision;
    double _lensLength;
    double _cameraHeight;
    char _solidsRetainHistory;
    char _showSolidsHistory;
    double _sweptSolidWidth;
    double _sweptSolidHeight;
    double _draftAngleFirstCrossSection;
    double _draftAngleSecondCrossSection;
    double _draftMagnitudeFirstCrossSection;
    double _draftMagnitudeSecondCrossSection;
    short _solidLoftedShape;
    char _loftedObjectNormals;
    double _latitude;
    double _longitude;
    double _northDirection;
    int _timeZone;
    char _displayLightGlyphs;
    char _dwgUnderlayFramesVisibility;
    char _dgnUnderlayFramesVisibility;
    ShadowMode _shadowMode;
    double _shadowPlaneLocation;
    std::string _styleSheetName;
    std::string _dimensionTextStyleName;
    std::string _dimensionStyleOverridesName;
    short _dimensionAngularDimensionDecimalPlaces;
    short _dimensionDecimalPlaces;
    short _dimensionToleranceDecimalPlaces;
    bool _dimensionAlternateUnitDimensioning;
    LinearUnitFormat _dimensionAlternateUnitFormat;
    double _dimensionAlternateUnitScaleFactor;
    double _dimensionExtensionLineOffset;
    double _dimensionScaleFactor;
    short _dimensionAlternateUnitDecimalPlaces;
    short _dimensionAlternateUnitToleranceDecimalPlaces;
    AngularUnitFormat _dimensionAngularUnit;
    FractionFormat _dimensionFractionFormat;
    LinearUnitFormat _dimensionLinearUnitFormat;
    char _dimensionDecimalSeparator;
    TextMovement _dimensionTextMovement;
    DimensionTextHorizontalAlignment _dimensionTextHorizontalAlignment;
    bool _dimensionSuppressFirstDimensionLine;
    bool _dimensionSuppressSecondDimensionLine;
    bool _dimensionGenerateTolerances;
    ToleranceAlignment _dimensionToleranceAlignment;
    ZeroHandling _dimensionZeroHandling;
    ZeroHandling _dimensionToleranceZeroHandling;
    short _dimensionFit;
    ZeroHandling _dimensionAlternateUnitZeroHandling;
    ZeroHandling _dimensionAlternateUnitToleranceZeroHandling;
    bool _dimensionCursorUpdate;
    TextArrowFitType _dimensionDimensionTextArrowFit;
    double _dimensionAlternateUnitRounding;
    std::string _dimensionAlternateDimensioningSuffix;
    double _dimensionArrowSize;
    ZeroHandling _dimensionAngularZeroHandling;
    ArcLengthSymbolPosition _dimensionArcLengthSymbolPosition;
    bool _dimensionSeparateArrowBlocks;
    double _dimensionCenterMarkSize;
    double _dimensionTickSize;
    Color _dimensionLineColor;
    Color _dimensionExtensionLineColor;
    Color _dimensionTextColor;
    double _dimensionLineExtension;
    double _dimensionLineIncrement;
    double _dimensionExtensionLineExtension;
    bool _dimensionIsExtensionLineLengthFixed;
    double _dimensionFixedExtensionLineLength;
    double _dimensionJoggedRadiusDimensionTransverseSegmentAngle;
    DimensionTextBackgroundFillMode _dimensionTextBackgroundFillMode;
    Color _dimensionTextBackgroundColor;
    double _dimensionLineGap;
    double _dimensionLinearScaleFactor;
    double _dimensionTextVerticalPosition;
    LineweightType _dimensionLineWeight;
    LineweightType _extensionLineWeight;
    std::string _dimensionPostFix;
    double _dimensionRounding;
    bool _dimensionSuppressFirstExtensionLine;
    bool _dimensionSuppressSecondExtensionLine;
    bool _dimensionSuppressOutsideExtensions;
    DimensionTextVerticalAlignment _dimensionTextVerticalAlignment;
    short _dimensionUnit;
    double _dimensionToleranceScaleFactor;
    bool _dimensionTextInsideHorizontal;
    bool _dimensionTextInsideExtensions;
    double _dimensionMinusTolerance;
    bool _dimensionTextOutsideExtensions;
    bool _dimensionTextOutsideHorizontal;
    bool _dimensionLimitsGeneration;
    double _dimensionPlusTolerance;
    double _dimensionTextHeight;
    TextDirection _dimensionTextDirection;
    double _dimensionAltMzf;
    std::string _dimensionAltMzs;
    double _dimensionMzf;
    std::string _dimensionMzs;
    std::string _dimensionLineType;
    std::string _dimensionTex1;
    std::string _dimensionTex2;

    Layer *_currentLayer;
    LineType *_currentLineType;
    TextStyle *_currentTextStyle;
    TextStyle *_dimensionTextStyle;
    DimensionStyle *_dimensionStyleOverrides;
    UCS *_modelSpaceUcs;
    UCS *_modelSpaceUcsBase;
    UCS *_paperSpaceUcs;
    UCS *_paperSpaceUcsBase;
};


/* --------------------------- CadHeader impls --------------------------- */

CadHeader::CadHeader() {}

CadHeader::CadHeader(CadDocument *document) {}

CadHeader::CadHeader(ACadVersion version) {}

std::string CadHeader::versionString() const {}

void CadHeader::setVersionString(const std::string &value) {}

ACadVersion CadHeader::version() const {}

void CadHeader::setVersion(ACadVersion) {}

short CadHeader::maintenanceVersion() const {}

void CadHeader::setMaintenanceVersion(short) {}

std::string CadHeader::codePage() const {}

void CadHeader::setCodePage(const std::string &value) {}

std::string CadHeader::lastSavedBy() const {}

void CadHeader::setLastSavedBy(const std::string &value) {}

bool CadHeader::associatedDimensions() const {}

void CadHeader::setAssociatedDimensions(bool) {}

bool CadHeader::updateDimensionsWhileDragging() const {}

void CadHeader::setUpdateDimensionsWhileDragging(bool) {}

bool CadHeader::dIMSAV() const {}

void CadHeader::setDIMSAV(bool) {}

MeasurementUnits CadHeader::measurementUnits() const {}

void CadHeader::setMeasurementUnits(MeasurementUnits) {}

bool CadHeader::polylineLineTypeGeneration() const {}

void CadHeader::setPolylineLineTypeGeneration(bool) {}

bool CadHeader::orthoMode() const {}

void CadHeader::setOrthoMode(bool) {}

bool CadHeader::regenerationMode() const {}

void CadHeader::setRegenerationMode(bool) {}

bool CadHeader::fillMode() const {}

void CadHeader::setFillMode(bool) {}

bool CadHeader::quickTextMode() const {}

void CadHeader::setQuickTextMode(bool) {}

SpaceLineTypeScaling CadHeader::paperSpaceLineTypeScaling() const {}

void CadHeader::setPaperSpaceLineTypeScaling(SpaceLineTypeScaling) {}

bool CadHeader::limitCheckingOn() const {}

void CadHeader::setLimitCheckingOn(bool) {}

bool CadHeader::blipMode() const {}

void CadHeader::setBlipMode(bool) {}

bool CadHeader::userTimer() const {}

void CadHeader::setUserTimer(bool) {}

bool CadHeader::sketchPolylines() const {}

void CadHeader::setSketchPolylines(bool) {}

AngularDirection CadHeader::angularDirection() const {}

void CadHeader::setAngularDirection(AngularDirection) {}

bool CadHeader::showSplineControlPoints() const {}

void CadHeader::setShowSplineControlPoints(bool) {}

bool CadHeader::mirrorText() const {}

void CadHeader::setMirrorText(bool) {}

bool CadHeader::worldView() const {}

void CadHeader::setWorldView(bool) {}

bool CadHeader::showModelSpace() const {}

void CadHeader::setShowModelSpace(bool) {}

bool CadHeader::paperSpaceLimitsChecking() const {}

void CadHeader::setPaperSpaceLimitsChecking(bool) {}

bool CadHeader::retainXRefDependentVisibilitySettings() const {}

void CadHeader::setRetainXRefDependentVisibilitySettings(bool) {}

bool CadHeader::displaySilhouetteCurves() const {}

void CadHeader::setDisplaySilhouetteCurves(bool) {}

bool CadHeader::createEllipseAsPolyline() const {}

void CadHeader::setCreateEllipseAsPolyline(bool) {}

bool CadHeader::proxyGraphics() const {}

void CadHeader::setProxyGraphics(bool) {}

short CadHeader::spatialIndexMaxTreeDepth() const {}

void CadHeader::setSpatialIndexMaxTreeDepth(short) {}

LinearUnitFormat CadHeader::linearUnitFormat() const {}

void CadHeader::setLinearUnitFormat(LinearUnitFormat) {}

short CadHeader::linearUnitPrecision() const {}

void CadHeader::setLinearUnitPrecision(short) {}

AngularUnitFormat CadHeader::angularUnit() const {}

void CadHeader::setAngularUnit(AngularUnitFormat) {}

short CadHeader::angularUnitPrecision() const {}

void CadHeader::setAngularUnitPrecision(short) {}

ObjectSnapMode CadHeader::objectSnapMode() const {}

void CadHeader::setObjectSnapMode(ObjectSnapMode) {}

AttributeVisibilityMode CadHeader::attributeVisibility() const {}

void CadHeader::setAttributeVisibility(AttributeVisibilityMode) {}

short CadHeader::pointDisplayMode() const {}

void CadHeader::setPointDisplayMode(short) {}

short CadHeader::userShort1() const {}

void CadHeader::setUserShort1(short) {}

short CadHeader::userShort2() const {}

void CadHeader::setUserShort2(short) {}

short CadHeader::userShort3() const {}

void CadHeader::setUserShort3(short) {}

short CadHeader::userShort4() const {}

void CadHeader::setUserShort4(short) {}

short CadHeader::userShort5() const {}

void CadHeader::setUserShort5(short) {}

short CadHeader::numberOfSplineSegments() const {}

void CadHeader::setNumberOfSplineSegments(short) {}

short CadHeader::surfaceDensityU() const {}

void CadHeader::setSurfaceDensityU(short) {}

short CadHeader::surfaceDensityV() const {}

void CadHeader::setSurfaceDensityV(short) {}

short CadHeader::surfaceType() const {}

void CadHeader::setSurfaceType(short) {}

short CadHeader::surfaceMeshTabulationCount1() const {}

void CadHeader::setSurfaceMeshTabulationCount1(short) {}

short CadHeader::surfaceMeshTabulationCount2() const {}

void CadHeader::setSurfaceMeshTabulationCount2(short) {}

SplineType CadHeader::splineType() const {}

void CadHeader::setSplineType(SplineType) {}

ShadeEdgeType CadHeader::shadeEdge() const {}

void CadHeader::setShadeEdge(ShadeEdgeType) {}

short CadHeader::shadeDiffuseToAmbientPercentage() const {}

void CadHeader::setShadeDiffuseToAmbientPercentage(short) {}

short CadHeader::unitMode() const {}

void CadHeader::setUnitMode(short) {}

short CadHeader::maxViewportCount() const {}

void CadHeader::setMaxViewportCount(short) {}

short CadHeader::surfaceIsolineCount() const {}

void CadHeader::setSurfaceIsolineCount(short) {}

VerticalAlignmentType CadHeader::currentMultilineJustification() const {}

void CadHeader::setCurrentMultilineJustification(VerticalAlignmentType) {}

short CadHeader::textQuality() const {}

void CadHeader::setTextQuality(short) {}

double CadHeader::lineTypeScale() const {}

void CadHeader::setLineTypeScale(double) {}

double CadHeader::textHeightDefault() const {}

void CadHeader::setTextHeightDefault(double) {}

std::string CadHeader::textStyleName() const {}

void CadHeader::setTextStyleName(const std::string &value) {}

std::string CadHeader::currentLayerName() const {}

void CadHeader::setCurrentLayerName(const std::string &value) {}

std::string CadHeader::currentLineTypeName() const {}

void CadHeader::setCurrentLineTypeName(const std::string &value) {}

std::string CadHeader::multiLineStyleName() const {}

void CadHeader::setMultiLineStyleName(const std::string &value) {}

double CadHeader::traceWidthDefault() const {}

void CadHeader::setTraceWidthDefault(double) {}

double CadHeader::sketchIncrement() const {}

void CadHeader::setSketchIncrement(double) {}

double CadHeader::filletRadius() const {}

void CadHeader::setFilletRadius(double) {}

double CadHeader::thicknessDefault() const {}

void CadHeader::setThicknessDefault(double) {}

double CadHeader::angleBase() const {}

void CadHeader::setAngleBase(double) {}

double CadHeader::pointDisplaySize() const {}

void CadHeader::setPointDisplaySize(double) {}

double CadHeader::polylineWidthDefault() const {}

void CadHeader::setPolylineWidthDefault(double) {}

double CadHeader::userDouble1() const {}

void CadHeader::setUserDouble1(double) {}

double CadHeader::userDouble2() const {}

void CadHeader::setUserDouble2(double) {}

double CadHeader::userDouble3() const {}

void CadHeader::setUserDouble3(double) {}

double CadHeader::userDouble4() const {}

void CadHeader::setUserDouble4(double) {}

double CadHeader::userDouble5() const {}

void CadHeader::setUserDouble5(double) {}

double CadHeader::chamferDistance1() const {}

void CadHeader::setChamferDistance1(double) {}

double CadHeader::chamferDistance2() const {}

void CadHeader::setChamferDistance2(double) {}

double CadHeader::chamferLength() const {}

void CadHeader::setChamferLength(double) {}

double CadHeader::chamferAngle() const {}

void CadHeader::setChamferAngle(double) {}

double CadHeader::facetResolution() const {}

void CadHeader::setFacetResolution(double) {}

double CadHeader::currentMultilineScale() const {}

void CadHeader::setCurrentMultilineScale(double) {}

double CadHeader::currentEntityLinetypeScale() const {}

void CadHeader::setCurrentEntityLinetypeScale(double) {}

std::string CadHeader::menuFileName() const {}

void CadHeader::setMenuFileName(const std::string &value) {}

unsigned long long CadHeader::handleSeed() const {}

void CadHeader::setHandleSeed(unsigned long long) {}

time_t CadHeader::createDateTime() const {}

void CadHeader::setCreateDateTime(time_t) {}

time_t CadHeader::universalCreateDateTime() const {}

void CadHeader::setUniversalCreateDateTime(time_t) {}

time_t CadHeader::updateDateTime() const {}

void CadHeader::setUpdateDateTime(time_t) {}

time_t CadHeader::universalUpdateDateTime() const {}

void CadHeader::setUniversalUpdateDateTime(time_t) {}

double CadHeader::totalEditingTime() const {}

void CadHeader::setTotalEditingTime(double) {}

double CadHeader::userElapsedTimeSpan() const {}

void CadHeader::setUserElapsedTimeSpan(double) {}

Color CadHeader::currentEntityColor() const {}

void CadHeader::setCurrentEntityColor(const Color &) {}

double CadHeader::viewportDefaultViewScaleFactor() const {}

void CadHeader::setViewportDefaultViewScaleFactor(double) {}

XYZ CadHeader::paperSpaceInsertionBase() const {}

void CadHeader::setPaperSpaceInsertionBase(const XYZ &) {}

XYZ CadHeader::paperSpaceExtMin() const {}

void CadHeader::setPaperSpaceExtMin(const XYZ &) {}

XYZ CadHeader::paperSpaceExtMax() const {}

void CadHeader::setPaperSpaceExtMax(const XYZ &) {}

XY CadHeader::paperSpaceLimitsMin() const {}

void CadHeader::setPaperSpaceLimitsMin(const XYZ &) {}

XY CadHeader::paperSpaceLimitsMax() const {}

void CadHeader::setPaperSpaceLimitsMax(const XY &) {}

double CadHeader::paperSpaceElevation() const {}

void CadHeader::setPaperSpaceElevation(double) {}

std::string CadHeader::paperSpaceBaseName() const {}

void CadHeader::setPaperSpaceBaseName(const std::string &value) {}

std::string CadHeader::paperSpaceName() const {}

void CadHeader::setPaperSpaceName(const std::string &value) {}

XYZ CadHeader::paperSpaceUcsOrigin() const {}

void CadHeader::setPaperSpaceUcsOrigin(const XYZ &) {}

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
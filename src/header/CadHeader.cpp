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

/* --------------------------- DG_CadHeaderPrivate -------------------------- */

class DG_CadHeaderPrivate
{
public:
    DG_CadHeaderPrivate();
    ~DG_CadHeaderPrivate();

    std::string _versionString;
    DG_ACadVersion _version;
    short _maintenanceVersion;
    std::string _codePage;
    std::string _lastSavedBy;
    bool _associatedDimensions;
    bool _updateDimensionsWhileDragging;
    bool _DIMSAV;
    DG_MeasurementUnits _measurementUnits;
    bool _polylineLineTypeGeneration;
    bool _orthoMode;
    bool _regenerationMode;
    bool _fillMode;
    bool _quickTextMode;
    DG_SpaceLineTypeScaling _paperSpaceLineTypeScaling;
    bool _limitCheckingOn;
    bool _blipMode;
    bool _userTimer;
    bool _sketchPolylines;
    DG_AngularDirection _angularDirection;
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
    DG_LinearUnitFormat _linearUnitFormat;
    short _linearUnitPrecision;
    DG_AngularUnitFormat _angularUnit;
    short _angularUnitPrecision;
    DG_ObjectSnapMode _objectSnapMode;
    DG_AttributeVisibilityMode _attributeVisibility;
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
    DG_SplineType _splineType;
    DG_ShadeEdgeType _shadeEdge;
    short _shadeDiffuseToAmbientPercentage;
    short _unitMode;
    short _maxViewportCount;
    short _surfaceIsolineCount;
    DG_VerticalAlignmentType _currentMultilineJustification;
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
    DG_Color _currentEntityColor;
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
    DG_LineweightType _currentEntityLineWeight;
    short _endCaps;
    short _joinStyle;
    bool _displayLineWeight;
    bool _xedit;
    bool _extendedNames;
    short _plotStyleMode;
    bool _loadOLEObject;
    DG_UnitsType _dinsUnits;
    DG_EntityPlotStyleType _currentEntityPlotStyle;
    std::string _fingerPrintGuid;
    std::string _versionGuid;
    DG_ObjectSortingFlags _entitySortingFlags;
    DG_IndexCreationFlags _indexCreationFlags;
    unsigned char _hideText;
    unsigned char _externalReferenceClippingBoundaryType;
    DG_DimensionAssociation _dimensionAssociativity;
    unsigned char _haloGapPercentage;
    DG_Color _obscuredColor;
    DG_Color _interfereColor;
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
    DG_ShadowMode _shadowMode;
    double _shadowPlaneLocation;
    std::string _styleSheetName;
    std::string _dimensionTextStyleName;
    std::string _dimensionStyleOverridesName;
    short _dimensionAngularDimensionDecimalPlaces;
    short _dimensionDecimalPlaces;
    short _dimensionToleranceDecimalPlaces;
    bool _dimensionAlternateUnitDimensioning;
    DG_LinearUnitFormat _dimensionAlternateUnitFormat;
    double _dimensionAlternateUnitScaleFactor;
    double _dimensionExtensionLineOffset;
    double _dimensionScaleFactor;
    short _dimensionAlternateUnitDecimalPlaces;
    short _dimensionAlternateUnitToleranceDecimalPlaces;
    DG_AngularUnitFormat _dimensionAngularUnit;
    DG_FractionFormat _dimensionFractionFormat;
    DG_LinearUnitFormat _dimensionLinearUnitFormat;
    char _dimensionDecimalSeparator;
    DG_TextMovement _dimensionTextMovement;
    DG_DimensionTextHorizontalAlignment _dimensionTextHorizontalAlignment;
    bool _dimensionSuppressFirstDimensionLine;
    bool _dimensionSuppressSecondDimensionLine;
    bool _dimensionGenerateTolerances;
    DG_ToleranceAlignment _dimensionToleranceAlignment;
    DG_ZeroHandling _dimensionZeroHandling;
    DG_ZeroHandling _dimensionToleranceZeroHandling;
    short _dimensionFit;
    DG_ZeroHandling _dimensionAlternateUnitZeroHandling;
    DG_ZeroHandling _dimensionAlternateUnitToleranceZeroHandling;
    bool _dimensionCursorUpdate;
    DG_TextArrowFitType _dimensionDimensionTextArrowFit;
    double _dimensionAlternateUnitRounding;
    std::string _dimensionAlternateDimensioningSuffix;
    double _dimensionArrowSize;
    DG_ZeroHandling _dimensionAngularZeroHandling;
    DG_ArcLengthSymbolPosition _dimensionArcLengthSymbolPosition;
    bool _dimensionSeparateArrowBlocks;
    double _dimensionCenterMarkSize;
    double _dimensionTickSize;
    DG_Color _dimensionLineColor;
    DG_Color _dimensionExtensionLineColor;
    DG_Color _dimensionTextColor;
    double _dimensionLineExtension;
    double _dimensionLineIncrement;
    double _dimensionExtensionLineExtension;
    bool _dimensionIsExtensionLineLengthFixed;
    double _dimensionFixedExtensionLineLength;
    double _dimensionJoggedRadiusDimensionTransverseSegmentAngle;
    DG_DimensionTextBackgroundFillMode _dimensionTextBackgroundFillMode;
    DG_Color _dimensionTextBackgroundColor;
    double _dimensionLineGap;
    double _dimensionLinearScaleFactor;
    double _dimensionTextVerticalPosition;
    DG_LineweightType _dimensionLineWeight;
    DG_LineweightType _extensionLineWeight;
    std::string _dimensionPostFix;
    double _dimensionRounding;
    bool _dimensionSuppressFirstExtensionLine;
    bool _dimensionSuppressSecondExtensionLine;
    bool _dimensionSuppressOutsideExtensions;
    DG_DimensionTextVerticalAlignment _dimensionTextVerticalAlignment;
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
    DG_TextDirection _dimensionTextDirection;
    double _dimensionAltMzf;
    std::string _dimensionAltMzs;
    double _dimensionMzf;
    std::string _dimensionMzs;
    std::string _dimensionLineType;
    std::string _dimensionTex1;
    std::string _dimensionTex2;

    DG_Layer *_currentLayer;
    DG_LineType *_currentLineType;
    DG_TextStyle *_currentTextStyle;
    DG_TextStyle *_dimensionTextStyle;
    DG_DimensionStyle *_dimensionStyleOverrides;
    DG_UCS *_modelSpaceUcs;
    DG_UCS *_modelSpaceUcsBase;
    DG_UCS *_paperSpaceUcs;
    DG_UCS *_paperSpaceUcsBase;
};


/* --------------------------- DG_CadHeader impls --------------------------- */

DG_CadHeader::DG_CadHeader() {}

DG_CadHeader::DG_CadHeader(DG_CadDocument *document) {}

DG_CadHeader::DG_CadHeader(DG_ACadVersion version) {}

std::string DG_CadHeader::VersionString() const {}

void DG_CadHeader::VersionString(const std::string &value) {}

DG_ACadVersion DG_CadHeader::Version() const {}

void DG_CadHeader::Version(DG_ACadVersion) {}

short DG_CadHeader::MaintenanceVersion() const {}

void DG_CadHeader::MaintenanceVersion(short) {}

std::string DG_CadHeader::CodePage() const {}

void DG_CadHeader::CodePage(const std::string &value) {}

std::string DG_CadHeader::LastSavedBy() const {}

void DG_CadHeader::LastSavedBy(const std::string &value) {}

bool DG_CadHeader::AssociatedDimensions() const {}

void DG_CadHeader::AssociatedDimensions(bool) {}

bool DG_CadHeader::UpdateDimensionsWhileDragging() const {}

void DG_CadHeader::UpdateDimensionsWhileDragging(bool) {}

bool DG_CadHeader::DIMSAV() const {}

void DG_CadHeader::DIMSAV(bool) {}

DG_MeasurementUnits DG_CadHeader::MeasurementUnits() const {}

void DG_CadHeader::MeasurementUnits(DG_MeasurementUnits) {}

bool DG_CadHeader::PolylineLineTypeGeneration() const {}

void DG_CadHeader::PolylineLineTypeGeneration(bool) {}

bool DG_CadHeader::OrthoMode() const {}

void DG_CadHeader::OrthoMode(bool) {}

bool DG_CadHeader::RegenerationMode() const {}

void DG_CadHeader::RegenerationMode(bool) {}

bool DG_CadHeader::FillMode() const {}

void DG_CadHeader::FillMode(bool) {}

bool DG_CadHeader::QuickTextMode() const {}

void DG_CadHeader::QuickTextMode(bool) {}

DG_SpaceLineTypeScaling DG_CadHeader::PaperSpaceLineTypeScaling() const {}

void DG_CadHeader::PaperSpaceLineTypeScaling(DG_SpaceLineTypeScaling) {}

bool DG_CadHeader::LimitCheckingOn() const {}

void DG_CadHeader::LimitCheckingOn(bool) {}

bool DG_CadHeader::BlipMode() const {}

void DG_CadHeader::BlipMode(bool) {}

bool DG_CadHeader::UserTimer() const {}

void DG_CadHeader::UserTimer(bool) {}

bool DG_CadHeader::SketchPolylines() const {}

void DG_CadHeader::SketchPolylines(bool) {}

DG_AngularDirection DG_CadHeader::AngularDirection() const {}

void DG_CadHeader::AngularDirection(DG_AngularDirection) {}

bool DG_CadHeader::ShowSplineControlPoints() const {}

void DG_CadHeader::ShowSplineControlPoints(bool) {}

bool DG_CadHeader::MirrorText() const {}

void DG_CadHeader::MirrorText(bool) {}

bool DG_CadHeader::WorldView() const {}

void DG_CadHeader::WorldView(bool) {}

bool DG_CadHeader::ShowModelSpace() const {}

void DG_CadHeader::ShowModelSpace(bool) {}

bool DG_CadHeader::PaperSpaceLimitsChecking() const {}

void DG_CadHeader::PaperSpaceLimitsChecking(bool) {}

bool DG_CadHeader::RetainXRefDependentVisibilitySettings() const {}

void DG_CadHeader::RetainXRefDependentVisibilitySettings(bool) {}

bool DG_CadHeader::DisplaySilhouetteCurves() const {}

void DG_CadHeader::DisplaySilhouetteCurves(bool) {}

bool DG_CadHeader::CreateEllipseAsPolyline() const {}

void DG_CadHeader::CreateEllipseAsPolyline(bool) {}

bool DG_CadHeader::ProxyGraphics() const {}

void DG_CadHeader::ProxyGraphics(bool) {}

short DG_CadHeader::SpatialIndexMaxTreeDepth() const {}

void DG_CadHeader::SpatialIndexMaxTreeDepth(short) {}

DG_LinearUnitFormat DG_CadHeader::LinearUnitFormat() const {}

void DG_CadHeader::LinearUnitFormat(DG_LinearUnitFormat) {}

short DG_CadHeader::LinearUnitPrecision() const {}

void DG_CadHeader::LinearUnitPrecision(short) {}

DG_AngularUnitFormat DG_CadHeader::AngularUnit() const {}

void DG_CadHeader::AngularUnit(DG_AngularUnitFormat) {}

short DG_CadHeader::AngularUnitPrecision() const {}

void DG_CadHeader::AngularUnitPrecision(short) {}

DG_ObjectSnapMode DG_CadHeader::ObjectSnapMode() const {}

void DG_CadHeader::ObjectSnapMode(DG_ObjectSnapMode) {}

DG_AttributeVisibilityMode DG_CadHeader::AttributeVisibility() const {}

void DG_CadHeader::AttributeVisibility(DG_AttributeVisibilityMode) {}

short DG_CadHeader::PointDisplayMode() const {}

void DG_CadHeader::PointDisplayMode(short) {}

short DG_CadHeader::UserShort1() const {}

void DG_CadHeader::UserShort1(short) {}

short DG_CadHeader::UserShort2() const {}

void DG_CadHeader::UserShort2(short) {}

short DG_CadHeader::UserShort3() const {}

void DG_CadHeader::UserShort3(short) {}

short DG_CadHeader::UserShort4() const {}

void DG_CadHeader::UserShort4(short) {}

short DG_CadHeader::UserShort5() const {}

void DG_CadHeader::UserShort5(short) {}

short DG_CadHeader::NumberOfSplineSegments() const {}

void DG_CadHeader::NumberOfSplineSegments(short) {}

short DG_CadHeader::SurfaceDensityU() const {}

void DG_CadHeader::SurfaceDensityU(short) {}

short DG_CadHeader::SurfaceDensityV() const {}

void DG_CadHeader::SurfaceDensityV(short) {}

short DG_CadHeader::SurfaceType() const {}

void DG_CadHeader::SurfaceType(short) {}

short DG_CadHeader::SurfaceMeshTabulationCount1() const {}

void DG_CadHeader::SurfaceMeshTabulationCount1(short) {}

short DG_CadHeader::SurfaceMeshTabulationCount2() const {}

void DG_CadHeader::SurfaceMeshTabulationCount2(short) {}

DG_SplineType DG_CadHeader::SplineType() const {}

void DG_CadHeader::SplineType(DG_SplineType) {}

DG_ShadeEdgeType DG_CadHeader::ShadeEdge() const {}

void DG_CadHeader::ShadeEdge(DG_ShadeEdgeType) {}

short DG_CadHeader::ShadeDiffuseToAmbientPercentage() const {}

void DG_CadHeader::ShadeDiffuseToAmbientPercentage(short) {}

short DG_CadHeader::UnitMode() const {}

void DG_CadHeader::UnitMode(short) {}

short DG_CadHeader::MaxViewportCount() const {}

void DG_CadHeader::MaxViewportCount(short) {}

short DG_CadHeader::SurfaceIsolineCount() const {}

void DG_CadHeader::SurfaceIsolineCount(short) {}

DG_VerticalAlignmentType DG_CadHeader::CurrentMultilineJustification() const {}

void DG_CadHeader::CurrentMultilineJustification(DG_VerticalAlignmentType) {}

short DG_CadHeader::TextQuality() const {}

void DG_CadHeader::TextQuality(short) {}

double DG_CadHeader::LineTypeScale() const {}

void DG_CadHeader::LineTypeScale(double) {}

double DG_CadHeader::TextHeightDefault() const {}

void DG_CadHeader::TextHeightDefault(double) {}

std::string DG_CadHeader::TextStyleName() const {}

void DG_CadHeader::TextStyleName(const std::string &value) {}

std::string DG_CadHeader::CurrentLayerName() const {}

void DG_CadHeader::CurrentLayerName(const std::string &value) {}

std::string DG_CadHeader::CurrentLineTypeName() const {}

void DG_CadHeader::CurrentLineTypeName(const std::string &value) {}

std::string DG_CadHeader::MultiLineStyleName() const {}

void DG_CadHeader::MultiLineStyleName(const std::string &value) {}

double DG_CadHeader::TraceWidthDefault() const {}

void DG_CadHeader::TraceWidthDefault(double) {}

double DG_CadHeader::SketchIncrement() const {}

void DG_CadHeader::SketchIncrement(double) {}

double DG_CadHeader::FilletRadius() const {}

void DG_CadHeader::FilletRadius(double) {}

double DG_CadHeader::ThicknessDefault() const {}

void DG_CadHeader::ThicknessDefault(double) {}

double DG_CadHeader::AngleBase() const {}

void DG_CadHeader::AngleBase(double) {}

double DG_CadHeader::PointDisplaySize() const {}

void DG_CadHeader::PointDisplaySize(double) {}

double DG_CadHeader::PolylineWidthDefault() const {}

void DG_CadHeader::PolylineWidthDefault(double) {}

double DG_CadHeader::UserDouble1() const {}

void DG_CadHeader::UserDouble1(double) {}

double DG_CadHeader::UserDouble2() const {}

void DG_CadHeader::UserDouble2(double) {}

double DG_CadHeader::UserDouble3() const {}

void DG_CadHeader::UserDouble3(double) {}

double DG_CadHeader::UserDouble4() const {}

void DG_CadHeader::UserDouble4(double) {}

double DG_CadHeader::UserDouble5() const {}

void DG_CadHeader::UserDouble5(double) {}

double DG_CadHeader::ChamferDistance1() const {}

void DG_CadHeader::ChamferDistance1(double) {}

double DG_CadHeader::ChamferDistance2() const {}

void DG_CadHeader::ChamferDistance2(double) {}

double DG_CadHeader::ChamferLength() const {}

void DG_CadHeader::ChamferLength(double) {}

double DG_CadHeader::ChamferAngle() const {}

void DG_CadHeader::ChamferAngle(double) {}

double DG_CadHeader::FacetResolution() const {}

void DG_CadHeader::FacetResolution(double) {}

double DG_CadHeader::CurrentMultilineScale() const {}

void DG_CadHeader::CurrentMultilineScale(double) {}

double DG_CadHeader::CurrentEntityLinetypeScale() const {}

void DG_CadHeader::CurrentEntityLinetypeScale(double) {}

std::string DG_CadHeader::MenuFileName() const {}

void DG_CadHeader::MenuFileName(const std::string &value) {}

unsigned long long DG_CadHeader::HandleSeed() const {}

void DG_CadHeader::HandleSeed(unsigned long long) {}

time_t DG_CadHeader::CreateDateTime() const {}

void DG_CadHeader::CreateDateTime(time_t) {}

time_t DG_CadHeader::UniversalCreateDateTime() const {}

void DG_CadHeader::UniversalCreateDateTime(time_t) {}

time_t DG_CadHeader::UpdateDateTime() const {}

void DG_CadHeader::UpdateDateTime(time_t) {}

time_t DG_CadHeader::UniversalUpdateDateTime() const {}

void DG_CadHeader::UniversalUpdateDateTime(time_t) {}

double DG_CadHeader::TotalEditingTime() const {}

void DG_CadHeader::TotalEditingTime(double) {}

double DG_CadHeader::UserElapsedTimeSpan() const {}

void DG_CadHeader::UserElapsedTimeSpan(double) {}

DG_Color DG_CadHeader::CurrentEntityColor() const {}

void DG_CadHeader::CurrentEntityColor(const DG_Color &) {}

double DG_CadHeader::ViewportDefaultViewScaleFactor() const {}

void DG_CadHeader::ViewportDefaultViewScaleFactor(double) {}

XYZ DG_CadHeader::PaperSpaceInsertionBase() const {}

void DG_CadHeader::PaperSpaceInsertionBase(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceExtMin() const {}

void DG_CadHeader::PaperSpaceExtMin(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceExtMax() const {}

void DG_CadHeader::PaperSpaceExtMax(const XYZ &) {}

XY DG_CadHeader::PaperSpaceLimitsMin() const {}

void DG_CadHeader::PaperSpaceLimitsMin(const XYZ &) {}

XY DG_CadHeader::PaperSpaceLimitsMax() const {}

void DG_CadHeader::PaperSpaceLimitsMax(const XY &) {}

double DG_CadHeader::PaperSpaceElevation() const {}

void DG_CadHeader::PaperSpaceElevation(double) {}

std::string DG_CadHeader::PaperSpaceBaseName() const {}

void DG_CadHeader::PaperSpaceBaseName(const std::string &value) {}

std::string DG_CadHeader::PaperSpaceName() const {}

void DG_CadHeader::PaperSpaceName(const std::string &value) {}

XYZ DG_CadHeader::PaperSpaceUcsOrigin() const {}

void DG_CadHeader::PaperSpaceUcsOrigin(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceUcsXAxis() const {}

void DG_CadHeader::PaperSpaceUcsXAxis(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceUcsYAxis() const {}

void DG_CadHeader::PaperSpaceUcsYAxis(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceOrthographicTopDOrigin() const {}

void DG_CadHeader::PaperSpaceOrthographicTopDOrigin(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceOrthographicBottomDOrigin() const {}

void DG_CadHeader::PaperSpaceOrthographicBottomDOrigin(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceOrthographicLeftDOrigin() const {}

void DG_CadHeader::PaperSpaceOrthographicLeftDOrigin(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceOrthographicRightDOrigin() const {}

void DG_CadHeader::PaperSpaceOrthographicRightDOrigin(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceOrthographicFrontDOrigin() const {}

void DG_CadHeader::PaperSpaceOrthographicFrontDOrigin(const XYZ &) {}

XYZ DG_CadHeader::PaperSpaceOrthographicBackDOrigin() const {}

void DG_CadHeader::PaperSpaceOrthographicBackDOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceOrthographicTopDOrigin() const {}

void DG_CadHeader::ModelSpaceOrthographicTopDOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceOrthographicBottomDOrigin() const {}

void DG_CadHeader::ModelSpaceOrthographicBottomDOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceOrthographicLeftDOrigin() const {}

void DG_CadHeader::ModelSpaceOrthographicLeftDOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceOrthographicRightDOrigin() const {}

void DG_CadHeader::ModelSpaceOrthographicRightDOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceOrthographicFrontDOrigin() const {}

void DG_CadHeader::ModelSpaceOrthographicFrontDOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceOrthographicBackDOrigin() const {}

void DG_CadHeader::ModelSpaceOrthographicBackDOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceInsertionBase() const {}

void DG_CadHeader::ModelSpaceInsertionBase(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceExtMin() const {}

void DG_CadHeader::ModelSpaceExtMin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceExtMax() const {}

void DG_CadHeader::ModelSpaceExtMax(const XYZ &) {}

XY DG_CadHeader::ModelSpaceLimitsMin() const {}

void DG_CadHeader::ModelSpaceLimitsMin(const XY &) {}

XY DG_CadHeader::ModelSpaceLimitsMax() const {}

void DG_CadHeader::ModelSpaceLimitsMax(const XY &) {}

std::string DG_CadHeader::UcsBaseName() const {}

void DG_CadHeader::UcsBaseName(const std::string &value) {}

std::string DG_CadHeader::UcsName() const {}

void DG_CadHeader::UcsName(const std::string &value) {}

double DG_CadHeader::Elevation() const {}

void DG_CadHeader::Elevation(double) {}

XYZ DG_CadHeader::ModelSpaceOrigin() const {}

void DG_CadHeader::ModelSpaceOrigin(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceXAxis() const {}

void DG_CadHeader::ModelSpaceXAxis(const XYZ &) {}

XYZ DG_CadHeader::ModelSpaceYAxis() const {}

void DG_CadHeader::ModelSpaceYAxis(const XYZ &) {}

std::string DG_CadHeader::DimensionBlockName() const {}

void DG_CadHeader::DimensionBlockName(const std::string &value) {}

std::string DG_CadHeader::ArrowBlockName() const {}

void DG_CadHeader::ArrowBlockName(const std::string &value) {}

std::string DG_CadHeader::DimensionBlockNameFirst() const {}

void DG_CadHeader::DimensionBlockNameFirst(const std::string &value) {}

std::string DG_CadHeader::DimensionBlockNameSecond() const {}

void DG_CadHeader::DimensionBlockNameSecond(const std::string &value) {}

short DG_CadHeader::StackedTextAlignment() const {}

void DG_CadHeader::StackedTextAlignment(short) {}

short DG_CadHeader::StackedTextSizePercentage() const {}

void DG_CadHeader::StackedTextSizePercentage(short) {}

std::string DG_CadHeader::HyperLinkBase() const {}

void DG_CadHeader::HyperLinkBase(const std::string &value) {}

DG_LineweightType DG_CadHeader::CurrentEntityLineWeight() const {}

void DG_CadHeader::CurrentEntityLineWeight(DG_LineweightType) {}

short DG_CadHeader::EndCaps() const {}

void DG_CadHeader::EndCaps(short) {}

short DG_CadHeader::JoinStyle() const {}

void DG_CadHeader::JoinStyle(short) {}

bool DG_CadHeader::DisplayLineWeight() const {}

void DG_CadHeader::DisplayLineWeight(bool) {}

bool DG_CadHeader::XEdit() const {}

void DG_CadHeader::XEdit(bool) {}

bool DG_CadHeader::ExtendedNames() const {}

void DG_CadHeader::ExtendedNames(bool) {}

short DG_CadHeader::PlotStyleMode() const {}

void DG_CadHeader::PlotStyleMode(short) {}

bool DG_CadHeader::LoadOLEObject() const {}

void DG_CadHeader::LoadOLEObject(bool) {}

DG_UnitsType DG_CadHeader::InsUnits() const {}

void DG_CadHeader::InsUnits(DG_UnitsType) {}

DG_EntityPlotStyleType DG_CadHeader::CurrentEntityPlotStyle() const {}

void DG_CadHeader::CurrentEntityPlotStyle(DG_EntityPlotStyleType) {}

std::string DG_CadHeader::FingerPrintGuid() const {}

void DG_CadHeader::FingerPrintGuid(const std::string &value) {}

std::string DG_CadHeader::VersionGuid() const {}

void DG_CadHeader::VersionGuid(const std::string &value) {}

DG_ObjectSortingFlags DG_CadHeader::EntitySortingFlags() const {}

void DG_CadHeader::EntitySortingFlags(DG_ObjectSortingFlags) {}

DG_IndexCreationFlags DG_CadHeader::IndexCreationFlags() const {}

void DG_CadHeader::IndexCreationFlags(DG_IndexCreationFlags) {}

unsigned char DG_CadHeader::HideText() const {}

void DG_CadHeader::HideText(unsigned char) {}

unsigned char DG_CadHeader::ExternalReferenceClippingBoundaryType() const {}

void DG_CadHeader::ExternalReferenceClippingBoundaryType(unsigned char) {}

DG_DimensionAssociation DG_CadHeader::DimensionAssociativity() const {}

void DG_CadHeader::DimensionAssociativity(DG_DimensionAssociation) {}

unsigned char DG_CadHeader::HaloGapPercentage() const {}

void DG_CadHeader::HaloGapPercentage(unsigned char) {}

DG_Color DG_CadHeader::ObscuredColor() const {}

void DG_CadHeader::ObscuredColor(const DG_Color &) {}

DG_Color DG_CadHeader::InterfereColor() const {}

void DG_CadHeader::InterfereColor(const DG_Color &) {}

unsigned char DG_CadHeader::ObscuredType() const {}

void DG_CadHeader::ObscuredType(unsigned char) {}

unsigned char DG_CadHeader::IntersectionDisplay() const {}

void DG_CadHeader::IntersectionDisplay(unsigned char) {}

std::string DG_CadHeader::ProjectName() const {}

void DG_CadHeader::ProjectName(const std::string &value) {}

bool DG_CadHeader::CameraDisplayObjects() const {}

void DG_CadHeader::CameraDisplayObjects(bool) {}

double DG_CadHeader::StepsPerSecond() const {}

void DG_CadHeader::StepsPerSecond(double) {}

double DG_CadHeader::StepSize() const {}

void DG_CadHeader::StepSize(double) {}

double DG_CadHeader::Dw3DPrecision() const {}

void DG_CadHeader::Dw3DPrecision(double) {}

double DG_CadHeader::LensLength() const {}

void DG_CadHeader::LensLength(double) {}

double DG_CadHeader::CameraHeight() const {}

void DG_CadHeader::CameraHeight(double) {}

char DG_CadHeader::SolidsRetainHistory() const {}

void DG_CadHeader::SolidsRetainHistory(char) {}

char DG_CadHeader::ShowSolidsHistory() const {}

void DG_CadHeader::ShowSolidsHistory(char) {}

double DG_CadHeader::SweptSolidWidth() const {}

void DG_CadHeader::SweptSolidWidth(double) {}

double DG_CadHeader::SweptSolidHeight() const {}

void DG_CadHeader::SweptSolidHeight(double) {}

double DG_CadHeader::DraftAngleFirstCrossSection() const {}

void DG_CadHeader::DraftAngleFirstCrossSection(double) {}

double DG_CadHeader::DraftAngleSecondCrossSection() const {}

void DG_CadHeader::DraftAngleSecondCrossSection(double) {}

double DG_CadHeader::DraftMagnitudeFirstCrossSection() const {}

void DG_CadHeader::DraftMagnitudeFirstCrossSection(double) {}

double DG_CadHeader::DraftMagnitudeSecondCrossSection() const {}

void DG_CadHeader::DraftMagnitudeSecondCrossSection(double) {}

short DG_CadHeader::SolidLoftedShape() const {}

void DG_CadHeader::SolidLoftedShape(short) {}

char DG_CadHeader::LoftedObjectNormals() const {}

void DG_CadHeader::LoftedObjectNormals(char) {}

double DG_CadHeader::Latitude() const {}

void DG_CadHeader::Latitude(double) {}

double DG_CadHeader::Longitude() const {}

void DG_CadHeader::Longitude(double) {}

double DG_CadHeader::NorthDirection() const {}

void DG_CadHeader::NorthDirection(double) {}

int DG_CadHeader::TimeZone() const {}

void DG_CadHeader::TimeZone(int) {}

char DG_CadHeader::DisplayLightGlyphs() const {}

void DG_CadHeader::DisplayLightGlyphs(char) {}

char DG_CadHeader::DwgUnderlayFramesVisibility() const {}

void DG_CadHeader::DwgUnderlayFramesVisibility(char) {}

char DG_CadHeader::DgnUnderlayFramesVisibility() const {}

void DG_CadHeader::DgnUnderlayFramesVisibility(char) {}

DG_ShadowMode DG_CadHeader::ShadowMode() const {}

void DG_CadHeader::ShadowMode(DG_ShadowMode) {}

double DG_CadHeader::ShadowPlaneLocation() const {}

void DG_CadHeader::ShadowPlaneLocation(double) {}

std::string DG_CadHeader::StyleSheetName() const {}

void DG_CadHeader::StyleSheetName(const std::string &value) {}

std::string DG_CadHeader::DimensionTextStyleName() const {}

void DG_CadHeader::DimensionTextStyleName(const std::string &value) {}

std::string DG_CadHeader::DimensionStyleOverridesName() const {}

void DG_CadHeader::DimensionStyleOverridesName(const std::string &value) {}

short DG_CadHeader::DimensionAngularDimensionDecimalPlaces() const {}

void DG_CadHeader::DimensionAngularDimensionDecimalPlaces(short) {}

short DG_CadHeader::DimensionDecimalPlaces() const {}

void DG_CadHeader::DimensionDecimalPlaces(short) {}

short DG_CadHeader::DimensionToleranceDecimalPlaces() const {}

void DG_CadHeader::DimensionToleranceDecimalPlaces(short) {}

bool DG_CadHeader::DimensionAlternateUnitDimensioning() const {}

void DG_CadHeader::DimensionAlternateUnitDimensioning(bool) {}

DG_LinearUnitFormat DG_CadHeader::DimensionAlternateUnitFormat() const {}

void DG_CadHeader::DimensionAlternateUnitFormat(DG_LinearUnitFormat) {}

double DG_CadHeader::DimensionAlternateUnitScaleFactor() const {}

void DG_CadHeader::DimensionAlternateUnitScaleFactor(double) {}

double DG_CadHeader::DimensionExtensionLineOffset() const {}

void DG_CadHeader::DimensionExtensionLineOffset(double) {}

double DG_CadHeader::DimensionScaleFactor() const {}

void DG_CadHeader::DimensionScaleFactor(double) {}

short DG_CadHeader::DimensionAlternateUnitDecimalPlaces() const {}

void DG_CadHeader::DimensionAlternateUnitDecimalPlaces(short) {}

short DG_CadHeader::DimensionAlternateUnitToleranceDecimalPlaces() const {}

void DG_CadHeader::DimensionAlternateUnitToleranceDecimalPlaces(short) {}

DG_AngularUnitFormat DG_CadHeader::DimensionAngularUnit() const {}

void DG_CadHeader::DimensionAngularUnit(DG_AngularUnitFormat) {}

DG_FractionFormat DG_CadHeader::DimensionFractionFormat() const {}

void DG_CadHeader::DimensionFractionFormat(DG_FractionFormat) {}

DG_LinearUnitFormat DG_CadHeader::DimensionLinearUnitFormat() const {}

void DG_CadHeader::DimensionLinearUnitFormat(DG_LinearUnitFormat) {}

char DG_CadHeader::DimensionDecimalSeparator() const {}

void DG_CadHeader::DimensionDecimalSeparator(char) {}

DG_TextMovement DG_CadHeader::DimensionTextMovement() const {}

void DG_CadHeader::DimensionTextMovement(DG_TextMovement) {}

DG_DimensionTextHorizontalAlignment DG_CadHeader::DimensionTextHorizontalAlignment() const {}

void DG_CadHeader::DimensionTextHorizontalAlignment(DG_DimensionTextHorizontalAlignment) {}

bool DG_CadHeader::DimensionSuppressFirstDimensionLine() const {}

void DG_CadHeader::DimensionSuppressFirstDimensionLine(bool) {}

bool DG_CadHeader::DimensionSuppressSecondDimensionLine() const {}

void DG_CadHeader::DimensionSuppressSecondDimensionLine(bool) {}

bool DG_CadHeader::DimensionGenerateTolerances() const {}

void DG_CadHeader::DimensionGenerateTolerances(bool) {}

DG_ToleranceAlignment DG_CadHeader::DimensionToleranceAlignment() const {}

void DG_CadHeader::DimensionToleranceAlignment(DG_ToleranceAlignment) {}

DG_ZeroHandling DG_CadHeader::DimensionZeroHandling() const {}

void DG_CadHeader::DimensionZeroHandling(DG_ZeroHandling) {}

DG_ZeroHandling DG_CadHeader::DimensionToleranceZeroHandling() const {}

void DG_CadHeader::DimensionToleranceZeroHandling(DG_ZeroHandling) {}

short DG_CadHeader::DimensionFit() const {}

void DG_CadHeader::DimensionFit(short) {}

DG_ZeroHandling DG_CadHeader::DimensionAlternateUnitZeroHandling() const {}

void DG_CadHeader::DimensionAlternateUnitZeroHandling(DG_ZeroHandling) {}

DG_ZeroHandling DG_CadHeader::DimensionAlternateUnitToleranceZeroHandling() const {}

void DG_CadHeader::DimensionAlternateUnitToleranceZeroHandling(DG_ZeroHandling) {}

bool DG_CadHeader::DimensionCursorUpdate() const {}

void DG_CadHeader::DimensionCursorUpdate(bool) {}

DG_TextArrowFitType DG_CadHeader::DimensionDimensionTextArrowFit() const {}

void DG_CadHeader::DimensionDimensionTextArrowFit(DG_TextArrowFitType) {}

double DG_CadHeader::DimensionAlternateUnitRounding() const {}

void DG_CadHeader::DimensionAlternateUnitRounding(double) {}

std::string DG_CadHeader::DimensionAlternateDimensioningSuffix() const {}

void DG_CadHeader::DimensionAlternateDimensioningSuffix(const std::string &value) {}

double DG_CadHeader::DimensionArrowSize() const {}

void DG_CadHeader::DimensionArrowSize(double) {}

DG_ZeroHandling DG_CadHeader::DimensionAngularZeroHandling() const {}

void DG_CadHeader::DimensionAngularZeroHandling(DG_ZeroHandling) {}

DG_ArcLengthSymbolPosition DG_CadHeader::DimensionArcLengthSymbolPosition() const {}

void DG_CadHeader::DimensionArcLengthSymbolPosition(DG_ArcLengthSymbolPosition) {}

bool DG_CadHeader::DimensionSeparateArrowBlocks() const {}

void DG_CadHeader::DimensionSeparateArrowBlocks(bool) {}

double DG_CadHeader::DimensionCenterMarkSize() const {}

void DG_CadHeader::DimensionCenterMarkSize(double) {}

double DG_CadHeader::DimensionTickSize() const {}

void DG_CadHeader::DimensionTickSize(double) {}

DG_Color DG_CadHeader::DimensionLineColor() const {}

void DG_CadHeader::DimensionLineColor(const DG_Color &) {}

DG_Color DG_CadHeader::DimensionExtensionLineColor() const {}

void DG_CadHeader::DimensionExtensionLineColor(const DG_Color &) {}

DG_Color DG_CadHeader::DimensionTextColor() const {}

void DG_CadHeader::DimensionTextColor(const DG_Color &) {}

double DG_CadHeader::DimensionLineExtension() const {}

void DG_CadHeader::DimensionLineExtension(double) {}

double DG_CadHeader::DimensionLineIncrement() const {}

void DG_CadHeader::DimensionLineIncrement(double) {}

double DG_CadHeader::DimensionExtensionLineExtension() const {}

void DG_CadHeader::DimensionExtensionLineExtension(double) {}

bool DG_CadHeader::DimensionIsExtensionLineLengthFixed() const {}

void DG_CadHeader::DimensionIsExtensionLineLengthFixed(bool) {}

double DG_CadHeader::DimensionFixedExtensionLineLength() const {}

void DG_CadHeader::DimensionFixedExtensionLineLength(double) {}

double DG_CadHeader::DimensionJoggedRadiusDimensionTransverseSegmentAngle() const {}

void DG_CadHeader::DimensionJoggedRadiusDimensionTransverseSegmentAngle(double) {}

DG_DimensionTextBackgroundFillMode DG_CadHeader::DimensionTextBackgroundFillMode() const {}

void DG_CadHeader::DimensionTextBackgroundFillMode(DG_DimensionTextBackgroundFillMode) {}

DG_Color DG_CadHeader::DimensionTextBackgroundColor() const {}

void DG_CadHeader::DimensionTextBackgroundColor(const DG_Color &) {}

double DG_CadHeader::DimensionLineGap() const {}

void DG_CadHeader::DimensionLineGap(double) {}

double DG_CadHeader::DimensionLinearScaleFactor() const {}

void DG_CadHeader::DimensionLinearScaleFactor(double) {}

double DG_CadHeader::DimensionTextVerticalPosition() const {}

void DG_CadHeader::DimensionTextVerticalPosition(double) {}

DG_LineweightType DG_CadHeader::DimensionLineWeight() const {}

void DG_CadHeader::DimensionLineWeight(DG_LineweightType) {}

DG_LineweightType DG_CadHeader::ExtensionLineWeight() const {}

void DG_CadHeader::ExtensionLineWeight(DG_LineweightType) {}

std::string DG_CadHeader::DimensionPostFix() const {}

void DG_CadHeader::DimensionPostFix(const std::string &value) {}

double DG_CadHeader::DimensionRounding() const {}

void DG_CadHeader::DimensionRounding(double) {}

bool DG_CadHeader::DimensionSuppressFirstExtensionLine() const {}

void DG_CadHeader::DimensionSuppressFirstExtensionLine(bool) {}

bool DG_CadHeader::DimensionSuppressSecondExtensionLine() const {}

void DG_CadHeader::DimensionSuppressSecondExtensionLine(bool) {}

bool DG_CadHeader::DimensionSuppressOutsideExtensions() const {}

void DG_CadHeader::DimensionSuppressOutsideExtensions(bool) {}

DG_DimensionTextVerticalAlignment DG_CadHeader::DimensionTextVerticalAlignment() const {}

void DG_CadHeader::DimensionTextVerticalAlignment(DG_DimensionTextVerticalAlignment) {}

short DG_CadHeader::DimensionUnit() const {}

void DG_CadHeader::DimensionUnit(short) {}

double DG_CadHeader::DimensionToleranceScaleFactor() const {}

void DG_CadHeader::DimensionToleranceScaleFactor(double) {}

bool DG_CadHeader::DimensionTextInsideHorizontal() const {}

void DG_CadHeader::DimensionTextInsideHorizontal(bool) {}

bool DG_CadHeader::DimensionTextInsideExtensions() const {}

void DG_CadHeader::DimensionTextInsideExtensions(bool) {}

double DG_CadHeader::DimensionMinusTolerance() const {}

void DG_CadHeader::DimensionMinusTolerance(double) {}

bool DG_CadHeader::DimensionTextOutsideExtensions() const {}

void DG_CadHeader::DimensionTextOutsideExtensions(bool) {}

bool DG_CadHeader::DimensionTextOutsideHorizontal() const {}

void DG_CadHeader::DimensionTextOutsideHorizontal(bool) {}

bool DG_CadHeader::DimensionLimitsGeneration() const {}

void DG_CadHeader::DimensionLimitsGeneration() {}

double DG_CadHeader::DimensionPlusTolerance() const {}

void DG_CadHeader::DimensionPlusTolerance(double) {}

double DG_CadHeader::DimensionTextHeight() const {}

void DG_CadHeader::DimensionTextHeight(double) {}

DG_TextDirection DG_CadHeader::DimensionTextDirection() const {}

void DG_CadHeader::DimensionTextDirection(DG_TextDirection) {}

double DG_CadHeader::DimensionAltMzf() const {}

void DG_CadHeader::DimensionAltMzf(double) {}

std::string DG_CadHeader::DimensionAltMzs() const {}

void DG_CadHeader::DimensionAltMzs(const std::string &value) {}

double DG_CadHeader::DimensionMzf() const {}

void DG_CadHeader::DimensionMzf(double) {}

std::string DG_CadHeader::DimensionMzs() const {}

void DG_CadHeader::DimensionMzs(const std::string &value) {}

std::string DG_CadHeader::DimensionLineType() const {}

void DG_CadHeader::DimensionLineType(const std::string &value) {}

std::string DG_CadHeader::DimensionTex1() const {}

void DG_CadHeader::DimensionTex1(const std::string &value) {}

std::string DG_CadHeader::DimensionTex2() const {}

void DG_CadHeader::DimensionTex2(const std::string &value) {}

DG_Layer *DG_CadHeader::CurrentLayer() const {}

void DG_CadHeader::CurrentLayer(DG_Layer *) {}

DG_LineType *DG_CadHeader::CurrentLineType() const {}

void DG_CadHeader::CurrentLineType(DG_LineType *) {}

DG_TextStyle *DG_CadHeader::CurrentTextStyle() const {}

void DG_CadHeader::TextStyle(DG_TextStyle *) {}

DG_TextStyle *DG_CadHeader::DimensionTextStyle() const {}

void DG_CadHeader::DimensionTextStyle(DG_TextStyle *) {}

DG_DimensionStyle *DG_CadHeader::DimensionStyleOverrides() const {}

void DG_CadHeader::DimensionStyleOverrides(DG_DimensionStyle *) {}

DG_UCS *DG_CadHeader::ModelSpaceUcs() const {}

void DG_CadHeader::ModelSpaceUcs(DG_UCS *) {}

DG_UCS *DG_CadHeader::ModelSpaceUcsBase() const {}

void DG_CadHeader::ModelSpaceUcsBase(DG_UCS *) {}

DG_UCS *DG_CadHeader::PaperSpaceUcs() const {}

void DG_CadHeader::PaperSpaceUcs(DG_UCS *) {}

DG_UCS *DG_CadHeader::PaperSpaceUcsBase() const {}

void DG_CadHeader::PaperSpaceUcsBase(DG_UCS *) {}

}// namespace dwg
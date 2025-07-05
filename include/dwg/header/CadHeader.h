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

#include <dwg/ACadVersion.h>
#include <dwg/Color.h>
#include <dwg/Coordinate.h>
#include <dwg/LineWeightType.h>
#include <dwg/entities/VerticalAlignmentType.h>
#include <dwg/exports.h>
#include <dwg/header/AttributeVisibilityMode.h>
#include <dwg/header/DimensionAssociation.h>
#include <dwg/header/EntityPlotStyleType.h>
#include <dwg/header/IndexCreationFlags.h>
#include <dwg/header/MeasurementUnits.h>
#include <dwg/header/ObjectSnapMode.h>
#include <dwg/header/ObjectSortingFlags.h>
#include <dwg/header/ShadeEdgeType.h>
#include <dwg/header/ShadowMode.h>
#include <dwg/header/SpaceLineTypeScaling.h>
#include <dwg/header/SplineType.h>
#include <dwg/tables/ArcLengthSymbolPosition.h>
#include <dwg/tables/DimensionTextBackgroundFillMode.h>
#include <dwg/tables/DimensionTextHorizontalAlignment.h>
#include <dwg/tables/DimensionTextVerticalAlignment.h>
#include <dwg/tables/FractionFormat.h>
#include <dwg/tables/TextArrowFitType.h>
#include <dwg/tables/TextDirection.h>
#include <dwg/tables/TextMovement.h>
#include <dwg/tables/ToleranceAlignment.h>
#include <dwg/tables/ZeroHandling.h>
#include <dwg/units/AngularDirection.h>
#include <dwg/units/AngularUnitFormat.h>
#include <dwg/units/LinearUnitFormat.h>
#include <dwg/units/UnitsType.h>
#include <dwg/utils/DateTime.h>
#include <string>

namespace dwg {

class UCS;
class Layer;
class LineType;
class TextStyle;
class DimensionStyle;
class MLineStyle;
class CadDocument;

class LIBDWG_API CadHeader
{
public:
    CadHeader();
    CadHeader(ACadVersion version);
    CadHeader(CadDocument *document);

    double angleBase() const;
    void setAngleBase(double);

    AngularDirection angularDirection() const;
    void setAngularDirection(AngularDirection);

    AngularUnitFormat angularUnit() const;
    void setAngularUnit(AngularUnitFormat);

    short angularUnitPrecision() const;
    void setAngularUnitPrecision(short);

    std::string arrowBlockName() const;
    void setArrowBlockName(const std::string &);

    bool associatedDimensions() const;
    void setAssociatedDimensions(bool);

    AttributeVisibilityMode attributeVisibility() const;
    void setAttributeVisibility(AttributeVisibilityMode);

    bool blipMode() const;
    void setBlipMode(bool);

    bool cameraDisplayObjects() const;
    void setCameraDisplayObjects(bool);

    double cameraHeight() const;
    void setCameraHeight(double);

    double chamferAngle() const;
    void setChamferAngle(double);

    double chamferDistance1() const;
    void setChamferDistance1(double);

    double chamferDistance2() const;
    void setChamferDistance2(double);

    double chamferLength() const;
    void setChamferLength(double);

    std::string codePage() const;
    void setCodePage(const std::string &);

    DateTime createDateTime() const;
    void setCreateDateTime(const DateTime &);

    bool createEllipseAsPolyline() const;
    void setCreateEllipseAsPolyline(bool);

    Color currentEntityColor() const;
    void setCurrentEntityColor(const Color &);

    double currentEntityLinetypeScale() const;
    void setCurrentEntityLinetypeScale(double);

    LineweightType currentEntityLineWeight() const;
    void setCurrentEntityLineWeight(LineweightType);

    EntityPlotStyleType currentEntityPlotStyle() const;
    void setCurrentEntityPlotStyle(EntityPlotStyleType);

    Layer *currentLayer() const;
    void setCurrentLayer(Layer *);

    std::string currentLayerName() const;
    void setCurrentLayerName(const std::string &);

    LineType *currentLineType() const;
    void setCurrentLineType(LineType *);

    std::string currentLineTypeName() const;
    void setCurrentLineTypeName(const std::string &);

    MLineStyle *currentMLineStyle() const;
    void setCurrentMLineStyle(MLineStyle *);

    VerticalAlignmentType currentMultilineJustification() const;
    void setCurrentMultilineJustification(VerticalAlignmentType);

    double currentMultilineScale() const;
    void setCurrentMultilineScale(double);

    std::string currentMultiLineStyleName() const;
    void setCurrentMultiLineStyleName(const std::string &);

    TextStyle *currentTextStyle() const;
    void setTextStyle(TextStyle *);

    char dgnUnderlayFramesVisibility() const;
    void setDgnUnderlayFramesVisibility(char);

    std::string dimensionAlternateDimensioningSuffix() const;
    void setDimensionAlternateDimensioningSuffix(const std::string &);

    short dimensionAlternateUnitDecimalPlaces() const;
    void setDimensionAlternateUnitDecimalPlaces(short);

    bool dimensionAlternateUnitDimensioning() const;
    void setDimensionAlternateUnitDimensioning(bool);

    LinearUnitFormat dimensionAlternateUnitFormat() const;
    void setDimensionAlternateUnitFormat(LinearUnitFormat);

    double dimensionAlternateUnitRounding() const;
    void setDimensionAlternateUnitRounding(double);

    double dimensionAlternateUnitScaleFactor() const;
    void setDimensionAlternateUnitScaleFactor(double);

    short dimensionAlternateUnitToleranceDecimalPlaces() const;
    void setDimensionAlternateUnitToleranceDecimalPlaces(short);

    ZeroHandling dimensionAlternateUnitToleranceZeroHandling() const;
    void setDimensionAlternateUnitToleranceZeroHandling(ZeroHandling);

    ZeroHandling dimensionAlternateUnitZeroHandling() const;
    void setDimensionAlternateUnitZeroHandling(ZeroHandling);

    double dimensionAltMzf() const;
    void setDimensionAltMzf(double);

    std::string dimensionAltMzs() const;
    void setDimensionAltMzs(const std::string &);

    short dimensionAngularDimensionDecimalPlaces() const;
    void setDimensionAngularDimensionDecimalPlaces(short);

    AngularUnitFormat dimensionAngularUnit() const;
    void setDimensionAngularUnit(AngularUnitFormat);

    ZeroHandling dimensionAngularZeroHandling() const;
    void setDimensionAngularZeroHandling(ZeroHandling);

    ArcLengthSymbolPosition dimensionArcLengthSymbolPosition() const;
    void setDimensionArcLengthSymbolPosition(ArcLengthSymbolPosition);

    double dimensionArrowSize() const;
    void setDimensionArrowSize(double);

    DimensionAssociation dimensionAssociativity() const;
    void setDimensionAssociativity(DimensionAssociation);

    std::string dimensionBlockName() const;
    void setDimensionBlockName(const std::string &);

    std::string dimensionBlockNameFirst() const;
    void setDimensionBlockNameFirst(const std::string &);

    std::string dimensionBlockNameSecond() const;
    void setDimensionBlockNameSecond(const std::string &);

    double dimensionCenterMarkSize() const;
    void setDimensionCenterMarkSize(double);

    bool dimensionCursorUpdate() const;
    void setDimensionCursorUpdate(bool);

    short dimensionDecimalPlaces() const;
    void setDimensionDecimalPlaces(short);

    char dimensionDecimalSeparator() const;
    void setDimensionDecimalSeparator(char);

    TextArrowFitType dimensionDimensionTextArrowFit() const;
    void setDimensionDimensionTextArrowFit(TextArrowFitType);

    Color dimensionExtensionLineColor() const;
    void setDimensionExtensionLineColor(const Color &);

    double dimensionExtensionLineExtension() const;
    void setDimensionExtensionLineExtension(double);

    double dimensionExtensionLineOffset() const;
    void setDimensionExtensionLineOffset(double);

    short dimensionFit() const;
    void setDimensionFit(short);

    double dimensionFixedExtensionLineLength() const;
    void setDimensionFixedExtensionLineLength(double);

    FractionFormat dimensionFractionFormat() const;
    void setDimensionFractionFormat(FractionFormat);

    bool dimensionGenerateTolerances() const;
    void setDimensionGenerateTolerances(bool);

    bool dimensionIsExtensionLineLengthFixed() const;
    void setDimensionIsExtensionLineLengthFixed(bool);

    double dimensionJoggedRadiusDimensionTransverseSegmentAngle() const;
    void setDimensionJoggedRadiusDimensionTransverseSegmentAngle(double);

    bool dimensionLimitsGeneration() const;
    void setDimensionLimitsGeneration(bool);

    double dimensionLinearScaleFactor() const;
    void setDimensionLinearScaleFactor(double);

    LinearUnitFormat dimensionLinearUnitFormat() const;
    void setDimensionLinearUnitFormat(LinearUnitFormat);

    Color dimensionLineColor() const;
    void setDimensionLineColor(const Color &);

    double dimensionLineExtension() const;
    void setDimensionLineExtension(double);

    double dimensionLineGap() const;
    void setDimensionLineGap(double);

    double dimensionLineIncrement() const;
    void setDimensionLineIncrement(double);

    std::string dimensionLineType() const;
    void setDimensionLineType(const std::string &);

    LineweightType dimensionLineWeight() const;
    void setDimensionLineWeight(LineweightType);

    double dimensionMinusTolerance() const;
    void setDimensionMinusTolerance(double);

    double dimensionMzf() const;
    void setDimensionMzf(double);

    std::string dimensionMzs() const;
    void setDimensionMzs(const std::string &);

    double dimensionPlusTolerance() const;
    void setDimensionPlusTolerance(double);

    std::string dimensionPostFix() const;
    void setDimensionPostFix(const std::string &);

    double dimensionRounding() const;
    void setDimensionRounding(double);

    double dimensionScaleFactor() const;
    void setDimensionScaleFactor(double);

    bool dimensionSeparateArrowBlocks() const;
    void setDimensionSeparateArrowBlocks(bool);

    DimensionStyle *currentDimensionStyle() const;
    void setCurrentDimensionStyle(DimensionStyle *);

    std::string currentDimensionStyleName() const;
    void setCurrentDimensionStyleName(const std::string &);

    bool dimensionSuppressFirstDimensionLine() const;
    void setDimensionSuppressFirstDimensionLine(bool);

    bool dimensionSuppressFirstExtensionLine() const;
    void setDimensionSuppressFirstExtensionLine(bool);

    bool dimensionSuppressOutsideExtensions() const;
    void setDimensionSuppressOutsideExtensions(bool);

    bool dimensionSuppressSecondDimensionLine() const;
    void setDimensionSuppressSecondDimensionLine(bool);

    bool dimensionSuppressSecondExtensionLine() const;
    void setDimensionSuppressSecondExtensionLine(bool);

    std::string dimensionTex1() const;
    void setDimensionTex1(const std::string &);

    std::string dimensionTex2() const;
    void setDimensionTex2(const std::string &);

    Color dimensionTextBackgroundColor() const;
    void setDimensionTextBackgroundColor(const Color &);

    DimensionTextBackgroundFillMode dimensionTextBackgroundFillMode() const;
    void setDimensionTextBackgroundFillMode(DimensionTextBackgroundFillMode);

    Color dimensionTextColor() const;
    void setDimensionTextColor(const Color &);

    TextDirection dimensionTextDirection() const;
    void setDimensionTextDirection(TextDirection);

    double dimensionTextHeight() const;
    void setDimensionTextHeight(double);

    DimensionTextHorizontalAlignment dimensionTextHorizontalAlignment() const;
    void setDimensionTextHorizontalAlignment(DimensionTextHorizontalAlignment);

    bool dimensionTextInsideExtensions() const;
    void setDimensionTextInsideExtensions(bool);

    bool dimensionTextInsideHorizontal() const;
    void setDimensionTextInsideHorizontal(bool);

    TextMovement dimensionTextMovement() const;
    void setDimensionTextMovement(TextMovement);

    bool dimensionTextOutsideExtensions() const;
    void setDimensionTextOutsideExtensions(bool);

    bool dimensionTextOutsideHorizontal() const;
    void setDimensionTextOutsideHorizontal(bool);

    TextStyle *dimensionTextStyle() const;
    void setDimensionTextStyle(TextStyle *);

    std::string dimensionTextStyleName() const;
    void setDimensionTextStyleName(const std::string &);

    DimensionTextVerticalAlignment dimensionTextVerticalAlignment() const;
    void setDimensionTextVerticalAlignment(DimensionTextVerticalAlignment);

    double dimensionTextVerticalPosition() const;
    void setDimensionTextVerticalPosition(double);

    double dimensionTickSize() const;
    void setDimensionTickSize(double);

    ToleranceAlignment dimensionToleranceAlignment() const;
    void setDimensionToleranceAlignment(ToleranceAlignment);

    short dimensionToleranceDecimalPlaces() const;
    void setDimensionToleranceDecimalPlaces(short);

    double dimensionToleranceScaleFactor() const;
    void setDimensionToleranceScaleFactor(double);

    ZeroHandling dimensionToleranceZeroHandling() const;
    void setDimensionToleranceZeroHandling(ZeroHandling);

    short dimensionUnit() const;
    void setDimensionUnit(short);

    ZeroHandling dimensionZeroHandling() const;
    void setDimensionZeroHandling(ZeroHandling);

    DimensionStyle *dimensionStyleOverrides() const;

    char displayLightGlyphs() const;
    void setDisplayLightGlyphs(char);

    bool displayLineWeight() const;
    void setDisplayLineWeight(bool);

    bool displaySilhouetteCurves() const;
    void setDisplaySilhouetteCurves(bool);

    CadDocument *document();
    void setDocument(CadDocument *document);

    double draftAngleFirstCrossSection() const;
    void setDraftAngleFirstCrossSection(double);

    double draftAngleSecondCrossSection() const;
    void setDraftAngleSecondCrossSection(double);

    double draftMagnitudeFirstCrossSection() const;
    void setDraftMagnitudeFirstCrossSection(double);

    double draftMagnitudeSecondCrossSection() const;
    void setDraftMagnitudeSecondCrossSection(double);

    double dw3DPrecision() const;
    void setDw3DPrecision(double);

    char dwgUnderlayFramesVisibility() const;
    void setDwgUnderlayFramesVisibility(char);

    double elevation() const;
    void setElevation(double);

    short endCaps() const;
    void setEndCaps(short);

    ObjectSortingFlags entitySortingFlags() const;
    void setEntitySortingFlags(ObjectSortingFlags);

    bool extendedNames() const;
    void setExtendedNames(bool);

    LineweightType extensionLineWeight() const;
    void setExtensionLineWeight(LineweightType);

    unsigned char externalReferenceClippingBoundaryType() const;
    void setExternalReferenceClippingBoundaryType(unsigned char);

    double facetResolution() const;
    void setFacetResolution(double);

    double filletRadius() const;
    void setFilletRadius(double);

    bool fillMode() const;
    void setFillMode(bool);

    std::string fingerPrintGuid() const;
    void setFingerPrintGuid(const std::string &);

    unsigned char haloGapPercentage() const;
    void setHaloGapPercentage(unsigned char);

    unsigned long long handleSeed() const;
    void setHandleSeed(unsigned long long);

    unsigned char hideText() const;
    void setHideText(unsigned char);

    std::string hyperLinkBase() const;
    void setHyperLinkBase(const std::string &);

    IndexCreationFlags indexCreationFlags() const;
    void setIndexCreationFlags(IndexCreationFlags);

    UnitsType insUnits() const;
    void setInsUnits(UnitsType);

    Color interfereColor() const;
    void setInterfereColor(const Color &);

    unsigned char intersectionDisplay() const;
    void setIntersectionDisplay(unsigned char);

    short joinStyle() const;
    void setJoinStyle(short);

    std::string lastSavedBy() const;
    void setLastSavedBy(const std::string &);

    double latitude() const;
    void setLatitude(double);

    double lensLength() const;
    void setLensLength(double);

    bool limitCheckingOn() const;
    void setLimitCheckingOn(bool);

    LinearUnitFormat linearUnitFormat() const;
    void setLinearUnitFormat(LinearUnitFormat);

    short linearUnitPrecision() const;
    void setLinearUnitPrecision(short);

    double lineTypeScale() const;
    void setLineTypeScale(double);

    bool loadOLEObject() const;
    void setLoadOLEObject(bool);

    char loftedObjectNormals() const;
    void setLoftedObjectNormals(char);

    double longitude() const;
    void setLongitude(double);

    short maintenanceVersion() const;
    void setMaintenanceVersion(short);

    short maxViewportCount() const;
    void setMaxViewportCount(short);

    MeasurementUnits measurementUnits() const;
    void setMeasurementUnits(MeasurementUnits);

    std::string menuFileName() const;
    void setMenuFileName(const std::string &);

    bool mirrorText() const;
    void setMirrorText(bool);

    XYZ modelSpaceExtMax() const;
    void setModelSpaceExtMax(const XYZ &);

    XYZ modelSpaceExtMin() const;
    void setModelSpaceExtMin(const XYZ &);

    XYZ modelSpaceInsertionBase() const;
    void setModelSpaceInsertionBase(const XYZ &);

    XY modelSpaceLimitsMax() const;
    void setModelSpaceLimitsMax(const XY &);

    XY modelSpaceLimitsMin() const;
    void setModelSpaceLimitsMin(const XY &);

    XYZ modelSpaceOrigin() const;
    void setModelSpaceOrigin(const XYZ &);

    XYZ modelSpaceOrthographicBackDOrigin() const;
    void setModelSpaceOrthographicBackDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicBottomDOrigin() const;
    void setModelSpaceOrthographicBottomDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicFrontDOrigin() const;
    void setModelSpaceOrthographicFrontDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicLeftDOrigin() const;
    void setModelSpaceOrthographicLeftDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicRightDOrigin() const;
    void setModelSpaceOrthographicRightDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicTopDOrigin() const;
    void setModelSpaceOrthographicTopDOrigin(const XYZ &);

    UCS *modelSpaceUcs() const;
    void setModelSpaceUcs(UCS *);

    UCS *modelSpaceUcsBase() const;
    void setModelSpaceUcsBase(UCS *);

    XYZ modelSpaceXAxis() const;
    void setModelSpaceXAxis(const XYZ &);

    XYZ modelSpaceYAxis() const;
    void setModelSpaceYAxis(const XYZ &);

    double northDirection() const;
    void setNorthDirection(double);

    short numberOfSplineSegments() const;
    void setNumberOfSplineSegments(short);

    ObjectSnapMode objectSnapMode() const;
    void setObjectSnapMode(ObjectSnapMode);

    Color obscuredColor() const;
    void setObscuredColor(const Color &);

    unsigned char obscuredType() const;
    void setObscuredType(unsigned char);

    bool orthoMode() const;
    void setOrthoMode(bool);

    std::string paperSpaceBaseName() const;
    void setPaperSpaceBaseName(const std::string &);

    double paperSpaceElevation() const;
    void setPaperSpaceElevation(double);

    XYZ paperSpaceExtMax() const;
    void setPaperSpaceExtMax(const XYZ &);

    XYZ paperSpaceExtMin() const;
    void setPaperSpaceExtMin(const XYZ &);

    XYZ paperSpaceInsertionBase() const;
    void setPaperSpaceInsertionBase(const XYZ &);

    bool paperSpaceLimitsChecking() const;
    void setPaperSpaceLimitsChecking(bool);

    XY paperSpaceLimitsMax() const;
    void setPaperSpaceLimitsMax(const XY &);

    XY paperSpaceLimitsMin() const;
    void setPaperSpaceLimitsMin(const XY &);

    SpaceLineTypeScaling paperSpaceLineTypeScaling() const;
    void setPaperSpaceLineTypeScaling(SpaceLineTypeScaling);

    std::string paperSpaceName() const;
    void setPaperSpaceName(const std::string &);

    XYZ paperSpaceOrthographicBackDOrigin() const;
    void setPaperSpaceOrthographicBackDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicBottomDOrigin() const;
    void setPaperSpaceOrthographicBottomDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicFrontDOrigin() const;
    void setPaperSpaceOrthographicFrontDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicLeftDOrigin() const;
    void setPaperSpaceOrthographicLeftDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicRightDOrigin() const;
    void setPaperSpaceOrthographicRightDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicTopDOrigin() const;
    void setPaperSpaceOrthographicTopDOrigin(const XYZ &);

    UCS *paperSpaceUcs() const;
    void setPaperSpaceUcs(UCS *);

    UCS *paperSpaceUcsBase() const;
    void setPaperSpaceUcsBase(UCS *);

    XYZ paperSpaceUcsOrigin() const;
    void setPaperSpaceUcsOrigin(const XYZ &);

    XYZ paperSpaceUcsXAxis() const;
    void setPaperSpaceUcsXAxis(const XYZ &);

    XYZ paperSpaceUcsYAxis() const;
    void setPaperSpaceUcsYAxis(const XYZ &);

    short plotStyleMode() const;
    void setPlotStyleMode(short);

    short pointDisplayMode() const;
    void setPointDisplayMode(short);

    double pointDisplaySize() const;
    void setPointDisplaySize(double);

    bool polylineLineTypeGeneration() const;
    void setPolylineLineTypeGeneration(bool);

    double polylineWidthDefault() const;
    void setPolylineWidthDefault(double);

    std::string projectName() const;
    void setProjectName(const std::string &);

    bool proxyGraphics() const;
    void setProxyGraphics(bool);

    bool quickTextMode() const;
    void setQuickTextMode(bool);

    bool regenerationMode() const;
    void setRegenerationMode(bool);

    long long requiredVersions() const;
    void setRequiredVersions(long long);

    bool retainXRefDependentVisibilitySettings() const;
    void setRetainXRefDependentVisibilitySettings(bool);

    short shadeDiffuseToAmbientPercentage() const;
    void setShadeDiffuseToAmbientPercentage(short);

    ShadeEdgeType shadeEdge() const;
    void setShadeEdge(ShadeEdgeType);

    ShadowMode shadowMode() const;
    void setShadowMode(ShadowMode);

    double shadowPlaneLocation() const;
    void setShadowPlaneLocation(double);

    bool showModelSpace() const;
    void setShowModelSpace(bool);

    char showSolidsHistory() const;
    void setShowSolidsHistory(char);

    bool showSplineControlPoints() const;
    void setShowSplineControlPoints(bool);

    double sketchIncrement() const;
    void setSketchIncrement(double);

    bool sketchPolylines() const;
    void setSketchPolylines(bool);

    short solidLoftedShape() const;
    void setSolidLoftedShape(short);

    char solidsRetainHistory() const;
    void setSolidsRetainHistory(char);

    short spatialIndexMaxTreeDepth() const;
    void setSpatialIndexMaxTreeDepth(short);

    SplineType splineType() const;
    void setSplineType(SplineType);

    short stackedTextAlignment() const;
    void setStackedTextAlignment(short);

    short stackedTextSizePercentage() const;
    void setStackedTextSizePercentage(short);

    double stepSize() const;
    void setStepSize(double);

    double stepsPerSecond() const;
    void setStepsPerSecond(double);

    std::string styleSheetName() const;
    void setStyleSheetName(const std::string &);

    short surfaceDensityU() const;
    void setSurfaceDensityU(short);

    short surfaceDensityV() const;
    void setSurfaceDensityV(short);

    short surfaceIsolineCount() const;
    void setSurfaceIsolineCount(short);

    short surfaceMeshTabulationCount1() const;
    void setSurfaceMeshTabulationCount1(short);

    short surfaceMeshTabulationCount2() const;
    void setSurfaceMeshTabulationCount2(short);

    short surfaceType() const;
    void setSurfaceType(short);

    double sweptSolidHeight() const;
    void setSweptSolidHeight(double);

    double sweptSolidWidth() const;
    void setSweptSolidWidth(double);

    double textHeightDefault() const;
    void setTextHeightDefault(double);

    short textQuality() const;
    void setTextQuality(short);

    std::string textStyleName() const;
    void setTextStyleName(const std::string &);

    double thicknessDefault() const;
    void setThicknessDefault(double);

    int timeZone() const;
    void setTimeZone(int);

    Timespan totalEditingTime() const;
    void setTotalEditingTime(const Timespan &);

    double traceWidthDefault() const;
    void setTraceWidthDefault(double);

    std::string ucsBaseName() const;
    void setUcsBaseName(const std::string &);

    std::string ucsName() const;
    void setUcsName(const std::string &);

    short unitMode() const;
    void setUnitMode(short);

    DateTime universalCreateDateTime() const;
    void setUniversalCreateDateTime(const DateTime &);

    DateTime universalUpdateDateTime() const;
    void setUniversalUpdateDateTime(const DateTime &);

    DateTime updateDateTime() const;
    void setUpdateDateTime(const DateTime &);

    bool updateDimensionsWhileDragging() const;
    void setUpdateDimensionsWhileDragging(bool);

    double userDouble1() const;
    void setUserDouble1(double);

    double userDouble2() const;
    void setUserDouble2(double);

    double userDouble3() const;
    void setUserDouble3(double);

    double userDouble4() const;
    void setUserDouble4(double);

    double userDouble5() const;
    void setUserDouble5(double);

    double userElapsedTimeSpan() const;
    void setUserElapsedTimeSpan(double);

    short userShort1() const;
    void setUserShort1(short);

    short userShort2() const;
    void setUserShort2(short);

    short userShort3() const;
    void setUserShort3(short);

    short userShort4() const;
    void setUserShort4(short);

    short userShort5() const;
    void setUserShort5(short);

    bool userTimer() const;
    void setUserTimer(bool);

    ACadVersion version() const;
    void setVersion(ACadVersion);

    std::string versionGuid() const;
    void setVersionGuid(const std::string &);

    std::string versionString() const;
    void setVersionString(const std::string &);

    double viewportDefaultViewScaleFactor() const;
    void setViewportDefaultViewScaleFactor(double);

    bool worldView() const;
    void setWorldView(bool);

    bool xedit() const;
    void setXEdit(bool);

    bool DIMSAV() const;
    void setDIMSAV(bool);

private:
    CadDocument *_document;
    std::string _versionString;
    ACadVersion _version;
    short _maintenanceVersion;
    std::string _codePage = "ANSI_1252";
    std::string _lastSavedBy = "libDWG";
    bool _associatedDimensions = true;
    bool _updateDimensionsWhileDragging = true;
    bool _DIMSAV = false;
    MeasurementUnits _measurementUnits = MeasurementUnits::Metric;
    bool _polylineLineTypeGeneration = false;
    bool _orthoMode = false;
    bool _regenerationMode = false;
    bool _fillMode = true;
    bool _quickTextMode = false;
    SpaceLineTypeScaling _paperSpaceLineTypeScaling = SpaceLineTypeScaling::Normal;
    bool _limitCheckingOn = false;
    bool _blipMode = false;
    bool _userTimer = false;
    bool _sketchPolylines = false;
    AngularDirection _angularDirection = AngularDirection::ClockWise;
    bool _showSplineControlPoints = false;
    bool _mirrorText = false;
    bool _worldView = true;
    bool _showModelSpace = false;
    bool _paperSpaceLimitsChecking = false;
    bool _retainXRefDependentVisibilitySettings = true;
    bool _displaySilhouetteCurves = false;
    bool _createEllipseAsPolyline = false;
    bool _proxyGraphics = true;
    short _spatialIndexMaxTreeDepth = 3020;
    LinearUnitFormat _linearUnitFormat = LinearUnitFormat::Decimal;
    short _linearUnitPrecision = 4;
    AngularUnitFormat _angularUnit = AngularUnitFormat::DecimalDegrees;
    short _angularUnitPrecision = 0;
    ObjectSnapMode _objectSnapMode = (ObjectSnapMode) 4133;
    AttributeVisibilityMode _attributeVisibility = AttributeVisibilityMode::Normal;
    short _pointDisplayMode = 0;
    short _userShort1 = 0;
    short _userShort2 = 0;
    short _userShort3 = 0;
    short _userShort4 = 0;
    short _userShort5 = 0;
    short _numberOfSplineSegments = 8;
    short _surfaceDensityU = 6;
    short _surfaceDensityV = 6;
    short _surfaceType = 6;
    short _surfaceMeshTabulationCount1 = 6;
    short _surfaceMeshTabulationCount2 = 6;
    SplineType _splineType = SplineType::CubicBSpline;
    ShadeEdgeType _shadeEdge = ShadeEdgeType::FacesInEntityColorEdgesInBlack;
    short _shadeDiffuseToAmbientPercentage = 70;
    short _unitMode = 0;
    short _maxViewportCount = 64;
    short _surfaceIsolineCount;
    VerticalAlignmentType _currentMultilineJustification = VerticalAlignmentType::Top;
    short _textQuality = 50;
    double _lineTypeScale = 1.0;
    double _textHeightDefault = 2.5;
    double _traceWidthDefault = 0.0;
    double _sketchIncrement = 1.0;
    double _filletRadius = 0.0;
    double _thicknessDefault = 0.0;
    double _angleBase = 0.0;
    double _pointDisplaySize = 0.0;
    double _polylineWidthDefault = 0.0;
    double _userDouble1 = 0.0;
    double _userDouble2 = 0.0;
    double _userDouble3 = 0.0;
    double _userDouble4 = 0.0;
    double _userDouble5 = 0.0;
    double _chamferDistance1 = 0.0;
    double _chamferDistance2 = 0.0;
    double _chamferLength = 0.0;
    double _chamferAngle = 0.0;
    double _facetResolution = 0.5;
    double _currentMultilineScale = 20.0;
    double _currentEntityLinetypeScale = 1.0;
    std::string _menuFileName = ".";
    unsigned long long _handleSeed = 0x01;
    DateTime _createDateTime;
    DateTime _universalCreateDateTime;
    DateTime _updateDateTime;
    DateTime _universalUpdateDateTime;
    Timespan _totalEditingTime;
    double _userElapsedTimeSpan;
    Color _currentEntityColor = Color::ByLayer;
    double _viewportDefaultViewScaleFactor;
    XYZ _paperSpaceInsertionBase;
    XYZ _paperSpaceExtMin = XYZ::Zero;
    XYZ _paperSpaceExtMax = XYZ::Zero;
    XY _paperSpaceLimitsMin;
    XY _paperSpaceLimitsMax;
    double _paperSpaceElevation = 0.0;
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
    short _stackedTextAlignment = 1;
    short _stackedTextSizePercentage = 70;
    std::string _hyperLinkBase;
    LineweightType _currentEntityLineWeight = LineweightType::ByLayer;
    short _endCaps = 0;
    short _joinStyle = 0;
    bool _displayLineWeight = false;
    bool _xedit = false;
    bool _extendedNames = true;
    short _plotStyleMode = 0;
    bool _loadOLEObject = false;
    UnitsType _insUnits = UnitsType::Unitless;
    EntityPlotStyleType _currentEntityPlotStyle = EntityPlotStyleType::ByLayer;
    std::string _fingerPrintGuid;
    std::string _versionGuid;
    ObjectSortingFlags _entitySortingFlags;
    IndexCreationFlags _indexCreationFlags;
    unsigned char _hideText;
    unsigned char _externalReferenceClippingBoundaryType;
    DimensionAssociation _dimensionAssociativity = DimensionAssociation::CreateExplodedDimensions;
    unsigned char _haloGapPercentage;
    Color _obscuredColor = Color::ByBlock;
    Color _interfereColor = Color((short) 1);
    unsigned char _obscuredType;
    unsigned char _intersectionDisplay;
    std::string _projectName;
    bool _cameraDisplayObjects;
    double _stepsPerSecond;
    double _stepSize = 6.0;
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
    double _dimensionLineExtension;
    double _dimensionLineIncrement;
    double _dimensionExtensionLineExtension;
    bool _dimensionIsExtensionLineLengthFixed;
    double _dimensionFixedExtensionLineLength;
    double _dimensionJoggedRadiusDimensionTransverseSegmentAngle;
    DimensionTextBackgroundFillMode _dimensionTextBackgroundFillMode;
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

    std::string _dimensionMzs;
    std::string _dimensionLineType;
    std::string _dimensionTex1;
    std::string _dimensionTex2;

    Layer *_currentLayer;
    LineType *_currentLineType;
    MLineStyle *_currentMLineStyle;
    TextStyle *_currentTextStyle;
    DimensionStyle *_currentDimensionStyle;
    DimensionStyle *_dimensionStyleOverrides;
    TextStyle *_dimensionTextStyle;
    UCS *_modelSpaceUcs;
    UCS *_modelSpaceUcsBase;
    UCS *_paperSpaceUcs;
    UCS *_paperSpaceUcsBase;
};

}// namespace dwg
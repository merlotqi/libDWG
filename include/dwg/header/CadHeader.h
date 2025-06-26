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
class CadDocument;

class LIBDWG_API CadHeader
{
public:
    CadHeader();
    CadHeader(ACadVersion version);
    CadHeader(CadDocument *document);

    CadDocument *document();
    void setDocument(CadDocument *document);

    std::string versionString() const;
    void setVersionString(const std::string &);

    ACadVersion version() const;
    void setVersion(ACadVersion);

    short maintenanceVersion() const;
    void setMaintenanceVersion(short);

    std::string codePage() const;
    void setCodePage(const std::string &);

    std::string lastSavedBy() const;
    void setLastSavedBy(const std::string &);

    bool associatedDimensions() const;
    void setAssociatedDimensions(bool);

    bool updateDimensionsWhileDragging() const;
    void setUpdateDimensionsWhileDragging(bool);

    bool DIMSAV() const;
    void setDIMSAV(bool);

    MeasurementUnits measurementUnits() const;
    void setMeasurementUnits(MeasurementUnits);

    bool polylineLineTypeGeneration() const;
    void setPolylineLineTypeGeneration(bool);

    bool orthoMode() const;
    void setOrthoMode(bool);

    bool regenerationMode() const;
    void setRegenerationMode(bool);

    bool fillMode() const;
    void setFillMode(bool);

    bool quickTextMode() const;
    void setQuickTextMode(bool);

    SpaceLineTypeScaling paperSpaceLineTypeScaling() const;
    void setPaperSpaceLineTypeScaling(SpaceLineTypeScaling);

    bool limitCheckingOn() const;
    void setLimitCheckingOn(bool);

    bool blipMode() const;
    void setBlipMode(bool);

    bool userTimer() const;
    void setUserTimer(bool);

    bool sketchPolylines() const;
    void setSketchPolylines(bool);

    AngularDirection angularDirection() const;
    void setAngularDirection(AngularDirection);

    bool showSplineControlPoints() const;
    void setShowSplineControlPoints(bool);

    bool mirrorText() const;
    void setMirrorText(bool);

    bool worldView() const;
    void setWorldView(bool);

    bool showModelSpace() const;
    void setShowModelSpace(bool);

    bool paperSpaceLimitsChecking() const;
    void setPaperSpaceLimitsChecking(bool);

    bool retainXRefDependentVisibilitySettings() const;
    void setRetainXRefDependentVisibilitySettings(bool);

    bool displaySilhouetteCurves() const;
    void setDisplaySilhouetteCurves(bool);

    bool createEllipseAsPolyline() const;
    void setCreateEllipseAsPolyline(bool);

    bool proxyGraphics() const;
    void setProxyGraphics(bool);

    short spatialIndexMaxTreeDepth() const;
    void setSpatialIndexMaxTreeDepth(short);

    LinearUnitFormat linearUnitFormat() const;
    void setLinearUnitFormat(LinearUnitFormat);

    short linearUnitPrecision() const;
    void setLinearUnitPrecision(short);

    AngularUnitFormat angularUnit() const;
    void setAngularUnit(AngularUnitFormat);

    short angularUnitPrecision() const;
    void setAngularUnitPrecision(short);

    ObjectSnapMode objectSnapMode() const;
    void setObjectSnapMode(ObjectSnapMode);

    AttributeVisibilityMode attributeVisibility() const;
    void setAttributeVisibility(AttributeVisibilityMode);

    short pointDisplayMode() const;
    void setPointDisplayMode(short);

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

    short numberOfSplineSegments() const;
    void setNumberOfSplineSegments(short);

    short surfaceDensityU() const;
    void setSurfaceDensityU(short);

    short surfaceDensityV() const;
    void setSurfaceDensityV(short);

    short surfaceType() const;
    void setSurfaceType(short);

    short surfaceMeshTabulationCount1() const;
    void setSurfaceMeshTabulationCount1(short);

    short surfaceMeshTabulationCount2() const;
    void setSurfaceMeshTabulationCount2(short);

    SplineType splineType() const;
    void setSplineType(SplineType);

    ShadeEdgeType shadeEdge() const;
    void setShadeEdge(ShadeEdgeType);

    short shadeDiffuseToAmbientPercentage() const;
    void setShadeDiffuseToAmbientPercentage(short);

    short unitMode() const;
    void setUnitMode(short);

    short maxViewportCount() const;
    void setMaxViewportCount(short);

    short surfaceIsolineCount() const;
    void setSurfaceIsolineCount(short);

    VerticalAlignmentType currentMultilineJustification() const;
    void setCurrentMultilineJustification(VerticalAlignmentType);

    short textQuality() const;
    void setTextQuality(short);

    double lineTypeScale() const;
    void setLineTypeScale(double);

    double textHeightDefault() const;
    void setTextHeightDefault(double);

    std::string textStyleName() const;
    void setTextStyleName(const std::string &);

    std::string currentLayerName() const;
    void setCurrentLayerName(const std::string &);

    std::string currentLineTypeName() const;
    void setCurrentLineTypeName(const std::string &);

    std::string multiLineStyleName() const;
    void setMultiLineStyleName(const std::string &);

    double traceWidthDefault() const;
    void setTraceWidthDefault(double);

    double sketchIncrement() const;
    void setSketchIncrement(double);

    double filletRadius() const;
    void setFilletRadius(double);

    double thicknessDefault() const;
    void setThicknessDefault(double);

    double angleBase() const;
    void setAngleBase(double);

    double pointDisplaySize() const;
    void setPointDisplaySize(double);

    double polylineWidthDefault() const;
    void setPolylineWidthDefault(double);

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

    double chamferDistance1() const;
    void setChamferDistance1(double);

    double chamferDistance2() const;
    void setChamferDistance2(double);

    double chamferLength() const;
    void setChamferLength(double);

    double chamferAngle() const;
    void setChamferAngle(double);

    double facetResolution() const;
    void setFacetResolution(double);

    double currentMultilineScale() const;
    void setCurrentMultilineScale(double);

    std::string currentMultiLineStyleName() const;
    void setCurrentMultiLineStyleName(const std::string &);

    std::string currentDimensionStyleName() const;
    void setCurrentDimensionStyleName(const std::string &);

    long long requiredVersions() const;
    void setRequiredVersions(long long);

    double currentEntityLinetypeScale() const;
    void setCurrentEntityLinetypeScale(double);

    std::string menuFileName() const;
    void setMenuFileName(const std::string &);

    unsigned long long handleSeed() const;
    void setHandleSeed(unsigned long long);

    DateTime createDateTime() const;
    void setCreateDateTime(const DateTime &);

    DateTime universalCreateDateTime() const;
    void setUniversalCreateDateTime(const DateTime &);

    DateTime updateDateTime() const;
    void setUpdateDateTime(const DateTime &);

    DateTime universalUpdateDateTime() const;
    void setUniversalUpdateDateTime(const DateTime &);

    double totalEditingTime() const;
    void setTotalEditingTime(double);

    double userElapsedTimeSpan() const;
    void setUserElapsedTimeSpan(double);

    Color currentEntityColor() const;
    void setCurrentEntityColor(const Color &);

    double viewportDefaultViewScaleFactor() const;
    void setViewportDefaultViewScaleFactor(double);

    XYZ paperSpaceInsertionBase() const;
    void setPaperSpaceInsertionBase(const XYZ &);

    XYZ paperSpaceExtMin() const;
    void setPaperSpaceExtMin(const XYZ &);

    XYZ paperSpaceExtMax() const;
    void setPaperSpaceExtMax(const XYZ &);

    XY paperSpaceLimitsMin() const;
    void setPaperSpaceLimitsMin(const XY &);

    XY paperSpaceLimitsMax() const;
    void setPaperSpaceLimitsMax(const XY &);

    double paperSpaceElevation() const;
    void setPaperSpaceElevation(double);

    std::string paperSpaceBaseName() const;
    void setPaperSpaceBaseName(const std::string &);

    std::string paperSpaceName() const;
    void setPaperSpaceName(const std::string &);

    XYZ paperSpaceUcsOrigin() const;
    void setPaperSpaceUcsOrigin(const XYZ &);

    XYZ paperSpaceUcsXAxis() const;
    void setPaperSpaceUcsXAxis(const XYZ &);

    XYZ paperSpaceUcsYAxis() const;
    void setPaperSpaceUcsYAxis(const XYZ &);

    XYZ paperSpaceOrthographicTopDOrigin() const;
    void setPaperSpaceOrthographicTopDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicBottomDOrigin() const;
    void setPaperSpaceOrthographicBottomDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicLeftDOrigin() const;
    void setPaperSpaceOrthographicLeftDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicRightDOrigin() const;
    void setPaperSpaceOrthographicRightDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicFrontDOrigin() const;
    void setPaperSpaceOrthographicFrontDOrigin(const XYZ &);

    XYZ paperSpaceOrthographicBackDOrigin() const;
    void setPaperSpaceOrthographicBackDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicTopDOrigin() const;
    void setModelSpaceOrthographicTopDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicBottomDOrigin() const;
    void setModelSpaceOrthographicBottomDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicLeftDOrigin() const;
    void setModelSpaceOrthographicLeftDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicRightDOrigin() const;
    void setModelSpaceOrthographicRightDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicFrontDOrigin() const;
    void setModelSpaceOrthographicFrontDOrigin(const XYZ &);

    XYZ modelSpaceOrthographicBackDOrigin() const;
    void setModelSpaceOrthographicBackDOrigin(const XYZ &);

    XYZ modelSpaceInsertionBase() const;
    void setModelSpaceInsertionBase(const XYZ &);

    XYZ modelSpaceExtMin() const;
    void setModelSpaceExtMin(const XYZ &);

    XYZ modelSpaceExtMax() const;
    void setModelSpaceExtMax(const XYZ &);

    XY modelSpaceLimitsMin() const;
    void setModelSpaceLimitsMin(const XY &);

    XY modelSpaceLimitsMax() const;
    void setModelSpaceLimitsMax(const XY &);

    std::string ucsBaseName() const;
    void setUcsBaseName(const std::string &);

    std::string ucsName() const;
    void setUcsName(const std::string &);

    double elevation() const;
    void setElevation(double);

    XYZ modelSpaceOrigin() const;
    void setModelSpaceOrigin(const XYZ &);

    XYZ modelSpaceXAxis() const;
    void setModelSpaceXAxis(const XYZ &);

    XYZ modelSpaceYAxis() const;
    void setModelSpaceYAxis(const XYZ &);

    std::string dimensionBlockName() const;
    void setDimensionBlockName(const std::string &);

    std::string arrowBlockName() const;
    void setArrowBlockName(const std::string &);

    std::string dimensionBlockNameFirst() const;
    void setDimensionBlockNameFirst(const std::string &);

    std::string dimensionBlockNameSecond() const;
    void setDimensionBlockNameSecond(const std::string &);

    short stackedTextAlignment() const;
    void setStackedTextAlignment(short);

    short stackedTextSizePercentage() const;
    void setStackedTextSizePercentage(short);

    std::string hyperLinkBase() const;
    void setHyperLinkBase(const std::string &);

    LineweightType currentEntityLineWeight() const;
    void setCurrentEntityLineWeight(LineweightType);

    short endCaps() const;
    void setEndCaps(short);

    short joinStyle() const;
    void setJoinStyle(short);

    bool displayLineWeight() const;
    void setDisplayLineWeight(bool);

    bool xedit() const;
    void setXEdit(bool);

    bool extendedNames() const;
    void setExtendedNames(bool);

    short plotStyleMode() const;
    void setPlotStyleMode(short);

    bool loadOLEObject() const;
    void setLoadOLEObject(bool);

    UnitsType insUnits() const;
    void setInsUnits(UnitsType);

    EntityPlotStyleType currentEntityPlotStyle() const;
    void setCurrentEntityPlotStyle(EntityPlotStyleType);

    std::string fingerPrintGuid() const;
    void setFingerPrintGuid(const std::string &);

    std::string versionGuid() const;
    void setVersionGuid(const std::string &);

    ObjectSortingFlags entitySortingFlags() const;
    void setEntitySortingFlags(ObjectSortingFlags);

    IndexCreationFlags indexCreationFlags() const;
    void setIndexCreationFlags(IndexCreationFlags);

    unsigned char hideText() const;
    void setHideText(unsigned char);

    unsigned char externalReferenceClippingBoundaryType() const;
    void setExternalReferenceClippingBoundaryType(unsigned char);

    DimensionAssociation dimensionAssociativity() const;
    void setDimensionAssociativity(DimensionAssociation);

    unsigned char haloGapPercentage() const;
    void setHaloGapPercentage(unsigned char);

    Color obscuredColor() const;
    void setObscuredColor(const Color &);

    Color interfereColor() const;
    void setInterfereColor(const Color &);

    unsigned char obscuredType() const;
    void setObscuredType(unsigned char);

    unsigned char intersectionDisplay() const;
    void setIntersectionDisplay(unsigned char);

    std::string projectName() const;
    void setProjectName(const std::string &);

    bool cameraDisplayObjects() const;
    void setCameraDisplayObjects(bool);

    double stepsPerSecond() const;
    void setStepsPerSecond(double);

    double stepSize() const;
    void setStepSize(double);

    double dw3DPrecision() const;
    void setDw3DPrecision(double);

    double lensLength() const;
    void setLensLength(double);

    double cameraHeight() const;
    void setCameraHeight(double);

    char solidsRetainHistory() const;
    void setSolidsRetainHistory(char);

    char showSolidsHistory() const;
    void setShowSolidsHistory(char);

    double sweptSolidWidth() const;
    void setSweptSolidWidth(double);

    double sweptSolidHeight() const;
    void setSweptSolidHeight(double);

    double draftAngleFirstCrossSection() const;
    void setDraftAngleFirstCrossSection(double);

    double draftAngleSecondCrossSection() const;
    void setDraftAngleSecondCrossSection(double);

    double draftMagnitudeFirstCrossSection() const;
    void setDraftMagnitudeFirstCrossSection(double);

    double draftMagnitudeSecondCrossSection() const;
    void setDraftMagnitudeSecondCrossSection(double);

    short solidLoftedShape() const;
    void setSolidLoftedShape(short);

    char loftedObjectNormals() const;
    void setLoftedObjectNormals(char);

    double latitude() const;
    void setLatitude(double);

    double longitude() const;
    void setLongitude(double);

    double northDirection() const;
    void setNorthDirection(double);

    int timeZone() const;
    void setTimeZone(int);

    char displayLightGlyphs() const;
    void setDisplayLightGlyphs(char);

    char dwgUnderlayFramesVisibility() const;
    void setDwgUnderlayFramesVisibility(char);

    char dgnUnderlayFramesVisibility() const;
    void setDgnUnderlayFramesVisibility(char);

    ShadowMode shadowMode() const;
    void setShadowMode(ShadowMode);

    double shadowPlaneLocation() const;
    void setShadowPlaneLocation(double);

    std::string styleSheetName() const;
    void setStyleSheetName(const std::string &);

    std::string dimensionTextStyleName() const;
    void setDimensionTextStyleName(const std::string &);

    std::string dimensionStyleOverridesName() const;
    void setDimensionStyleOverridesName(const std::string &);

    short dimensionAngularDimensionDecimalPlaces() const;
    void setDimensionAngularDimensionDecimalPlaces(short);

    short dimensionDecimalPlaces() const;
    void setDimensionDecimalPlaces(short);

    short dimensionToleranceDecimalPlaces() const;
    void setDimensionToleranceDecimalPlaces(short);

    bool dimensionAlternateUnitDimensioning() const;
    void setDimensionAlternateUnitDimensioning(bool);

    LinearUnitFormat dimensionAlternateUnitFormat() const;
    void setDimensionAlternateUnitFormat(LinearUnitFormat);

    double dimensionAlternateUnitScaleFactor() const;
    void setDimensionAlternateUnitScaleFactor(double);

    double dimensionExtensionLineOffset() const;
    void setDimensionExtensionLineOffset(double);

    double dimensionScaleFactor() const;
    void setDimensionScaleFactor(double);

    short dimensionAlternateUnitDecimalPlaces() const;
    void setDimensionAlternateUnitDecimalPlaces(short);

    short dimensionAlternateUnitToleranceDecimalPlaces() const;
    void setDimensionAlternateUnitToleranceDecimalPlaces(short);

    AngularUnitFormat dimensionAngularUnit() const;
    void setDimensionAngularUnit(AngularUnitFormat);

    FractionFormat dimensionFractionFormat() const;
    void setDimensionFractionFormat(FractionFormat);

    LinearUnitFormat dimensionLinearUnitFormat() const;
    void setDimensionLinearUnitFormat(LinearUnitFormat);

    char dimensionDecimalSeparator() const;
    void setDimensionDecimalSeparator(char);

    TextMovement dimensionTextMovement() const;
    void setDimensionTextMovement(TextMovement);

    DimensionTextHorizontalAlignment dimensionTextHorizontalAlignment() const;
    void setDimensionTextHorizontalAlignment(DimensionTextHorizontalAlignment);

    bool dimensionSuppressFirstDimensionLine() const;
    void setDimensionSuppressFirstDimensionLine(bool);

    bool dimensionSuppressSecondDimensionLine() const;
    void setDimensionSuppressSecondDimensionLine(bool);

    bool dimensionGenerateTolerances() const;
    void setDimensionGenerateTolerances(bool);

    ToleranceAlignment dimensionToleranceAlignment() const;
    void setDimensionToleranceAlignment(ToleranceAlignment);

    ZeroHandling dimensionZeroHandling() const;
    void setDimensionZeroHandling(ZeroHandling);

    ZeroHandling dimensionToleranceZeroHandling() const;
    void setDimensionToleranceZeroHandling(ZeroHandling);

    short dimensionFit() const;
    void setDimensionFit(short);

    ZeroHandling dimensionAlternateUnitZeroHandling() const;
    void setDimensionAlternateUnitZeroHandling(ZeroHandling);

    ZeroHandling dimensionAlternateUnitToleranceZeroHandling() const;
    void setDimensionAlternateUnitToleranceZeroHandling(ZeroHandling);

    bool dimensionCursorUpdate() const;
    void setDimensionCursorUpdate(bool);

    TextArrowFitType dimensionDimensionTextArrowFit() const;
    void setDimensionDimensionTextArrowFit(TextArrowFitType);

    double dimensionAlternateUnitRounding() const;
    void setDimensionAlternateUnitRounding(double);

    std::string dimensionAlternateDimensioningSuffix() const;
    void setDimensionAlternateDimensioningSuffix(const std::string &);

    double dimensionArrowSize() const;
    void setDimensionArrowSize(double);

    ZeroHandling dimensionAngularZeroHandling() const;
    void setDimensionAngularZeroHandling(ZeroHandling);

    ArcLengthSymbolPosition dimensionArcLengthSymbolPosition() const;
    void setDimensionArcLengthSymbolPosition(ArcLengthSymbolPosition);

    bool dimensionSeparateArrowBlocks() const;
    void setDimensionSeparateArrowBlocks(bool);

    double dimensionCenterMarkSize() const;
    void setDimensionCenterMarkSize(double);

    double dimensionTickSize() const;
    void setDimensionTickSize(double);

    Color dimensionLineColor() const;
    void setDimensionLineColor(const Color &);

    Color dimensionExtensionLineColor() const;
    void setDimensionExtensionLineColor(const Color &);

    Color dimensionTextColor() const;
    void setDimensionTextColor(const Color &);

    double dimensionLineExtension() const;
    void setDimensionLineExtension(double);

    double dimensionLineIncrement() const;
    void setDimensionLineIncrement(double);

    double dimensionExtensionLineExtension() const;
    void setDimensionExtensionLineExtension(double);

    bool dimensionIsExtensionLineLengthFixed() const;
    void setDimensionIsExtensionLineLengthFixed(bool);

    double dimensionFixedExtensionLineLength() const;
    void setDimensionFixedExtensionLineLength(double);

    double dimensionJoggedRadiusDimensionTransverseSegmentAngle() const;
    void setDimensionJoggedRadiusDimensionTransverseSegmentAngle(double);

    DimensionTextBackgroundFillMode dimensionTextBackgroundFillMode() const;
    void setDimensionTextBackgroundFillMode(DimensionTextBackgroundFillMode);

    Color dimensionTextBackgroundColor() const;
    void setDimensionTextBackgroundColor(const Color &);

    double dimensionLineGap() const;
    void setDimensionLineGap(double);

    double dimensionLinearScaleFactor() const;
    void setDimensionLinearScaleFactor(double);

    double dimensionTextVerticalPosition() const;
    void setDimensionTextVerticalPosition(double);

    LineweightType dimensionLineWeight() const;
    void setDimensionLineWeight(LineweightType);

    LineweightType extensionLineWeight() const;
    void setExtensionLineWeight(LineweightType);

    std::string dimensionPostFix() const;
    void setDimensionPostFix(const std::string &);

    double dimensionRounding() const;
    void setDimensionRounding(double);

    bool dimensionSuppressFirstExtensionLine() const;
    void setDimensionSuppressFirstExtensionLine(bool);

    bool dimensionSuppressSecondExtensionLine() const;
    void setDimensionSuppressSecondExtensionLine(bool);

    bool dimensionSuppressOutsideExtensions() const;
    void setDimensionSuppressOutsideExtensions(bool);

    DimensionTextVerticalAlignment dimensionTextVerticalAlignment() const;
    void setDimensionTextVerticalAlignment(DimensionTextVerticalAlignment);

    short dimensionUnit() const;
    void setDimensionUnit(short);

    double dimensionToleranceScaleFactor() const;
    void setDimensionToleranceScaleFactor(double);

    bool dimensionTextInsideHorizontal() const;
    void setDimensionTextInsideHorizontal(bool);

    bool dimensionTextInsideExtensions() const;
    void setDimensionTextInsideExtensions(bool);

    double dimensionMinusTolerance() const;
    void setDimensionMinusTolerance(double);

    bool dimensionTextOutsideExtensions() const;
    void setDimensionTextOutsideExtensions(bool);

    bool dimensionTextOutsideHorizontal() const;
    void setDimensionTextOutsideHorizontal(bool);

    bool dimensionLimitsGeneration() const;
    void setDimensionLimitsGeneration(bool);

    double dimensionPlusTolerance() const;
    void setDimensionPlusTolerance(double);

    double dimensionTextHeight() const;
    void setDimensionTextHeight(double);

    TextDirection dimensionTextDirection() const;
    void setDimensionTextDirection(TextDirection);

    double dimensionAltMzf() const;
    void setDimensionAltMzf(double);

    std::string dimensionAltMzs() const;
    void setDimensionAltMzs(const std::string &);

    double dimensionMzf() const;
    void setDimensionMzf(double);

    std::string dimensionMzs() const;
    void setDimensionMzs(const std::string &);

    std::string dimensionLineType() const;
    void setDimensionLineType(const std::string &);

    std::string dimensionTex1() const;
    void setDimensionTex1(const std::string &);

    std::string dimensionTex2() const;
    void setDimensionTex2(const std::string &);

    Layer *currentLayer() const;
    void setCurrentLayer(Layer *);

    LineType *currentLineType() const;
    void setCurrentLineType(LineType *);

    TextStyle *currentTextStyle() const;
    void setTextStyle(TextStyle *);

    TextStyle *dimensionTextStyle() const;
    void setDimensionTextStyle(TextStyle *);

    DimensionStyle *dimensionStyleOverrides() const;

    UCS *modelSpaceUcs() const;
    void setModelSpaceUcs(UCS *);

    UCS *modelSpaceUcsBase() const;
    void setModelSpaceUcsBase(UCS *);

    UCS *paperSpaceUcs() const;
    void setPaperSpaceUcs(UCS *);

    UCS *paperSpaceUcsBase() const;
    void setPaperSpaceUcsBase(UCS *);

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
    double _totalEditingTime;
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
    TextStyle *_currentTextStyle;
    TextStyle *_dimensionTextStyle;
    DimensionStyle *_dimensionStyleOverrides;
    UCS *_modelSpaceUcs;
    UCS *_modelSpaceUcsBase;
    UCS *_paperSpaceUcs;
    UCS *_paperSpaceUcsBase;
};

}// namespace dwg
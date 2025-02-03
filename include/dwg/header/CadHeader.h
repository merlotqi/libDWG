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

#include <cpl_ports.h>
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

namespace dwg {

class DG_UCS;
class DG_Layer;
class DG_LineType;
class DG_TextStyle;
class DG_DimensionStyle;
class DG_CadDocument;

class DG_CadHeaderPrivate;
class LIBDWG_API DG_CadHeader
{
    DG_CadHeaderPrivate *d;

public:
    DG_CadHeader();
    DG_CadHeader(DG_CadDocument *document);
    DG_CadHeader(DG_ACadVersion version);

    std::string VersionString() const;
    void VersionString(const std::string &);

    DG_ACadVersion Version() const;
    void Version(DG_ACadVersion);

    short MaintenanceVersion() const;
    void MaintenanceVersion(short);

    std::string CodePage() const;
    void CodePage(const std::string &);

    std::string LastSavedBy() const;
    void LastSavedBy(const std::string &);

    bool AssociatedDimensions() const;
    void AssociatedDimensions(bool);

    bool UpdateDimensionsWhileDragging() const;
    void UpdateDimensionsWhileDragging(bool);

    bool DIMSAV() const;
    void DIMSAV(bool);

    DG_MeasurementUnits MeasurementUnits() const;
    void MeasurementUnits(DG_MeasurementUnits);

    bool PolylineLineTypeGeneration() const;
    void PolylineLineTypeGeneration(bool);

    bool OrthoMode() const;
    void OrthoMode(bool);

    bool RegenerationMode() const;
    void RegenerationMode(bool);

    bool FillMode() const;
    void FillMode(bool);

    bool QuickTextMode() const;
    void QuickTextMode(bool);

    DG_SpaceLineTypeScaling PaperSpaceLineTypeScaling() const;
    void PaperSpaceLineTypeScaling(DG_SpaceLineTypeScaling);

    bool LimitCheckingOn() const;
    void LimitCheckingOn(bool);

    bool BlipMode() const;
    void BlipMode(bool);

    bool UserTimer() const;
    void UserTimer(bool);

    bool SketchPolylines() const;
    void SketchPolylines(bool);

    DG_AngularDirection AngularDirection() const;
    void AngularDirection(DG_AngularDirection);

    bool ShowSplineControlPoints() const;
    void ShowSplineControlPoints(bool);

    bool MirrorText() const;
    void MirrorText(bool);

    bool WorldView() const;
    void WorldView(bool);

    bool ShowModelSpace() const;
    void ShowModelSpace(bool);

    bool PaperSpaceLimitsChecking() const;
    void PaperSpaceLimitsChecking(bool);

    bool RetainXRefDependentVisibilitySettings() const;
    void RetainXRefDependentVisibilitySettings(bool);

    bool DisplaySilhouetteCurves() const;
    void DisplaySilhouetteCurves(bool);

    bool CreateEllipseAsPolyline() const;
    void CreateEllipseAsPolyline(bool);

    bool ProxyGraphics() const;
    void ProxyGraphics(bool);

    short SpatialIndexMaxTreeDepth() const;
    void SpatialIndexMaxTreeDepth(short);

    DG_LinearUnitFormat LinearUnitFormat() const;
    void LinearUnitFormat(DG_LinearUnitFormat);

    short LinearUnitPrecision() const;
    void LinearUnitPrecision(short);

    DG_AngularUnitFormat AngularUnit() const;
    void AngularUnit(DG_AngularUnitFormat);

    short AngularUnitPrecision() const;
    void AngularUnitPrecision(short);

    DG_ObjectSnapMode ObjectSnapMode() const;
    void ObjectSnapMode(DG_ObjectSnapMode);

    DG_AttributeVisibilityMode AttributeVisibility() const;
    void AttributeVisibility(DG_AttributeVisibilityMode);

    short PointDisplayMode() const;
    void PointDisplayMode(short);

    short UserShort1() const;
    void UserShort1(short);

    short UserShort2() const;
    void UserShort2(short);

    short UserShort3() const;
    void UserShort3(short);

    short UserShort4() const;
    void UserShort4(short);

    short UserShort5() const;
    void UserShort5(short);

    short NumberOfSplineSegments() const;
    void NumberOfSplineSegments(short);

    short SurfaceDensityU() const;
    void SurfaceDensityU(short);

    short SurfaceDensityV() const;
    void SurfaceDensityV(short);

    short SurfaceType() const;
    void SurfaceType(short);

    short SurfaceMeshTabulationCount1() const;
    void SurfaceMeshTabulationCount1(short);

    short SurfaceMeshTabulationCount2() const;
    void SurfaceMeshTabulationCount2(short);

    DG_SplineType SplineType() const;
    void SplineType(DG_SplineType);

    DG_ShadeEdgeType ShadeEdge() const;
    void ShadeEdge(DG_ShadeEdgeType);

    short ShadeDiffuseToAmbientPercentage() const;
    void ShadeDiffuseToAmbientPercentage(short);

    short UnitMode() const;
    void UnitMode(short);

    short MaxViewportCount() const;
    void MaxViewportCount(short);

    short SurfaceIsolineCount() const;
    void SurfaceIsolineCount(short);

    DG_VerticalAlignmentType CurrentMultilineJustification() const;
    void CurrentMultilineJustification(DG_VerticalAlignmentType);

    short TextQuality() const;
    void TextQuality(short);

    double LineTypeScale() const;
    void LineTypeScale(double);

    double TextHeightDefault() const;
    void TextHeightDefault(double);

    std::string TextStyleName() const;
    void TextStyleName(const std::string &);

    std::string CurrentLayerName() const;
    void CurrentLayerName(const std::string &);

    std::string CurrentLineTypeName() const;
    void CurrentLineTypeName(const std::string &);

    std::string MultiLineStyleName() const;
    void MultiLineStyleName(const std::string &);

    double TraceWidthDefault() const;
    void TraceWidthDefault(double);

    double SketchIncrement() const;
    void SketchIncrement(double);

    double FilletRadius() const;
    void FilletRadius(double);

    double ThicknessDefault() const;
    void ThicknessDefault(double);

    double AngleBase() const;
    void AngleBase(double);

    double PointDisplaySize() const;
    void PointDisplaySize(double);

    double PolylineWidthDefault() const;
    void PolylineWidthDefault(double);

    double UserDouble1() const;
    void UserDouble1(double);

    double UserDouble2() const;
    void UserDouble2(double);

    double UserDouble3() const;
    void UserDouble3(double);

    double UserDouble4() const;
    void UserDouble4(double);

    double UserDouble5() const;
    void UserDouble5(double);

    double ChamferDistance1() const;
    void ChamferDistance1(double);

    double ChamferDistance2() const;
    void ChamferDistance2(double);

    double ChamferLength() const;
    void ChamferLength(double);

    double ChamferAngle() const;
    void ChamferAngle(double);

    double FacetResolution() const;
    void FacetResolution(double);

    double CurrentMultilineScale() const;
    void CurrentMultilineScale(double);

    double CurrentEntityLinetypeScale() const;
    void CurrentEntityLinetypeScale(double);

    std::string MenuFileName() const;
    void MenuFileName(const std::string &);

    unsigned long long HandleSeed() const;
    void HandleSeed(unsigned long long);

    time_t CreateDateTime() const;
    void CreateDateTime(time_t);

    time_t UniversalCreateDateTime() const;
    void UniversalCreateDateTime(time_t);

    time_t UpdateDateTime() const;
    void UpdateDateTime(time_t);

    time_t UniversalUpdateDateTime() const;
    void UniversalUpdateDateTime(time_t);

    double TotalEditingTime() const;
    void TotalEditingTime(double);

    double UserElapsedTimeSpan() const;
    void UserElapsedTimeSpan(double);

    DG_Color CurrentEntityColor() const;
    void CurrentEntityColor(const DG_Color &);

    double ViewportDefaultViewScaleFactor() const;
    void ViewportDefaultViewScaleFactor(double);

    XYZ PaperSpaceInsertionBase() const;
    void PaperSpaceInsertionBase(const XYZ &);

    XYZ PaperSpaceExtMin() const;
    void PaperSpaceExtMin(const XYZ &);

    XYZ PaperSpaceExtMax() const;
    void PaperSpaceExtMax(const XYZ &);

    XY PaperSpaceLimitsMin() const;
    void PaperSpaceLimitsMin(const XYZ &);

    XY PaperSpaceLimitsMax() const;
    void PaperSpaceLimitsMax(const XY &);

    double PaperSpaceElevation() const;
    void PaperSpaceElevation(double);

    std::string PaperSpaceBaseName() const;
    void PaperSpaceBaseName(const std::string &);

    std::string PaperSpaceName() const;
    void PaperSpaceName(const std::string &);

    XYZ PaperSpaceUcsOrigin() const;
    void PaperSpaceUcsOrigin(const XYZ &);

    XYZ PaperSpaceUcsXAxis() const;
    void PaperSpaceUcsXAxis(const XYZ &);

    XYZ PaperSpaceUcsYAxis() const;
    void PaperSpaceUcsYAxis(const XYZ &);

    XYZ PaperSpaceOrthographicTopDOrigin() const;
    void PaperSpaceOrthographicTopDOrigin(const XYZ &);

    XYZ PaperSpaceOrthographicBottomDOrigin() const;
    void PaperSpaceOrthographicBottomDOrigin(const XYZ &);

    XYZ PaperSpaceOrthographicLeftDOrigin() const;
    void PaperSpaceOrthographicLeftDOrigin(const XYZ &);

    XYZ PaperSpaceOrthographicRightDOrigin() const;
    void PaperSpaceOrthographicRightDOrigin(const XYZ &);

    XYZ PaperSpaceOrthographicFrontDOrigin() const;
    void PaperSpaceOrthographicFrontDOrigin(const XYZ &);

    XYZ PaperSpaceOrthographicBackDOrigin() const;
    void PaperSpaceOrthographicBackDOrigin(const XYZ &);

    XYZ ModelSpaceOrthographicTopDOrigin() const;
    void ModelSpaceOrthographicTopDOrigin(const XYZ &);

    XYZ ModelSpaceOrthographicBottomDOrigin() const;
    void ModelSpaceOrthographicBottomDOrigin(const XYZ &);

    XYZ ModelSpaceOrthographicLeftDOrigin() const;
    void ModelSpaceOrthographicLeftDOrigin(const XYZ &);

    XYZ ModelSpaceOrthographicRightDOrigin() const;
    void ModelSpaceOrthographicRightDOrigin(const XYZ &);

    XYZ ModelSpaceOrthographicFrontDOrigin() const;
    void ModelSpaceOrthographicFrontDOrigin(const XYZ &);

    XYZ ModelSpaceOrthographicBackDOrigin() const;
    void ModelSpaceOrthographicBackDOrigin(const XYZ &);

    XYZ ModelSpaceInsertionBase() const;
    void ModelSpaceInsertionBase(const XYZ &);

    XYZ ModelSpaceExtMin() const;
    void ModelSpaceExtMin(const XYZ &);

    XYZ ModelSpaceExtMax() const;
    void ModelSpaceExtMax(const XYZ &);

    XY ModelSpaceLimitsMin() const;
    void ModelSpaceLimitsMin(const XY &);

    XY ModelSpaceLimitsMax() const;
    void ModelSpaceLimitsMax(const XY &);

    std::string UcsBaseName() const;
    void UcsBaseName(const std::string &);

    std::string UcsName() const;
    void UcsName(const std::string &);

    double Elevation() const;
    void Elevation(double);

    XYZ ModelSpaceOrigin() const;
    void ModelSpaceOrigin(const XYZ &);

    XYZ ModelSpaceXAxis() const;
    void ModelSpaceXAxis(const XYZ &);

    XYZ ModelSpaceYAxis() const;
    void ModelSpaceYAxis(const XYZ &);

    std::string DimensionBlockName() const;
    void DimensionBlockName(const std::string &);

    std::string ArrowBlockName() const;
    void ArrowBlockName(const std::string &);

    std::string DimensionBlockNameFirst() const;
    void DimensionBlockNameFirst(const std::string &);

    std::string DimensionBlockNameSecond() const;
    void DimensionBlockNameSecond(const std::string &);

    short StackedTextAlignment() const;
    void StackedTextAlignment(short);

    short StackedTextSizePercentage() const;
    void StackedTextSizePercentage(short);

    std::string HyperLinkBase() const;
    void HyperLinkBase(const std::string &);

    DG_LineweightType CurrentEntityLineWeight() const;
    void CurrentEntityLineWeight(DG_LineweightType);

    short EndCaps() const;
    void EndCaps(short);

    short JoinStyle() const;
    void JoinStyle(short);

    bool DisplayLineWeight() const;
    void DisplayLineWeight(bool);

    bool XEdit() const;
    void XEdit(bool);

    bool ExtendedNames() const;
    void ExtendedNames(bool);

    short PlotStyleMode() const;
    void PlotStyleMode(short);

    bool LoadOLEObject() const;
    void LoadOLEObject(bool);

    DG_UnitsType InsUnits() const;
    void InsUnits(DG_UnitsType);

    DG_EntityPlotStyleType CurrentEntityPlotStyle() const;
    void CurrentEntityPlotStyle(DG_EntityPlotStyleType);

    std::string FingerPrintGuid() const;
    void FingerPrintGuid(const std::string &);

    std::string VersionGuid() const;
    void VersionGuid(const std::string &);

    DG_ObjectSortingFlags EntitySortingFlags() const;
    void EntitySortingFlags(DG_ObjectSortingFlags);

    DG_IndexCreationFlags IndexCreationFlags() const;
    void IndexCreationFlags(DG_IndexCreationFlags);

    unsigned char HideText() const;
    void HideText(unsigned char);

    unsigned char ExternalReferenceClippingBoundaryType() const;
    void ExternalReferenceClippingBoundaryType(unsigned char);

    DG_DimensionAssociation DimensionAssociativity() const;
    void DimensionAssociativity(DG_DimensionAssociation);

    unsigned char HaloGapPercentage() const;
    void HaloGapPercentage(unsigned char);

    DG_Color ObscuredColor() const;
    void ObscuredColor(const DG_Color &);

    DG_Color InterfereColor() const;
    void InterfereColor(const DG_Color &);

    unsigned char ObscuredType() const;
    void ObscuredType(unsigned char);

    unsigned char IntersectionDisplay() const;
    void IntersectionDisplay(unsigned char);

    std::string ProjectName() const;
    void ProjectName(const std::string &);

    bool CameraDisplayObjects() const;
    void CameraDisplayObjects(bool);

    double StepsPerSecond() const;
    void StepsPerSecond(double);

    double StepSize() const;
    void StepSize(double);

    double Dw3DPrecision() const;
    void Dw3DPrecision(double);

    double LensLength() const;
    void LensLength(double);

    double CameraHeight() const;
    void CameraHeight(double);

    char SolidsRetainHistory() const;
    void SolidsRetainHistory(char);

    char ShowSolidsHistory() const;
    void ShowSolidsHistory(char);

    double SweptSolidWidth() const;
    void SweptSolidWidth(double);

    double SweptSolidHeight() const;
    void SweptSolidHeight(double);

    double DraftAngleFirstCrossSection() const;
    void DraftAngleFirstCrossSection(double);

    double DraftAngleSecondCrossSection() const;
    void DraftAngleSecondCrossSection(double);

    double DraftMagnitudeFirstCrossSection() const;
    void DraftMagnitudeFirstCrossSection(double);

    double DraftMagnitudeSecondCrossSection() const;
    void DraftMagnitudeSecondCrossSection(double);

    short SolidLoftedShape() const;
    void SolidLoftedShape(short);

    char LoftedObjectNormals() const;
    void LoftedObjectNormals(char);

    double Latitude() const;
    void Latitude(double);

    double Longitude() const;
    void Longitude(double);

    double NorthDirection() const;
    void NorthDirection(double);

    int TimeZone() const;
    void TimeZone(int);

    char DisplayLightGlyphs() const;
    void DisplayLightGlyphs(char);

    char DwgUnderlayFramesVisibility() const;
    void DwgUnderlayFramesVisibility(char);

    char DgnUnderlayFramesVisibility() const;
    void DgnUnderlayFramesVisibility(char);

    DG_ShadowMode ShadowMode() const;
    void ShadowMode(DG_ShadowMode);

    double ShadowPlaneLocation() const;
    void ShadowPlaneLocation(double);

    std::string StyleSheetName() const;
    void StyleSheetName(const std::string &);

    std::string DimensionTextStyleName() const;
    void DimensionTextStyleName(const std::string &);

    std::string DimensionStyleOverridesName() const;
    void DimensionStyleOverridesName(const std::string &);

    short DimensionAngularDimensionDecimalPlaces() const;
    void DimensionAngularDimensionDecimalPlaces(short);

    short DimensionDecimalPlaces() const;
    void DimensionDecimalPlaces(short);

    short DimensionToleranceDecimalPlaces() const;
    void DimensionToleranceDecimalPlaces(short);

    bool DimensionAlternateUnitDimensioning() const;
    void DimensionAlternateUnitDimensioning(bool);

    DG_LinearUnitFormat DimensionAlternateUnitFormat() const;
    void DimensionAlternateUnitFormat(DG_LinearUnitFormat);

    double DimensionAlternateUnitScaleFactor() const;
    void DimensionAlternateUnitScaleFactor(double);

    double DimensionExtensionLineOffset() const;
    void DimensionExtensionLineOffset(double);

    double DimensionScaleFactor() const;
    void DimensionScaleFactor(double);

    short DimensionAlternateUnitDecimalPlaces() const;
    void DimensionAlternateUnitDecimalPlaces(short);

    short DimensionAlternateUnitToleranceDecimalPlaces() const;
    void DimensionAlternateUnitToleranceDecimalPlaces(short);

    DG_AngularUnitFormat DimensionAngularUnit() const;
    void DimensionAngularUnit(DG_AngularUnitFormat);

    DG_FractionFormat DimensionFractionFormat() const;
    void DimensionFractionFormat(DG_FractionFormat);

    DG_LinearUnitFormat DimensionLinearUnitFormat() const;
    void DimensionLinearUnitFormat(DG_LinearUnitFormat);

    char DimensionDecimalSeparator() const;
    void DimensionDecimalSeparator(char);

    DG_TextMovement DimensionTextMovement() const;
    void DimensionTextMovement(DG_TextMovement);

    DG_DimensionTextHorizontalAlignment DimensionTextHorizontalAlignment() const;
    void DimensionTextHorizontalAlignment(DG_DimensionTextHorizontalAlignment);

    bool DimensionSuppressFirstDimensionLine() const;
    void DimensionSuppressFirstDimensionLine(bool);

    bool DimensionSuppressSecondDimensionLine() const;
    void DimensionSuppressSecondDimensionLine(bool);

    bool DimensionGenerateTolerances() const;
    void DimensionGenerateTolerances(bool);

    DG_ToleranceAlignment DimensionToleranceAlignment() const;
    void DimensionToleranceAlignment(DG_ToleranceAlignment);

    DG_ZeroHandling DimensionZeroHandling() const;
    void DimensionZeroHandling(DG_ZeroHandling);

    DG_ZeroHandling DimensionToleranceZeroHandling() const;
    void DimensionToleranceZeroHandling(DG_ZeroHandling);

    short DimensionFit() const;
    void DimensionFit(short);

    DG_ZeroHandling DimensionAlternateUnitZeroHandling() const;
    void DimensionAlternateUnitZeroHandling(DG_ZeroHandling);

    DG_ZeroHandling DimensionAlternateUnitToleranceZeroHandling() const;
    void DimensionAlternateUnitToleranceZeroHandling(DG_ZeroHandling);

    bool DimensionCursorUpdate() const;
    void DimensionCursorUpdate(bool);

    DG_TextArrowFitType DimensionDimensionTextArrowFit() const;
    void DimensionDimensionTextArrowFit(DG_TextArrowFitType);

    double DimensionAlternateUnitRounding() const;
    void DimensionAlternateUnitRounding(double);

    std::string DimensionAlternateDimensioningSuffix() const;
    void DimensionAlternateDimensioningSuffix(const std::string &);

    double DimensionArrowSize() const;
    void DimensionArrowSize(double);

    DG_ZeroHandling DimensionAngularZeroHandling() const;
    void DimensionAngularZeroHandling(DG_ZeroHandling);

    DG_ArcLengthSymbolPosition DimensionArcLengthSymbolPosition() const;
    void DimensionArcLengthSymbolPosition(DG_ArcLengthSymbolPosition);

    bool DimensionSeparateArrowBlocks() const;
    void DimensionSeparateArrowBlocks(bool);

    double DimensionCenterMarkSize() const;
    void DimensionCenterMarkSize(double);

    double DimensionTickSize() const;
    void DimensionTickSize(double);

    DG_Color DimensionLineColor() const;
    void DimensionLineColor(const DG_Color &);

    DG_Color DimensionExtensionLineColor() const;
    void DimensionExtensionLineColor(const DG_Color &);

    DG_Color DimensionTextColor() const;
    void DimensionTextColor(const DG_Color &);

    double DimensionLineExtension() const;
    void DimensionLineExtension(double);

    double DimensionLineIncrement() const;
    void DimensionLineIncrement(double);

    double DimensionExtensionLineExtension() const;
    void DimensionExtensionLineExtension(double);

    bool DimensionIsExtensionLineLengthFixed() const;
    void DimensionIsExtensionLineLengthFixed(bool);

    double DimensionFixedExtensionLineLength() const;
    void DimensionFixedExtensionLineLength(double);

    double DimensionJoggedRadiusDimensionTransverseSegmentAngle() const;
    void DimensionJoggedRadiusDimensionTransverseSegmentAngle(double);

    DG_DimensionTextBackgroundFillMode DimensionTextBackgroundFillMode() const;
    void DimensionTextBackgroundFillMode(DG_DimensionTextBackgroundFillMode);

    DG_Color DimensionTextBackgroundColor() const;
    void DimensionTextBackgroundColor(const DG_Color &);

    double DimensionLineGap() const;
    void DimensionLineGap(double);

    double DimensionLinearScaleFactor() const;
    void DimensionLinearScaleFactor(double);

    double DimensionTextVerticalPosition() const;
    void DimensionTextVerticalPosition(double);

    DG_LineweightType DimensionLineWeight() const;
    void DimensionLineWeight(DG_LineweightType);

    DG_LineweightType ExtensionLineWeight() const;
    void ExtensionLineWeight(DG_LineweightType);

    std::string DimensionPostFix() const;
    void DimensionPostFix(const std::string &);

    double DimensionRounding() const;
    void DimensionRounding(double);

    bool DimensionSuppressFirstExtensionLine() const;
    void DimensionSuppressFirstExtensionLine(bool);

    bool DimensionSuppressSecondExtensionLine() const;
    void DimensionSuppressSecondExtensionLine(bool);

    bool DimensionSuppressOutsideExtensions() const;
    void DimensionSuppressOutsideExtensions(bool);

    DG_DimensionTextVerticalAlignment DimensionTextVerticalAlignment() const;
    void DimensionTextVerticalAlignment(DG_DimensionTextVerticalAlignment);

    short DimensionUnit() const;
    void DimensionUnit(short);

    double DimensionToleranceScaleFactor() const;
    void DimensionToleranceScaleFactor(double);

    bool DimensionTextInsideHorizontal() const;
    void DimensionTextInsideHorizontal(bool);

    bool DimensionTextInsideExtensions() const;
    void DimensionTextInsideExtensions(bool);

    double DimensionMinusTolerance() const;
    void DimensionMinusTolerance(double);

    bool DimensionTextOutsideExtensions() const;
    void DimensionTextOutsideExtensions(bool);

    bool DimensionTextOutsideHorizontal() const;
    void DimensionTextOutsideHorizontal(bool);

    bool DimensionLimitsGeneration() const;
    void DimensionLimitsGeneration();

    double DimensionPlusTolerance() const;
    void DimensionPlusTolerance(double);

    double DimensionTextHeight() const;
    void DimensionTextHeight(double);

    DG_TextDirection DimensionTextDirection() const;
    void DimensionTextDirection(DG_TextDirection);

    double DimensionAltMzf() const;
    void DimensionAltMzf(double);

    std::string DimensionAltMzs() const;
    void DimensionAltMzs(const std::string &);

    double DimensionMzf() const;
    void DimensionMzf(double);

    std::string DimensionMzs() const;
    void DimensionMzs(const std::string &);

    std::string DimensionLineType() const;
    void DimensionLineType(const std::string &);

    std::string DimensionTex1() const;
    void DimensionTex1(const std::string &);

    std::string DimensionTex2() const;
    void DimensionTex2(const std::string &);

    DG_Layer *CurrentLayer() const;
    void CurrentLayer(DG_Layer *);

    DG_LineType *CurrentLineType() const;
    void CurrentLineType(DG_LineType *);

    DG_TextStyle *CurrentTextStyle() const;
    void TextStyle(DG_TextStyle *);

    DG_TextStyle *DimensionTextStyle() const;
    void DimensionTextStyle(DG_TextStyle *);

    DG_DimensionStyle *DimensionStyleOverrides() const;
    void DimensionStyleOverrides(DG_DimensionStyle *);

    DG_UCS *ModelSpaceUcs() const;
    void ModelSpaceUcs(DG_UCS *);

    DG_UCS *ModelSpaceUcsBase() const;
    void ModelSpaceUcsBase(DG_UCS *);

    DG_UCS *PaperSpaceUcs() const;
    void PaperSpaceUcs(DG_UCS *);

    DG_UCS *PaperSpaceUcsBase() const;
    void PaperSpaceUcsBase(DG_UCS *);
};

}// namespace dwg

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

class UCS;
CPL_SMARTER_PTR(UCS);
class Layer;
CPL_SMARTER_PTR(Layer);
class LineType;
CPL_SMARTER_PTR(LineType);
class TextStyle;
CPL_SMARTER_PTR(TextStyle);
class DimensionStyle;
CPL_SMARTER_PTR(DimensionStyle);

class CadDocument;
class CadHeaderPrivate;
class LIBDWG_API CadHeader : public CPL::RefObject
{
    CadHeaderPrivate *d;

public:
    CadHeader();
    CadHeader(CadDocument *document);
    CadHeader(ACadVersion version);

    CPL::String VersionString() const;
    void VersionString(const char *);

    ACadVersion Version() const;
    void Version(ACadVersion);

    short MaintenanceVersion() const;
    void MaintenanceVersion(short);

    CPL::String CodePage() const;
    void CodePage(const char *);

    CPL::String LastSavedBy() const void LastSavedBy(const char *);

    bool AssociatedDimensions() const;
    void AssociatedDimensions(bool);

    bool UpdateDimensionsWhileDragging() const;
    void UpdateDimensionsWhileDragging(bool);

    bool DIMSAV() const;
    void DIMSAV(bool);

    dwg::MeasurementUnits MeasurementUnits() const;
    void MeasurementUnits(dwg::MeasurementUnits);

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

    SpaceLineTypeScaling PaperSpaceLineTypeScaling() const;
    void PaperSpaceLineTypeScaling(SpaceLineTypeScaling);

    bool LimitCheckingOn() const;
    void LimitCheckingOn(bool);

    bool BlipMode() const;
    void BlipMode(bool);

    bool UserTimer() const;
    void UserTimer(bool);

    bool SketchPolylines() const;
    void SketchPolylines(bool);

    dwg::AngularDirection AngularDirection() const;
    void AngularDirection(dwg::AngularDirection);

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

    dwg::LinearUnitFormat LinearUnitFormat() const;
    void LinearUnitFormat(dwg::LinearUnitFormat);

    short LinearUnitPrecision() const;
    void LinearUnitPrecision(short);

    AngularUnitFormat AngularUnit() const;
    void AngularUnit(AngularUnitFormat);

    short AngularUnitPrecision() const;
    void AngularUnitPrecision(short);

    dwg::ObjectSnapMode ObjectSnapMode() const;
    void ObjectSnapMode(dwg::ObjectSnapMode);

    AttributeVisibilityMode AttributeVisibility() const;
    void AttributeVisibility(AttributeVisibilityMode);

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

    dwg::SplineType SplineType() const;
    void SplineType(dwg::SplineType);

    ShadeEdgeType ShadeEdge() const;
    void ShadeEdge(ShadeEdgeType);

    short ShadeDiffuseToAmbientPercentage() const;
    void ShadeDiffuseToAmbientPercentage(short);

    short UnitMode() const;
    void UnitMode(short);

    short MaxViewportCount() const;
    void MaxViewportCount(short);

    short SurfaceIsolineCount() const;
    void SurfaceIsolineCount(short);

    VerticalAlignmentType CurrentMultilineJustification() const;
    void CurrentMultilineJustification(VerticalAlignmentType);

    short TextQuality() const;
    void TextQuality(short);

    double LineTypeScale() const;
    void LineTypeScale(double);

    double TextHeightDefault() const;
    void TextHeightDefault(double);

    CPL::String TextStyleName() const;
    void TextStyleName(const char *);

    CPL::String CurrentLayerName() const;
    void CurrentLayerName(const char *);

    CPL::String CurrentLineTypeName() const;
    void CurrentLineTypeName(const char *);

    CPL::String MultiLineStyleName() const;
    void MultiLineStyleName(const char *);

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

    CPL::String MenuFileName() const;
    void MenuFileName(const char *);

    unsigned long long HandleSeed() const;
    void HandleSeed(unsigned long long);

    CPL::DateTime CreateDateTime() const;
    void CreateDateTime(CPL::DateTime);

    CPL::DateTime UniversalCreateDateTime() const;
    void UniversalCreateDateTime(CPL::DateTime);

    CPL::DateTime UpdateDateTime() const;
    void UpdateDateTime(CPL::DateTime);

    CPL::DateTime UniversalUpdateDateTime() const;
    void UniversalUpdateDateTime(CPL::DateTime);

    CPL::Timespan TotalEditingTime() const;
    void TotalEditingTime(CPL::Timespan);

    CPL::Timespan UserElapsedTimeSpan() const;
    void UserElapsedTimeSpan(CPL::Timespan);

    Color CurrentEntityColor() const;
    void CurrentEntityColor(const Color &);

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

    CPL::String PaperSpaceBaseName() const;
    void PaperSpaceBaseName(const char *);

    CPL::String PaperSpaceName() const;
    void PaperSpaceName(const char *);

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

    CPL::String UcsBaseName() const;
    void UcsBaseName(const char *);

    CPL::String UcsName() const;
    void UcsName(const char *);

    double Elevation() const;
    void Elevation(double);

    XYZ ModelSpaceOrigin() const;
    void ModelSpaceOrigin(const XYZ &);

    XYZ ModelSpaceXAxis() const;
    void ModelSpaceXAxis(const XYZ &);

    XYZ ModelSpaceYAxis() const;
    void ModelSpaceYAxis(const XYZ &);

    CPL::String DimensionBlockName() const;
    void DimensionBlockName(const char *);

    CPL::String ArrowBlockName() const;
    void ArrowBlockName(const char *);

    CPL::String DimensionBlockNameFirst() const;
    void DimensionBlockNameFirst(const char *);

    CPL::String DimensionBlockNameSecond() const;
    void DimensionBlockNameSecond(const char *);

    short StackedTextAlignment() const;
    void StackedTextAlignment(short);

    short StackedTextSizePercentage() const;
    void StackedTextSizePercentage(short);

    CPL::String HyperLinkBase() const;
    void HyperLinkBase(const char *);

    LineweightType CurrentEntityLineWeight() const;
    void CurrentEntityLineWeight(LineweightType);

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

    UnitsType InsUnits() const;
    void InsUnits(UnitsType);

    EntityPlotStyleType CurrentEntityPlotStyle() const;
    void CurrentEntityPlotStyle(EntityPlotStyleType);

    CPL::String FingerPrintGuid() const;
    void FingerPrintGuid(const char *);

    CPL::String VersionGuid() const;
    void VersionGuid(const char *);

    ObjectSortingFlags EntitySortingFlags() const;
    void EntitySortingFlags(ObjectSortingFlags);

    dwg::IndexCreationFlags IndexCreationFlags() const;
    void IndexCreationFlags(dwg::IndexCreationFlags);

    unsigned char HideText() const;
    void HideText(unsigned char);

    unsigned char ExternalReferenceClippingBoundaryType() const;
    void ExternalReferenceClippingBoundaryType(unsigned char);

    DimensionAssociation DimensionAssociativity() const;
    void DimensionAssociativity(DimensionAssociation);

    unsigned char HaloGapPercentage() const;
    void HaloGapPercentage(unsigned char);

    Color ObscuredColor() const;
    void ObscuredColor(const Color &);

    Color InterfereColor() const;
    void InterfereColor(const Color &);

    unsigned char ObscuredType() const;
    void ObscuredType(unsigned char);

    unsigned char IntersectionDisplay() const;
    void IntersectionDisplay(unsigned char);

    CPL::String ProjectName() const;
    void ProjectName(const char *);

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

    dwg::ShadowMode ShadowMode() const;
    void ShadowMode(dwg::ShadowMode);

    double ShadowPlaneLocation() const;
    void ShadowPlaneLocation(double);

    CPL::String StyleSheetName() const;
    void StyleSheetName(const char *);

    CPL::String DimensionTextStyleName() const;
    void DimensionTextStyleName(const char *);

    CPL::String DimensionStyleOverridesName() const;
    void DimensionStyleOverridesName(const char *);

    short DimensionAngularDimensionDecimalPlaces() const;
    void DimensionAngularDimensionDecimalPlaces(short);

    short DimensionDecimalPlaces() const;
    void DimensionDecimalPlaces(short);

    short DimensionToleranceDecimalPlaces() const;
    void DimensionToleranceDecimalPlaces(short);

    bool DimensionAlternateUnitDimensioning() const;
    void DimensionAlternateUnitDimensioning(bool);

    LinearUnitFormat DimensionAlternateUnitFormat() const;
    void DimensionAlternateUnitFormat(LinearUnitFormat);

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

    AngularUnitFormat DimensionAngularUnit() const;
    void DimensionAngularUnit(AngularUnitFormat);

    FractionFormat DimensionFractionFormat() const;
    void DimensionFractionFormat(FractionFormat);

    LinearUnitFormat DimensionLinearUnitFormat() const;
    void DimensionLinearUnitFormat(LinearUnitFormat);

    char DimensionDecimalSeparator() const;
    void DimensionDecimalSeparator(char);

    TextMovement DimensionTextMovement() const;
    void DimensionTextMovement(TextMovement);

    dwg::DimensionTextHorizontalAlignment
    DimensionTextHorizontalAlignment() const;
    void DimensionTextHorizontalAlignment(
            dwg::DimensionTextHorizontalAlignment);

    bool DimensionSuppressFirstDimensionLine() const;
    void DimensionSuppressFirstDimensionLine(bool);

    bool DimensionSuppressSecondDimensionLine() const;
    void DimensionSuppressSecondDimensionLine(bool);

    bool DimensionGenerateTolerances() const;
    void DimensionGenerateTolerances(bool);

    ToleranceAlignment DimensionToleranceAlignment() const;
    void DimensionToleranceAlignment(ToleranceAlignment);

    ZeroHandling DimensionZeroHandling() const;
    void DimensionZeroHandling(ZeroHandling);

    ZeroHandling DimensionToleranceZeroHandling() const;
    void DimensionToleranceZeroHandling(ZeroHandling);

    short DimensionFit() const;
    void DimensionFit(short);

    ZeroHandling DimensionAlternateUnitZeroHandling() const;
    void DimensionAlternateUnitZeroHandling(ZeroHandling);

    ZeroHandling DimensionAlternateUnitToleranceZeroHandling() const;
    void DimensionAlternateUnitToleranceZeroHandling(ZeroHandling);

    bool DimensionCursorUpdate() const;
    void DimensionCursorUpdate(bool);

    TextArrowFitType DimensionDimensionTextArrowFit() const;
    void DimensionDimensionTextArrowFit(TextArrowFitType);

    double DimensionAlternateUnitRounding() const;
    void DimensionAlternateUnitRounding(double);

    CPL::String DimensionAlternateDimensioningSuffix() const;
    void DimensionAlternateDimensioningSuffix(const char *);

    double DimensionArrowSize() const;
    void DimensionArrowSize(double);

    ZeroHandling DimensionAngularZeroHandling() const;
    void DimensionAngularZeroHandling(ZeroHandling);

    ArcLengthSymbolPosition DimensionArcLengthSymbolPosition() const;
    void DimensionArcLengthSymbolPosition(ArcLengthSymbolPosition);

    bool DimensionSeparateArrowBlocks() const;
    void DimensionSeparateArrowBlocks(bool);

    double DimensionCenterMarkSize() const;
    void DimensionCenterMarkSize(double);

    double DimensionTickSize() const;
    void DimensionTickSize(double);

    Color DimensionLineColor() const;
    void DimensionLineColor(const Color &);

    Color DimensionExtensionLineColor() const;
    void DimensionExtensionLineColor(const Color &);

    Color DimensionTextColor() const;
    void DimensionTextColor(const Color &);

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

    dwg::DimensionTextBackgroundFillMode
    DimensionTextBackgroundFillMode() const;
    void DimensionTextBackgroundFillMode(dwg::DimensionTextBackgroundFillMode);

    Color DimensionTextBackgroundColor() const;
    void DimensionTextBackgroundColor(const Color &);

    double DimensionLineGap() const;
    void DimensionLineGap(double);

    double DimensionLinearScaleFactor() const;
    void DimensionLinearScaleFactor(double);

    double DimensionTextVerticalPosition() const;
    void DimensionTextVerticalPosition(double);

    LineweightType DimensionLineWeight() const;
    void DimensionLineWeight(LineweightType);

    LineweightType ExtensionLineWeight() const;
    void ExtensionLineWeight(LineweightType);

    CPL::String DimensionPostFix() const;
    void DimensionPostFix(const char *);

    double DimensionRounding() const;
    void DimensionRounding(double);

    bool DimensionSuppressFirstExtensionLine() const;
    void DimensionSuppressFirstExtensionLine(bool);

    bool DimensionSuppressSecondExtensionLine() const;
    void DimensionSuppressSecondExtensionLine(bool);

    bool DimensionSuppressOutsideExtensions() const;
    void DimensionSuppressOutsideExtensions(bool);

    dwg::DimensionTextVerticalAlignment DimensionTextVerticalAlignment() const;
    void DimensionTextVerticalAlignment(dwg::DimensionTextVerticalAlignment);

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

    TextDirection DimensionTextDirection() const;
    void DimensionTextDirection(TextDirection);

    double DimensionAltMzf() const;
    void DimensionAltMzf(double);

    CPL::String DimensionAltMzs() const;
    void DimensionAltMzs(const char *);

    double DimensionMzf() const;
    void DimensionMzf(double);

    CPL::String DimensionMzs() const;
    void DimensionMzs(const char *);

    CPL::String DimensionLineType() const;
    void DimensionLineType(const char *);

    CPL::String DimensionTex1() const;
    void DimensionTex1(const char *);

    CPL::String DimensionTex2() const;
    void DimensionTex2(const char *);

    LayerPtr CurrentLayer() const;
    void CurrentLayer(Layer *);

    LineTypePtr CurrentLineType() const;
    void CurrentLineType(LineType *);

    TextStylePtr CurrentTextStyle() const;
    void TextStyle(TextStyle *);

    TextStylePtr DimensionTextStyle() const;
    void DimensionTextStyle(TextStyle *);

    DimensionStylePtr DimensionStyleOverrides() const;
    void DimensionStyleOverrides(DimensionStyle *);

    UCSPtr ModelSpaceUcs() const;
    void ModelSpaceUcs(UCS *);

    UCSPtr ModelSpaceUcsBase() const;
    void ModelSpaceUcsBase(UCS *);

    UCSPtr PaperSpaceUcs() const;
    void PaperSpaceUcs(UCS *);

    UCSPtr PaperSpaceUcsBase() const;
    void PaperSpaceUcsBase(UCS *);
};
CPL_SMARTER_PTR(CadHeader)

}// namespace dwg

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
#include <dwg/tables/UCS.h>
#include <dwg/tables/ZeroHandling.h>
#include <dwg/units/AngularDirection.h>
#include <dwg/units/AngularUnitFormat.h>
#include <dwg/units/LinearUnitFormat.h>
#include <dwg/units/UnitsType.h>

namespace dwg {

class CadDocument;
class CadHeaderPrivate;
class LIBDWG_API CadHeader : public CPL::RefObject
{
    CadHeaderPrivate *d;
public:
    CadHeader();
    CadHeader(CadDocument *document);
    CadHeader(ACadVersion version);

    CPL::String VersionString;

    ACadVersion Version;

    // "$ACADMAINTVER", 70
    short MaintenanceVersion;
    // "$DWGCODEPAGE", 3
    CPL::String CodePage;// "ANSI_1252"
    // "$LASTSAVEDBY", 3
    CPL::String LastSavedBy;// "libDWG"
    // "$REQUIREDVERSIONS", 70
    bool AssociatedDimensions;
    // "$DIMSHO", 70
    bool UpdateDimensionsWhileDragging;

    bool DIMSAV;

    // "$MEASUREMENT", 70
    MeasurementUnits MeasurementUnits;
    // "$PLINEGEN", 70
    bool PolylineLineTypeGeneration;
    // "$ORTHOMODE", 70
    bool OrthoMode;
    // "$REGENMODE", 70
    bool RegenerationMode;
    // "$FILLMODE", 70
    bool FillMode;
    // "$QTEXTMODE", 70
    bool QuickTextMode;
    SpaceLineTypeScaling PaperSpaceLineTypeScaling =
            SpaceLineTypeScaling::Normal;
    // "$PSLTSCALE", 70
    bool LimitCheckingOn;
    // "$BLIPMODE", 70
    bool BlipMode;
    // "$USRTIMER", 70
    bool UserTimer;
    // "$SKPOLY", 70
    bool SketchPolylines;
    // "$ANGDIR", 70
    AngularDirection AngularDirection;
    // "$SPLFRAME", 70
    bool ShowSplineControlPoints;
    // "$MIRRTEXT", 70
    bool MirrorText;
    // "$WORLDVIEW", 70
    bool WorldView;
    // "$TILEMODE", 70
    bool ShowModelSpace;
    // "$PLIMCHECK", 70
    bool PaperSpaceLimitsChecking;
    // "$VISRETAIN", 70
    bool RetainXRefDependentVisibilitySettings;
    // "$DISPSILH", 70
    bool DisplaySilhouetteCurves;


    bool CreateEllipseAsPolyline;

    // "$PROXYGRAPHICS", 70
    bool ProxyGraphics;
    // "$TREEDEPTH", 70
    short SpatialIndexMaxTreeDepth;
    // "$LUNITS", 70
    LinearUnitFormat linearUnitFormat;
    // "$LUPREC", 70
    short LinearUnitPrecision;
    // "$AUNITS", 70
    AngularUnitFormat AngularUnit;
    // "$AUPREC", 70
    short AngularUnitPrecision;


    ObjectSnapMode ObjectSnapMode;
    // "$ATTMODE", 70
    AttributeVisibilityMode AttributeVisibility;
    // "$PDMODE", 70
    short PointDisplayMode;
    // "$USERI1", 70
    short UserShort1;
    // "$USERI2", 70
    short UserShort2;
    // "$USERI3", 70
    short UserShort3;
    // "$USERI4", 70
    short UserShort4;
    // "$USERI5", 70
    short UserShort5;
    // "$SPLINESEGS", 70
    short NumberOfSplineSegments = 8;
    // "$SURFU", 70
    short SurfaceDensityU;
    // "$SURFV", 70
    short SurfaceDensityV;
    // "$SURFTYPE", 70
    short SurfaceType;
    // "$SURFTAB1", 70
    short SurfaceMeshTabulationCount1;
    // "$SURFTAB2", 70
    short SurfaceMeshTabulationCount2;
    // "$SPLINETYPE", 70
    SplineType SplineType;
    // "$SHADEDGE", 70
    ShadeEdgeType ShadeEdge;
    // "$SHADEDIF", 70
    short ShadeDiffuseToAmbientPercentage;
    // "$UNITMODE", 70
    short UnitMode;
    // "$MAXACTVP", 70
    short MaxViewportCount;

    short SurfaceIsolineCount;

    // "$CMLJUST", 70
    VerticalAlignmentType CurrentMultilineJustification;

    short TextQuality;

    // "$LTSCALE", 40
    double LineTypeScale = 1.0;

    // "$TEXTSIZE", 40
    double TextHeightDefault = 2.5;

    // "$TEXTSTYLE", true, 7
    CPL::String TextStyleName;

    // "$CLAYER", true, 8
    CPL::String CurrentLayerName;

    // "$CELTYPE", true, 6
    CPL::String CurrentLineTypeName;

    // "$CMLSTYLE", true, 2
    CPL::String MultiLineStyleName = "Standard";

    // "$TRACEWID", 40
    double TraceWidthDefault = 0;

    // "$SKETCHINC", 40
    double SketchIncrement;
    // "$FILLETRAD", 40
    double FilletRadius;
    // "$THICKNESS", 40
    double ThicknessDefault;
    // "$ANGBASE", 50
    double AngleBase = 0.0;
    // "$PDSIZE", 40
    double PointDisplaySize = 0.0;
    // "$PLINEWID", 40
    double PolylineWidthDefault;
    // "$USERR1", 40
    double UserDouble1;
    // "$USERR2", 40
    double UserDouble2;
    // "$USERR3", 40
    double UserDouble3;
    // "$USERR4", 40
    double UserDouble4;
    // "$USERR5", 40
    double UserDouble5;
    // "$CHAMFERA", 40
    double ChamferDistance1;
    // "$CHAMFERB", 40
    double ChamferDistance2;
    // "$CHAMFERC", 40
    double ChamferLength;
    // "$CHAMFERD", 40
    double ChamferAngle;

    double FacetResolution;

    // "$CMLSCALE", 40
    double CurrentMultilineScale = 20.0;
    // "$CELTSCALE", 40
    double CurrentEntityLinetypeScale = 1.0;
    // "$MENU", 1
    CPL::String MenuFileName = ".";
    // "$HANDSEED", 5
    unsigned long long HandleSeed = 0x0;
    // "$TDCREATE", 40
    CPL::DateTime CreateDateTime;

    // "$TDUCREATE", 40
    CPL::DateTime UniversalCreateDateTime;
    // "$TDUPDATE", 40
    CPL::DateTime UpdateDateTime;
    // "$TDUUPDATE", 40
    CPL::DateTime UniversalUpdateDateTime;
    // "$TDINDWG", 40
    CPL::Timespan TotalEditingTime;
    // "$TDUSRTIMER", 40
    CPL::Timespan UserElapsedTimeSpan;
    // "$CECOLOR", 62
    Color CurrentEntityColor = Color::ByLayer;
    // "$PSVPSCALE", 40
    double ViewportDefaultViewScaleFactor;
    // "$PINSBASE", 10, 20, 30
    XYZ PaperSpaceInsertionBase = XYZ::Zero;
    // "$PEXTMIN", 10, 20, 30
    XYZ PaperSpaceExtMin;
    // "$PEXTMAX", 10, 20, 30
    XYZ PaperSpaceExtMax;
    // "$PLIMMIN", 10, 20
    XY PaperSpaceLimitsMin;
    // "$PLIMMAX", 10, 20
    XY PaperSpaceLimitsMax;
    // "$PELEVATION", 40
    double PaperSpaceElevation;
    // "$PUCSBASE", true, 2
    CPL::String PaperSpaceBaseName;
    // "$PUCSNAME", true, 2
    CPL::String PaperSpaceName;
    // "$PUCSORG", 10, 20, 30
    XYZ PaperSpaceUcsOrigin;
    // "$PUCSXDIR", 10, 20, 30
    XYZ PaperSpaceUcsXAxis;
    // "$PUCSYDIR", 10, 20, 30
    XYZ PaperSpaceUcsYAxis;
    // "$PUCSORGTOP", 10, 20, 30
    XYZ PaperSpaceOrthographicTopDOrigin;
    // "$PUCSORGBOTTOM", 10, 20, 30
    XYZ PaperSpaceOrthographicBottomDOrigin;
    // "$PUCSORGLEFT", 10, 20, 30
    XYZ PaperSpaceOrthographicLeftDOrigin;
    // "$PUCSORGRIGHT", 10, 20, 30
    XYZ PaperSpaceOrthographicRightDOrigin;
    // "$PUCSORGFRONT", 10, 20, 30
    XYZ PaperSpaceOrthographicFrontDOrigin;
    // "$PUCSORGBACK", 10, 20, 30
    XYZ PaperSpaceOrthographicBackDOrigin;
    // "$UCSORGTOP", 10, 20, 30
    XYZ ModelSpaceOrthographicTopDOrigin;
    // "$UCSORGBOTTOM", 10, 20, 30
    XYZ ModelSpaceOrthographicBottomDOrigin;
    // "$UCSORGLEFT", 10, 20, 30
    XYZ ModelSpaceOrthographicLeftDOrigin;
    // "$UCSORGRIGHT", 10, 20, 30
    XYZ ModelSpaceOrthographicRightDOrigin;
    // "$UCSORGFRONT", 10, 20, 30
    XYZ ModelSpaceOrthographicFrontDOrigin;
    // "$UCSORGBACK", 10, 20, 30
    XYZ ModelSpaceOrthographicBackDOrigin;
    // "$INSBASE", 10, 20, 30
    XYZ ModelSpaceInsertionBase = XYZ::Zero;
    // "$EXTMIN", 10, 20, 30
    XYZ ModelSpaceExtMin;
    // "$EXTMAX", 10, 20, 30
    XYZ ModelSpaceExtMax;
    // "$LIMMIN", 10, 20
    XY ModelSpaceLimitsMin;
    // "$LIMMAX", 10, 20
    XY ModelSpaceLimitsMax;
    // "$UCSBASE", true, 2
    CPL::String UcsBaseName;
    // "$UCSNAME", true, 2
    CPL::String UcsName;
    // "$ELEVATION", 40
    double Elevation;
    // "$UCSORG", 10, 20, 30
    XYZ ModelSpaceOrigin;
    // "$UCSXDIR", 10, 20, 30
    XYZ ModelSpaceXAxis;
    // "$UCSYDIR", 10, 20, 30
    XYZ ModelSpaceYAxis;
    // "$DIMBLK", 1
    CPL::String DimensionBlockName;
    // "$DIMLDRBLK", 1
    CPL::String ArrowBlockName;
    // "$DIMBLK1", 1
    CPL::String DimensionBlockNameFirst;
    // "$DIMBLK2", 1
    CPL::String DimensionBlockNameSecond;


    short StackedTextAlignment = 1;
    short StackedTextSizePercentage = 70;


    // "$HYPERLINKBASE", 1
    CPL::String HyperLinkBase;
    // "$CELWEIGHT", 370
    LineweightType CurrentEntityLineWeight = LineweightType::ByLayer;
    // "$ENDCAPS", 280
    short EndCaps;
    // "$JOINSTYLE", 280
    short JoinStyle;
    // "$LWDISPLAY", 290
    bool DisplayLineWeight = false;
    // "$XEDIT", 290
    bool XEdit;
    // "$EXTNAMES", 290
    bool ExtendedNames = true;
    // "$PSTYLEMODE", 290
    short PlotStyleMode;
    //[CadSystemVariable("$OLESTARTUP", 290
    bool LoadOLEObject;
    // "$INSUNITS", 70
    UnitsType InsUnits = UnitsType::Unitless;
    // "$CEPSNTYPE", 380
    EntityPlotStyleType CurrentEntityPlotStyle;
    // "$FINGERPRINTGUID", 2
    CPL::String FingerPrintGuid;
    // "$VERSIONGUID", 2
    CPL::String VersionGuid;

    // "$SORTENTS", 280
    ObjectSortingFlags EntitySortingFlags;
    // "$INDEXCTL", 280
    IndexCreationFlags IndexCreationFlags;
    // "$HIDETEXT", 280   //note: mismatch with docs, code 290
    unsigned char HideText;
    // "$XCLIPFRAME", 280 //note: mismatch with docs, code 290
    unsigned char ExternalReferenceClippingBoundaryType;
    // "$DIMASSOC", 280
    DimensionAssociation DimensionAssociativity;
    // "$HALOGAP", 280
    unsigned char HaloGapPercentage;

    Color ObscuredColor;
    // "$INTERFERECOLOR", 62
    Color InterfereColor;

    unsigned char ObscuredType;

    unsigned char IntersectionDisplay;
    // "$PROJECTNAME", 1
    CPL::String ProjectName;

    bool CameraDisplayObjects;
    double StepsPerSecond;
    double StepSize;
    double Dw3DPrecision;
    double LensLength;
    double CameraHeight;
    char SolidsRetainHistory;
    char ShowSolidsHistory;
    double SweptSolidWidth;
    double SweptSolidHeight;
    double DraftAngleFirstCrossSection;
    double DraftAngleSecondCrossSection;
    double DraftMagnitudeFirstCrossSection;
    double DraftMagnitudeSecondCrossSection;
    short SolidLoftedShape;
    char LoftedObjectNormals;

    // "$LATITUDE", 40
    double Latitude = 37.7950;
    // "$LONGITUDE", 40
    double Longitude = -122.394;
    // "$NORTHDIRECTION", 40
    double NorthDirection;
    // "$TIMEZONE", 70
    int TimeZone;

    char DisplayLightGlyphs;
    // "$DWFFRAME", 280
    char DwgUnderlayFramesVisibility;

    // "$DGNFRAME", 280
    char DgnUnderlayFramesVisibility;

    // "$CSHADOW", 280
    ShadowMode ShadowMode;

    // "$SHADOWPLANELOCATION", 40
    double ShadowPlaneLocation;

    CPL::String StyleSheetName;

    // "$DIMTXSTY", true, 7
    CPL::String DimensionTextStyleName;
    // "$DIMSTYLE", true, 2
    CPL::String DimensionStyleOverridesName;
    // "$DIMADEC", 70
    short DimensionAngularDimensionDecimalPlaces;
    // "$DIMDEC", 70
    short DimensionDecimalPlaces;
    // "$DIMTDEC", 70
    short DimensionToleranceDecimalPlaces;
    // "$DIMALT", 70
    bool DimensionAlternateUnitDimensioning;
    // "$DIMALTU", 70
    LinearUnitFormat DimensionAlternateUnitFormat;
    // "$DIMALTF", 40
    double DimensionAlternateUnitScaleFactor;
    // "$DIMEXO", 40
    double DimensionExtensionLineOffset;
    // "$DIMSCALE", 40
    double DimensionScaleFactor;
    // "$DIMALTD", 70
    short DimensionAlternateUnitDecimalPlaces;
    // "$DIMALTTD", 70
    short DimensionAlternateUnitToleranceDecimalPlaces;
    // "$DIMAUNIT", 70
    AngularUnitFormat DimensionAngularUnit;
    // "$DIMFRAC", 70
    FractionFormat DimensionFractionFormat;
    // "$DIMLUNIT", 70
    LinearUnitFormat DimensionLinearUnitFormat;
    // "$DIMDSEP", 70
    char DimensionDecimalSeparator;
    // "$DIMTMOVE", 70
    TextMovement DimensionTextMovement;
    // "$DIMJUST", 70
    DimensionTextHorizontalAlignment DimensionTextHorizontalAlignment;
    // "$DIMSD1", 70
    bool DimensionSuppressFirstDimensionLine;
    // "$DIMSD2", 70
    bool DimensionSuppressSecondDimensionLine;
    // "$DIMTOL", 70
    bool DimensionGenerateTolerances;
    // "$DIMTOLJ", 70
    ToleranceAlignment DimensionToleranceAlignment;
    // "$DIMZIN", 70
    ZeroHandling DimensionZeroHandling;
    // "$DIMTZIN", 70
    ZeroHandling DimensionToleranceZeroHandling;
    // "$DIMFIT", 70
    short DimensionFit;
    // "$DIMALTZ", 70
    ZeroHandling DimensionAlternateUnitZeroHandling;
    // "$DIMALTTZ", 70
    ZeroHandling DimensionAlternateUnitToleranceZeroHandling;
    // "$DIMUPT", 70
    bool DimensionCursorUpdate;
    // "$DIMATFIT", 70
    TextArrowFitType DimensionDimensionTextArrowFit;
    // "$DIMALTRND", 40
    double DimensionAlternateUnitRounding;
    // "$DIMAPOST", 1
    CPL::String DimensionAlternateDimensioningSuffix;
    // "$DIMASZ", 40
    double DimensionArrowSize;
    // "$DIMAZIN", 70
    ZeroHandling DimensionAngularZeroHandling;
    // "$DIMARCSYM", 70
    ArcLengthSymbolPosition DimensionArcLengthSymbolPosition;
    // "$DIMSAH", 70
    bool DimensionSeparateArrowBlocks;
    // "$DIMCEN", 40
    double DimensionCenterMarkSize;
    // "$DIMTSZ", 40
    double DimensionTickSize;
    // "$DIMCLRD", 70
    Color DimensionLineColor;
    // "$DIMCLRE", 70
    Color DimensionExtensionLineColor;
    // "$DIMCLRT", 70
    Color DimensionTextColor;
    // "$DIMDLE", 40
    double DimensionLineExtension;
    // "$DIMDLI", 40
    double DimensionLineIncrement;
    // "$DIMEXE", 40
    double DimensionExtensionLineExtension;
    // "$DIMFXLON", 70
    bool DimensionIsExtensionLineLengthFixed;
    // "$DIMFXL", 40
    double DimensionFixedExtensionLineLength;
    // "$DIMJOGANG", 40
    double DimensionJoggedRadiusDimensionTransverseSegmentAngle;
    // "$DIMTFILL", 70
    DimensionTextBackgroundFillMode DimensionTextBackgroundFillMode;
    // DxfReferenceType.Ignored, "$DIMTFILLCLR", 62
    Color DimensionTextBackgroundColor;
    // "$DIMGAP", 40
    double DimensionLineGap;
    // "$DIMLFAC", 40
    double DimensionLinearScaleFactor;
    // "$DIMTVP", 40
    double DimensionTextVerticalPosition;
    // "$DIMLWD", 70
    LineweightType DimensionLineWeight;
    // "$DIMLWE", 70
    LineweightType ExtensionLineWeight;
    // "$DIMPOST", 1
    CPL::String DimensionPostFix;
    // "$DIMRND", 40
    double DimensionRounding;
    // "$DIMSE1", 70
    bool DimensionSuppressFirstExtensionLine;
    // "$DIMSE2", 70
    bool DimensionSuppressSecondExtensionLine;
    // "$DIMSOXD", 70
    bool DimensionSuppressOutsideExtensions;
    // "$DIMTAD", 70
    DimensionTextVerticalAlignment DimensionTextVerticalAlignment;
    // "$DIMUNIT", 70
    short DimensionUnit;
    // "$DIMTFAC", 40
    double DimensionToleranceScaleFactor;
    // "$DIMTIH", 70
    bool DimensionTextInsideHorizontal;
    // "$DIMTIX", 70
    bool DimensionTextInsideExtensions;
    // "$DIMTM", 40
    double DimensionMinusTolerance;
    // "$DIMTOFL", 70
    bool DimensionTextOutsideExtensions;
    // "$DIMTOH", 70
    bool DimensionTextOutsideHorizontal;
    // "$DIMLIM", 70
    bool DimensionLimitsGeneration;
    // "$DIMTP", 40
    double DimensionPlusTolerance;
    // "$DIMTXT", 40
    double DimensionTextHeight;
    // "$DIMTXTDIRECTION", 70
    TextDirection DimensionTextDirection;
    // "$DIMALTMZF", 40
    double DimensionAltMzf;
    // "$DIMALTMZS", 6
    CPL::String DimensionAltMzs;
    // "$DIMMZF", 40
    double DimensionMzf;
    // "$DIMMZS", 6
    CPL::String DimensionMzs;
    // "$DIMLTYPE", 6
    CPL::String DimensionLineType = "ByBlock";
    // "$DIMLTEX1", 6
    CPL::String DimensionTex1 = "ByBlock";
    // "$DIMLTEX2", 6
    CPL::String DimensionTex2 = "ByBlock";

    Layer CurrentLayer;
    LineType CurrentLineType;
    TextStyle CurrentTextStyle;
    TextStyle DimensionTextStyle;
    DimensionStyle DimensionStyleOverrides;

    //TODO: How header UCS work??
    UCS ModelSpaceUcs;
    UCS ModelSpaceUcsBase;
    UCS PaperSpaceUcs;
    UCS PaperSpaceUcsBase;
};
CPL_SMARTER_PTR(CadHeader)

}// namespace dwg

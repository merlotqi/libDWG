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

class CadHeaderPrivate
{
public:
    CadHeaderPrivate();
    ~CadHeaderPrivate();

    CPL::String _versionString;

    ACadVersion _version;

    // "$ACADMAINTVER", 70
    short _maintenanceVersion;
    // "$DWGCODEPAGE", 3
    CPL::String _codePage;// "ANSI_1252"
    // "$LASTSAVEDBY", 3
    CPL::String _lastSavedBy;// "libDWG"
    // "$REQUIREDVERSIONS", 70
    bool _associatedDimensions;
    // "$DIMSHO", 70
    bool _updateDimensionsWhileDragging;

    bool _DIMSAV;

    // "$MEASUREMENT", 70
    MeasurementUnits _measurementUnits;
    // "$PLINEGEN", 70
    bool _polylineLineTypeGeneration;
    // "$ORTHOMODE", 70
    bool _orthoMode;
    // "$REGENMODE", 70
    bool _regenerationMode;
    // "$FILLMODE", 70
    bool _fillMode;
    // "$QTEXTMODE", 70
    bool _quickTextMode;
    SpaceLineTypeScaling _paperSpaceLineTypeScaling =
            SpaceLineTypeScaling::Normal;
    // "$PSLTSCALE", 70
    bool _limitCheckingOn;
    // "$BLIPMODE", 70
    bool _blipMode;
    // "$USRTIMER", 70
    bool _userTimer;
    // "$SKPOLY", 70
    bool _sketchPolylines;
    // "$ANGDIR", 70
    AngularDirection _angularDirection;
    // "$SPLFRAME", 70
    bool _showSplineControlPoints;
    // "$MIRRTEXT", 70
    bool _mirrorText;
    // "$WORLDVIEW", 70
    bool _worldView;
    // "$TILEMODE", 70
    bool _showModelSpace;
    // "$PLIMCHECK", 70
    bool _paperSpaceLimitsChecking;
    // "$VISRETAIN", 70
    bool _retainXRefDependentVisibilitySettings;
    // "$DISPSILH", 70
    bool _displaySilhouetteCurves;


    bool _createEllipseAsPolyline;

    // "$PROXYGRAPHICS", 70
    bool _proxyGraphics;
    // "$TREEDEPTH", 70
    short _spatialIndexMaxTreeDepth;
    // "$LUNITS", 70
    LinearUnitFormat _linearUnitFormat;
    // "$LUPREC", 70
    short _linearUnitPrecision;
    // "$AUNITS", 70
    AngularUnitFormat _angularUnit;
    // "$AUPREC", 70
    short _angularUnitPrecision;


    ObjectSnapMode _objectSnapMode;
    // "$ATTMODE", 70
    AttributeVisibilityMode _attributeVisibility;
    // "$PDMODE", 70
    short _pointDisplayMode;
    // "$USERI1", 70
    short _userShort1;
    // "$USERI2", 70
    short _userShort2;
    // "$USERI3", 70
    short _userShort3;
    // "$USERI4", 70
    short _userShort4;
    // "$USERI5", 70
    short _userShort5;
    // "$SPLINESEGS", 70
    short _numberOfSplineSegments = 8;
    // "$SURFU", 70
    short _surfaceDensityU;
    // "$SURFV", 70
    short _surfaceDensityV;
    // "$SURFTYPE", 70
    short _surfaceType;
    // "$SURFTAB1", 70
    short _surfaceMeshTabulationCount1;
    // "$SURFTAB2", 70
    short _surfaceMeshTabulationCount2;
    // "$SPLINETYPE", 70
    SplineType _splineType;
    // "$SHADEDGE", 70
    ShadeEdgeType _shadeEdge;
    // "$SHADEDIF", 70
    short _shadeDiffuseToAmbientPercentage;
    // "$UNITMODE", 70
    short _unitMode;
    // "$MAXACTVP", 70
    short _maxViewportCount;

    short _surfaceIsolineCount;

    // "$CMLJUST", 70
    VerticalAlignmentType _currentMultilineJustification;

    short _textQuality;

    // "$LTSCALE", 40
    double _lineTypeScale = 1.0;

    // "$TEXTSIZE", 40
    double _textHeightDefault = 2.5;

    // "$TEXTSTYLE", true, 7
    CPL::String _textStyleName;

    // "$CLAYER", true, 8
    CPL::String _currentLayerName;

    // "$CELTYPE", true, 6
    CPL::String _currentLineTypeName;

    // "$CMLSTYLE", true, 2
    CPL::String _multiLineStyleName = "Standard";

    // "$TRACEWID", 40
    double _traceWidthDefault = 0;

    // "$SKETCHINC", 40
    double _sketchIncrement;
    // "$FILLETRAD", 40
    double _filletRadius;
    // "$THICKNESS", 40
    double _thicknessDefault;
    // "$ANGBASE", 50
    double _angleBase = 0.0;
    // "$PDSIZE", 40
    double _pointDisplaySize = 0.0;
    // "$PLINEWID", 40
    double _polylineWidthDefault;
    // "$USERR1", 40
    double _userDouble1;
    // "$USERR2", 40
    double _userDouble2;
    // "$USERR3", 40
    double _userDouble3;
    // "$USERR4", 40
    double _userDouble4;
    // "$USERR5", 40
    double _userDouble5;
    // "$CHAMFERA", 40
    double _chamferDistance1;
    // "$CHAMFERB", 40
    double _chamferDistance2;
    // "$CHAMFERC", 40
    double _chamferLength;
    // "$CHAMFERD", 40
    double _chamferAngle;

    double _facetResolution;

    // "$CMLSCALE", 40
    double _currentMultilineScale = 20.0;
    // "$CELTSCALE", 40
    double _currentEntityLinetypeScale = 1.0;
    // "$MENU", 1
    CPL::String _menuFileName = ".";
    // "$HANDSEED", 5
    unsigned long long _handleSeed = 0x0;
    // "$TDCREATE", 40
    CPL::DateTime _createDateTime;

    // "$TDUCREATE", 40
    CPL::DateTime _universalCreateDateTime;
    // "$TDUPDATE", 40
    CPL::DateTime _updateDateTime;
    // "$TDUUPDATE", 40
    CPL::DateTime _universalUpdateDateTime;
    // "$TDINDWG", 40
    CPL::Timespan _totalEditingTime;
    // "$TDUSRTIMER", 40
    CPL::Timespan _userElapsedTimeSpan;
    // "$CECOLOR", 62
    Color _currentEntityColor = Color::ByLayer;
    // "$PSVPSCALE", 40
    double _viewportDefaultViewScaleFactor;
    // "$PINSBASE", 10, 20, 30
    XYZ _paperSpaceInsertionBase = XYZ::Zero;
    // "$PEXTMIN", 10, 20, 30
    XYZ _paperSpaceExtMin;
    // "$PEXTMAX", 10, 20, 30
    XYZ _paperSpaceExtMax;
    // "$PLIMMIN", 10, 20
    XY _paperSpaceLimitsMin;
    // "$PLIMMAX", 10, 20
    XY _paperSpaceLimitsMax;
    // "$PELEVATION", 40
    double _paperSpaceElevation;
    // "$PUCSBASE", true, 2
    CPL::String _paperSpaceBaseName;
    // "$PUCSNAME", true, 2
    CPL::String _paperSpaceName;
    // "$PUCSORG", 10, 20, 30
    XYZ _paperSpaceUcsOrigin;
    // "$PUCSXDIR", 10, 20, 30
    XYZ _paperSpaceUcsXAxis;
    // "$PUCSYDIR", 10, 20, 30
    XYZ _paperSpaceUcsYAxis;
    // "$PUCSORGTOP", 10, 20, 30
    XYZ _paperSpaceOrthographicTopDOrigin;
    // "$PUCSORGBOTTOM", 10, 20, 30
    XYZ _paperSpaceOrthographicBottomDOrigin;
    // "$PUCSORGLEFT", 10, 20, 30
    XYZ _paperSpaceOrthographicLeftDOrigin;
    // "$PUCSORGRIGHT", 10, 20, 30
    XYZ _paperSpaceOrthographicRightDOrigin;
    // "$PUCSORGFRONT", 10, 20, 30
    XYZ _paperSpaceOrthographicFrontDOrigin;
    // "$PUCSORGBACK", 10, 20, 30
    XYZ _paperSpaceOrthographicBackDOrigin;
    // "$UCSORGTOP", 10, 20, 30
    XYZ _modelSpaceOrthographicTopDOrigin;
    // "$UCSORGBOTTOM", 10, 20, 30
    XYZ _modelSpaceOrthographicBottomDOrigin;
    // "$UCSORGLEFT", 10, 20, 30
    XYZ _modelSpaceOrthographicLeftDOrigin;
    // "$UCSORGRIGHT", 10, 20, 30
    XYZ _modelSpaceOrthographicRightDOrigin;
    // "$UCSORGFRONT", 10, 20, 30
    XYZ _modelSpaceOrthographicFrontDOrigin;
    // "$UCSORGBACK", 10, 20, 30
    XYZ _modelSpaceOrthographicBackDOrigin;
    // "$INSBASE", 10, 20, 30
    XYZ _modelSpaceInsertionBase = XYZ::Zero;
    // "$EXTMIN", 10, 20, 30
    XYZ _modelSpaceExtMin;
    // "$EXTMAX", 10, 20, 30
    XYZ _modelSpaceExtMax;
    // "$LIMMIN", 10, 20
    XY _modelSpaceLimitsMin;
    // "$LIMMAX", 10, 20
    XY _modelSpaceLimitsMax;
    // "$UCSBASE", true, 2
    CPL::String _ucsBaseName;
    // "$UCSNAME", true, 2
    CPL::String _ucsName;
    // "$ELEVATION", 40
    double _elevation;
    // "$UCSORG", 10, 20, 30
    XYZ _modelSpaceOrigin;
    // "$UCSXDIR", 10, 20, 30
    XYZ _modelSpaceXAxis;
    // "$UCSYDIR", 10, 20, 30
    XYZ _modelSpaceYAxis;
    // "$DIMBLK", 1
    CPL::String _dimensionBlockName;
    // "$DIMLDRBLK", 1
    CPL::String _arrowBlockName;
    // "$DIMBLK1", 1
    CPL::String _dimensionBlockNameFirst;
    // "$DIMBLK2", 1
    CPL::String _dimensionBlockNameSecond;


    short _stackedTextAlignment = 1;
    short _stackedTextSizePercentage = 70;


    // "$HYPERLINKBASE", 1
    CPL::String _hyperLinkBase;
    // "$CELWEIGHT", 370
    LineweightType _currentEntityLineWeight = LineweightType::ByLayer;
    // "$ENDCAPS", 280
    short _endCaps;
    // "$JOINSTYLE", 280
    short _joinStyle;
    // "$LWDISPLAY", 290
    bool _displayLineWeight = false;
    // "$XEDIT", 290
    bool _xedit;
    // "$EXTNAMES", 290
    bool _extendedNames = true;
    // "$PSTYLEMODE", 290
    short _plotStyleMode;
    //[CadSystemVariable("$OLESTARTUP", 290
    bool _loadOLEObject;
    // "$INSUNITS", 70
    UnitsType _dinsUnits = UnitsType::Unitless;
    // "$CEPSNTYPE", 380
    EntityPlotStyleType _currentEntityPlotStyle;
    // "$FINGERPRINTGUID", 2
    CPL::String _fingerPrintGuid;
    // "$VERSIONGUID", 2
    CPL::String _versionGuid;

    // "$SORTENTS", 280
    ObjectSortingFlags _entitySortingFlags;
    // "$INDEXCTL", 280
    IndexCreationFlags _indexCreationFlags;
    // "$HIDETEXT", 280   //note: mismatch with docs, code 290
    unsigned char _hideText;
    // "$XCLIPFRAME", 280 //note: mismatch with docs, code 290
    unsigned char _externalReferenceClippingBoundaryType;
    // "$DIMASSOC", 280
    DimensionAssociation _dimensionAssociativity;
    // "$HALOGAP", 280
    unsigned char _haloGapPercentage;

    Color _obscuredColor;
    // "$INTERFERECOLOR", 62
    Color _interfereColor;

    unsigned char _obscuredType;

    unsigned char _intersectionDisplay;
    // "$PROJECTNAME", 1
    CPL::String _projectName;

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

    // "$LATITUDE", 40
    double _latitude = 37.7950;
    // "$LONGITUDE", 40
    double _longitude = -122.394;
    // "$NORTHDIRECTION", 40
    double _northDirection;
    // "$TIMEZONE", 70
    int _timeZone;

    char _displayLightGlyphs;
    // "$DWFFRAME", 280
    char _dwgUnderlayFramesVisibility;

    // "$DGNFRAME", 280
    char _dgnUnderlayFramesVisibility;

    // "$CSHADOW", 280
    ShadowMode _shadowMode;

    // "$SHADOWPLANELOCATION", 40
    double _shadowPlaneLocation;

    CPL::String _styleSheetName;

    // "$DIMTXSTY", true, 7
    CPL::String _dimensionTextStyleName;
    // "$DIMSTYLE", true, 2
    CPL::String _dimensionStyleOverridesName;
    // "$DIMADEC", 70
    short _dimensionAngularDimensionDecimalPlaces;
    // "$DIMDEC", 70
    short _dimensionDecimalPlaces;
    // "$DIMTDEC", 70
    short _dimensionToleranceDecimalPlaces;
    // "$DIMALT", 70
    bool _dimensionAlternateUnitDimensioning;
    // "$DIMALTU", 70
    LinearUnitFormat _dimensionAlternateUnitFormat;
    // "$DIMALTF", 40
    double _dimensionAlternateUnitScaleFactor;
    // "$DIMEXO", 40
    double _dimensionExtensionLineOffset;
    // "$DIMSCALE", 40
    double _dimensionScaleFactor;
    // "$DIMALTD", 70
    short _dimensionAlternateUnitDecimalPlaces;
    // "$DIMALTTD", 70
    short _dimensionAlternateUnitToleranceDecimalPlaces;
    // "$DIMAUNIT", 70
    AngularUnitFormat _dimensionAngularUnit;
    // "$DIMFRAC", 70
    FractionFormat _dimensionFractionFormat;
    // "$DIMLUNIT", 70
    LinearUnitFormat _dimensionLinearUnitFormat;
    // "$DIMDSEP", 70
    char _dimensionDecimalSeparator;
    // "$DIMTMOVE", 70
    TextMovement _dimensionTextMovement;
    // "$DIMJUST", 70
    DimensionTextHorizontalAlignment _dimensionTextHorizontalAlignment;
    // "$DIMSD1", 70
    bool _dimensionSuppressFirstDimensionLine;
    // "$DIMSD2", 70
    bool _dimensionSuppressSecondDimensionLine;
    // "$DIMTOL", 70
    bool _dimensionGenerateTolerances;
    // "$DIMTOLJ", 70
    ToleranceAlignment _dimensionToleranceAlignment;
    // "$DIMZIN", 70
    ZeroHandling _dimensionZeroHandling;
    // "$DIMTZIN", 70
    ZeroHandling _dimensionToleranceZeroHandling;
    // "$DIMFIT", 70
    short _dimensionFit;
    // "$DIMALTZ", 70
    ZeroHandling _dimensionAlternateUnitZeroHandling;
    // "$DIMALTTZ", 70
    ZeroHandling _dimensionAlternateUnitToleranceZeroHandling;
    // "$DIMUPT", 70
    bool _dimensionCursorUpdate;
    // "$DIMATFIT", 70
    TextArrowFitType _dimensionDimensionTextArrowFit;
    // "$DIMALTRND", 40
    double _dimensionAlternateUnitRounding;
    // "$DIMAPOST", 1
    CPL::String _dimensionAlternateDimensioningSuffix;
    // "$DIMASZ", 40
    double _dimensionArrowSize;
    // "$DIMAZIN", 70
    ZeroHandling _dimensionAngularZeroHandling;
    // "$DIMARCSYM", 70
    ArcLengthSymbolPosition _dimensionArcLengthSymbolPosition;
    // "$DIMSAH", 70
    bool _dimensionSeparateArrowBlocks;
    // "$DIMCEN", 40
    double _dimensionCenterMarkSize;
    // "$DIMTSZ", 40
    double _dimensionTickSize;
    // "$DIMCLRD", 70
    Color _dimensionLineColor;
    // "$DIMCLRE", 70
    Color _dimensionExtensionLineColor;
    // "$DIMCLRT", 70
    Color _dimensionTextColor;
    // "$DIMDLE", 40
    double _dimensionLineExtension;
    // "$DIMDLI", 40
    double _dimensionLineIncrement;
    // "$DIMEXE", 40
    double _dimensionExtensionLineExtension;
    // "$DIMFXLON", 70
    bool _dimensionIsExtensionLineLengthFixed;
    // "$DIMFXL", 40
    double _dimensionFixedExtensionLineLength;
    // "$DIMJOGANG", 40
    double _dimensionJoggedRadiusDimensionTransverseSegmentAngle;
    // "$DIMTFILL", 70
    DimensionTextBackgroundFillMode _dimensionTextBackgroundFillMode;
    // DxfReferenceType.Ignored, "$DIMTFILLCLR", 62
    Color _dimensionTextBackgroundColor;
    // "$DIMGAP", 40
    double _dimensionLineGap;
    // "$DIMLFAC", 40
    double _dimensionLinearScaleFactor;
    // "$DIMTVP", 40
    double _dimensionTextVerticalPosition;
    // "$DIMLWD", 70
    LineweightType _dimensionLineWeight;
    // "$DIMLWE", 70
    LineweightType _extensionLineWeight;
    // "$DIMPOST", 1
    CPL::String _dimensionPostFix;
    // "$DIMRND", 40
    double _dimensionRounding;
    // "$DIMSE1", 70
    bool _dimensionSuppressFirstExtensionLine;
    // "$DIMSE2", 70
    bool _dimensionSuppressSecondExtensionLine;
    // "$DIMSOXD", 70
    bool _dimensionSuppressOutsideExtensions;
    // "$DIMTAD", 70
    DimensionTextVerticalAlignment _dimensionTextVerticalAlignment;
    // "$DIMUNIT", 70
    short _dimensionUnit;
    // "$DIMTFAC", 40
    double _dimensionToleranceScaleFactor;
    // "$DIMTIH", 70
    bool _dimensionTextInsideHorizontal;
    // "$DIMTIX", 70
    bool _dimensionTextInsideExtensions;
    // "$DIMTM", 40
    double _dimensionMinusTolerance;
    // "$DIMTOFL", 70
    bool _dimensionTextOutsideExtensions;
    // "$DIMTOH", 70
    bool _dimensionTextOutsideHorizontal;
    // "$DIMLIM", 70
    bool _dimensionLimitsGeneration;
    // "$DIMTP", 40
    double _dimensionPlusTolerance;
    // "$DIMTXT", 40
    double _dimensionTextHeight;
    // "$DIMTXTDIRECTION", 70
    TextDirection _dimensionTextDirection;
    // "$DIMALTMZF", 40
    double _dimensionAltMzf;
    // "$DIMALTMZS", 6
    CPL::String _dimensionAltMzs;
    // "$DIMMZF", 40
    double _dimensionMzf;
    // "$DIMMZS", 6
    CPL::String _dimensionMzs;
    // "$DIMLTYPE", 6
    CPL::String _dimensionLineType = "ByBlock";
    // "$DIMLTEX1", 6
    CPL::String _dimensionTex1 = "ByBlock";
    // "$DIMLTEX2", 6
    CPL::String _dimensionTex2 = "ByBlock";

    Layer _currentLayer;
    LineType _currentLineType;
    TextStyle _currentTextStyle;
    TextStyle _dimensionTextStyle;
    DimensionStyle _dimensionStyleOverrides;

    //TODO: How header UCS work??
    UCS _modelSpaceUcs;
    UCS _modelSpaceUcsBase;
    UCS _paperSpaceUcs;
    UCS _paperSpaceUcsBase;
};
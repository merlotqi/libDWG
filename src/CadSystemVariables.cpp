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

#include <assert.h>
#include <dwg/CadSystemVariables_p.h>
#include <dwg/header/CadHeader.h>
#include <dwg/utils/StringHelp.h>

namespace dwg {

static std::vector<CadSystemVariableAttribute> _headerVariables = {
        {"$ANGBASE", {50}},
        {"$ANGDIR", {70}},
        {"$AUNITS", {70}},
        {"$AUPREC", {70}},
        {"$DIMLDRBLK", {1}},
        {"$DIMASO", {70}},
        {"$ATTMODE", {70}},
        {"$BLIPMODE", {70}},
        {"$CAMERADISPLAY", {290}},
        {"$CAMERAHEIGHT", {40}},
        {"$CHAMFERD", {40}},
        {"$CHAMFERA", {40}},
        {"$CHAMFERB", {40}},
        {"$CHAMFERC", {40}},
        {"$DWGCODEPAGE", {3}},
        {"$TDCREATE", {40}},
        {"$PELLIPSE", {70}},
        {"$CECOLOR", {62}},
        {"$CELTSCALE", {40}},
        {"$CELWEIGHT", {370}},
        {"$CEPSNTYPE", {380}},
        {"$CLAYER", true, {8}},
        {"$CELTYPE", true, {6}},
        {"$CMLJUST", {70}},
        {"$CMLSCALE", {40}},
        {"$CMLSTYLE", true, {2}},
        {"$DGNFRAME", {280}},
        {"$DIMAPOST", {1}},
        {"$DIMALTD", {70}},
        {"$DIMALT", {70}},
        {"$DIMALTU", {70}},
        {"$DIMALTRND", {40}},
        {"$DIMALTF", {40}},
        {"$DIMALTTD", {70}},
        {"$DIMALTTZ", {70}},
        {"$DIMALTZ", {70}},
        {"$DIMALTMZF", {40}},
        {"$DIMALTMZS", {6}},
        {"$DIMADEC", {70}},
        {"$DIMAUNIT", {70}},
        {"$DIMAZIN", {70}},
        {"$DIMARCSYM", {70}},
        {"$DIMASZ", {40}},
        {"$DIMASSOC", {280}},
        {"$DIMBLK", {1}},
        {"$DIMBLK1", {1}},
        {"$DIMBLK2", {1}},
        {"$DIMCEN", {40}},
        {"$DIMUPT", {70}},
        {"$DIMDEC", {70}},
        {"$DIMDSEP", {70}},
        {"$DIMATFIT", {70}},
        {"$DIMCLRE", {70}},
        {"$DIMEXE", {40}},
        {"$DIMEXO", {40}},
        {"$DIMFIT", {70}},
        {"$DIMFXL", {40}},
        {"$DIMFRAC", {70}},
        {"$DIMTOL", {70}},
        {"$DIMFXLON", {70}},
        {"$DIMJOGANG", {40}},
        {"$DIMLIM", {70}},
        {"$DIMLFAC", {40}},
        {"$DIMLUNIT", {70}},
        {"$DIMCLRD", {70}},
        {"$DIMDLE", {40}},
        {"$DIMGAP", {40}},
        {"$DIMDLI", {40}},
        {"$DIMLTYPE", {6}},
        {"$DIMLWD", {70}},
        {"$DIMTM", {40}},
        {"$DIMMZF", {40}},
        {"$DIMMZS", {6}},
        {"$DIMTP", {40}},
        {"$DIMPOST", {1}},
        {"$DIMRND", {40}},
        {"$DIMSCALE", {40}},
        {"$DIMSAH", {70}},
        {"$DIMSTYLE", true, {2}},
        {"$DIMSD1", {70}},
        {"$DIMSE1", {70}},
        {"$DIMSOXD", {70}},
        {"$DIMSD2", {70}},
        {"$DIMSE2", {70}},
        {"$DIMLTEX1", {6}},
        {"$DIMLTEX2", {6}},
        {DxfReferenceType::Ignored, "$DIMTFILLCLR", {62}},
        {"$DIMTFILL", {70}},
        {"$DIMCLRT", {70}},
        {"$DIMTXTDIRECTION", {70}},
        {"$DIMTXT", {40}},
        {"$DIMJUST", {70}},
        {"$DIMTIX", {70}},
        {"$DIMTIH", {70}},
        {"$DIMTMOVE", {70}},
        {"$DIMTOFL", {70}},
        {"$DIMTOH", {70}},
        {"$DIMTXSTY", true, {7}},
        {"$DIMTAD", {70}},
        {"$DIMTVP", {40}},
        {"$DIMTSZ", {40}},
        {"$DIMTOLJ", {70}},
        {"$DIMTDEC", {70}},
        {"$DIMTFAC", {40}},
        {"$DIMTZIN", {70}},
        {"$DIMUNIT", {70}},
        {"$DIMZIN", {70}},
        {"$LIGHTGLYPHDISPLAY", {280}},
        {"$LWDISPLAY", {290}},
        {"$DISPSILH", {70}},
        {"$LOFTANG1", {40}},
        {"$LOFTANG2", {40}},
        {"$LOFTMAG1", {40}},
        {"$LOFTMAG2", {40}},
        {"$3DDWFPREC", {40}},
        {"$DWFFRAME", {280}},
        {"$ELEVATION", {40}},
        {"$ENDCAPS", {280}},
        {"$SORTENTS", {280}},
        {"$EXTNAMES", {290}},
        {"$DIMLWE", {70}},
        {"$XCLIPFRAME", {280}},
        {"$FACETRES", {40}},
        {"$FILLETRAD", {40}},
        {"$FILLMODE", {70}},
        {"$FINGERPRINTGUID", {2}},
        {"$HALOGAP", {280}},
        {"$HANDSEED", {5}},
        {"$HIDETEXT", {280}},
        {"$HYPERLINKBASE", {1}},
        {"$INDEXCTL", {280}},
        {"$INSUNITS", {70}},
        {"$INTERFERECOLOR", {62}},
        {"$JOINSTYLE", {280}},
        {DxfReferenceType::Ignored, "$LASTSAVEDBY", {3}},
        {"$LATITUDE", {40}},
        {"$LENSLENGTH", {40}},
        {"$LIMCHECK", {70}},
        {"$LUNITS", {70}},
        {"$LUPREC", {70}},
        {"$LTSCALE", {40}},
        {"$LOFTNORMALS", {280}},
        {"$LONGITUDE", {40}},
        {DxfReferenceType::Ignored, "$ACADMAINTVER", {70}},
        {"$MAXACTVP", {70}},
        {"$MEASUREMENT", {70}},
        {"$MENU", {1}},
        {"$MIRRTEXT", {70}},
        {"$EXTMAX", {10, 20, 30}},
        {"$EXTMIN", {10, 20, 30}},
        {"$INSBASE", {10, 20, 30}},
        {"$LIMMAX", {10, 20}},
        {"$LIMMIN", {10, 20}},
        {"$UCSORG", {10, 20, 30}},
        {"$UCSORGBACK", {10, 20, 30}},
        {"$UCSORGBOTTOM", {10, 20, 30}},
        {"$UCSORGFRONT", {10, 20, 30}},
        {"$UCSORGLEFT", {10, 20, 30}},
        {"$UCSORGRIGHT", {10, 20, 30}},
        {"$UCSORGTOP", {10, 20, 30}},
        {"$UCSXDIR", {10, 20, 30}},
        {"$UCSYDIR", {10, 20, 30}},
        {"$NORTHDIRECTION", {40}},
        {"$SPLINESEGS", {70}},
        {"$OSMODE", {70}},
        {"$ORTHOMODE", {70}},
        {"$PUCSBASE", true, {2}},
        {"$PELEVATION", {40}},
        {"$PEXTMAX", {10, 20, 30}},
        {"$PEXTMIN", {10, 20, 30}},
        {"$PINSBASE", {10, 20, 30}},
        {"$PLIMCHECK", {70}},
        {"$PLIMMAX", {10, 20}},
        {"$PLIMMIN", {10, 20}},
        {"$PSLTSCALE", {70}},
        {"$PUCSNAME", true, {2}},
        {"$PUCSORGBACK", {10, 20, 30}},
        {"$PUCSORGBOTTOM", {10, 20, 30}},
        {"$PUCSORGFRONT", {10, 20, 30}},
        {"$PUCSORGLEFT", {10, 20, 30}},
        {"$PUCSORGRIGHT", {10, 20, 30}},
        {"$PUCSORGTOP", {10, 20, 30}},
        {"$PUCSORG", {10, 20, 30}},
        {"$PUCSXDIR", {10, 20, 30}},
        {"$PUCSYDIR", {10, 20, 30}},
        {"$PSTYLEMODE", {290}},
        {"$PDMODE", {70}},
        {"$PDSIZE", {40}},
        {"$PLINEGEN", {70}},
        {"$PLINEWID", {40}},
        {"$PROJECTNAME", {1}},
        {"$PROXYGRAPHICS", {70}},
        {"$QTEXTMODE", {70}},
        {"$REGENMODE", {70}},
        {DxfReferenceType::Ignored, "$REQUIREDVERSIONS", {70}},
        {"$VISRETAIN", {70}},
        {"$SHADEDIF", {70}},
        {"$SHADEDGE", {70}},
        {"$CSHADOW", {280}},
        {"$SHADOWPLANELOCATION", {40}},
        {"$TILEMODE", {70}},
        {"$SHOWHIST", {280}},
        {"$SPLFRAME", {70}},
        {"$SKETCHINC", {40}},
        {"$SKPOLY", {70}},
        {"$LOFTPARAM", {70}},
        {"$SOLIDHIST", {280}},
        {"$TREEDEPTH", {70}},
        {"$SPLINETYPE", {70}},
        {"$STEPSIZE", {40}},
        {"$STEPSPERSEC", {40}},
        {"$STYLESHEET", {1}},
        {"$SURFU", {70}},
        {"$SURFV", {70}},
        {"$SURFTAB1", {70}},
        {"$SURFTAB2", {70}},
        {"$SURFTYPE", {70}},
        {"$PSOLHEIGHT", {40}},
        {"$PSOLWIDTH", {40}},
        {"$TEXTSIZE", {40}},
        {"$TEXTSTYLE", true, {7}},
        {"$THICKNESS", {40}},
        {"$TIMEZONE", {70}},
        {"$TDINDWG", {40}},
        {"$TRACEWID", {40}},
        {"$UCSBASE", true, {2}},
        {"$UCSNAME", true, {2}},
        {"$UNITMODE", {70}},
        {"$TDUCREATE", {40}},
        {"$TDUUPDATE", {40}},
        {"$TDUPDATE", {40}},
        {"$DIMSHO", {70}},
        {"$USERR1", {40}},
        {"$USERR2", {40}},
        {"$USERR3", {40}},
        {"$USERR4", {40}},
        {"$USERR5", {40}},
        {"$TDUSRTIMER", {40}},
        {"$USERI1", {70}},
        {"$USERI2", {70}},
        {"$USERI3", {70}},
        {"$USERI4", {70}},
        {"$USERI5", {70}},
        {"$USRTIMER", {70}},
        {"$VERSIONGUID", {2}},
        {"$ACADVER", {DxfCode::Text}},
        {"$PSVPSCALE", {40}},
        {"$WORLDVIEW", {70}},
        {"$XEDIT", {290}},
};

std::vector<CadSystemVariableAttribute> CadSystemVariables::headerVariables()
{
    return _headerVariables;
}

std::map<std::string, CadSystemVariableAttribute> CadSystemVariables::headerMap()
{
    std::map<std::string, CadSystemVariableAttribute> _map;
    for (auto &&attr: _headerVariables)
    {
        _map.insert({attr.name(), attr});
    }
    return _map;
}

DwgVariant CadSystemVariables::value(const std::string &key, CadHeader *header)
{
    assert(header);
    if (key == "$ANGBASE")
    {
        return header->angleBase();
    }
    if (key == "$ANGDIR")
    {
        return static_cast<short>(header->angularDirection());
    }
    if (key == "$AUNITS")
    {
        return static_cast<short>(header->angularUnit());
    }
    if (key == "$AUPREC")
    {
        return header->angularUnitPrecision();
    }
    if (key == "$DIMLDRBLK")
    {
        return header->arrowBlockName();
    }
    if (key == "$DIMASO")
    {
        return header->associatedDimensions();
    }
    if (key == "$ATTMODE")
    {
        return static_cast<int>(header->attributeVisibility());
    }
    if (key == "$BLIPMODE")
    {
        return header->blipMode();
    }
    if (key == "$CAMERADISPLAY")
    {
        return header->cameraDisplayObjects();
    }
    if (key == "$CAMERAHEIGHT")
    {
        return header->cameraHeight();
    }
    if (key == "$CHAMFERD")
    {
        return header->chamferAngle();
    }
    if (key == "$CHAMFERA")
    {
        return header->chamferDistance1();
    }
    if (key == "$CHAMFERB")
    {
        return header->chamferDistance2();
    }
    if (key == "$CHAMFERC")
    {
        return header->chamferLength();
    }
    if (key == "$DWGCODEPAGE")
    {
        return header->codePage();
    }
    if (key == "$TDCREATE")
    {
        return header->createDateTime();
    }
    if (key == "$PELLIPSE")
    {
        return header->createEllipseAsPolyline();
    }
    if (key == "$CECOLOR")
    {
        return header->currentEntityColor();
    }
    if (key == "$CELTSCALE")
    {
        return header->currentEntityLinetypeScale();
    }
    if (key == "$CELWEIGHT")
    {
        return static_cast<short>(header->currentEntityLineWeight());
    }
    if (key == "$CEPSNTYPE")
    {
        return static_cast<short>(header->currentEntityPlotStyle());
    }
    if (key == "$CLAYER")
    {
        return header->currentLayerName();
    }
    if (key == "$CELTYPE")
    {
        return header->currentLineTypeName();
    }
    if (key == "$CMLJUST")
    {
        return static_cast<short>(header->currentMultilineJustification());
    }
    if (key == "$CMLSCALE")
    {
        return header->currentMultilineScale();
    }
    if (key == "$CMLSTYLE")
    {
        return header->currentMultiLineStyleName();
    }
    if (key == "$DGNFRAME")
    {
        return header->dgnUnderlayFramesVisibility();
    }
    if (key == "$DIMAPOST")
    {
        return header->dimensionAlternateDimensioningSuffix();
    }
    if (key == "$DIMALTD")
    {
        return header->dimensionAlternateUnitDecimalPlaces();
    }
    if (key == "$DIMALT")
    {
        return header->dimensionAlternateUnitDimensioning();
    }
    if (key == "$DIMALTU")
    {
        return static_cast<short>(header->dimensionAlternateUnitFormat());
    }
    if (key == "$DIMALTRND")
    {
        return header->dimensionAlternateUnitRounding();
    }
    if (key == "$DIMALTF")
    {
        return header->dimensionAlternateUnitScaleFactor();
    }
    if (key == "$DIMALTTD")
    {
        return header->dimensionAlternateUnitToleranceDecimalPlaces();
    }
    if (key == "$DIMALTTZ")
    {
        return static_cast<unsigned char>(header->dimensionAlternateUnitToleranceZeroHandling());
    }
    if (key == "$DIMALTZ")
    {
        return static_cast<unsigned char>(header->dimensionAlternateUnitZeroHandling());
    }
    if (key == "$DIMALTMZF")
    {
        return header->dimensionAltMzf();
    }
    if (key == "$DIMALTMZS")
    {
        return header->dimensionAltMzs();
    }
    if (key == "$DIMADEC")
    {
        return header->dimensionAngularDimensionDecimalPlaces();
    }
    if (key == "$DIMAUNIT")
    {
        return static_cast<short>(header->dimensionAngularUnit());
    }
    if (key == "$DIMAZIN")
    {
        return static_cast<unsigned char>(header->dimensionAngularZeroHandling());
    }
    if (key == "$DIMARCSYM")
    {
        return static_cast<short>(header->dimensionArcLengthSymbolPosition());
    }
    if (key == "$DIMASZ")
    {
        return header->dimensionArrowSize();
    }
    if (key == "$DIMASSOC")
    {
        return static_cast<short>(header->dimensionAssociativity());
    }
    if (key == "$DIMBLK")
    {
        return header->dimensionBlockName();
    }
    if (key == "$DIMBLK1")
    {
        return header->dimensionBlockNameFirst();
    }
    if (key == "$DIMBLK2")
    {
        return header->dimensionBlockNameSecond();
    }
    if (key == "$DIMCEN")
    {
        return header->dimensionCenterMarkSize();
    }
    if (key == "$DIMUPT")
    {
        return header->dimensionCursorUpdate();
    }
    if (key == "$DIMDEC")
    {
        return header->dimensionDecimalPlaces();
    }
    if (key == "$DIMDSEP")
    {
        return header->dimensionDecimalSeparator();
    }
    if (key == "$DIMATFIT")
    {
        return static_cast<unsigned char>(header->dimensionDimensionTextArrowFit());
    }
    if (key == "$DIMCLRE")
    {
        return header->dimensionExtensionLineColor();
    }
    if (key == "$DIMEXE")
    {
        return header->dimensionExtensionLineExtension();
    }
    if (key == "$DIMEXO")
    {
        return header->dimensionExtensionLineOffset();
    }
    if (key == "$DIMFIT")
    {
        return header->dimensionFit();
    }
    if (key == "$DIMFXL")
    {
        return header->dimensionFixedExtensionLineLength();
    }
    if (key == "$DIMFRAC")
    {
        return static_cast<short>(header->dimensionFractionFormat());
    }
    if (key == "$DIMTOL")
    {
        return header->dimensionGenerateTolerances();
    }
    if (key == "$DIMFXLON")
    {
        return header->dimensionIsExtensionLineLengthFixed();
    }
    if (key == "$DIMJOGANG")
    {
        return header->dimensionJoggedRadiusDimensionTransverseSegmentAngle();
    }
    if (key == "$DIMLIM")
    {
        return header->dimensionLimitsGeneration();
    }
    if (key == "$DIMLFAC")
    {
        return header->dimensionLinearScaleFactor();
    }
    if (key == "$DIMLUNIT")
    {
        return static_cast<short>(header->dimensionLinearUnitFormat());
    }
    if (key == "$DIMCLRD")
    {
        return header->dimensionLineColor();
    }
    if (key == "$DIMDLE")
    {
        return header->dimensionLineExtension();
    }
    if (key == "$DIMGAP")
    {
        return header->dimensionLineGap();
    }
    if (key == "$DIMDLI")
    {
        return header->dimensionLineIncrement();
    }
    if (key == "$DIMLTYPE")
    {
        return header->dimensionLineType();
    }
    if (key == "$DIMLWD")
    {
        return static_cast<short>(header->dimensionLineWeight());
    }
    if (key == "$DIMTM")
    {
        return header->dimensionMinusTolerance();
    }
    if (key == "$DIMMZF")
    {
        return header->dimensionMzf();
    }
    if (key == "$DIMMZS")
    {
        return header->dimensionMzs();
    }
    if (key == "$DIMTP")
    {
        return header->dimensionPlusTolerance();
    }
    if (key == "$DIMPOST")
    {
        return header->dimensionPostFix();
    }
    if (key == "$DIMRND")
    {
        return header->dimensionRounding();
    }
    if (key == "$DIMSCALE")
    {
        return header->dimensionScaleFactor();
    }
    if (key == "$DIMSAH")
    {
        return header->dimensionSeparateArrowBlocks();
    }
    if (key == "$DIMSTYLE")
    {
        return header->currentDimensionStyleName();
    }
    if (key == "$DIMSD1")
    {
        return header->dimensionSuppressFirstDimensionLine();
    }
    if (key == "$DIMSE1")
    {
        return header->dimensionSuppressFirstExtensionLine();
    }
    if (key == "$DIMSOXD")
    {
        return header->dimensionSuppressOutsideExtensions();
    }
    if (key == "$DIMSD2")
    {
        return header->dimensionSuppressSecondDimensionLine();
    }
    if (key == "$DIMSE2")
    {
        return header->dimensionSuppressSecondExtensionLine();
    }
    if (key == "$DIMLTEX1")
    {
        return header->dimensionTex1();
    }
    if (key == "$DIMLTEX2")
    {
        return header->dimensionTex2();
    }
    if (key == "$DIMTFILLCLR")
    {
        return header->dimensionTextBackgroundColor();
    }
    if (key == "$DIMTFILL")
    {
        return static_cast<short>(header->dimensionTextBackgroundFillMode());
    }
    if (key == "$DIMCLRT")
    {
        return header->dimensionTextColor();
    }
    if (key == "$DIMTXTDIRECTION")
    {
        return static_cast<unsigned char>(header->dimensionTextDirection());
    }
    if (key == "$DIMTXT")
    {
        return header->dimensionTextHeight();
    }
    if (key == "$DIMJUST")
    {
        return static_cast<unsigned char>(header->dimensionTextHorizontalAlignment());
    }
    if (key == "$DIMTIX")
    {
        return header->dimensionTextInsideExtensions();
    }
    if (key == "$DIMTIH")
    {
        return header->dimensionTextInsideHorizontal();
    }
    if (key == "$DIMTMOVE")
    {
        return static_cast<short>(header->dimensionTextMovement());
    }
    if (key == "$DIMTOFL")
    {
        return header->dimensionTextOutsideExtensions();
    }
    if (key == "$DIMTOH")
    {
        return header->dimensionTextOutsideHorizontal();
    }
    if (key == "$DIMTXSTY")
    {
        return header->dimensionTextStyleName();
    }
    if (key == "$DIMTAD")
    {
        return static_cast<int>(header->dimensionTextVerticalAlignment());
    }
    if (key == "$DIMTVP")
    {
        return header->dimensionTextVerticalPosition();
    }
    if (key == "$DIMTSZ")
    {
        return header->dimensionTickSize();
    }
    if (key == "$DIMTOLJ")
    {
        return static_cast<unsigned char>(header->dimensionToleranceAlignment());
    }
    if (key == "$DIMTDEC")
    {
        return header->dimensionToleranceDecimalPlaces();
    }
    if (key == "$DIMTFAC")
    {
        return header->dimensionToleranceScaleFactor();
    }
    if (key == "$DIMTZIN")
    {
        return static_cast<unsigned char>(header->dimensionToleranceZeroHandling());
    }
    if (key == "$DIMUNIT")
    {
        return header->dimensionUnit();
    }
    if (key == "$DIMZIN")
    {
        return static_cast<unsigned char>(header->dimensionZeroHandling());
    }
    if (key == "$LIGHTGLYPHDISPLAY")
    {
        return header->displayLightGlyphs();
    }
    if (key == "$LWDISPLAY")
    {
        return header->displayLineWeight();
    }
    if (key == "$DISPSILH")
    {
        return header->displaySilhouetteCurves();
    }
    if (key == "$LOFTANG1")
    {
        return header->draftAngleFirstCrossSection();
    }
    if (key == "$LOFTANG2")
    {
        return header->draftAngleSecondCrossSection();
    }
    if (key == "$LOFTMAG1")
    {
        return header->draftMagnitudeFirstCrossSection();
    }
    if (key == "$LOFTMAG2")
    {
        return header->draftMagnitudeSecondCrossSection();
    }
    if (key == "$3DDWFPREC")
    {
        return header->dw3DPrecision();
    }
    if (key == "$DWFFRAME")
    {
        return header->dwgUnderlayFramesVisibility();
    }
    if (key == "$ELEVATION")
    {
        return header->elevation();
    }
    if (key == "$ENDCAPS")
    {
        return header->endCaps();
    }
    if (key == "$SORTENTS")
    {
        return static_cast<unsigned char>(header->entitySortingFlags());
    }
    if (key == "$EXTNAMES")
    {
        return header->extendedNames();
    }
    if (key == "$DIMLWE")
    {
        return static_cast<short>(header->extensionLineWeight());
    }
    if (key == "$XCLIPFRAME")
    {
        return header->externalReferenceClippingBoundaryType();
    }
    if (key == "$FACETRES")
    {
        return header->facetResolution();
    }
    if (key == "$FILLETRAD")
    {
        return header->filletRadius();
    }
    if (key == "$FILLMODE")
    {
        return header->fillMode();
    }
    if (key == "$FINGERPRINTGUID")
    {
        return header->fingerPrintGuid();
    }
    if (key == "$HALOGAP")
    {
        return header->haloGapPercentage();
    }
    if (key == "$HANDSEED")
    {
        return header->handleSeed();
    }
    if (key == "$HIDETEXT")
    {
        return header->hideText();
    }
    if (key == "$INDEXCTL")
    {
        return static_cast<unsigned char>(header->indexCreationFlags());
    }
    if (key == "$INSUNITS")
    {
        return static_cast<short>(header->insUnits());
    }
    if (key == "$INTERFERECOLOR")
    {
        return header->interfereColor();
    }
    if (key == "$JOINSTYLE")
    {
        return header->joinStyle();
    }
    if (key == "$LASTSAVEDBY")
    {
        return header->lastSavedBy();
    }
    if (key == "$LATITUDE")
    {
        return header->latitude();
    }
    if (key == "$LENSLENGTH")
    {
        return header->lensLength();
    }
    if (key == "$LIMCHECK")
    {
        return header->limitCheckingOn();
    }
    if (key == "$LUNITS")
    {
        return static_cast<short>(header->linearUnitFormat());
    }
    if (key == "$LUPREC")
    {
        return header->linearUnitPrecision();
    }
    if (key == "$LTSCALE")
    {
        return header->lineTypeScale();
    }
    if (key == "$LOFTNORMALS")
    {
        return header->loftedObjectNormals();
    }
    if (key == "$LONGITUDE")
    {
        return header->longitude();
    }
    if (key == "$ACADMAINTVER")
    {
        return header->maintenanceVersion();
    }
    if (key == "$MAXACTVP")
    {
        return header->maxViewportCount();
    }
    if (key == "$MEASUREMENT")
    {
        return static_cast<short>(header->measurementUnits());
    }
    if (key == "$MENU")
    {
        return header->menuFileName();
    }
    if (key == "$MIRRTEXT")
    {
        return header->mirrorText();
    }
    if (key == "$EXTMAX")
    {
        return header->modelSpaceExtMax();
    }
    if (key == "$EXTMIN")
    {
        return header->modelSpaceExtMin();
    }
    if (key == "$INSBASE")
    {
        return header->modelSpaceInsertionBase();
    }
    if (key == "$LIMMAX")
    {
        return header->modelSpaceLimitsMax();
    }
    if (key == "$LIMMIN")
    {
        return header->modelSpaceLimitsMin();
    }
    if (key == "$UCSORG")
    {
        return header->modelSpaceOrigin();
    }
    if (key == "$UCSORGBACK")
    {
        return header->modelSpaceOrthographicBackDOrigin();
    }
    if (key == "$UCSORGBOTTOM")
    {
        return header->modelSpaceOrthographicBottomDOrigin();
    }
    if (key == "$UCSORGFRONT")
    {
        return header->modelSpaceOrthographicFrontDOrigin();
    }
    if (key == "$UCSORGLEFT")
    {
        return header->modelSpaceOrthographicLeftDOrigin();
    }
    if (key == "$UCSORGRIGHT")
    {
        return header->modelSpaceOrthographicRightDOrigin();
    }
    if (key == "$UCSORGTOP")
    {
        return header->modelSpaceOrthographicTopDOrigin();
    }
    if (key == "$UCSXDIR")
    {
        return header->modelSpaceXAxis();
    }
    if (key == "$UCSYDIR")
    {
        return header->modelSpaceYAxis();
    }
    if (key == "$NORTHDIRECTION")
    {
        return header->northDirection();
    }
    if (key == "$SPLINESEGS")
    {
        return header->numberOfSplineSegments();
    }
    if (key == "$OSMODE")
    {
        return static_cast<unsigned short>(header->objectSnapMode());
    }
    if (key == "$ORTHOMODE")
    {
        return header->orthoMode();
    }
    if (key == "$PUCSBASE")
    {
        return header->paperSpaceBaseName();
    }
    if (key == "$PELEVATION")
    {
        return header->paperSpaceElevation();
    }
    if (key == "$PEXTMAX")
    {
        return header->paperSpaceExtMax();
    }
    if (key == "$PEXTMIN")
    {
        return header->paperSpaceExtMin();
    }
    if (key == "$PINSBASE")
    {
        return header->paperSpaceInsertionBase();
    }
    if (key == "$PLIMCHECK")
    {
        return header->paperSpaceLimitsChecking();
    }
    if (key == "$PLIMMAX")
    {
        return header->paperSpaceLimitsMax();
    }
    if (key == "$PLIMMIN")
    {
        return header->paperSpaceLimitsMin();
    }
    if (key == "$PSLTSCALE")
    {
        return static_cast<short>(header->paperSpaceLineTypeScaling());
    }
    if (key == "$PUCSNAME")
    {
        return header->paperSpaceName();
    }
    if (key == "$PUCSORGBACK")
    {
        return header->paperSpaceOrthographicBackDOrigin();
    }
    if (key == "$PUCSORGBOTTOM")
    {
        return header->paperSpaceOrthographicBottomDOrigin();
    }
    if (key == "$PUCSORGFRONT")
    {
        return header->paperSpaceOrthographicFrontDOrigin();
    }
    if (key == "$PUCSORGLEFT")
    {
        return header->paperSpaceOrthographicLeftDOrigin();
    }
    if (key == "$PUCSORGRIGHT")
    {
        return header->paperSpaceOrthographicRightDOrigin();
    }
    if (key == "$PUCSORGTOP")
    {
        return header->paperSpaceOrthographicTopDOrigin();
    }
    if (key == "$PUCSORG")
    {
        return header->paperSpaceUcsOrigin();
    }
    if (key == "$PUCSXDIR")
    {
        return header->paperSpaceUcsXAxis();
    }
    if (key == "$$PUCSYDIR")
    {
        return header->paperSpaceUcsYAxis();
    }
    if (key == "$PSTYLEMODE")
    {
        return header->plotStyleMode();
    }
    if (key == "$PDMODE")
    {
        return header->pointDisplayMode();
    }
    if (key == "$PDSIZE")
    {
        return header->pointDisplaySize();
    }
    if (key == "$PLINEGEN")
    {
        return header->polylineLineTypeGeneration();
    }
    if (key == "$PLINEWID")
    {
        return header->polylineWidthDefault();
    }
    if (key == "$PROJECTNAME")
    {
        return header->projectName();
    }
    if (key == "$PROXYGRAPHICS")
    {
        return header->proxyGraphics();
    }
    if (key == "$QTEXTMODE")
    {
        return header->quickTextMode();
    }
    if (key == "$REGENMODE")
    {
        return header->regenerationMode();
    }
    if (key == "$REQUIREDVERSIONS")
    {
        return header->requiredVersions();
    }
    if (key == "$VISRETAIN")
    {
        return header->retainXRefDependentVisibilitySettings();
    }
    if (key == "$SHADEDIF")
    {
        return header->shadeDiffuseToAmbientPercentage();
    }
    if (key == "$SHADEDGE")
    {
        return static_cast<short>(header->shadeEdge());
    }
    if (key == "$CSHADOW")
    {
        return static_cast<unsigned char>(header->shadowMode());
    }
    if (key == "$SHADOWPLANELOCATION")
    {
        return header->shadowPlaneLocation();
    }
    if (key == "$TILEMODE")
    {
        return header->showModelSpace();
    }
    if (key == "$SHOWHIST")
    {
        return header->showSolidsHistory();
    }
    if (key == "$SPLFRAME")
    {
        return header->showSplineControlPoints();
    }
    if (key == "$SKETCHINC")
    {
        return header->sketchIncrement();
    }
    if (key == "$SKPOLY")
    {
        return header->sketchPolylines();
    }
    if (key == "$LOFTPARAM")
    {
        return header->solidLoftedShape();
    }
    if (key == "$SOLIDHIST")
    {
        return header->solidsRetainHistory();
    }
    if (key == "$TREEDEPTH")
    {
        return header->spatialIndexMaxTreeDepth();
    }
    if (key == "$SPLINETYPE")
    {
        return static_cast<short>(header->splineType());
    }
    if (key == "$STEPSIZE")
    {
        return header->stepSize();
    }
    if (key == "$STEPSPERSEC")
    {
        return header->stepsPerSecond();
    }
    if (key == "$STYLESHEET")
    {
        return header->styleSheetName();
    }
    if (key == "$SURFU")
    {
        return header->surfaceDensityU();
    }
    if (key == "$SURFV")
    {
        return header->surfaceDensityV();
    }
    if (key == "$SURFTAB1")
    {
        return header->surfaceMeshTabulationCount1();
    }
    if (key == "$SURFTAB2")
    {
        return header->surfaceMeshTabulationCount2();
    }
    if (key == "$SURFTYPE")
    {
        return header->surfaceType();
    }
    if (key == "$PSOLHEIGHT")
    {
        return header->sweptSolidHeight();
    }
    if (key == "$PSOLWIDTH")
    {
        return header->sweptSolidWidth();
    }
    if (key == "$TEXTSIZE")
    {
        return header->textHeightDefault();
    }
    if (key == "$TEXTSTYLE")
    {
        return header->textStyleName();
    }
    if (key == "$THICKNESS")
    {
        return header->thicknessDefault();
    }
    if (key == "$TIMEZONE")
    {
        return header->timeZone();
    }
    if (key == "$TDINDWG")
    {
        return header->totalEditingTime();
    }
    if (key == "$TRACEWID")
    {
        return header->traceWidthDefault();
    }
    if (key == "$UCSBASE")
    {
        return header->ucsBaseName();
    }
    if (key == "$UCSNAME")
    {
        return header->ucsName();
    }
    if (key == "$UNITMODE")
    {
        return header->unitMode();
    }
    if (key == "$TDUCREATE")
    {
        return header->universalCreateDateTime();
    }
    if (key == "$TDUUPDATE")
    {
        return header->universalUpdateDateTime();
    }
    if (key == "$TDUPDATE")
    {
        return header->updateDateTime();
    }
    if (key == "$DIMSHO")
    {
        return header->updateDimensionsWhileDragging();
    }
    if (key == "$USERR1")
    {
        return header->userDouble1();
    }
    if (key == "$USERR2")
    {
        return header->userDouble2();
    }
    if (key == "$USERR3")
    {
        return header->userDouble3();
    }
    if (key == "$USERR4")
    {
        return header->userDouble4();
    }
    if (key == "$USERR5")
    {
        return header->userDouble5();
    }
    if (key == "$TDUSRTIMER")
    {
        return header->userElapsedTimeSpan();
    }
    if (key == "$USERI1")
    {
        return header->userShort1();
    }
    if (key == "$USERI2")
    {
        return header->userShort2();
    }
    if (key == "$USERI3")
    {
        return header->userShort3();
    }
    if (key == "$USERI4")
    {
        return header->userShort4();
    }
    if (key == "$USERI5")
    {
        return header->userShort5();
    }
    if (key == "$USRTIMER")
    {
        return header->userTimer();
    }
    if (key == "$VERSIONGUID")
    {
        return header->versionGuid();
    }
    if (key == "$ACADVER")
    {
        return header->versionString();
    }
    if (key == "$PSVPSCALE")
    {
        return header->viewportDefaultViewScaleFactor();
    }
    if (key == "$WORLDVIEW")
    {
        return header->worldView();
    }
    if (key == "$XEDIT")
    {
        return header->xedit();
    }
}

}// namespace dwg
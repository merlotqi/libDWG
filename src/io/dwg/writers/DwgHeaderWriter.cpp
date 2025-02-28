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
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/DwgHeaderWriter_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/tables/AppId.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/View.h>
#include <dwg/tables/VPort.h>
#include <dwg/io/dwg/CRC8StreamHandler_p.h>
#include <dwg/objects/Group.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/Layout.h>

namespace dwg {

DwgHeaderWriter::DwgHeaderWriter(std::ostream *stream, CadDocument *document, Encoding encoding)
    : DwgSectionIO(document->header()->version())
{
    _document = document;
    _encoding = encoding;

    _startWriter = DwgStreamWriterBase::GetStreamWriter(_version, stream, _encoding);
    _writer = DwgStreamWriterBase::GetStreamWriter(_version, &_msmain, _encoding);
}

DwgHeaderWriter::~DwgHeaderWriter() 
{
    delete _startWriter;
    _startWriter = nullptr;

    delete _writer;
    _writer = nullptr;
}

std::string DwgHeaderWriter::sectionName() const { return DwgSectionDefinition::Header; }

void DwgHeaderWriter::write()
{
    //+R2007 Only:
    if (R2007Plus)
    {
        //Setup the writers
        _writer = DwgStreamWriterBase::GetMergedWriter(_version, &_msmain, _encoding);
        _writer->savePositonForSize();
    }

    //R2013+:
    if (R2013Plus)
    {
        //BLL : Variable REQUIREDVERSIONS, default value 0, read only.
        _writer->writeBitLongLong(0);
    }

    //Common:
    //BD : Unknown, default value 412148564080.0
    _writer->writeBitDouble(412148564080.0);
    //BD: Unknown, default value 1.0
    _writer->writeBitDouble(1.0);
    //BD: Unknown, default value 1.0
    _writer->writeBitDouble(1.0);
    //BD: Unknown, default value 1.0
    _writer->writeBitDouble(1.0);

    //TV: Unknown text string, default "m"
    _writer->writeVariableText("m");
    //TV: Unknown text string, default ""
    _writer->writeVariableText("");
    //TV: Unknown text string, default ""
    _writer->writeVariableText("");
    //TV: Unknown text string, default ""
    _writer->writeVariableText("");

    //BL : Unknown long, default value 24L
    _writer->writeBitLong(24);
    //BL: Unknown long, default value 0L;
    _writer->writeBitLong(0);

    //R13-R14 Only:
    if (R13_14Only)
    {
        //BS : Unknown short, default value 0
        _writer->writeBitShort(0);
    }

    //Pre-2004 Only:
    if (R2004Pre)
    {
        //H : Handle of the current viewport entity header (hard pointer)
        _writer->handleReference(0ULL);
    }

    //Common:
    //B: DIMASO
    _writer->writeBit(_document->header()->associatedDimensions());
    //B: DIMSHO
    _writer->writeBit(_document->header()->updateDimensionsWhileDragging());

    //R13-R14 Only:
    if (R13_14Only)
    {
        //B : DIMSAV Undocumented.
        _writer->writeBit(_document->header()->DIMSAV());
    }

    //Common:
    //B: PLINEGEN
    _writer->writeBit(_document->header()->polylineLineTypeGeneration());
    //B : ORTHOMODE
    _writer->writeBit(_document->header()->orthoMode());
    //B: REGENMODE
    _writer->writeBit(_document->header()->regenerationMode());
    //B : FILLMODE
    _writer->writeBit(_document->header()->fillMode());
    //B : QTEXTMODE
    _writer->writeBit(_document->header()->quickTextMode());
    //B : PSLTSCALE
    _writer->writeBit(_document->header()->paperSpaceLineTypeScaling() == SpaceLineTypeScaling::Normal);
    //B : LIMCHECK
    _writer->writeBit(_document->header()->limitCheckingOn());

    //R13-R14 Only (stored in registry from R15 onwards):
    if (R13_14Only)
        //B : BLIPMODE
        _writer->writeBit(_document->header()->blipMode());

    //R2004+:
    if (R2004Plus)
        //B : Undocumented
        _writer->writeBit(false);

    //Common:
    //B: USRTIMER(User timer on / off).
    _writer->writeBit(_document->header()->userTimer());
    //B : SKPOLY
    _writer->writeBit(_document->header()->sketchPolylines());
    //B : ANGDIR
    _writer->writeBit(_document->header()->angularDirection() != AngularDirection::CounterClockWise);
    //B : SPLFRAME
    _writer->writeBit(_document->header()->showSplineControlPoints());

    //R13-R14 Only (stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //B : ATTREQ
        _writer->writeBit(false);
        //B : ATTDIA
        _writer->writeBit(false);
    }

    //Common:
    //B: MIRRTEXT
    _writer->writeBit(_document->header()->mirrorText());
    //B : WORLDVIEW
    _writer->writeBit(_document->header()->worldView());

    //R13 - R14 Only:
    if (R13_14Only)
    {
        //B: WIREFRAME Undocumented.
        _writer->writeBit(false);
    }

    //Common:
    //B: TILEMODE
    _writer->writeBit(_document->header()->showModelSpace());
    //B : PLIMCHECK
    _writer->writeBit(_document->header()->paperSpaceLimitsChecking());
    //B : VISRETAIN
    _writer->writeBit(_document->header()->retainXRefDependentVisibilitySettings());

    //R13 - R14 Only(stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //B : DELOBJ
        _writer->writeBit(false);
    }

    //Common:
    //B: DISPSILH
    _writer->writeBit(_document->header()->displaySilhouetteCurves());
    //B : PELLIPSE(not present in DXF)
    _writer->writeBit(_document->header()->createEllipseAsPolyline());
    //BS: PROXYGRAPHICS
    _writer->writeBitShort((short) (_document->header()->proxyGraphics() ? 1 : 0));

    //R13-R14 Only (stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //BS : DRAGMODE
        _writer->writeBitShort(0);
    }

    //Common:
    //BS: TREEDEPTH
    _writer->writeBitShort(_document->header()->spatialIndexMaxTreeDepth());
    //BS : LUNITS
    _writer->writeBitShort((short) _document->header()->linearUnitFormat());
    //BS : LUPREC
    _writer->writeBitShort(_document->header()->linearUnitPrecision());
    //BS : AUNITS
    _writer->writeBitShort((short) _document->header()->angularUnit());
    //BS : AUPREC
    _writer->writeBitShort(_document->header()->angularUnitPrecision());

    //R13 - R14 Only Only(stored in registry from R15 onwards):
    if (R13_14Only)
        //BS: OSMODE
        _writer->writeBitShort((short) _document->header()->objectSnapMode());

    //Common:
    //BS: ATTMODE
    _writer->writeBitShort((short) _document->header()->attributeVisibility());

    //R13 - R14 Only Only(stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //BS: COORDS
        _writer->writeBitShort(0);
    }

    //Common:
    //BS: PDMODE
    _writer->writeBitShort(_document->header()->pointDisplayMode());

    //R13 - R14 Only Only(stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //BS: PICKSTYLE
        _writer->writeBitShort(0);
    }

    //R2004 +:
    if (R2004Plus)
    {
        //BL: Unknown
        _writer->writeBitLong(0);
        //BL: Unknown
        _writer->writeBitLong(0);
        //BL: Unknown
        _writer->writeBitLong(0);
    }

    //Common:
    //BS : USERI1
    _writer->writeBitShort(_document->header()->userShort1());
    //BS : USERI2
    _writer->writeBitShort(_document->header()->userShort2());
    //BS : USERI3
    _writer->writeBitShort(_document->header()->userShort3());
    //BS : USERI4
    _writer->writeBitShort(_document->header()->userShort4());
    //BS : USERI5
    _writer->writeBitShort(_document->header()->userShort5());

    //BS: SPLINESEGS
    _writer->writeBitShort(_document->header()->numberOfSplineSegments());
    //BS : SURFU
    _writer->writeBitShort(_document->header()->surfaceDensityU());
    //BS : SURFV
    _writer->writeBitShort(_document->header()->surfaceDensityV());
    //BS : SURFTYPE
    _writer->writeBitShort(_document->header()->surfaceType());
    //BS : SURFTAB1
    _writer->writeBitShort(_document->header()->surfaceMeshTabulationCount1());
    //BS : SURFTAB2
    _writer->writeBitShort(_document->header()->surfaceMeshTabulationCount2());
    //BS : SPLINETYPE
    _writer->writeBitShort((short) _document->header()->splineType());
    //BS : SHADEDGE
    _writer->writeBitShort((short) _document->header()->shadeEdge());
    //BS : SHADEDIF
    _writer->writeBitShort(_document->header()->shadeDiffuseToAmbientPercentage());
    //BS: UNITMODE
    _writer->writeBitShort(_document->header()->unitMode());
    //BS : MAXACTVP
    _writer->writeBitShort(_document->header()->maxViewportCount());
    //BS : ISOLINES
    _writer->writeBitShort(_document->header()->surfaceIsolineCount());
    //BS : CMLJUST
    _writer->writeBitShort((short) _document->header()->currentMultilineJustification());
    //BS : TEXTQLTY
    _writer->writeBitShort(_document->header()->textQuality());
    //BD : LTSCALE
    _writer->writeBitDouble(_document->header()->lineTypeScale());
    //BD : TEXTSIZE
    _writer->writeBitDouble(_document->header()->textHeightDefault());
    //BD : TRACEWID
    _writer->writeBitDouble(_document->header()->traceWidthDefault());
    //BD : SKETCHINC
    _writer->writeBitDouble(_document->header()->sketchIncrement());
    //BD : FILLETRAD
    _writer->writeBitDouble(_document->header()->filletRadius());
    //BD : THICKNESS
    _writer->writeBitDouble(_document->header()->thicknessDefault());
    //BD : ANGBASE
    _writer->writeBitDouble(_document->header()->angleBase());
    //BD : PDSIZE
    _writer->writeBitDouble(_document->header()->pointDisplaySize());
    //BD : PLINEWID
    _writer->writeBitDouble(_document->header()->polylineWidthDefault());
    //BD : USERR1
    _writer->writeBitDouble(_document->header()->userDouble1());
    //BD : USERR2
    _writer->writeBitDouble(_document->header()->userDouble2());
    //BD : USERR3
    _writer->writeBitDouble(_document->header()->userDouble3());
    //BD : USERR4
    _writer->writeBitDouble(_document->header()->userDouble4());
    //BD : USERR5
    _writer->writeBitDouble(_document->header()->userDouble5());
    //BD : CHAMFERA
    _writer->writeBitDouble(_document->header()->chamferDistance1());
    //BD : CHAMFERB
    _writer->writeBitDouble(_document->header()->chamferDistance2());
    //BD : CHAMFERC
    _writer->writeBitDouble(_document->header()->chamferLength());
    //BD : CHAMFERD
    _writer->writeBitDouble(_document->header()->chamferAngle());
    //BD : FACETRES
    _writer->writeBitDouble(_document->header()->facetResolution());
    //BD : CMLSCALE
    _writer->writeBitDouble(_document->header()->currentMultilineScale());
    //BD : CELTSCALE
    _writer->writeBitDouble(_document->header()->currentEntityLinetypeScale());

    //TV: MENUNAME
    _writer->writeVariableText(_document->header()->menuFileName());

    //Common:
    //BL: TDCREATE(Julian day)
    //BL: TDCREATE(Milliseconds into the day)
    _writer->writeDateTime(_document->header()->createDateTime());
    //BL: TDUPDATE(Julian day)
    //BL: TDUPDATE(Milliseconds into the day)
    _writer->writeDateTime(_document->header()->updateDateTime());

    //R2004 +:
    if (R2004Plus)
    {
        //BL : Unknown
        _writer->writeBitLong(0);
        //BL : Unknown
        _writer->writeBitLong(0);
        //BL : Unknown
        _writer->writeBitLong(0);
    }

    //Common:
    //BL: TDINDWG(Days)
    //BL: TDINDWG(Milliseconds into the day)
    _writer->writeTimeSpan(_document->header()->totalEditingTime());
    //BL: TDUSRTIMER(Days)
    //BL: TDUSRTIMER(Milliseconds into the day)
    _writer->writeTimeSpan(_document->header()->userElapsedTimeSpan());

    //CMC : CECOLOR
    _writer->writeCmColor(_document->header()->currentEntityColor());

    //H : HANDSEED The next handle, with an 8-bit length specifier preceding the handle
    //bytes (standard hex handle form) (code 0). The HANDSEED is not part of the handle
    //stream, but of the normal data stream (relevant for R21 and later).
    _writer->main()->handleReference(_document->header()->handleSeed());

    //H : CLAYER (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->header()->currentLayer()->handle());

    //H: TEXTSTYLE(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->header()->currentTextStyle()->handle());

    //H: CELTYPE(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->header()->currentLineType()->handle());

    //R2007 + Only:
    if (R2007Plus)
    {
        //H: CMATERIAL(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //Common:
    //H: DIMSTYLE (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->header()->dimensionStyleOverrides()->handle());

    //H: CMLSTYLE (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

    //R2000+ Only:
    if (R2000Plus)
    {
        //BD: PSVPSCALE
        _writer->writeBitDouble(_document->header()->viewportDefaultViewScaleFactor());
    }

    //Common:
    //3BD: INSBASE(PSPACE)
    _writer->write3BitDouble(_document->header()->paperSpaceInsertionBase());
    //3BD: EXTMIN(PSPACE)
    _writer->write3BitDouble(_document->header()->paperSpaceExtMin());
    //3BD: EXTMAX(PSPACE)
    _writer->write3BitDouble(_document->header()->paperSpaceExtMax());
    //2RD: LIMMIN(PSPACE)
    _writer->write2RawDouble(_document->header()->paperSpaceLimitsMin());
    //2RD: LIMMAX(PSPACE)
    _writer->write2RawDouble(_document->header()->paperSpaceLimitsMax());
    //BD: ELEVATION(PSPACE)
    _writer->writeBitDouble(_document->header()->paperSpaceElevation());
    //3BD: UCSORG(PSPACE)
    _writer->write3BitDouble(_document->header()->paperSpaceUcsOrigin());
    //3BD: UCSXDIR(PSPACE)
    _writer->write3BitDouble(_document->header()->paperSpaceUcsXAxis());
    //3BD: UCSYDIR(PSPACE)
    _writer->write3BitDouble(_document->header()->paperSpaceUcsYAxis());

    //H: UCSNAME (PSPACE) (hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->header()->paperSpaceUcs()->handle());

    //R2000+ Only:
    if (R2000Plus)
    {
        //H : PUCSORTHOREF (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

        //BS : PUCSORTHOVIEW	??
        _writer->writeBitShort(0);

        //H: PUCSBASE(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

        //3BD: PUCSORGTOP
        _writer->write3BitDouble(_document->header()->paperSpaceOrthographicTopDOrigin());
        //3BD: PUCSORGBOTTOM
        _writer->write3BitDouble(_document->header()->paperSpaceOrthographicBottomDOrigin());
        //3BD: PUCSORGLEFT
        _writer->write3BitDouble(_document->header()->paperSpaceOrthographicLeftDOrigin());
        //3BD: PUCSORGRIGHT
        _writer->write3BitDouble(_document->header()->paperSpaceOrthographicRightDOrigin());
        //3BD: PUCSORGFRONT
        _writer->write3BitDouble(_document->header()->paperSpaceOrthographicFrontDOrigin());
        //3BD: PUCSORGBACK
        _writer->write3BitDouble(_document->header()->paperSpaceOrthographicBackDOrigin());
    }

    //Common:
    //3BD: INSBASE(MSPACE)
    _writer->write3BitDouble(_document->header()->modelSpaceInsertionBase());
    //3BD: EXTMIN(MSPACE)
    _writer->write3BitDouble(_document->header()->modelSpaceExtMin());
    //3BD: EXTMAX(MSPACE)
    _writer->write3BitDouble(_document->header()->modelSpaceExtMax());
    //2RD: LIMMIN(MSPACE)
    _writer->write2RawDouble(_document->header()->modelSpaceLimitsMin());
    //2RD: LIMMAX(MSPACE)
    _writer->write2RawDouble(_document->header()->modelSpaceLimitsMax());
    //BD: ELEVATION(MSPACE)
    _writer->writeBitDouble(_document->header()->elevation());
    //3BD: UCSORG(MSPACE)
    _writer->write3BitDouble(_document->header()->modelSpaceOrigin());
    //3BD: UCSXDIR(MSPACE)
    _writer->write3BitDouble(_document->header()->modelSpaceXAxis());
    //3BD: UCSYDIR(MSPACE)
    _writer->write3BitDouble(_document->header()->modelSpaceYAxis());

    //H: UCSNAME(MSPACE)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->header()->modelSpaceUcs()->handle());

    //R2000 + Only:
    if (R2000Plus)
    {
        //H: UCSORTHOREF(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

        //BS: UCSORTHOVIEW	??
        _writer->writeBitShort(0);

        //H : UCSBASE(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

        //3BD: UCSORGTOP
        _writer->write3BitDouble(_document->header()->modelSpaceOrthographicTopDOrigin());
        //3BD: UCSORGBOTTOM
        _writer->write3BitDouble(_document->header()->modelSpaceOrthographicBottomDOrigin());
        //3BD: UCSORGLEFT
        _writer->write3BitDouble(_document->header()->modelSpaceOrthographicLeftDOrigin());
        //3BD: UCSORGRIGHT
        _writer->write3BitDouble(_document->header()->modelSpaceOrthographicRightDOrigin());
        //3BD: UCSORGFRONT
        _writer->write3BitDouble(_document->header()->modelSpaceOrthographicFrontDOrigin());
        //3BD: UCSORGBACK
        _writer->write3BitDouble(_document->header()->modelSpaceOrthographicBackDOrigin());

        //TV : DIMPOST
        _writer->writeVariableText(_document->header()->dimensionPostFix());
        //TV : DIMAPOST
        _writer->writeVariableText(_document->header()->dimensionAlternateDimensioningSuffix());
    }

    //R13-R14 Only:
    if (R13_14Only)
    {
        //B: DIMTOL
        _writer->writeBit(_document->header()->dimensionGenerateTolerances());
        //B : DIMLIM
        _writer->writeBit(_document->header()->dimensionLimitsGeneration());
        //B : DIMTIH
        _writer->writeBit(_document->header()->dimensionTextInsideHorizontal());
        //B : DIMTOH
        _writer->writeBit(_document->header()->dimensionTextOutsideHorizontal());
        //B : DIMSE1
        _writer->writeBit(_document->header()->dimensionSuppressFirstExtensionLine());
        //B : DIMSE2
        _writer->writeBit(_document->header()->dimensionSuppressSecondExtensionLine());
        //B : DIMALT
        _writer->writeBit(_document->header()->dimensionAlternateUnitDimensioning());
        //B : DIMTOFL
        _writer->writeBit(_document->header()->dimensionTextOutsideExtensions());
        //B : DIMSAH
        _writer->writeBit(_document->header()->dimensionSeparateArrowBlocks());
        //B : DIMTIX
        _writer->writeBit(_document->header()->dimensionTextInsideExtensions());
        //B : DIMSOXD
        _writer->writeBit(_document->header()->dimensionSuppressOutsideExtensions());
        //RC : DIMALTD
        _writer->writeByte((unsigned char) _document->header()->dimensionAlternateUnitDecimalPlaces());
        //RC : DIMZIN
        _writer->writeByte((unsigned char) _document->header()->dimensionZeroHandling());
        //B : DIMSD1
        _writer->writeBit(_document->header()->dimensionSuppressFirstDimensionLine());
        //B : DIMSD2
        _writer->writeBit(_document->header()->dimensionSuppressSecondDimensionLine());
        //RC : DIMTOLJ
        _writer->writeByte((unsigned char) _document->header()->dimensionToleranceAlignment());
        //RC : DIMJUST
        _writer->writeByte((unsigned char) _document->header()->dimensionTextHorizontalAlignment());
        //RC : DIMFIT
        _writer->writeByte((unsigned char) _document->header()->dimensionFit());
        //B : DIMUPT
        _writer->writeBit(_document->header()->dimensionCursorUpdate());
        //RC : DIMTZIN
        _writer->writeByte((unsigned char) _document->header()->dimensionToleranceZeroHandling());
        //RC: DIMALTZ
        _writer->writeByte((unsigned char) _document->header()->dimensionAlternateUnitZeroHandling());
        //RC : DIMALTTZ
        _writer->writeByte((unsigned char) _document->header()->dimensionAlternateUnitToleranceZeroHandling());
        //RC : DIMTAD
        _writer->writeByte((unsigned char) _document->header()->dimensionTextVerticalAlignment());
        //BS : DIMUNIT
        _writer->writeBitShort(_document->header()->dimensionUnit());
        //BS : DIMAUNIT
        _writer->writeBitShort(_document->header()->dimensionAngularDimensionDecimalPlaces());
        //BS : DIMDEC
        _writer->writeBitShort(_document->header()->dimensionDecimalPlaces());
        //BS : DIMTDEC
        _writer->writeBitShort(_document->header()->dimensionToleranceDecimalPlaces());
        //BS : DIMALTU
        _writer->writeBitShort((short) _document->header()->dimensionAlternateUnitFormat());
        //BS : DIMALTTD
        _writer->writeBitShort(_document->header()->dimensionAlternateUnitToleranceDecimalPlaces());

        //H : DIMTXSTY(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, _document->header()->dimensionStyleOverrides()->handle());
    }

    //Common:
    //BD: DIMSCALE
    _writer->writeBitDouble(_document->header()->dimensionScaleFactor());
    //BD : DIMASZ
    _writer->writeBitDouble(_document->header()->dimensionArrowSize());
    //BD : DIMEXO
    _writer->writeBitDouble(_document->header()->dimensionExtensionLineOffset());
    //BD : DIMDLI
    _writer->writeBitDouble(_document->header()->dimensionLineIncrement());
    //BD : DIMEXE
    _writer->writeBitDouble(_document->header()->dimensionExtensionLineExtension());
    //BD : DIMRND
    _writer->writeBitDouble(_document->header()->dimensionRounding());
    //BD : DIMDLE
    _writer->writeBitDouble(_document->header()->dimensionLineExtension());
    //BD : DIMTP
    _writer->writeBitDouble(_document->header()->dimensionPlusTolerance());
    //BD : DIMTM
    _writer->writeBitDouble(_document->header()->dimensionMinusTolerance());

    //R2007 + Only:
    if (R2007Plus)
    {
        //BD: DIMFXL
        _writer->writeBitDouble(_document->header()->dimensionFixedExtensionLineLength());
        //BD : DIMJOGANG
        _writer->writeBitDouble(_document->header()->dimensionJoggedRadiusDimensionTransverseSegmentAngle());
        //BS : DIMTFILL
        _writer->writeBitShort((short) _document->header()->dimensionTextBackgroundFillMode());
        //CMC : DIMTFILLCLR
        _writer->writeCmColor(_document->header()->dimensionTextBackgroundColor());
    }

    //R2000 + Only:
    if (R2000Plus)
    {
        //B: DIMTOL
        _writer->writeBit(_document->header()->dimensionGenerateTolerances());
        //B : DIMLIM
        _writer->writeBit(_document->header()->dimensionLimitsGeneration());
        //B : DIMTIH
        _writer->writeBit(_document->header()->dimensionTextInsideHorizontal());
        //B : DIMTOH
        _writer->writeBit(_document->header()->dimensionTextOutsideHorizontal());
        //B : DIMSE1
        _writer->writeBit(_document->header()->dimensionSuppressFirstExtensionLine());
        //B : DIMSE2
        _writer->writeBit(_document->header()->dimensionSuppressSecondExtensionLine());
        //BS : DIMTAD
        _writer->writeBitShort((short) _document->header()->dimensionTextVerticalAlignment());
        //BS : DIMZIN
        _writer->writeBitShort((short) _document->header()->dimensionZeroHandling());
        //BS : DIMAZIN
        _writer->writeBitShort((short) _document->header()->dimensionAngularZeroHandling());
    }

    //R2007 + Only:
    if (R2007Plus)
    {
        //BS: DIMARCSYM
        _writer->writeBitShort((short) _document->header()->dimensionArcLengthSymbolPosition());
    }

    //Common:
    //BD: DIMTXT
    _writer->writeBitDouble(_document->header()->dimensionTextHeight());
    //BD : DIMCEN
    _writer->writeBitDouble(_document->header()->dimensionCenterMarkSize());
    //BD: DIMTSZ
    _writer->writeBitDouble(_document->header()->dimensionTickSize());
    //BD : DIMALTF
    _writer->writeBitDouble(_document->header()->dimensionAlternateUnitScaleFactor());
    //BD : DIMLFAC
    _writer->writeBitDouble(_document->header()->dimensionLinearScaleFactor());
    //BD : DIMTVP
    _writer->writeBitDouble(_document->header()->dimensionTextVerticalPosition());
    //BD : DIMTFAC
    _writer->writeBitDouble(_document->header()->dimensionToleranceScaleFactor());
    //BD : DIMGAP
    _writer->writeBitDouble(_document->header()->dimensionLineGap());

    //R13 - R14 Only:
    if (R13_14Only)
    {
        //T: DIMPOST
        _writer->writeVariableText(_document->header()->dimensionPostFix());
        //T : DIMAPOST
        _writer->writeVariableText(_document->header()->dimensionAlternateDimensioningSuffix());
        //T : DIMBLK
        _writer->writeVariableText(_document->header()->dimensionBlockName());
        //T : DIMBLK1
        _writer->writeVariableText(_document->header()->dimensionBlockNameFirst());
        //T : DIMBLK2
        _writer->writeVariableText(_document->header()->dimensionBlockNameSecond());
    }

    //R2000 + Only:
    if (R2000Plus)
    {
        //BD: DIMALTRND
        _writer->writeBitDouble(_document->header()->dimensionAlternateUnitRounding());
        //B : DIMALT
        _writer->writeBit(_document->header()->dimensionAlternateUnitDimensioning());
        //BS : DIMALTD
        _writer->writeBitShort(_document->header()->dimensionAlternateUnitDecimalPlaces());
        //B : DIMTOFL
        _writer->writeBit(_document->header()->dimensionTextOutsideExtensions());
        //B : DIMSAH
        _writer->writeBit(_document->header()->dimensionSeparateArrowBlocks());
        //B : DIMTIX
        _writer->writeBit(_document->header()->dimensionTextInsideExtensions());
        //B : DIMSOXD
        _writer->writeBit(_document->header()->dimensionSuppressOutsideExtensions());
    }

    //Common:
    //CMC: DIMCLRD
    _writer->writeCmColor(_document->header()->dimensionLineColor());
    //CMC : DIMCLRE
    _writer->writeCmColor(_document->header()->dimensionExtensionLineColor());
    //CMC : DIMCLRT
    _writer->writeCmColor(_document->header()->dimensionTextColor());

    //R2000 + Only:
    if (R2000Plus)
    {
        //BS: DIMADEC
        _writer->writeBitShort(_document->header()->dimensionAngularDimensionDecimalPlaces());
        //BS : DIMDEC
        _writer->writeBitShort(_document->header()->dimensionDecimalPlaces());
        //BS : DIMTDEC
        _writer->writeBitShort(_document->header()->dimensionToleranceDecimalPlaces());
        //BS : DIMALTU
        _writer->writeBitShort((short) _document->header()->dimensionAlternateUnitFormat());
        //BS : DIMALTTD
        _writer->writeBitShort(_document->header()->dimensionAlternateUnitToleranceDecimalPlaces());
        //BS : DIMAUNIT
        _writer->writeBitShort((short) _document->header()->dimensionAngularUnit());
        //BS : DIMFRAC
        _writer->writeBitShort((short) _document->header()->dimensionFractionFormat());
        //BS : DIMLUNIT
        _writer->writeBitShort((short) _document->header()->dimensionLinearUnitFormat());
        //BS : DIMDSEP
        _writer->writeBitShort((short) _document->header()->dimensionDecimalSeparator());
        //BS : DIMTMOVE
        _writer->writeBitShort((short) _document->header()->dimensionTextMovement());
        //BS : DIMJUST
        _writer->writeBitShort((short) _document->header()->dimensionTextHorizontalAlignment());
        //B : DIMSD1
        _writer->writeBit(_document->header()->dimensionSuppressFirstExtensionLine());
        //B : DIMSD2
        _writer->writeBit(_document->header()->dimensionSuppressSecondExtensionLine());
        //BS : DIMTOLJ
        _writer->writeBitShort((short) _document->header()->dimensionToleranceAlignment());
        //BS : DIMTZIN
        _writer->writeBitShort((short) _document->header()->dimensionToleranceZeroHandling());
        //BS: DIMALTZ
        _writer->writeBitShort((short) _document->header()->dimensionAlternateUnitZeroHandling());
        //BS : DIMALTTZ
        _writer->writeBitShort((short) _document->header()->dimensionAlternateUnitToleranceZeroHandling());
        //B : DIMUPT
        _writer->writeBit(_document->header()->dimensionCursorUpdate());
        //BS : DIMATFIT
        _writer->writeBitShort((short) _document->header()->dimensionDimensionTextArrowFit());
    }

    //R2007 + Only:
    if (R2007Plus)
    {
        //B: DIMFXLON
        _writer->writeBit(_document->header()->dimensionIsExtensionLineLengthFixed());
    }

    //R2010 + Only:
    if (R2010Plus)
    {
        //B: DIMTXTDIRECTION
        _writer->writeBit(_document->header()->dimensionTextDirection() == TextDirection::RightToLeft);
        //BD : DIMALTMZF
        _writer->writeBitDouble(_document->header()->dimensionAltMzf());
        //T : DIMALTMZS
        _writer->writeVariableText(_document->header()->dimensionAltMzs());
        //BD : DIMMZF
        _writer->writeBitDouble(_document->header()->dimensionMzf());
        //T : DIMMZS
        _writer->writeVariableText(_document->header()->dimensionMzs());
    }

    //R2000 + Only:
    if (R2000Plus)
    {
        //H: DIMTXSTY(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DIMLDRBLK(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DIMBLK(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DIMBLK1(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DIMBLK2(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //R2007+ Only:
    if (R2007Plus)
    {
        //H : DIMLTYPE (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DIMLTEX1(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DIMLTEX2(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //R2000+ Only:
    if (R2000Plus)
    {
        //BS: DIMLWD
        _writer->writeBitShort((short) _document->header()->dimensionLineWeight());
        //BS : DIMLWE
        _writer->writeBitShort((short) _document->header()->extensionLineWeight());
    }

    //H: BLOCK CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->blockRecords()->handle());
    //H: LAYER CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->layers()->handle());
    //H: STYLE CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->textStyles()->handle());
    //H: LINETYPE CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->lineTypes()->handle());
    //H: VIEW CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->views()->handle());
    //H: UCS CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->UCSs()->handle());
    //H: VPORT CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->VPorts()->handle());
    //H: APPID CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->appIds()->handle());
    //H: DIMSTYLE CONTROL OBJECT(hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->dimensionStyles()->handle());

    //R13 - R15 Only:
    if (R13_15Only)
    {
        //H: VIEWPORT ENTITY HEADER CONTROL OBJECT(hard owner)
        _writer->handleReference(DwgReferenceType::HardOwnership, 0ULL);
    }

    //Common:
    //H: DICTIONARY(ACAD_GROUP)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->groups()->handle());
    //H: DICTIONARY(ACAD_MLINESTYLE)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->mlineStyles()->handle());

    //H : DICTIONARY (NAMED OBJECTS) (hard owner)
    _writer->handleReference(DwgReferenceType::HardOwnership, _document->rootDictionary()->handle());

    //R2000+ Only:
    if (R2000Plus)
    {
        //BS: TSTACKALIGN, default = 1(not present in DXF)
        _writer->writeBitShort(_document->header()->stackedTextAlignment());
        //BS: TSTACKSIZE, default = 70(not present in DXF)
        _writer->writeBitShort(_document->header()->stackedTextSizePercentage());

        //TV: HYPERLINKBASE
        _writer->writeVariableText(_document->header()->hyperLinkBase());
        //TV : STYLESHEET
        _writer->writeVariableText(_document->header()->styleSheetName());

        //H : DICTIONARY(LAYOUTS)(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, _document->layouts()->handle());
        //H: DICTIONARY(PLOTSETTINGS)(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DICTIONARY(PLOTSTYLES)(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //R2004 +:
    if (R2004Plus)
    {
        //H: DICTIONARY (MATERIALS) (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DICTIONARY (COLORS) (hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
    }

    //R2007 +:
    if (R2007Plus)
    {
        //H: DICTIONARY(VISUALSTYLE)(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

        //R2013+:
        if (R2013Plus)
        {
            //H : UNKNOWN (hard pointer)	//DICTIONARY_VISUALSTYLE
            _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        }
    }

    //R2000 +:
    if (R2000Plus)
    {
        //BL: Flags:

        //CELWEIGHT Flags & 0x001F
        int flags = ((int) _document->header()->currentEntityLineWeight() & 0x1F) |
                    //ENDCAPS Flags & 0x0060
                    (_document->header()->endCaps() << 0x5) |
                    //JOINSTYLE Flags & 0x0180
                    (_document->header()->joinStyle() << 0x7);

        //LWDISPLAY!(Flags & 0x0200)
        if (!_document->header()->displayLineWeight()) { flags |= 0x200; }
        //XEDIT!(Flags & 0x0400)
        if (!_document->header()->xedit()) { flags |= 0x400; }
        //EXTNAMES Flags & 0x0800
        if (_document->header()->extendedNames()) { flags |= 0x800; }
        //PSTYLEMODE Flags & 0x2000
        if (_document->header()->plotStyleMode() == 1) { flags |= 0x2000; }
        //OLESTARTUP Flags & 0x4000
        if (_document->header()->loadOLEObject()) { flags |= 0x4000; }

        _writer->writeBitLong(flags);

        //BS: INSUNITS
        _writer->writeBitShort((short) _document->header()->insUnits());
        //BS : CEPSNTYPE
        _writer->writeBitShort((short) _document->header()->currentEntityPlotStyle());

        if (_document->header()->currentEntityPlotStyle() == EntityPlotStyleType::ByObjectId)
        {
            //H: CPSNID(present only if CEPSNTYPE == 3) (hard pointer)
            _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        }

        //TV: FINGERPRINTGUID
        _writer->writeVariableText(_document->header()->fingerPrintGuid());
        //TV : VERSIONGUID
        _writer->writeVariableText(_document->header()->versionGuid());
    }

    //R2004 +:
    if (R2004Plus)
    {
        //RC: SORTENTS
        _writer->writeByte((unsigned char) _document->header()->entitySortingFlags());
        //RC : INDEXCTL
        _writer->writeByte((unsigned char) _document->header()->indexCreationFlags());
        //RC : HIDETEXT
        _writer->writeByte(_document->header()->hideText());
        //RC : XCLIPFRAME, before R2010 the value can be 0 or 1 only.
        _writer->writeByte(_document->header()->externalReferenceClippingBoundaryType());
        //RC : DIMASSOC
        _writer->writeByte((unsigned char) _document->header()->dimensionAssociativity());
        //RC : HALOGAP
        _writer->writeByte(_document->header()->haloGapPercentage());
        //BS : OBSCUREDCOLOR
        _writer->writeBitShort(_document->header()->obscuredColor().index());
        //BS : INTERSECTIONCOLOR
        _writer->writeBitShort(_document->header()->interfereColor().index());
        //RC : OBSCUREDLTYPE
        _writer->writeByte(_document->header()->obscuredType());
        //RC: INTERSECTIONDISPLAY
        _writer->writeByte(_document->header()->intersectionDisplay());

        //TV : PROJECTNAME
        _writer->writeVariableText(_document->header()->projectName());
    }

    //Common:
    //H: BLOCK_RECORD(*PAPER_SPACE)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->paperSpace()->handle());
    //H: BLOCK_RECORD(*MODEL_SPACE)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->modelSpace()->handle());
    //H: LTYPE(BYLAYER)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->lineTypes()->getValue("ByLayer")->handle());
    //H: LTYPE(BYBLOCK)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->lineTypes()->getValue("ByBlock")->handle());
    //H: LTYPE(CONTINUOUS)(hard pointer)
    _writer->handleReference(DwgReferenceType::HardPointer, _document->lineTypes()->getValue("Continuous")->handle());

    //R2007 +:
    if (R2007Plus)
    {
        //B: CAMERADISPLAY
        _writer->writeBit(_document->header()->cameraDisplayObjects());

        //BL : unknown
        _writer->writeBitLong(0);
        //BL : unknown
        _writer->writeBitLong(0);
        //BD : unknown
        _writer->writeBitDouble(0);

        //BD : STEPSPERSEC
        _writer->writeBitDouble(_document->header()->stepsPerSecond());
        //BD : STEPSIZE
        _writer->writeBitDouble(_document->header()->stepSize());
        //BD : 3DDWFPREC
        _writer->writeBitDouble(_document->header()->dw3DPrecision());
        //BD : LENSLENGTH
        _writer->writeBitDouble(_document->header()->lensLength());
        //BD : CAMERAHEIGHT
        _writer->writeBitDouble(_document->header()->cameraHeight());
        //RC : SOLIDHIST
        _writer->writeByte((unsigned char) _document->header()->solidsRetainHistory());
        //RC : SHOWHIST
        _writer->writeByte((unsigned char) _document->header()->showSolidsHistory());
        //BD : PSOLWIDTH
        _writer->writeBitDouble(_document->header()->sweptSolidWidth());
        //BD : PSOLHEIGHT
        _writer->writeBitDouble(_document->header()->sweptSolidHeight());
        //BD : LOFTANG1
        _writer->writeBitDouble(_document->header()->draftAngleFirstCrossSection());
        //BD : LOFTANG2
        _writer->writeBitDouble(_document->header()->draftAngleSecondCrossSection());
        //BD : LOFTMAG1
        _writer->writeBitDouble(_document->header()->draftMagnitudeFirstCrossSection());
        //BD : LOFTMAG2
        _writer->writeBitDouble(_document->header()->draftMagnitudeSecondCrossSection());
        //BS : LOFTPARAM
        _writer->writeBitShort(_document->header()->solidLoftedShape());
        //RC : LOFTNORMALS
        _writer->writeByte((unsigned char) _document->header()->loftedObjectNormals());
        //BD : LATITUDE
        _writer->writeBitDouble(_document->header()->latitude());
        //BD : LONGITUDE
        _writer->writeBitDouble(_document->header()->longitude());
        //BD : NORTHDIRECTION
        _writer->writeBitDouble(_document->header()->northDirection());
        //BL : TIMEZONE
        _writer->writeBitLong(_document->header()->timeZone());
        //RC : LIGHTGLYPHDISPLAY
        _writer->writeByte((unsigned char) _document->header()->displayLightGlyphs());
        //RC : TILEMODELIGHTSYNCH	??
        _writer->writeByte((unsigned char) '0');
        //RC : DWFFRAME
        _writer->writeByte((unsigned char) _document->header()->dwgUnderlayFramesVisibility());
        //RC : DGNFRAME
        _writer->writeByte((unsigned char) _document->header()->dgnUnderlayFramesVisibility());

        //B : unknown
        _writer->writeBit(false);

        //CMC : INTERFERECOLOR
        _writer->writeCmColor(_document->header()->interfereColor());

        //H : INTERFEREOBJVS(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: INTERFEREVPVS(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);
        //H: DRAGVS(hard pointer)
        _writer->handleReference(DwgReferenceType::HardPointer, 0ULL);

        //RC: CSHADOW
        _writer->writeByte((unsigned char) _document->header()->shadowMode());
        //BD : unknown
        _writer->writeBitDouble(_document->header()->shadowPlaneLocation());
    }

    //R14 +:
    if (_document->header()->version() >= ACadVersion::AC1014)
    {
        //BS : unknown short(type 5 / 6 only) these do not seem to be required,
        _writer->writeBitShort(-1);
        //BS : unknown short(type 5 / 6 only) even for type 5.
        _writer->writeBitShort(-1);
        //BS : unknown short(type 5 / 6 only)
        _writer->writeBitShort(-1);
        //BS : unknown short(type 5 / 6 only)
        _writer->writeBitShort(-1);

        if (R2004Plus)
        {
            //This file versions seem to finish with this values
            _writer->writeBitLong(0);
            _writer->writeBitLong(0);
            _writer->writeBit(false);
        }
    }

    _writer->writeSpearShift();

    //Write the size and merge the streams
    writeSizeAndCrc();
}

void DwgHeaderWriter::writeSizeAndCrc()
{
    //0xCF,0x7B,0x1F,0x23,0xFD,0xDE,0x38,0xA9,0x5F,0x7C,0x68,0xB8,0x4E,0x6D,0x33,0x5F
    _startWriter->writeBytes(DwgSectionDefinition::StartSentinels[sectionName()]);

    CRC8OutputStreamHandler crc(_startWriter->stream(), 0xC0C1);

    //RL : Size of the section.
    crc.write((int) _msmain.str().length());

    //R2010/R2013 (only present if the maintenance version is greater than 3!) or R2018+:
    if (R2010Plus && _document->header()->maintenanceVersion() > 3 || R2018Plus)
    {
        //Unknown (4 unsigned char long), might be part of a 64-bit size.
        crc.write<int>(0);
    }

    crc.write(_msmain.str());

    //Common:
    //RS : CRC for the data section, starting after the sentinel.Use 0xC0C1 for the initial value.
    crc.write<unsigned short>(crc.seed());

    //Ending sentinel: 0x30,0x84,0xE0,0xDC,0x02,0x21,0xC7,0x56,0xA0,0x83,0x97,0x47,0xB1,0x92,0xCC,0xA0
    _startWriter->writeBytes(DwgSectionDefinition::EndSentinels[sectionName()]);
}

}// namespace dwg
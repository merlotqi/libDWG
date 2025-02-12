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

#include <dwg/io/dwg/writers/DwgHeaderWriter_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/CadDocument.h>

namespace dwg {

DwgHeaderWriter::DwgHeaderWriter(std::ostream *stream, CadDocument *document, Encoding encoding)
    : DwgSectionIO(document->Header.Version)
{
    _document = document;
    _encoding = encoding;

    _startWriter = DwgStreamWriterBase::GetStreamWriter(_version, stream, _encoding);
    _writer = DwgStreamWriterBase::GetStreamWriter(_version, &_msmain, _encoding);
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
        _writer->handleReference(DwgReferenceType::Undefined, 0);
    }

    //Common:
    //B: DIMASO
    _writer->writeBit(_document->Header.AssociatedDimensions);
    //B: DIMSHO
    _writer->writeBit(_document->Header.UpdateDimensionsWhileDragging);

    //R13-R14 Only:
    if (R13_14Only)
    {
        //B : DIMSAV Undocumented.
        _writer->writeBit(_document->Header.DIMSAV);
    }

    //Common:
    //B: PLINEGEN
    _writer->writeBit(_document->Header.PolylineLineTypeGeneration);
    //B : ORTHOMODE
    _writer->writeBit(_document->Header.OrthoMode);
    //B: REGENMODE
    _writer->writeBit(_document->Header.RegenerationMode);
    //B : FILLMODE
    _writer->writeBit(_document->Header.FillMode);
    //B : QTEXTMODE
    _writer->writeBit(_document->Header.QuickTextMode);
    //B : PSLTSCALE
    _writer->writeBit(_document->Header.PaperSpaceLineTypeScaling == header::SpaceLineTypeScaling::Normal);
    //B : LIMCHECK
    _writer->writeBit(_document->Header.LimitCheckingOn);

    //R13-R14 Only (stored in registry from R15 onwards):
    if (R13_14Only)
        //B : BLIPMODE
        _writer->writeBit(_document->Header.BlipMode);

    //R2004+:
    if (R2004Plus)
        //B : Undocumented
        _writer->writeBit(false);

    //Common:
    //B: USRTIMER(User timer on / off).
    _writer->writeBit(_document->Header.UserTimer);
    //B : SKPOLY
    _writer->writeBit(_document->Header.SketchPolylines);
    //B : ANGDIR
    _writer->writeBit(_document->Header.AngularDirection != units::AngularDirection::CounterClockWise);
    //B : SPLFRAME
    _writer->writeBit(_document->Header.ShowSplineControlPoints);

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
    _writer->writeBit(_document->Header.MirrorText);
    //B : WORLDVIEW
    _writer->writeBit(_document->Header.WorldView);

    //R13 - R14 Only:
    if (R13_14Only)
    {
        //B: WIREFRAME Undocumented.
        _writer->writeBit(false);
    }

    //Common:
    //B: TILEMODE
    _writer->writeBit(_document->Header.ShowModelSpace);
    //B : PLIMCHECK
    _writer->writeBit(_document->Header.PaperSpaceLimitsChecking);
    //B : VISRETAIN
    _writer->writeBit(_document->Header.RetainXRefDependentVisibilitySettings);

    //R13 - R14 Only(stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //B : DELOBJ
        _writer->writeBit(false);
    }

    //Common:
    //B: DISPSILH
    _writer->writeBit(_document->Header.DisplaySilhouetteCurves);
    //B : PELLIPSE(not present in DXF)
    _writer->writeBit(_document->Header.CreateEllipseAsPolyline);
    //BS: PROXYGRAPHICS
    _writer->writeBitShort((short) (_document->Header.ProxyGraphics ? 1 : 0));

    //R13-R14 Only (stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //BS : DRAGMODE
        _writer->writeBitShort(0);
    }

    //Common:
    //BS: TREEDEPTH
    _writer->writeBitShort(_document->Header.SpatialIndexMaxTreeDepth);
    //BS : LUNITS
    _writer->writeBitShort((short) _document->Header.LinearUnitFormat);
    //BS : LUPREC
    _writer->writeBitShort(_document->Header.LinearUnitPrecision);
    //BS : AUNITS
    _writer->writeBitShort((short) _document->Header.AngularUnit);
    //BS : AUPREC
    _writer->writeBitShort(_document->Header.AngularUnitPrecision);

    //R13 - R14 Only Only(stored in registry from R15 onwards):
    if (R13_14Only)
        //BS: OSMODE
        _writer->writeBitShort((short) _document->Header.ObjectSnapMode);

    //Common:
    //BS: ATTMODE
    _writer->writeBitShort((short) _document->Header.AttributeVisibility);

    //R13 - R14 Only Only(stored in registry from R15 onwards):
    if (R13_14Only)
    {
        //BS: COORDS
        _writer->writeBitShort(0);
    }

    //Common:
    //BS: PDMODE
    _writer->writeBitShort(_document->Header.PointDisplayMode);

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
    _writer->writeBitShort(_document->Header.UserShort1);
    //BS : USERI2
    _writer->writeBitShort(_document->Header.UserShort2);
    //BS : USERI3
    _writer->writeBitShort(_document->Header.UserShort3);
    //BS : USERI4
    _writer->writeBitShort(_document->Header.UserShort4);
    //BS : USERI5
    _writer->writeBitShort(_document->Header.UserShort5);

    //BS: SPLINESEGS
    _writer->writeBitShort(_document->Header.NumberOfSplineSegments);
    //BS : SURFU
    _writer->writeBitShort(_document->Header.SurfaceDensityU);
    //BS : SURFV
    _writer->writeBitShort(_document->Header.SurfaceDensityV);
    //BS : SURFTYPE
    _writer->writeBitShort(_document->Header.SurfaceType);
    //BS : SURFTAB1
    _writer->writeBitShort(_document->Header.SurfaceMeshTabulationCount1);
    //BS : SURFTAB2
    _writer->writeBitShort(_document->Header.SurfaceMeshTabulationCount2);
    //BS : SPLINETYPE
    _writer->writeBitShort((short) _document->Header.SplineType);
    //BS : SHADEDGE
    _writer->writeBitShort((short) _document->Header.ShadeEdge);
    //BS : SHADEDIF
    _writer->writeBitShort(_document->Header.ShadeDiffuseToAmbientPercentage);
    //BS: UNITMODE
    _writer->writeBitShort(_document->Header.UnitMode);
    //BS : MAXACTVP
    _writer->writeBitShort(_document->Header.MaxViewportCount);
    //BS : ISOLINES
    _writer->writeBitShort(_document->Header.SurfaceIsolineCount);
    //BS : CMLJUST
    _writer->writeBitShort((short) _document->Header.CurrentMultilineJustification);
    //BS : TEXTQLTY
    _writer->writeBitShort(_document->Header.TextQuality);
    //BD : LTSCALE
    _writer->writeBitDouble(_document->Header.LineTypeScale);
    //BD : TEXTSIZE
    _writer->writeBitDouble(_document->Header.TextHeightDefault);
    //BD : TRACEWID
    _writer->writeBitDouble(_document->Header.TraceWidthDefault);
    //BD : SKETCHINC
    _writer->writeBitDouble(_document->Header.SketchIncrement);
    //BD : FILLETRAD
    _writer->writeBitDouble(_document->Header.FilletRadius);
    //BD : THICKNESS
    _writer->writeBitDouble(_document->Header.ThicknessDefault);
    //BD : ANGBASE
    _writer->writeBitDouble(_document->Header.AngleBase);
    //BD : PDSIZE
    _writer->writeBitDouble(_document->Header.PointDisplaySize);
    //BD : PLINEWID
    _writer->writeBitDouble(_document->Header.PolylineWidthDefault);
    //BD : USERR1
    _writer->writeBitDouble(_document->Header.UserDouble1);
    //BD : USERR2
    _writer->writeBitDouble(_document->Header.UserDouble2);
    //BD : USERR3
    _writer->writeBitDouble(_document->Header.UserDouble3);
    //BD : USERR4
    _writer->writeBitDouble(_document->Header.UserDouble4);
    //BD : USERR5
    _writer->writeBitDouble(_document->Header.UserDouble5);
    //BD : CHAMFERA
    _writer->writeBitDouble(_document->Header.ChamferDistance1);
    //BD : CHAMFERB
    _writer->writeBitDouble(_document->Header.ChamferDistance2);
    //BD : CHAMFERC
    _writer->writeBitDouble(_document->Header.ChamferLength);
    //BD : CHAMFERD
    _writer->writeBitDouble(_document->Header.ChamferAngle);
    //BD : FACETRES
    _writer->writeBitDouble(_document->Header.FacetResolution);
    //BD : CMLSCALE
    _writer->writeBitDouble(_document->Header.CurrentMultilineScale);
    //BD : CELTSCALE
    _writer->writeBitDouble(_document->Header.CurrentEntityLinetypeScale);

    //TV: MENUNAME
    _writer->writeVariableText(_document->Header.MenuFileName);

    //Common:
    //BL: TDCREATE(Julian day)
    //BL: TDCREATE(Milliseconds into the day)
    _writer->writeDateTime(_document->Header.CreateDateTime);
    //BL: TDUPDATE(Julian day)
    //BL: TDUPDATE(Milliseconds into the day)
    _writer->writeDateTime(_document->Header.UpdateDateTime);

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
    _writer->writeTimeSpan(_document->Header.TotalEditingTime);
    //BL: TDUSRTIMER(Days)
    //BL: TDUSRTIMER(Milliseconds into the day)
    _writer->writeTimeSpan(_document->Header.UserElapsedTimeSpan);

    //CMC : CECOLOR
    _writer->writeCmColor(_document->Header.CurrentEntityColor);

    //H : HANDSEED The next handle, with an 8-bit length specifier preceding the handle
    //bytes (standard hex handle form) (code 0). The HANDSEED is not part of the handle
    //stream, but of the normal data stream (relevant for R21 and later).
    _writer->Main()->HandleReference(_document->Header.HandleSeed);

    //H : CLAYER (hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->Header.CurrentLayer.Handle());

    //H: TEXTSTYLE(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->Header.CurrentTextStyle.Handle());

    //H: CELTYPE(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->Header.CurrentLineType.Handle());

    //R2007 + Only:
    if (R2007Plus)
    {
        //H: CMATERIAL(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
    }

    //Common:
    //H: DIMSTYLE (hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->Header.DimensionStyleOverrides.Handle());

    //H: CMLSTYLE (hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, 0);

    //R2000+ Only:
    if (R2000Plus)
    {
        //BD: PSVPSCALE
        _writer->writeBitDouble(_document->Header.ViewportDefaultViewScaleFactor);
    }

    //Common:
    //3BD: INSBASE(PSPACE)
    _writer->write3BitDouble(_document->Header.PaperSpaceInsertionBase);
    //3BD: EXTMIN(PSPACE)
    _writer->write3BitDouble(_document->Header.PaperSpaceExtMin);
    //3BD: EXTMAX(PSPACE)
    _writer->write3BitDouble(_document->Header.PaperSpaceExtMax);
    //2RD: LIMMIN(PSPACE)
    _writer->write2RawDouble(_document->Header.PaperSpaceLimitsMin);
    //2RD: LIMMAX(PSPACE)
    _writer->write2RawDouble(_document->Header.PaperSpaceLimitsMax);
    //BD: ELEVATION(PSPACE)
    _writer->writeBitDouble(_document->Header.PaperSpaceElevation);
    //3BD: UCSORG(PSPACE)
    _writer->write3BitDouble(_document->Header.PaperSpaceUcsOrigin);
    //3BD: UCSXDIR(PSPACE)
    _writer->write3BitDouble(_document->Header.PaperSpaceUcsXAxis);
    //3BD: UCSYDIR(PSPACE)
    _writer->write3BitDouble(_document->Header.PaperSpaceUcsYAxis);

    //H: UCSNAME (PSPACE) (hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->Header.PaperSpaceUcs.Handle());

    //R2000+ Only:
    if (R2000Plus)
    {
        //H : PUCSORTHOREF (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);

        //BS : PUCSORTHOVIEW	??
        _writer->writeBitShort(0);

        //H: PUCSBASE(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);

        //3BD: PUCSORGTOP
        _writer->write3BitDouble(_document->Header.PaperSpaceOrthographicTopDOrigin);
        //3BD: PUCSORGBOTTOM
        _writer->write3BitDouble(_document->Header.PaperSpaceOrthographicBottomDOrigin);
        //3BD: PUCSORGLEFT
        _writer->write3BitDouble(_document->Header.PaperSpaceOrthographicLeftDOrigin);
        //3BD: PUCSORGRIGHT
        _writer->write3BitDouble(_document->Header.PaperSpaceOrthographicRightDOrigin);
        //3BD: PUCSORGFRONT
        _writer->write3BitDouble(_document->Header.PaperSpaceOrthographicFrontDOrigin);
        //3BD: PUCSORGBACK
        _writer->write3BitDouble(_document->Header.PaperSpaceOrthographicBackDOrigin);
    }

    //Common:
    //3BD: INSBASE(MSPACE)
    _writer->write3BitDouble(_document->Header.ModelSpaceInsertionBase);
    //3BD: EXTMIN(MSPACE)
    _writer->write3BitDouble(_document->Header.ModelSpaceExtMin);
    //3BD: EXTMAX(MSPACE)
    _writer->write3BitDouble(_document->Header.ModelSpaceExtMax);
    //2RD: LIMMIN(MSPACE)
    _writer->write2RawDouble(_document->Header.ModelSpaceLimitsMin);
    //2RD: LIMMAX(MSPACE)
    _writer->write2RawDouble(_document->Header.ModelSpaceLimitsMax);
    //BD: ELEVATION(MSPACE)
    _writer->writeBitDouble(_document->Header.Elevation);
    //3BD: UCSORG(MSPACE)
    _writer->write3BitDouble(_document->Header.ModelSpaceOrigin);
    //3BD: UCSXDIR(MSPACE)
    _writer->write3BitDouble(_document->Header.ModelSpaceXAxis);
    //3BD: UCSYDIR(MSPACE)
    _writer->write3BitDouble(_document->Header.ModelSpaceYAxis);

    //H: UCSNAME(MSPACE)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->Header.ModelSpaceUcs.Handle());

    //R2000 + Only:
    if (R2000Plus)
    {
        //H: UCSORTHOREF(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);

        //BS: UCSORTHOVIEW	??
        _writer->writeBitShort(0);

        //H : UCSBASE(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);

        //3BD: UCSORGTOP
        _writer->write3BitDouble(_document->Header.ModelSpaceOrthographicTopDOrigin);
        //3BD: UCSORGBOTTOM
        _writer->write3BitDouble(_document->Header.ModelSpaceOrthographicBottomDOrigin);
        //3BD: UCSORGLEFT
        _writer->write3BitDouble(_document->Header.ModelSpaceOrthographicLeftDOrigin);
        //3BD: UCSORGRIGHT
        _writer->write3BitDouble(_document->Header.ModelSpaceOrthographicRightDOrigin);
        //3BD: UCSORGFRONT
        _writer->write3BitDouble(_document->Header.ModelSpaceOrthographicFrontDOrigin);
        //3BD: UCSORGBACK
        _writer->write3BitDouble(_document->Header.ModelSpaceOrthographicBackDOrigin);

        //TV : DIMPOST
        _writer->writeVariableText(_document->Header.DimensionPostFix);
        //TV : DIMAPOST
        _writer->writeVariableText(_document->Header.DimensionAlternateDimensioningSuffix);
    }

    //R13-R14 Only:
    if (R13_14Only)
    {
        //B: DIMTOL
        _writer->writeBit(_document->Header.DimensionGenerateTolerances);
        //B : DIMLIM
        _writer->writeBit(_document->Header.DimensionLimitsGeneration);
        //B : DIMTIH
        _writer->writeBit(_document->Header.DimensionTextInsideHorizontal);
        //B : DIMTOH
        _writer->writeBit(_document->Header.DimensionTextOutsideHorizontal);
        //B : DIMSE1
        _writer->writeBit(_document->Header.DimensionSuppressFirstExtensionLine);
        //B : DIMSE2
        _writer->writeBit(_document->Header.DimensionSuppressSecondExtensionLine);
        //B : DIMALT
        _writer->writeBit(_document->Header.DimensionAlternateUnitDimensioning);
        //B : DIMTOFL
        _writer->writeBit(_document->Header.DimensionTextOutsideExtensions);
        //B : DIMSAH
        _writer->writeBit(_document->Header.DimensionSeparateArrowBlocks);
        //B : DIMTIX
        _writer->writeBit(_document->Header.DimensionTextInsideExtensions);
        //B : DIMSOXD
        _writer->writeBit(_document->Header.DimensionSuppressOutsideExtensions);
        //RC : DIMALTD
        _writer->writeByte((unsigned char) _document->Header.DimensionAlternateUnitDecimalPlaces);
        //RC : DIMZIN
        _writer->writeByte((unsigned char) _document->Header.DimensionZeroHandling);
        //B : DIMSD1
        _writer->writeBit(_document->Header.DimensionSuppressFirstDimensionLine);
        //B : DIMSD2
        _writer->writeBit(_document->Header.DimensionSuppressSecondDimensionLine);
        //RC : DIMTOLJ
        _writer->writeByte((unsigned char) _document->Header.DimensionToleranceAlignment);
        //RC : DIMJUST
        _writer->writeByte((unsigned char) _document->Header.DimensionTextHorizontalAlignment);
        //RC : DIMFIT
        _writer->writeByte((unsigned char) _document->Header.DimensionFit);
        //B : DIMUPT
        _writer->writeBit(_document->Header.DimensionCursorUpdate);
        //RC : DIMTZIN
        _writer->writeByte((unsigned char) _document->Header.DimensionToleranceZeroHandling);
        //RC: DIMALTZ
        _writer->writeByte((unsigned char) _document->Header.DimensionAlternateUnitZeroHandling);
        //RC : DIMALTTZ
        _writer->writeByte((unsigned char) _document->Header.DimensionAlternateUnitToleranceZeroHandling);
        //RC : DIMTAD
        _writer->writeByte((unsigned char) _document->Header.DimensionTextVerticalAlignment);
        //BS : DIMUNIT
        _writer->writeBitShort(_document->Header.DimensionUnit);
        //BS : DIMAUNIT
        _writer->writeBitShort(_document->Header.DimensionAngularDimensionDecimalPlaces);
        //BS : DIMDEC
        _writer->writeBitShort(_document->Header.DimensionDecimalPlaces);
        //BS : DIMTDEC
        _writer->writeBitShort(_document->Header.DimensionToleranceDecimalPlaces);
        //BS : DIMALTU
        _writer->writeBitShort((short) _document->Header.DimensionAlternateUnitFormat);
        //BS : DIMALTTD
        _writer->writeBitShort(_document->Header.DimensionAlternateUnitToleranceDecimalPlaces);

        //H : DIMTXSTY(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, _document->Header.DimensionStyleOverrides.Handle());
    }

    //Common:
    //BD: DIMSCALE
    _writer->writeBitDouble(_document->Header.DimensionScaleFactor);
    //BD : DIMASZ
    _writer->writeBitDouble(_document->Header.DimensionArrowSize);
    //BD : DIMEXO
    _writer->writeBitDouble(_document->Header.DimensionExtensionLineOffset);
    //BD : DIMDLI
    _writer->writeBitDouble(_document->Header.DimensionLineIncrement);
    //BD : DIMEXE
    _writer->writeBitDouble(_document->Header.DimensionExtensionLineExtension);
    //BD : DIMRND
    _writer->writeBitDouble(_document->Header.DimensionRounding);
    //BD : DIMDLE
    _writer->writeBitDouble(_document->Header.DimensionLineExtension);
    //BD : DIMTP
    _writer->writeBitDouble(_document->Header.DimensionPlusTolerance);
    //BD : DIMTM
    _writer->writeBitDouble(_document->Header.DimensionMinusTolerance);

    //R2007 + Only:
    if (R2007Plus)
    {
        //BD: DIMFXL
        _writer->writeBitDouble(_document->Header.DimensionFixedExtensionLineLength);
        //BD : DIMJOGANG
        _writer->writeBitDouble(_document->Header.DimensionJoggedRadiusDimensionTransverseSegmentAngle);
        //BS : DIMTFILL
        _writer->writeBitShort((short) _document->Header.DimensionTextBackgroundFillMode);
        //CMC : DIMTFILLCLR
        _writer->writeCmColor(_document->Header.DimensionTextBackgroundColor);
    }

    //R2000 + Only:
    if (R2000Plus)
    {
        //B: DIMTOL
        _writer->writeBit(_document->Header.DimensionGenerateTolerances);
        //B : DIMLIM
        _writer->writeBit(_document->Header.DimensionLimitsGeneration);
        //B : DIMTIH
        _writer->writeBit(_document->Header.DimensionTextInsideHorizontal);
        //B : DIMTOH
        _writer->writeBit(_document->Header.DimensionTextOutsideHorizontal);
        //B : DIMSE1
        _writer->writeBit(_document->Header.DimensionSuppressFirstExtensionLine);
        //B : DIMSE2
        _writer->writeBit(_document->Header.DimensionSuppressSecondExtensionLine);
        //BS : DIMTAD
        _writer->writeBitShort((short) _document->Header.DimensionTextVerticalAlignment);
        //BS : DIMZIN
        _writer->writeBitShort((short) _document->Header.DimensionZeroHandling);
        //BS : DIMAZIN
        _writer->writeBitShort((short) _document->Header.DimensionAngularZeroHandling);
    }

    //R2007 + Only:
    if (R2007Plus)
    {
        //BS: DIMARCSYM
        _writer->writeBitShort((short) _document->Header.DimensionArcLengthSymbolPosition);
    }

    //Common:
    //BD: DIMTXT
    _writer->writeBitDouble(_document->Header.DimensionTextHeight);
    //BD : DIMCEN
    _writer->writeBitDouble(_document->Header.DimensionCenterMarkSize);
    //BD: DIMTSZ
    _writer->writeBitDouble(_document->Header.DimensionTickSize);
    //BD : DIMALTF
    _writer->writeBitDouble(_document->Header.DimensionAlternateUnitScaleFactor);
    //BD : DIMLFAC
    _writer->writeBitDouble(_document->Header.DimensionLinearScaleFactor);
    //BD : DIMTVP
    _writer->writeBitDouble(_document->Header.DimensionTextVerticalPosition);
    //BD : DIMTFAC
    _writer->writeBitDouble(_document->Header.DimensionToleranceScaleFactor);
    //BD : DIMGAP
    _writer->writeBitDouble(_document->Header.DimensionLineGap);

    //R13 - R14 Only:
    if (R13_14Only)
    {
        //T: DIMPOST
        _writer->writeVariableText(_document->Header.DimensionPostFix);
        //T : DIMAPOST
        _writer->writeVariableText(_document->Header.DimensionAlternateDimensioningSuffix);
        //T : DIMBLK
        _writer->writeVariableText(_document->Header.DimensionBlockName);
        //T : DIMBLK1
        _writer->writeVariableText(_document->Header.DimensionBlockNameFirst);
        //T : DIMBLK2
        _writer->writeVariableText(_document->Header.DimensionBlockNameSecond);
    }

    //R2000 + Only:
    if (R2000Plus)
    {
        //BD: DIMALTRND
        _writer->writeBitDouble(_document->Header.DimensionAlternateUnitRounding);
        //B : DIMALT
        _writer->writeBit(_document->Header.DimensionAlternateUnitDimensioning);
        //BS : DIMALTD
        _writer->writeBitShort(_document->Header.DimensionAlternateUnitDecimalPlaces);
        //B : DIMTOFL
        _writer->writeBit(_document->Header.DimensionTextOutsideExtensions);
        //B : DIMSAH
        _writer->writeBit(_document->Header.DimensionSeparateArrowBlocks);
        //B : DIMTIX
        _writer->writeBit(_document->Header.DimensionTextInsideExtensions);
        //B : DIMSOXD
        _writer->writeBit(_document->Header.DimensionSuppressOutsideExtensions);
    }

    //Common:
    //CMC: DIMCLRD
    _writer->writeCmColor(_document->Header.DimensionLineColor);
    //CMC : DIMCLRE
    _writer->writeCmColor(_document->Header.DimensionExtensionLineColor);
    //CMC : DIMCLRT
    _writer->writeCmColor(_document->Header.DimensionTextColor);

    //R2000 + Only:
    if (R2000Plus)
    {
        //BS: DIMADEC
        _writer->writeBitShort(_document->Header.DimensionAngularDimensionDecimalPlaces);
        //BS : DIMDEC
        _writer->writeBitShort(_document->Header.DimensionDecimalPlaces);
        //BS : DIMTDEC
        _writer->writeBitShort(_document->Header.DimensionToleranceDecimalPlaces);
        //BS : DIMALTU
        _writer->writeBitShort((short) _document->Header.DimensionAlternateUnitFormat);
        //BS : DIMALTTD
        _writer->writeBitShort(_document->Header.DimensionAlternateUnitToleranceDecimalPlaces);
        //BS : DIMAUNIT
        _writer->writeBitShort((short) _document->Header.DimensionAngularUnit);
        //BS : DIMFRAC
        _writer->writeBitShort((short) _document->Header.DimensionFractionFormat);
        //BS : DIMLUNIT
        _writer->writeBitShort((short) _document->Header.DimensionLinearUnitFormat);
        //BS : DIMDSEP
        _writer->writeBitShort((short) _document->Header.DimensionDecimalSeparator);
        //BS : DIMTMOVE
        _writer->writeBitShort((short) _document->Header.DimensionTextMovement);
        //BS : DIMJUST
        _writer->writeBitShort((short) _document->Header.DimensionTextHorizontalAlignment);
        //B : DIMSD1
        _writer->writeBit(_document->Header.DimensionSuppressFirstExtensionLine);
        //B : DIMSD2
        _writer->writeBit(_document->Header.DimensionSuppressSecondExtensionLine);
        //BS : DIMTOLJ
        _writer->writeBitShort((short) _document->Header.DimensionToleranceAlignment);
        //BS : DIMTZIN
        _writer->writeBitShort((short) _document->Header.DimensionToleranceZeroHandling);
        //BS: DIMALTZ
        _writer->writeBitShort((short) _document->Header.DimensionAlternateUnitZeroHandling);
        //BS : DIMALTTZ
        _writer->writeBitShort((short) _document->Header.DimensionAlternateUnitToleranceZeroHandling);
        //B : DIMUPT
        _writer->writeBit(_document->Header.DimensionCursorUpdate);
        //BS : DIMATFIT
        _writer->writeBitShort((short) _document->Header.DimensionDimensionTextArrowFit);
    }

    //R2007 + Only:
    if (R2007Plus)
    {
        //B: DIMFXLON
        _writer->writeBit(_document->Header.DimensionIsExtensionLineLengthFixed);
    }

    //R2010 + Only:
    if (R2010Plus)
    {
        //B: DIMTXTDIRECTION
        _writer->writeBit(_document->Header.DimensionTextDirection == tables::TextDirection::RightToLeft);
        //BD : DIMALTMZF
        _writer->writeBitDouble(_document->Header.DimensionAltMzf);
        //T : DIMALTMZS
        _writer->writeVariableText(_document->Header.DimensionAltMzs);
        //BD : DIMMZF
        _writer->writeBitDouble(_document->Header.DimensionMzf);
        //T : DIMMZS
        _writer->writeVariableText(_document->Header.DimensionMzs);
    }

    //R2000 + Only:
    if (R2000Plus)
    {
        //H: DIMTXSTY(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DIMLDRBLK(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DIMBLK(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DIMBLK1(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DIMBLK2(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
    }

    //R2007+ Only:
    if (R2007Plus)
    {
        //H : DIMLTYPE (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DIMLTEX1(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DIMLTEX2(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
    }

    //R2000+ Only:
    if (R2000Plus)
    {
        //BS: DIMLWD
        _writer->writeBitShort((short) _document->Header.DimensionLineWeight);
        //BS : DIMLWE
        _writer->writeBitShort((short) _document->Header.ExtensionLineWeight);
    }

    //H: BLOCK CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->BlockRecords.Handle());
    //H: LAYER CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->Layers.Handle());
    //H: STYLE CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->TextStyles.Handle());
    //H: LINETYPE CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->LineTypes.Handle());
    //H: VIEW CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->Views.Handle());
    //H: UCS CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->UCSs.Handle());
    //H: VPORT CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->VPorts.Handle());
    //H: APPID CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->AppIds.Handle());
    //H: DIMSTYLE CONTROL OBJECT(hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->DimensionStyles.Handle());

    //R13 - R15 Only:
    if (R13_15Only)
    {
        //H: VIEWPORT ENTITY HEADER CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership, 0);
    }

    //Common:
    //H: DICTIONARY(ACAD_GROUP)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->Groups.Handle());
    //H: DICTIONARY(ACAD_MLINESTYLE)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->MLineStyles.Handle());

    //H : DICTIONARY (NAMED OBJECTS) (hard owner)
    _writer->HandleReference(DwgReferenceType::HardOwnership, _document->_rootDictionary.Handle());

    //R2000+ Only:
    if (R2000Plus)
    {
        //BS: TSTACKALIGN, default = 1(not present in DXF)
        _writer->writeBitShort(_document->Header.StackedTextAlignment);
        //BS: TSTACKSIZE, default = 70(not present in DXF)
        _writer->writeBitShort(_document->Header.StackedTextSizePercentage);

        //TV: HYPERLINKBASE
        _writer->writeVariableText(_document->Header.HyperLinkBase);
        //TV : STYLESHEET
        _writer->writeVariableText(_document->Header.StyleSheetName);

        //H : DICTIONARY(LAYOUTS)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, _document->Layouts.Handle());
        //H: DICTIONARY(PLOTSETTINGS)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DICTIONARY(PLOTSTYLES)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
    }

    //R2004 +:
    if (R2004Plus)
    {
        //H: DICTIONARY (MATERIALS) (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DICTIONARY (COLORS) (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
    }

    //R2007 +:
    if (R2007Plus)
    {
        //H: DICTIONARY(VISUALSTYLE)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);

        //R2013+:
        if (R2013Plus)
        {
            //H : UNKNOWN (hard pointer)	//DICTIONARY_VISUALSTYLE
            _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        }
    }

    //R2000 +:
    if (R2000Plus)
    {
        //BL: Flags:

        //CELWEIGHT Flags & 0x001F
        int flags = ((int) _document->Header.CurrentEntityLineWeight & 0x1F) |
                    //ENDCAPS Flags & 0x0060
                    (_document->Header.EndCaps << 0x5) |
                    //JOINSTYLE Flags & 0x0180
                    (_document->Header.JoinStyle << 0x7);

        //LWDISPLAY!(Flags & 0x0200)
        if (!_document->Header.DisplayLineWeight) { flags |= 0x200; }
        //XEDIT!(Flags & 0x0400)
        if (!_document->Header.XEdit) { flags |= 0x400; }
        //EXTNAMES Flags & 0x0800
        if (_document->Header.ExtendedNames) { flags |= 0x800; }
        //PSTYLEMODE Flags & 0x2000
        if (_document->Header.PlotStyleMode == 1) { flags |= 0x2000; }
        //OLESTARTUP Flags & 0x4000
        if (_document->Header.LoadOLEObject) { flags |= 0x4000; }

        _writer->writeBitLong(flags);

        //BS: INSUNITS
        _writer->writeBitShort((short) _document->Header.InsUnits);
        //BS : CEPSNTYPE
        _writer->writeBitShort((short) _document->Header.CurrentEntityPlotStyle);

        if (_document->Header.CurrentEntityPlotStyle == header::EntityPlotStyleType::ByObjectId)
        {
            //H: CPSNID(present only if CEPSNTYPE == 3) (hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        }

        //TV: FINGERPRINTGUID
        _writer->writeVariableText(_document->Header.FingerPrintGuid);
        //TV : VERSIONGUID
        _writer->writeVariableText(_document->Header.VersionGuid);
    }

    //R2004 +:
    if (R2004Plus)
    {
        //RC: SORTENTS
        _writer->writeByte((unsigned char) _document->Header.EntitySortingFlags);
        //RC : INDEXCTL
        _writer->writeByte((unsigned char) _document->Header.IndexCreationFlags);
        //RC : HIDETEXT
        _writer->writeByte(_document->Header.HideText);
        //RC : XCLIPFRAME, before R2010 the value can be 0 or 1 only.
        _writer->writeByte(_document->Header.ExternalReferenceClippingBoundaryType);
        //RC : DIMASSOC
        _writer->writeByte((unsigned char) _document->Header.DimensionAssociativity);
        //RC : HALOGAP
        _writer->writeByte(_document->Header.HaloGapPercentage);
        //BS : OBSCUREDCOLOR
        _writer->writeBitShort(_document->Header.ObscuredColor.Index());
        //BS : INTERSECTIONCOLOR
        _writer->writeBitShort(_document->Header.InterfereColor.Index());
        //RC : OBSCUREDLTYPE
        _writer->writeByte(_document->Header.ObscuredType);
        //RC: INTERSECTIONDISPLAY
        _writer->writeByte(_document->Header.IntersectionDisplay);

        //TV : PROJECTNAME
        _writer->writeVariableText(_document->Header.ProjectName);
    }

    //Common:
    //H: BLOCK_RECORD(*PAPER_SPACE)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->PaperSpace().Handle());
    //H: BLOCK_RECORD(*MODEL_SPACE)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->ModelSpace().Handle());
    //H: LTYPE(BYLAYER)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->LineTypes["ByLayer"].Handle());
    //H: LTYPE(BYBLOCK)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->LineTypes["ByBlock"].Handle());
    //H: LTYPE(CONTINUOUS)(hard pointer)
    _writer->HandleReference(DwgReferenceType::HardPointer, _document->LineTypes["Continuous"].Handle());

    //R2007 +:
    if (R2007Plus)
    {
        //B: CAMERADISPLAY
        _writer->writeBit(_document->Header.CameraDisplayObjects);

        //BL : unknown
        _writer->writeBitLong(0);
        //BL : unknown
        _writer->writeBitLong(0);
        //BD : unknown
        _writer->writeBitDouble(0);

        //BD : STEPSPERSEC
        _writer->writeBitDouble(_document->Header.StepsPerSecond);
        //BD : STEPSIZE
        _writer->writeBitDouble(_document->Header.StepSize);
        //BD : 3DDWFPREC
        _writer->writeBitDouble(_document->Header.Dw3DPrecision);
        //BD : LENSLENGTH
        _writer->writeBitDouble(_document->Header.LensLength);
        //BD : CAMERAHEIGHT
        _writer->writeBitDouble(_document->Header.CameraHeight);
        //RC : SOLIDHIST
        _writer->writeByte((unsigned char) _document->Header.SolidsRetainHistory);
        //RC : SHOWHIST
        _writer->writeByte((unsigned char) _document->Header.ShowSolidsHistory);
        //BD : PSOLWIDTH
        _writer->writeBitDouble(_document->Header.SweptSolidWidth);
        //BD : PSOLHEIGHT
        _writer->writeBitDouble(_document->Header.SweptSolidHeight);
        //BD : LOFTANG1
        _writer->writeBitDouble(_document->Header.DraftAngleFirstCrossSection);
        //BD : LOFTANG2
        _writer->writeBitDouble(_document->Header.DraftAngleSecondCrossSection);
        //BD : LOFTMAG1
        _writer->writeBitDouble(_document->Header.DraftMagnitudeFirstCrossSection);
        //BD : LOFTMAG2
        _writer->writeBitDouble(_document->Header.DraftMagnitudeSecondCrossSection);
        //BS : LOFTPARAM
        _writer->writeBitShort(_document->Header.SolidLoftedShape);
        //RC : LOFTNORMALS
        _writer->writeByte((unsigned char) _document->Header.LoftedObjectNormals);
        //BD : LATITUDE
        _writer->writeBitDouble(_document->Header.Latitude);
        //BD : LONGITUDE
        _writer->writeBitDouble(_document->Header.Longitude);
        //BD : NORTHDIRECTION
        _writer->writeBitDouble(_document->Header.NorthDirection);
        //BL : TIMEZONE
        _writer->writeBitLong(_document->Header.TimeZone);
        //RC : LIGHTGLYPHDISPLAY
        _writer->writeByte((unsigned char) _document->Header.DisplayLightGlyphs);
        //RC : TILEMODELIGHTSYNCH	??
        _writer->writeByte((unsigned char) '0');
        //RC : DWFFRAME
        _writer->writeByte((unsigned char) _document->Header.DwgUnderlayFramesVisibility);
        //RC : DGNFRAME
        _writer->writeByte((unsigned char) _document->Header.DgnUnderlayFramesVisibility);

        //B : unknown
        _writer->writeBit(false);

        //CMC : INTERFERECOLOR
        _writer->writeCmColor(_document->Header.InterfereColor);

        //H : INTERFEREOBJVS(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: INTERFEREVPVS(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);
        //H: DRAGVS(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, 0);

        //RC: CSHADOW
        _writer->writeByte((unsigned char) _document->Header.ShadowMode);
        //BD : unknown
        _writer->writeBitDouble(_document->Header.ShadowPlaneLocation);
    }

    //R14 +:
    if (_document->Header.Version >= ACadVersion::AC1014)
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
    _startWriter->WriteBytes(DwgSectionDefinition::StartSentinels[SectionName()]);

    CRC8StreamHandler *crc = new CRC8StreamHandler(_startWriter->Stream(), 0xC0C1);
    StreamIO swriter = new StreamIO(crc);

    //RL : Size of the section.
    swriter.Write((int) _msmain.Length);

    //R2010/R2013 (only present if the maintenance version is greater than 3!) or R2018+:
    if (R2010Plus && _document->Header.MaintenanceVersion > 3 || R2018Plus)
    {
        //Unknown (4 unsigned char long), might be part of a 64-bit size.
        swriter.Write<int>(0);
    }

    crc.Write(_msmain.GetBuffer(), 0, (int) _msmain.Length);
    0.


            //Common:
            //RS : CRC for the data section, starting after the sentinel.Use 0xC0C1 for the initial value.
            swriter.Write<unsigned short>(crc->Seed);

    //Ending sentinel: 0x30,0x84,0xE0,0xDC,0x02,0x21,0xC7,0x56,0xA0,0x83,0x97,0x47,0xB1,0x92,0xCC,0xA0
    _startWriter->WriteBytes(DwgSectionDefinition::EndSentinels[SectionName()]);
}

}// namespace dwg
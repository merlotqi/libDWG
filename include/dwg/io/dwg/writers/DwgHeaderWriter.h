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

#include <dwg/io/dwg/DwgSectionIO.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter.h>
#include <dwg/CadDocument.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase.h>

#include <sstream>

namespace dwg {
namespace io {

class DwgHeaderWriter : DwgSectionIO
{
        public:
    std::string SectionName() const override {return DwgSectionDefinition::Header;}

private:
    std::ostringstream _msmain;
    IDwgStreamWriter* _startWriter;
    IDwgStreamWriter* _writer;
    CadDocument* _document;
    header::CadHeader _header;
    Encoding _encoding;

public:
    DwgHeaderWriter(std::ostream* stream, CadDocument* document, Encoding encoding)
        : DwgSectionIO(document->Header.Version)
    {
        _document = document;
        _header = document->Header;
        _encoding = encoding;

        _startWriter = DwgStreamWriterBase::GetStreamWriter(
                _version, stream, _encoding);
        _writer = DwgStreamWriterBase::GetStreamWriter(
                _version, &_msmain, _encoding);
    }

    void Write()
    {
        //+R2007 Only:
        if (R2007Plus)
        {
            //Setup the writers
            _writer = DwgStreamWriterBase::GetMergedWriter(
                    _version, &_msmain, _encoding);
            _writer->SavePositonForSize();
        }

        //R2013+:
        if (R2013Plus)
        {
            //BLL : Variable REQUIREDVERSIONS, default value 0, read only.
            _writer->WriteBitLongLong(0);
        }

        //Common:
        //BD : Unknown, default value 412148564080.0
        _writer->WriteBitDouble(412148564080.0);
        //BD: Unknown, default value 1.0
        _writer->WriteBitDouble(1.0);
        //BD: Unknown, default value 1.0
        _writer->WriteBitDouble(1.0);
        //BD: Unknown, default value 1.0
        _writer->WriteBitDouble(1.0);

        //TV: Unknown text string, default "m"
        _writer->WriteVariableText("m");
        //TV: Unknown text string, default ""
        _writer->WriteVariableText("");
        //TV: Unknown text string, default ""
        _writer->WriteVariableText("");
        //TV: Unknown text string, default ""
        _writer->WriteVariableText("");

        //BL : Unknown long, default value 24L
        _writer->WriteBitLong(24);
        //BL: Unknown long, default value 0L;
        _writer->WriteBitLong(0);

        //R13-R14 Only:
        if (R13_14Only)
        {
            //BS : Unknown short, default value 0
            _writer->WriteBitShort(0);
        }

        //Pre-2004 Only:
        if (R2004Pre)
        {
            //H : Handle of the current viewport entity header (hard pointer)
            _writer->HandleReference(0);
        }

        //Common:
        //B: DIMASO
        _writer->WriteBit(_header.AssociatedDimensions);
        //B: DIMSHO
        _writer->WriteBit(_header.UpdateDimensionsWhileDragging);

        //R13-R14 Only:
        if (R13_14Only)
        {
            //B : DIMSAV Undocumented.
            _writer->WriteBit(_header.DIMSAV);
        }

        //Common:
        //B: PLINEGEN
        _writer->WriteBit(_header.PolylineLineTypeGeneration);
        //B : ORTHOMODE
        _writer->WriteBit(_header.OrthoMode);
        //B: REGENMODE
        _writer->WriteBit(_header.RegenerationMode);
        //B : FILLMODE
        _writer->WriteBit(_header.FillMode);
        //B : QTEXTMODE
        _writer->WriteBit(_header.QuickTextMode);
        //B : PSLTSCALE
        _writer->WriteBit(_header.PaperSpaceLineTypeScaling ==
                              SpaceLineTypeScaling::Normal);
        //B : LIMCHECK
        _writer->WriteBit(_header.LimitCheckingOn);

        //R13-R14 Only (stored in registry from R15 onwards):
        if (R13_14Only)
            //B : BLIPMODE
            _writer->WriteBit(_header.BlipMode);

        //R2004+:
        if (R2004Plus)
            //B : Undocumented
            _writer->WriteBit(false);

        //Common:
        //B: USRTIMER(User timer on / off).
        _writer->WriteBit(_header.UserTimer);
        //B : SKPOLY
        _writer->WriteBit(_header.SketchPolylines);
        //B : ANGDIR
        _writer->WriteBit(_header.AngularDirection !=
                              units::AngularDirection::CounterClockWise);
        //B : SPLFRAME
        _writer->WriteBit(_header.ShowSplineControlPoints);

        //R13-R14 Only (stored in registry from R15 onwards):
        if (R13_14Only)
        {
            //B : ATTREQ
            _writer->WriteBit(false);
            //B : ATTDIA
            _writer->WriteBit(false);
        }

        //Common:
        //B: MIRRTEXT
        _writer->WriteBit(_header.MirrorText);
        //B : WORLDVIEW
        _writer->WriteBit(_header.WorldView);

        //R13 - R14 Only:
        if (R13_14Only)
        {
            //B: WIREFRAME Undocumented.
            _writer->WriteBit(false);
        }

        //Common:
        //B: TILEMODE
        _writer->WriteBit(_header.ShowModelSpace);
        //B : PLIMCHECK
        _writer->WriteBit(_header.PaperSpaceLimitsChecking);
        //B : VISRETAIN
        _writer->WriteBit(
                _header.RetainXRefDependentVisibilitySettings);

        //R13 - R14 Only(stored in registry from R15 onwards):
        if (R13_14Only)
        {
            //B : DELOBJ
            _writer->WriteBit(false);
        }

        //Common:
        //B: DISPSILH
        _writer->WriteBit(_header.DisplaySilhouetteCurves);
        //B : PELLIPSE(not present in DXF)
        _writer->WriteBit(_header.CreateEllipseAsPolyline);
        //BS: PROXYGRAPHICS
        _writer->WriteBitShort(
                (short) (_header.ProxyGraphics ? 1 : 0));

        //R13-R14 Only (stored in registry from R15 onwards):
        if (R13_14Only)
        {
            //BS : DRAGMODE
            _writer->WriteBitShort(0);
        }

        //Common:
        //BS: TREEDEPTH
        _writer->WriteBitShort(_header.SpatialIndexMaxTreeDepth);
        //BS : LUNITS
        _writer->WriteBitShort((short) _header.LinearUnitFormat);
        //BS : LUPREC
        _writer->WriteBitShort(_header.LinearUnitPrecision);
        //BS : AUNITS
        _writer->WriteBitShort((short) _header.AngularUnit);
        //BS : AUPREC
        _writer->WriteBitShort(_header.AngularUnitPrecision);

        //R13 - R14 Only Only(stored in registry from R15 onwards):
        if (R13_14Only)
            //BS: OSMODE
            _writer->WriteBitShort((short) _header.ObjectSnapMode);

        //Common:
        //BS: ATTMODE
        _writer->WriteBitShort((short) _header.AttributeVisibility);

        //R13 - R14 Only Only(stored in registry from R15 onwards):
        if (R13_14Only)
        {
            //BS: COORDS
            _writer->WriteBitShort(0);
        }

        //Common:
        //BS: PDMODE
        _writer->WriteBitShort(_header.PointDisplayMode);

        //R13 - R14 Only Only(stored in registry from R15 onwards):
        if (R13_14Only)
        {
            //BS: PICKSTYLE
            _writer->WriteBitShort(0);
        }

        //R2004 +:
        if (R2004Plus)
        {
            //BL: Unknown
            _writer->WriteBitLong(0);
            //BL: Unknown
            _writer->WriteBitLong(0);
            //BL: Unknown
            _writer->WriteBitLong(0);
        }

        //Common:
        //BS : USERI1
        _writer->WriteBitShort(_header.UserShort1);
        //BS : USERI2
        _writer->WriteBitShort(_header.UserShort2);
        //BS : USERI3
        _writer->WriteBitShort(_header.UserShort3);
        //BS : USERI4
        _writer->WriteBitShort(_header.UserShort4);
        //BS : USERI5
        _writer->WriteBitShort(_header.UserShort5);

        //BS: SPLINESEGS
        _writer->WriteBitShort(_header.NumberOfSplineSegments);
        //BS : SURFU
        _writer->WriteBitShort(_header.SurfaceDensityU);
        //BS : SURFV
        _writer->WriteBitShort(_header.SurfaceDensityV);
        //BS : SURFTYPE
        _writer->WriteBitShort(_header.SurfaceType);
        //BS : SURFTAB1
        _writer->WriteBitShort(_header.SurfaceMeshTabulationCount1);
        //BS : SURFTAB2
        _writer->WriteBitShort(_header.SurfaceMeshTabulationCount2);
        //BS : SPLINETYPE
        _writer->WriteBitShort((short) _header.SplineType);
        //BS : SHADEDGE
        _writer->WriteBitShort((short) _header.ShadeEdge);
        //BS : SHADEDIF
        _writer->WriteBitShort(
                _header.ShadeDiffuseToAmbientPercentage);
        //BS: UNITMODE
        _writer->WriteBitShort(_header.UnitMode);
        //BS : MAXACTVP
        _writer->WriteBitShort(_header.MaxViewportCount);
        //BS : ISOLINES
        _writer->WriteBitShort(_header.SurfaceIsolineCount);
        //BS : CMLJUST
        _writer->WriteBitShort(
                (short) _header.CurrentMultilineJustification);
        //BS : TEXTQLTY
        _writer->WriteBitShort(_header.TextQuality);
        //BD : LTSCALE
        _writer->WriteBitDouble(_header.LineTypeScale);
        //BD : TEXTSIZE
        _writer->WriteBitDouble(_header.TextHeightDefault);
        //BD : TRACEWID
        _writer->WriteBitDouble(_header.TraceWidthDefault);
        //BD : SKETCHINC
        _writer->WriteBitDouble(_header.SketchIncrement);
        //BD : FILLETRAD
        _writer->WriteBitDouble(_header.FilletRadius);
        //BD : THICKNESS
        _writer->WriteBitDouble(_header.ThicknessDefault);
        //BD : ANGBASE
        _writer->WriteBitDouble(_header.AngleBase);
        //BD : PDSIZE
        _writer->WriteBitDouble(_header.PointDisplaySize);
        //BD : PLINEWID
        _writer->WriteBitDouble(_header.PolylineWidthDefault);
        //BD : USERR1
        _writer->WriteBitDouble(_header.UserDouble1);
        //BD : USERR2
        _writer->WriteBitDouble(_header.UserDouble2);
        //BD : USERR3
        _writer->WriteBitDouble(_header.UserDouble3);
        //BD : USERR4
        _writer->WriteBitDouble(_header.UserDouble4);
        //BD : USERR5
        _writer->WriteBitDouble(_header.UserDouble5);
        //BD : CHAMFERA
        _writer->WriteBitDouble(_header.ChamferDistance1);
        //BD : CHAMFERB
        _writer->WriteBitDouble(_header.ChamferDistance2);
        //BD : CHAMFERC
        _writer->WriteBitDouble(_header.ChamferLength);
        //BD : CHAMFERD
        _writer->WriteBitDouble(_header.ChamferAngle);
        //BD : FACETRES
        _writer->WriteBitDouble(_header.FacetResolution);
        //BD : CMLSCALE
        _writer->WriteBitDouble(_header.CurrentMultilineScale);
        //BD : CELTSCALE
        _writer->WriteBitDouble(_header.CurrentEntityLinetypeScale);

        //TV: MENUNAME
        _writer->WriteVariableText(_header.MenuFileName);

        //Common:
        //BL: TDCREATE(Julian day)
        //BL: TDCREATE(Milliseconds into the day)
        _writer->WriteDateTime(_header.CreateDateTime);
        //BL: TDUPDATE(Julian day)
        //BL: TDUPDATE(Milliseconds into the day)
        _writer->WriteDateTime(_header.UpdateDateTime);

        //R2004 +:
        if (R2004Plus)
        {
            //BL : Unknown
            _writer->WriteBitLong(0);
            //BL : Unknown
            _writer->WriteBitLong(0);
            //BL : Unknown
            _writer->WriteBitLong(0);
        }

        //Common:
        //BL: TDINDWG(Days)
        //BL: TDINDWG(Milliseconds into the day)
        _writer->WriteTimeSpan(_header.TotalEditingTime);
        //BL: TDUSRTIMER(Days)
        //BL: TDUSRTIMER(Milliseconds into the day)
        _writer->WriteTimeSpan(_header.UserElapsedTimeSpan);

        //CMC : CECOLOR
        _writer->WriteCmColor(_header.CurrentEntityColor);

        //H : HANDSEED The next handle, with an 8-bit length specifier preceding the handle
        //bytes (standard hex handle form) (code 0). The HANDSEED is not part of the handle
        //stream, but of the normal data stream (relevant for R21 and later).
        _writer->Main()->HandleReference(_header.HandleSeed);

        //H : CLAYER (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _header.CurrentLayer);

        //H: TEXTSTYLE(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _header.CurrentTextStyle);

        //H: CELTYPE(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _header.CurrentLineType);

        //R2007 + Only:
        if (R2007Plus)
        {
            //H: CMATERIAL(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
        }

        //Common:
        //H: DIMSTYLE (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _header.DimensionStyleOverrides);

        //H: CMLSTYLE (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);

        //R2000+ Only:
        if (R2000Plus)
        {
            //BD: PSVPSCALE
            _writer->WriteBitDouble(
                    _header.ViewportDefaultViewScaleFactor);
        }

        //Common:
        //3BD: INSBASE(PSPACE)
        _writer->Write3BitDouble(_header.PaperSpaceInsertionBase);
        //3BD: EXTMIN(PSPACE)
        _writer->Write3BitDouble(_header.PaperSpaceExtMin);
        //3BD: EXTMAX(PSPACE)
        _writer->Write3BitDouble(_header.PaperSpaceExtMax);
        //2RD: LIMMIN(PSPACE)
        _writer->Write2RawDouble(_header.PaperSpaceLimitsMin);
        //2RD: LIMMAX(PSPACE)
        _writer->Write2RawDouble(_header.PaperSpaceLimitsMax);
        //BD: ELEVATION(PSPACE)
        _writer->WriteBitDouble(_header.PaperSpaceElevation);
        //3BD: UCSORG(PSPACE)
        _writer->Write3BitDouble(_header.PaperSpaceUcsOrigin);
        //3BD: UCSXDIR(PSPACE)
        _writer->Write3BitDouble(_header.PaperSpaceUcsXAxis);
        //3BD: UCSYDIR(PSPACE)
        _writer->Write3BitDouble(_header.PaperSpaceUcsYAxis);

        //H: UCSNAME (PSPACE) (hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _header.PaperSpaceUcs);

        //R2000+ Only:
        if (R2000Plus)
        {
            //H : PUCSORTHOREF (hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);

            //BS : PUCSORTHOVIEW	??
            _writer->WriteBitShort(0);

            //H: PUCSBASE(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);

            //3BD: PUCSORGTOP
            _writer->Write3BitDouble(
                    _header.PaperSpaceOrthographicTopDOrigin);
            //3BD: PUCSORGBOTTOM
            _writer->Write3BitDouble(
                    _header.PaperSpaceOrthographicBottomDOrigin);
            //3BD: PUCSORGLEFT
            _writer->Write3BitDouble(
                    _header.PaperSpaceOrthographicLeftDOrigin);
            //3BD: PUCSORGRIGHT
            _writer->Write3BitDouble(
                    _header.PaperSpaceOrthographicRightDOrigin);
            //3BD: PUCSORGFRONT
            _writer->Write3BitDouble(
                    _header.PaperSpaceOrthographicFrontDOrigin);
            //3BD: PUCSORGBACK
            _writer->Write3BitDouble(
                    _header.PaperSpaceOrthographicBackDOrigin);
        }

        //Common:
        //3BD: INSBASE(MSPACE)
        _writer->Write3BitDouble(_header.ModelSpaceInsertionBase);
        //3BD: EXTMIN(MSPACE)
        _writer->Write3BitDouble(_header.ModelSpaceExtMin);
        //3BD: EXTMAX(MSPACE)
        _writer->Write3BitDouble(_header.ModelSpaceExtMax);
        //2RD: LIMMIN(MSPACE)
        _writer->Write2RawDouble(_header.ModelSpaceLimitsMin);
        //2RD: LIMMAX(MSPACE)
        _writer->Write2RawDouble(_header.ModelSpaceLimitsMax);
        //BD: ELEVATION(MSPACE)
        _writer->WriteBitDouble(_header.Elevation);
        //3BD: UCSORG(MSPACE)
        _writer->Write3BitDouble(_header.ModelSpaceOrigin);
        //3BD: UCSXDIR(MSPACE)
        _writer->Write3BitDouble(_header.ModelSpaceXAxis);
        //3BD: UCSYDIR(MSPACE)
        _writer->Write3BitDouble(_header.ModelSpaceYAxis);

        //H: UCSNAME(MSPACE)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _header.ModelSpaceUcs);

        //R2000 + Only:
        if (R2000Plus)
        {
            //H: UCSORTHOREF(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);

            //BS: UCSORTHOVIEW	??
            _writer->WriteBitShort(0);

            //H : UCSBASE(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);

            //3BD: UCSORGTOP
            _writer->Write3BitDouble(
                    _header.ModelSpaceOrthographicTopDOrigin);
            //3BD: UCSORGBOTTOM
            _writer->Write3BitDouble(
                    _header.ModelSpaceOrthographicBottomDOrigin);
            //3BD: UCSORGLEFT
            _writer->Write3BitDouble(
                    _header.ModelSpaceOrthographicLeftDOrigin);
            //3BD: UCSORGRIGHT
            _writer->Write3BitDouble(
                    _header.ModelSpaceOrthographicRightDOrigin);
            //3BD: UCSORGFRONT
            _writer->Write3BitDouble(
                    _header.ModelSpaceOrthographicFrontDOrigin);
            //3BD: UCSORGBACK
            _writer->Write3BitDouble(
                    _header.ModelSpaceOrthographicBackDOrigin);

            //TV : DIMPOST
            _writer->WriteVariableText(_header.DimensionPostFix);
            //TV : DIMAPOST
            _writer->WriteVariableText(
                    _header.DimensionAlternateDimensioningSuffix);
        }

        //R13-R14 Only:
        if (R13_14Only)
        {
            //B: DIMTOL
            _writer->WriteBit(_header.DimensionGenerateTolerances);
            //B : DIMLIM
            _writer->WriteBit(_header.DimensionLimitsGeneration);
            //B : DIMTIH
            _writer->WriteBit(_header.DimensionTextInsideHorizontal);
            //B : DIMTOH
            _writer->WriteBit(_header.DimensionTextOutsideHorizontal);
            //B : DIMSE1
            _writer->WriteBit(
                    _header.DimensionSuppressFirstExtensionLine);
            //B : DIMSE2
            _writer->WriteBit(
                    _header.DimensionSuppressSecondExtensionLine);
            //B : DIMALT
            _writer->WriteBit(
                    _header.DimensionAlternateUnitDimensioning);
            //B : DIMTOFL
            _writer->WriteBit(_header.DimensionTextOutsideExtensions);
            //B : DIMSAH
            _writer->WriteBit(_header.DimensionSeparateArrowBlocks);
            //B : DIMTIX
            _writer->WriteBit(_header.DimensionTextInsideExtensions);
            //B : DIMSOXD
            _writer->WriteBit(
                    _header.DimensionSuppressOutsideExtensions);
            //RC : DIMALTD
            _writer->WriteByte(
                    (unsigned char) _header.DimensionAlternateUnitDecimalPlaces);
            //RC : DIMZIN
            _writer->WriteByte((unsigned char) _header.DimensionZeroHandling);
            //B : DIMSD1
            _writer->WriteBit(
                    _header.DimensionSuppressFirstDimensionLine);
            //B : DIMSD2
            _writer->WriteBit(
                    _header.DimensionSuppressSecondDimensionLine);
            //RC : DIMTOLJ
            _writer->WriteByte(
                    (unsigned char) _header.DimensionToleranceAlignment);
            //RC : DIMJUST
            _writer->WriteByte(
                    (unsigned char) _header.DimensionTextHorizontalAlignment);
            //RC : DIMFIT
            _writer->WriteByte((unsigned char) _header.DimensionFit);
            //B : DIMUPT
            _writer->WriteBit(_header.DimensionCursorUpdate);
            //RC : DIMTZIN
            _writer->WriteByte(
                    (unsigned char) _header.DimensionToleranceZeroHandling);
            //RC: DIMALTZ
            _writer->WriteByte(
                    (unsigned char) _header.DimensionAlternateUnitZeroHandling);
            //RC : DIMALTTZ
            _writer->WriteByte(
                    (unsigned char) _header
                            .DimensionAlternateUnitToleranceZeroHandling);
            //RC : DIMTAD
            _writer->WriteByte(
                    (unsigned char) _header.DimensionTextVerticalAlignment);
            //BS : DIMUNIT
            _writer->WriteBitShort(_header.DimensionUnit);
            //BS : DIMAUNIT
            _writer->WriteBitShort(
                    _header.DimensionAngularDimensionDecimalPlaces);
            //BS : DIMDEC
            _writer->WriteBitShort(_header.DimensionDecimalPlaces);
            //BS : DIMTDEC
            _writer->WriteBitShort(
                    _header.DimensionToleranceDecimalPlaces);
            //BS : DIMALTU
            _writer->WriteBitShort(
                    (short) _header.DimensionAlternateUnitFormat);
            //BS : DIMALTTD
            _writer->WriteBitShort(
                    _header.DimensionAlternateUnitToleranceDecimalPlaces);

            //H : DIMTXSTY(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer,
                                         _header.DimensionStyleOverrides);
        }

        //Common:
        //BD: DIMSCALE
        _writer->WriteBitDouble(_header.DimensionScaleFactor);
        //BD : DIMASZ
        _writer->WriteBitDouble(_header.DimensionArrowSize);
        //BD : DIMEXO
        _writer->WriteBitDouble(_header.DimensionExtensionLineOffset);
        //BD : DIMDLI
        _writer->WriteBitDouble(_header.DimensionLineIncrement);
        //BD : DIMEXE
        _writer->WriteBitDouble(
                _header.DimensionExtensionLineExtension);
        //BD : DIMRND
        _writer->WriteBitDouble(_header.DimensionRounding);
        //BD : DIMDLE
        _writer->WriteBitDouble(_header.DimensionLineExtension);
        //BD : DIMTP
        _writer->WriteBitDouble(_header.DimensionPlusTolerance);
        //BD : DIMTM
        _writer->WriteBitDouble(_header.DimensionMinusTolerance);

        //R2007 + Only:
        if (R2007Plus)
        {
            //BD: DIMFXL
            _writer->WriteBitDouble(
                    _header.DimensionFixedExtensionLineLength);
            //BD : DIMJOGANG
            _writer->WriteBitDouble(
                    _header
                            .DimensionJoggedRadiusDimensionTransverseSegmentAngle);
            //BS : DIMTFILL
            _writer->WriteBitShort(
                    (short) _header.DimensionTextBackgroundFillMode);
            //CMC : DIMTFILLCLR
            _writer->WriteCmColor(
                    _header.DimensionTextBackgroundColor);
        }

        //R2000 + Only:
        if (R2000Plus)
        {
            //B: DIMTOL
            _writer->WriteBit(_header.DimensionGenerateTolerances);
            //B : DIMLIM
            _writer->WriteBit(_header.DimensionLimitsGeneration);
            //B : DIMTIH
            _writer->WriteBit(_header.DimensionTextInsideHorizontal);
            //B : DIMTOH
            _writer->WriteBit(_header.DimensionTextOutsideHorizontal);
            //B : DIMSE1
            _writer->WriteBit(
                    _header.DimensionSuppressFirstExtensionLine);
            //B : DIMSE2
            _writer->WriteBit(
                    _header.DimensionSuppressSecondExtensionLine);
            //BS : DIMTAD
            _writer->WriteBitShort(
                    (short) _header.DimensionTextVerticalAlignment);
            //BS : DIMZIN
            _writer->WriteBitShort(
                    (short) _header.DimensionZeroHandling);
            //BS : DIMAZIN
            _writer->WriteBitShort(
                    (short) _header.DimensionAngularZeroHandling);
        }

        //R2007 + Only:
        if (R2007Plus)
        {
            //BS: DIMARCSYM
            _writer->WriteBitShort(
                    (short) _header.DimensionArcLengthSymbolPosition);
        }

        //Common:
        //BD: DIMTXT
        _writer->WriteBitDouble(_header.DimensionTextHeight);
        //BD : DIMCEN
        _writer->WriteBitDouble(_header.DimensionCenterMarkSize);
        //BD: DIMTSZ
        _writer->WriteBitDouble(_header.DimensionTickSize);
        //BD : DIMALTF
        _writer->WriteBitDouble(
                _header.DimensionAlternateUnitScaleFactor);
        //BD : DIMLFAC
        _writer->WriteBitDouble(_header.DimensionLinearScaleFactor);
        //BD : DIMTVP
        _writer->WriteBitDouble(_header.DimensionTextVerticalPosition);
        //BD : DIMTFAC
        _writer->WriteBitDouble(_header.DimensionToleranceScaleFactor);
        //BD : DIMGAP
        _writer->WriteBitDouble(_header.DimensionLineGap);

        //R13 - R14 Only:
        if (R13_14Only)
        {
            //T: DIMPOST
            _writer->WriteVariableText(_header.DimensionPostFix);
            //T : DIMAPOST
            _writer->WriteVariableText(
                    _header.DimensionAlternateDimensioningSuffix);
            //T : DIMBLK
            _writer->WriteVariableText(_header.DimensionBlockName);
            //T : DIMBLK1
            _writer->WriteVariableText(
                    _header.DimensionBlockNameFirst);
            //T : DIMBLK2
            _writer->WriteVariableText(
                    _header.DimensionBlockNameSecond);
        }

        //R2000 + Only:
        if (R2000Plus)
        {
            //BD: DIMALTRND
            _writer->WriteBitDouble(
                    _header.DimensionAlternateUnitRounding);
            //B : DIMALT
            _writer->WriteBit(
                    _header.DimensionAlternateUnitDimensioning);
            //BS : DIMALTD
            _writer->WriteBitShort(
                    _header.DimensionAlternateUnitDecimalPlaces);
            //B : DIMTOFL
            _writer->WriteBit(_header.DimensionTextOutsideExtensions);
            //B : DIMSAH
            _writer->WriteBit(_header.DimensionSeparateArrowBlocks);
            //B : DIMTIX
            _writer->WriteBit(_header.DimensionTextInsideExtensions);
            //B : DIMSOXD
            _writer->WriteBit(
                    _header.DimensionSuppressOutsideExtensions);
        }

        //Common:
        //CMC: DIMCLRD
        _writer->WriteCmColor(_header.DimensionLineColor);
        //CMC : DIMCLRE
        _writer->WriteCmColor(_header.DimensionExtensionLineColor);
        //CMC : DIMCLRT
        _writer->WriteCmColor(_header.DimensionTextColor);

        //R2000 + Only:
        if (R2000Plus)
        {
            //BS: DIMADEC
            _writer->WriteBitShort(
                    _header.DimensionAngularDimensionDecimalPlaces);
            //BS : DIMDEC
            _writer->WriteBitShort(_header.DimensionDecimalPlaces);
            //BS : DIMTDEC
            _writer->WriteBitShort(
                    _header.DimensionToleranceDecimalPlaces);
            //BS : DIMALTU
            _writer->WriteBitShort(
                    (short) _header.DimensionAlternateUnitFormat);
            //BS : DIMALTTD
            _writer->WriteBitShort(
                    _header.DimensionAlternateUnitToleranceDecimalPlaces);
            //BS : DIMAUNIT
            _writer->WriteBitShort(
                    (short) _header.DimensionAngularUnit);
            //BS : DIMFRAC
            _writer->WriteBitShort(
                    (short) _header.DimensionFractionFormat);
            //BS : DIMLUNIT
            _writer->WriteBitShort(
                    (short) _header.DimensionLinearUnitFormat);
            //BS : DIMDSEP
            _writer->WriteBitShort(
                    (short) _header.DimensionDecimalSeparator);
            //BS : DIMTMOVE
            _writer->WriteBitShort(
                    (short) _header.DimensionTextMovement);
            //BS : DIMJUST
            _writer->WriteBitShort(
                    (short) _header.DimensionTextHorizontalAlignment);
            //B : DIMSD1
            _writer->WriteBit(
                    _header.DimensionSuppressFirstExtensionLine);
            //B : DIMSD2
            _writer->WriteBit(
                    _header.DimensionSuppressSecondExtensionLine);
            //BS : DIMTOLJ
            _writer->WriteBitShort(
                    (short) _header.DimensionToleranceAlignment);
            //BS : DIMTZIN
            _writer->WriteBitShort(
                    (short) _header.DimensionToleranceZeroHandling);
            //BS: DIMALTZ
            _writer->WriteBitShort(
                    (short) _header.DimensionAlternateUnitZeroHandling);
            //BS : DIMALTTZ
            _writer->WriteBitShort(
                    (short) _header
                            .DimensionAlternateUnitToleranceZeroHandling);
            //B : DIMUPT
            _writer->WriteBit(_header.DimensionCursorUpdate);
            //BS : DIMATFIT
            _writer->WriteBitShort(
                    (short) _header.DimensionDimensionTextArrowFit);
        }

        //R2007 + Only:
        if (R2007Plus)
        {
            //B: DIMFXLON
            _writer->WriteBit(
                    _header.DimensionIsExtensionLineLengthFixed);
        }

        //R2010 + Only:
        if (R2010Plus)
        {
            //B: DIMTXTDIRECTION
            _writer->WriteBit(_header.DimensionTextDirection ==
                                  tables::TextDirection::RightToLeft);
            //BD : DIMALTMZF
            _writer->WriteBitDouble(_header.DimensionAltMzf);
            //T : DIMALTMZS
            _writer->WriteVariableText(_header.DimensionAltMzs);
            //BD : DIMMZF
            _writer->WriteBitDouble(_header.DimensionMzf);
            //T : DIMMZS
            _writer->WriteVariableText(_header.DimensionMzs);
        }

        //R2000 + Only:
        if (R2000Plus)
        {
            //H: DIMTXSTY(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DIMLDRBLK(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DIMBLK(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DIMBLK1(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DIMBLK2(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
        }

        //R2007+ Only:
        if (R2007Plus)
        {
            //H : DIMLTYPE (hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DIMLTEX1(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DIMLTEX2(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
        }

        //R2000+ Only:
        if (R2000Plus)
        {
            //BS: DIMLWD
            _writer->WriteBitShort(
                    (short) _header.DimensionLineWeight);
            //BS : DIMLWE
            _writer->WriteBitShort(
                    (short) _header.ExtensionLineWeight);
        }

        //H: BLOCK CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->BlockRecords);
        //H: LAYER CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->Layers);
        //H: STYLE CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->TextStyles);
        //H: LINETYPE CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->LineTypes);
        //H: VIEW CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->Views);
        //H: UCS CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->UCSs);
        //H: VPORT CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->VPorts);
        //H: APPID CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->AppIds);
        //H: DIMSTYLE CONTROL OBJECT(hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->DimensionStyles);

        //R13 - R15 Only:
        if (R13_15Only)
        {
            //H: VIEWPORT ENTITY HEADER CONTROL OBJECT(hard owner)
            _writer->HandleReference(DwgReferenceType::HardOwnership, nullptr);
        }

        //Common:
        //H: DICTIONARY(ACAD_GROUP)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _document->Groups);
        //H: DICTIONARY(ACAD_MLINESTYLE)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _document->MLineStyles);

        //H : DICTIONARY (NAMED OBJECTS) (hard owner)
        _writer->HandleReference(DwgReferenceType::HardOwnership,
                                     _document->RootDictionary);

        //R2000+ Only:
        if (R2000Plus)
        {
            //BS: TSTACKALIGN, default = 1(not present in DXF)
            _writer->WriteBitShort(_header.StackedTextAlignment);
            //BS: TSTACKSIZE, default = 70(not present in DXF)
            _writer->WriteBitShort(_header.StackedTextSizePercentage);

            //TV: HYPERLINKBASE
            _writer->WriteVariableText(_header.HyperLinkBase);
            //TV : STYLESHEET
            _writer->WriteVariableText(_header.StyleSheetName);

            //H : DICTIONARY(LAYOUTS)(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer,
                                         _document->Layouts);
            //H: DICTIONARY(PLOTSETTINGS)(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DICTIONARY(PLOTSTYLES)(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
        }

        //R2004 +:
        if (R2004Plus)
        {
            //H: DICTIONARY (MATERIALS) (hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DICTIONARY (COLORS) (hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
        }

        //R2007 +:
        if (R2007Plus)
        {
            //H: DICTIONARY(VISUALSTYLE)(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);

            //R2013+:
            if (R2013Plus)
            {
                //H : UNKNOWN (hard pointer)	//DICTIONARY_VISUALSTYLE
                _writer->HandleReference(DwgReferenceType::HardPointer,
                                             nullptr);
            }
        }

        //R2000 +:
        if (R2000Plus)
        {
            //BL: Flags:

            //CELWEIGHT Flags & 0x001F
            int flags = ((int) _header.CurrentEntityLineWeight & 0x1F) |
                        //ENDCAPS Flags & 0x0060
                        (_header.EndCaps << 0x5) |
                        //JOINSTYLE Flags & 0x0180
                        (_header.JoinStyle << 0x7);

            //LWDISPLAY!(Flags & 0x0200)
            if (!_header.DisplayLineWeight) { flags |= 0x200; }
            //XEDIT!(Flags & 0x0400)
            if (!_header.XEdit) { flags |= 0x400; }
            //EXTNAMES Flags & 0x0800
            if (_header.ExtendedNames) { flags |= 0x800; }
            //PSTYLEMODE Flags & 0x2000
            if (_header.PlotStyleMode == 1) { flags |= 0x2000; }
            //OLESTARTUP Flags & 0x4000
            if (_header.LoadOLEObject) { flags |= 0x4000; }

            _writer->WriteBitLong(flags);

            //BS: INSUNITS
            _writer->WriteBitShort((short) _header.InsUnits);
            //BS : CEPSNTYPE
            _writer->WriteBitShort(
                    (short) _header.CurrentEntityPlotStyle);

            if (_header.CurrentEntityPlotStyle ==
                header::EntityPlotStyleType::ByObjectId)
            {
                //H: CPSNID(present only if CEPSNTYPE == 3) (hard pointer)
                _writer->HandleReference(DwgReferenceType::HardPointer,
                                             nullptr);
            }

            //TV: FINGERPRINTGUID
            _writer->WriteVariableText(_header.FingerPrintGuid);
            //TV : VERSIONGUID
            _writer->WriteVariableText(_header.VersionGuid);
        }

        //R2004 +:
        if (R2004Plus)
        {
            //RC: SORTENTS
            _writer->WriteByte((unsigned char) _header.EntitySortingFlags);
            //RC : INDEXCTL
            _writer->WriteByte((unsigned char) _header.IndexCreationFlags);
            //RC : HIDETEXT
            _writer->WriteByte(_header.HideText);
            //RC : XCLIPFRAME, before R2010 the value can be 0 or 1 only.
            _writer->WriteByte(
                    _header.ExternalReferenceClippingBoundaryType);
            //RC : DIMASSOC
            _writer->WriteByte((unsigned char) _header.DimensionAssociativity);
            //RC : HALOGAP
            _writer->WriteByte(_header.HaloGapPercentage);
            //BS : OBSCUREDCOLOR
            _writer->WriteBitShort(_header.ObscuredColor.Index());
            //BS : INTERSECTIONCOLOR
            _writer->WriteBitShort(_header.InterfereColor.Index());
            //RC : OBSCUREDLTYPE
            _writer->WriteByte(_header.ObscuredType);
            //RC: INTERSECTIONDISPLAY
            _writer->WriteByte(_header.IntersectionDisplay);

            //TV : PROJECTNAME
            _writer->WriteVariableText(_header.ProjectName);
        }

        //Common:
        //H: BLOCK_RECORD(*PAPER_SPACE)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _document->PaperSpace);
        //H: BLOCK_RECORD(*MODEL_SPACE)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _document->ModelSpace);
        //H: LTYPE(BYLAYER)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _document->LineTypes["ByLayer"]);
        //H: LTYPE(BYBLOCK)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _document->LineTypes["ByBlock"]);
        //H: LTYPE(CONTINUOUS)(hard pointer)
        _writer->HandleReference(DwgReferenceType::HardPointer,
                                     _document->LineTypes["Continuous"]);

        //R2007 +:
        if (R2007Plus)
        {
            //B: CAMERADISPLAY
            _writer->WriteBit(_header.CameraDisplayObjects);

            //BL : unknown
            _writer->WriteBitLong(0);
            //BL : unknown
            _writer->WriteBitLong(0);
            //BD : unknown
            _writer->WriteBitDouble(0);

            //BD : STEPSPERSEC
            _writer->WriteBitDouble(_header.StepsPerSecond);
            //BD : STEPSIZE
            _writer->WriteBitDouble(_header.StepSize);
            //BD : 3DDWFPREC
            _writer->WriteBitDouble(_header.Dw3DPrecision);
            //BD : LENSLENGTH
            _writer->WriteBitDouble(_header.LensLength);
            //BD : CAMERAHEIGHT
            _writer->WriteBitDouble(_header.CameraHeight);
            //RC : SOLIDHIST
            _writer->WriteByte((unsigned char) _header.SolidsRetainHistory);
            //RC : SHOWHIST
            _writer->WriteByte((unsigned char) _header.ShowSolidsHistory);
            //BD : PSOLWIDTH
            _writer->WriteBitDouble(_header.SweptSolidWidth);
            //BD : PSOLHEIGHT
            _writer->WriteBitDouble(_header.SweptSolidHeight);
            //BD : LOFTANG1
            _writer->WriteBitDouble(
                    _header.DraftAngleFirstCrossSection);
            //BD : LOFTANG2
            _writer->WriteBitDouble(
                    _header.DraftAngleSecondCrossSection);
            //BD : LOFTMAG1
            _writer->WriteBitDouble(
                    _header.DraftMagnitudeFirstCrossSection);
            //BD : LOFTMAG2
            _writer->WriteBitDouble(
                    _header.DraftMagnitudeSecondCrossSection);
            //BS : LOFTPARAM
            _writer->WriteBitShort(_header.SolidLoftedShape);
            //RC : LOFTNORMALS
            _writer->WriteByte((unsigned char) _header.LoftedObjectNormals);
            //BD : LATITUDE
            _writer->WriteBitDouble(_header.Latitude);
            //BD : LONGITUDE
            _writer->WriteBitDouble(_header.Longitude);
            //BD : NORTHDIRECTION
            _writer->WriteBitDouble(_header.NorthDirection);
            //BL : TIMEZONE
            _writer->WriteBitLong(_header.TimeZone);
            //RC : LIGHTGLYPHDISPLAY
            _writer->WriteByte((unsigned char) _header.DisplayLightGlyphs);
            //RC : TILEMODELIGHTSYNCH	??
            _writer->WriteByte((unsigned char) '0');
            //RC : DWFFRAME
            _writer->WriteByte(
                    (unsigned char) _header.DwgUnderlayFramesVisibility);
            //RC : DGNFRAME
            _writer->WriteByte(
                    (unsigned char) _header.DgnUnderlayFramesVisibility);

            //B : unknown
            _writer->WriteBit(false);

            //CMC : INTERFERECOLOR
            _writer->WriteCmColor(_header.InterfereColor);

            //H : INTERFEREOBJVS(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: INTERFEREVPVS(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);
            //H: DRAGVS(hard pointer)
            _writer->HandleReference(DwgReferenceType::HardPointer, nullptr);

            //RC: CSHADOW
            _writer->WriteByte((unsigned char) _header.ShadowMode);
            //BD : unknown
            _writer->WriteBitDouble(_header.ShadowPlaneLocation);
        }

        //R14 +:
        if (_header.Version >= ACadVersion.AC1014)
        {
            //BS : unknown short(type 5 / 6 only) these do not seem to be required,
            _writer->WriteBitShort(-1);
            //BS : unknown short(type 5 / 6 only) even for type 5.
            _writer->WriteBitShort(-1);
            //BS : unknown short(type 5 / 6 only)
            _writer->WriteBitShort(-1);
            //BS : unknown short(type 5 / 6 only)
            _writer->WriteBitShort(-1);

            if (R2004Plus)
            {
                //This file versions seem to finish with this values
                _writer->WriteBitLong(0);
                _writer->WriteBitLong(0);
                _writer->WriteBit(false);
            }
        }

        _writer->WriteSpearShift();

        //Write the size and merge the streams
        writeSizeAndCrc();
    }

private:
    void writeSizeAndCrc()
    {
        //0xCF,0x7B,0x1F,0x23,0xFD,0xDE,0x38,0xA9,0x5F,0x7C,0x68,0xB8,0x4E,0x6D,0x33,0x5F
        _startWriter->WriteBytes(
                DwgSectionDefinition::StartSentinels[SectionName()]);

        CRC8StreamHandler crc =
                new CRC8StreamHandler(_startWriter.Stream, 0xC0C1);
        StreamIO swriter = new StreamIO(crc);

        //RL : Size of the section.
        swriter.Write((int) _msmain.Length);

        //R2010/R2013 (only present if the maintenance version is greater than 3!) or R2018+:
        if (R2010Plus && _header.MaintenanceVersion > 3 || R2018Plus)
        {
            //Unknown (4 unsigned char long), might be part of a 64-bit size.
            swriter.Write<int>(0);
        }

        crc.Write(_msmain.GetBuffer(), 0, (int) _msmain.Length);

        //Common:
        //RS : CRC for the data section, starting after the sentinel.Use 0xC0C1 for the initial value.
        swriter.Write<ushort>(crc.Seed);

        //Ending sentinel: 0x30,0x84,0xE0,0xDC,0x02,0x21,0xC7,0x56,0xA0,0x83,0x97,0x47,0xB1,0x92,0xCC,0xA0
        _startWriter->WriteBytes(
                DwgSectionDefinition::EndSentinels[SectionName()]);
    }
};


}// namespace io
}// namespace dwg
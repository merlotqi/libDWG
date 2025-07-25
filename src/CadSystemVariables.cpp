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
#include <dwg/attributes/CadSystemVariableAttribute_p.h>
#include <dwg/header/CadHeader.h>
#include <dwg/utils/StringHelp.h>
#include <initializer_list>
#include <memory>
#include <rttr/registration>
#include <vector>

namespace dwg {

static std::vector<CadSystemVariableAttribute> _headerVariables = {
        {CadSystemVariables::ANGBASE, {50}},
        {CadSystemVariables::ANGDIR, {70}},
        {CadSystemVariables::AUNITS, {70}},
        {CadSystemVariables::AUPREC, {70}},
        {CadSystemVariables::DIMLDRBLK, {1}},
        {CadSystemVariables::DIMASO, {70}},
        {CadSystemVariables::ATTMODE, {70}},
        {CadSystemVariables::BLIPMODE, {70}},
        {CadSystemVariables::CAMERADISPLAY, {290}},
        {CadSystemVariables::CAMERAHEIGHT, {40}},
        {CadSystemVariables::CHAMFERD, {40}},
        {CadSystemVariables::CHAMFERA, {40}},
        {CadSystemVariables::CHAMFERB, {40}},
        {CadSystemVariables::CHAMFERC, {40}},
        {CadSystemVariables::DWGCODEPAGE, {3}},
        {CadSystemVariables::TDCREATE, {40}},
        {CadSystemVariables::PELLIPSE, {70}},
        {CadSystemVariables::CECOLOR, {62}},
        {CadSystemVariables::CELTSCALE, {40}},
        {CadSystemVariables::CELWEIGHT, {370}},
        {CadSystemVariables::CEPSNTYPE, {380}},
        {CadSystemVariables::CLAYER, true, {8}},
        {CadSystemVariables::CELTYPE, true, {6}},
        {CadSystemVariables::CMLJUST, {70}},
        {CadSystemVariables::CMLSCALE, {40}},
        {CadSystemVariables::CMLSTYLE, true, {2}},
        {CadSystemVariables::DGNFRAME, {280}},
        {CadSystemVariables::DIMAPOST, {1}},
        {CadSystemVariables::DIMALTD, {70}},
        {CadSystemVariables::DIMALT, {70}},
        {CadSystemVariables::DIMALTU, {70}},
        {CadSystemVariables::DIMALTRND, {40}},
        {CadSystemVariables::DIMALTF, {40}},
        {CadSystemVariables::DIMALTTD, {70}},
        {CadSystemVariables::DIMALTTZ, {70}},
        {CadSystemVariables::DIMALTZ, {70}},
        {CadSystemVariables::DIMALTMZF, {40}},
        {CadSystemVariables::DIMALTMZS, {6}},
        {CadSystemVariables::DIMADEC, {70}},
        {CadSystemVariables::DIMAUNIT, {70}},
        {CadSystemVariables::DIMAZIN, {70}},
        {CadSystemVariables::DIMARCSYM, {70}},
        {CadSystemVariables::DIMASZ, {40}},
        {CadSystemVariables::DIMASSOC, {280}},
        {CadSystemVariables::DIMBLK, {1}},
        {CadSystemVariables::DIMBLK1, {1}},
        {CadSystemVariables::DIMBLK2, {1}},
        {CadSystemVariables::DIMCEN, {40}},
        {CadSystemVariables::DIMUPT, {70}},
        {CadSystemVariables::DIMDEC, {70}},
        {CadSystemVariables::DIMDSEP, {70}},
        {CadSystemVariables::DIMATFIT, {70}},
        {CadSystemVariables::DIMCLRE, {70}},
        {CadSystemVariables::DIMEXE, {40}},
        {CadSystemVariables::DIMEXO, {40}},
        {CadSystemVariables::DIMFIT, {70}},
        {CadSystemVariables::DIMFXL, {40}},
        {CadSystemVariables::DIMFRAC, {70}},
        {CadSystemVariables::DIMTOL, {70}},
        {CadSystemVariables::DIMFXLON, {70}},
        {CadSystemVariables::DIMJOGANG, {40}},
        {CadSystemVariables::DIMLIM, {70}},
        {CadSystemVariables::DIMLFAC, {40}},
        {CadSystemVariables::DIMLUNIT, {70}},
        {CadSystemVariables::DIMCLRD, {70}},
        {CadSystemVariables::DIMDLE, {40}},
        {CadSystemVariables::DIMGAP, {40}},
        {CadSystemVariables::DIMDLI, {40}},
        {CadSystemVariables::DIMLTYPE, {6}},
        {CadSystemVariables::DIMLWD, {70}},
        {CadSystemVariables::DIMTM, {40}},
        {CadSystemVariables::DIMMZF, {40}},
        {CadSystemVariables::DIMMZS, {6}},
        {CadSystemVariables::DIMTP, {40}},
        {CadSystemVariables::DIMPOST, {1}},
        {CadSystemVariables::DIMRND, {40}},
        {CadSystemVariables::DIMSCALE, {40}},
        {CadSystemVariables::DIMSAH, {70}},
        {CadSystemVariables::DIMSTYLE, true, {2}},
        {CadSystemVariables::DIMSD1, {70}},
        {CadSystemVariables::DIMSE1, {70}},
        {CadSystemVariables::DIMSOXD, {70}},
        {CadSystemVariables::DIMSD2, {70}},
        {CadSystemVariables::DIMSE2, {70}},
        {CadSystemVariables::DIMLTEX1, {6}},
        {CadSystemVariables::DIMLTEX2, {6}},
        {DxfReferenceType::Ignored, CadSystemVariables::DIMTFILLCLR, {62}},
        {CadSystemVariables::DIMTFILL, {70}},
        {CadSystemVariables::DIMCLRT, {70}},
        {CadSystemVariables::DIMTXTDIRECTION, {70}},
        {CadSystemVariables::DIMTXT, {40}},
        {CadSystemVariables::DIMJUST, {70}},
        {CadSystemVariables::DIMTIX, {70}},
        {CadSystemVariables::DIMTIH, {70}},
        {CadSystemVariables::DIMTMOVE, {70}},
        {CadSystemVariables::DIMTOFL, {70}},
        {CadSystemVariables::DIMTOH, {70}},
        {CadSystemVariables::DIMTXSTY, true, {7}},
        {CadSystemVariables::DIMTAD, {70}},
        {CadSystemVariables::DIMTVP, {40}},
        {CadSystemVariables::DIMTSZ, {40}},
        {CadSystemVariables::DIMTOLJ, {70}},
        {CadSystemVariables::DIMTDEC, {70}},
        {CadSystemVariables::DIMTFAC, {40}},
        {CadSystemVariables::DIMTZIN, {70}},
        {CadSystemVariables::DIMUNIT, {70}},
        {CadSystemVariables::DIMZIN, {70}},
        {CadSystemVariables::LIGHTGLYPHDISPLAY, {280}},
        {CadSystemVariables::LWDISPLAY, {290}},
        {CadSystemVariables::DISPSILH, {70}},
        {CadSystemVariables::LOFTANG1, {40}},
        {CadSystemVariables::LOFTANG2, {40}},
        {CadSystemVariables::LOFTMAG1, {40}},
        {CadSystemVariables::LOFTMAG2, {40}},
        {CadSystemVariables::_3DDWFPREC, {40}},
        {CadSystemVariables::DWFFRAME, {280}},
        {CadSystemVariables::ELEVATION, {40}},
        {CadSystemVariables::ENDCAPS, {280}},
        {CadSystemVariables::SORTENTS, {280}},
        {CadSystemVariables::EXTNAMES, {290}},
        {CadSystemVariables::DIMLWE, {70}},
        {CadSystemVariables::XCLIPFRAME, {280}},
        {CadSystemVariables::FACETRES, {40}},
        {CadSystemVariables::FILLETRAD, {40}},
        {CadSystemVariables::FILLMODE, {70}},
        {CadSystemVariables::FINGERPRINTGUID, {2}},
        {CadSystemVariables::HALOGAP, {280}},
        {CadSystemVariables::HANDSEED, {5}},
        {CadSystemVariables::HIDETEXT, {280}},
        {CadSystemVariables::HYPERLINKBASE, {1}},
        {CadSystemVariables::INDEXCTL, {280}},
        {CadSystemVariables::INSUNITS, {70}},
        {CadSystemVariables::INTERFERECOLOR, {62}},
        {CadSystemVariables::JOINSTYLE, {280}},
        {DxfReferenceType::Ignored, CadSystemVariables::LASTSAVEDBY, {3}},
        {CadSystemVariables::LATITUDE, {40}},
        {CadSystemVariables::LENSLENGTH, {40}},
        {CadSystemVariables::LIMCHECK, {70}},
        {CadSystemVariables::LUNITS, {70}},
        {CadSystemVariables::LUPREC, {70}},
        {CadSystemVariables::LTSCALE, {40}},
        {CadSystemVariables::LOFTNORMALS, {280}},
        {CadSystemVariables::LONGITUDE, {40}},
        {DxfReferenceType::Ignored, CadSystemVariables::ACADMAINTVER, {70}},
        {CadSystemVariables::MAXACTVP, {70}},
        {CadSystemVariables::MEASUREMENT, {70}},
        {CadSystemVariables::MENU, {1}},
        {CadSystemVariables::MIRRTEXT, {70}},
        {CadSystemVariables::EXTMAX, {10, 20, 30}},
        {CadSystemVariables::EXTMIN, {10, 20, 30}},
        {CadSystemVariables::INSBASE, {10, 20, 30}},
        {CadSystemVariables::LIMMAX, {10, 20}},
        {CadSystemVariables::LIMMIN, {10, 20}},
        {CadSystemVariables::UCSORG, {10, 20, 30}},
        {CadSystemVariables::UCSORGBACK, {10, 20, 30}},
        {CadSystemVariables::UCSORGBOTTOM, {10, 20, 30}},
        {CadSystemVariables::UCSORGFRONT, {10, 20, 30}},
        {CadSystemVariables::UCSORGLEFT, {10, 20, 30}},
        {CadSystemVariables::UCSORGRIGHT, {10, 20, 30}},
        {CadSystemVariables::UCSORGTOP, {10, 20, 30}},
        {CadSystemVariables::UCSXDIR, {10, 20, 30}},
        {CadSystemVariables::UCSYDIR, {10, 20, 30}},
        {CadSystemVariables::NORTHDIRECTION, {40}},
        {CadSystemVariables::SPLINESEGS, {70}},
        {CadSystemVariables::OSMODE, {70}},
        {CadSystemVariables::ORTHOMODE, {70}},
        {CadSystemVariables::PUCSBASE, true, {2}},
        {CadSystemVariables::PELEVATION, {40}},
        {CadSystemVariables::PEXTMAX, {10, 20, 30}},
        {CadSystemVariables::PEXTMIN, {10, 20, 30}},
        {CadSystemVariables::PINSBASE, {10, 20, 30}},
        {CadSystemVariables::PLIMCHECK, {70}},
        {CadSystemVariables::PLIMMAX, {10, 20}},
        {CadSystemVariables::PLIMMIN, {10, 20}},
        {CadSystemVariables::PSLTSCALE, {70}},
        {CadSystemVariables::PUCSNAME, true, {2}},
        {CadSystemVariables::PUCSORGBACK, {10, 20, 30}},
        {CadSystemVariables::PUCSORGBOTTOM, {10, 20, 30}},
        {CadSystemVariables::PUCSORGFRONT, {10, 20, 30}},
        {CadSystemVariables::PUCSORGLEFT, {10, 20, 30}},
        {CadSystemVariables::PUCSORGRIGHT, {10, 20, 30}},
        {CadSystemVariables::PUCSORGTOP, {10, 20, 30}},
        {CadSystemVariables::PUCSORG, {10, 20, 30}},
        {CadSystemVariables::PUCSXDIR, {10, 20, 30}},
        {CadSystemVariables::PUCSYDIR, {10, 20, 30}},
        {CadSystemVariables::PSTYLEMODE, {290}},
        {CadSystemVariables::PDMODE, {70}},
        {CadSystemVariables::PDSIZE, {40}},
        {CadSystemVariables::PLINEGEN, {70}},
        {CadSystemVariables::PLINEWID, {40}},
        {CadSystemVariables::PROJECTNAME, {1}},
        {CadSystemVariables::PROXYGRAPHICS, {70}},
        {CadSystemVariables::QTEXTMODE, {70}},
        {CadSystemVariables::REGENMODE, {70}},
        {DxfReferenceType::Ignored, CadSystemVariables::REQUIREDVERSIONS, {70}},
        {CadSystemVariables::VISRETAIN, {70}},
        {CadSystemVariables::SHADEDIF, {70}},
        {CadSystemVariables::SHADEDGE, {70}},
        {CadSystemVariables::CSHADOW, {280}},
        {CadSystemVariables::SHADOWPLANELOCATION, {40}},
        {CadSystemVariables::TILEMODE, {70}},
        {CadSystemVariables::SHOWHIST, {280}},
        {CadSystemVariables::SPLFRAME, {70}},
        {CadSystemVariables::SKETCHINC, {40}},
        {CadSystemVariables::SKPOLY, {70}},
        {CadSystemVariables::LOFTPARAM, {70}},
        {CadSystemVariables::SOLIDHIST, {280}},
        {CadSystemVariables::TREEDEPTH, {70}},
        {CadSystemVariables::SPLINETYPE, {70}},
        {CadSystemVariables::STEPSIZE, {40}},
        {CadSystemVariables::STEPSPERSEC, {40}},
        {CadSystemVariables::STYLESHEET, {1}},
        {CadSystemVariables::SURFU, {70}},
        {CadSystemVariables::SURFV, {70}},
        {CadSystemVariables::SURFTAB1, {70}},
        {CadSystemVariables::SURFTAB2, {70}},
        {CadSystemVariables::SURFTYPE, {70}},
        {CadSystemVariables::PSOLHEIGHT, {40}},
        {CadSystemVariables::PSOLWIDTH, {40}},
        {CadSystemVariables::TEXTSIZE, {40}},
        {CadSystemVariables::TEXTSTYLE, true, {7}},
        {CadSystemVariables::THICKNESS, {40}},
        {CadSystemVariables::TIMEZONE, {70}},
        {CadSystemVariables::TDINDWG, {40}},
        {CadSystemVariables::TRACEWID, {40}},
        {CadSystemVariables::UCSBASE, true, {2}},
        {CadSystemVariables::UCSNAME, true, {2}},
        {CadSystemVariables::UNITMODE, {70}},
        {CadSystemVariables::TDUCREATE, {40}},
        {CadSystemVariables::TDUUPDATE, {40}},
        {CadSystemVariables::TDUPDATE, {40}},
        {CadSystemVariables::DIMSHO, {70}},
        {CadSystemVariables::USERR1, {40}},
        {CadSystemVariables::USERR2, {40}},
        {CadSystemVariables::USERR3, {40}},
        {CadSystemVariables::USERR4, {40}},
        {CadSystemVariables::USERR5, {40}},
        {CadSystemVariables::TDUSRTIMER, {40}},
        {CadSystemVariables::USERI1, {70}},
        {CadSystemVariables::USERI2, {70}},
        {CadSystemVariables::USERI3, {70}},
        {CadSystemVariables::USERI4, {70}},
        {CadSystemVariables::USERI5, {70}},
        {CadSystemVariables::USRTIMER, {70}},
        {CadSystemVariables::VERSIONGUID, {2}},
        {CadSystemVariables::ACADVER, {1}},
        {CadSystemVariables::PSVPSCALE, {40}},
        {CadSystemVariables::WORLDVIEW, {70}},
        {CadSystemVariables::XEDIT, {290}},
};

std::vector<std::pair<std::string, std::string>> CadSystemVariables::_systemVaraible2PropertyKeyMappings = {};

std::map<std::string, CadSystemVariableAttribute> CadSystemVariables::headerMap()
{
    static std::once_flag flag;
    std::call_once(flag, [&]() {
        _systemVaraible2PropertyKeyMappings.clear();

        using namespace rttr;
        auto type = rttr::type::get<CadHeader>();
        auto properties = type.get_properties();
        for (auto &&property: properties)
        {
            auto name = property.get_name();
            auto variable = property.get_metadata("CadSystemVariable").get_value<CadSystemVariableAttribute>();
            _systemVaraible2PropertyKeyMappings.push_back({variable.name(), std::string(name)});
        }
    });
  
    std::map<std::string, CadSystemVariableAttribute> _map;
    for (auto &&attr: _headerVariables)
    {
        _map.insert({attr.name(), attr});
    }
    return _map;
}

DwgVariant CadSystemVariables::value(const std::string &key, const DxfCode &code, CadHeader *header)
{
    assert(header);
    DwgVariant var = CadSystemVariables::value(key, header);
    return var;
}

DwgVariant CadSystemVariables::value(const std::string &key, CadHeader *header)
{
    assert(header);
    if (key == CadSystemVariables::ANGBASE)
    {
        return header->angleBase();
    }
    if (key == CadSystemVariables::ANGDIR)
    {
        return static_cast<short>(header->angularDirection());
    }
    if (key == CadSystemVariables::AUNITS)
    {
        return static_cast<short>(header->angularUnit());
    }
    if (key == CadSystemVariables::AUPREC)
    {
        return header->angularUnitPrecision();
    }
    if (key == CadSystemVariables::DIMLDRBLK)
    {
        return header->arrowBlockName();
    }
    if (key == CadSystemVariables::DIMASO)
    {
        return header->associatedDimensions();
    }
    if (key == CadSystemVariables::ATTMODE)
    {
        return static_cast<int>(header->attributeVisibility());
    }
    if (key == CadSystemVariables::BLIPMODE)
    {
        return header->blipMode();
    }
    if (key == CadSystemVariables::CAMERADISPLAY)
    {
        return header->cameraDisplayObjects();
    }
    if (key == CadSystemVariables::CAMERAHEIGHT)
    {
        return header->cameraHeight();
    }
    if (key == CadSystemVariables::CHAMFERD)
    {
        return header->chamferAngle();
    }
    if (key == CadSystemVariables::CHAMFERA)
    {
        return header->chamferDistance1();
    }
    if (key == CadSystemVariables::CHAMFERB)
    {
        return header->chamferDistance2();
    }
    if (key == CadSystemVariables::CHAMFERC)
    {
        return header->chamferLength();
    }
    if (key == CadSystemVariables::DWGCODEPAGE)
    {
        return header->codePage();
    }
    if (key == CadSystemVariables::TDCREATE)
    {
        return header->createDateTime();
    }
    if (key == CadSystemVariables::PELLIPSE)
    {
        return header->createEllipseAsPolyline();
    }
    if (key == CadSystemVariables::CECOLOR)
    {
        return header->currentEntityColor();
    }
    if (key == CadSystemVariables::CELTSCALE)
    {
        return header->currentEntityLinetypeScale();
    }
    if (key == CadSystemVariables::CELWEIGHT)
    {
        return static_cast<short>(header->currentEntityLineWeight());
    }
    if (key == CadSystemVariables::CEPSNTYPE)
    {
        return static_cast<short>(header->currentEntityPlotStyle());
    }
    if (key == CadSystemVariables::CLAYER)
    {
        return header->currentLayerName();
    }
    if (key == CadSystemVariables::CELTYPE)
    {
        return header->currentLineTypeName();
    }
    if (key == CadSystemVariables::CMLJUST)
    {
        return static_cast<short>(header->currentMultilineJustification());
    }
    if (key == CadSystemVariables::CMLSCALE)
    {
        return header->currentMultilineScale();
    }
    if (key == CadSystemVariables::CMLSTYLE)
    {
        return header->currentMultiLineStyleName();
    }
    if (key == CadSystemVariables::DGNFRAME)
    {
        return header->dgnUnderlayFramesVisibility();
    }
    if (key == CadSystemVariables::DIMAPOST)
    {
        return header->dimensionAlternateDimensioningSuffix();
    }
    if (key == CadSystemVariables::DIMALTD)
    {
        return header->dimensionAlternateUnitDecimalPlaces();
    }
    if (key == CadSystemVariables::DIMALT)
    {
        return header->dimensionAlternateUnitDimensioning();
    }
    if (key == CadSystemVariables::DIMALTU)
    {
        return static_cast<short>(header->dimensionAlternateUnitFormat());
    }
    if (key == CadSystemVariables::DIMALTRND)
    {
        return header->dimensionAlternateUnitRounding();
    }
    if (key == CadSystemVariables::DIMALTF)
    {
        return header->dimensionAlternateUnitScaleFactor();
    }
    if (key == CadSystemVariables::DIMALTTD)
    {
        return header->dimensionAlternateUnitToleranceDecimalPlaces();
    }
    if (key == CadSystemVariables::DIMALTTZ)
    {
        return static_cast<unsigned char>(header->dimensionAlternateUnitToleranceZeroHandling());
    }
    if (key == CadSystemVariables::DIMALTZ)
    {
        return static_cast<unsigned char>(header->dimensionAlternateUnitZeroHandling());
    }
    if (key == CadSystemVariables::DIMALTMZF)
    {
        return header->dimensionAltMzf();
    }
    if (key == CadSystemVariables::DIMALTMZS)
    {
        return header->dimensionAltMzs();
    }
    if (key == CadSystemVariables::DIMADEC)
    {
        return header->dimensionAngularDimensionDecimalPlaces();
    }
    if (key == CadSystemVariables::DIMAUNIT)
    {
        return static_cast<short>(header->dimensionAngularUnit());
    }
    if (key == CadSystemVariables::DIMAZIN)
    {
        return static_cast<unsigned char>(header->dimensionAngularZeroHandling());
    }
    if (key == CadSystemVariables::DIMARCSYM)
    {
        return static_cast<short>(header->dimensionArcLengthSymbolPosition());
    }
    if (key == CadSystemVariables::DIMASZ)
    {
        return header->dimensionArrowSize();
    }
    if (key == CadSystemVariables::DIMASSOC)
    {
        return static_cast<short>(header->dimensionAssociativity());
    }
    if (key == CadSystemVariables::DIMBLK)
    {
        return header->dimensionBlockName();
    }
    if (key == CadSystemVariables::DIMBLK1)
    {
        return header->dimensionBlockNameFirst();
    }
    if (key == CadSystemVariables::DIMBLK2)
    {
        return header->dimensionBlockNameSecond();
    }
    if (key == CadSystemVariables::DIMCEN)
    {
        return header->dimensionCenterMarkSize();
    }
    if (key == CadSystemVariables::DIMUPT)
    {
        return header->dimensionCursorUpdate();
    }
    if (key == CadSystemVariables::DIMDEC)
    {
        return header->dimensionDecimalPlaces();
    }
    if (key == CadSystemVariables::DIMDSEP)
    {
        return header->dimensionDecimalSeparator();
    }
    if (key == CadSystemVariables::DIMATFIT)
    {
        return static_cast<unsigned char>(header->dimensionDimensionTextArrowFit());
    }
    if (key == CadSystemVariables::DIMCLRE)
    {
        return header->dimensionExtensionLineColor();
    }
    if (key == CadSystemVariables::DIMEXE)
    {
        return header->dimensionExtensionLineExtension();
    }
    if (key == CadSystemVariables::DIMEXO)
    {
        return header->dimensionExtensionLineOffset();
    }
    if (key == CadSystemVariables::DIMFIT)
    {
        return header->dimensionFit();
    }
    if (key == CadSystemVariables::DIMFXL)
    {
        return header->dimensionFixedExtensionLineLength();
    }
    if (key == CadSystemVariables::DIMFRAC)
    {
        return static_cast<short>(header->dimensionFractionFormat());
    }
    if (key == CadSystemVariables::DIMTOL)
    {
        return header->dimensionGenerateTolerances();
    }
    if (key == CadSystemVariables::DIMFXLON)
    {
        return header->dimensionIsExtensionLineLengthFixed();
    }
    if (key == CadSystemVariables::DIMJOGANG)
    {
        return header->dimensionJoggedRadiusDimensionTransverseSegmentAngle();
    }
    if (key == CadSystemVariables::DIMLIM)
    {
        return header->dimensionLimitsGeneration();
    }
    if (key == CadSystemVariables::DIMLFAC)
    {
        return header->dimensionLinearScaleFactor();
    }
    if (key == CadSystemVariables::DIMLUNIT)
    {
        return static_cast<short>(header->dimensionLinearUnitFormat());
    }
    if (key == CadSystemVariables::DIMCLRD)
    {
        return header->dimensionLineColor();
    }
    if (key == CadSystemVariables::DIMDLE)
    {
        return header->dimensionLineExtension();
    }
    if (key == CadSystemVariables::DIMGAP)
    {
        return header->dimensionLineGap();
    }
    if (key == CadSystemVariables::DIMDLI)
    {
        return header->dimensionLineIncrement();
    }
    if (key == CadSystemVariables::DIMLTYPE)
    {
        return header->dimensionLineType();
    }
    if (key == CadSystemVariables::DIMLWD)
    {
        return static_cast<short>(header->dimensionLineWeight());
    }
    if (key == CadSystemVariables::DIMTM)
    {
        return header->dimensionMinusTolerance();
    }
    if (key == CadSystemVariables::DIMMZF)
    {
        return header->dimensionMzf();
    }
    if (key == CadSystemVariables::DIMMZS)
    {
        return header->dimensionMzs();
    }
    if (key == CadSystemVariables::DIMTP)
    {
        return header->dimensionPlusTolerance();
    }
    if (key == CadSystemVariables::DIMPOST)
    {
        return header->dimensionPostFix();
    }
    if (key == CadSystemVariables::DIMRND)
    {
        return header->dimensionRounding();
    }
    if (key == CadSystemVariables::DIMSCALE)
    {
        return header->dimensionScaleFactor();
    }
    if (key == CadSystemVariables::DIMSAH)
    {
        return header->dimensionSeparateArrowBlocks();
    }
    if (key == CadSystemVariables::DIMSTYLE)
    {
        return header->currentDimensionStyleName();
    }
    if (key == CadSystemVariables::DIMSD1)
    {
        return header->dimensionSuppressFirstDimensionLine();
    }
    if (key == CadSystemVariables::DIMSE1)
    {
        return header->dimensionSuppressFirstExtensionLine();
    }
    if (key == CadSystemVariables::DIMSOXD)
    {
        return header->dimensionSuppressOutsideExtensions();
    }
    if (key == CadSystemVariables::DIMSD2)
    {
        return header->dimensionSuppressSecondDimensionLine();
    }
    if (key == CadSystemVariables::DIMSE2)
    {
        return header->dimensionSuppressSecondExtensionLine();
    }
    if (key == CadSystemVariables::DIMLTEX1)
    {
        return header->dimensionTex1();
    }
    if (key == CadSystemVariables::DIMLTEX2)
    {
        return header->dimensionTex2();
    }
    if (key == CadSystemVariables::DIMTFILLCLR)
    {
        return header->dimensionTextBackgroundColor();
    }
    if (key == CadSystemVariables::DIMTFILL)
    {
        return static_cast<short>(header->dimensionTextBackgroundFillMode());
    }
    if (key == CadSystemVariables::DIMCLRT)
    {
        return header->dimensionTextColor();
    }
    if (key == CadSystemVariables::DIMTXTDIRECTION)
    {
        return static_cast<unsigned char>(header->dimensionTextDirection());
    }
    if (key == CadSystemVariables::DIMTXT)
    {
        return header->dimensionTextHeight();
    }
    if (key == CadSystemVariables::DIMJUST)
    {
        return static_cast<unsigned char>(header->dimensionTextHorizontalAlignment());
    }
    if (key == CadSystemVariables::DIMTIX)
    {
        return header->dimensionTextInsideExtensions();
    }
    if (key == CadSystemVariables::DIMTIH)
    {
        return header->dimensionTextInsideHorizontal();
    }
    if (key == CadSystemVariables::DIMTMOVE)
    {
        return static_cast<short>(header->dimensionTextMovement());
    }
    if (key == CadSystemVariables::DIMTOFL)
    {
        return header->dimensionTextOutsideExtensions();
    }
    if (key == CadSystemVariables::DIMTOH)
    {
        return header->dimensionTextOutsideHorizontal();
    }
    if (key == CadSystemVariables::DIMTXSTY)
    {
        return header->dimensionTextStyleName();
    }
    if (key == CadSystemVariables::DIMTAD)
    {
        return static_cast<int>(header->dimensionTextVerticalAlignment());
    }
    if (key == CadSystemVariables::DIMTVP)
    {
        return header->dimensionTextVerticalPosition();
    }
    if (key == CadSystemVariables::DIMTSZ)
    {
        return header->dimensionTickSize();
    }
    if (key == CadSystemVariables::DIMTOLJ)
    {
        return static_cast<unsigned char>(header->dimensionToleranceAlignment());
    }
    if (key == CadSystemVariables::DIMTDEC)
    {
        return header->dimensionToleranceDecimalPlaces();
    }
    if (key == CadSystemVariables::DIMTFAC)
    {
        return header->dimensionToleranceScaleFactor();
    }
    if (key == CadSystemVariables::DIMTZIN)
    {
        return static_cast<unsigned char>(header->dimensionToleranceZeroHandling());
    }
    if (key == CadSystemVariables::DIMUNIT)
    {
        return header->dimensionUnit();
    }
    if (key == CadSystemVariables::DIMZIN)
    {
        return static_cast<unsigned char>(header->dimensionZeroHandling());
    }
    if (key == CadSystemVariables::LIGHTGLYPHDISPLAY)
    {
        return header->displayLightGlyphs();
    }
    if (key == CadSystemVariables::LWDISPLAY)
    {
        return header->displayLineWeight();
    }
    if (key == CadSystemVariables::DISPSILH)
    {
        return header->displaySilhouetteCurves();
    }
    if (key == CadSystemVariables::LOFTANG1)
    {
        return header->draftAngleFirstCrossSection();
    }
    if (key == CadSystemVariables::LOFTANG2)
    {
        return header->draftAngleSecondCrossSection();
    }
    if (key == CadSystemVariables::LOFTMAG1)
    {
        return header->draftMagnitudeFirstCrossSection();
    }
    if (key == CadSystemVariables::LOFTMAG2)
    {
        return header->draftMagnitudeSecondCrossSection();
    }
    if (key == CadSystemVariables::_3DDWFPREC)
    {
        return header->dw3DPrecision();
    }
    if (key == CadSystemVariables::DWFFRAME)
    {
        return header->dwgUnderlayFramesVisibility();
    }
    if (key == CadSystemVariables::ELEVATION)
    {
        return header->elevation();
    }
    if (key == CadSystemVariables::ENDCAPS)
    {
        return header->endCaps();
    }
    if (key == CadSystemVariables::SORTENTS)
    {
        return static_cast<unsigned char>(header->entitySortingFlags());
    }
    if (key == CadSystemVariables::EXTNAMES)
    {
        return header->extendedNames();
    }
    if (key == CadSystemVariables::DIMLWE)
    {
        return static_cast<short>(header->extensionLineWeight());
    }
    if (key == CadSystemVariables::XCLIPFRAME)
    {
        return header->externalReferenceClippingBoundaryType();
    }
    if (key == CadSystemVariables::FACETRES)
    {
        return header->facetResolution();
    }
    if (key == CadSystemVariables::FILLETRAD)
    {
        return header->filletRadius();
    }
    if (key == CadSystemVariables::FILLMODE)
    {
        return header->fillMode();
    }
    if (key == CadSystemVariables::FINGERPRINTGUID)
    {
        return header->fingerPrintGuid();
    }
    if (key == CadSystemVariables::HALOGAP)
    {
        return header->haloGapPercentage();
    }
    if (key == CadSystemVariables::HANDSEED)
    {
        return header->handleSeed();
    }
    if (key == CadSystemVariables::HIDETEXT)
    {
        return header->hideText();
    }
    if (key == CadSystemVariables::INDEXCTL)
    {
        return static_cast<unsigned char>(header->indexCreationFlags());
    }
    if (key == CadSystemVariables::INSUNITS)
    {
        return static_cast<short>(header->insUnits());
    }
    if (key == CadSystemVariables::INTERFERECOLOR)
    {
        return header->interfereColor();
    }
    if (key == CadSystemVariables::JOINSTYLE)
    {
        return header->joinStyle();
    }
    if (key == CadSystemVariables::LASTSAVEDBY)
    {
        return header->lastSavedBy();
    }
    if (key == CadSystemVariables::LATITUDE)
    {
        return header->latitude();
    }
    if (key == CadSystemVariables::LENSLENGTH)
    {
        return header->lensLength();
    }
    if (key == CadSystemVariables::LIMCHECK)
    {
        return header->limitCheckingOn();
    }
    if (key == CadSystemVariables::LUNITS)
    {
        return static_cast<short>(header->linearUnitFormat());
    }
    if (key == CadSystemVariables::LUPREC)
    {
        return header->linearUnitPrecision();
    }
    if (key == CadSystemVariables::LTSCALE)
    {
        return header->lineTypeScale();
    }
    if (key == CadSystemVariables::LOFTNORMALS)
    {
        return header->loftedObjectNormals();
    }
    if (key == CadSystemVariables::LONGITUDE)
    {
        return header->longitude();
    }
    if (key == CadSystemVariables::ACADMAINTVER)
    {
        return header->maintenanceVersion();
    }
    if (key == CadSystemVariables::MAXACTVP)
    {
        return header->maxViewportCount();
    }
    if (key == CadSystemVariables::MEASUREMENT)
    {
        return static_cast<short>(header->measurementUnits());
    }
    if (key == CadSystemVariables::MENU)
    {
        return header->menuFileName();
    }
    if (key == CadSystemVariables::MIRRTEXT)
    {
        return header->mirrorText();
    }
    if (key == CadSystemVariables::EXTMAX)
    {
        return header->modelSpaceExtMax();
    }
    if (key == CadSystemVariables::EXTMIN)
    {
        return header->modelSpaceExtMin();
    }
    if (key == CadSystemVariables::INSBASE)
    {
        return header->modelSpaceInsertionBase();
    }
    if (key == CadSystemVariables::LIMMAX)
    {
        return header->modelSpaceLimitsMax();
    }
    if (key == CadSystemVariables::LIMMIN)
    {
        return header->modelSpaceLimitsMin();
    }
    if (key == CadSystemVariables::UCSORG)
    {
        return header->modelSpaceOrigin();
    }
    if (key == CadSystemVariables::UCSORGBACK)
    {
        return header->modelSpaceOrthographicBackDOrigin();
    }
    if (key == CadSystemVariables::UCSORGBOTTOM)
    {
        return header->modelSpaceOrthographicBottomDOrigin();
    }
    if (key == CadSystemVariables::UCSORGFRONT)
    {
        return header->modelSpaceOrthographicFrontDOrigin();
    }
    if (key == CadSystemVariables::UCSORGLEFT)
    {
        return header->modelSpaceOrthographicLeftDOrigin();
    }
    if (key == CadSystemVariables::UCSORGRIGHT)
    {
        return header->modelSpaceOrthographicRightDOrigin();
    }
    if (key == CadSystemVariables::UCSORGTOP)
    {
        return header->modelSpaceOrthographicTopDOrigin();
    }
    if (key == CadSystemVariables::UCSXDIR)
    {
        return header->modelSpaceXAxis();
    }
    if (key == CadSystemVariables::UCSYDIR)
    {
        return header->modelSpaceYAxis();
    }
    if (key == CadSystemVariables::NORTHDIRECTION)
    {
        return header->northDirection();
    }
    if (key == CadSystemVariables::SPLINESEGS)
    {
        return header->numberOfSplineSegments();
    }
    if (key == CadSystemVariables::OSMODE)
    {
        return static_cast<unsigned short>(header->objectSnapMode());
    }
    if (key == CadSystemVariables::ORTHOMODE)
    {
        return header->orthoMode();
    }
    if (key == CadSystemVariables::PUCSBASE)
    {
        return header->paperSpaceBaseName();
    }
    if (key == CadSystemVariables::PELEVATION)
    {
        return header->paperSpaceElevation();
    }
    if (key == CadSystemVariables::PEXTMAX)
    {
        return header->paperSpaceExtMax();
    }
    if (key == CadSystemVariables::PEXTMIN)
    {
        return header->paperSpaceExtMin();
    }
    if (key == CadSystemVariables::PINSBASE)
    {
        return header->paperSpaceInsertionBase();
    }
    if (key == CadSystemVariables::PLIMCHECK)
    {
        return header->paperSpaceLimitsChecking();
    }
    if (key == CadSystemVariables::PLIMMAX)
    {
        return header->paperSpaceLimitsMax();
    }
    if (key == CadSystemVariables::PLIMMIN)
    {
        return header->paperSpaceLimitsMin();
    }
    if (key == CadSystemVariables::PSLTSCALE)
    {
        return static_cast<short>(header->paperSpaceLineTypeScaling());
    }
    if (key == CadSystemVariables::PUCSNAME)
    {
        return header->paperSpaceName();
    }
    if (key == CadSystemVariables::PUCSORGBACK)
    {
        return header->paperSpaceOrthographicBackDOrigin();
    }
    if (key == CadSystemVariables::PUCSORGBOTTOM)
    {
        return header->paperSpaceOrthographicBottomDOrigin();
    }
    if (key == CadSystemVariables::PUCSORGFRONT)
    {
        return header->paperSpaceOrthographicFrontDOrigin();
    }
    if (key == CadSystemVariables::PUCSORGLEFT)
    {
        return header->paperSpaceOrthographicLeftDOrigin();
    }
    if (key == CadSystemVariables::PUCSORGRIGHT)
    {
        return header->paperSpaceOrthographicRightDOrigin();
    }
    if (key == CadSystemVariables::PUCSORGTOP)
    {
        return header->paperSpaceOrthographicTopDOrigin();
    }
    if (key == CadSystemVariables::PUCSORG)
    {
        return header->paperSpaceUcsOrigin();
    }
    if (key == CadSystemVariables::PUCSXDIR)
    {
        return header->paperSpaceUcsXAxis();
    }
    if (key == CadSystemVariables::PUCSYDIR)
    {
        return header->paperSpaceUcsYAxis();
    }
    if (key == CadSystemVariables::PSTYLEMODE)
    {
        return header->plotStyleMode();
    }
    if (key == CadSystemVariables::PDMODE)
    {
        return header->pointDisplayMode();
    }
    if (key == CadSystemVariables::PDSIZE)
    {
        return header->pointDisplaySize();
    }
    if (key == CadSystemVariables::PLINEGEN)
    {
        return header->polylineLineTypeGeneration();
    }
    if (key == CadSystemVariables::PLINEWID)
    {
        return header->polylineWidthDefault();
    }
    if (key == CadSystemVariables::PROJECTNAME)
    {
        return header->projectName();
    }
    if (key == CadSystemVariables::PROXYGRAPHICS)
    {
        return header->proxyGraphics();
    }
    if (key == CadSystemVariables::QTEXTMODE)
    {
        return header->quickTextMode();
    }
    if (key == CadSystemVariables::REGENMODE)
    {
        return header->regenerationMode();
    }
    if (key == CadSystemVariables::REQUIREDVERSIONS)
    {
        return header->requiredVersions();
    }
    if (key == CadSystemVariables::VISRETAIN)
    {
        return header->retainXRefDependentVisibilitySettings();
    }
    if (key == CadSystemVariables::SHADEDIF)
    {
        return header->shadeDiffuseToAmbientPercentage();
    }
    if (key == CadSystemVariables::SHADEDGE)
    {
        return static_cast<short>(header->shadeEdge());
    }
    if (key == CadSystemVariables::CSHADOW)
    {
        return static_cast<unsigned char>(header->shadowMode());
    }
    if (key == CadSystemVariables::SHADOWPLANELOCATION)
    {
        return header->shadowPlaneLocation();
    }
    if (key == CadSystemVariables::TILEMODE)
    {
        return header->showModelSpace();
    }
    if (key == CadSystemVariables::SHOWHIST)
    {
        return header->showSolidsHistory();
    }
    if (key == CadSystemVariables::SPLFRAME)
    {
        return header->showSplineControlPoints();
    }
    if (key == CadSystemVariables::SKETCHINC)
    {
        return header->sketchIncrement();
    }
    if (key == CadSystemVariables::SKPOLY)
    {
        return header->sketchPolylines();
    }
    if (key == CadSystemVariables::LOFTPARAM)
    {
        return header->solidLoftedShape();
    }
    if (key == CadSystemVariables::SOLIDHIST)
    {
        return header->solidsRetainHistory();
    }
    if (key == CadSystemVariables::TREEDEPTH)
    {
        return header->spatialIndexMaxTreeDepth();
    }
    if (key == CadSystemVariables::SPLINETYPE)
    {
        return static_cast<short>(header->splineType());
    }
    if (key == CadSystemVariables::STEPSIZE)
    {
        return header->stepSize();
    }
    if (key == CadSystemVariables::STEPSPERSEC)
    {
        return header->stepsPerSecond();
    }
    if (key == CadSystemVariables::STYLESHEET)
    {
        return header->styleSheetName();
    }
    if (key == CadSystemVariables::SURFU)
    {
        return header->surfaceDensityU();
    }
    if (key == CadSystemVariables::SURFV)
    {
        return header->surfaceDensityV();
    }
    if (key == CadSystemVariables::SURFTAB1)
    {
        return header->surfaceMeshTabulationCount1();
    }
    if (key == CadSystemVariables::SURFTAB2)
    {
        return header->surfaceMeshTabulationCount2();
    }
    if (key == CadSystemVariables::SURFTYPE)
    {
        return header->surfaceType();
    }
    if (key == CadSystemVariables::PSOLHEIGHT)
    {
        return header->sweptSolidHeight();
    }
    if (key == CadSystemVariables::PSOLWIDTH)
    {
        return header->sweptSolidWidth();
    }
    if (key == CadSystemVariables::TEXTSIZE)
    {
        return header->textHeightDefault();
    }
    if (key == CadSystemVariables::TEXTSTYLE)
    {
        return header->textStyleName();
    }
    if (key == CadSystemVariables::THICKNESS)
    {
        return header->thicknessDefault();
    }
    if (key == CadSystemVariables::TIMEZONE)
    {
        return header->timeZone();
    }
    if (key == CadSystemVariables::TDINDWG)
    {
        return header->totalEditingTime();
    }
    if (key == CadSystemVariables::TRACEWID)
    {
        return header->traceWidthDefault();
    }
    if (key == CadSystemVariables::UCSBASE)
    {
        return header->ucsBaseName();
    }
    if (key == CadSystemVariables::UCSNAME)
    {
        return header->ucsName();
    }
    if (key == CadSystemVariables::UNITMODE)
    {
        return header->unitMode();
    }
    if (key == CadSystemVariables::TDUCREATE)
    {
        return header->universalCreateDateTime();
    }
    if (key == CadSystemVariables::TDUUPDATE)
    {
        return header->universalUpdateDateTime();
    }
    if (key == CadSystemVariables::TDUPDATE)
    {
        return header->updateDateTime();
    }
    if (key == CadSystemVariables::DIMSHO)
    {
        return header->updateDimensionsWhileDragging();
    }
    if (key == CadSystemVariables::USERR1)
    {
        return header->userDouble1();
    }
    if (key == CadSystemVariables::USERR2)
    {
        return header->userDouble2();
    }
    if (key == CadSystemVariables::USERR3)
    {
        return header->userDouble3();
    }
    if (key == CadSystemVariables::USERR4)
    {
        return header->userDouble4();
    }
    if (key == CadSystemVariables::USERR5)
    {
        return header->userDouble5();
    }
    if (key == CadSystemVariables::TDUSRTIMER)
    {
        return header->userElapsedTimeSpan();
    }
    if (key == CadSystemVariables::USERI1)
    {
        return header->userShort1();
    }
    if (key == CadSystemVariables::USERI2)
    {
        return header->userShort2();
    }
    if (key == CadSystemVariables::USERI3)
    {
        return header->userShort3();
    }
    if (key == CadSystemVariables::USERI4)
    {
        return header->userShort4();
    }
    if (key == CadSystemVariables::USERI5)
    {
        return header->userShort5();
    }
    if (key == CadSystemVariables::USRTIMER)
    {
        return header->userTimer();
    }
    if (key == CadSystemVariables::VERSIONGUID)
    {
        return header->versionGuid();
    }
    if (key == CadSystemVariables::ACADVER)
    {
        return header->versionString();
    }
    if (key == CadSystemVariables::PSVPSCALE)
    {
        return header->viewportDefaultViewScaleFactor();
    }
    if (key == CadSystemVariables::WORLDVIEW)
    {
        return header->worldView();
    }
    if (key == CadSystemVariables::XEDIT)
    {
        return header->xedit();
    }
    return DwgVariant();
}

void CadSystemVariables::setValue(CadHeader *header, const std::string &key, const std::vector<DwgVariant> &parameters)
{
}

}// namespace dwg
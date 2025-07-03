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

#include <dwg/attributes/CadSystemVariableAttribute_p.h>
#include <dwg/utils/DwgVariant.h>
#include <map>
#include <string>
#include <vector>

namespace dwg {

class CadHeader;
class CadSystemVariables
{
public:
    static constexpr auto ANGBASE = "$ANGBASE";
    static constexpr auto ANGDIR = "$ANGDIR";
    static constexpr auto AUNITS = "$AUNITS";
    static constexpr auto AUPREC = "$AUPREC";
    static constexpr auto DIMLDRBLK = "$DIMLDRBLK";
    static constexpr auto DIMASO = "$DIMASO";
    static constexpr auto ATTMODE = "$ATTMODE";
    static constexpr auto BLIPMODE = "$BLIPMODE";
    static constexpr auto CAMERADISPLAY = "$CAMERADISPLAY";
    static constexpr auto CAMERAHEIGHT = "$CAMERAHEIGHT";
    static constexpr auto CHAMFERD = "$CHAMFERD";
    static constexpr auto CHAMFERA = "$CHAMFERA";
    static constexpr auto CHAMFERB = "$CHAMFERB";
    static constexpr auto CHAMFERC = "$CHAMFERC";
    static constexpr auto DWGCODEPAGE = "$DWGCODEPAGE";
    static constexpr auto TDCREATE = "$TDCREATE";
    static constexpr auto PELLIPSE = "$PELLIPSE";
    static constexpr auto CECOLOR = "$CECOLOR";
    static constexpr auto CELTSCALE = "$CELTSCALE";
    static constexpr auto CELWEIGHT = "$CELWEIGHT";
    static constexpr auto CEPSNTYPE = "$CEPSNTYPE";
    static constexpr auto CLAYER = "$CLAYER";
    static constexpr auto CELTYPE = "$CELTYPE";
    static constexpr auto CMLJUST = "$CMLJUST";
    static constexpr auto CMLSCALE = "$CMLSCALE";
    static constexpr auto CMLSTYLE = "$CMLSTYLE";
    static constexpr auto DGNFRAME = "$DGNFRAME";
    static constexpr auto DIMAPOST = "$DIMAPOST";
    static constexpr auto DIMALTD = "$DIMALTD";
    static constexpr auto DIMALT = "$DIMALT";
    static constexpr auto DIMALTU = "$DIMALTU";
    static constexpr auto DIMALTRND = "$DIMALTRND";
    static constexpr auto DIMALTF = "$DIMALTF";
    static constexpr auto DIMALTTD = "$DIMALTTD";
    static constexpr auto DIMALTTZ = "$DIMALTTZ";
    static constexpr auto DIMALTZ = "$DIMALTZ";
    static constexpr auto DIMALTMZF = "$DIMALTMZF";
    static constexpr auto DIMALTMZS = "$DIMALTMZS";
    static constexpr auto DIMADEC = "$DIMADEC";
    static constexpr auto DIMAUNIT = "$DIMAUNIT";
    static constexpr auto DIMAZIN = "$DIMAZIN";
    static constexpr auto DIMARCSYM = "$DIMARCSYM";
    static constexpr auto DIMASZ = "$DIMASZ";
    static constexpr auto DIMASSOC = "$DIMASSOC";
    static constexpr auto DIMBLK = "$DIMBLK";
    static constexpr auto DIMBLK1 = "$DIMBLK1";
    static constexpr auto DIMBLK2 = "$DIMBLK2";
    static constexpr auto DIMCEN = "$DIMCEN";
    static constexpr auto DIMUPT = "$DIMUPT";
    static constexpr auto DIMDEC = "$DIMDEC";
    static constexpr auto DIMDSEP = "$DIMDSEP";
    static constexpr auto DIMATFIT = "$DIMATFIT";
    static constexpr auto DIMCLRE = "$DIMCLRE";
    static constexpr auto DIMEXE = "$DIMEXE";
    static constexpr auto DIMEXO = "$DIMEXO";
    static constexpr auto DIMFIT = "$DIMFIT";
    static constexpr auto DIMFXL = "$DIMFXL";
    static constexpr auto DIMFRAC = "$DIMFRAC";
    static constexpr auto DIMTOL = "$DIMTOL";
    static constexpr auto DIMFXLON = "$DIMFXLON";
    static constexpr auto DIMJOGANG = "$DIMJOGANG";
    static constexpr auto DIMLIM = "$DIMLIM";
    static constexpr auto DIMLFAC = "$DIMLFAC";
    static constexpr auto DIMLUNIT = "$DIMLUNIT";
    static constexpr auto DIMCLRD = "$DIMCLRD";
    static constexpr auto DIMDLE = "$DIMDLE";
    static constexpr auto DIMGAP = "$DIMGAP";
    static constexpr auto DIMDLI = "$DIMDLI";
    static constexpr auto DIMLTYPE = "$DIMLTYPE";
    static constexpr auto DIMLWD = "$DIMLWD";
    static constexpr auto DIMTM = "$DIMTM";
    static constexpr auto DIMMZF = "$DIMMZF";
    static constexpr auto DIMMZS = "$DIMMZS";
    static constexpr auto DIMTP = "$DIMTP";
    static constexpr auto DIMPOST = "$DIMPOST";
    static constexpr auto DIMRND = "$DIMRND";
    static constexpr auto DIMSCALE = "$DIMSCALE";
    static constexpr auto DIMSAH = "$DIMSAH";
    static constexpr auto DIMSTYLE = "$DIMSTYLE";
    static constexpr auto DIMSD1 = "$DIMSD1";
    static constexpr auto DIMSE1 = "$DIMSE1";
    static constexpr auto DIMSOXD = "$DIMSOXD";
    static constexpr auto DIMSD2 = "$DIMSD2";
    static constexpr auto DIMSE2 = "$DIMSE2";
    static constexpr auto DIMLTEX1 = "$DIMLTEX1";
    static constexpr auto DIMLTEX2 = "$DIMLTEX2";
    static constexpr auto DIMTFILLCLR = "$DIMTFILLCLR";
    static constexpr auto DIMTFILL = "$DIMTFILL";
    static constexpr auto DIMCLRT = "$DIMCLRT";
    static constexpr auto DIMTXTDIRECTION = "$DIMTXTDIRECTION";
    static constexpr auto DIMTXT = "$DIMTXT";
    static constexpr auto DIMJUST = "$DIMJUST";
    static constexpr auto DIMTIX = "$DIMTIX";
    static constexpr auto DIMTIH = "$DIMTIH";
    static constexpr auto DIMTMOVE = "$DIMTMOVE";
    static constexpr auto DIMTOFL = "$DIMTOFL";
    static constexpr auto DIMTOH = "$DIMTOH";
    static constexpr auto DIMTXSTY = "$DIMTXSTY";
    static constexpr auto DIMTAD = "$DIMTAD";
    static constexpr auto DIMTVP = "$DIMTVP";
    static constexpr auto DIMTSZ = "$DIMTSZ";
    static constexpr auto DIMTOLJ = "$DIMTOLJ";
    static constexpr auto DIMTDEC = "$DIMTDEC";
    static constexpr auto DIMTFAC = "$DIMTFAC";
    static constexpr auto DIMTZIN = "$DIMTZIN";
    static constexpr auto DIMUNIT = "$DIMUNIT";
    static constexpr auto DIMZIN = "$DIMZIN";
    static constexpr auto LIGHTGLYPHDISPLAY = "$LIGHTGLYPHDISPLAY";
    static constexpr auto LWDISPLAY = "$LWDISPLAY";
    static constexpr auto DISPSILH = "$DISPSILH";
    static constexpr auto LOFTANG1 = "$LOFTANG1";
    static constexpr auto LOFTANG2 = "$LOFTANG2";
    static constexpr auto LOFTMAG1 = "$LOFTMAG1";
    static constexpr auto LOFTMAG2 = "$LOFTMAG2";
    static constexpr auto _3DDWFPREC = "$3DDWFPREC";
    static constexpr auto DWFFRAME = "$DWFFRAME";
    static constexpr auto ELEVATION = "$ELEVATION";
    static constexpr auto ENDCAPS = "$ENDCAPS";
    static constexpr auto SORTENTS = "$SORTENTS";
    static constexpr auto EXTNAMES = "$EXTNAMES";
    static constexpr auto DIMLWE = "$DIMLWE";
    static constexpr auto XCLIPFRAME = "$XCLIPFRAME";
    static constexpr auto FACETRES = "$FACETRES";
    static constexpr auto FILLETRAD = "$FILLETRAD";
    static constexpr auto FILLMODE = "$FILLMODE";
    static constexpr auto FINGERPRINTGUID = "$FINGERPRINTGUID";
    static constexpr auto HALOGAP = "$HALOGAP";
    static constexpr auto HANDSEED = "$HANDSEED";
    static constexpr auto HIDETEXT = "$HIDETEXT";
    static constexpr auto HYPERLINKBASE = "$HYPERLINKBASE";
    static constexpr auto INDEXCTL = "$INDEXCTL";
    static constexpr auto INSUNITS = "$INSUNITS";
    static constexpr auto INTERFERECOLOR = "$INTERFERECOLOR";
    static constexpr auto JOINSTYLE = "$JOINSTYLE";
    static constexpr auto LASTSAVEDBY = "$LASTSAVEDBY";
    static constexpr auto LATITUDE = "$LATITUDE";
    static constexpr auto LENSLENGTH = "$LENSLENGTH";
    static constexpr auto LIMCHECK = "$LIMCHECK";
    static constexpr auto LUNITS = "$LUNITS";
    static constexpr auto LUPREC = "$LUPREC";
    static constexpr auto LTSCALE = "$LTSCALE";
    static constexpr auto LOFTNORMALS = "$LOFTNORMALS";
    static constexpr auto LONGITUDE = "$LONGITUDE";
    static constexpr auto ACADMAINTVER = "$ACADMAINTVER";
    static constexpr auto MAXACTVP = "$MAXACTVP";
    static constexpr auto MEASUREMENT = "$MEASUREMENT";
    static constexpr auto MENU = "$MENU";
    static constexpr auto MIRRTEXT = "$MIRRTEXT";
    static constexpr auto EXTMAX = "$EXTMAX";
    static constexpr auto EXTMIN = "$EXTMIN";
    static constexpr auto INSBASE = "$INSBASE";
    static constexpr auto LIMMAX = "$LIMMAX";
    static constexpr auto LIMMIN = "$LIMMIN";
    static constexpr auto UCSORG = "$UCSORG";
    static constexpr auto UCSORGBACK = "$UCSORGBACK";
    static constexpr auto UCSORGBOTTOM = "$UCSORGBOTTOM";
    static constexpr auto UCSORGFRONT = "$UCSORGFRONT";
    static constexpr auto UCSORGLEFT = "$UCSORGLEFT";
    static constexpr auto UCSORGRIGHT = "$UCSORGRIGHT";
    static constexpr auto UCSORGTOP = "$UCSORGTOP";
    static constexpr auto UCSXDIR = "$UCSXDIR";
    static constexpr auto UCSYDIR = "$UCSYDIR";
    static constexpr auto NORTHDIRECTION = "$NORTHDIRECTION";
    static constexpr auto SPLINESEGS = "$SPLINESEGS";
    static constexpr auto OSMODE = "$OSMODE";
    static constexpr auto ORTHOMODE = "$ORTHOMODE";
    static constexpr auto PUCSBASE = "$PUCSBASE";
    static constexpr auto PELEVATION = "$PELEVATION";
    static constexpr auto PEXTMAX = "$PEXTMAX";
    static constexpr auto PEXTMIN = "$PEXTMIN";
    static constexpr auto PINSBASE = "$PINSBASE";
    static constexpr auto PLIMCHECK = "$PLIMCHECK";
    static constexpr auto PLIMMAX = "$PLIMMAX";
    static constexpr auto PLIMMIN = "$PLIMMIN";
    static constexpr auto PSLTSCALE = "$PSLTSCALE";
    static constexpr auto PUCSNAME = "$PUCSNAME";
    static constexpr auto PUCSORGBACK = "$PUCSORGBACK";
    static constexpr auto PUCSORGBOTTOM = "$PUCSORGBOTTOM";
    static constexpr auto PUCSORGFRONT = "$PUCSORGFRONT";
    static constexpr auto PUCSORGLEFT = "$PUCSORGLEFT";
    static constexpr auto PUCSORGRIGHT = "$PUCSORGRIGHT";
    static constexpr auto PUCSORGTOP = "$PUCSORGTOP";
    static constexpr auto PUCSORG = "$PUCSORG";
    static constexpr auto PUCSXDIR = "$PUCSXDIR";
    static constexpr auto PUCSYDIR = "$PUCSYDIR";
    static constexpr auto PSTYLEMODE = "$PSTYLEMODE";
    static constexpr auto PDMODE = "$PDMODE";
    static constexpr auto PDSIZE = "$PDSIZE";
    static constexpr auto PLINEGEN = "$PLINEGEN";
    static constexpr auto PLINEWID = "$PLINEWID";
    static constexpr auto PROJECTNAME = "$PROJECTNAME";
    static constexpr auto PROXYGRAPHICS = "$PROXYGRAPHICS";
    static constexpr auto QTEXTMODE = "$QTEXTMODE";
    static constexpr auto REGENMODE = "$REGENMODE";
    static constexpr auto REQUIREDVERSIONS = "$REQUIREDVERSIONS";
    static constexpr auto VISRETAIN = "$VISRETAIN";
    static constexpr auto SHADEDIF = "$SHADEDIF";
    static constexpr auto SHADEDGE = "$SHADEDGE";
    static constexpr auto CSHADOW = "$CSHADOW";
    static constexpr auto SHADOWPLANELOCATION = "$SHADOWPLANELOCATION";
    static constexpr auto TILEMODE = "$TILEMODE";
    static constexpr auto SHOWHIST = "$SHOWHIST";
    static constexpr auto SPLFRAME = "$SPLFRAME";
    static constexpr auto SKETCHINC = "$SKETCHINC";
    static constexpr auto SKPOLY = "$SKPOLY";
    static constexpr auto LOFTPARAM = "$LOFTPARAM";
    static constexpr auto SOLIDHIST = "$SOLIDHIST";
    static constexpr auto TREEDEPTH = "$TREEDEPTH";
    static constexpr auto SPLINETYPE = "$SPLINETYPE";
    static constexpr auto STEPSIZE = "$STEPSIZE";
    static constexpr auto STEPSPERSEC = "$STEPSPERSEC";
    static constexpr auto STYLESHEET = "$STYLESHEET";
    static constexpr auto SURFU = "$SURFU";
    static constexpr auto SURFV = "$SURFV";
    static constexpr auto SURFTAB1 = "$SURFTAB1";
    static constexpr auto SURFTAB2 = "$SURFTAB2";
    static constexpr auto SURFTYPE = "$SURFTYPE";
    static constexpr auto PSOLHEIGHT = "$PSOLHEIGHT";
    static constexpr auto PSOLWIDTH = "$PSOLWIDTH";
    static constexpr auto TEXTSIZE = "$TEXTSIZE";
    static constexpr auto TEXTSTYLE = "$TEXTSTYLE";
    static constexpr auto THICKNESS = "$THICKNESS";
    static constexpr auto TIMEZONE = "$TIMEZONE";
    static constexpr auto TDINDWG = "$TDINDWG";
    static constexpr auto TRACEWID = "$TRACEWID";
    static constexpr auto UCSBASE = "$UCSBASE";
    static constexpr auto UCSNAME = "$UCSNAME";
    static constexpr auto UNITMODE = "$UNITMODE";
    static constexpr auto TDUCREATE = "$TDUCREATE";
    static constexpr auto TDUUPDATE = "$TDUUPDATE";
    static constexpr auto TDUPDATE = "$TDUPDATE";
    static constexpr auto DIMSHO = "$DIMSHO";
    static constexpr auto USERR1 = "$USERR1";
    static constexpr auto USERR2 = "$USERR2";
    static constexpr auto USERR3 = "$USERR3";
    static constexpr auto USERR4 = "$USERR4";
    static constexpr auto USERR5 = "$USERR5";
    static constexpr auto TDUSRTIMER = "$TDUSRTIMER";
    static constexpr auto USERI1 = "$USERI1";
    static constexpr auto USERI2 = "$USERI2";
    static constexpr auto USERI3 = "$USERI3";
    static constexpr auto USERI4 = "$USERI4";
    static constexpr auto USERI5 = "$USERI5";
    static constexpr auto USRTIMER = "$USRTIMER";
    static constexpr auto VERSIONGUID = "$VERSIONGUID";
    static constexpr auto ACADVER = "$ACADVER";
    static constexpr auto PSVPSCALE = "$PSVPSCALE";
    static constexpr auto WORLDVIEW = "$WORLDVIEW";
    static constexpr auto XEDIT = "$XEDIT";
    
    static std::map<std::string, CadSystemVariableAttribute> headerMap();

    static DwgVariant value(const std::string &, const DxfCode &, CadHeader *header);

    static DwgVariant value(const std::string &, CadHeader *header);

    static void setValue(CadHeader *header, const std::string &key, const std::vector<DwgVariant> &parameters);
};

}// namespace dwg
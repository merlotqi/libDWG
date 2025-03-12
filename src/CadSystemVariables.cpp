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

#include <dwg/CadSystemVariables_p.h>

namespace dwg {

static std::vector<CadSystemVariableAttribute> _headerVariables = {
    {"$ANGBASE", {50}},
    {"$ANGDIR", {70}},
    {"$AUNITS", {70}},
    {"$AUPREC", {70}},
    {"$DIMLDRBLK", {1}},
    {"$DIMASO", {70}},
    {"$ATTMODE", {70}},
    {"$BLIPMODE", 70}
    {"$CAMERADISPLAY", 290}
    {"$CAMERAHEIGHT", 40}
    {"$CHAMFERD", 40}
    {"$CHAMFERA", 40}
    {"$CHAMFERB", 40}
    {"$CHAMFERC", 40}
    {"$DWGCODEPAGE", 3}
    {"$TDCREATE", 40}
    {"$PELLIPSE", 70}
    {"$CECOLOR", 62}
    {"$CELTSCALE", 40}
    {"$CELWEIGHT", 370}
    {"$CEPSNTYPE", 380}
    {"$CLAYER", true, 8}
    {"$CELTYPE", true, 6}
    {"$CMLJUST", 70}
    {"$CMLSCALE", 40}
    {"$CMLSTYLE", true, 2}
    {"$DGNFRAME", 280}
    {"$DIMAPOST", 1}
    {"$DIMALTD", 70}
    {"$DIMALT", 70}
    {"$DIMALTU", 70}
    {"$DIMALTRND", 40}
    {"$DIMALTF", 40}
    {"$DIMALTTD", 70}
    {"$DIMALTTZ", 70}
    {"$DIMALTZ", 70}
    {"$DIMALTMZF", 40}
    {"$DIMALTMZS", 6}
    {"$DIMADEC", 70}
    {"$DIMAUNIT", 70}
    {"$DIMAZIN", 70}
    {"$DIMARCSYM", 70}
    {"$DIMASZ", 40}
    {"$DIMASSOC", 280}
    {"$DIMBLK", 1}
    {"$DIMBLK1", 1}
    {"$DIMBLK2", 1}
    {"$DIMCEN", 40}
    {"$DIMUPT", 70}
    {"$DIMDEC", 70}
    {"$DIMDSEP", 70}
    {"$DIMATFIT", 70}
    {"$DIMCLRE", 70}
    {"$DIMEXE", 40}
    {"$DIMEXO", 40}
    {"$DIMFIT", 70}
    {"$DIMFXL", 40}
    {"$DIMFRAC", 70}
    {"$DIMTOL", 70}
    {"$DIMFXLON", 70}
    {"$DIMJOGANG", 40}
    {"$DIMLIM", 70}
    {"$DIMLFAC", 40}
    {"$DIMLUNIT", 70}
    {"$DIMCLRD", 70}
    {"$DIMDLE", 40}
    {"$DIMGAP", 40}
    {"$DIMDLI", 40}
    {"$DIMLTYPE", 6}
    {"$DIMLWD", 70}
    {"$DIMTM", 40}
    {"$DIMMZF", 40}
    {"$DIMMZS", 6}
    {"$DIMTP", 40}
    {"$DIMPOST", 1}
    {"$DIMRND", 40}
    {"$DIMSCALE", 40}
    {"$DIMSAH", 70}
    {"$DIMSTYLE", true, 2}
    {"$DIMSD1", 70}
    {"$DIMSE1", 70}
    {"$DIMSOXD", 70}
    {"$DIMSD2", 70}
    {"$DIMSE2", 70}
    {"$DIMLTEX1", 6}
    {"$DIMLTEX2", 6}
    {DxfReferenceType::Ignored, "$DIMTFILLCLR", 62}
    {"$DIMTFILL", 70}
    {"$DIMCLRT", 70}
    {"$DIMTXTDIRECTION", 70}
    {"$DIMTXT", 40}
    {"$DIMJUST", 70}
    {"$DIMTIX", 70}
    {"$DIMTIH", 70}
    {"$DIMTMOVE", 70}
    {"$DIMTOFL", 70}
    {"$DIMTOH", 70}
    {"$DIMTXSTY", true, 7}
    {"$DIMTAD", 70}
    {"$DIMTVP", 40}
    {"$DIMTSZ", 40}
    {"$DIMTOLJ", 70}
    {"$DIMTDEC", 70}
    {"$DIMTFAC", 40}
    {"$DIMTZIN", 70}
    {"$DIMUNIT", 70}
    {"$DIMZIN", 70}
    {"$LIGHTGLYPHDISPLAY", 280}
    {"$LWDISPLAY", 290}
    {"$DISPSILH", 70}
    {"$LOFTANG1", 40}
    {"$LOFTANG2", 40}
    {"$LOFTMAG1", 40}
    {"$LOFTMAG2", 40}
    {"$3DDWFPREC", 40}
    {"$DWFFRAME", 280}
    {"$ELEVATION", 40}
    {"$ENDCAPS", 280}
    {"$SORTENTS", 280}
    {"$EXTNAMES", 290}
    {"$DIMLWE", 70}
    {"$XCLIPFRAME", 280}
    {"$FACETRES", 40}
    {"$FILLETRAD", 40}
    {"$FILLMODE", 70}
    {"$FINGERPRINTGUID", 2}
    {"$HALOGAP", 280}
    {"$HANDSEED", 5}
    {"$HIDETEXT", 280}
    {"$HYPERLINKBASE", 1}
    {"$INDEXCTL", 280}
    {"$INSUNITS", 70}
    {"$INTERFERECOLOR", 62}
    {"$JOINSTYLE", 280}
    {DxfReferenceType::Ignored, "$LASTSAVEDBY", 3}
    {"$LATITUDE", 40}
    {"$LENSLENGTH", 40}
    {"$LIMCHECK", 70}
    {"$LUNITS", 70}
    {"$LUPREC", 70}
    {"$LTSCALE", 40}
};

std::vector<CadSystemVariableAttribute> CadSystemVariables::headerVariables()
{

}

}
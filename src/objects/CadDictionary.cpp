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

#include <dwg/objects/CadDictionary.h>

namespace dwg {

CPL::String CadDictionary::Root = "ROOT";
CPL::String CadDictionary::AcadColor = "ACAD_COLOR";
CPL::String CadDictionary::AcadGroup = "ACAD_GROUP";
CPL::String CadDictionary::AcadLayout = "ACAD_LAYOUT";
CPL::String CadDictionary::AcadMaterial = "ACAD_MATERIAL";
CPL::String CadDictionary::AcadSortEnts = "ACAD_SORTENTS";
CPL::String CadDictionary::AcadMLeaderStyle = "ACAD_MLEADERSTYLE";
CPL::String CadDictionary::AcadMLineStyle = "ACAD_MLINESTYLE";
CPL::String CadDictionary::AcadTableStyle = "ACAD_TABLESTYLE";
CPL::String CadDictionary::AcadPlotSettings = "ACAD_PLOTSETTINGS";
CPL::String CadDictionary::VariableDictionary = "AcDbVariableDictionary";
CPL::String CadDictionary::AcadPlotStyleName = "ACAD_PLOTSTYLENAME";
CPL::String CadDictionary::AcadScaleList = "ACAD_SCALELIST";
CPL::String CadDictionary::AcadVisualStyle = "ACAD_VISUALSTYLE";
CPL::String CadDictionary::AcadFieldList = "ACAD_FIELDLIST";
CPL::String CadDictionary::AcadImageDict = "ACAD_IMAGE_DICT";

}
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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/objects/CadDictionary.h>


namespace dwg {

std::string CadDictionary::Root = "ROOT";
std::string CadDictionary::AcadColor = "ACAD_COLOR";
std::string CadDictionary::AcadGroup = "ACAD_GROUP";
std::string CadDictionary::AcadLayout = "ACAD_LAYOUT";
std::string CadDictionary::AcadMaterial = "ACAD_MATERIAL";
std::string CadDictionary::AcadSortEnts = "ACAD_SORTENTS";
std::string CadDictionary::AcadMLeaderStyle = "ACAD_MLEADERSTYLE";
std::string CadDictionary::AcadMLineStyle = "ACAD_MLINESTYLE";
std::string CadDictionary::AcadTableStyle = "ACAD_TABLESTYLE";
std::string CadDictionary::AcadPlotSettings = "ACAD_PLOTSETTINGS";
std::string CadDictionary::VariableDictionary = "AcDbVariableDictionary";
std::string CadDictionary::AcadPlotStyleName = "ACAD_PLOTSTYLENAME";
std::string CadDictionary::AcadScaleList = "ACAD_SCALELIST";
std::string CadDictionary::AcadVisualStyle = "ACAD_VISUALSTYLE";
std::string CadDictionary::AcadFieldList = "ACAD_FIELDLIST";
std::string CadDictionary::AcadImageDict = "ACAD_IMAGE_DICT";
std::string CadDictionary::GeographicData = "ACAD_GEOGRAPHICDATA";

CadDictionary *CadDictionary::CreateRoot()
{
    return nullptr;
}

void CadDictionary::CreateDefaultEntries(CadDictionary *root) {}

CadDictionary::CadDictionary() {}

CadDictionary::CadDictionary(const std::string &name) : NonGraphicalObject(name) {}

ObjectType CadDictionary::objectType() const
{
    return ObjectType::DICTIONARY;
}

std::string CadDictionary::objectName() const
{
    return DxfFileToken::ObjectDictionary;
}

std::string CadDictionary::subclassMarker() const
{
    return DxfSubclassMarker::Dictionary;
}

bool CadDictionary::hardOwnerFlag() const
{
    return _hardOwnerFlag;
}

void CadDictionary::setHardOwnerFlag(bool value)
{
    _hardOwnerFlag = value;
}

DictionaryCloningFlags CadDictionary::clonningFlags() const
{
    return _clonningFlags;
}

void CadDictionary::setClonningFlags(DictionaryCloningFlags value)
{
    _clonningFlags = value;
}

}// namespace dwg
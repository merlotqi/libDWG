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
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/objects/Scale.h>


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
    CadDictionary *pRoot = new CadDictionary(Root);
    CreateDefaultEntries(pRoot);
    return pRoot;
}

void CadDictionary::CreateDefaultEntries(CadDictionary *root)
{
    assert(root);

    root->tryAdd(new CadDictionary(AcadColor));
    root->tryAdd(new CadDictionary(AcadGroup));

    CadDictionary *layouts = root->ensureCadDictionaryExist(AcadLayout);

    root->tryAdd(new CadDictionary(AcadMaterial));
    root->tryAdd(new CadDictionary(AcadSortEnts));

    CadDictionary *mLeaderStyles = root->ensureCadDictionaryExist(AcadMLeaderStyle);
    mLeaderStyles->tryAdd(MultiLeaderStyle::Default());

    CadDictionary *mLineStyles = root->ensureCadDictionaryExist(AcadMLineStyle);
    mLineStyles->tryAdd(MLineStyle::Default());

    root->tryAdd(new CadDictionary(AcadTableStyle));
    root->tryAdd(new CadDictionary(AcadPlotSettings));

    root->tryAdd(new CadDictionary(VariableDictionary));

    CadDictionary *scales = root->ensureCadDictionaryExist(AcadScaleList);
    scales->tryAdd(new Scale("A0", 1.0, 1.0, true));
    scales->tryAdd(new Scale("A1", 1.0, 2.0, false));
    scales->tryAdd(new Scale("A2", 1.0, 4.0, false));
    scales->tryAdd(new Scale("A3", 1.0, 5.0, false));
    scales->tryAdd(new Scale("A4", 1.0, 8.0, false));
    scales->tryAdd(new Scale("A5", 1.0, 10.0, false));
    scales->tryAdd(new Scale("A6", 1.0, 16.0, false));
    scales->tryAdd(new Scale("A7", 1.0, 20.0, false));
    scales->tryAdd(new Scale("A8", 1.0, 30.0, false));
    scales->tryAdd(new Scale("A9", 1.0, 40.0, false));
    scales->tryAdd(new Scale("B0", 1.0, 50.0, false));
    scales->tryAdd(new Scale("B1", 1.0, 100.0, false));
    scales->tryAdd(new Scale("B2", 2.0, 1.0, false));
    scales->tryAdd(new Scale("B3", 4.0, 1.0, false));
    scales->tryAdd(new Scale("B4", 8.0, 1.0, false));
    scales->tryAdd(new Scale("B5", 10.0, 1.0, false));
    scales->tryAdd(new Scale("B6", 100.0, 1.0, false));

    root->tryAdd(new CadDictionary(AcadVisualStyle));
    root->tryAdd(new CadDictionary(AcadFieldList));
    root->tryAdd(new CadDictionary(AcadImageDict));
}

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

bool CadDictionary::StringComparerOrdinalIgnoreCase::operator()(const std::string &lhs, const std::string &rhs) const
{
    if (lhs.size() != rhs.size())
    {
        return false;
    }

    for (size_t i = 0; i < lhs.size(); ++i)
    {
        if (std::toupper(lhs[i]) != std::toupper(rhs[i]))
        {
            return false;
        }
    }

    return true;
}

}// namespace dwg
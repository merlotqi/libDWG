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

#include <dwg/enums/objects/DictionaryCloningFlags.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <map>
#include <string>
#include <vector>


namespace dwg {
namespace objects {

class CadDictionary : public NonGraphicalObject
{
    std::map<std::string, NonGraphicalObject *> _entries;

public:
    static constexpr auto Root = "ROOT";
    static constexpr auto AcadColor = "ACAD_COLOR";
    static constexpr auto AcadGroup = "ACAD_GROUP";
    static constexpr auto AcadLayout = "ACAD_LAYOUT";
    static constexpr auto AcadMaterial = "ACAD_MATERIAL";
    static constexpr auto AcadSortEnts = "ACAD_SORTENTS";
    static constexpr auto AcadMLeaderStyle = "ACAD_MLEADERSTYLE";
    static constexpr auto AcadMLineStyle = "ACAD_MLINESTYLE";
    static constexpr auto AcadTableStyle = "ACAD_TABLESTYLE";
    static constexpr auto AcadPlotSettings = "ACAD_PLOTSETTINGS";
    static constexpr auto VariableDictionary = "AcDbVariableDictionary";
    static constexpr auto AcadPlotStyleName = "ACAD_PLOTSTYLENAME";
    static constexpr auto AcadScaleList = "ACAD_SCALELIST";
    static constexpr auto AcadVisualStyle = "ACAD_VISUALSTYLE";
    static constexpr auto AcadFieldList = "ACAD_FIELDLIST";
    static constexpr auto AcadImageDict = "ACAD_IMAGE_DICT";

    bool HardOwnerFlag;

    DictionaryCloningFlags ClonningFlags;
    std::vector<std::string> EntryName() const;
    std::vector<unsigned long long> EntryHandles() const;

    CadObject *operator[](const std::string &key);

    static CadDictionary *CreateRoot();
    static void CreateDefaultEntries(CadDictionary *root);

public:
    CadDictionary() {}
    CadDictionary(const std::string &name) {}
     dwg::ObjectType ObjectType() const override {return dwg::ObjectType::DICTIONARY;}
     std::string ObjectName() const override {return DxfFileToken::ObjectDictionary;}
     std::string SubclassMarker() const override {return DxfSubclassMarker::Dictionary;}

    void Add(const std::string &key, NonGraphicalObject *value);
    void Add(NonGraphicalObject *value);
    bool TryAdd(NonGraphicalObject *value) const;
    bool ContainsKey(const std::string &key) const;
    void Remove(const std::string &key, NonGraphicalObject *&item);
    void Clear();

    template<class T>
    bool TryGetEntry(const std::string &name, T *&value)
    {
    }
};

}// namespace objects
}// namespace dwg
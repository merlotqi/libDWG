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

#include <dwg/objects/DictionaryCloningFlags.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <map>
#include <string>
#include <vector>

namespace dwg {

class CadDictionary : public NonGraphicalObject
{
    std::map<std::string, NonGraphicalObjectPtr> _entries;
    bool _hard_owner_flag;
    DictionaryCloningFlags _clonning_flags;

public:
    static std::string Root;
    static std::string AcadColor;
    static std::string AcadGroup;
    static std::string AcadLayout;
    static std::string AcadMaterial;
    static std::string AcadSortEnts;
    static std::string AcadMLeaderStyle;
    static std::string AcadMLineStyle;
    static std::string AcadTableStyle;
    static std::string AcadPlotSettings;
    static std::string VariableDictionary;
    static std::string AcadPlotStyleName;
    static std::string AcadScaleList;
    static std::string AcadVisualStyle;
    static std::string AcadFieldList;
    static std::string AcadImageDict;


public:
    CadDictionary();
    CadDictionary(const std::string &name);
     dwg::ObjectType ObjectType() const override {return dwg::ObjectType::DICTIONARY;}
     std::string ObjectName() const override {return DxfFileToken::ObjectDictionary;}
     std::string SubclassMarker() const override {return DxfSubclassMarker::Dictionary;}

    void Add(const std::string &key, NonGraphicalObject *value);
    void Add(NonGraphicalObject *value);
    bool TryAdd(NonGraphicalObject *value) const;
    bool ContainsKey(const std::string &key) const;
    NonGraphicalObjectPtr Remove(const std::string &key);
    void Clear();

    bool HardOwnerFlag() const;
    void HardOwnerFlag(bool );

    DictionaryCloningFlags ClonningFlags() const;
    void ClonningFlags(DictionaryCloningFlags );
    
    std::vector<std::string> EntryName() const;
    std::vector<unsigned long long> EntryHandles() const;

    CadObjectPtr operator[](const std::string &key);

    static SmarterPtr<CadDictionary> CreateRoot();
    static void CreateDefaultEntries(CadDictionary *root);

    NonGraphicalObjectPtr TryGetEntry(const std::string &name);

private:
    SmarterPtr<CadDictionary> ensureCadDictionaryExist(const std::string& name);
    void onEntryNameChanged(const std::string& olName, const std::string& newName);
};
SMARTER_PTR(CadDictionary)


}// namespace dwg
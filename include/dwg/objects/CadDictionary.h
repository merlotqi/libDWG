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
    std::map<CPL::String, NonGraphicalObjectPtr> _entries;
    bool _hard_owner_flag;
    DictionaryCloningFlags _clonning_flags;

public:
    static CPL::String Root;
    static CPL::String AcadColor;
    static CPL::String AcadGroup;
    static CPL::String AcadLayout;
    static CPL::String AcadMaterial;
    static CPL::String AcadSortEnts;
    static CPL::String AcadMLeaderStyle;
    static CPL::String AcadMLineStyle;
    static CPL::String AcadTableStyle;
    static CPL::String AcadPlotSettings;
    static CPL::String VariableDictionary;
    static CPL::String AcadPlotStyleName;
    static CPL::String AcadScaleList;
    static CPL::String AcadVisualStyle;
    static CPL::String AcadFieldList;
    static CPL::String AcadImageDict;


public:
    CadDictionary();
    CadDictionary(const CPL::String &name);
     dwg::ObjectType ObjectType() const override {return dwg::ObjectType::DICTIONARY;}
     CPL::String ObjectName() const override {return DxfFileToken::ObjectDictionary;}
     CPL::String SubclassMarker() const override {return DxfSubclassMarker::Dictionary;}

    void Add(const CPL::String &key, NonGraphicalObject *value);
    void Add(NonGraphicalObject *value);
    bool TryAdd(NonGraphicalObject *value) const;
    bool ContainsKey(const CPL::String &key) const;
    NonGraphicalObjectPtr Remove(const CPL::String &key);
    void Clear();

    bool HardOwnerFlag() const;
    void HardOwnerFlag(bool );

    DictionaryCloningFlags ClonningFlags() const;
    void ClonningFlags(DictionaryCloningFlags );
    
    std::vector<CPL::String> EntryName() const;
    std::vector<unsigned long long> EntryHandles() const;

    CadObjectPtr operator[](const CPL::String &key);

    static SmarterPtr<CadDictionary> CreateRoot();
    static void CreateDefaultEntries(CadDictionary *root);

    NonGraphicalObjectPtr TryGetEntry(const CPL::String &name);

private:
    SmarterPtr<CadDictionary> ensureCadDictionaryExist(const CPL::String& name);
    void onEntryNameChanged(const CPL::String& olName, const CPL::String& newName);
};
CPL_SMARTER_PTR(CadDictionary)


}// namespace dwg
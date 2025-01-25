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

#include <vector>

namespace dwg {

class LIBDWG_API DG_CadDictionary : public DG_NonGraphicalObject
{
    std::map<CPL::String, DG_NonGraphicalObjectWPtr> _entries;
    bool _hard_owner_flag;
    DG_DictionaryCloningFlags _clonning_flags;

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
    DG_CadDictionary();
    DG_CadDictionary(const char *name);
    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;

    void Add(const char *key, DG_NonGraphicalObject *value);
    void Add(DG_NonGraphicalObject *value);
    bool TryAdd(DG_NonGraphicalObject *value) const;
    bool ContainsKey(const char *key) const;
    DG_NonGraphicalObjectPtr Remove(const char *key);
    void Clear();

    bool HardOwnerFlag() const;
    void HardOwnerFlag(bool);

    DG_DictionaryCloningFlags ClonningFlags() const;
    void ClonningFlags(DG_DictionaryCloningFlags);

    std::vector<CPL::String> EntryName() const;
    std::vector<unsigned long long> EntryHandles() const;

    DG_CadObjectPtr operator[](const char *key);

    static CPL::SmarterPtr<DG_CadDictionary> CreateRoot();
    static void CreateDefaultEntries(DG_CadDictionary *root);

    DG_NonGraphicalObjectPtr TryGetEntry(const char *name);

private:
    CPL::SmarterPtr<DG_CadDictionary>
    ensureCadDictionaryExist(const char *name);
    void onEntryNameChanged(const char *olName, const char *newName);
};
CPL_SMARTER_PTR(DG_CadDictionary)


}// namespace dwg
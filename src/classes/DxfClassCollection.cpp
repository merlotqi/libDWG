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

#include <dwg/classes/DxfClassCollection.h>
#include <dwg/CadDocument.h>
#include <dwg/classes/DxfClass.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>

namespace dwg {

void DxfClassCollection::UpdateDxfClasses(CadDocument *doc)
{
    //AcDbDictionaryWithDefault
    doc->Classes.addOrUpdate(new DxfClass("AcDbDictionaryWithDefault", (short) (500 + doc->Classes.count()),
                                          (ACadVersion) 22, "ACDBDICTIONARYWDFLT", 499, 42, ProxyFlag::R13FormatProxy,
                                          false));

    //AcDbPlaceHolder
    doc->Classes.addOrUpdate(new DxfClass("AcDbPlaceHolder", (short) (500 + doc->Classes.count()), (ACadVersion) 0,
                                          "ACDBPLACEHOLDER", 499, 0, ProxyFlag::None, false));

    //AcDbLayout
    doc->Classes.addOrUpdate(new DxfClass("AcDbLayout", (short) (500 + doc->Classes.count()), (ACadVersion) 0, "LAYOUT",
                                          499, 0, ProxyFlag::None, false));

    //AcDbDictionaryVar
    doc->Classes.addOrUpdate(new DxfClass("AcDbDictionaryVar", (short) (500 + doc->Classes.count()), (ACadVersion) 20,
                                          "DICTIONARYVAR", 499, 0, ProxyFlag::None, false));

    //AcDbTableStyle
    doc->Classes.addOrUpdate(new DxfClass("AcDbTableStyle", (short) (500 + doc->Classes.count()), ACadVersion::AC1018,
                                          "TABLESTYLE", 499, 0, (ProxyFlags) 4095, false));

    //AcDbMaterial
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbMaterial", (short) (500 + doc->Classes.count()), (ACadVersion) 0, "MATERIAL", 499, 0,
            ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog),
            false));

    //AcDbVisualStyle
    doc->Classes.addOrUpdate(new DxfClass("AcDbVisualStyle", (short) (500 + doc->Classes.count()), ACadVersion::AC1021,
                                          "VISUALSTYLE", 499, 0, (ProxyFlags) 4095, false));

    //AcDbScale
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbScale", (short) (500 + doc->Classes.count()), ACadVersion::AC1021, "SCALE", 499, 1,
            ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog),
            false));

    //AcDbMLeaderStyle
    doc->Classes.addOrUpdate(new DxfClass("AcDbMLeaderStyle", (short) (500 + doc->Classes.count()), ACadVersion::AC1021,
                                          "MLEADERSTYLE", 499, 25, (ProxyFlags) 4095, false));

    //AcDbCellStyleMap
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbCellStyleMap", (short) (500 + doc->Classes.count()), ACadVersion::AC1021, "CELLSTYLEMAP", 499, 25,
            ProxyFlags(ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog), false));

    //ExAcXREFPanelObject
    doc->Classes.addOrUpdate(new DxfClass(
            "ExAcXREFPanelObject", (short) (500 + doc->Classes.count()), (ACadVersion) 0, "EXACXREFPANELOBJECT", 499, 0,
            ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog), false));

    //AcDbImpNonPersistentObjectsCollection
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbImpNonPersistentObjectsCollection", (short) (500 + doc->Classes.count()), (ACadVersion) 0,
            "NPOCOLLECTION", 499, 0,
            ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog),
            false));

    //AcDbLayerIndex
    doc->Classes.addOrUpdate(new DxfClass("AcDbLayerIndex", (short) (500 + doc->Classes.count()), (ACadVersion) 0,
                                          "LAYER_INDEX", 499, 0, ProxyFlag::None, false));

    //AcDbSpatialIndex
    doc->Classes.addOrUpdate(new DxfClass("AcDbSpatialIndex", (short) (500 + doc->Classes.count()), (ACadVersion) 0,
                                          "SPATIAL_INDEX", 499, 0, ProxyFlag::None, false));

    //AcDbIdBuffer
    doc->Classes.addOrUpdate(new DxfClass("AcDbIdBuffer", (short) (500 + doc->Classes.count()), ACadVersion::AC1014,
                                          "IDBUFFER", 499, 0, ProxyFlag::R13FormatProxy, false));

    //AcDbSectionViewStyle
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbSectionViewStyle", (short) (500 + doc->Classes.count()), (ACadVersion) 0, "ACDBSECTIONVIEWSTYLE", 499,
            0, ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog), false));

    //AcDbDetailViewStyle
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbDetailViewStyle", (short) (500 + doc->Classes.count()), (ACadVersion) 0, "ACDBDETAILVIEWSTYLE", 499, 0,
            ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog), false));

    //AcDbSubDMesh
    doc->Classes.addOrUpdate(new DxfClass("AcDbSubDMesh", (short) (500 + doc->Classes.count()), (ACadVersion) 0, "MESH",
                                          498, 0, ProxyFlag::None, false));

    //AcDbSortentsTable
    doc->Classes.addOrUpdate(new DxfClass("AcDbSortentsTable", (short) (500 + doc->Classes.count()),
                                          ACadVersion::AC1014, "SORTENTSTABLE", 499, 0, ProxyFlag::None, false));

    //AcDbTextObjectContextData
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbTextObjectContextData", (short) (500 + doc->Classes.count()), (ACadVersion) 0,
            "ACDB_TEXTOBJECTCONTEXTDATA_CLASS", 499, 0,
            ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog),
            false));

    //AcDbWipeout
    doc->Classes.addOrUpdate(new DxfClass(
            "WipeOut", "AcDbWipeout", (short) (500 + doc->Classes.count()), ACadVersion::AC1015, "WIPEOUT", 498, 0,
            ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::TransformAllowed | ProxyFlag::ColorChangeAllowed |
                       ProxyFlag::LayerChangeAllowed | ProxyFlag::LinetypeChangeAllowed |
                       ProxyFlag::LinetypeScaleChangeAllowed | ProxyFlag::VisibilityChangeAllowed |
                       ProxyFlag::R13FormatProxy),
            false));

    //AcDbWipeoutVariables
    doc->Classes.addOrUpdate(new DxfClass("WipeOut", "AcDbWipeoutVariables", (short) (500 + doc->Classes.count()),
                                          ACadVersion::AC1015, "WIPEOUTVARIABLES", 499, 0, ProxyFlag::R13FormatProxy,
                                          false));

    //AcDbDimAssoc
    doc->Classes.addOrUpdate(new DxfClass("AcDbDimAssoc", "AcDbDimAssoc", (short) (500 + doc->Classes.count()),
                                          (ACadVersion) 0, "DIMASSOC", 499, 0, ProxyFlag::None, false));

    //AcDbTable
    doc->Classes.addOrUpdate(
            new DxfClass("AcDbTable", (short) (500 + doc->Classes.count()), ACadVersion::AC1018, "ACAD_TABLE", 498, 0,
                         ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog), false));

    //AcDbTableContent
    doc->Classes.addOrUpdate(new DxfClass(
            "AcDbTableContent", (short) (500 + doc->Classes.count()), ACadVersion::AC1018, "TABLECONTENT", 499, 21,
            ProxyFlags(ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog), false));

    //AcDbTableGeometry
    doc->Classes.addOrUpdate(
            new DxfClass("AcDbTableGeometry", (short) (500 + doc->Classes.count()), (ACadVersion) 0, "TABLEGEOMETRY",
                         499, 0, ProxyFlags(ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog), false));

    //AcDbRasterImage
    doc->Classes.addOrUpdate(
            new DxfClass(DxfSubclassMarker::RasterImage, (short) (500 + doc->Classes.count()), ACadVersion::AC1014,
                         DxfFileToken::EntityImage, 498, 0,
                         ProxyFlags(ProxyFlag::EraseAllowed | ProxyFlag::TransformAllowed |
                                    ProxyFlag::ColorChangeAllowed | ProxyFlag::LayerChangeAllowed |
                                    ProxyFlag::LinetypeChangeAllowed | ProxyFlag::LinetypeScaleChangeAllowed |
                                    ProxyFlag::VisibilityChangeAllowed | ProxyFlag::R13FormatProxy),
                         false));

    //AcDbRasterImageDef
    doc->Classes.addOrUpdate(new DxfClass(DxfSubclassMarker::RasterImageDef, (short) (500 + doc->Classes.count()),
                                          ACadVersion::AC1014, DxfFileToken::ObjectImageDefinition, 499, 0,
                                          ProxyFlag::R13FormatProxy, false));

    //AcDbColor
    doc->Classes.addOrUpdate(new DxfClass(DxfSubclassMarker::DbColor, (short) (500 + doc->Classes.count()),
                                          ACadVersion::AC1015, DxfFileToken::ObjectDBColor, 499, 14, ProxyFlag::None,
                                          false));
};

void DxfClassCollection::add(DxfClass *cls)
{
    if (!cls) return;
    _entries.insert({cls->dxfName(), cls});
}

void DxfClassCollection::addOrUpdate(DxfClass *item) {}

DxfClass *DxfClassCollection::getByName(const std::string &name) const
{
    auto it = _entries.find(name);
    if (it != _entries.end()) { return it->second; }
    else { return nullptr; }
}

size_t DxfClassCollection::count() const { return _entries.size(); }

void DxfClassCollection::clear() { _entries.clear(); }

bool DxfClassCollection::contains(const std::string &name) const
{
    auto it = _entries.find(name);
    return (it == _entries.end()) ? false : true;
}

}// namespace dwg
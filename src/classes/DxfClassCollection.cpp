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

#include <dwg/CadDocument.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/classes/DxfClass.h>
#include <dwg/classes/DxfClassCollection.h>

namespace dwg {

DxfClassCollection::~DxfClassCollection()
{
    for (auto &it: _entries) delete it.second;
}

void DxfClassCollection::UpdateDxfClasses(CadDocument *doc)
{
    //AcDbDictionaryWithDefault
    doc->classes()->addOrUpdate(new DxfClass(
            DxfSubclassMarker::DictionaryWithDefault, (short) (500 + doc->classes()->count()), (ACadVersion) 22,
            DxfFileToken::ObjectDictionaryWithDefault, 499, 42, ProxyFlag::R13FormatProxy, false));

    //AcDbPlaceHolder
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::AcDbPlaceHolder,
                                             (short) (500 + doc->classes()->count()), (ACadVersion) 0,
                                             DxfFileToken::ObjectPlaceholder, 499, 0, ProxyFlag::None, false));

    //AcDbLayout
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::Layout, (short) (500 + doc->classes()->count()),
                                             (ACadVersion) 0, DxfFileToken::ObjectLayout, 499, 0, ProxyFlag::None,
                                             false));

    //AcDbDictionaryVar
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::DictionaryVar, (short) (500 + doc->classes()->count()),
                                             (ACadVersion) 20, DxfFileToken::ObjectDictionaryVar, 499, 0,
                                             ProxyFlag::None, false));

    //AcDbTableStyle
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::TableStyle, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1018, DxfFileToken::ObjectTableStyle, 499, 0,
                                             (ProxyFlags) 4095, false));

    //AcDbMaterial
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::Material, (short) (500 + doc->classes()->count()),
                                             (ACadVersion) 0, DxfFileToken::ObjectMaterial, 499, 0,
                                             ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed |
                                                     ProxyFlag::DisablesProxyWarningDialog,
                                             false));

    //AcDbVisualStyle
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::VisualStyle, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1021, DxfFileToken::ObjectVisualStyle, 499, 0,
                                             (ProxyFlags) 4095, false));

    //AcDbScale
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::Scale, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1021, DxfFileToken::ObjectScale, 499, 1,
                                             ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed |
                                                     ProxyFlag::DisablesProxyWarningDialog,
                                             false));

    //AcDbMLeaderStyle
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::MLeaderStyle, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1021, DxfFileToken::ObjectMLeaderStyle, 499, 25,
                                             (ProxyFlags) 4095, false));

    //AcDbCellStyleMap
    doc->classes()->addOrUpdate(
            new DxfClass(DxfSubclassMarker::CellStyleMap, (short) (500 + doc->classes()->count()), ACadVersion::AC1021,
                         DxfFileToken::ObjectCellStyleMap, 499, 25,
                         ProxyFlags() | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog, false));

    //ExAcXREFPanelObject
    doc->classes()->addOrUpdate(new DxfClass(
            "ExAcXREFPanelObject", (short) (500 + doc->classes()->count()), (ACadVersion) 0, "EXACXREFPANELOBJECT", 499,
            0, ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog, false));

    //AcDbImpNonPersistentObjectsCollection
    doc->classes()->addOrUpdate(new DxfClass(
            "AcDbImpNonPersistentObjectsCollection", (short) (500 + doc->classes()->count()), (ACadVersion) 0,
            "NPOCOLLECTION", 499, 0,
            ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog,
            false));

    //AcDbLayerIndex
    doc->classes()->addOrUpdate(new DxfClass("AcDbLayerIndex", (short) (500 + doc->classes()->count()), (ACadVersion) 0,
                                             "LAYER_INDEX", 499, 0, ProxyFlag::None, false));

    //AcDbSpatialIndex
    doc->classes()->addOrUpdate(new DxfClass("AcDbSpatialIndex", (short) (500 + doc->classes()->count()),
                                             (ACadVersion) 0, "SPATIAL_INDEX", 499, 0, ProxyFlag::None, false));

    //AcDbIdBuffer
    doc->classes()->addOrUpdate(new DxfClass("AcDbIdBuffer", (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1014, "IDBUFFER", 499, 0, ProxyFlag::R13FormatProxy,
                                             false));

    //AcDbSectionViewStyle
    doc->classes()->addOrUpdate(new DxfClass(
            "AcDbSectionViewStyle", (short) (500 + doc->classes()->count()), (ACadVersion) 0, "ACDBSECTIONVIEWSTYLE",
            499, 0, ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog, false));

    //AcDbDetailViewStyle
    doc->classes()->addOrUpdate(new DxfClass(
            "AcDbDetailViewStyle", (short) (500 + doc->classes()->count()), (ACadVersion) 0, "ACDBDETAILVIEWSTYLE", 499,
            0, ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog, false));

    //AcDbSubDMesh
    doc->classes()->addOrUpdate(new DxfClass("AcDbSubDMesh", (short) (500 + doc->classes()->count()), (ACadVersion) 0,
                                             "MESH", 498, 0, ProxyFlag::None, false));

    //AcDbSortentsTable
    doc->classes()->addOrUpdate(new DxfClass("AcDbSortentsTable", (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1014, "SORTENTSTABLE", 499, 0, ProxyFlag::None, false));

    //AcDbTextObjectContextData
    doc->classes()->addOrUpdate(new DxfClass("AcDbTextObjectContextData", (short) (500 + doc->classes()->count()),
                                             (ACadVersion) 0, "ACDB_TEXTOBJECTCONTEXTDATA_CLASS", 499, 0,
                                             ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed |
                                                     ProxyFlag::DisablesProxyWarningDialog,
                                             false));

    //AcDbWipeout
    doc->classes()->addOrUpdate(new DxfClass(
            "WipeOut", "AcDbWipeout", (short) (500 + doc->classes()->count()), ACadVersion::AC1015, "WIPEOUT", 498, 0,
            ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::TransformAllowed | ProxyFlag::ColorChangeAllowed |
                    ProxyFlag::LayerChangeAllowed | ProxyFlag::LinetypeChangeAllowed |
                    ProxyFlag::LinetypeScaleChangeAllowed | ProxyFlag::VisibilityChangeAllowed |
                    ProxyFlag::R13FormatProxy,
            false));

    //AcDbWipeoutVariables
    doc->classes()->addOrUpdate(new DxfClass("WipeOut", "AcDbWipeoutVariables", (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1015, "WIPEOUTVARIABLES", 499, 0, ProxyFlag::R13FormatProxy,
                                             false));

    //AcDbDimAssoc
    doc->classes()->addOrUpdate(new DxfClass("AcDbDimAssoc", "AcDbDimAssoc", (short) (500 + doc->classes()->count()),
                                             (ACadVersion) 0, "DIMASSOC", 499, 0, ProxyFlag::None, false));

    //AcDbTable
    doc->classes()->addOrUpdate(
            new DxfClass("AcDbTable", (short) (500 + doc->classes()->count()), ACadVersion::AC1018, "ACAD_TABLE", 498,
                         0, ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog, false));

    //AcDbTableContent
    doc->classes()->addOrUpdate(new DxfClass(
            "AcDbTableContent", (short) (500 + doc->classes()->count()), ACadVersion::AC1018, "TABLECONTENT", 499, 21,
            ProxyFlags() | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog, false));

    //AcDbTableGeometry
    doc->classes()->addOrUpdate(new DxfClass(
            "AcDbTableGeometry", (short) (500 + doc->classes()->count()), (ACadVersion) 0, "TABLEGEOMETRY", 499, 0,
            ProxyFlags() | ProxyFlag::CloningAllowed | ProxyFlag::DisablesProxyWarningDialog, false));

    //AcDbRasterImage
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::RasterImage, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1014, DxfFileToken::EntityImage, 498, 0,
                                             ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::TransformAllowed |
                                                     ProxyFlag::ColorChangeAllowed | ProxyFlag::LayerChangeAllowed |
                                                     ProxyFlag::LinetypeChangeAllowed |
                                                     ProxyFlag::LinetypeScaleChangeAllowed |
                                                     ProxyFlag::VisibilityChangeAllowed | ProxyFlag::R13FormatProxy,
                                             false));

    //AcDbRasterImageDef
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::RasterImageDef, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1014, DxfFileToken::ObjectImageDefinition, 499, 0,
                                             ProxyFlag::R13FormatProxy, false));

    //AcDbColor
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::DbColor, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1015, DxfFileToken::ObjectDBColor, 499, 14, ProxyFlag::None,
                                             false));

	//AcDbGeoData
    doc->classes()->addOrUpdate(new DxfClass(DxfSubclassMarker::GeoData, (short) (500 + doc->classes()->count()),
                                             ACadVersion::AC1021, DxfFileToken::ObjectGeoData, 499, 45,
                                             (ProxyFlags) 4095, false));

	//AcDbMLeader
    doc->classes()->addOrUpdate(
            new DxfClass(DxfSubclassMarker::MultiLeader, (short) (500 + doc->classes()->count()), ACadVersion::MC0_0,
                         DxfFileToken::EntityMultiLeader, 499, 0,
                         ProxyFlags() | ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog, false));
};

void DxfClassCollection::add(DxfClass *cls)
{
    if (!cls)
        return;
    _entries.insert({cls->dxfName(), cls});
}

void DxfClassCollection::addOrUpdate(DxfClass *item)
{
    assert(item);
    auto it = _entries.find(item->dxfName());
    if (it != _entries.end())
    {
        it->second->setInstanceCount(item->instanceCount());
    }
    else
    {
        _entries.insert({item->dxfName(), item});
    }
}

DxfClass *DxfClassCollection::getByName(const std::string &name) const
{
    auto it = _entries.find(name);
    if (it != _entries.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

size_t DxfClassCollection::count() const
{
    return _entries.size();
}

void DxfClassCollection::clear()
{
    _entries.clear();
}

bool DxfClassCollection::contains(const std::string &name) const
{
    auto it = _entries.find(name);
    return (it == _entries.end()) ? false : true;
}

std::map<std::string, DxfClass *>::const_iterator DxfClassCollection::begin() const
{
    return _entries.begin();
}

std::map<std::string, DxfClass *>::const_iterator DxfClassCollection::end() const
{
    return _entries.end();
}

}// namespace dwg
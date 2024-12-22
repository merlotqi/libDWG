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

#ifndef LIBDWG_DXFCLASS_H
#define LIBDWG_DXFCLASS_H

#include <dwg/utils/Flags.h>
#include <vector>

namespace dwg {

enum ProxyFlag : unsigned short
{
    /// None.
    None = 0,
    /// Erase allowed.
    EraseAllowed = 1,
    /// Transform allowed.
    TransformAllowed = 2,
    /// Clor change allowed.
    ColorChangeAllowed = 4,
    /// Layer change allowed.
    LayerChangeAllowed = 8,
    /// Line type change allowed.
    LinetypeChangeAllowed = 16,
    /// Line type scale change allowed.
    LinetypeScaleChangeAllowed = 32,
    /// Visibility change allowed.
    VisibilityChangeAllowed = 64,
    /// Cloning allowed.
    CloningAllowed = 128,
    /// Line weight change allowed.
    LineweightChangeAllowed = 256,
    /// Plot Style Name change allowed.
    PlotStyleNameChangeAllowed = 512,
    /// All operations except cloning allowed.
    AllOperationsExceptCloningAllowed = 895,
    /// All operations allowed.
    AllOperationsAllowed = 1023,
    /// Disables proxy warning dialog.
    DisablesProxyWarningDialog = 1024,
    /// R13 format proxy.
    R13FormatProxy = 32768,
};
DECLARE_FLAGS(ProxyFlags, ProxyFlag)

class DxfClass
{
public:
    std::string DxfName;
    std::string CppClassName;
    std::string ApplicationName = "ObjectDBX Classes";
    ProxyFlags proxyFlags;
    int InstanceCount;
    bool WasZombie;
    bool IsAnEntity;
    short ClassNumber;
    short ItemClassId;
    ACadVersion DwgVersion;
    short MaintenanceVersion;


    DxfClass(const std::string &_cppClassName, short _classNumber,
             ACadVersion _version, const std::string &_dxfName,
             short _itemClassId, short _maintenanceVersion,
             ProxyFlags _proxyFlags, bool _wasZombie)
    {
        CppClassName = _cppClassName;
        ClassNumber = _classNumber;
        DwgVersion = _version;
        DxfName = _dxfName;
        ItemClassId = _itemClassId;
        MaintenanceVersion = _maintenanceVersion;
        proxyFlags = _proxyFlags;
        WasZombie = _wasZombie;
    }
};

class DxfClassCollection
{
    std::map<std::string, DxfClass> _entries;

public:
    static void UpdateDxfClasses(CadDocument *doc)
    {
        //AcDbDictionaryWithDefault
        doc->Classes.AddOrUpdate(DxfClass("AcDbDictionaryWithDefault",
                                          (short) (500 + doc->Classes.Count()),
                                          (ACadVersion) 22,
                                          "ACDBDICTIONARYWDFLT", 499, 42,
                                          ProxyFlag::R13FormatProxy, false));

        //AcDbPlaceHolder
        doc->Classes.AddOrUpdate(DxfClass("AcDbPlaceHolder",
                                          (short) (500 + doc->Classes.Count()),
                                          (ACadVersion) 0, "ACDBPLACEHOLDER",
                                          499, 0, ProxyFlag::None, false));

        //AcDbLayout
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbLayout", (short) (500 + doc->Classes.Count()),
                (ACadVersion) 0, "LAYOUT", 499, 0, ProxyFlag::None, false));

        //AcDbDictionaryVar
        doc->Classes.AddOrUpdate(DxfClass("AcDbDictionaryVar",
                                          (short) (500 + doc->Classes.Count()),
                                          (ACadVersion) 20, "DICTIONARYVAR",
                                          499, 0, ProxyFlag::None, false));

        //AcDbTableStyle
        doc->Classes.AddOrUpdate(DxfClass("AcDbTableStyle",
                                          (short) (500 + doc->Classes.Count()),
                                          ACadVersion::AC1018, "TABLESTYLE",
                                          499, 0, (ProxyFlags) 4095, false));

        //AcDbMaterial
        doc->Classes.AddOrUpdate(
                DxfClass("AcDbMaterial", (short) (500 + doc->Classes.Count()),
                        (ACadVersion) 0, "MATERIAL", 499, 0, 
                        ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed |
                                 ProxyFlag::DisablesProxyWarningDialog,
                         false));

        //AcDbVisualStyle
        doc->Classes.AddOrUpdate(DxfClass("AcDbVisualStyle",
                                          (short) (500 + doc->Classes.Count()),
                                          ACadVersion::AC1021, "VISUALSTYLE",
                                          499, 0, (ProxyFlags) 4095, false));

        //AcDbScale
        doc->Classes.AddOrUpdate(
                DxfClass("AcDbScale", (short) (500 + doc->Classes.Count()),
                         ACadVersion::AC1021, "SCALE", 499, 1,
                         ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed |
                                 ProxyFlag::DisablesProxyWarningDialog,
                         false));

        //AcDbMLeaderStyle
        doc->Classes.AddOrUpdate(DxfClass("AcDbMLeaderStyle",
                                          (short) (500 + doc->Classes.Count()),
                                          ACadVersion::AC1021, "MLEADERSTYLE",
                                          499, 25, (ProxyFlags) 4095, false));

        //AcDbCellStyleMap
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbCellStyleMap", (short) (500 + doc->Classes.Count()),
                ACadVersion::AC1021, "CELLSTYLEMAP", 499, 25,
                ProxyFlag::CloningAllowed |
                        ProxyFlag::DisablesProxyWarningDialog,
                false));

        //ExAcXREFPanelObject
        doc->Classes.AddOrUpdate(DxfClass(
                "ExAcXREFPanelObject", (short) (500 + doc->Classes.Count()), 0,
                "EXACXREFPANELOBJECT", 499, 0,
                ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog,
                false));

        //AcDbImpNonPersistentObjectsCollection
        doc->Classes.AddOrUpdate(
                DxfClass("AcDbImpNonPersistentObjectsCollection",
                         (short) (500 + doc->Classes.Count()), 0,
                         "NPOCOLLECTION", 499, 0,
                         ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed |
                                 ProxyFlag::DisablesProxyWarningDialog,
                         false));

        //AcDbLayerIndex
        doc->Classes.AddOrUpdate(
                DxfClass("AcDbLayerIndex", (short) (500 + doc->Classes.Count()),
                         0, "LAYER_INDEX", 499, 0, ProxyFlag::None, false));

        //AcDbSpatialIndex
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbSpatialIndex", (short) (500 + doc->Classes.Count()), 0,
                "SPATIAL_INDEX", 499, 0, ProxyFlag::None, false));

        //AcDbIdBuffer
        doc->Classes.AddOrUpdate(DxfClass("AcDbIdBuffer",
                                          (short) (500 + doc->Classes.Count()),
                                          ACadVersion::AC1014, "IDBUFFER", 499,
                                          0, ProxyFlag::R13FormatProxy, false));

        //AcDbSectionViewStyle
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbSectionViewStyle", (short) (500 + doc->Classes.Count()), 0,
                "ACDBSECTIONVIEWSTYLE", 499, 0,
                ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog,
                false));

        //AcDbDetailViewStyle
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbDetailViewStyle", (short) (500 + doc->Classes.Count()), 0,
                "ACDBDETAILVIEWSTYLE", 499, 0,
                ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog,
                false));

        //AcDbSubDMesh
        doc->Classes.AddOrUpdate(
                DxfClass("AcDbSubDMesh", (short) (500 + doc->Classes.Count()),
                         0, "MESH", 498, 0, ProxyFlag::None, false));

        //AcDbSortentsTable
        doc->Classes.AddOrUpdate(DxfClass("AcDbSortentsTable",
                                          (short) (500 + doc->Classes.Count()),
                                          ACadVersion::AC1014, "SORTENTSTABLE",
                                          499, 0, ProxyFlag::None, false));

        //AcDbTextObjectContextData
        doc->Classes.AddOrUpdate(
                DxfClass("AcDbTextObjectContextData",
                         (short) (500 + doc->Classes.Count()), 0,
                         "ACDB_TEXTOBJECTCONTEXTDATA_CLASS", 499, 0,
                         ProxyFlag::EraseAllowed | ProxyFlag::CloningAllowed |
                                 ProxyFlag::DisablesProxyWarningDialog,
                         false));

        //AcDbWipeout
        doc->Classes.AddOrUpdate(DxfClass(
                "WipeOut", "AcDbWipeout", (short) (500 + doc->Classes.Count()),
                ACadVersion::AC1015, "WIPEOUT", 498, 0,
                ProxyFlag::EraseAllowed | ProxyFlag::TransformAllowed |
                        ProxyFlag::ColorChangeAllowed |
                        ProxyFlag::LayerChangeAllowed |
                        ProxyFlag::LinetypeChangeAllowed |
                        ProxyFlag::LinetypeScaleChangeAllowed |
                        ProxyFlag::VisibilityChangeAllowed |
                        ProxyFlag::R13FormatProxy,
                false));

        //AcDbWipeoutVariables
        doc->Classes.AddOrUpdate(DxfClass(
                "WipeOut", "AcDbWipeoutVariables",
                (short) (500 + doc->Classes.Count()), ACadVersion::AC1015,
                "WIPEOUTVARIABLES", 499, 0, ProxyFlag::R13FormatProxy, false));

        //AcDbDimAssoc
        doc->Classes.AddOrUpdate(DxfClass("AcDbDimAssoc", "AcDbDimAssoc",
                                          (short) (500 + doc->Classes.Count()),
                                          0, "DIMASSOC", 499, 0,
                                          ProxyFlag::None, false));

        //AcDbTable
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbTable", (short) (500 + doc->Classes.Count()),
                ACadVersion::AC1018, "ACAD_TABLE", 498, 0,
                ProxyFlag::EraseAllowed | ProxyFlag::DisablesProxyWarningDialog,
                false));

        //AcDbTableContent
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbTableContent", (short) (500 + doc->Classes.Count()),
                ACadVersion::AC1018, "TABLECONTENT", 499, 21,
                ProxyFlag::CloningAllowed |
                        ProxyFlag::DisablesProxyWarningDialog,
                false));

        //AcDbTableGeometry
        doc->Classes.AddOrUpdate(DxfClass(
                "AcDbTableGeometry", (short) (500 + doc->Classes.Count()), 0,
                "TABLEGEOMETRY", 499, 0,
                ProxyFlag::CloningAllowed |
                        ProxyFlag::DisablesProxyWarningDialog,
                false));

        //AcDbRasterImage
        doc->Classes.AddOrUpdate(
                DxfClass(DxfSubclassMarker::RasterImage,
                         (short) (500 + doc->Classes.Count()),
                         ACadVersion::AC1014, DxfFileToken::EntityImage, 498, 0,
                         ProxyFlag::EraseAllowed | ProxyFlag::TransformAllowed |
                                 ProxyFlag::ColorChangeAllowed |
                                 ProxyFlag::LayerChangeAllowed |
                                 ProxyFlag::LinetypeChangeAllowed |
                                 ProxyFlag::LinetypeScaleChangeAllowed |
                                 ProxyFlag::VisibilityChangeAllowed |
                                 ProxyFlag::R13FormatProxy,
                         false));

        //AcDbRasterImageDef
        doc->Classes.AddOrUpdate(DxfClass(
                DxfSubclassMarker::RasterImageDef,
                (short) (500 + doc->Classes.Count()), ACadVersion::AC1014,
                DxfFileToken::ObjectImageDefinition, 499, 0,
                ProxyFlag::R13FormatProxy, false));

        //AcDbColor
        doc->Classes.AddOrUpdate(DxfClass(
                DxfSubclassMarker::DbColor, (short) (500 + doc->Classes.Count()),
                ACadVersion::AC1015, DxfFileToken::ObjectDBColor, 499, 14,
                ProxyFlag::None, false));
    };

    void AddOrUpdate(DxfClass item) {}

    size_t Count() const;
};

#endif// LIBDWG_DXFCLASS_H

}// namespace dwg
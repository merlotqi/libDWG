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

#include <dwg/ACadVersion.h>
#include <dwg/CadObjectCollection.h>
#include <dwg/IHandledCadObject.h>
#include <dwg/entities/Entity.h>
#include <dwg/exports.h>
#include <map>
#include <string>


namespace dwg {

class CadHeader;
class CadSummaryInfo;
class DxfClassCollection;
class TableCollection;
class AppIdsTable;
class BlockRecordsTable;
class DimensionStylesTable;
class LayersTable;
class LineTypesTable;
class TextStylesTable;
class UCSTable;
class ViewsTable;
class VPortsTable;
class ColorCollection;
class LayoutCollection;
class GroupCollection;
class ScaleCollection;
class MLineStyleCollection;
class ImageDefinitionCollection;
class MLeaderStyleCollection;
class CadDictionary;
class BlockRecord;
class CadObject;

class LIBDWG_API CadDocument : public IHandledCadObject
{
public:
    CadDocument();
    CadDocument(ACadVersion version);
    ~CadDocument();

    void createDefaults();
    void updateCollections(bool createDictionaries);

    unsigned long long handle() const override;

    CadHeader *header() const;
    void setHeader(CadHeader *);

    CadSummaryInfo *summaryInfo() const;
    void setSummaryInfo(CadSummaryInfo *);

    DxfClassCollection *classes() const;
    void setClasses(DxfClassCollection *);

    AppIdsTable *appIds() const;
    BlockRecordsTable *blockRecords() const;
    DimensionStylesTable *dimensionStyles() const;
    LayersTable *layers() const;
    LineTypesTable *lineTypes() const;
    TextStylesTable *textStyles() const;
    UCSTable *UCSs() const;
    ViewsTable *views() const;
    VPortsTable *vports() const;

    ColorCollection *colors() const;
    LayoutCollection *layouts() const;
    GroupCollection *groups() const;
    ScaleCollection *scales() const;
    MLineStyleCollection *mlineStyles() const;
    ImageDefinitionCollection *imageDefinitions() const;
    MLeaderStyleCollection *mleaderStyles() const;

    CadDictionary *rootDictionary() const;
    CadObjectCollection<Entity *> &entities();

    BlockRecord *modelSpace() const;
    BlockRecord *paperSpace() const;

    void registerCollection(TableCollection *);

protected:
    CadDocument(bool createDefaults);
    void setRootDictionary(CadDictionary *dic);

private:
    void setAppIds(AppIdsTable *);
    void setBlockRecords(BlockRecordsTable *);
    void setDimensionStyles(DimensionStylesTable *);
    void setLayers(LayersTable *);
    void setLineTypes(LineTypesTable *);
    void setTextStyles(TextStylesTable *);
    void setUCSs(UCSTable *);
    void setViews(ViewsTable *);
    void setVPorts(VPortsTable *);

    bool updateCollection(const std::string &dictName, bool createDictionary, CadDictionary **dictionary);
    void addCadObject(CadObject *cadObject);
    void removeCadObject(CadObject *cadObject);

private:
    CadHeader *_header = nullptr;
    CadSummaryInfo *_summaryInfo = nullptr;

    BlockRecordsTable *_blockRecords = nullptr;
    LayersTable *_layers = nullptr;
    DimensionStylesTable *_dimensionStyles = nullptr;
    TextStylesTable *_textStyles = nullptr;
    LineTypesTable *_lineTypes = nullptr;
    ViewsTable *_views = nullptr;
    UCSTable *_ucss = nullptr;
    VPortsTable *_vports = nullptr;
    AppIdsTable *_appIds = nullptr;

    CadDictionary *_rootDictionary = nullptr;

    ColorCollection *_colors = nullptr;
    LayoutCollection *_layouts = nullptr;
    GroupCollection *_groups = nullptr;
    ScaleCollection *_scales = nullptr;
    MLineStyleCollection *_mlineStyles = nullptr;
    ImageDefinitionCollection *_imageDefinitions = nullptr;
    MLeaderStyleCollection *_mleaderStyles = nullptr;
    DxfClassCollection *_classes = nullptr;

    std::map<unsigned long long, IHandledCadObject *> _cadObjects;
};

}// namespace dwg

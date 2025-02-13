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

#include <dwg/IHandledCadObject.h>

namespace dwg {

class CadHeader;
class CadSummaryInfo;
class DxfClassCollection;
class AppIdsTable;
class BlockRecordsTable;
class DimensionStylesTable;
class LayersTable;
class LineTypesTable;
class TextStylesTable;
class UCSTable;
class ViewsTable;
class VPortsTable;

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
    BlockRecordsTable* blockRecords() const;
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
    CadObjectCollection<Entity *> entities() const;

    BlockRecord *modelSpace() const;
    BlockRecord *paperSpace() const;

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
};

}// namespace dwg

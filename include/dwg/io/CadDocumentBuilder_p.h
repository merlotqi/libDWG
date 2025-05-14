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
#include <dwg/io/Notification.h>
#include <dwg/utils/Delegate.h>
#include <map>

namespace dwg {

class CadDocument;
class AppIdsTable;
class BlockRecordsTable;
class DimensionStylesTable;
class LayersTable;
class LineTypesTable;
class TextStylesTable;
class UCSTable;
class ViewsTable;
class VPortsTable;
class CadTemplate;
class ICadObjectTemplate;
class CadObject;
class ICadTableEntryTemplate;
class ICadTableTemplate;
class ICadDictionaryTemplate;

class CadDocumentBuilder
{
public:
    CadDocumentBuilder(ACadVersion version, CadDocument *document);
    virtual ~CadDocumentBuilder();

    ACadVersion version() const;
    CadDocument *documentToBuild() const;

    AppIdsTable *appIds() const;
    void setAppIds(AppIdsTable *tables);

    BlockRecordsTable *blockRecords() const;
    void setBlockRecords(BlockRecordsTable *tables);

    DimensionStylesTable *dimensionStyles() const;
    void setDimensionStyles(DimensionStylesTable *table);

    LayersTable *layers() const;
    void setLayers(LayersTable *table);

    LineTypesTable *lineTypesTable() const;
    void setLineTypesTable(LineTypesTable *);

    TextStylesTable *textStyles() const;
    void setTextStyles(TextStylesTable *);

    UCSTable *UCSs() const;
    void setUCSs(UCSTable *);

    ViewsTable *views() const;
    void setViews(ViewsTable *);

    VPortsTable *vports() const;
    void setVPorts(VPortsTable *);

    virtual bool keepUnknownEntities() const = 0;
    virtual bool keepUnknownNonGraphicalObjects() const = 0;

    unsigned long long initialHandSeed() const;
    void setInitialHandSeed(unsigned long long);

    virtual void buildDocument();
    void setAppTemplate(CadTemplate *tmpl);

    void setRegisterTables();
    void setBuildTables();

    Delegate<void(const std::string &, Notification)> OnNotification;


protected:
    std::map<unsigned long long, CadTemplate *> _cadObjectsTemplates;
    std::map<unsigned long long, ICadObjectTemplate *> _templatesMap;
    std::map<unsigned long long, CadObject *> _cadObjects;
    std::map<unsigned long long, ICadTableEntryTemplate *> _tableEntryTemplates;
    std::map<unsigned long long, ICadTableTemplate *> _tableTemplates;
    std::map<unsigned long long, ICadDictionaryTemplate *> _dictionaryTemplates;
};

}// namespace dwg
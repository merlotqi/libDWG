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

#include <map>
#include <cpl_ports.h>
#include <dwg/io/Notification.h>

namespace dwg {

class DG_CadDocumentBuilder
{
public:
    DG_CadDocumentBuilder(DG_ACadVersion version, DG_CadDocument *document);

    DG_ACadVersion Version() const;
    DG_CadDocument* DocumentToBuild() const;
    
    DG_AppIdsTable* AppIds() const;
    void AppIds(DG_AppIdsTable *tables);
    
    DG_BlockRecordsTable* BlockRecords() const;
    void BlockRecords(DG_BlockRecordsTable *tables);

    DG_DimensionStylesTable *DimensionStyles() const;
    void DimensionStyles(DG_DimensionStylesTable *table);

    DG_LayersTable *Layers() const;
    void Layers(DG_LayersTable *table);

    DG_LineTypesTable* LineTypesTable() const;
    void LineTypesTable(DG_LineTypesTable *);

    DG_TextStylesTable* TextStyles() const;
    void TextStyles(DG_TextStylesTable *);

    DG_UCSTable* UCSs() const;
    void UCSs(DG_UCSTable *);

    DG_ViewsTable *Views() const;
    void Views(DG_ViewsTable *);

    DG_VPortsTable* VPorts() const;
    void VPorts(DG_VPortsTable *);

    virtual bool KeepUnknownEntities() const = 0;

    virtual bool KeepUnknownNonGraphicalObjects() const = 0;

    unsigned long long InitialHandSeed() const;
    void InitialHandSeed(unsigned long long);

    virtual void BuildDocument();
    void AppTemplate(CadTemplate * tmpl);

    void RegisterTables();
    void BuildTables();

    CPL::Delegate<void(const std::string&, DG_Notification)> OnNotification;


protected:
    std::map<unsigned long long, CadTemplate*> _cadObjectsTemplates;
    std::map<unsigned long long, ICadObjectTemplate *> _templatesMap;
    std::map<unsigned long long, CadObject *> _cadObjects;
    std::map<unsigned long long, ICadTableEntryTemplate *> _tableEntryTemplates;
    std::map<unsigned long long, ICadTableTemplate *> _tableTemplates;
    std::map<unsigned long long, ICadDictionaryTemplate *> _dictionaryTemplates;
};

}
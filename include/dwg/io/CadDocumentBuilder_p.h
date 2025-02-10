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

#include <functional>
#include <dwg/io/Notification.h>
#include <map>


namespace dwg {

class CadDocumentBuilder
{
public:
    CadDocumentBuilder(ACadVersion version, CadDocument *document);

    ACadVersion Version() const;
    CadDocument *DocumentToBuild() const;

    AppIdsTable *AppIds() const;
    void AppIds(AppIdsTable *tables);

    BlockRecordsTable *BlockRecords() const;
    void BlockRecords(BlockRecordsTable *tables);

    DimensionStylesTable *DimensionStyles() const;
    void DimensionStyles(DimensionStylesTable *table);

    LayersTable *Layers() const;
    void Layers(LayersTable *table);

    LineTypesTable *LineTypesTable() const;
    void LineTypesTable(LineTypesTable *);

    TextStylesTable *TextStyles() const;
    void TextStyles(TextStylesTable *);

    UCSTable *UCSs() const;
    void UCSs(UCSTable *);

    ViewsTable *Views() const;
    void Views(ViewsTable *);

    VPortsTable *VPorts() const;
    void VPorts(VPortsTable *);

    virtual bool KeepUnknownEntities() const = 0;

    virtual bool KeepUnknownNonGraphicalObjects() const = 0;

    unsigned long long InitialHandSeed() const;
    void InitialHandSeed(unsigned long long);

    virtual void BuildDocument();
    void AppTemplate(CadTemplate *tmpl);

    void RegisterTables();
    void BuildTables();

    std::function<void(const std::string &, Notification)> OnNotification;


protected:
    std::map<unsigned long long, CadTemplate *> _cadObjectsTemplates;
    std::map<unsigned long long, ICadObjectTemplate *> _templatesMap;
    std::map<unsigned long long, CadObject *> _cadObjects;
    std::map<unsigned long long, ICadTableEntryTemplate *> _tableEntryTemplates;
    std::map<unsigned long long, ICadTableTemplate *> _tableTemplates;
    std::map<unsigned long long, ICadDictionaryTemplate *> _dictionaryTemplates;
};

}// namespace dwg
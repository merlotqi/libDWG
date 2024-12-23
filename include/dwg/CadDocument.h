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

#include <dwg/CadSummaryInfo.h>
#include <dwg/DxfClass.h>
#include <dwg/IHandledCadObject.h>
#include <dwg/header/CadHeader.h>
#include <dwg/tables/AppId.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/VPort.h>
#include <dwg/tables/View.h>

#include <dwg/entities/Entity.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/ObjectDictionaryCollection.h>

namespace dwg {

class CadDocument : IHandledCadObject
{
public:
    CadDocument(bool createDefault)
    {
        _cadObjects.insert({Handle(), this});
        if(createDefault)
        {
            CreateDefaults();
        }
    }

    unsigned long long Handle() const override;
    header::CadHeader Header;
    CadSummaryInfo SummaryInfo;
    DxfClassCollection Classes;

    tables::AppIdsTable AppIds;
    tables::BlockRecordsTable BlockRecords;
    tables::DimensionStylesTable DimensionStyles;
    tables::LayersTable Layers;
    tables::LineTypesTable LineTypes;
    tables::TextStylesTable TextStyles;
    tables::UCSTable UCSs;
    tables::ViewsTable Views;
    tables::VPortsTable VPorts;

    objects::ColorCollection Colors;
    objects::LayoutCollection Layouts;
    objects::GroupCollection Groups;
    objects::ScaleCollection Scales;
    objects::MLineStyleCollection MLineStyles;
    objects::ImageDefinitionCollection ImageDefinitions;
    objects::MLeaderStyleCollection MLeaderStyles;

    CadObjectCollection<entities::Entity *> Entities;
    tables::BlockRecord &ModelSpace();
    tables::BlockRecord &PaperSpace();

    objects::CadDictionary _rootDictionary;

    std::map<unsigned long long, IHandledCadObject *> _cadObjects;

    void CreateDefaults()
    {
        DxfClassCollection::UpdateDxfClasses(this);
    }
};

}// namespace dwg

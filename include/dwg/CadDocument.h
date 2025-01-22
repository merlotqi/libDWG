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
#include <dwg/entities/Entity.h>
#include <dwg/header/CadHeader.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/ObjectDictionaryCollection.h>
#include <dwg/tables/AppId.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/VPort.h>
#include <dwg/tables/View.h>


namespace dwg {

class CadDocument : public IHandledCadObject
{
public:
    CadDocument(bool createDefault);

    unsigned long long Handle() const override;
    CadHeader Header;
    CadSummaryInfo SummaryInfo;
    DxfClassCollection Classes;

    AppIdsTable AppIds;
    BlockRecordsTable BlockRecords;
    DimensionStylesTable DimensionStyles;
    LayersTable Layers;
    LineTypesTable LineTypes;
    TextStylesTable TextStyles;
    UCSTable UCSs;
    ViewsTable Views;
    VPortsTable VPorts;

    ColorCollection Colors;
    LayoutCollection Layouts;
    GroupCollection Groups;
    ScaleCollection Scales;
    MLineStyleCollection MLineStyles;
    ImageDefinitionCollection ImageDefinitions;
    MLeaderStyleCollection MLeaderStyles;

    CadObjectCollection<Entity *> Entities;
    BlockRecord &ModelSpace();
    BlockRecord &PaperSpace();

    CadDictionary _rootDictionary;

    std::map<unsigned long long, IHandledCadObject *> _cadObjects;

    void CreateDefaults();
};
CPL_SMARTER_PTR(CadDocument)

}// namespace dwg

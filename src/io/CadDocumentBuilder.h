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
#include <dwg/CadDocument.h>
#include <dwg/tables/AppId.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/View.h>
#include <dwg/tables/VPort.h>

namespace dwg {
namespace io {


class CadDocumentBuilder
{
public:
    ACadVersion Version;
    CadDocument *DocumentToBuild;
    AppIdsTable AppIds;
    BlockRecordsTable BlockRecords;
    DimensionStylesTable DimensionStyles;
    LayersTable Layers;
    LineTypesTable LineTypesTable;
    TextStylesTable TextStyles;
    UCSTable UCSs;
    ViewsTable Views;
    VPortsTable VPorts;

    bool KeepUnknownEntities;

    bool KeepUnknownNonGraphicalObjects;

    unsigned long long InitialHandSeed;

    std::map<unsigned long long, CadTemplate> cadObjectsTemplates;

    std::map<unsigned long long, ICadObjectTemplate> templatesMap;

    std::map<unsigned long long, CadObject> cadObjects;

    std::map<unsigned long long, ICadTableEntryTemplate> tableEntryTemplates;

    std::map<unsigned long long, ICadTableTemplate> tableTemplates;

    std::map<unsigned long long, ICadDictionaryTemplate> dictionaryTemplates;
};

}// namespace io
}// namespace dwg
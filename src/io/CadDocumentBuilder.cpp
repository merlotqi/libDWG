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

#include <dwg/io/CadDocumentBuilder_p.h>

namespace dwg {

CadDocumentBuilder::CadDocumentBuilder(ACadVersion version, CadDocument *document) {}

CadDocumentBuilder::~CadDocumentBuilder() {}

ACadVersion CadDocumentBuilder::version() const
{
    return ACadVersion::Unknown;
}

CadDocument *CadDocumentBuilder::documentToBuild() const
{
    return nullptr;
}

AppIdsTable *CadDocumentBuilder::appIds() const
{
    return nullptr;
}

void CadDocumentBuilder::setAppIds(AppIdsTable *tables) {}

BlockRecordsTable *CadDocumentBuilder::blockRecords() const
{
    return nullptr;
}

void CadDocumentBuilder::setBlockRecords(BlockRecordsTable *tables) {}

DimensionStylesTable *CadDocumentBuilder::dimensionStyles() const
{
    return nullptr;
}

void CadDocumentBuilder::setDimensionStyles(DimensionStylesTable *table) {}

LayersTable *CadDocumentBuilder::layers() const
{
    return nullptr;
}

void CadDocumentBuilder::setLayers(LayersTable *table) {}

LineTypesTable *CadDocumentBuilder::lineTypesTable() const
{
    return nullptr;
}

void CadDocumentBuilder::setLineTypesTable(LineTypesTable *) {}

TextStylesTable *CadDocumentBuilder::textStyles() const
{
    return nullptr;
}

void CadDocumentBuilder::setTextStyles(TextStylesTable *) {}

UCSTable *CadDocumentBuilder::UCSs() const
{
    return nullptr;
}

void CadDocumentBuilder::setUCSs(UCSTable *) {}

ViewsTable *CadDocumentBuilder::views() const
{
    return nullptr;
}

void CadDocumentBuilder::setViews(ViewsTable *) {}

VPortsTable *CadDocumentBuilder::vports() const
{
    return nullptr;
}

void CadDocumentBuilder::setVPorts(VPortsTable *) {}

unsigned long long CadDocumentBuilder::initialHandSeed() const
{
    return 0ULL;
}

void CadDocumentBuilder::setInitialHandSeed(unsigned long long) {}

void CadDocumentBuilder::buildDocument() {}

void CadDocumentBuilder::setAppTemplate(CadTemplate *tmpl) {}

void CadDocumentBuilder::setRegisterTables() {}

void CadDocumentBuilder::setBuildTables() {}

}// namespace dwg
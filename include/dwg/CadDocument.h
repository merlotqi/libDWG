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

#include <dwg/CadHeader.h>
#include <dwg/CadSummaryInfo.h>
#include <dwg/IHandledCadObject.h>


namespace dwg {

class CadDocument : IHandledCadObject
{
public:
    unsigned long handle() const override;

    CadHeader getHeader() const;

    void setHeader(const CadHeader &value);

    CadSummaryInfo getSummaryInfo() const;

    void setSummaryInfo(const CadSummaryInfo &value);

    DxfCalssCollection getClasses() const;

    void setClasses(const DxfCalssCollection &value);

    AppIdsTable getAppIds() const;

    void setAppIds(const AppIdsTable &value);

    BlockRecordsTable getBlockRecords() const;

    void setBlockRecords(const BlockRecordsTable &value);

    DimensionStylesTable getDimensionStyles() const;

    void setDimensionStyles(const DimensionStylesTable &value);

    LayersTable getLayers() const;

    void setLayers(const LayersTable &value);

    LineTypesTable getLineTypes() const;

    void setLineTypes(const LineTypesTable &value);

    TextStylesTable getTextStyles() const;

    void setTextStyles(const TextStylesTable &value);

    UCSTable getUCSs() const;

    void setUCSs(const UCSTable &value);

    ViewsTable getViews() const;

    void setViews(const ViewsTable &value);

    VPortsTable getVPorts() const;

    void setVPorts(const VPortsTable &value);

    LayoutCollection getLayouts() const;

    void setLayouts(const LayoutCollection &value);

    GroupCollection getGroups() const;

    void setGroups(const GroupCollection &value);
};

}// namespace dwg

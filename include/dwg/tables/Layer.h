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

#include <dwg/Color.h>
#include <dwg/LineWeightType.h>
#include <dwg/tables/LayerFlags.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TableEntry.h>

namespace dwg {

class LIBDWG_API DG_Layer : public DG_TableEntry
{
public:
    DG_Layer();

    DG_Layer(const char *name);

    static constexpr auto DefaultName = "0";
    static CPL::SmarterPtr<DG_Layer> Default();

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;

    DG_LayerFlags Flags() const;
    void Flags(DG_LayerFlags);

    DG_Color Color() const;
    void Color(const DG_Color &);

    DG_LineTypePtr LineType() const;
    void LineType(DG_LineType *);

    bool PlotFlag() const;
    void PlotFlag(bool);

    DG_LineweightType LineWeight() const;
    void LineWeight(LineweightType);
    
    unsigned long long PlotStyleName() const;
    void PlotStyleName(unsigned long long);

    DG_MaterialPtr Material() const;
    void Material(DG_Material *);

    bool IsOn() const;
    void IsOn(bool);
};
CPL_SMARTER_PTR(DG_Layer)

class LIBDWG_API DG_LayersTable : public DG_Table
{
public:
    DG_LayersTable() = default;
    CPL::String ObjectName() const override;
    DG_ObjectType ObjectType() const override;

protected:
    std::vector<CPL::String> defaultEntries() const override;
};

}// namespace dwg
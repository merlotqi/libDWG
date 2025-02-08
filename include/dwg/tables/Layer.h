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
#include <dwg/tables/TableEntry.h>

namespace dwg {

class Material;
class LineType;

class LIBDWG_API Layer : public TableEntry
{
public:
    Layer();

    Layer(const std::string &name);

    static constexpr auto DefaultName = "0";
    static Layer *Default();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    LayerFlags flags() const;
    void setFlags(LayerFlags);

    Color color() const;
    void setColor(const Color &);

    LineType *lineType() const;
    void setLineType(LineType *);

    bool plotFlag() const;
    void setPlotFlag(bool);

    LineweightType lineWeight() const;
    void setLineWeight(LineweightType);

    unsigned long long plotStyleName() const;
    void setPlotStyleName(unsigned long long);

    Material *material() const;
    void setMaterial(Material *);

    bool isOn() const;
    void setIsOn(bool);
};

class LIBDWG_API LayersTable : public Table
{
public:
    LayersTable() = default;
    std::string objectName() const override;
    ObjectType objectType() const override;

protected:
    std::vector<std::string> defaultEntries() const override;
};

}// namespace dwg
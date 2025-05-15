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

#include <dwg/entities/Dimension.h>
#include <dwg/io/template/CadEntityTemplate_p.h>

namespace dwg {

class DimensionPlaceHolder : public Dimension
{
public:
    DimensionPlaceHolder();
    ObjectType objectType() const override;
    double measurement() const override;
    std::string objectName() const override;
};

class CadDimensionTemplate : public CadEntityTemplate
{
public:
    CadDimensionTemplate();
    CadDimensionTemplate(Dimension *dimension);
    void build(CadDocumentBuilder *builder) override;

    std::optional<unsigned long long> styleHandle() const;
    void setStyleHandle(unsigned long long);

    std::optional<unsigned long long> blockHandle() const;
    void setBlockHandle(unsigned long long);

    std::string blockName() const;
    void setBlockName(const std::string &);

    std::string styleName() const;
    void setStyleName(const std::string &);

    void setDimensionFlags(DimensionType flags);
    void setDimensionObject(Dimension *dimension);

private:
    std::optional<unsigned long long> _styleHandle;
    std::optional<unsigned long long> _blockHandle;
    std::string _blockName;
    std::string _styleName;
};

}// namespace dwg
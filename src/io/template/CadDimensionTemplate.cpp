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

#include <dwg/DxfFileToken_p.h>
#include <dwg/io/template/CadDimensionTemplate_p.h>

namespace dwg {

/* -------------------------- DimensionPlaceHolder -------------------------- */
DimensionPlaceHolder::DimensionPlaceHolder() : Dimension(DimensionType::Linear) {}

ObjectType DimensionPlaceHolder::objectType() const
{
    return ObjectType::INVALID;
}
double DimensionPlaceHolder::measurement() const
{
    return 0.0;
}

std::string DimensionPlaceHolder::objectName() const
{
    return DxfFileToken::EntityDimension;
}

/* -------------------------- CadDimensionTemplate -------------------------- */
CadDimensionTemplate::CadDimensionTemplate() : CadEntityTemplate(new DimensionPlaceHolder()) {}

CadDimensionTemplate::CadDimensionTemplate(Dimension *dimension) : CadEntityTemplate(dimension) {}

void CadDimensionTemplate::build(CadDocumentBuilder *builder) {}

std::optional<unsigned long long> CadDimensionTemplate::styleHandle() const
{
    return _styleHandle;
}

void CadDimensionTemplate::setStyleHandle(unsigned long long value)
{
    _styleHandle = value;
}

std::optional<unsigned long long> CadDimensionTemplate::blockHandle() const
{
    return _blockHandle;
}

void CadDimensionTemplate::setBlockHandle(unsigned long long value)
{
    _blockHandle = value;
}

std::string CadDimensionTemplate::blockName() const
{
    return _blockName;
}

void CadDimensionTemplate::setBlockName(const std::string &value)
{
    _blockName = value;
}

std::string CadDimensionTemplate::styleName() const
{
    return _styleName;
}

void CadDimensionTemplate::setStyleName(const std::string &value)
{
    _styleName = value;
}

void CadDimensionTemplate::setDimensionFlags(DimensionType flags) {}

void CadDimensionTemplate::setDimensionObject(Dimension *dimension) {}

}// namespace dwg
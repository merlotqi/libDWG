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

#include <dwg/io/template/CadDimensionStyleTemplate_p.h>

namespace dwg {

CadDimensionStyleTemplate::CadDimensionStyleTemplate() : CadTemplateT<DimensionStyle *>(new DimensionStyle()) {}

CadDimensionStyleTemplate::CadDimensionStyleTemplate(DimensionStyle *dimStyle)
    : CadTemplateT<DimensionStyle *>(dimStyle)
{
}

void CadDimensionStyleTemplate::build(CadDocumentBuilder *builder) {}

std::string CadDimensionStyleTemplate::textStyle_Name() const
{
    return _textStyle_Name;
}

void CadDimensionStyleTemplate::setTextStyle_Name(const std::string &value)
{
    _textStyle_Name = value;
}

std::string CadDimensionStyleTemplate::DIMBL_Name() const
{
    return _DIMBL_Name;
}

void CadDimensionStyleTemplate::setDIMBL_Name(const std::string &value)
{
    _DIMBL_Name = value;
}

std::string CadDimensionStyleTemplate::DIMBLK1_Name() const
{
    return _DIMBLK1_Name;
}

void CadDimensionStyleTemplate::setDIMBLK1_Name(const std::string &value)
{
    _DIMBLK1_Name = value;
}

std::string CadDimensionStyleTemplate::DIMBLK2_Name() const
{
    return _DIMBLK2_Name;
}

void CadDimensionStyleTemplate::setDIMBLK2_Name(const std::string &value)
{
    _DIMBLK2_Name = value;
}

std::optional<unsigned long long> CadDimensionStyleTemplate::TextStyleHandle() const
{
    return _TextStyleHandle;
}

void CadDimensionStyleTemplate::setTextStyleHandle(unsigned long long value)
{
    _TextStyleHandle = value;
}

std::optional<unsigned long long> CadDimensionStyleTemplate::DIMLDRBLK() const
{
    return _DIMLDRBLK;
}

void CadDimensionStyleTemplate::setDIMLDRBLK(unsigned long long value)
{
    _DIMLDRBLK = value;
}

std::optional<unsigned long long> CadDimensionStyleTemplate::DIMBLK() const
{
    return _DIMBLK;
}

void CadDimensionStyleTemplate::setDIMBLK(unsigned long long value)
{
    _DIMBLK = value;
}

std::optional<unsigned long long> CadDimensionStyleTemplate::DIMBLK1() const
{
    return _DIMBLK1;
}

void CadDimensionStyleTemplate::setDIMBLK1(unsigned long long value)
{
    _DIMBLK1 = value;
}

std::optional<unsigned long long> CadDimensionStyleTemplate::DIMBLK2() const
{
    return _DIMBLK2;
}

void CadDimensionStyleTemplate::setDIMBLK2(unsigned long long value)
{
    _DIMBLK2 = value;
}

unsigned long long CadDimensionStyleTemplate::Dimltype() const
{
    return _Dimltype;
}

void CadDimensionStyleTemplate::setDimltype(unsigned long long value)
{
    _Dimltype = value;
}

unsigned long long CadDimensionStyleTemplate::Dimltex1() const
{
    return _Dimltex1;
}

void CadDimensionStyleTemplate::setDimltex1(unsigned long long value)
{
    _Dimltex1 = value;
}

unsigned long long CadDimensionStyleTemplate::Dimltex2() const
{
    return _Dimltex2;
}

void CadDimensionStyleTemplate::setDimltex2(unsigned long long value)
{
    _Dimltex2 = value;
}

}// namespace dwg
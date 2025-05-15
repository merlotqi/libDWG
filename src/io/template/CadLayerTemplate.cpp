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

#include <dwg/io/template/CadLayerTemplate_p.h>

namespace dwg {

CadLayerTemplate::CadLayerTemplate() : CadTemplateT<Layer *>(new Layer()) {}

CadLayerTemplate::CadLayerTemplate(Layer *l) : CadTemplateT<Layer *>(l) {}

void CadLayerTemplate::build(CadDocumentBuilder *builder) {}

unsigned long long CadLayerTemplate::layerControlHandle() const
{
    return _layerControlHandle;
}

void CadLayerTemplate::setLayerControlHandle(unsigned long long value)
{
    _layerControlHandle = value;
}

unsigned long long CadLayerTemplate::plotStyleHandle() const
{
    return _plotStyleHandle;
}

void CadLayerTemplate::setPlotStyleHandle(unsigned long long value)
{
    _layerControlHandle = value;
}

unsigned long long CadLayerTemplate::materialHandle() const
{
    return _materialHandle;
}

void CadLayerTemplate::setMaterialHandle(unsigned long long value)
{
    _materialHandle = value;
}

std::optional<unsigned long long> CadLayerTemplate::lineTypeHandle() const
{
    return _lineTypeHandle;
}

void CadLayerTemplate::setLineTypeHandle(unsigned long long value)
{
    _lineTypeHandle = value;
}

std::string CadLayerTemplate::lineTypeName() const
{
    return _lineTypeName;
}

void CadLayerTemplate::setLineTypeName(const std::string &value)
{
    _lineTypeName = value;
}

std::string CadLayerTemplate::trueColorName() const
{
    return _trueColorName;
}

void CadLayerTemplate::setTrueColorName(const std::string &value)
{
    _trueColorName = value;
}

}// namespace dwg
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

#include <dwg/io/template/CadLayoutTemplate_p.h>

namespace dwg {

CadLayoutTemplate::CadLayoutTemplate() : CadTemplateT<Layout *>(new Layout()) {}

CadLayoutTemplate::CadLayoutTemplate(Layout *l) : CadTemplateT<Layout *>(l) {}

void CadLayoutTemplate::build(CadDocumentBuilder *builder) {}

std::optional<unsigned long long> CadLayoutTemplate::paperSpaceBlockHandle() const
{
    return _paperSpaceBlockHandle;
}

void CadLayoutTemplate::setPaperSpaceBlockHandle(unsigned long long value)
{
    _paperSpaceBlockHandle = value;
}

std::optional<unsigned long long> CadLayoutTemplate::activeViewportHandle() const
{
    return _activeViewportHandle;
}

void CadLayoutTemplate::setActiveViewportHandle(unsigned long long value)
{
    _activeViewportHandle = value;
}

std::optional<unsigned long long> CadLayoutTemplate::baseUcsHandle() const
{
    return _baseUcsHandle;
}

void CadLayoutTemplate::setBaseUcsHandle(unsigned long long value)
{
    _baseUcsHandle = value;
}

std::optional<unsigned long long> CadLayoutTemplate::namesUcsHandle() const
{
    return _namesUcsHandle;
}

void CadLayoutTemplate::setNamesUcsHandle(unsigned long long value)
{
    _namesUcsHandle = value;
}

std::optional<unsigned long long> CadLayoutTemplate::lasActiveViewportHandle() const
{
    return _lasActiveViewportHandle;
}

void CadLayoutTemplate::setLasActiveViewportHandle(unsigned long long value)
{
    _lasActiveViewportHandle = value;
}

std::vector<unsigned long long> CadLayoutTemplate::viewportHandles() const
{
    return _viewportHandles;
}

std::vector<unsigned long long> &CadLayoutTemplate::viewportHandles()
{
    return _viewportHandles;
}

}// namespace dwg
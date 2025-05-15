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

#include <dwg/io/template/CadPolyLineTemplate_p.h>

namespace dwg {

/* --------------------------- PolyLinePlaceholder -------------------------- */
PolyLinePlaceholder::PolyLinePlaceholder() {}

ObjectType PolyLinePlaceholder::objectType() const
{
    return ObjectType::INVALID;
}


/* --------------------------- CadPolyLineTemplate -------------------------- */
CadPolyLineTemplate::CadPolyLineTemplate() : CadEntityTemplate(new PolyLinePlaceholder()) {}

CadPolyLineTemplate::CadPolyLineTemplate(Polyline *polyline) : CadEntityTemplate(polyline) {}

void CadPolyLineTemplate::build(CadDocumentBuilder *builder) {}

std::optional<unsigned long long> CadPolyLineTemplate::firstVertexHandle() const
{
    return _firstVertexHandle;
}

void CadPolyLineTemplate::setFirstVertexHandle(unsigned long long value)
{
    _firstVertexHandle = value;
}

std::optional<unsigned long long> CadPolyLineTemplate::lastVertexHandle() const
{
    return _lastVertexHandle;
}

void CadPolyLineTemplate::setLastVertexHandle(unsigned long long value)
{
    _lastVertexHandle = value;
}

std::optional<unsigned long long> CadPolyLineTemplate::seqendHandle() const
{
    return _seqendHandle;
}

void CadPolyLineTemplate::setSeqendHandle(unsigned long long value)
{
    _seqendHandle = value;
}

std::vector<unsigned long long> CadPolyLineTemplate::vertexHandles() const
{
    return _vertexHandles;
}

std::vector<unsigned long long> &CadPolyLineTemplate::vertexHandles()
{
    return _vertexHandles;
}

Polyline *CadPolyLineTemplate::polyline() const
{
    return nullptr;
}

void CadPolyLineTemplate::SetPolyLineObject(Polyline *polyline) {}

void CadPolyLineTemplate::buildPolyfaceMesh(PolyfaceMesh *polyfaceMesh, CadDocumentBuilder *builder) {}

}// namespace dwg
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

#include <dwg/entities/PolyfaceMesh.h>
#include <dwg/io/template/CadPolyfaceMeshTemplate_p.h>


namespace dwg {

CadPolyfaceMeshTemplate::CadPolyfaceMeshTemplate(PolyfaceMesh *entity) : CadEntityTemplate(entity) {}

void CadPolyfaceMeshTemplate::build(CadDocumentBuilder *builder) {}

std::optional<unsigned long long> CadPolyfaceMeshTemplate::firstVerticeHandle() const
{
    return _firstVerticeHandle;
}

void CadPolyfaceMeshTemplate::setFirstVerticeHandle(unsigned long long value)
{
    _firstVerticeHandle = value;
}

std::optional<unsigned long long> CadPolyfaceMeshTemplate::lastVerticeHandle() const
{
    return _lastVerticeHandle;
}

void CadPolyfaceMeshTemplate::setLastVerticeHandle(unsigned long long value)
{
    _lastVerticeHandle = value;
}

std::optional<unsigned long long> CadPolyfaceMeshTemplate::seqendHandle() const
{
    return _seqendHandle;
}

void CadPolyfaceMeshTemplate::setSeqendHandle(unsigned long long value)
{
    _seqendHandle = value;
}

std::vector<unsigned long long> CadPolyfaceMeshTemplate::verticesHandles() const
{
    return _verticesHandles;
}

std::vector<unsigned long long> &CadPolyfaceMeshTemplate::verticesHandles()
{
    return _verticesHandles;
}

void CadPolyfaceMeshTemplate::addItemToPolyface(CadObject *item, CadDocumentBuilder *builder) {}

}// namespace dwg
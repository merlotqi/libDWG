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

#include <dwg/io/template/CadMLineTemplate_p.h>

namespace dwg {

CadMLineTemplate::CadMLineTemplate() : CadEntityTemplate(new MLine()) {}

CadMLineTemplate::CadMLineTemplate(MLine *mline) : CadEntityTemplate(mline) {}

CadMLineTemplate::~CadMLineTemplate() {}

std::optional<unsigned long long> CadMLineTemplate::MLineStylehandle() const
{
    return _mlineStyleHandle;
}

void CadMLineTemplate::setMLineStylehandle(unsigned long long handle)
{
    _mlineStyleHandle = handle;
}

const std::string &CadMLineTemplate::MLineStyleName() const
{
    return _mlineStyleName;
}

void CadMLineTemplate::setMLineStyleName(const std::string &name)
{
    _mlineStyleName = name;
}

std::optional<int> CadMLineTemplate::NVertex() const
{
    return _nVertex;
}

void CadMLineTemplate::setNVertex(int n)
{
    _nVertex = n;
}

std::optional<int> CadMLineTemplate::NElements() const
{
    return _nElements;
}

void CadMLineTemplate::setNElements(int n)
{
    _nElements = n;
}

bool CadMLineTemplate::tryReadVertex(int dxfcode, double value)
{
    return false;
}

void CadMLineTemplate::build(CadDocumentBuilder *builder) {}

}// namespace dwg
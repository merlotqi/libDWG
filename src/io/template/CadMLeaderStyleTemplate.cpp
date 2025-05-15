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

#include <dwg/io/template/CadMLeaderStyleTemplate_p.h>

namespace dwg {

CadMLeaderStyleTemplate::CadMLeaderStyleTemplate() : CadTemplateT<MultiLeaderStyle *>(new MultiLeaderStyle()) {}

CadMLeaderStyleTemplate::CadMLeaderStyleTemplate(MultiLeaderStyle *style) : CadTemplateT<MultiLeaderStyle *>(style) {}

void CadMLeaderStyleTemplate::build(CadDocumentBuilder *builder) {}

unsigned long long CadMLeaderStyleTemplate::leaderLineTypeHandle() const
{
    return _leaderLineTypeHandle;
}

void CadMLeaderStyleTemplate::setLeaderLineTypeHandle(unsigned long long value)
{
    _leaderLineTypeHandle = value;
}

unsigned long long CadMLeaderStyleTemplate::arrowheadHandle() const
{
    return _arrowheadHandle;
}

void CadMLeaderStyleTemplate::setArrowheadHandle(unsigned long long value)
{
    _arrowheadHandle = value;
}

unsigned long long CadMLeaderStyleTemplate::mtextStyleHandle() const
{
    return _mtextStyleHandle;
}

void CadMLeaderStyleTemplate::setMTextStyleHandle(unsigned long long value)
{
    _mtextStyleHandle = value;
}

unsigned long long CadMLeaderStyleTemplate::blockContentHandle() const
{
    return _blockContentHandle;
}

void CadMLeaderStyleTemplate::setBlockContentHandle(unsigned long long value)
{
    _blockContentHandle = value;
}

}// namespace dwg
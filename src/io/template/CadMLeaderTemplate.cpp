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

#include <dwg/io/template/CadMLeaderTemplate_p.h>

namespace dwg {

CadMLeaderTemplate::CadMLeaderTemplate() : CadEntityTemplate(new MultiLeader()) {}

CadMLeaderTemplate::CadMLeaderTemplate(MultiLeader *entity) : CadEntityTemplate(entity) {}

CadMLeaderTemplate::~CadMLeaderTemplate() noexcept {}

void CadMLeaderTemplate::build(CadDocumentBuilder *builder) {}

unsigned long long CadMLeaderTemplate::leaderStyleHandle() const
{
    return _leaderStyleHandle;
}

void CadMLeaderTemplate::setLeaderStyleHandle(unsigned long long value)
{
    _leaderStyleHandle = value;
}

unsigned long long CadMLeaderTemplate::leaderLineTypeHandle() const
{
    return _leaderLineTypeHandle;
}

void CadMLeaderTemplate::setLeaderLineTypeHandle(unsigned long long value)
{
    _leaderLineTypeHandle = value;
}

unsigned long long CadMLeaderTemplate::mtextStyleHandle() const
{
    return _mtextStyleHandle;
}

void CadMLeaderTemplate::setMtextStyleHandle(unsigned long long value)
{
    _mtextStyleHandle = value;
}

unsigned long long CadMLeaderTemplate::blockContentHandle() const
{
    return _blockContentHandle;
}

void CadMLeaderTemplate::setBlockContentHandle(unsigned long long value)
{
    _blockContentHandle = value;
}

unsigned long long CadMLeaderTemplate::arrowheadHandle() const
{
    return _arrowheadHandle;
}

void CadMLeaderTemplate::setArrowheadHandle(unsigned long long value)
{
    _arrowheadHandle = value;
}

std::map<unsigned long long, bool> CadMLeaderTemplate::arrowheadHandles() const
{
    return _arrowheadHandles;
}

std::map<unsigned long long, bool> &CadMLeaderTemplate::arrowheadHandles()
{
    return _arrowheadHandles;
}

std::map<MultiLeader::BlockAttribute, unsigned long long> CadMLeaderTemplate::blockAttributeHandles() const
{
    return _blockAttributeHandles;
}

std::map<MultiLeader::BlockAttribute, unsigned long long> &CadMLeaderTemplate::blockAttributeHandles()
{
    return _blockAttributeHandles;
}

unsigned long long CadMLeaderTemplate::annotContextTextStyleHandle() const
{
    return _annotContextTextStyleHandle;
}

void CadMLeaderTemplate::setAnnotContextTextStyleHandle(unsigned long long value)
{
    _annotContextTextStyleHandle = value;
}

unsigned long long CadMLeaderTemplate::annotContextBlockRecordHandle() const
{
    return _annotContextBlockRecordHandle;
}

void CadMLeaderTemplate::setAnnotContextBlockRecordHandle(unsigned long long value)
{
    _annotContextBlockRecordHandle = value;
}

std::vector<CadMLeaderTemplate::LeaderLineSubTemplate> CadMLeaderTemplate::leaderLineSubTemplates() const
{
    return _leaderLineSubTemplates;
}

std::vector<CadMLeaderTemplate::LeaderLineSubTemplate> &CadMLeaderTemplate::leaderLineSubTemplates()
{
    return _leaderLineSubTemplates;
}

}// namespace dwg
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

#include <dwg/io/template/CadInsertTemplate_p.h>

namespace dwg {

CadInsertTemplate::CadInsertTemplate() : CadEntityTemplate(new Insert()) {}

CadInsertTemplate::CadInsertTemplate(Insert *insert) : CadEntityTemplate(insert) {}

void CadInsertTemplate::build(CadDocumentBuilder *builder) {}

bool CadInsertTemplate::hasAtts() const
{
    return _hasAtts;
}

void CadInsertTemplate::setHasAtts(bool value)
{
    _hasAtts = value;
}

int CadInsertTemplate::ownedObjectsCount() const
{
    return _ownedObjectsCount;
}

void CadInsertTemplate::setOwnedObjectsCount(int value)
{
    _ownedObjectsCount = value;
}

std::optional<unsigned long long> CadInsertTemplate::blockHeaderHandle() const
{
    return _blockHeaderHandle;
}

void CadInsertTemplate::setBlockHeaderHandle(unsigned long long value)
{
    _blockHeaderHandle = value;
}

std::string CadInsertTemplate::blockName() const
{
    return _blockName;
}

void CadInsertTemplate::setBlockName(const std::string &value)
{
    _blockName = value;
}

std::optional<unsigned long long> CadInsertTemplate::firstAttributeHandle() const
{
    return _firstAttributeHandle;
}

void CadInsertTemplate::setFirstAttributeHandle(unsigned long long value)
{
    _firstAttributeHandle = value;
}

std::optional<unsigned long long> CadInsertTemplate::endAttributeHandle() const
{
    return _endAttributeHandle;
}

void CadInsertTemplate::setEndAttributeHandle(unsigned long long value)
{
    _endAttributeHandle = value;
}

std::optional<unsigned long long> CadInsertTemplate::seqendHandle() const
{
    return _seqendHandle;
}

void CadInsertTemplate::setSeqendHandle(unsigned long long value)
{
    _seqendHandle = value;
}

std::vector<unsigned long long> CadInsertTemplate::attributesHandles() const
{
    return _attributesHandles;
}

std::vector<unsigned long long> &CadInsertTemplate::attributesHandles()
{
    return _attributesHandles;
}

void CadInsertTemplate::setAttributesHandles(const std::vector<unsigned long long> &value)
{
    _attributesHandles = value;
}

}// namespace dwg
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

#include <dwg/io/template/CadBlockRecordTemplate_p.h>

namespace dwg {

CadBlockRecordTemplate::CadBlockRecordTemplate() : CadTemplateT<BlockRecord *>(new BlockRecord()) {}

CadBlockRecordTemplate::CadBlockRecordTemplate(BlockRecord *block) : CadTemplateT<BlockRecord *>(block) {}

void CadBlockRecordTemplate::build(CadDocumentBuilder *builder) {}

void CadBlockRecordTemplate::setBlockToRecord(CadDocumentBuilder *builder) {}

std::optional<unsigned long long> CadBlockRecordTemplate::firstEntityHandle() const
{
    return _firstEntityHandle;
}

void CadBlockRecordTemplate::setFirstEntityHandle(unsigned long long value)
{
    _firstEntityHandle = value;
}

std::optional<unsigned long long> CadBlockRecordTemplate::lastEntityHandle() const
{
    return _lastEntityHandle;
}

void CadBlockRecordTemplate::setLastEntityHandle(unsigned long long value)
{
    _lastEntityHandle = value;
}

std::optional<unsigned long long> CadBlockRecordTemplate::beginBlockHandle() const
{
    return _beginBlockHandle;
}

void CadBlockRecordTemplate::setBeginBlockHandle(unsigned long long value)
{
    _beginBlockHandle = value;
}

std::optional<unsigned long long> CadBlockRecordTemplate::endBlockHandle() const
{
    return _endBlockHandle;
}

void CadBlockRecordTemplate::setEndBlockHandle(unsigned long long value)
{
    _endBlockHandle = value;
}

std::optional<unsigned long long> CadBlockRecordTemplate::layoutHandle() const
{
    return _layoutHandle;
}

void CadBlockRecordTemplate::setLayoutHandle(unsigned long long value)
{
    _layoutHandle = value;
}

std::vector<unsigned long long> CadBlockRecordTemplate::ownedObjectHandles() const
{
    return _ownedObjectHandles;
}

std::vector<unsigned long long> &CadBlockRecordTemplate::ownedObjectHandles()
{
    return _ownedObjectHandles;
}

std::vector<unsigned long long> CadBlockRecordTemplate::insertHandles() const
{
    return _insertHandles;
}

std::vector<unsigned long long> &CadBlockRecordTemplate::insertHandles()
{
    return _insertHandles;
}

std::string CadBlockRecordTemplate::layerName() const
{
    return _layerName;
}

void CadBlockRecordTemplate::setLayerName(const std::string &value)
{
    _layerName = value;
}

void CadBlockRecordTemplate::addEntity(CadDocumentBuilder *builder, Entity *entity) {}

}// namespace dwg
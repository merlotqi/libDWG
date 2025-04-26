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

#pragma once

#include <dwg/io/template/CadTemplate_p.h>
#include <dwg/tables/BlockRecord.h>

namespace dwg {

class Entity;
class CadBlockRecordTemplate : public CadTemplateT<BlockRecord *>
{
public:
    CadBlockRecordTemplate();
    CadBlockRecordTemplate(BlockRecord *block);
    void build(CadDocumentBuilder *builder);
    void setBlockToRecord(CadDocumentBuilder *builder);

    std::optional<unsigned long long> firstEntityHandle() const;
    void setFirstEntityHandle(unsigned long long);

    std::optional<unsigned long long> lastEntityHandle() const;
    void setLastEntityHandle(unsigned long long);

    std::optional<unsigned long long> beginBlockHandle() const;
    void setBeginBlockHandle(unsigned long long);

    std::optional<unsigned long long> endBlockHandle() const;
    void setEndBlockHandle(unsigned long long);

    std::optional<unsigned long long> layoutHandle() const;
    void setLayoutHandle(unsigned long long);

    std::vector<unsigned long long> ownedObjectHandles() const;
    std::vector<unsigned long long> &ownedObjectHandles();

    std::vector<unsigned long long> insertHandles() const;
    std::vector<unsigned long long> &insertHandles();

    std::string layerName() const;
    void setLayerName(const std::string &);

private:
    void addEntity(CadDocumentBuilder *builder, Entity *entity);
};

}// namespace dwg
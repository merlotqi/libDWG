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

#include <dwg/io/template/CadEntityTemplate_p.h>
#include <dwg/entities/Insert.h>

namespace dwg {

class CadInsertTemplate : public CadEntityTemplate
{
public:
    CadInsertTemplate();
    CadInsertTemplate(Insert *insert);
    void build(CadDocumentBuilder *builder) override;

    bool hasAtts() const;
    void setHasAtts(bool);

    int ownedObjectsCount() const;
    void setOwnedObjectsCount(int);

    std::optional<unsigned long long> blockHeaderHandle() const;
    void setBlockHeaderHandle(unsigned long long);

    std::string blockName() const;
    void setBlockName(const std::string &);

    std::optional<unsigned long long> firstAttributeHandle() const;
    void setFirstAttributeHandle(unsigned long long);

    std::optional<unsigned long long> endAttributeHandle() const;
    void setEndAttributeHandle(unsigned long long);

    std::optional<unsigned long long> seqendHandle() const;
    void setSeqendHandle(unsigned long long);

    std::vector<unsigned long long> attributesHandles() const;
    std::vector<unsigned long long> &attributesHandles();
    void setAttributesHandles(const std::vector<unsigned long long> &);

private:
    bool _hasAtts;
    int _ownedObjectsCount;
    std::optional<unsigned long long> _blockHeaderHandle;
    std::string _blockName;
    std::optional<unsigned long long> _firstAttributeHandle;
    std::optional<unsigned long long> _endAttributeHandle;
    std::optional<unsigned long long> _seqendHandle;
    std::vector<unsigned long long> _attributesHandles;
};

}// namespace dwg
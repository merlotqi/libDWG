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

#include <dwg/entities/MultiLeader.h>
#include <dwg/io/template/CadEntityTemplate_p.h>
#include <dwg/objects/MultiLeaderAnnotContext.h>
#include <map>
#include <vector>

namespace dwg {

class CadMLeaderTemplate : public CadEntityTemplate
{
public:
    struct LeaderLineSubTemplate
    {
        MultiLeaderAnnotContextLeaderLine *leaderLine;
        unsigned long long lineTypeHandle;
        unsigned long long arrowSymbolHandle;
    };

    CadMLeaderTemplate();
    CadMLeaderTemplate(MultiLeader *);
    void build(CadDocumentBuilder *builder) override;


    unsigned long long leaderStyleHandle() const;
    void setLeaderStyleHandle(unsigned long long);

    unsigned long long leaderLineTypeHandle() const;
    void setLeaderLineTypeHandle(unsigned long long);

    unsigned long long mtextStyleHandle() const;
    void setMtextStyleHandle(unsigned long long);

    unsigned long long blockContentHandle() const;
    void setBlockContentHandle(unsigned long long);

    unsigned long long arrowheadHandle() const;
    void setArrowheadHandle(unsigned long long);

    std::map<unsigned long long, bool> arrowheadHandles() const;
    std::map<unsigned long long, bool> &arrowheadHandles() ;

    std::map<MultiLeader::BlockAttribute, unsigned long long> blockAttributeHandles() const;
    std::map<MultiLeader::BlockAttribute, unsigned long long> &blockAttributeHandles();

    unsigned long long annotContextTextStyleHandle() const;
    void setAnnotContextTextStyleHandle(unsigned long long);

    unsigned long long annotContextBlockRecordHandle() const;
    void setAnnotContextBlockRecordHandle(unsigned long long);

    std::vector<LeaderLineSubTemplate> leaderLineSubTemplates() const;
    std::vector<LeaderLineSubTemplate> &leaderLineSubTemplates();

private:
    unsigned long long _leaderStyleHandle;
    unsigned long long _leaderLineTypeHandle;
    unsigned long long _mtextStyleHandle;
    unsigned long long _blockContentHandle;
    unsigned long long _arrowheadHandle;
    std::map<unsigned long long, bool> _arrowheadHandles;
    std::map<MultiLeader::BlockAttribute, unsigned long long> _blockAttributeHandles;
    unsigned long long _annotContextTextStyleHandle;
    unsigned long long _annotContextBlockRecordHandle;
    std::vector<LeaderLineSubTemplate> _leaderLineSubTemplates;
};

}// namespace dwg
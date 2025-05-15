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
#include <dwg/objects/MultiLeaderStyle.h>

namespace dwg {

class CadMLeaderStyleTemplate : public CadTemplateT<MultiLeaderStyle *>
{
public:
    CadMLeaderStyleTemplate();
    CadMLeaderStyleTemplate(MultiLeaderStyle *);
    void build(CadDocumentBuilder *builder) override;

    unsigned long long leaderLineTypeHandle() const;
    void setLeaderLineTypeHandle(unsigned long long);

    unsigned long long arrowheadHandle() const;
    void setArrowheadHandle(unsigned long long);

    unsigned long long mtextStyleHandle() const;
    void setMTextStyleHandle(unsigned long long);

    unsigned long long blockContentHandle() const;
    void setBlockContentHandle(unsigned long long);

private:
    unsigned long long _leaderLineTypeHandle;
    unsigned long long _arrowheadHandle;
    unsigned long long _mtextStyleHandle;
    unsigned long long _blockContentHandle;
};

}// namespace dwg
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
#include <dwg/tables/LineType.h>

namespace dwg {

class CadLineTypeTemplate : public CadTemplate<LineType *>
{
public:
    struct SegmentTemplate
    {
        LineType::Segment segment;
        std::optional<unsigned long long> styleHandle;
        void build(CadDocumentBuilder *builder);
    };

    CadLineTypeTemplate();
    CadLineTypeTemplate(LineType *);
    void build(CadDocumentBuilder *builder);

    std::optional<unsigned long long> ltypeControlHandle() const;
    void setLtypeControlHandle(unsigned long long);

    std::optional<double> totalLen() const;
    void setTotalLen(double);

    std::vector<SegmentTemplate> segmentTemplates() const;
    std::vector<SegmentTemplate> &segmentTemplates();

};

}// namespace dwg
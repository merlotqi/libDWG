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

#include <dwg/io/template/CadLineTypeTemplate_p.h>

namespace dwg {

/* ------------------ CadLineTypeTemplate::SegmentTemplate ------------------ */
void CadLineTypeTemplate::SegmentTemplate::build(CadDocumentBuilder *builder) {}


/* --------------------------- CadLineTypeTemplate -------------------------- */
CadLineTypeTemplate::CadLineTypeTemplate() : CadTemplateT<LineType *>(new LineType()) {}

CadLineTypeTemplate::CadLineTypeTemplate(LineType *l) : CadTemplateT<LineType *>(l) {}

void CadLineTypeTemplate::build(CadDocumentBuilder *builder) {}

std::optional<unsigned long long> CadLineTypeTemplate::ltypeControlHandle() const
{
    return _ltypeControlHandle;
}

void CadLineTypeTemplate::setLtypeControlHandle(unsigned long long value)
{
    _ltypeControlHandle = value;
}

std::optional<double> CadLineTypeTemplate::totalLen() const
{
    return _totalLen;
}

void CadLineTypeTemplate::setTotalLen(double value)
{
    _totalLen = value;
}

std::vector<CadLineTypeTemplate::SegmentTemplate> CadLineTypeTemplate::segmentTemplates() const
{
    return _segmentTemplates;
}

std::vector<CadLineTypeTemplate::SegmentTemplate> &CadLineTypeTemplate::segmentTemplates()
{
    return _segmentTemplates;
}

}// namespace dwg
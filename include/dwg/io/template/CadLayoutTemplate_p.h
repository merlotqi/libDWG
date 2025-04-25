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

namespace dwg {

class CadLayoutTemplate : public CadTemplate<Layout *>
{
public:
    CadLayoutTemplate();
    CadLayoutTemplate(Layout *l);
    void build(CadDocumentBuilder *builder);

    std::optional<unsigned long long> paperSpaceBlockHandle() const;
    void setPaperSpaceBlockHandle(unsigned long long);

    std::optional<unsigned long long> activeViewportHandle() const;
    void setActiveViewportHandle(unsigned long long);

    std::optional<unsigned long long> baseUcsHandle() const;
    void setBaseUcsHandle(unsigned long long);

    std::optional<unsigned long long> namesUcsHandle() const;
    void setNamesUcsHandle(unsigned long long);

    std::optional<unsigned long long> lasActiveViewportHandle() const;
    void setLasActiveViewportHandle(unsigned long long);

    std::vector<unsigned long long> viewportHandles() const;
    std::vector<unsigned long long> &viewportHandles();

private:
    std::optional<unsigned long long> _paperSpaceBlockHandle;
    std::optional<unsigned long long> _activeViewportHandle;
    std::optional<unsigned long long> _baseUcsHandle;
    std::optional<unsigned long long> _namesUcsHandle;
    std::optional<unsigned long long> _lasActiveViewportHandle;
    std::vector<unsigned long long> _viewportHandles;
};

}// namespace dwg
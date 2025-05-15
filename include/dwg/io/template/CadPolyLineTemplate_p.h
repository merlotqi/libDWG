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

#include <dwg/entities/PolyLine.h>
#include <dwg/io/template/CadEntityTemplate_p.h>
namespace dwg {

class PolyfaceMesh;

class PolyLinePlaceholder : public Polyline
{
public:
    PolyLinePlaceholder();
    ObjectType objectType() const override;
};

class CadPolyLineTemplate : public CadEntityTemplate
{
public:
    CadPolyLineTemplate();
    CadPolyLineTemplate(Polyline *polyline);
    void build(CadDocumentBuilder *builder) override;

    std::optional<unsigned long long> firstVertexHandle() const;
    void setFirstVertexHandle(unsigned long long);
    
    std::optional<unsigned long long> lastVertexHandle() const;
    void setLastVertexHandle(unsigned long long);

    std::optional<unsigned long long> seqendHandle() const;
    void setSeqendHandle(unsigned long long);

    std::vector<unsigned long long> vertexHandles() const;
    std::vector<unsigned long long> &vertexHandles();

    Polyline *polyline() const;
    void SetPolyLineObject(Polyline *polyline);

private:
    void buildPolyfaceMesh(PolyfaceMesh *polyfaceMesh, CadDocumentBuilder *builder);

private:
    std::optional<unsigned long long> _firstVertexHandle;
    std::optional<unsigned long long> _lastVertexHandle;
    std::optional<unsigned long long> _seqendHandle;
    std::vector<unsigned long long> _vertexHandles;
};

}// namespace dwg
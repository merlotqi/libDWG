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

#include <dwg/entities/collection/VertexSeqendCollection.h>
#include <dwg/entities/Seqend.h>

namespace dwg {

VertexSeqendCollection::VertexSeqendCollection(CadObject *owner) : _owner(owner) 
{
    _seqend = new Seqend();
}

VertexSeqendCollection::~VertexSeqendCollection() {}

CadObject *VertexSeqendCollection::owner() const
{
    return _owner;
}

Seqend *VertexSeqendCollection::seqend() const
{
    return _seqend;
}

void VertexSeqendCollection::setSeqend(Seqend *value)
{
    _seqend = value;
}

size_t VertexSeqendCollection::size() const
{
    return _entities.size();
}

Vertex *VertexSeqendCollection::at(size_t index)
{
    return _entities.at(index);
}

Vertex *VertexSeqendCollection::operator[](size_t index)
{
    return _entities.operator[](index);
}

void VertexSeqendCollection::add(Vertex *entity) {}

void VertexSeqendCollection::add(const std::initializer_list<Vertex *> &entities) {}

Vertex *VertexSeqendCollection::remove(Vertex *entity)
{
    return entity;
}

void VertexSeqendCollection::clear() {}

}// namespace dwg
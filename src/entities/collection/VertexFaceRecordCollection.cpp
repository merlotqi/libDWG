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

#include <dwg/entities/collection/VertexFaceRecordCollection.h>

namespace dwg {

VertexFaceRecordCollection::VertexFaceRecordCollection(CadObject *owner) : _owner(owner) 
{
}

VertexFaceRecordCollection::~VertexFaceRecordCollection() {}

CadObject *VertexFaceRecordCollection::owner() const
{
    return _owner;
}

size_t VertexFaceRecordCollection::size() const
{
    return _entities.size();
}

VertexFaceRecord *VertexFaceRecordCollection::at(size_t index)
{
    return _entities.at(index);
}

VertexFaceRecord *VertexFaceRecordCollection::operator[](size_t index)
{
    return _entities.operator[](index);
}

void VertexFaceRecordCollection::add(VertexFaceRecord *entity) {}

void VertexFaceRecordCollection::add(const std::initializer_list<VertexFaceRecord *> &entities) {}

VertexFaceRecord *VertexFaceRecordCollection::remove(VertexFaceRecord *entity)
{
    return entity;
}

void VertexFaceRecordCollection::clear() {}

}// namespace dwg
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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/Insert.h>

namespace dwg {

Insert::Insert(BlockRecord *) {}

Insert::~Insert() {}

ObjectType Insert::objectType() const { return isMultiple() ? ObjectType::MINSERT : ObjectType::INSERT; }

std::string Insert::objectName() const { return DxfFileToken::EntityInsert; }

std::string Insert::subclassMarker() const { return isMultiple() ? DxfSubclassMarker::MInsert : DxfSubclassMarker::Insert; }

BlockRecord *Insert::block() const { return _block; }

void Insert::setBlock(BlockRecord *value) { _block = value; }

XYZ Insert::insertPoint() const { return _insertPoint; }

void Insert::setInsertPoint(const XYZ &point) { _insertPoint = point; }

double Insert::XScale() const { return _xscale; }

void Insert::setXScale(double scale) { _xscale = scale; }

double Insert::YScale() const { return _yscale; }

void Insert::setYScale(double scale) { _yscale = scale; }

double Insert::ZScale() const { return _zscale; }

void Insert::setZScale(double scale) { _zscale = scale; }

double Insert::rotation() const { return _rotation; }

void Insert::setRotation(double angle) { _rotation = angle; }

XYZ Insert::normal() const { return _normal; }

void Insert::setNormal(const XYZ &normal) { _normal = normal;}

unsigned short Insert::columnCount() const { return _columnCount; }

void Insert::setColumnCount(unsigned short count) { _columnCount = count; }

unsigned short Insert::rowCount() const { return _rowCount; }

void Insert::setRowCount(unsigned short count) { _rowCount = count; }

double Insert::columnSpacing() const { return _columnSpacing; }

void Insert::setColumnSpacing(double spacing) { _columnSpacing = spacing; }

double Insert::rowSpacing() const { return _rowSpacing; }

void Insert::setRowSpacing(double spacing) { _rowSpacing = spacing; }

bool Insert::hasAttributes() const { return false; }

bool Insert::hasDynamicSubclass() const
{
    return true;
}

bool Insert::isMultiple() const
{
    return false;
}

Insert::Insert() {}

}// namespace dwg
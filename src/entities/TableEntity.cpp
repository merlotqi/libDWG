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
#include <dwg/entities/TableEntity.h>

namespace dwg {

TableEntity::Cell::Cell() {}

bool TableEntity::Cell::hasMultipleContent() const 
{ 
    return contents.size() > 1;
}

TableEntity::Cell::TableCellContent TableEntity::Cell::content() const 
{ 
    if(hasMultipleContent() || contents.size() == 0) 
        return TableCellContent();
    else
        return contents.at(0);
}

TableEntity::TableEntity() {}

TableEntity::~TableEntity() {}

ObjectType TableEntity::objectType() const { return ObjectType::UNLISTED; }

std::string TableEntity::objectName() const { return DxfFileToken::EntityTable; }

std::string TableEntity::subclassMarker() const { return DxfSubclassMarker::TableEntity; }

short TableEntity::version() const { return _version; }

void TableEntity::setVersion(short value) { _version = value; }

XYZ TableEntity::horizontalDirection() const { return _horizontalDirection; }

void TableEntity::setHorizontalDirection(const XYZ &value) { _horizontalDirection = value; }

int TableEntity::valueFlag() const { return _valueFlag; }

void TableEntity::setValueFlag(int value) { _valueFlag = value; }

std::vector<TableEntity::Row> TableEntity::rows() const { return _rows; }

void TableEntity::setRows(const std::vector<TableEntity::Row> &value) { _rows = value; }

std::vector<TableEntity::Column> TableEntity::columns() const { return _columns; }

void TableEntity::setColumns(const std::vector<TableEntity::Column> &value) { _columns = value; }

bool TableEntity::overrideFlag() const { return _overrideFlag; }

void TableEntity::setOverrideFlag(bool value) { _overrideFlag = value; }

bool TableEntity::overrideBorderColor() const { return _overrideBorderColor; }

void TableEntity::setOverrideBorderColor(bool value) { _overrideBorderColor = value; }

bool TableEntity::overrideBorderLineWeight() const { return _overrideBorderLineWeight; }

void TableEntity::setOverrideBorderLineWeight(bool value) { _overrideBorderLineWeight = value; }

bool TableEntity::overrideBorderVisibility() const { return _overrideBorderVisibility; }

void TableEntity::setOverrideBorderVisibility(bool value) { _overrideBorderVisibility = value; }

TableStyle *TableEntity::style() const { return _style; }

void TableEntity::setTableStyle(TableStyle *value) { _style = value; }

BlockRecord *TableEntity::tableBlock() const { return _tableBlock; }

void TableEntity::setTableBlock(BlockRecord *value) { _tableBlock = value; }

TableContent *TableEntity::content() const { return _content; }

void TableEntity::setContent(TableContent *value) { _content = value; }

TableBreakData TableEntity::tableBreakData() const { return _tableBreakData; }

void TableEntity::setTableBreakData(const TableBreakData &value) { _tableBreakData = value; }

std::vector<TableBreakRowRange> TableEntity::breakRowRanges() const { return _breakRowRanges; }

void TableEntity::setBreakRowRanges(const std::vector<TableBreakRowRange> &value) { _breakRowRanges = value; }

TableEntity::Cell TableEntity::cellAt(int row, int column) const { return TableEntity::Cell(); }

}// namespace dwg
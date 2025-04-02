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

#include <dwg/entities/Insert.h>
#include <dwg/entities/TableEntityBase.h>

namespace dwg {

class TableEntity : public Insert
{
public:
    TableEntity();
    virtual ~TableEntity();
    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    short version() const;
    void setVersion(short v);

    XYZ horizontalDirection() const;
    void setHorizontalDirection(const XYZ &);

    int valueFlag() const;
    void setValueFlag(int flag);

    std::vector<Row> rows() const;
    void setRows(const std::vector<Row> &rows);

    std::vector<Column> columns() const;
    void setColumns(const std::vector<Column> &cols);

    bool overrideFlag() const;
    void setOverrideFlag(flag);

    bool overrideBorderColor() const;
    void setOverrideBorderColor(bool obc);

    bool overrideBorderLineWeight() const;
    void setOverrideBorderLineWeight(bool oblw);

    bool overrideBorderVisibility() const;
    void setOverrideBorderVisibility(bool obv);

    TableStyle *style() const;
    void setTableStyle(TableStyle *);

    BlockRecord *tableBlock() const;
    void setTableBlock(BlockRecord *record);

    TableContent content() const;
    void setContent(const TableContent &);

    BreakData tableBreakData() const;
    void setTableBreakData(const BreakData &);

    std::vector<BreakRowRange> breakRowRanges() const;
    void setBreakRowRanges(const std::vector<BreakRowRange> &);

    Cell cellAt(int row, int column) const;
};

}// namespace dwg
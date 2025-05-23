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
#include <dwg/utils/QFlags.h>

namespace dwg {

class TableContent;
class TableStyle;
class LIBDWG_API TableEntity : public Insert
{
public:
    TableEntity();
    ~TableEntity();
    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

public:
    struct LIBDWG_API Cell
    {
        enum class CellType
        {
            Text = 1,
            Block = 2
        };

        enum TableCellStateFlag
        {
            /// None
            None = 0x0,
            /// Content  locked
            ContentLocked = 0x1,
            /// Content read only
            ContentReadOnly = 0x2,
            /// Linked.
            Linked = 0x4,
            /// Content modifed after update
            ContentModifiedAfterUpdate = 0x8,
            /// Format locked
            FormatLocked = 0x10,
            /// Format readonly
            FormatReadOnly = 0x20,
            /// Format was modified after update
            FormatModifiedAfterUpdate = 0x40,
        };
        Q_DECLARE_FLAGS(TableCellStateFlags, TableCellStateFlag);

        enum class TableCellContentType
        {
            Unknown = 0,
            Value = 0x1,
            Field = 0x2,
            Block = 0x4,
        };

        struct LIBDWG_API TableCellContent
        {
            TableContentFormat format;
            TableCellContentType contentType;
            TableCellValue value;
        };


        struct LIBDWG_API TableCellContentGeometry
        {
            XYZ distanceTopLeft;
            XYZ distanceCenter;
            double contentWidth;
            double contentHeight;
            double width;
            double height;
            int flags;
        };


        Cell();

        CellType type;
        int flagValue;
        int mergedValue;
        bool autofit;
        int borderWith;
        int borderHeight;
        short virtualEdgeFlag;
        double rotation;
        std::string toolTip;
        TableCellStateFlags stateFlags;
        bool hasLinkedData;
        TableCellStyle styleOverride;
        int customData;
        std::vector<TableCustomDataEntry> customDataCollection;
        std::vector<TableCellContent> contents;
        TableCellContentGeometry geometry;

        bool hasMultipleContent() const;
        TableCellContent content() const;
    };

    struct LIBDWG_API Column
    {
        std::string name;
        double width;
        int customData;
        TableCellStyle styleOverride;
        std::vector<TableCustomDataEntry> customDataCollection;
    };

    struct LIBDWG_API Row
    {
        double height;
        int customData;
        TableCellStyle cellStyleOverride;
        std::vector<Cell> cells;
        std::vector<TableCustomDataEntry> customDataCollection;
    };

public:
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
    void setOverrideFlag(bool);

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

    TableContent *content() const;
    void setContent(TableContent *);

    TableBreakData tableBreakData() const;
    void setTableBreakData(const TableBreakData &);

    std::vector<TableBreakRowRange> breakRowRanges() const;
    void setBreakRowRanges(const std::vector<TableBreakRowRange> &);

    Cell cellAt(int row, int column) const;

private:
    short _version;
    XYZ _horizontalDirection;
    int _valueFlag;
    std::vector<Row> _rows;
    std::vector<Column> _columns;
    bool _overrideFlag;
    bool _overrideBorderColor;
    bool _overrideBorderLineWeight;
    bool _overrideBorderVisibility;
    TableStyle *_style;
    BlockRecord *_tableBlock;
    TableContent *_content;
    TableBreakData _tableBreakData;
    std::vector<TableBreakRowRange> _breakRowRanges;
};

}// namespace dwg
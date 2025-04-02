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

#include <dwg/Color.h>
#include <dwg/utils/DwgVariant.h>

namespace dwg {
enum class TableBorderPropertyFlag
{
    /// None.
    None = 0x0,
    /// Border type.
    BorderType = 0x1,
    /// Line weight.
    LineWeight = 0x2,
    /// Line type.
    LineType = 0x4,
    /// Color.
    Color = 0x8,
    /// Invisibility.
    Invisibility = 0x10,
    /// Double line spacing.
    DoubleLineSpacing = 0x20,
    /// All.
    All = 0x3F
};
typedef int TableBorderPropertyFlags;

enum class TableCellContentLayoutFlag
{
    None = 0,
    Flow = 1,
    StackedHorizontal = 2,
    StackedVertical = 4
};
typedef int TableCellContentLayoutFlags;

enum class TableCellContentType
{
    Unknown = 0,
    Value = 0x1,
    Field = 0x2,
    Block = 0x4,
};

enum class TableCellStateFlag
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
typedef int TableCellStateFlags;

enum class TableCellStylePropertyFlag
{
    None = 0x0,
    //Content format properties:
    DataType = 0x1,
    DataFormat = 0x2,
    Rotation = 0x4,
    BlockScale = 0x8,
    Alignment = 0x10,
    ContentColor = 0x20,
    TextStyle = 0x40,
    TextHeight = 0x80,
    AutoScale = 0x100,
    // Cell style properties:
    BackgroundColor = 0x200,
    MarginLeft = 0x400,
    MarginTop = 0x800,
    MarginRight = 0x1000,
    MarginBottom = 0x2000,
    ContentLayout = 0x4000,
    MarginHorizontalSpacing = 0x20000,
    MarginVerticalSpacing = 0x40000,
    //Row/column properties:
    MergeAll = 0x8000,
    //Table properties:
    FlowDirectionBottomToTop = 0x10000
};
typedef int TableCellStylePropertyFlags;


enum class TableBorderType
{
    /// Single border line.
    Single = 1,
    /// Double border line.
    Double = 2
};

enum class TableBreakFlowDirection
{
    /// Right
    Right = 1,
    /// Vertical
    Vertical = 2,
    /// Left
    Left = 4
};

enum class TableBreakOptionFlag
{
    /// None
    None = 0,
    /// Enable breaks
    EnableBreaks = 1,
    /// Repeat top labels
    RepeatTopLabels = 2,
    /// Repeat bottom labels
    RepeatBottomLabels = 4,
    /// Allow manual positions
    AllowManualPositions = 8,
    /// Allow manual heights
    AllowManualHeights = 16
};
typedef int TableBreakOptionFlags;

enum class TableCellEdgeFlag
{
    Unknown = 0,
    Top = 1,
    Right = 2,
    Bottom = 4,
    Left = 8,
    InsideVertical = 16,
    InsideHorizontal = 32,
};
typedef int TableCellEdgeFlags;

enum class TableCellStyleTypeType
{
    Cell = 1,
    Row = 2,
    Column = 3,
    FormattedTableData = 4,
    Table = 5
};

enum class TableCellType
{
    Text = 1,
    Block = 2
};

enum class TableValueUnitType
{
    /// No units.
    NoUnits = 0,
    /// Distance.
    Distance = 1,
    /// Angle.
    Angle = 2,
    /// Area.
    Area = 4,
    /// Volumne.
    Volume = 8,
    /// Currency.
    Currency = 0x10,
    /// Percentage.
    Percentage = 0x20
};

enum class TableCellValueType
{
    /// Unknown
    Unknown = 0,
    /// 32 bit Long value
    Long = 1,
    /// Double value
    Double = 2,
    /// String value
    String = 4,
    /// Date value
    Date = 8,
    /// 2D point value
    Point2D = 0x10,
    /// 3D point value
    Point3D = 0x20,
    /// Object handle value
    Handle = 0x40,
    /// Buffer value
    Buffer = 0x80,
    /// Result buffer value
    ResultBuffer = 0x100,
    /// General
    General = 0x200
};

enum class TableMarginFlag
{
    None = 0,
    Override = 1,
};
typedef int TableMarginFlags;

struct TableBreakHeight
{
    XYZ position;
    double height;
};

struct TableCellValue
{
    TableCellValueType valueType;
    TableValueUnitType units;
    int flags;
    bool isEmpty;
    std::string text;
    std::string format;
    std::string formatedValue;
    DwgVariant value;
};

struct TableBreakData
{
    TableBreakOptionFlags flags;
    TableBreakFlowDirection flowDirection;
    double breakSpacing;
    std::vector<TableBreakHeight> heights;
};

struct TableBreakRowRange
{
    XYZ position;
    int startRowIndex;
    int endRowIndex;
};

struct TableCellBorder
{
    TableCellEdgeFlags edgeFlags;
    TableBorderPropertyFlags propertyOverrideFlags;
    TableBorderType type;
    Color color;
    short lineWeight;
    bool isInvisible;
    double doubleLineSpacing;
};

struct TableContentFormat
{
    bool hasData;
    double rotation;
    double scale;
    int alignment;
    TableCellStylePropertyFlags propertyOverrideFlags;
    int propertyFlags;
    int valueDataType;
    int valueUnitType;
    std::string valueFormatString;
    Color color;
    double textHeight;
};

struct TableCellContent
{
    TableContentFormat format;
    TableCellContentType contentType;
    TableCellValue value;
};

struct TableCellContentGeometry
{
    XYZ distanceTopLeft;
    XYZ distanceCenter;
    double contentWidth;
    double contentHeight;
    double width;
    double height;
    int flags;
};

struct TableCellRange
{
    int topRowIndex;
    int leftColumnIndex;
    int bottomRowIndex;
    int rightColumnIndex;
};

struct TableCellStyle : TableContentFormat
{
    TableCellStyleTypeType type;
    TableCellStylePropertyFlags tableCellStylePropertyFlags;
    Color backgroundColor;
    TableCellContentLayoutFlags contentLayoutFlags;
    TableMarginFlags marginOverrideFlags;
    double verticalMargin;
    double horizontalMargin;
    double bottomMargin;
    double rightMargin;
    double marginHorizontalSpacing;
    double marginVerticalSpacing;
    std::vector<TableCellBorder> borders;
};


struct TableCustomDataEntry
{
    std::string name;
    TableCellValue value;
};

struct TableCell
{
    TableCellType type;
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

struct TableColumn
{
    std::string name;
    double width;
    int customData;
    TableCellStyle styleOverride;
    std::vector<TableCustomDataEntry> customDataCollection;
};

struct TableRow
{
    double height;
    int customData;
    TableCellStyle cellStyleOverride;
    std::vector<TableCell> cells;
    std::vector<TableCustomDataEntry> cstomDataCollection;
};

struct TableAttribute
{
    std::string value;
};

}// namespace dwg
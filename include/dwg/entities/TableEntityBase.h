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
#include <dwg/utils/QFlags.h>

namespace dwg {

class LIBDWG_API TableBreakData
{
public:
    struct BreakHeight
    {
        XYZ position;
        double height;
    };
    enum class BreakOptionFlag
    {
        None = 0,                /// None
        EnableBreaks = 1,        /// Enable breaks
        RepeatTopLabels = 2,     /// Repeat top labels
        RepeatBottomLabels = 4,  /// Repeat bottom labels
        AllowManualPositions = 8,/// Allow manual positions
        AllowManualHeights = 16  /// Allow manual heights
    };
    Q_DECLARE_FLAGS(BreakOptionFlags, BreakOptionFlag);

    enum class BreakFlowDirection
    {
        Right = 1,   /// Right
        Vertical = 2,/// Vertical
        Left = 4     /// Left
    };

public:
    TableBreakData();
    ~TableBreakData();

    BreakOptionFlags flags() const;
    void setFlags(BreakOptionFlags);

    BreakFlowDirection flowDirection() const;
    void setFlowDirection(BreakFlowDirection);

    double breakSpacing() const;
    void setBreakSpacing(double);

    std::vector<BreakHeight> heights() const;
    void setHeight(const std::vector<BreakHeight> &);

private:
    BreakOptionFlags _flags;
    BreakFlowDirection _flowDirection;
    double _breakSpacing;
    std::vector<BreakHeight> _heights;
};

class LIBDWG_API TableBreakRowRange
{
public:
    TableBreakRowRange();
    ~TableBreakRowRange();

    XYZ position() const;
    void setPosition(const XYZ &);

    int startRowIndex() const;
    void setStartRowIndex(int);

    int endRowIndex() const;
    void setEndRowIndex(int);

private:
    XYZ _position;
    int _startRowIndex;
    int _endRowIndex;
};

class LIBDWG_API TableCellValue
{
public:
    enum class TableValueUnitType
    {
        NoUnits = 0,     /// No units.
        Distance = 1,    /// Distance.
        Angle = 2,       /// Angle.
        Area = 4,        /// Area.
        Volume = 8,      /// Volumne.
        Currency = 0x10, /// Currency.
        Percentage = 0x20/// Percentage.
    };

    enum class TableCellValueType
    {
        Unknown = 0,         /// Unknown
        Long = 1,            /// 32 bit Long value
        Double = 2,          /// Double value
        String = 4,          /// String value
        Date = 8,            /// Date value
        Point2D = 0x10,      /// 2D point value
        Point3D = 0x20,      /// 3D point value
        Handle = 0x40,       /// Object handle value
        Buffer = 0x80,       /// Buffer value
        ResultBuffer = 0x100,/// Result buffer value
        General = 0x200      /// General
    };

public:
    TableCellValue();
    ~TableCellValue();

    TableCellValueType valueType() const;
    void setValueType(TableCellValueType);

    TableValueUnitType units() const;
    void setUnits(TableValueUnitType);

    int flags() const;
    void setFlags(int);

    bool isEmpty() const;
    void setEmpty(bool);

    std::string text() const;
    void setText(const std::string &);

    std::string format() const;
    void setFormat(const std::string &);

    std::string formatedValue() const;
    void setFormatedValue(const std::string &);

    DwgVariant value() const;
    void setValue(const DwgVariant &);

private:
    TableCellValueType _valueType;
    TableValueUnitType _units;
    int _flags;
    bool _isEmpty;
    std::string _text;
    std::string _format;
    std::string _formatedValue;
    DwgVariant _value;
};

class LIBDWG_API TableCellBorder
{
public:
    enum class TableBorderPropertyFlag
    {
        None = 0x0,              /// None.
        BorderType = 0x1,        /// Border type.
        LineWeight = 0x2,        /// Line weight.
        LineType = 0x4,          /// Line type.
        Color = 0x8,             /// Color.
        Invisibility = 0x10,     /// Invisibility.
        DoubleLineSpacing = 0x20,/// Double line spacing.
        All = 0x3F               /// All.
    };
    Q_DECLARE_FLAGS(TableBorderPropertyFlags, TableBorderPropertyFlag);

    enum class TableBorderType
    {
        Single = 1,/// Single border line.
        Double = 2 /// Double border line.
    };

    enum class CellEdgeFlag
    {
        Unknown = 0,
        Top = 1,
        Right = 2,
        Bottom = 4,
        Left = 8,
        InsideVertical = 16,
        InsideHorizontal = 32,
    };
    Q_DECLARE_FLAGS(CellEdgeFlags, CellEdgeFlag);

public:
    TableCellBorder();
    ~TableCellBorder();

    CellEdgeFlags edgeFlags() const;
    void setEdgeFlags(CellEdgeFlags);

    TableBorderPropertyFlags propertyOverrideFlags() const;
    void setPropertyOverrideFlags(TableBorderPropertyFlags);

    TableBorderType type() const;
    void setType(TableBorderType);

    Color color() const;
    void setColor(const Color &);

    short lineWeight() const;
    void setLineWeight(short);

    bool isInvisible() const;
    void setIsInvisible(bool);

    double doubleLineSpacing() const;
    void setDoubleLineSpacing(double);

private:
    CellEdgeFlags _edgeFlags;
    TableBorderPropertyFlags _propertyOverrideFlags;
    TableBorderType _type;
    Color _color;
    short _lineWeight;
    bool _isInvisible;
    double _doubleLineSpacing;
};

class LIBDWG_API TableContentFormat
{
public:
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
    Q_DECLARE_FLAGS(TableCellStylePropertyFlags, TableCellStylePropertyFlag);

public:
    TableContentFormat();
    ~TableContentFormat();

    bool hasData() const;
    void setHasData(bool);

    double rotation() const;
    void setRotation(double);

    double scale() const;
    void setScale(double);

    int alignment() const;
    void setAlignment(int);

    TableCellStylePropertyFlags propertyOverrideFlags() const;
    void setPropertyOverrideFlags(TableCellStylePropertyFlags);

    int propertyFlags() const;
    void setPropertyFlags(int);

    int valueDataType() const;
    void setValueDataType(int);

    int valueUnitType() const;
    void setValueUnitType(int);

    std::string valueFormatString() const;
    void setValueFormatString(const std::string &);

    Color color() const;
    void setColor(const Color &);

    double textHeight() const;
    void setTextHeight(double);

private:
    bool _hasData;
    double _rotation;
    double _scale;
    int _alignment;
    TableCellStylePropertyFlags _propertyOverrideFlags;
    int _propertyFlags;
    int _valueDataType;
    int _valueUnitType;
    std::string _valueFormatString;
    Color _color;
    double _textHeight;
};

class LIBDWG_API TableCellStyle : public TableContentFormat
{
public:
    enum class CellStyleTypeType
    {
        Cell = 1,
        Row = 2,
        Column = 3,
        FormattedTableData = 4,
        Table = 5
    };

    enum class TableCellContentLayoutFlag
    {
        None = 0,
        Flow = 1,
        StackedHorizontal = 2,
        StackedVertical = 4
    };
    Q_DECLARE_FLAGS(TableCellContentLayoutFlags, TableCellContentLayoutFlag);

    enum class MarginFlags
    {
        None = 0,
        Override = 1,
    };

    TableCellStyle();

    CellStyleTypeType type() const;
    void setType(CellStyleTypeType);

    TableCellStylePropertyFlags tableCellStylePropertyFlags() const;
    void setTableCellStylePropertyFlags(TableCellStylePropertyFlags);

    Color backgroundColor() const;
    void setBackgroundColor(const Color &);

    TableCellContentLayoutFlags contentLayoutFlags() const;
    void setContentLayoutFlags(TableCellContentLayoutFlags);

    MarginFlags marginOverrideFlags() const;
    void setMarginOverrideFlags(MarginFlags);

    double verticalMargin() const;
    void setVerticalMargin(double);

    double horizontalMargin() const;
    void setHorizontalMargin(double);

    double bottomMargin() const;
    void setBottomMargin(double);

    double rightMargin() const;
    void setRightMargin(double);

    double marginHorizontalSpacing() const;
    void setMarginHorizontalSpacing(double);

    double marginVerticalSpacing() const;
    void setMarginVerticalSpacing(double);

    std::vector<TableCellBorder> borders() const;
    void setBorders(const std::vector<TableCellBorder> &);

private:
    CellStyleTypeType _type;
    TableCellStylePropertyFlags _tableCellStylePropertyFlags;
    Color _backgroundColor;
    TableCellContentLayoutFlags _contentLayoutFlags;
    MarginFlags _marginOverrideFlags;
    double _verticalMargin;
    double _horizontalMargin;
    double _bottomMargin;
    double _rightMargin;
    double _marginHorizontalSpacing;
    double _marginVerticalSpacing;
    std::vector<TableCellBorder> _borders;
};

class LIBDWG_API TableCustomDataEntry
{
public:
    TableCustomDataEntry();

    std::string name() const;
    void setNname(const std::string &);
    TableCellValue value() const;
    void setValue(const TableCellValue &);

private:
    std::string _name;
    TableCellValue _value;
};

}// namespace dwg
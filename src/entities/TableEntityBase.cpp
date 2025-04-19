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

#include <dwg/entities/TableEntityBase.h>

namespace dwg {

/* ----------------------------- TableBreakData ----------------------------- */
TableBreakData::TableBreakData() {}

TableBreakData::~TableBreakData() {}

TableBreakData::BreakOptionFlags TableBreakData::flags() const
{
    return _flags;
}

void TableBreakData::setFlags(TableBreakData::BreakOptionFlags value)
{
    _flags = value;
}

TableBreakData::BreakFlowDirection TableBreakData::flowDirection() const
{
    return _flowDirection;
}

void TableBreakData::setFlowDirection(TableBreakData::BreakFlowDirection value)
{
    _flowDirection = value;
}

double TableBreakData::breakSpacing() const
{
    return _breakSpacing;
}

void TableBreakData::setBreakSpacing(double value)
{
    _breakSpacing = value;
}

std::vector<TableBreakData::BreakHeight> TableBreakData::heights() const
{
    return _heights;
}

void TableBreakData::setHeight(const std::vector<TableBreakData::BreakHeight> &value)
{
    _heights = value;
}


/* --------------------------- TableBreakRowRange --------------------------- */
TableBreakRowRange::TableBreakRowRange() {}

TableBreakRowRange::~TableBreakRowRange() {}

XYZ TableBreakRowRange::position() const
{
    return _position;
}

void TableBreakRowRange::setPosition(const XYZ &value)
{
    _position = value;
}

int TableBreakRowRange::startRowIndex() const
{
    return _startRowIndex;
}

void TableBreakRowRange::setStartRowIndex(int value)
{
    _startRowIndex = value;
}

int TableBreakRowRange::endRowIndex() const
{
    return _endRowIndex;
}

void TableBreakRowRange::setEndRowIndex(int value)
{
    _endRowIndex = value;
}


/* ----------------------------- TableCellValue ----------------------------- */
TableCellValue::TableCellValue() {}

TableCellValue::~TableCellValue() {}

TableCellValue::TableCellValueType TableCellValue::valueType() const
{
    return _valueType;
}

void TableCellValue::setValueType(TableCellValue::TableCellValueType value)
{
    _valueType = value;
}

TableCellValue::TableValueUnitType TableCellValue::units() const
{
    return _units;
}

void TableCellValue::setUnits(TableCellValue::TableValueUnitType value)
{
    _units = value;
}

int TableCellValue::flags() const
{
    return _flags;
}

void TableCellValue::setFlags(int value)
{
    _flags = value;
}

bool TableCellValue::isEmpty() const
{
    return _isEmpty;
}

void TableCellValue::setEmpty(bool value)
{
    _isEmpty = value;
}

std::string TableCellValue::text() const
{
    return _text;
}

void TableCellValue::setText(const std::string &value)
{
    _text = value;
}

std::string TableCellValue::format() const
{
    return _format;
}

void TableCellValue::setFormat(const std::string &value)
{
    _format = value;
}

std::string TableCellValue::formatedValue() const
{
    return _formatedValue;
}

void TableCellValue::setFormatedValue(const std::string &value)
{
    _formatedValue = value;
}

DwgVariant TableCellValue::value() const
{
    return _value;
}

void TableCellValue::setValue(const DwgVariant &value)
{
    _value = value;
}


/* ----------------------------- TableCellBorder ---------------------------- */
TableCellBorder::TableCellBorder() : _color(Color(short(0))) {}

TableCellBorder::~TableCellBorder() {}

TableCellBorder::CellEdgeFlags TableCellBorder::edgeFlags() const
{
    return _edgeFlags;
}

void TableCellBorder::setEdgeFlags(TableCellBorder::CellEdgeFlags) {}

TableCellBorder::TableBorderPropertyFlags TableCellBorder::propertyOverrideFlags() const
{
    return _propertyOverrideFlags;
}

void TableCellBorder::setPropertyOverrideFlags(TableCellBorder::TableBorderPropertyFlags) {}

TableCellBorder::TableBorderType TableCellBorder::type() const
{
    return _type;
}

void TableCellBorder::setType(TableCellBorder::TableBorderType) {}

Color TableCellBorder::color() const
{
    return _color;
}

void TableCellBorder::setColor(const Color &) {}

short TableCellBorder::lineWeight() const
{
    return _lineWeight;
}

void TableCellBorder::setLineWeight(short) {}

bool TableCellBorder::isInvisible() const
{
    return _isInvisible;
}

void TableCellBorder::setIsInvisible(bool) {}

double TableCellBorder::doubleLineSpacing() const
{
    return _doubleLineSpacing;
}

void TableCellBorder::setDoubleLineSpacing(double) {}


/* -------------------------- TableContentFormat --------------------------- */
TableContentFormat::TableContentFormat() : _color(Color(short(0))) {}

TableContentFormat::~TableContentFormat() {}

bool TableContentFormat::hasData() const
{
    return _hasData;
}

void TableContentFormat::setHasData(bool) {}

double TableContentFormat::rotation() const
{
    return _rotation;
}

void TableContentFormat::setRotation(double) {}

double TableContentFormat::scale() const
{
    return _scale;
}

void TableContentFormat::setScale(double) {}

int TableContentFormat::alignment() const
{
    return _alignment;
}

void TableContentFormat::setAlignment(int) {}

TableContentFormat::TableCellStylePropertyFlags TableContentFormat::propertyOverrideFlags() const
{
    return _propertyOverrideFlags;
}

void TableContentFormat::setPropertyOverrideFlags(TableContentFormat::TableCellStylePropertyFlags) {}

int TableContentFormat::propertyFlags() const
{
    return _propertyFlags;
}

void TableContentFormat::setPropertyFlags(int) {}

int TableContentFormat::valueDataType() const
{
    return _valueDataType;
}

void TableContentFormat::setValueDataType(int) {}

int TableContentFormat::valueUnitType() const
{
    return _valueUnitType;
}

void TableContentFormat::setValueUnitType(int) {}

std::string TableContentFormat::valueFormatString() const
{
    return _valueFormatString;
}

void TableContentFormat::setValueFormatString(const std::string &) {}

Color TableContentFormat::color() const
{
    return _color;
}

void TableContentFormat::setColor(const Color &) {}

double TableContentFormat::textHeight() const
{
    return _textHeight;
}

void TableContentFormat::setTextHeight(double) {}


/* ----------------------------- TableCellStyle ----------------------------- */
TableCellStyle::TableCellStyle() : _backgroundColor(Color(short(0))) {}

TableCellStyle::CellStyleTypeType TableCellStyle::type() const
{
    return _type;
}

void TableCellStyle::setType(TableCellStyle::CellStyleTypeType) {}

TableContentFormat::TableCellStylePropertyFlags TableCellStyle::tableCellStylePropertyFlags() const
{
    return _tableCellStylePropertyFlags;
}

void TableCellStyle::setTableCellStylePropertyFlags(TableContentFormat::TableCellStylePropertyFlags) {}

Color TableCellStyle::backgroundColor() const
{
    return _backgroundColor;
}

void TableCellStyle::setBackgroundColor(const Color &) {}

TableCellStyle::TableCellContentLayoutFlags TableCellStyle::contentLayoutFlags() const
{
    return _contentLayoutFlags;
}

void TableCellStyle::setContentLayoutFlags(TableCellStyle::TableCellContentLayoutFlags) {}

TableCellStyle::MarginFlags TableCellStyle::marginOverrideFlags() const
{
    return _marginOverrideFlags;
}

void TableCellStyle::setMarginOverrideFlags(TableCellStyle::MarginFlags) {}

double TableCellStyle::verticalMargin() const
{
    return _verticalMargin;
}

void TableCellStyle::setVerticalMargin(double) {}

double TableCellStyle::horizontalMargin() const
{
    return _horizontalMargin;
}

void TableCellStyle::setHorizontalMargin(double) {}

double TableCellStyle::bottomMargin() const
{
    return _bottomMargin;
}

void TableCellStyle::setBottomMargin(double) {}

double TableCellStyle::rightMargin() const
{
    return _rightMargin;
}

void TableCellStyle::setRightMargin(double) {}

double TableCellStyle::marginHorizontalSpacing() const
{
    return _marginHorizontalSpacing;
}

void TableCellStyle::setMarginHorizontalSpacing(double) {}

double TableCellStyle::marginVerticalSpacing() const
{
    return _marginVerticalSpacing;
}

void TableCellStyle::setMarginVerticalSpacing(double) {}

std::vector<TableCellBorder> TableCellStyle::borders() const
{
    return _borders;
}

void TableCellStyle::setBorders(const std::vector<TableCellBorder> &) {}


/* -------------------------- TableCustomDataEntry -------------------------- */
TableCustomDataEntry::TableCustomDataEntry() {}

std::string TableCustomDataEntry::name() const
{
    return _name;
}

void TableCustomDataEntry::setNname(const std::string &) {}

TableCellValue TableCustomDataEntry::value() const
{
    return _value;
}

void TableCustomDataEntry::setValue(const TableCellValue &) {}

}// namespace dwg
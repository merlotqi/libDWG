/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software{} you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation{} either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY{} without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program{} if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/MText.h>

namespace dwg {

MText::TextColumn::TextColumn() {}

MText::MText() : _backgroundTransparency(Transparency::ByBlock) {}

MText::~MText() {}

ObjectType MText::objectType() const
{
    return ObjectType::MTEXT;
}

std::string MText::objectName() const
{
    return DxfFileToken::EntityMText;
}

std::string MText::subclassMarker() const
{
    return DxfSubclassMarker::MText;
}

double MText::horizontalWidth() const
{
    return _horizontalWidth;
}

void MText::setHorizontalWidth(double width)
{
    _horizontalWidth = width;
}

double MText::verticalHeight() const
{
    return _verticalHeight;
}

void MText::setVerticalHeight(double height)
{
    _verticalHeight = height;
}

XYZ MText::insertPoint() const
{
    return _insertPoint;
}

void MText::setInsertPoint(const XYZ &point)
{
    _insertPoint = point;
}

XYZ MText::normal() const
{
    return _normal;
}

void MText::setNormal(const XYZ &normal)
{
    _normal = normal;
}

double MText::height() const
{
    return _height;
}

void MText::setHeight(double height)
{
    _height = height;
}

double MText::rectangleHeight() const
{
    return _rectangleHeight;
}

void MText::setRectangleHeight(double height)
{
    _rectangleHeight = height;
}

double MText::rectangleWidth() const
{
    return _rectangleWidth;
}

void MText::setRectangleWidth(double width)
{
    _rectangleWidth = width;
}

AttachmentPointType MText::attachmentPoint() const
{
    return _attachmentPoint;
}

void MText::setAttachmentPoint(AttachmentPointType type)
{
    _attachmentPoint = type;
}

DrawingDirectionType MText::drawingDirection() const
{
    return _drawingDirection;
}

void MText::setDrawingDirection(DrawingDirectionType direction)
{
    _drawingDirection = direction;
}

std::string MText::value() const
{
    return _value;
}

void MText::setValue(const std::string &value)
{
    _value = value;
}

TextStyle *MText::style() const
{
    return _style;
}

void MText::setStyle(TextStyle *style)
{
    _style = style;
}

XYZ MText::alignmentPoint() const
{
    return _alignmentPoint;
}

void MText::setAlignmentPoint(const XYZ &point)
{
    _alignmentPoint = point;
}

double MText::rotation() const
{
    return _rotation;
}

void MText::setRotation(double rotation)
{
    _rotation = rotation;
}

LineSpacingStyleType MText::lineSpacingStyle() const
{
    return _lineSpacingStyle;
}

void MText::setLineSpacingStyle(LineSpacingStyleType style)
{
    _lineSpacingStyle = style;
}

double MText::lineSpacing() const
{
    return _lineSpacing;
}

void MText::setLineSpacing(double spacing)
{
    _lineSpacing = spacing;
}

BackgroundFillFlags MText::backgroundFillFlags() const
{
    return _backgroundFillFlags;
}

void MText::setBackgroundFillFlags(BackgroundFillFlags flags)
{
    _backgroundFillFlags = flags;
}

double MText::backgroundScale() const
{
    return _backgroundScale;
}

void MText::setBackgroundScale(double scale)
{
    _backgroundScale = scale;
}

Color MText::backgroundColor() const
{
    return _backgroundColor;
}

void MText::setBackgroundColor(const Color &color)
{
    _backgroundColor = color;
}

Transparency MText::backgroundTransparency() const
{
    return _backgroundTransparency;
}

void MText::setBackgroundTransparency(const Transparency &transparency)
{
    _backgroundTransparency = transparency;
}

MText::TextColumn MText::column() const
{
    return _column;
}

void MText::setColumn(const MText::TextColumn &column)
{
    _column = column;
}

bool MText::isAnnotative() const
{
    return _isAnnotative;
}

void MText::setIsAnnotative(bool annotative)
{
    _isAnnotative = annotative;
}

}// namespace dwg
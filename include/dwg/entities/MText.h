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
#include <dwg/Transparency.h>
#include <dwg/entities/AttachmentPointType.h>
#include <dwg/entities/BackgroundFillFlags.h>
#include <dwg/entities/ColumnType.h>
#include <dwg/entities/DrawingDirectionType.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/LineSpacingStyleType.h>

namespace dwg {

class TextStyle;

class LIBDWG_API MText : public Entity
{
public:
    struct LIBDWG_API TextColumn
    {
        ColumnType columnType;            ///< Type of column layout.
        int columnCount;                  ///< The number of columns.
        bool columnFlowReversed;          ///< Whether the column flow is reversed.
        bool columnAutoHeight;            ///< Whether the column height is automatically adjusted.
        double columnWidth;               ///< The width of each column.
        double columnGutter;              ///< The spacing between columns.
        std::vector<double> columnHeights;///< List of individual column heights.

        TextColumn();
    };

public:
    MText();
    ~MText();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    double horizontalWidth() const;
    void setHorizontalWidth(double width);

    double verticalHeight() const;
    void setVerticalHeight(double height);

    XYZ insertPoint() const;
    void setInsertPoint(const XYZ &point);

    XYZ normal() const;
    void setNormal(const XYZ &normal);

    double height() const;
    void setHeight(double height);

    double rectangleHeight() const;
    void setRectangleHeight(double height);

    double rectangleWidth() const;
    void setRectangleWidth(double width);

    AttachmentPointType attachmentPoint() const;
    void setAttachmentPoint(AttachmentPointType type);

    DrawingDirectionType drawingDirection() const;
    void setDrawingDirection(DrawingDirectionType direction);

    std::string value() const;
    void setValue(const std::string &value);

    TextStyle *style() const;
    void setStyle(TextStyle *style);

    XYZ alignmentPoint() const;
    void setAlignmentPoint(const XYZ &point);

    double rotation() const;
    void setRotation(double rotation);

    LineSpacingStyleType lineSpacingStyle() const;
    void setLineSpacingStyle(LineSpacingStyleType style);

    double lineSpacing() const;
    void setLineSpacing(double spacing);

    BackgroundFillFlags backgroundFillFlags() const;
    void setBackgroundFillFlags(BackgroundFillFlags flags);

    double backgroundScale() const;
    void setBackgroundScale(double scale);

    Color backgroundColor() const;
    void setBackgroundColor(const Color &color);

    Transparency backgroundTransparency() const;
    void setBackgroundTransparency(const Transparency &transparency);

    TextColumn column() const;
    void setColumn(const TextColumn &column);

    bool isAnnotative() const;
    void setIsAnnotative(bool annotative);

    void assignDocument(CadDocument *doc) override;
    void unassignDocument() override;

private:
    XYZ _insertPoint;                        ///< The insertion point of the text.
    XYZ _normal;                             ///< The normal vector defining the text plane.
    XYZ _alignmentPoint;                     ///< The alignment point of the text.
    double _height;                          ///< The text height.
    double _rectangleWidth;                  ///< The width of the bounding rectangle.
    double _rectangleHeight;                 ///< The height of the bounding rectangle.
    double _horizontalWidth;                 ///< The actual horizontal width of the text.
    double _verticalHeight;                  ///< The actual vertical height of the text.
    double _rotation;                        ///< The rotation angle of the text in degrees.
    double _lineSpacing;                     ///< The spacing between lines.
    double _backgroundScale;                 ///< The scale factor for the background fill.
    AttachmentPointType _attachmentPoint;    ///< Defines how the text is attached.
    DrawingDirectionType _drawingDirection;  ///< The direction in which the text is drawn.
    std::string _value;                      ///< The text string.
    TextStyle *_style;                       ///< Pointer to the text style.
    LineSpacingStyleType _lineSpacingStyle;  ///< The type of line spacing used.
    BackgroundFillFlags _backgroundFillFlags;///< Flags for background fill options.
    Color _backgroundColor;                  ///< The background color of the text.
    Transparency _backgroundTransparency;    ///< The background transparency level.
    bool _isAnnotative;                      ///< Indicates whether the text is annotative.
    TextColumn _column;                      ///< The text column layout.
};

}// namespace dwg
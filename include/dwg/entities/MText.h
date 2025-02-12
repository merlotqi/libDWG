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

/**
 * @class MText
 * @brief Represents a multi-line text entity in a DWG/DXF drawing.
 *
 * MText allows for the representation of multi-line text with various formatting
 * options, including alignment, rotation, background fill, and column settings.
 */
class LIBDWG_API MText : public Entity
{
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
    TextStyle *_style;                       ///< Pointer to the text style.
    LineSpacingStyleType _lineSpacingStyle;  ///< The type of line spacing used.
    BackgroundFillFlags _backgroundFillFlags;///< Flags for background fill options.
    Color _backgroundColor;                  ///< The background color of the text.
    Transparency _backgroundTransparency;    ///< The background transparency level.
    bool _isAnnotative;                      ///< Indicates whether the text is annotative.

public:
    /**
     * @struct TextColumn
     * @brief Represents column settings for multi-line text.
     *
     * MText supports text being formatted into multiple columns with configurable
     * properties such as column width, count, and gutter spacing.
     */
    struct LIBDWG_API TextColumn
    {
        ColumnType ColumnType;            ///< Type of column layout.
        int ColumnCount;                  ///< The number of columns.
        bool ColumnFlowReversed;          ///< Whether the column flow is reversed.
        bool ColumnAutoHeight;            ///< Whether the column height is automatically adjusted.
        double ColumnWidth;               ///< The width of each column.
        double ColumnGutter;              ///< The spacing between columns.
        std::vector<double> ColumnHeights;///< List of individual column heights.

        /**
         * @brief Constructs a TextColumn object with default values.
         */
        TextColumn();
    };

public:
    /**
     * @brief Constructs a MText object.
     */
    MText();

    /**
     * @brief Destroys the MText object.
     */
    ~MText();

    /**
     * @brief Gets the object type of the multi-line text.
     * @return The object type as ObjectType.
     */
    virtual ObjectType objectType() const override;

    /**
     * @brief Gets the name of the multi-line text object.
     * @return The object name as a string.
     */
    virtual std::string objectName() const override;

    /**
     * @brief Gets the subclass marker associated with this object.
     * @return The subclass marker as a string.
     */
    virtual std::string subclassMarker() const override;

    /**
     * @brief Gets the insertion point of the text.
     * @return The insertion point as XYZ.
     */
    XYZ insertPoint() const;

    /**
     * @brief Sets the insertion point of the text.
     * @param point The new insertion point.
     */
    void setInsertPoint(const XYZ &point);

    /**
     * @brief Gets the normal vector defining the text plane.
     * @return The normal vector as XYZ.
     */
    XYZ normal() const;

    /**
     * @brief Sets the normal vector defining the text plane.
     * @param normal The new normal vector.
     */
    void setNormal(const XYZ &normal);

    /**
     * @brief Gets the text height.
     * @return The text height as a double.
     */
    double height() const;

    /**
     * @brief Sets the text height.
     * @param height The new text height.
     */
    void setHeight(double height);

    /**
     * @brief Gets the height of the text bounding rectangle.
     * @return The rectangle height as a double.
     */
    double rectangleHeight() const;

    /**
     * @brief Sets the height of the text bounding rectangle.
     * @param height The new rectangle height.
     */
    void setRectangleHeight(double height);

    /**
     * @brief Gets the width of the text bounding rectangle.
     * @return The rectangle width as a double.
     */
    double rectangleWidth() const;

    /**
     * @brief Sets the width of the text bounding rectangle.
     * @param width The new rectangle width.
     */
    void setRectangleWidth(double width);

    /**
     * @brief Gets the attachment point type.
     * @return The attachment point type as AttachmentPointType.
     */
    AttachmentPointType attachmentPoint() const;

    /**
     * @brief Sets the attachment point type.
     * @param type The new attachment point type.
     */
    void setAttachmentPoint(AttachmentPointType type);

    /**
     * @brief Gets the drawing direction type.
     * @return The drawing direction type as DrawingDirectionType.
     */
    DrawingDirectionType drawingDirection() const;

    /**
     * @brief Sets the drawing direction type.
     * @param direction The new drawing direction type.
     */
    void setDrawingDirection(DrawingDirectionType direction);

    /**
     * @brief Gets the text value.
     * @return The text as a string.
     */
    std::string value() const;

    /**
     * @brief Sets the text value.
     * @param value The new text content.
     */
    void setValue(const std::string &value);

    /**
     * @brief Gets the text style.
     * @return Pointer to the text style.
     */
    TextStyle *style() const;

    /**
     * @brief Sets the text style.
     * @param style Pointer to the new text style.
     */
    void setStyle(TextStyle *style);

    /**
     * @brief Gets the alignment point of the text.
     * @return The alignment point as XYZ.
     */
    XYZ alignmentPoint() const;

    /**
     * @brief Sets the alignment point of the text.
     * @param point The new alignment point.
     */
    void setAlignmentPoint(const XYZ &point);

    /**
     * @brief Gets the rotation angle of the text.
     * @return The rotation angle in degrees.
     */
    double rotation() const;

    /**
     * @brief Sets the rotation angle of the text.
     * @param rotation The new rotation angle in degrees.
     */
    void setRotation(double rotation);

    /**
     * @brief Gets the line spacing style.
     * @return The line spacing style as LineSpacingStyleType.
     */
    LineSpacingStyleType lineSpacingStyle() const;

    /**
     * @brief Sets the line spacing style.
     * @param style The new line spacing style.
     */
    void setLineSpacingStyle(LineSpacingStyleType style);

    /**
     * @brief Gets the line spacing factor.
     * @return The line spacing as a double.
     */
    double lineSpacing() const;

    /**
     * @brief Sets the line spacing factor.
     * @param spacing The new line spacing value.
     */
    void setLineSpacing(double spacing);

    /**
     * @brief Gets the background fill flags.
     * @return The background fill flags as BackgroundFillFlags.
     */
    BackgroundFillFlags backgroundFillFlags() const;

    /**
     * @brief Sets the background fill flags.
     * @param flags The new background fill flags.
     */
    void setBackgroundFillFlags(BackgroundFillFlags flags);

    /**
     * @brief Gets the background scale factor.
     * @return The background scale as a double.
     */
    double backgroundScale() const;

    /**
     * @brief Sets the background scale factor.
     * @param scale The new background scale.
     */
    void setBackgroundScale(double scale);

    /**
     * @brief Gets the background color.
     * @return The background color as Color.
     */
    Color backgroundColor() const;

    /**
     * @brief Sets the background color.
     * @param color The new background color.
     */
    void setBackgroundColor(const Color &color);

    /**
     * @brief Gets the background transparency level.
     * @return The background transparency as Transparency.
     */
    Transparency backgroundTransparency() const;

    /**
     * @brief Sets the background transparency level.
     * @param transparency The new background transparency.
     */
    void setBackgroundTransparency(const Transparency &transparency);

    /**
     * @brief Gets the text column settings.
     * @return The text column settings as TextColumn.
     */
    TextColumn column() const;

    /**
     * @brief Sets the text column settings.
     * @param column The new column settings.
     */
    void setColumn(const TextColumn &column);

    /**
     * @brief Checks if the text is annotative.
     * @return True if annotative, false otherwise.
     */
    bool isAnnotative() const;

    /**
     * @brief Sets whether the text is annotative.
     * @param annotative True if annotative, false otherwise.
     */
    void setIsAnnotative(bool annotative);
};

}// namespace dwg
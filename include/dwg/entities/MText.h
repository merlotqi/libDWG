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
#include <dwg/entities/IText.h>
#include <dwg/entities/LineSpacingStyleType.h>
#include <dwg/tables/TextStyle.h>


namespace dwg {

class LIBDWG_API MText : public Entity, IText
{
    XYZ _insertPoint;
    XYZ _normal;
    XYZ _alignmentPoint;
    double _height;
    double _rectangleWidth;
    double _rectangleHeight;
    double _horizontalWidth;
    double _verticalHeight;
    double _rotation;
    double _lineSpacing;
    double _backgroundScale;
    AttachmentPointType _attachmentPoint;
    DrawingDirectionType _drawingDirection;
    TextStyleWPtr _style;
    LineSpacingStyleType _lineSpacingStyle;
    dwg::BackgroundFillFlags _backgroundFillFlags;
    Color _backgroundColor;
    Transparency _backgroundTransparency;
    bool _isAnnotative;

public:
    struct LIBDWG_API TextColumn
    {
        dwg::ColumnType ColumnType;
        int ColumnCount;
        bool ColumnFlowReversed;
        bool ColumnAutoHeight;
        double ColumnWidth;
        double ColumnGutter;
        std::vector<double> ColumnHeights;

        TextColumn();
    };

public:
    MText();
    ~MText();

    // Override to return the object type of the Arc
    virtual dwg::ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    XYZ InsertPoint() const;
    void InsertPoint(const XYZ &);

    XYZ Normal() const;
    void Normal(const XYZ &);

    double Height() const override;
    void Height(double) override;

    double RectangleHeight() const;
    void RectangleHeight(double);

    double RectangleWidth() const;
    void RectangleWidth(double);

    AttachmentPointType AttachmentPoint() const;
    void AttachmentPoint(AttachmentPointType);

    DrawingDirectionType DrawingDirection() const;
    void DrawingDirection(DrawingDirectionType);

    CPL::String Value() const override;
    void Value(const char *) override;

    TextStylePtr Style() const override;
    void Style(TextStyle *) override;

    XYZ AlignmentPoint() const;
    void AlignmentPoint(const XYZ &);

    double HorizontalWidth() const;
    void HorizontalWidth(double);

    double VerticalHeight() const;
    void VerticalHeight(double);

    double Rotation() const;
    void Rotation(double);

    LineSpacingStyleType LineSpacingStyle() const;
    void LineSpacingStyle(LineSpacingStyleType);

    double LineSpacing() const;
    void LineSpacing(double);

    dwg::BackgroundFillFlags BackgroundFillFlags() const;
    void BackgroundFillFlags(dwg::BackgroundFillFlags);

    double BackgroundScale() const;
    void BackgroundScale(double);

    Color BackgroundColor() const;
    void BackgroundColor(const Color &);

    Transparency BackgroundTransparency() const;
    void BackgroundTransparency(const Transparency &);

    TextColumn Column() const;
    void Column(const TextColumn &);

    bool IsAnnotative() const;
    void IsAnnotative(bool);

private:
    TextColumn _column;
};
CPL_SMARTER_PTR(MText)

}// namespace dwg
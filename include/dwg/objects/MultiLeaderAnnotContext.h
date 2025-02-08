/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General  License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General  License for more details.
 *
 * You should have received a copy of the GNU General  License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <dwg/Color.h>
#include <dwg/Coordinate.h>
#include <dwg/FlowDirectionType.h>
#include <dwg/LineSpacingStyle.h>
#include <dwg/LineWeightType.h>
#include <dwg/TextAlignmentType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentPointType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/objects/LeaderLinePropertOverrideFlags.h>
#include <dwg/objects/NonGraphicalObject.h>

namespace dwg {

class TextStyle;
class LineType;
class BlockRecord;

class LIBDWG_API MultiLeaderAnnotContext : public NonGraphicalObject
{
public:
    struct StartEndPointPair
    {
        XYZ StartPoint;
        XYZ EndPoint;
    };

    struct LeaderLine
    {
        std::vector<XYZ> Points;
        int BreakInfoCount;
        int SegmentIndex;
        std::vector<StartEndPointPair> StartEndPoints;
        int Index;
        MultiLeaderPathType PathType;
        Color LineColor;
        LineType *LineType;
        LineweightType LineWeight;
        double ArrowheadSize;
        BlockRecord *ArrowHead;
        LeaderLinePropertOverrideFlags OverrideFlags;
    };

    struct LeaderRoot
    {
        bool ContentValid;
        bool Unknown;
        XYZ ConnectionPoint;
        XYZ Direction;
        std::vector<StartEndPointPair> BreakStartEndPointsPairs;
        int LeaderIndex;
        double LandingDistance;
        std::vector<LeaderLine> Lines;
        TextAttachmentDirectionType TextAttachmentDirection;
    };

public:
    MultiLeaderAnnotContext();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    std::vector<LeaderRoot> LeaderRoots() const;

    double ScaleFactor() const;
    void ScaleFactor(double);

    XYZ ContentBasePoint() const;
    void ContentBasePoint(const XYZ &);

    double TextHeight() const;
    void TextHeight(double);

    double ArrowheadSize() const;
    void ArrowheadSize(double);

    double LandingGap() const;
    void LandingGap(double);

    TextAttachmentType TextLeftAttachment() const;
    void TextLeftAttachment(TextAttachmentType);

    TextAttachmentType TextRightAttachment() const;
    void TextRightAttachment(TextAttachmentType);

    TextAlignmentType TextAlignment() const;
    void TextAlignment(TextAlignmentType);

    BlockContentConnectionType BlockContentConnection() const;
    void BlockContentConnection(BlockContentConnectionType);

    bool HasTextContents() const;
    void HasTextContents(bool);

    std::string TextLabel() const;
    void TextLabel(const std::string &);

    XYZ TextNormal() const;
    void TextNormal(const XYZ &);

    TextStyle *TextStyle();
    void TextStyle(TextStyle *);

    XYZ TextLocation() const;
    void TextLocation(const XYZ &);

    XYZ Direction() const;
    void Direction(const XYZ &);

    double TextRotation() const;
    void TextRotation(double);

    double BoundaryHeight() const;
    void BoundaryHeight(double);

    double LineSpacingFactor() const;
    void LineSpacingFactor(double);

    LineSpacingStyle LineSpacing() const;
    void LineSpacing(LineSpacingStyle);

    Color TextColor() const;
    void TextColor(const Color &);

    TextAttachmentPointType TextAttachmentPoint() const;
    void TextAttachmentPoint(TextAttachmentPointType);

    FlowDirectionType FlowDirection() const;
    void FlowDirection(FlowDirectionType);

    Color BackgroundFillColor() const;
    void BackgroundFillColor(const Color &);

    double BackgroundScaleFactor() const;
    void BackgroundScaleFactor(double);

    int BackgroundTransparency() const;
    void BackgroundTransparency(int);

    bool BackgroundFillEnabled() const;
    void BackgroundFillEnabled(bool);

    bool BackgroundMaskFillOn() const;
    void BackgroundMaskFillOn(bool);

    short ColumnType() const;
    void ColumnType(short);

    bool TextHeightAutomatic() const;
    void TextHeightAutomatic(bool);

    double ColumnWidth() const;
    void ColumnWidth(double);

    double ColumnGutter() const;
    void ColumnGutter(double);

    bool ColumnFlowReversed() const;
    void ColumnFlowReversed(bool);

    std::vector<double> ColumnSizes() const;

    bool WordBreak() const;
    void WordBreak(bool);

    bool HasContentsBlock() const;
    void HasContentsBlock(bool);

    BlockRecord *BlockContent() const;
    void BlockContent(BlockRecord *);

    XYZ BlockContentNormal() const;
    void BlockContentNormal(const XYZ &);

    XYZ BlockContentLocation() const;
    void BlockContentLocation(const XYZ &);

    XYZ BlockContentScale() const;
    void BlockContentScale(const XYZ &);

    double BlockContentRotation() const;
    void BlockContentRotation(double);

    Color BlockContentColor() const;
    void BlockContentColor(const Color &);

    Matrix4 TransformationMatrix() const;
    void TransformationMatrix(const Matrix4 &);

    XYZ BasePoint() const;
    void BasePoint(const XYZ &);

    XYZ BaseDirection() const;
    void BaseDirection(const XYZ &);

    XYZ BaseVertical() const;
    void BaseVertical(const XYZ &);

    bool NormalReversed() const;
    void NormalReversed(bool);

    TextAttachmentType TextTopAttachment() const;
    void TextTopAttachment(TextAttachmentType);

    TextAttachmentType TextBottomAttachment() const;
    void TextBottomAttachment(TextAttachmentType);
};

}// namespace dwg
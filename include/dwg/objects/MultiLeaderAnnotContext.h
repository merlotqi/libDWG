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

class DG_TextStyle;
class DG_LineType;
class DG_BlockRecord;

class LIBDWG_API DG_MultiLeaderAnnotContext : public DG_NonGraphicalObject
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
        DG_MultiLeaderPathType PathType;
        DG_Color LineColor;
        DG_LineType *LineType;
        DG_LineweightType LineWeight;
        double ArrowheadSize;
        DG_BlockRecord *ArrowHead;
        DG_LeaderLinePropertOverrideFlags OverrideFlags;
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
        DG_TextAttachmentDirectionType TextAttachmentDirection;
    };

public:
    DG_MultiLeaderAnnotContext();

    DG_ObjectType ObjectType() const override;
    std::string ObjectName() const override;
    std::string SubclassMarker() const override;

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

    DG_TextAttachmentType TextLeftAttachment() const;
    void TextLeftAttachment(DG_TextAttachmentType);

    DG_TextAttachmentType TextRightAttachment() const;
    void TextRightAttachment(DG_TextAttachmentType);

    DG_TextAlignmentType TextAlignment() const;
    void TextAlignment(DG_TextAlignmentType);

    DG_BlockContentConnectionType BlockContentConnection() const;
    void BlockContentConnection(DG_BlockContentConnectionType);

    bool HasTextContents() const;
    void HasTextContents(bool);

    std::string TextLabel() const;
    void TextLabel(const std::string &);

    XYZ TextNormal() const;
    void TextNormal(const XYZ &);

    DG_TextStyle *TextStyle();
    void TextStyle(DG_TextStyle *);

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

    DG_LineSpacingStyle LineSpacing() const;
    void LineSpacing(DG_LineSpacingStyle);

    DG_Color TextColor() const;
    void TextColor(const DG_Color &);

    DG_TextAttachmentPointType TextAttachmentPoint() const;
    void TextAttachmentPoint(DG_TextAttachmentPointType);

    DG_FlowDirectionType FlowDirection() const;
    void FlowDirection(DG_FlowDirectionType);

    DG_Color BackgroundFillColor() const;
    void BackgroundFillColor(const DG_Color &);

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

    DG_BlockRecord *BlockContent() const;
    void BlockContent(DG_BlockRecord *);

    XYZ BlockContentNormal() const;
    void BlockContentNormal(const XYZ &);

    XYZ BlockContentLocation() const;
    void BlockContentLocation(const XYZ &);

    XYZ BlockContentScale() const;
    void BlockContentScale(const XYZ &);

    double BlockContentRotation() const;
    void BlockContentRotation(double);

    DG_Color BlockContentColor() const;
    void BlockContentColor(const DG_Color &);

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

    DG_TextAttachmentType TextTopAttachment() const;
    void TextTopAttachment(DG_TextAttachmentType);

    DG_TextAttachmentType TextBottomAttachment() const;
    void TextBottomAttachment(DG_TextAttachmentType);
};

}// namespace dwg
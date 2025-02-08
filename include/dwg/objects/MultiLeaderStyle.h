/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General License for more details.
 *
 * You should have received a copy of the GNU General License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <dwg/Color.h>
#include <dwg/Coordinate.h>
#include <dwg/LineweightType.h>
#include <dwg/TextAlignmentType.h>
#include <dwg/TextAngleType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/objects/LeaderContentType.h>
#include <dwg/objects/LeaderDrawOrderType.h>
#include <dwg/objects/MultiLeaderDrawOrderType.h>
#include <dwg/objects/NonGraphicalObject.h>

namespace dwg {

class LineType;
class BlockRecord;
class TextStyle;
class BlockRecord;

class LIBDWG_API MultiLeaderStyle : public NonGraphicalObject
{
public:
    static constexpr auto DefaultName = "Standard";

    static MultiLeaderStyle *Default;

public:
    MultiLeaderStyle();
    MultiLeaderStyle(const std::string &name);

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    LeaderContentType ContentType() const;
    void ContentType(LeaderContentType);

    MultiLeaderDrawOrderType MultiLeaderDrawOrder() const;
    void MultiLeaderDrawOrder(MultiLeaderDrawOrderType);

    LeaderDrawOrderType LeaderDrawOrder() const;
    void LeaderDrawOrder(LeaderDrawOrderType);

    int MaxLeaderSegmentsPoints() const;
    void MaxLeaderSegmentsPoints(int);

    double FirstSegmentAngleConstraint() const;
    void FirstSegmentAngleConstraint(double);

    double SecondSegmentAngleConstraint() const;
    void SecondSegmentAngleConstraint(double);

    MultiLeaderPathType PathType() const;
    void PathType(MultiLeaderPathType);

    Color LineColor() const;
    void LineColor(const Color &);

    LineType *LeaderLineType() const;
    void LeaderLineType(LineType *);

    LineweightType LeaderLineWeight() const;
    void LeaderLineWeight(LineweightType);

    bool EnableLanding() const;
    void EnableLanding(bool);

    double LandingGap() const;
    void LandingGap(double);

    bool EnableDogleg() const;
    void EnableDogleg(bool);

    double LandingDistance() const;
    void LandingDistance(double);

    std::string Description() const;
    void Description(const std::string &);

    BlockRecord *Arrowhead() const;
    void Arrowhead(BlockRecord *);

    double ArrowheadSize() const;
    void ArrowheadSize(double);

    std::string DefaultTextContents() const;
    void DefaultTextContents(const std::string &);

    TextStyle *TextStyle() const;
    void TextStyle(TextStyle *);

    TextAttachmentType TextLeftAttachment() const;
    void TextLeftAttachment(TextAttachmentType);

    TextAngleType TextAngle() const;
    void TextAngle(TextAngleType);

    TextAlignmentType TextAlignment() const;
    void TextAlignment(TextAlignmentType);

    TextAlignmentType TextRightAttachment() const;
    void TextRightAttachment(TextAlignmentType);

    Color TextColor() const;
    void TextColor(const Color &);

    double TextHeight() const;
    void TextHeight(double);

    bool TextFrame() const;
    void TextFrame(bool);

    bool TextAlignAlwaysLeft() const;
    void TextAlignAlwaysLeft(bool);

    double AlignSpace() const;
    void AlignSpace(double);

    BlockRecord *BlockContent() const;
    void BlockContent(BlockRecord *);

    Color BlockContentColor() const;
    void BlockContentColor(const Color &);

    XYZ BlockContentScale() const;
    void BlockContentScale(const XYZ &);

    bool EnableBlockContentScale() const;
    void EnableBlockContentScale(bool);

    double BlockContentRotation() const;
    void BlockContentRotation(double);

    bool EnableBlockContentRotation() const;
    void EnableBlockContentRotation(bool);

    BlockContentConnectionType BlockContentConnection() const;
    void BlockContentConnection(BlockContentConnectionType);

    double ScaleFactor() const;
    void ScaleFactor(double);

    bool OverwritePropertyValue() const;
    void OverwritePropertyValue(bool);

    bool IsAnnotative() const;
    void IsAnnotative(bool);

    double BreakGapSize() const;
    void BreakGapSize(double);

    TextAttachmentDirectionType TextAttachmentDirection() const;
    void TextAttachmentDirection(TextAttachmentDirectionType);

    TextAttachmentType TextBottomAttachment() const;
    void TextBottomAttachment(TextAttachmentType);

    TextAttachmentType TextTopAttachment() const;
    void TextTopAttachment(TextAttachmentType);
};

}// namespace dwg
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
#include <dwg/LineweightType.h>
#include <dwg/TextAlignmentType.h>
#include <dwg/TextAngleType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/Coordinate.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/objects/LeaderContentType.h>
#include <dwg/objects/LeaderDrawOrderType.h>
#include <dwg/objects/NonGraphicalObject.h>

namespace dwg {

class DG_LineType;
CPL_SMARTER_PTR(DG_LineType)

class DG_BlockRecord;
CPL_SMARTER_PTR(DG_BlockRecord)

class DG_TextStyle;
CPL_SMARTER_PTR(DG_TextStyle)

class DG_BlockRecord;
CPL_SMARTER_PTR(DG_BlockRecord)

class LIBDWG_API DG_MultiLeaderStyle : public DG_NonGraphicalObject
{
public:
    static constexpr auto DefaultName = "Standard";
    
    static CPL::SmarterPtr<DG_MultiLeaderStyle> Default;
    
public:
    DG_MultiLeaderStyle();
    DG_MultiLeaderStyle(const char *name);

    DG_ObjectType ObjectType() const override;    
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;

    DG_LeaderContentType ContentType() const;
    void ContentType(DG_LeaderContentType);
    
    DG_MultiLeaderDrawOrderType MultiLeaderDrawOrder() const;
    void MultiLeaderDrawOrder(DG_MultiLeaderDrawOrderType);

    DG_LeaderDrawOrderType LeaderDrawOrder() const;
    void LeaderDrawOrder(DG_LeaderDrawOrderType);

    int MaxLeaderSegmentsPoints() const;
    void MaxLeaderSegmentsPoints(int);
    
    double FirstSegmentAngleConstraint() const;
    void FirstSegmentAngleConstraint(double);
    
    double SecondSegmentAngleConstraint() const;
    void SecondSegmentAngleConstraint(double);
    
    DG_MultiLeaderPathType PathType() const;
    void PathType(DG_MultiLeaderPathType);
    
    DG_Color LineColor() const;
    void LineColor(const DG_Color &);

    DG_LineTypePtr LeaderLineType() const;
    void LeaderLineType(DG_LineType *);
    
    DG_LineweightType LeaderLineWeight() const;
    void LeaderLineWeight(DG_LineweightType);
    
    bool EnableLanding() const;
    void EnableLanding(bool);
    
    double LandingGap() const;
    void LandingGap(double);
    
    bool EnableDogleg() const;
    void EnableDogleg(bool);
    
    double LandingDistance() const;
    void LandingDistance(double);
    
    CPL::String Description() const;
    void Description(const char *);

    DG_BlockRecordPtr Arrowhead() const;
    void Arrowhead(DG_BlockRecord *);
    
    double ArrowheadSize() const;
    void ArrowheadSize(double);
    
    CPL::String DefaultTextContents() const;
    void DefaultTextContents(const char *);

    DG_TextStylePtr TextStyle() const;
    void TextStyle(DG_TextStyle *);
    
    DG_TextAttachmentType TextLeftAttachment() const;
    void TextLeftAttachment(DG_TextAttachmentType);
    
    DG_TextAngleType TextAngle() const;
    void TextAngle(DG_TextAngleType);
    
    DG_TextAlignmentType TextAlignment() const;
    void TextAlignment(DG_TextAlignmentType);
    
    DG_TextAlignmentType TextRightAttachment() const;
    void TextRightAttachment(DG_TextAlignmentType);
    
    DG_Color TextColor() const;
    void TextColor(const DG_Color &);
    
    double TextHeight() const;
    void TextHeight(double);
    
    bool TextFrame() const;
    void TextFrame(bool);
    
    bool TextAlignAlwaysLeft() const;
    void TextAlignAlwaysLeft(bool);
    
    double AlignSpace() const;
    void AlignSpace(double);
    
    DG_BlockRecordPtr BlockContent() const;
    void BlockContent(DG_BlockRecord *);
    
    DG_Color BlockContentColor() const;
    void BlockContentColor(const DG_Color &);
    
    XYZ BlockContentScale() const;
    void BlockContentScale(const XYZ &);
    
    bool EnableBlockContentScale() const;
    void EnableBlockContentScale(bool);
    
    double BlockContentRotation() const;
    void BlockContentRotation(double);
    
    bool EnableBlockContentRotation() const;
    void EnableBlockContentRotation(bool);
    
    DG_BlockContentConnectionType BlockContentConnection() const;
    void BlockContentConnection(DG_BlockContentConnectionType);
    
    double ScaleFactor() const;
    void ScaleFactor(double);
    
    bool OverwritePropertyValue() const;
    void OverwritePropertyValue(bool);
    
    bool IsAnnotative() const;
    void IsAnnotative(bool);
    
    double BreakGapSize() const;
    void BreakGapSize(double);
    
    DG_TextAttachmentDirectionType TextAttachmentDirection() const;
    void TextAttachmentDirection(DG_TextAttachmentDirectionType);
    
    DG_TextAttachmentType TextBottomAttachment() const;
    void TextBottomAttachment(DG_TextAttachmentType);

    DG_TextAttachmentType TextTopAttachment() const;
    void TextTopAttachment(DG_TextAttachmentType);
};
CPL_SMARTER_PTR(DG_MultiLeaderStyle)

}// namespace dwg
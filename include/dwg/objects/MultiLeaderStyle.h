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
#include <dwg/base/Coordinate.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/objects/LeaderContentType.h>
#include <dwg/objects/LeaderDrawOrderType.h>
#include <dwg/objects/NonGraphicalObject.h>


namespace dwg {


class MultiLeaderStyle : NonGraphicalObject
{
public:
    static constexpr auto DefaultName = "Standard";
    static MultiLeaderStyle
            Default;// { get { return new MultiLeaderStyle(DefaultName); } }

    dwg::ObjectType ObjectType() const { return ObjectType::UNLISTED; }
    CPL::String ObjectName() const { return DxfFileToken::ObjectMLeaderStyle; }
    CPL::String SubclassMarker() const
    {
        return DxfSubclassMarker::MLeaderStyle;
    }


    // 170
    LeaderContentType ContentType;
    // 171
    MultiLeaderDrawOrderType MultiLeaderDrawOrder;
    // 172
    LeaderDrawOrderType LeaderDrawOrder;
    // 90
    int MaxLeaderSegmentsPoints;
    // 40
    double FirstSegmentAngleConstraint;
    // 41
    double SecondSegmentAngleConstraint;
    // 173
    MultiLeaderPathType PathType;
    // 91
    Color LineColor;
    // DxfReferenceType.Handle, 340
    unsigned long long LeaderLineTypeHandle;
    // 92
    LineweightType LeaderLineWeight;
    // 290
    bool EnableLanding;
    // 42
    double LandingGap;
    // 291
    bool EnableDogleg;
    // 43
    double LandingDistance;
    // 3
    CPL::String Description;
    // DxfReferenceType.Handle, 341
    unsigned long long ArrowheadHandle;
    // 44
    double ArrowheadSize;
    // 300
    CPL::String DefaultTextContents;
    // DxfReferenceType.Handle, 342
    unsigned long long TextStyleHandle;
    // 174
    TextAttachmentType TextLeftAttachment;
    // 175
    TextAngleType TextAngle;
    // 176
    TextAlignmentType TextAlignment;
    // 178
    TextAttachmentType TextRightAttachment;
    // 93
    Color TextColor;
    // 45
    double TextHeight;
    // 292
    bool TextFrame;
    // 297
    bool TextAlignAlwaysLeft;
    // 46
    double AlignSpace;
    // DxfReferenceType.Handle, 343
    unsigned long long BlockContentHandle;
    // 94
    Color BlockContentColor;
    // 47, 49, 140
    XYZ BlockContentScale;
    // 293
    bool EnableBlockContentScale;
    // DxfReferenceType.IsAngle, 141
    double BlockContentRotation;
    // 294
    bool EnableBlockContentRotation;
    // 177
    BlockContentConnectionType BlockContentConnection;
    // 142
    double ScaleFactor;
    // 295
    bool OverwritePropertyValue;
    // 296
    bool IsAnnotative;
    // 143
    double BreakGapSize;
    // 271
    TextAttachmentDirectionType TextAttachmentDirection;
    // 272
    TextAttachmentType TextBottomAttachment;
    // 273
    TextAttachmentType TextTopAttachment;

public:
    MultiLeaderStyle() {}
    MultiLeaderStyle(const CPL::String &name) : NonGraphicalObject(name) {}
};


MultiLeaderStyle MultiLeaderStyle::Default =
        MultiLeaderStyle(MultiLeaderStyle::DefaultName);

}// namespace dwg
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

#include <dwg/FlowDirectionType.h>
#include <dwg/LineSpacingStyle.h>
#include <dwg/LineweightType.h>
#include <dwg/TextAlignmentType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentPointType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/objects/LeaderLinePropertOverrideFlags.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/base/Color.h>
#include <dwg/base/Coordinate.h>
#include <dwg/base/Matrix.h>

namespace dwg {

class MultiLeaderAnnotContext : public NonGraphicalObject
{
public:
    MultiLeaderAnnotContext();

    dwg::ObjectType ObjectType() const { return ObjectType::UNLISTED; }
    CPL::String ObjectName() const
    {
        return DxfFileToken::ObjectMLeaderContextData;
    }
    CPL::String SubclassMarker() const
    {
        return DxfSubclassMarker::MultiLeaderAnnotContext;
    }

    struct StartEndPointPair
    {
        XYZ StartPoint;// 12,22,32
        XYZ EndPoint;  // 13,23,33
    };

    struct LeaderLine
    {
        std::vector<XYZ> Points;
        int BreakInfoCount;
        int SegmentIndex;
        std::vector<StartEndPointPair> StartEndPoints;
        int Index;                             // 91
        MultiLeaderPathType PathType;// 170
        Color LineColor;                       // 92
        LineType LineType;
        LineweightType LineWeight;// 171
        double ArrowheadSize;     // 40
        BlockRecord ArrowHead;
        LeaderLinePropertOverrideFlags OverrideFlags;
    };

    struct LeaderRoot
    {
        bool ContentValid;  // 290
        bool Unknown;       // 291
        XYZ ConnectionPoint;// 10, 20, 30
        XYZ Direction;      // 11, 21, 31
        std::vector<StartEndPointPair> BreakStartEndPointsPairs;
        int LeaderIndex;       // 90
        double LandingDistance;// 40
        std::vector<LeaderLine> Lines;
        TextAttachmentDirectionType TextAttachmentDirection;// 271
    };

    std::vector<LeaderRoot> LeaderRoots;
    double ScaleFactor;                                         // 40
    XYZ ContentBasePoint;                                       // 10,20,30
    double TextHeight;                                          // 41
    double ArrowheadSize;                                       // 140
    double LandingGap;                                          // 145
    TextAttachmentType TextLeftAttachment;                      // 174
    TextAttachmentType TextRightAttachment;                     // 175
    TextAlignmentType TextAlignment;                            // 176
    BlockContentConnectionType BlockContentConnection;// 177
    bool HasTextContents;                                       // 290
    CPL::String TextLabel;                                      // 304
    XYZ TextNormal;                                             // 11,21,31
    TextStyle TextStyle;                                // 340

    XYZ TextLocation;// 12,22,32
    XYZ Direction;   // 13,23,33

    double TextRotation;         // 42
    double BoundaryHeight;       //44
    double LineSpacingFactor;    // 45
    LineSpacingStyle LineSpacing;// 170

    Color TextColor;                            // 90
    TextAttachmentPointType TextAttachmentPoint;// 171
    FlowDirectionType FlowDirection;            // 172
    Color BackgroundFillColor;                  // 91
    double BackgroundScaleFactor;               // 141
    int BackgroundTransparency;                 // 92
    bool BackgroundFillEnabled;                 // 291
    bool BackgroundMaskFillOn;                  // 292
    short ColumnType;                           // 173
    bool TextHeightAutomatic;                   // 293
                                                // 142
    double ColumnWidth;
    // 143
    double ColumnGutter;
    // 294
    bool ColumnFlowReversed;
    // 144
    std::vector<double> ColumnSizes;
    // 295
    bool WordBreak;
    // 296
    bool HasContentsBlock;
    // 341
    BlockRecord BlockContent;
    // 14, 24, 34
    XYZ BlockContentNormal;
    // 15, 25, 35
    XYZ BlockContentLocation;
    // 16, 26, 36
    XYZ BlockContentScale;
    // 46
    double BlockContentRotation;
    // 93
    Color BlockContentColor;
    // 93
    Matrix4 TransformationMatrix;
    // 110, 120, 130
    XYZ BasePoint;
    // 111, 121, 131
    XYZ BaseDirection;
    // 112, 122, 132
    XYZ BaseVertical;
    // 297
    bool NormalReversed;
    // 273
    TextAttachmentType TextTopAttachment;
    // 272
    TextAttachmentType TextBottomAttachment;
};

}// namespace dwg
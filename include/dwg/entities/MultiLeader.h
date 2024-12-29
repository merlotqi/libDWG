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

#include <dwg/entities/AttributeDefinition.h>
#include <dwg/entities/Entity.h>
#include <dwg/LineWeightType.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/entities/MultiLeaderPropertyOverrideFlags.h>
#include <dwg/objects/LeaderContentType.h>
#include <dwg/objects/MultiLeaderAnnotContext.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/LineType.h>
#include <dwg/base/Color.h>


#include <dwg/TextAlignmentType.h>
#include <dwg/TextAngleType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentPointType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/tables/TextStyle.h>


namespace dwg {

class MultiLeader : public Entity
{
public:
    MultiLeader();
    virtual ~MultiLeader();

    class BlockAttribute
    {
    public:
        AttributeDefinition *attributeDefinition;// 330
        short Index;                             // 177

        double width;    // 44
        std::string text;// 302
    };

    MultiLeaderAnnotContext *contextData;
    MultiLeaderStyle *style;

    MultiLeaderPropertyOverrideFlags propertyOverrideFlags;// 90
    MultiLeaderPathType pathType;                          // 170
    Color lineColoe;                                       // 91

    LineType leaderLineType;// 341
    LineweightType leaderLineWeight;// 171

    bool enableLanding;    // 290
    bool enableDogleg;     // 291
    double landingDistance;// 41

    BlockRecord *arrowhead;// 342

    double arrowheadSize;// 42

    LeaderContentType contentType;// 172


    TextStyle *textStyle;          // 343
    TextAttachmentType textLeftAttachment; // 173
    TextAttachmentType textRightAttachment;// 95
    TextAngleType textAngle;               // 174
    TextAlignmentType textAlignment;       // 175
    Color textColor;                       // 92
    bool textFrame;                        // 292

    BlockRecord *blockContent;                // 344
    Color blockContentColor;                          // 93
    XYZ blockContentScale;                            // 10, 20, 30
    double blockContentRotation;                      // 43
    BlockContentConnectionType blockContentConnection;// 176


    bool enableAnnotationScale = 293;

    std::vector<BlockAttribute> blockAttributes;

    bool textDirectionNegative;                         // 294
    short textAligninIPE;                               // 178
    TextAttachmentPointType textAttachmentPoint;        // 179
    double scaleFactor;                                 // 45
    TextAttachmentDirectionType textAttachmentDirection;// 271
    TextAttachmentType textBottomAttachment;            // 272
    TextAttachmentType textTopAttachment;               // 273


    bool extendedToText;
};


}// namespace dwg
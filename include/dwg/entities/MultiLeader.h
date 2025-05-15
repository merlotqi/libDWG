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
#include <dwg/LineWeightType.h>
#include <dwg/TextAlignmentType.h>
#include <dwg/TextAngleType.h>
#include <dwg/TextAttachmentDirectionType.h>
#include <dwg/TextAttachmentPointType.h>
#include <dwg/TextAttachmentType.h>
#include <dwg/entities/BlockContentConnectionType.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/MultiLeaderPathType.h>
#include <dwg/entities/MultiLeaderPropertyOverrideFlags.h>
#include <dwg/objects/LeaderContentType.h>

namespace dwg {

class AttributeDefinition;
class MultiLeaderStyle;
class MultiLeaderAnnotContext;
class BlockRecord;
class TextStyle;

class LIBDWG_API MultiLeader : public Entity
{
public:
    class BlockAttribute
    {
    public:
        AttributeDefinition *AttributeDefinition;///< Pointer to the attribute definition.
        short Index;                             ///< Index of the attribute within the block.
        double Width;                            ///< Width of the attribute text.
        std::string Text;                        ///< The actual text content of the attribute.
    };

public:
    MultiLeader();
    virtual ~MultiLeader();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    MultiLeaderAnnotContext *contextData() const;
    void setContextData(MultiLeaderAnnotContext *context);

    MultiLeaderStyle *style() const;
    void setStyle(MultiLeaderStyle *style);

    MultiLeaderPropertyOverrideFlags propertyOverrideFlags() const;
    void setPropertyOverrideFlags(MultiLeaderPropertyOverrideFlags flags);

    MultiLeaderPathType pathType() const;
    void setPathType(MultiLeaderPathType pathType);

    Color lineColor() const;
    void setLineColor(const Color &color);

    LineType *leaderLineType() const;
    void setLeaderLineType(LineType *lineType);

    LineweightType leaderLineLength() const;
    void setLeaderLineLength(LineweightType length);

    bool enableLanding() const;
    void setEnableLanding(bool enable);

    bool enableDogleg() const;
    void setEnableDogleg(bool enable);

    double landingDistance() const;
    void setLandingDistance(double distance);

    BlockRecord *arrowhead() const;
    void setArrowhead(BlockRecord *block);

    double arrowheadSize() const;
    void setArrowheadSize(double size);

    LeaderContentType contentType() const;
    void setContentType(LeaderContentType type);

    TextStyle *textStyle() const;
    void setTextStyle(TextStyle *style);

    BlockRecord *blockContent() const;
    void setBlockContent(BlockRecord *block);

    bool enableAnnotationScale() const;
    void setEnableAnnotationScale(bool enable);

    std::vector<BlockAttribute> blockAttributes() const;
    void setBlockAttributes(const std::vector<BlockAttribute> &attributes);

    bool textDirectionNegative() const;
    void setTextDirectionNegative(bool negative);

    short textAligninIPE() const;
    void setTextAligninIPE(short alignment);

    TextAttachmentPointType textAttachmentPoint() const;
    void setTextAttachmentPoint(TextAttachmentPointType point);
};

}// namespace dwg
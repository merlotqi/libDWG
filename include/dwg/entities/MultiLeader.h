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

/**
 * @class MultiLeader
 * @brief Represents a MultiLeader entity in a DWG/DXF drawing.
 *
 * A MultiLeader consists of leader lines, arrowheads, and associated content, 
 * such as text or block references, commonly used for annotations.
 */
class LIBDWG_API MultiLeader : public Entity
{
public:
    /**
     * @class BlockAttribute
     * @brief Represents an attribute within a block content of the MultiLeader.
     */
    class BlockAttribute
    {
    public:
        AttributeDefinition *AttributeDefinition;///< Pointer to the attribute definition.
        short Index;                             ///< Index of the attribute within the block.
        double Width;                            ///< Width of the attribute text.
        std::string Text;                        ///< The actual text content of the attribute.
    };

public:
    /**
     * @brief Default constructor.
     */
    MultiLeader();

    /**
     * @brief Destructor.
     */
    virtual ~MultiLeader();

    /**
     * @brief Gets the annotation context data associated with this MultiLeader.
     * @return A pointer to the annotation context data.
     */
    MultiLeaderAnnotContext *contextData() const;

    /**
     * @brief Sets the annotation context data.
     * @param context Pointer to the new annotation context data.
     */
    void setContextData(MultiLeaderAnnotContext *context);

    /**
     * @brief Gets the MultiLeader style.
     * @return A pointer to the MultiLeader style.
     */
    MultiLeaderStyle *style() const;

    /**
     * @brief Sets the MultiLeader style.
     * @param style Pointer to the new MultiLeader style.
     */
    void setStyle(MultiLeaderStyle *style);

    /**
     * @brief Gets the property override flags for this MultiLeader.
     * @return The override flags.
     */
    MultiLeaderPropertyOverrideFlags propertyOverrideFlags() const;

    /**
     * @brief Sets the property override flags.
     * @param flags The new override flags.
     */
    void setPropertyOverrideFlags(MultiLeaderPropertyOverrideFlags flags);

    /**
     * @brief Gets the path type of the leader lines.
     * @return The path type.
     */
    MultiLeaderPathType pathType() const;

    /**
     * @brief Sets the path type of the leader lines.
     * @param pathType The new path type.
     */
    void setPathType(MultiLeaderPathType pathType);

    /**
     * @brief Gets the leader line color.
     * @return The color of the leader line.
     */
    Color lineColor() const;

    /**
     * @brief Sets the leader line color.
     * @param color The new color.
     */
    void setLineColor(const Color &color);

    /**
     * @brief Gets the leader line type.
     * @return A pointer to the leader line type.
     */
    LineType *leaderLineType() const;

    /**
     * @brief Sets the leader line type.
     * @param lineType Pointer to the new leader line type.
     */
    void setLeaderLineType(LineType *lineType);

    /**
     * @brief Gets the leader line length.
     * @return The leader line length.
     */
    LineweightType leaderLineLength() const;

    /**
     * @brief Sets the leader line length.
     * @param length The new leader line length.
     */
    void setLeaderLineLength(LineweightType length);

    /**
     * @brief Checks if landing is enabled.
     * @return True if landing is enabled, false otherwise.
     */
    bool enableLanding() const;

    /**
     * @brief Enables or disables landing.
     * @param enable True to enable, false to disable.
     */
    void setEnableLanding(bool enable);

    /**
     * @brief Checks if dogleg is enabled.
     * @return True if dogleg is enabled, false otherwise.
     */
    bool enableDogleg() const;

    /**
     * @brief Enables or disables dogleg.
     * @param enable True to enable, false to disable.
     */
    void setEnableDogleg(bool enable);

    /**
     * @brief Gets the landing distance.
     * @return The landing distance.
     */
    double landingDistance() const;

    /**
     * @brief Sets the landing distance.
     * @param distance The new landing distance.
     */
    void setLandingDistance(double distance);

    /**
     * @brief Gets the arrowhead block reference.
     * @return A pointer to the arrowhead block record.
     */
    BlockRecord *arrowhead() const;

    /**
     * @brief Sets the arrowhead block reference.
     * @param block Pointer to the new arrowhead block record.
     */
    void setArrowhead(BlockRecord *block);

    /**
     * @brief Gets the arrowhead size.
     * @return The size of the arrowhead.
     */
    double arrowheadSize() const;

    /**
     * @brief Sets the arrowhead size.
     * @param size The new arrowhead size.
     */
    void setArrowheadSize(double size);

    /**
     * @brief Gets the MultiLeader content type.
     * @return The content type.
     */
    LeaderContentType contentType() const;

    /**
     * @brief Sets the MultiLeader content type.
     * @param type The new content type.
     */
    void setContentType(LeaderContentType type);

    /**
     * @brief Gets the text style.
     * @return A pointer to the text style.
     */
    TextStyle *textStyle() const;

    /**
     * @brief Sets the text style.
     * @param style Pointer to the new text style.
     */
    void setTextStyle(TextStyle *style);

    /**
     * @brief Gets the block content.
     * @return A pointer to the block content.
     */
    BlockRecord *blockContent() const;

    /**
     * @brief Sets the block content.
     * @param block Pointer to the new block content.
     */
    void setBlockContent(BlockRecord *block);

    /**
     * @brief Checks if annotation scale is enabled.
     * @return True if annotation scale is enabled, false otherwise.
     */
    bool enableAnnotationScale() const;

    /**
     * @brief Enables or disables annotation scale.
     * @param enable True to enable, false to disable.
     */
    void setEnableAnnotationScale(bool enable);

    /**
     * @brief Gets the block attributes.
     * @return A vector containing the block attributes.
     */
    std::vector<BlockAttribute> blockAttributes() const;

    /**
     * @brief Sets the block attributes.
     * @param attributes The new block attributes.
     */
    void setBlockAttributes(const std::vector<BlockAttribute> &attributes);

    /**
     * @brief Checks if text direction is negative.
     * @return True if the text direction is negative, false otherwise.
     */
    bool textDirectionNegative() const;

    /**
     * @brief Sets the text direction.
     * @param negative True to set the direction as negative, false otherwise.
     */
    void setTextDirectionNegative(bool negative);

    /**
     * @brief Gets the text alignment in IPE (Insertion Point Editing).
     * @return The text alignment value.
     */
    short textAligninIPE() const;

    /**
     * @brief Sets the text alignment in IPE.
     * @param alignment The new text alignment value.
     */
    void setTextAligninIPE(short alignment);

    /**
     * @brief Gets the text attachment point.
     * @return The text attachment point type.
     */
    TextAttachmentPointType textAttachmentPoint() const;

    /**
     * @brief Sets the text attachment point.
     * @param point The new text attachment point type.
     */
    void setTextAttachmentPoint(TextAttachmentPointType point);
};

}// namespace dwg
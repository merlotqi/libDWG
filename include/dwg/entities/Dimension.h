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

#include <dwg/entities/AttachmentPointType.h>
#include <dwg/entities/DimensionType.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/LineSpacingStyleType.h>

namespace dwg {

class BlockRecord;
class DimensionStyle;
class Line;
class MText;
class Point;

// The Dimension class represents a dimension entity in a CAD system,
// providing properties and methods for dimension management and manipulation.
class LIBDWG_API Dimension : public Entity
{
    RTTR_ENABLE(Entity)

public:
    Dimension();
    Dimension(DimensionType type);
    virtual ~Dimension();

public:
    virtual std::string subclassMarker() const override;

    AttachmentPointType attachmentPoint() const;
    void setAttachmentPoint(AttachmentPointType value);

    BlockRecord *block() const;
    void setBlock(BlockRecord *value);

    const XYZ &definitionPoint() const;
    void setDefinitionPoint(const XYZ &value);

    DimensionTypes flags() const;
    void setFlags(DimensionTypes value);

    bool flipArrow1() const;
    void setFlipArrow1(bool value);

    bool flipArrow2() const;
    void setFlipArrow2(bool value);

    double horizontalDirection() const;
    void setHorizontalDirection(double value);

    const XYZ &insertionPoint() const;
    void setInsertionPoint(const XYZ &value);

    bool isAngular() const;

    bool isTextUserDefinedLocation() const;
    void setIsTextUserDefinedLocation(bool value);

    double lineSpacingFactor() const;
    void setLineSpacingFactor(double value);

    LineSpacingStyleType lineSpacingStyle() const;
    void setLineSpacingStyle(LineSpacingStyleType value);

    virtual double measurement() const = 0;

    const XYZ &normal() const;
    void setNormal(const XYZ &value);

    DimensionStyle *style() const;
    void setStyle(DimensionStyle *value);

    const std::string &text() const;
    void setText(const std::string &value);

    const XYZ &textMiddlePoint() const;
    void setTextMiddlePoint(const XYZ &value);

    double textRotation() const;
    void setTextRotation(double value);

    unsigned char version() const;
    void setVersion(unsigned char value);

    std::string measurementText() const;
    std::string measurementText(DimensionStyle *style) const;

    virtual void updateBlock();

    void assignDocument(CadDocument *doc) override;
    void unassignDocument() override;

protected:
    static Entity *dimensionLine(const XYZ &start, const XYZ &end, DimensionStyle *style);
    static Line *extensionLine(const XYZ &start, const XYZ &end, DimensionStyle *style, LineType *linetype);
    void angularBlock(double radius, const XY &centerRef, const XY &ref1, double minOffset, bool drawRef2);
    std::vector<Entity *> centerCross(const XYZ &center, double radius, DimensionStyle *style);
    void createBlock();
    Point *createDefinitionPoint(const XYZ &location);
    MText *createTextEntity(const XYZ &insertPoint, const std::string &text);
    Entity *dimensionArrow(const XYZ &insertPoint, const XYZ &dir, DimensionStyle *style, BlockRecord *record);
    Line *dimensionRadialLine(const XY &start, const XY &end, double rotation, short reversed);
    void tableOnRemove(CadObject *item);
    std::string generateBlockName() const;

protected:
    unsigned char _version;                // The version of the dimension entity
    BlockRecord *_block;                   // Pointer to the block associated with the dimension
    XYZ _definitionPoint;                  // The definition point (e.g., the base point) of the dimension
    XYZ _textMiddlePoint;                  // The middle point of the dimension text
    XYZ _insertionPoint;                   // The insertion point of the dimension entity
    XYZ _normal;                           // The normal vector for the dimension (usually related to the drawing plane)
    DimensionTypes _flags;                 // Flags indicating dimension-specific settings or properties
    AttachmentPointType _attachmentPoint;  // The attachment point type for the dimension text
    LineSpacingStyleType _lineSpacingStyle;// The line spacing style for text
    double _lineSpacingFactor;             // The factor affecting the line spacing for text
    bool _flipArrow1;                      // Boolean indicating if the first arrow is flipped
    bool _flipArrow2;                      // Boolean indicating if the second arrow is flipped
    std::string _text;                     // The text displayed in the dimension
    double _textRotation;                  // Rotation angle for the dimension text
    double _horizontalDirection;           // Horizontal direction for text alignment
    DimensionStyle *_dimStyle;             // Pointer to the associated dimension style
};

}// namespace dwg
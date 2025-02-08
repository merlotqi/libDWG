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

// The Dimension class represents a dimension entity in a CAD system,
// providing properties and methods for dimension management and manipulation.
class LIBDWG_API Dimension : public Entity
{
    unsigned char _version;// The version of the dimension entity
    BlockRecord *_block;// Pointer to the block associated with the dimension
    XYZ _definitionPoint;// The definition point (e.g., the base point) of the dimension
    XYZ _textMiddlePoint;// The middle point of the dimension text
    XYZ _insertionPoint; // The insertion point of the dimension entity
    XYZ _normal;// The normal vector for the dimension (usually related to the drawing plane)
    DimensionType
            _flags;// Flags indicating dimension-specific settings or properties
    AttachmentPointType
            _attachmentPoint;// The attachment point type for the dimension text
    LineSpacingStyleType _lineSpacingStyle;// The line spacing style for text
    double _lineSpacingFactor;// The factor affecting the line spacing for text
    bool _flipArrow1;    // Boolean indicating if the first arrow is flipped
    bool _flipArrow2;    // Boolean indicating if the second arrow is flipped
    std::string _text;   // The text displayed in the dimension
    double _textRotation;// Rotation angle for the dimension text
    double _horizontalDirection; // Horizontal direction for text alignment
    DimensionStyle *_dimStyle;// Pointer to the associated dimension style

public:
    // Default constructor for the Dimension class
    Dimension();
    virtual ~Dimension();

public:
    // Override to return the subclass marker associated with this object
    virtual std::string subclassMarker() const override;

    // Getter and setter for the version of the dimension
    unsigned char version() const;
    void setVersion(unsigned char value);

    // Getter and setter for the associated block record
    BlockRecord *block() const;
    void setBlock(BlockRecord *value);

    // Getter and setter for the definition point of the dimension
    XYZ definitionPoint() const;
    void setDefinitionPoint(const XYZ &value);

    // Getter and setter for the middle point of the dimension text
    XYZ textMiddlePoint() const;
    void setTextMiddlePoint(const XYZ &value);

    // Getter and setter for the insertion point of the dimension
    XYZ insertionPoint() const;
    void setInsertionPoint(const XYZ &value);

    // Getter and setter for the normal vector of the dimension
    XYZ normal() const;
    void setNormal(const XYZ &value);

    // Getter and setter for the flags (dimension-specific properties)
    DimensionType flags() const;
    void setFlags(DimensionType value);

    // Getter and setter for the attachment point type of the dimension text
    AttachmentPointType attachmentPoint() const;
    void setAttachmentPoint(AttachmentPointType value);

    // Getter and setter for the line spacing style of the dimension text
    LineSpacingStyleType lineSpacingStyle() const;
    void setLineSpacingStyle(LineSpacingStyleType value);

    // Getter and setter for the line spacing factor (affects text spacing)
    double lineSpacingFactor() const;
    void setLineSpacingFactor(double value);

    // Getter and setter for flipping the first arrow of the dimension
    bool flipArrow1() const;
    void setFlipArrow1(bool value);

    // Getter and setter for flipping the second arrow of the dimension
    bool flipArrow2() const;
    void setFlipArrow2(bool value);

    // Getter and setter for the dimension text
    const std::string &text() const;
    void setText(const std::string &value);

    // Getter and setter for the text rotation angle
    double textRotation() const;
    void setTextRotation(double value);

    // Getter and setter for the horizontal direction of the text
    double horizontalDirection() const;
    void setHorizontalDirection(double value);

    // Getter and setter for the associated dimension style
    DimensionStyle *dimStyle() const;
    void setDimStyle(DimensionStyle *value);

    // Pure virtual method that must be implemented by derived classes to calculate the dimension measurement
    virtual double measurement() const = 0;

public:
    // Determines if the text position is user-defined
    bool isTextUserDefinedLocation() const;
    void setIsTextUserDefinedLocation(bool value);
};

}// namespace dwg
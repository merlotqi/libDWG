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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/entities/Dimension.h>

namespace dwg {

Dimension::Dimension() {}

Dimension::Dimension(DimensionType type)
{
    _flags = type;
    _flags |= DimensionType::BlockReference;
}

Dimension::~Dimension() {}

std::string Dimension::subclassMarker() const { return DxfSubclassMarker::Dimension; }

unsigned char Dimension::version() const { return _version; }

void Dimension::setVersion(unsigned char value) { _version = value; }

BlockRecord *Dimension::block() const { return _block; }

void Dimension::setBlock(BlockRecord *value) { _block = value; }

XYZ Dimension::definitionPoint() const { return _definitionPoint; }

void Dimension::setDefinitionPoint(const XYZ &value) { _definitionPoint = value; }

XYZ Dimension::textMiddlePoint() const { return _textMiddlePoint; }

void Dimension::setTextMiddlePoint(const XYZ &value) { _textMiddlePoint = value; }

XYZ Dimension::insertionPoint() const { return _insertionPoint; }

void Dimension::setInsertionPoint(const XYZ &value) { _insertionPoint = value; }

XYZ Dimension::normal() const { return _normal; }

void Dimension::setNormal(const XYZ &value) { _normal = value; }

DimensionTypes Dimension::flags() const { return _flags; }

void Dimension::setFlags(DimensionTypes value) { _flags = value; }

AttachmentPointType Dimension::attachmentPoint() const { return _attachmentPoint; }

void Dimension::setAttachmentPoint(AttachmentPointType value) { _attachmentPoint = value; }

LineSpacingStyleType Dimension::lineSpacingStyle() const { return _lineSpacingStyle; }

void Dimension::setLineSpacingStyle(LineSpacingStyleType value) { _lineSpacingStyle = value; }

double Dimension::lineSpacingFactor() const { return _lineSpacingFactor; }

void Dimension::setLineSpacingFactor(double value) { _lineSpacingFactor = value; }

bool Dimension::flipArrow1() const { return _flipArrow1; }

void Dimension::setFlipArrow1(bool value) { _flipArrow1 = value; }

bool Dimension::flipArrow2() const { return _flipArrow2; }

void Dimension::setFlipArrow2(bool value) { _flipArrow2 = value; }

const std::string &Dimension::text() const { return _text; }

void Dimension::setText(const std::string &value) { _text = value; }

double Dimension::textRotation() const { return _textRotation; }

void Dimension::setTextRotation(double value) { _textRotation = value; }

double Dimension::horizontalDirection() const { return _horizontalDirection; }

void Dimension::setHorizontalDirection(double value) { _horizontalDirection = value; }

DimensionStyle *Dimension::dimStyle() const { return _dimStyle; }

void Dimension::setDimStyle(DimensionStyle *value) {}

bool Dimension::isTextUserDefinedLocation() const { return _flags & DimensionType::TextUserDefinedLocation; }

void Dimension::setIsTextUserDefinedLocation(bool value) {}

}// namespace dwg

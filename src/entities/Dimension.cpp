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
#include <dwg/attributes/DxfCodeValueAttribute_p.h>
#include <dwg/attributes/DxfSubClassAttribute_p.h>
#include <dwg/entities/Dimension.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>

namespace dwg {

Dimension::Dimension() {}

Dimension::Dimension(DimensionType type)
{
    _flags = type;
    _flags |= DimensionType::BlockReference;
}

Dimension::~Dimension() {}

std::string Dimension::subclassMarker() const
{
    return DxfSubclassMarker::Dimension;
}

unsigned char Dimension::version() const
{
    return _version;
}

void Dimension::setVersion(unsigned char value)
{
    _version = value;
}

std::string Dimension::measurementText() const
{
    return std::string();
}

std::string Dimension::measurementText(DimensionStyle *style) const
{
    return std::string();
}

void Dimension::updateBlock() {}

BlockRecord *Dimension::block() const
{
    return _block;
}

void Dimension::setBlock(BlockRecord *value)
{
    _block = value;
}

const XYZ &Dimension::definitionPoint() const
{
    return _definitionPoint;
}

void Dimension::setDefinitionPoint(const XYZ &value)
{
    _definitionPoint = value;
}

const XYZ &Dimension::textMiddlePoint() const
{
    return _textMiddlePoint;
}

void Dimension::setTextMiddlePoint(const XYZ &value)
{
    _textMiddlePoint = value;
}

const XYZ &Dimension::insertionPoint() const
{
    return _insertionPoint;
}

void Dimension::setInsertionPoint(const XYZ &value)
{
    _insertionPoint = value;
}

bool Dimension::isAngular() const
{
    return false;
}

const XYZ &Dimension::normal() const
{
    return _normal;
}

void Dimension::setNormal(const XYZ &value)
{
    _normal = value;
}

DimensionTypes Dimension::flags() const
{
    return _flags;
}

void Dimension::setFlags(DimensionTypes value)
{
    _flags = value;
}

AttachmentPointType Dimension::attachmentPoint() const
{
    return _attachmentPoint;
}

void Dimension::setAttachmentPoint(AttachmentPointType value)
{
    _attachmentPoint = value;
}

LineSpacingStyleType Dimension::lineSpacingStyle() const
{
    return _lineSpacingStyle;
}

void Dimension::setLineSpacingStyle(LineSpacingStyleType value)
{
    _lineSpacingStyle = value;
}

double Dimension::lineSpacingFactor() const
{
    return _lineSpacingFactor;
}

void Dimension::setLineSpacingFactor(double value)
{
    _lineSpacingFactor = value;
}

bool Dimension::flipArrow1() const
{
    return _flipArrow1;
}

void Dimension::setFlipArrow1(bool value)
{
    _flipArrow1 = value;
}

bool Dimension::flipArrow2() const
{
    return _flipArrow2;
}

void Dimension::setFlipArrow2(bool value)
{
    _flipArrow2 = value;
}

const std::string &Dimension::text() const
{
    return _text;
}

void Dimension::setText(const std::string &value)
{
    _text = value;
}

double Dimension::textRotation() const
{
    return _textRotation;
}

void Dimension::setTextRotation(double value)
{
    _textRotation = value;
}

double Dimension::horizontalDirection() const
{
    return _horizontalDirection;
}

void Dimension::setHorizontalDirection(double value)
{
    _horizontalDirection = value;
}

DimensionStyle *Dimension::style() const
{
    return _dimStyle;
}

void Dimension::setStyle(DimensionStyle *value) {}

bool Dimension::isTextUserDefinedLocation() const
{
    return _flags & DimensionType::TextUserDefinedLocation;
}

void Dimension::setIsTextUserDefinedLocation(bool value) {}

void Dimension::assignDocument(CadDocument *doc) {}

void Dimension::unassignDocument() {}

Entity *Dimension::dimensionLine(const XYZ &start, const XYZ &end, DimensionStyle *style)
{
    return nullptr;
}

Line *Dimension::extensionLine(const XYZ &start, const XYZ &end, DimensionStyle *style, LineType *linetype)
{
    return nullptr;
}

void Dimension::angularBlock(double radius, const XY &centerRef, const XY &ref1, double minOffset, bool drawRef2) {}

std::vector<Entity *> Dimension::centerCross(const XYZ &center, double radius, DimensionStyle *style)
{
    return std::vector<Entity *>();
}

void Dimension::createBlock() {}

Point *Dimension::createDefinitionPoint(const XYZ &location)
{
    return nullptr;
}

MText *Dimension::createTextEntity(const XYZ &insertPoint, const std::string &text)
{
    return nullptr;
}

Entity *Dimension::dimensionArrow(const XYZ &insertPoint, const XYZ &dir, DimensionStyle *style, BlockRecord *record)
{
    return nullptr;
}

Line *Dimension::dimensionRadialLine(const XY &start, const XY &end, double rotation, short reversed)
{
    return nullptr;
}

void Dimension::tableOnRemove(CadObject *item) {}

std::string Dimension::generateBlockName() const
{
    return std::string();
}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<Dimension>("Dimension")(
            metadata("DxfName", DxfFileToken::EntityDimension),
            metadata("DxfSubClass", DxfSubClassAttribute(DxfSubclassMarker::Dimension)))
            .property("attachmentPoint", &Dimension::attachmentPoint,
                      &Dimension::setAttachmentPoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({71})))
            .property("block", &Dimension::block, &Dimension::setBlock)(
                    metadata("DxfCodeValue", DxfCodeValueAttribute(DxfReferenceType::Name, {2})))
            .property("definitionPoint", &Dimension::definitionPoint,
                      &Dimension::setDefinitionPoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({10, 20, 30})))
            .property("flags", &Dimension::flags,
                      &Dimension::setFlags)(metadata("DxfCodeValue", DxfCodeValueAttribute({70})))
            .property("flipArrow1", &Dimension::flipArrow1,
                      &Dimension::setFlipArrow1)(metadata("DxfCodeValue", DxfCodeValueAttribute({74})))
            .property("flipArrow2", &Dimension::flipArrow2,
                      &Dimension::setFlipArrow2)(metadata("DxfCodeValue", DxfCodeValueAttribute({75})))
            .property("horizontalDirection", &Dimension::horizontalDirection, &Dimension::setHorizontalDirection)(
                    metadata("DxfCodeValue", DxfCodeValueAttribute(DxfReferenceTypes() | DxfReferenceType::Optional |
                                                                           DxfReferenceType::IsAngle,
                                                                   {51})))
            .property("insertionPoint", &Dimension::insertionPoint,
                      &Dimension::setInsertionPoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({12, 22, 32})))
            .property("lineSpacingFactor", &Dimension::lineSpacingFactor, &Dimension::setLineSpacingFactor)(
                    metadata("DxfCodeValue", DxfCodeValueAttribute(DxfReferenceType::Optional, {41})))
            .property("lineSpacingStyle", &Dimension::lineSpacingStyle, &Dimension::setLineSpacingStyle)(
                    metadata("DxfCodeValue", DxfCodeValueAttribute(DxfReferenceType::Optional, {72})))
            .property_readonly("measurement", &Dimension::measurement)(
                    metadata("DxfCodeValue", DxfCodeValueAttribute(DxfReferenceType::Optional, {42})))
            .property("normal", &Dimension::normal,
                      &Dimension::setNormal)(metadata("DxfCodeValue", DxfCodeValueAttribute({210, 220, 230})))
            .property("style", &Dimension::style, &Dimension::setStyle)(
                    metadata("DxfCodeValue", DxfCodeValueAttribute(DxfReferenceType::Name, {2})))
            .property("text", &Dimension::text, &Dimension::setText)(
                    metadata("DxfCodeValue", DxfCodeValueAttribute({DxfReferenceType::Optional, {1}})))
            .property("textMiddlePoint", &Dimension::textMiddlePoint,
                      &Dimension::setTextMiddlePoint)(metadata("DxfCodeValue", DxfCodeValueAttribute({11, 21, 31})))
            .property("textRotation", &Dimension::textRotation, &Dimension::setTextRotation)(metadata(
                    "DxfCodeValue",
                    DxfCodeValueAttribute(DxfReferenceTypes() | DxfReferenceType::Optional | DxfReferenceType::IsAngle,
                                          {53})))
            .property("version", &Dimension::version,
                      &Dimension::setVersion)(metadata("DxfCodeValue", DxfCodeValueAttribute({280})));
}

}// namespace dwg
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
#include <dwg/entities/TextEntity.h>

namespace dwg {

TextEntity::TextEntity() {}

TextEntity::~TextEntity() {}

ObjectType TextEntity::objectType() const
{
    return ObjectType::TEXT;
}

std::string TextEntity::objectName() const
{
    return DxfFileToken::EntityText;
}

std::string TextEntity::subclassMarker() const
{
    return DxfSubclassMarker::Text;
}

const std::type_info &TextEntity::typeInfo() const
{
    return typeid(TextEntity);
}

double TextEntity::thickness() const
{
    return _thickness;
}

void TextEntity::setThickness(double) {}

XYZ TextEntity::insertPoint() const
{
    return _insertPoint;
}

void TextEntity::setInsertPoint(const XYZ &) {}

double TextEntity::height() const
{
    return _height;
}

void TextEntity::setHeight(double) {}

std::string TextEntity::value() const
{
    return _value;
}

void TextEntity::setValue(const std::string &) {}

double TextEntity::rotation() const
{
    return _rotation;
}

void TextEntity::setRotation(double) {}

double TextEntity::widthFactor() const
{
    return _widthFactor;
}

void TextEntity::setWidthFactor(double) {}

double TextEntity::obliqueAngle() const
{
    return _obliqueAngle;
}

void TextEntity::setObliqueAngle(double) {}

TextStyle *TextEntity::style() const
{
    return _style;
}

void TextEntity::setStyle(TextStyle *) {}

TextMirrorFlag TextEntity::mirror() const
{
    return _mirror;
}

void TextEntity::setMirror(TextMirrorFlag) {}

TextHorizontalAlignment TextEntity::horizontalAlignment() const
{
    return _horizontalAlignment;
}

void TextEntity::setHorizontalAlignment(TextHorizontalAlignment) {}

XYZ TextEntity::alignmentPoint() const
{
    return _alignmentPoint;
}

void TextEntity::setAlignmentPoint(const XYZ &) {}

XYZ TextEntity::normal() const
{
    return _normal;
}

void TextEntity::setNormal(const XYZ &) {}

TextVerticalAlignment TextEntity::verticalAlignment() const
{
    return _verticalAlignment;
}

void TextEntity::setVerticalAlignment(TextVerticalAlignment) {}

void TextEntity::assignDocument(CadDocument *doc) {}

void TextEntity::unassignDocument() {}

}// namespace dwg
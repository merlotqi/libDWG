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
#include <dwg/tables/TextStyle.h>


namespace dwg {

TextStyle::TextStyle() {}

TextStyle::TextStyle(const std::string &name) : TableEntry(name) {}

TextStyle::~TextStyle() {}

TextStyle *TextStyle::Default()
{
    return new TextStyle(DefaultName);
}

ObjectType TextStyle::objectType() const
{
    return ObjectType::STYLE;
}

std::string TextStyle::objectName() const
{
    return DxfFileToken::TableStyle;
}

std::string TextStyle::subclassMarker() const
{
    return DxfSubclassMarker::TextStyle;
}

StyleFlags TextStyle::flags() const
{
    return _flags;
}

void TextStyle::setFlags(StyleFlags value)
{
    _flags = value;
}

std::string TextStyle::filename() const
{
    return _filename;
}

void TextStyle::setFilename(const std::string &value)
{
    _filename = value;
}

std::string TextStyle::bigFontFilename() const
{
    return _bigFontFilename;
}

void TextStyle::setBigFontFilename(const std::string &value)
{
    _bigFontFilename = value;
}

double TextStyle::height() const
{
    return _height;
}

void TextStyle::setHeight(double value)
{
    _height = value;
}

double TextStyle::width() const
{
    return _width;
}

void TextStyle::setWidth(double value)
{
    _width = value;
}

double TextStyle::lastHeight() const
{
    return _lastHeight;
}

void TextStyle::setLastHeight(double value)
{
    _lastHeight = value;
}

double TextStyle::obliqueAngle() const
{
    return _obliqueAngle;
}

void TextStyle::setObliqueAngle(double value)
{
    _obliqueAngle = value;
}

TextMirrorFlag TextStyle::mirrorFlag() const
{
    return _mirrorFlag;
}

void TextStyle::setMirrorFlag(TextMirrorFlag value)
{
    _mirrorFlag = value;
}

FontFlags TextStyle::trueType() const
{
    return _trueType;
}

void TextStyle::setTrueType(FontFlags value)
{
    _trueType = value;
}

bool TextStyle::isShapeFile() const
{
    bool v = _flags & static_cast<int>(StyleFlag::IsShape);
    return v;
}

}// namespace dwg
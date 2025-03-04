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
#include <dwg/objects/BookColor.h>
#include <fmt/core.h>
#include <stdexcept>

namespace dwg {

BookColor::BookColor() : _color((short) 0) {}

BookColor::BookColor(const std::string &name) : _name(name), _color((short) 0) {}

BookColor::~BookColor() {}

ObjectType BookColor::objectType() const { return ObjectType::UNLISTED; }

std::string BookColor::objectName() const { return DxfFileToken::ObjectDBColor; }

std::string BookColor::subclassMarker() const { return DxfSubclassMarker::DbColor; }

std::string BookColor::name() const { return _name; }

void BookColor::setName(const std::string &value)
{
    if (value.find('$') == std::string::npos)
    {
        throw new std::invalid_argument(fmt::format("Invalid BookColor name: ({}), a book color name has to separate "
                                                    "the book name and the color name by the character '$'",
                                                    value));
    }
    _name = value;
}

std::string BookColor::colorName() const
{
    auto pos = _name.find('$');
    if (pos == std::string::npos) return _name;
    else
        return _name.substr(0, pos);
}

std::string BookColor::bookName() const
{
    auto pos = _name.find('$');
    if (pos == std::string::npos) return _name;
    else
        return _name.substr(pos + 1);
}

Color BookColor::color() const { return _color; }

void BookColor::setColor(const Color &value) { _color = value; }

}// namespace dwg
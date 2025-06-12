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

#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/objects/evaluations/BlockElement.h>

namespace dwg {

BlockElement::BlockElement() {}

BlockElement::~BlockElement() {}

std::string BlockElement::subclassMarker() const
{
    return DxfSubclassMarker::BlockElement;
}

std::string BlockElement::elementName() const
{
    return _elementName;
}

void BlockElement::setElementName(const std::string &name)
{
    _elementName = name;
}

int BlockElement::value1071() const
{
    return _value1071;
}

void BlockElement::setValue1071(int value)
{
    _value1071 = value;
}

}// namespace dwg
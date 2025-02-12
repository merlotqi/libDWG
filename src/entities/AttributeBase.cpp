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

#include <dwg/entities/AttributeBase.h>

namespace dwg {

AttributeBase::AttributeBase() {}

AttributeBase::~AttributeBase() {}

TextVerticalAlignment AttributeBase::verticalAlignment() const { return _verticalAlignment; }

void AttributeBase::setVerticalAlignment(TextVerticalAlignment alignment) { _verticalAlignment = alignment; }

unsigned char AttributeBase::version() const { return _version; }

void AttributeBase::setVersion(unsigned char version) { _version = version; }

std::string AttributeBase::tag() const { return _tag; }

void AttributeBase::setTag(const std::string &tag) { _tag = tag; }

AttributeFlags AttributeBase::flags() const { return _flags; }

void AttributeBase::setFlags(AttributeFlags flags) { _flags = flags; }

AttributeBase::AttributeType AttributeBase::attributeType() const { return _attributeType; }

void AttributeBase::setAttributeType(AttributeType attributeType) { _attributeType = attributeType; }

bool AttributeBase::isReallyLocked() const { return _isReallyLocked; }

void AttributeBase::setIsReallyLocked(bool value) { _isReallyLocked = value; }

MText *AttributeBase::mtext() const { return _mtext; }

void AttributeBase::setMText(MText *mtext) { _mtext = mtext; }

void AttributeBase::matchAttributeProperties(AttributeBase *src) { src->matchProperties(this); }

}// namespace dwg

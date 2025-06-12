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
#include <dwg/objects/evaluations/Block1PtParameter.h>


namespace dwg {

Block1PtParameter::Block1PtParameter() {}

Block1PtParameter::~Block1PtParameter() {}

std::string Block1PtParameter::subclassMarker() const
{
    return DxfSubclassMarker::Block1PtParameter;
}

XYZ Block1PtParameter::location() const
{
    return _location;
}

void Block1PtParameter::setLocation(const XYZ &value)
{
    _location = value;
}

long long Block1PtParameter::value93() const
{
    return _value93;
}

void Block1PtParameter::setValue93(long long value)
{
    _value93 = value;
}

short Block1PtParameter::value170() const
{
    return _value170;
}

void Block1PtParameter::setValue170(short value)
{
    _value170 = value;
}

short Block1PtParameter::value171() const
{
    return _value171;
}

void Block1PtParameter::setValue171(short value)
{
    _value171 = value;
}

}// namespace dwg
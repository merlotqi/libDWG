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

#include <dwg/io/dwg/fileheaders/DwgSectionLocatorRecord_p.h>

namespace dwg {

DwgSectionLocatorRecord::DwgSectionLocatorRecord(std::optional<int> number, long long seeker, long long size)
    : _number(number), _seeker(seeker), _size(size)
{
}

bool DwgSectionLocatorRecord::isInTheRecord(int position) const
{
    return position >= _seeker && position < _seeker + _size;
}

std::optional<int> DwgSectionLocatorRecord::number() const
{
    return _number;
}

long long DwgSectionLocatorRecord::seeker() const
{
    return _seeker;
}

long long DwgSectionLocatorRecord::size() const
{
    return _size;
}

void DwgSectionLocatorRecord::setNumber(int number)
{
    _number = number;
}

void DwgSectionLocatorRecord::setSeeker(long long seeker)
{
    _seeker = seeker;
}

void DwgSectionLocatorRecord::setSize(long long size)
{
    _size = size;
}

}// namespace dwg

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

DwgSectionLocatorRecord::DwgSectionLocatorRecord(int32_t number, int64_t seeker,
                        int64_t size)
    : _Number(number), _Seeker(seeker), _Size(size)
{
}

bool DwgSectionLocatorRecord::IsInTheRecord(int32_t position) const
{
    return position >= _Seeker && position < _Seeker + _Size;
}

 int32_t DwgSectionLocatorRecord::Number() const { return _Number; }

 int64_t DwgSectionLocatorRecord::Seeker() const { return _Seeker; }

 int64_t DwgSectionLocatorRecord::Size() const { return _Size; }

 void DwgSectionLocatorRecord::Number(int32_t number) { _Number = number; }

 void DwgSectionLocatorRecord::Seeker(int64_t seeker) { _Seeker = seeker; }

 void DwgSectionLocatorRecord::Size(int64_t size) { _Size = size; }

}


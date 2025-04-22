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

#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC15_p.h>
#include <stdexcept>

namespace dwg {

std::vector<unsigned char> DwgFileHeaderAC15::EndSentinel = {0x95, 0xA0, 0x4E, 0x28, 0x99, 0x82, 0x1A, 0xE5,
                                                             0x5E, 0x41, 0xE0, 0x5F, 0x9D, 0x3A, 0x4D, 0x00};

DwgFileHeaderAC15::DwgFileHeaderAC15() {}

DwgFileHeaderAC15::DwgFileHeaderAC15(ACadVersion version) : DwgFileHeader(version) {}

DwgFileHeaderAC15::~DwgFileHeaderAC15() {}

void DwgFileHeaderAC15::addSection(const std::string &name)
{
    throw std::runtime_error("not implemented");
}

DwgSectionDescriptor &DwgFileHeaderAC15::getDescriptor(const std::string &name)
{
    throw std::runtime_error("not implemented");
}

std::map<int, DwgSectionLocatorRecord> DwgFileHeaderAC15::records() const
{
    return _records;
}

std::map<int, DwgSectionLocatorRecord>& DwgFileHeaderAC15::records()
{
    return _records;
}

void DwgFileHeaderAC15::setRcords(const std::map<int, DwgSectionLocatorRecord> & value)
{
    _records = value; 
}

}// namespace dwg
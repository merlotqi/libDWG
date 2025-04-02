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

#include <dwg/io/dwg/fileheaders/DwgLocalSectionMap_p.h>

namespace dwg {

DwgLocalSectionMap::DwgLocalSectionMap() : DwgLocalSectionMap(0) {}

DwgLocalSectionMap::DwgLocalSectionMap(int value)
    : _compression(2), _isEmpty(false), _offset(0), _compressedSize(0), _pageNumber(0), _decompressedSize(0),
      _seeker(0), _size(0), _checksum(0), _CRC(0), _pageSize(0), _ODA(0), _sectionMap(value)
{
}

int DwgLocalSectionMap::compression() const
{
    return _compression;
}

void DwgLocalSectionMap::setCompression(int value)
{
    _compression = value;
}

bool DwgLocalSectionMap::isEmpty() const
{
    return _isEmpty;
}

void DwgLocalSectionMap::setIsEmpty(bool value)
{
    _isEmpty = value;
}

unsigned long long DwgLocalSectionMap::offset() const
{
    return _offset;
}

void DwgLocalSectionMap::setOffset(unsigned long long value)
{
    _offset = value;
}

unsigned long long DwgLocalSectionMap::compressedSize() const
{
    return _compressedSize;
}

void DwgLocalSectionMap::setCompressedSize(unsigned long long value)
{
    _compressedSize = value;
}

int DwgLocalSectionMap::pageNumber() const
{
    return _pageNumber;
}

void DwgLocalSectionMap::setPageNumber(int value)
{
    _pageNumber = value;
}

unsigned long long DwgLocalSectionMap::decompressedSize() const
{
    return _decompressedSize;
}

void DwgLocalSectionMap::setDecompressedSize(unsigned long long value)
{
    _decompressedSize = value;
}

long long DwgLocalSectionMap::seeker() const
{
    return _seeker;
}

void DwgLocalSectionMap::setSeeker(long long value)
{
    _seeker = value;
}

long long DwgLocalSectionMap::size() const
{
    return _size;
}

void DwgLocalSectionMap::setSize(long long value)
{
    _size = value;
}

unsigned long long DwgLocalSectionMap::checksum() const
{
    return _checksum;
}

void DwgLocalSectionMap::setChecksum(unsigned long long value)
{
    _checksum = value;
}

unsigned long long DwgLocalSectionMap::CRC() const
{
    return _CRC;
}

void DwgLocalSectionMap::setCRC(unsigned long long value)
{
    _CRC = value;
}

long long DwgLocalSectionMap::pageSize() const
{
    return _pageSize;
}

void DwgLocalSectionMap::setPageSize(long long value)
{
    _pageSize = value;
}

unsigned int DwgLocalSectionMap::ODA() const
{
    return _ODA;
}

void DwgLocalSectionMap::setODA(unsigned int value)
{
    _ODA = value;
}

int DwgLocalSectionMap::sectionMap() const
{
    return _sectionMap;
}

void DwgLocalSectionMap::setSectionMap(int value)
{
    _sectionMap = value;
}

}// namespace dwg

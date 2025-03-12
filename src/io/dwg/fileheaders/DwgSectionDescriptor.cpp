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

#include <dwg/io/dwg/fileheaders/DwgSectionDescriptor_p.h>

namespace dwg {

DwgSectionDescriptor::DwgSectionDescriptor() : DwgSectionDescriptor("") {}

DwgSectionDescriptor::DwgSectionDescriptor(const std::string &name)
    : _pageType(0x4163043B), _compressedSize(0), _pageCount(0), _decompressedSize(0x7400), _compressed(2),
      _sectionId(0), _encrypted(0), _name(name)
{
}

long DwgSectionDescriptor::pageType() const { return _pageType; }

std::string DwgSectionDescriptor::name() const { return _name; }

void DwgSectionDescriptor::setName(const std::string &name) { _name = name; }

unsigned long long DwgSectionDescriptor::compressedSize() const { return _compressedSize; }

void DwgSectionDescriptor::setCompressedSize(unsigned long long value) { _compressedSize = value; }

int DwgSectionDescriptor::pageCount() const { return _pageCount; }

void DwgSectionDescriptor::setPageCount(int value) { _pageCount = value; }

unsigned long long DwgSectionDescriptor::decompressedSize() const { return _decompressedSize; }

void DwgSectionDescriptor::setDecompressedSize(unsigned long long value) { _decompressedSize = value; }

int DwgSectionDescriptor::compressedCode() const { return _compressed; }

void DwgSectionDescriptor::setCompressedCode(int value) { _compressed = value; }

bool DwgSectionDescriptor::isCompressed() const { return _compressed == 1; }

int DwgSectionDescriptor::sectionId() const { return _sectionId; }

void DwgSectionDescriptor::setSectionId(int value) { _sectionId = value; }

int DwgSectionDescriptor::encrypted() const { return _encrypted; }

void DwgSectionDescriptor::setEncrypted(int value) { _encrypted = value; }

unsigned long long DwgSectionDescriptor::hashCode(bool *ok) const
{
    if (_hashCode.has_value())
    {
        if (ok)
            *ok = true;
        return _hashCode.value();
    }
    else
    {
        if (ok)
            *ok = false;
        return 0;
    }
}

void DwgSectionDescriptor::setHashCode(unsigned long long value) { _hashCode = value; }

unsigned long long DwgSectionDescriptor::encoding(bool *ok) const
{
    if (_encoding.has_value())
    {
        if (ok)
            *ok = true;
        return _encoding.value();
    }
    else
    {
        if (ok)
            *ok = false;
        return 0;
    }
}

void DwgSectionDescriptor::setEncoding(unsigned long long value) { _encoding = value; }

std::vector<DwgLocalSectionMap> DwgSectionDescriptor::localSections() const { return _localSections; }

std::vector<DwgLocalSectionMap> &DwgSectionDescriptor::localSections() { return _localSections; }

void DwgSectionDescriptor::setLocalSections(const std::vector<DwgLocalSectionMap> &value) { _localSections = value; }

}// namespace dwg

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

#pragma once

#include <dwg/io/dwg/fileheaders/DwgLocalSectionMap_p.h>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace dwg {

class DwgSectionDescriptor
{
    int32_t _CompressedCode = 2;

public:
    DwgSectionDescriptor();

    DwgSectionDescriptor(const std::string &name);

    long PageType() const;

    std::string Name() const;
    void Name(const std::string& name);

    unsigned long long CompressedSize() const;
    void CompressedSize(unsigned long long);

    int PageCount() const;
    void PageCount(int);

    unsigned long long DecompressedSize() const;
    void DecompressedSize(unsigned long long);

    int CompressedCode() const;
    void CompressedCode(int);

    bool IsCompressed() const;

    int SectionId() const;
    void SectionId(int);

    int Encrypted() const;
    void Encrypted(int);

    unsigned long long HashCode(bool *ok = nullptr) const;
    void HashCode(unsigned long long);

    unsigned long long Encoding(bool *ok = nullptr) const;
    void Encoding(unsigned long long);

    std::vector<DwgLocalSectionMap> LocalSections() const;
    void LocalSections(const std::vector<DwgLocalSectionMap> &);
};

}// namespace dwg
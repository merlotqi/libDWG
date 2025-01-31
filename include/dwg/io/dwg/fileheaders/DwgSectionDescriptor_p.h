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

#include "DwgLocalSectionMap.h"
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace dwg {
namespace io {

class DwgSectionDescriptor
{
    int32_t _CompressedCode = 2;

public:
    int64_t PageType = 0x4163043B;
    std::string Name;
    uint64_t CompressedSize = 0;
    int32_t PageCount = 0;
    uint64_t DecompressedSize = 0x7400;
    int32_t Compressed = 0;
    int32_t SectionId = 0;
    int32_t Encrypted = 0;
    uint64_t HashCode = 0;
    uint64_t Encoding = 0;
    std::vector<DwgLocalSectionMap> LocalSections;

public:
    DwgSectionDescriptor(const std::string &name = std::string()) : Name(name)
    {
    }

    inline int32_t CompressedCode() const { return _CompressedCode; }
    inline void CompressedCode(int32_t value)
    {
        if (value == 1 || value == 2) _CompressedCode = value;
        else
            throw new std::exception();
    }
};


}// namespace io
}// namespace dwg
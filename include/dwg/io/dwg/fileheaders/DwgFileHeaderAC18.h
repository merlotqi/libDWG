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

#include <dwg/io/dwg/fileheaders/DwgFileHeaderAC15.h>

namespace dwg {
namespace io {

class DwgFileHeaderAC18 : DwgFileHeaderAC15
{
public:
    uint8_t DwgVersion;
    uint8_t AppReleaseVersion;
    int64_t SummaryInfoAddr;
    int64_t SecurityType;
    int64_t VbaProjectAddr;
    int32_t RootTreeNodeGap;
    uint32_t GapArraySize;
    uint32_t CRCSeed;
    int32_t LastPageId;
    int64_t LastSectionAddr;
    int64_t SecondHeaderAddr;
    uint32_t GapAmount;
    uint32_t SectionAmount;
    uint32_t SectionPageMapId;
    int64_t PageMapAddress;
    uint32_t SectionMapId;
    uint32_t SectionArrayPageSize;
    int32_t RigthGap;
    int32_t LeftGap;
    std::map<std::string, DwgSectionDescriptor> Descriptors;

    DwgFileHeaderAC18();
    DwgFileHeaderAC18(ACadVersion version);
    void AddSection(const std::string &name);
    void AddSection(const DwgSectionDescriptor &descriptor);
};


}// namespace io
}// namespace dwg
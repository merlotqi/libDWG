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

#ifndef LIBDWG_DWGFILEHEADER_H
#define LIBDWG_DWGFILEHEADER_H

#include <cstdint>
#include <dwg/ACadVersion.h>
#include <map>
#include <string>
#include <vector>

namespace dwg {
namespace io {











struct Dwg21CompressedMetadata
{
    uint64_t HeaderSize;
    uint64_t FileSize;
    uint64_t PagesMapCrcCompressed;
    uint64_t PagesMapCorrectionFactor;
    uint64_t PagesMapCrcSeed;
    uint64_t Map2Offset;
    uint64_t Map2Id;
    uint64_t PagesMapOffset;
    uint64_t Header2offset;
    uint64_t PagesMapSizeCompressed;
    uint64_t PagesMapSizeUncompressed;
    uint64_t PagesAmount;
    uint64_t PagesMaxId;
    uint64_t SectionsMap2Id;
    uint64_t PagesMapId;
    uint64_t Unknow0x20;

    uint64_t Unknow0x40;
    uint64_t PagesMapCrcUncompressed;
    uint64_t Unknown0xF800;
    uint64_t Unknown4;
    uint64_t Unknown1;
    uint64_t SectionsAmount;
    uint64_t SectionsMapCrcUncompressed;
    uint64_t SectionsMapSizeCompressed;
    uint64_t SectionsMapId;
    uint64_t SectionsMapSizeUncompressed;
    uint64_t SectionsMapCrcCompressed;
    uint64_t SectionsMapCorrectionFactor;
    uint64_t SectionsMapCrcSeed;
    uint64_t StreamVersion;
    uint64_t CrcSeed;
    uint64_t CrcSeedEncoded;
    uint64_t RandomSeed;
    uint64_t HeaderCRC64;
};

struct DwgFileHeaderAC21 : DwgFileHeaderAC18
{
    Dwg21CompressedMetadata CompressedMetadata;

    DwgFileHeaderAC21();
    DwgFileHeaderAC21(ACadVersion version);
};

}// namespace io
}// namespace dwg

#endif// DWG_FILE_HEADER_H
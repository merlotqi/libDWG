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

namespace dwg {
namespace io {

struct Dwg21CompressedMetadata
{
    unsigned long long HeaderSize = 0x70;
    unsigned long long FileSize = 0;
    unsigned long long PagesMapCrcCompressed = 0;
    unsigned long long PagesMapCorrectionFactor = 0;
    unsigned long long PagesMapCrcSeed = 0;
    unsigned long long Map2Offset = 0;
    unsigned long long Map2Id = 0;
    unsigned long long PagesMapOffset = 0;
    unsigned long long Header2offset = 0;
    unsigned long long PagesMapSizeCompressed = 0;
    unsigned long long PagesMapSizeUncompressed = 0;
    unsigned long long PagesAmount = 0;
    unsigned long long PagesMaxId = 0;
    unsigned long long SectionsMap2Id = 0;
    unsigned long long PagesMapId = 0;
    unsigned long long Unknow0x20 = 32;
    unsigned long long Unknow0x40 = 64;
    unsigned long long PagesMapCrcUncompressed = 0;
    unsigned long long Unknown0xF800 = 0xF800;
    unsigned long long Unknown4 = 4;
    unsigned long long Unknown1 = 1;
    unsigned long long SectionsAmount = 0;
    unsigned long long SectionsMapCrcUncompressed = 0;
    unsigned long long SectionsMapSizeCompressed = 0;
    unsigned long long SectionsMapId = 0;
    unsigned long long SectionsMapSizeUncompressed = 0;
    unsigned long long SectionsMapCrcCompressed = 0;
    unsigned long long SectionsMapCorrectionFactor = 0;
    unsigned long long SectionsMapCrcSeed = 0;
    unsigned long long StreamVersion = 393472;
    unsigned long long CrcSeed = 0;
    unsigned long long CrcSeedEncoded = 0;
    unsigned long long RandomSeed = 0;
    unsigned long long HeaderCRC64 = 0;

    Dwg21CompressedMetadata() {}
};

}// namespace io
}// namespace dwg
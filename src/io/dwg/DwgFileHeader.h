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

struct DwgLocalSectionMap
{
    int32_t Compression = 2;
    bool IsEmpty;
    uint64_t Offset;
    uint64_t CompressedSize;
    int32_t PageNumber;
    uint64_t DecompressedSize;
    int64_t Seeker;
    int64_t Size;
    uint64_t Checksum;
    uint64_t CRC;
    int64_t PageSize;
    uint32_t ODA;
    int32_t SectionMap;

    DwgLocalSectionMap(int value = 0);
};

struct DwgSectionLocatorRecord
{
    int32_t Number;
    int64_t Seeker;
    int64_t Size;

    DwgSectionLocatorRecord(int32_t number = 0, int64_t seeker = 0,
                            int64_t size = 0);
    bool IsInTheRecord(int32_t position) const;
};

struct DwgSectionDescriptor
{
    int64_t PageType;
    std::string Name;
    uint64_t CompressedSize;
    int32_t PageCount;
    uint64_t DecompressedSize;
    int32_t Compressed;
    int32_t SectionId;
    int32_t Encrypted;
    uint64_t HashCode;
    uint64_t Encoding;
    std::vector<DwgLocalSectionMap> LocalSections;

    DwgSectionDescriptor(const std::string &name = std::string());
};

struct DwgFileHeader
{
public:
    ACadVersion Version;
    int64_t PreviewAddress;
    int32_t AcadMaintenanceVersion;
    CodePage DrawingCodePage;

    DwgFileHeader();
    DwgFileHeader(ACadVersion version);

    static DwgFileHeader *CreateFileHeader(ACadVersion version);

    virtual void AddSection(const std::string &name) = 0;
    virtual DwgSectionDescriptor &GetDescriptor(const std::string &name) = 0;
};

struct DwgFileHeaderAC15 : DwgFileHeader
{
    static std::vector<unsigned char> EndSentinel;
    std::map<int32_t, DwgSectionLocatorRecord> Records;
    void AddSection(const std::string &name) override;
    DwgSectionDescriptor &GetDescriptor(const std::string &name) override;

    DwgFileHeaderAC15();
    DwgFileHeaderAC15(ACadVersion version);
};

struct DwgFileHeaderAC18 : DwgFileHeaderAC15
{
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
    std::map<std::string, DwgSectionDescriptor> Descriptiors;

    DwgFileHeaderAC18();
    DwgFileHeaderAC18(ACadVersion version);
    void AddSection(const std::string &name);
    void AddSection(const DwgSectionDescriptor &descriptor);
};


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
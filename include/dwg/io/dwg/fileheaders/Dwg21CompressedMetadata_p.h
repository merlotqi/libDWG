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

class Dwg21CompressedMetadata
{
public:
    Dwg21CompressedMetadata();

    unsigned long long headerSize() const;
    void setHeaderSize(unsigned long long headerSize);

    unsigned long long fileSize() const;
    void setFileSize(unsigned long long fileSize);

    unsigned long long pagesMapCrcCompressed() const;
    void setPagesMapCrcCompressed(unsigned long long pagesMapCrcCompressed);

    unsigned long long pagesMapCorrectionFactor() const;
    void setPagesMapCorrectionFactor(unsigned long long pagesMapCorrectionFactor);

    unsigned long long pagesMapCrcSeed() const;
    void setPagesMapCrcSeed(unsigned long long pagesMapCrcSeed);

    unsigned long long map2Offset() const;
    void setMap2Offset(unsigned long long map2Offset);

    unsigned long long map2Id() const;
    void setMap2Id(unsigned long long map2Id);

    unsigned long long pagesMapOffset() const;
    void setPagesMapOffset(unsigned long long pagesMapOffset);

    unsigned long long header2offset() const;
    void setHeader2offset(unsigned long long header2Offset);

    unsigned long long pagesMapSizeCompressed() const;
    void setPagesMapSizeCompressed(unsigned long long pagesMapSizeCompressed);

    unsigned long long pagesMapSizeUncompressed() const;
    void setPagesMapSizeUncompressed(unsigned long long pagesMapSizeUncompressed);

    unsigned long long pagesAmount() const;
    void setPagesAmount(unsigned long long pagesAmount);

    unsigned long long pagesMaxId() const;
    void setPagesMaxId(unsigned long long pagesMaxId);

    unsigned long long sectionsMap2Id() const;
    void setSectionsMap2Id(unsigned long long sectionsMap2Id);

    unsigned long long pagesMapId() const;
    void setPagesMapId(unsigned long long pagesMapId);

    unsigned long long unknow0x20() const;
    void setUnknow0x20(unsigned long long unknow0x20);

    unsigned long long unknow0x40() const;
    void setUnknow0x40(unsigned long long unknow0x40);

    unsigned long long pagesMapCrcUncompressed() const;
    void setPagesMapCrcUncompressed(unsigned long long pagesMapCrcUncompressed);

    unsigned long long unknown0xF800() const;
    void setUnknown0xF800(unsigned long long unknown0xF800);

    unsigned long long unknown4() const;
    void setUnknown4(unsigned long long unknown4);

    unsigned long long unknown1() const;
    void setUnknown1(unsigned long long unknown1);

    unsigned long long sectionsAmount() const;
    void setSectionsAmount(unsigned long long sectionsAmount);

    unsigned long long sectionsMapCrcUncompressed() const;
    void setSectionsMapCrcUncompressed(unsigned long long sectionsMapCrcUncompressed);

    unsigned long long sectionsMapSizeCompressed() const;
    void setSectionsMapSizeCompressed(unsigned long long sectionsMapSizeCompressed);

    unsigned long long sectionsMapId() const;
    void setSectionsMapId(unsigned long long sectionsMapId);

    unsigned long long sectionsMapSizeUncompressed() const;
    void setSectionsMapSizeUncompressed(unsigned long long sectionsMapSizeUncompressed);

    unsigned long long sectionsMapCrcCompressed() const;
    void setSectionsMapCrcCompressed(unsigned long long sectionsMapCrcCompressed);

    unsigned long long sectionsMapCorrectionFactor() const;
    void setSectionsMapCorrectionFactor(unsigned long long sectionsMapCorrectionFactor);

    unsigned long long sectionsMapCrcSeed() const;
    void setSectionsMapCrcSeed(unsigned long long sectionsMapCrcSeed);

    unsigned long long streamVersion() const;
    void setStreamVersion(unsigned long long streamVersion);

    unsigned long long crcSeed() const;
    void setCrcSeed(unsigned long long crcSeed);

    unsigned long long crcSeedEncoded() const;
    void setCrcSeedEncoded(unsigned long long crcSeedEncoded);

    unsigned long long randomSeed() const;
    void setRandomSeed(unsigned long long randomSeed);

    unsigned long long headerCRC64() const;
    void setHeaderCRC64(unsigned long long headerCRC64);

private:
    unsigned long long _headerSize;
    unsigned long long _fileSize;
    unsigned long long _pagesMapCrcCompressed;
    unsigned long long _pagesMapCorrectionFactor;
    unsigned long long _pagesMapCrcSeed;
    unsigned long long _map2Offset;
    unsigned long long _map2Id;
    unsigned long long _pagesMapOffset;
    unsigned long long _header2offset;
    unsigned long long _pagesMapSizeCompressed;
    unsigned long long _pagesMapSizeUncompressed;
    unsigned long long _pagesAmount;
    unsigned long long _pagesMaxId;
    unsigned long long _sectionsMap2Id;
    unsigned long long _pagesMapId;
    unsigned long long _unknow0x20;
    unsigned long long _unknow0x40;
    unsigned long long _pagesMapCrcUncompressed;
    unsigned long long _unknown0xF800;
    unsigned long long _unknown4;
    unsigned long long _unknown1;
    unsigned long long _sectionsAmount;
    unsigned long long _sectionsMapCrcUncompressed;
    unsigned long long _sectionsMapSizeCompressed;
    unsigned long long _sectionsMapId;
    unsigned long long _sectionsMapSizeUncompressed;
    unsigned long long _sectionsMapCrcCompressed;
    unsigned long long _sectionsMapCorrectionFactor;
    unsigned long long _sectionsMapCrcSeed;
    unsigned long long _streamVersion;
    unsigned long long _crcSeed;
    unsigned long long _crcSeedEncoded;
    unsigned long long _randomSeed;
    unsigned long long _headerCRC64;
};

}// namespace dwg
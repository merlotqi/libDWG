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

#include <dwg/io/dwg/fileheaders/Dwg21CompressedMetadata_p.h>

namespace dwg {

Dwg21CompressedMetadata::Dwg21CompressedMetadata()
    : _headerSize(0x70), _fileSize(0), _pagesMapCrcCompressed(0), _pagesMapCorrectionFactor(0), _pagesMapCrcSeed(0),
      _map2Offset(0), _map2Id(0), _pagesMapOffset(0), _header2Offset(0), _pagesMapSizeCompressed(0),
      _pagesMapSizeUncompressed(0), _pagesAmount(0), _pagesMaxId(0), _sectionsMap2Id(0), _pagesMapId(0),
      _unknow0x20(32), _unknow0x40(64), _pagesMapCrcUncompressed(0), _unknown0xF800(0xF800), _unknown4(4), _unknown1(1),
      _sectionsAmount(0), _sectionsMapCrcUncompressed(0), _sectionsMapSizeCompressed(0), _sectionsMapId(0),
      _sectionsMapSizeUncompressed(0), _sectionsMapCrcCompressed(0), _sectionsMapCorrectionFactor(0),
      _sectionsMapCrcSeed(0), _streamVersion(393472), _crcSeed(0), _crcSeedEncoded(0), _randomSeed(0), _headerCRC64(0)
{
}

unsigned long long Dwg21CompressedMetadata::headerSize() const { return _headerSize; }

void Dwg21CompressedMetadata::setHeaderSize(unsigned long long headerSize) { _headerSize = headerSize; }

unsigned long long Dwg21CompressedMetadata::fileSize() const { return _fileSize; }

void Dwg21CompressedMetadata::setFileSize(unsigned long long fileSize) { _fileSize = fileSize; }

unsigned long long Dwg21CompressedMetadata::pagesMapCrcCompressed() const { return _pagesMapCrcCompressed; }

void Dwg21CompressedMetadata::setPagesMapCrcCompressed(unsigned long long pagesMapCrcCompressed)
{
    _pagesMapCrcCompressed = pagesMapCrcCompressed;
}

unsigned long long Dwg21CompressedMetadata::pagesMapCorrectionFactor() const { return _pagesMapCorrectionFactor; }

void Dwg21CompressedMetadata::setPagesMapCorrectionFactor(unsigned long long pagesMapCorrectionFactor)
{
    _pagesMapCorrectionFactor = pagesMapCorrectionFactor;
}

unsigned long long Dwg21CompressedMetadata::pagesMapCrcSeed() const { return _pagesMapCrcSeed; }

void Dwg21CompressedMetadata::setPagesMapCrcSeed(unsigned long long pagesMapCrcSeed)
{
    _pagesMapCrcSeed = pagesMapCrcSeed;
}

unsigned long long Dwg21CompressedMetadata::map2Offset() const { return _map2Offset; }

void Dwg21CompressedMetadata::setMap2Offset(unsigned long long map2Offset) { _map2Offset = map2Offset; }

unsigned long long Dwg21CompressedMetadata::map2Id() const { return _map2Id; }

void Dwg21CompressedMetadata::setMap2Id(unsigned long long map2Id) { _map2Id = map2Id; }

unsigned long long Dwg21CompressedMetadata::pagesMapOffset() const { return _pagesMapOffset; }

void Dwg21CompressedMetadata::setPagesMapOffset(unsigned long long pagesMapOffset) { _pagesMapOffset = pagesMapOffset; }

unsigned long long Dwg21CompressedMetadata::header2Offset() const { return _header2Offset; }

void Dwg21CompressedMetadata::setHeader2Offset(unsigned long long header2Offset) { _header2Offset = header2Offset; }

unsigned long long Dwg21CompressedMetadata::pagesMapSizeCompressed() const { return _pagesMapSizeCompressed; }

void Dwg21CompressedMetadata::setPagesMapSizeCompressed(unsigned long long pagesMapSizeCompressed)
{
    _pagesMapSizeCompressed = pagesMapSizeCompressed;
}

unsigned long long Dwg21CompressedMetadata::pagesMapSizeUncompressed() const { return _pagesMapSizeUncompressed; }

void Dwg21CompressedMetadata::setPagesMapSizeUncompressed(unsigned long long pagesMapSizeUncompressed)
{
    _pagesMapSizeUncompressed = pagesMapSizeUncompressed;
}

unsigned long long Dwg21CompressedMetadata::pagesAmount() const { return _pagesAmount; }

void Dwg21CompressedMetadata::setPagesAmount(unsigned long long pagesAmount) { _pagesAmount = pagesAmount; }

unsigned long long Dwg21CompressedMetadata::pagesMaxId() const { return _pagesMaxId; }

void Dwg21CompressedMetadata::setPagesMaxId(unsigned long long pagesMaxId) { _pagesMaxId = pagesMaxId; }

unsigned long long Dwg21CompressedMetadata::sectionsMap2Id() const { return _sectionsMap2Id; }

void Dwg21CompressedMetadata::setSectionsMap2Id(unsigned long long sectionsMap2Id) { _sectionsMap2Id = sectionsMap2Id; }

unsigned long long Dwg21CompressedMetadata::pagesMapId() const { return _pagesMapId; }

void Dwg21CompressedMetadata::setPagesMapId(unsigned long long pagesMapId) { _pagesMapId = pagesMapId; }

unsigned long long Dwg21CompressedMetadata::unknow0x20() const { return _unknow0x20; }

void Dwg21CompressedMetadata::setUnknow0x20(unsigned long long unknow0x20) { _unknow0x20 = unknow0x20; }

unsigned long long Dwg21CompressedMetadata::unknow0x40() const { return _unknow0x40; }

void Dwg21CompressedMetadata::setUnknow0x40(unsigned long long unknow0x40) { _unknow0x40 = unknow0x40; }

unsigned long long Dwg21CompressedMetadata::pagesMapCrcUncompressed() const { return _pagesMapCrcUncompressed; }

void Dwg21CompressedMetadata::setPagesMapCrcUncompressed(unsigned long long pagesMapCrcUncompressed)
{
    _pagesMapCrcUncompressed = pagesMapCrcUncompressed;
}

unsigned long long Dwg21CompressedMetadata::unknown0xF800() const { return _unknown0xF800; }

void Dwg21CompressedMetadata::setUnknown0xF800(unsigned long long unknown0xF800) { _unknown0xF800 = unknown0xF800; }

unsigned long long Dwg21CompressedMetadata::unknown4() const { return _unknown4; }

void Dwg21CompressedMetadata::setUnknown4(unsigned long long unknown4) { _unknown4 = unknown4; }

unsigned long long Dwg21CompressedMetadata::unknown1() const { return _unknown1; }

void Dwg21CompressedMetadata::setUnknown1(unsigned long long unknown1) { _unknown1 = unknown1; }

unsigned long long Dwg21CompressedMetadata::sectionsAmount() const { return _sectionsAmount; }

void Dwg21CompressedMetadata::setSectionsAmount(unsigned long long sectionsAmount) { _sectionsAmount = sectionsAmount; }

unsigned long long Dwg21CompressedMetadata::sectionsMapCrcUncompressed() const { return _sectionsMapCrcUncompressed; }

void Dwg21CompressedMetadata::setSectionsMapCrcUncompressed(unsigned long long sectionsMapCrcUncompressed)
{
    _sectionsMapCrcUncompressed = sectionsMapCrcUncompressed;
}

unsigned long long Dwg21CompressedMetadata::sectionsMapSizeCompressed() const { return _sectionsMapSizeCompressed; }

void Dwg21CompressedMetadata::setSectionsMapSizeCompressed(unsigned long long sectionsMapSizeCompressed)
{
    _sectionsMapSizeCompressed = sectionsMapSizeCompressed;
}

unsigned long long Dwg21CompressedMetadata::sectionsMapId() const { return _sectionsMapId; }

void Dwg21CompressedMetadata::setSectionsMapId(unsigned long long sectionsMapId) { _sectionsMapId = sectionsMapId; }

unsigned long long Dwg21CompressedMetadata::sectionsMapSizeUncompressed() const { return _sectionsMapSizeUncompressed; }

void Dwg21CompressedMetadata::setSectionsMapSizeUncompressed(unsigned long long sectionsMapSizeUncompressed)
{
    _sectionsMapSizeUncompressed = sectionsMapSizeUncompressed;
}

unsigned long long Dwg21CompressedMetadata::sectionsMapCrcCompressed() const { return _sectionsMapCrcCompressed; }

void Dwg21CompressedMetadata::setSectionsMapCrcCompressed(unsigned long long sectionsMapCrcCompressed)
{
    _sectionsMapCrcCompressed = sectionsMapCrcCompressed;
}

unsigned long long Dwg21CompressedMetadata::sectionsMapCorrectionFactor() const { return _sectionsMapCorrectionFactor; }

void Dwg21CompressedMetadata::setSectionsMapCorrectionFactor(unsigned long long sectionsMapCorrectionFactor)
{
    _sectionsMapCorrectionFactor = sectionsMapCorrectionFactor;
}

unsigned long long Dwg21CompressedMetadata::sectionsMapCrcSeed() const { return _sectionsMapCrcSeed; }

void Dwg21CompressedMetadata::setSectionsMapCrcSeed(unsigned long long sectionsMapCrcSeed)
{
    _sectionsMapCrcSeed = sectionsMapCrcSeed;
}

unsigned long long Dwg21CompressedMetadata::streamVersion() const { return _streamVersion; }

void Dwg21CompressedMetadata::setStreamVersion(unsigned long long streamVersion) { _streamVersion = streamVersion; }

unsigned long long Dwg21CompressedMetadata::crcSeed() const { return _crcSeed; }

void Dwg21CompressedMetadata::setCrcSeed(unsigned long long crcSeed) { _crcSeed = crcSeed; }

unsigned long long Dwg21CompressedMetadata::crcSeedEncoded() const { return _crcSeedEncoded; }

void Dwg21CompressedMetadata::setCrcSeedEncoded(unsigned long long crcSeedEncoded) { _crcSeedEncoded = crcSeedEncoded; }

unsigned long long Dwg21CompressedMetadata::randomSeed() const { return _randomSeed; }

void Dwg21CompressedMetadata::setRandomSeed(unsigned long long randomSeed) { _randomSeed = randomSeed; }

unsigned long long Dwg21CompressedMetadata::headerCRC64() const { return _headerCRC64; }

void Dwg21CompressedMetadata::setHeaderCRC64(unsigned long long headerCRC64) { _headerCRC64 = headerCRC64; }

}// namespace dwg

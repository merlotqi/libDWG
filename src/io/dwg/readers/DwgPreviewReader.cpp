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

#include <assert.h>
#include <dwg/DwgPreview.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/readers/DwgPreviewReader_p.h>
#include <dwg/io/dwg/readers/IDwgStreamReader_p.h>


namespace dwg {

DwgPreviewReader::DwgPreviewReader(ACadVersion version, IDwgStreamReader *reader, long long previewAddress)
    : DwgSectionIO(version), _reader(reader), _previewAddress(previewAddress)
{
    _startSentinel = DwgSectionDefinition::StartSentinels[DwgSectionDefinition::Preview];
    _endSentinel = DwgSectionDefinition::EndSentinels[DwgSectionDefinition::Preview];
}

DwgPreviewReader::~DwgPreviewReader() {}

std::string DwgPreviewReader::sectionName() const
{
    return DwgSectionDefinition::Preview;
}

DwgPreview *DwgPreviewReader::read()
{
    // { 0x1F,0x25,0x6D,0x07,0xD4,0x36,0x28,0x28,0x9D,0x57,0xCA,0x3F,0x9D,0x44,0x10,0x2B }
    std::vector<unsigned char> sentinel = _reader->readSentinel();
    assert(DwgSectionIO::CheckSentinel(sentinel, _startSentinel));

    // overall size	RL	overall size of image area
    long long overallSize = _reader->readRawLong();

    //images present RC counter indicating what is present here
    unsigned char imagespresent = (unsigned char) _reader->readRawChar();

    long long headerDataStart = 0;
    long long headerDataSize = 0;
    long long startOfImage = 0;
    long long sizeImage = 0;

    DwgPreview::PreviewType previewCode = DwgPreview::PreviewType::Unknown;
    for (int i = 0; i < imagespresent; ++i)
    {
        // Code RC code indicating what follows
        unsigned char code = (unsigned char) _reader->readRawChar();
        switch (code)
        {
            case 1:
                // header data start RL start of header data
                headerDataStart = _reader->readRawLong();
                headerDataSize = _reader->readRawLong();
                break;
            default:
                previewCode = (DwgPreview::PreviewType) code;
                startOfImage = _reader->readRawLong();
                sizeImage = _reader->readRawLong();
                break;
        };
    }

    assert(_previewAddress + 39 == headerDataStart);
    auto header = _reader->readBytes(headerDataSize);

    assert(_previewAddress + headerDataSize + 39 == startOfImage);
    auto body = _reader->readBytes(sizeImage);

    return new DwgPreview(previewCode, header, body);
}

}// namespace dwg
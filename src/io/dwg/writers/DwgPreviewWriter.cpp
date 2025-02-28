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

#include <dwg/io/dwg/writers/DwgPreviewWriter_p.h>
#include <dwg/utils/Encoding.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>

namespace dwg {

DwgPreviewWriter::DwgPreviewWriter(ACadVersion version, std::ostream *stream)
    : DwgSectionIO(version)
{
    _swriter = DwgStreamWriterBase::GetStreamWriter(version, stream, Encoding(CodePage::Windows1252));
    _startSentinel = {0x1F, 0x25, 0x6D, 0x07, 0xD4, 0x36, 0x28, 0x28, 0x9D, 0x57, 0xCA, 0x3F, 0x9D, 0x44, 0x10, 0x2B};
    _endSentinel = {0xE0, 0xDA, 0x92, 0xF8, 0x2B, 0xC9, 0xD7, 0xD7, 0x62, 0xA8, 0x35, 0xC0, 0x62, 0xBB, 0xEF, 0xD4};
}

DwgPreviewWriter::~DwgPreviewWriter()
{
    delete _swriter;
    _swriter = nullptr;
}

std::string DwgPreviewWriter::sectionName() const { return DwgSectionDefinition::Preview; }

void DwgPreviewWriter::write()
{
    _swriter->writeBytes(_startSentinel);
    _swriter->writeRawLong(1);
    _swriter->writeByte(0);
    _swriter->writeBytes(_endSentinel);
}

}// namespace dwg
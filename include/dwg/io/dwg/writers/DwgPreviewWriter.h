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

#include <dwg/io/dwg/DwgSectionIO.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter.h>

namespace dwg {
namespace io {

	class DwgPreviewWriter : DwgSectionIO
	{
        IDwgStreamWriter* _swriter;
        static std::vector<unsigned char> _startSentinel;
        static std::vector<unsigned char> _endSentinel;

    public:
        std::string SectionName() const { return DwgSectionDefinition::Preview; }

		public DwgPreviewWriter(ACadVersion version, Stream stream) : base(version)
		{
			_swriter = DwgStreamWriterBase.GetStreamWriter(version, stream, Encoding::Windows1252());
		}

		public void Write()
		{
			_swriter->WriteBytes(_startSentinel);
			_swriter->WriteRawLong(1);
			_swriter->WriteByte(0);
			_swriter->WriteBytes(_endSentinel);
		}
	};

    std::vector<unsigned char> DwgPreviewWriter::_startSentinel = 
    {
        0x1F,0x25,0x6D,0x07,0xD4,0x36,0x28,0x28,0x9D,0x57,0xCA,0x3F,0x9D,0x44,0x10,0x2B
    };
    std::vector<unsigned char> DwgPreviewWriter::_startSentinel = 
    {
        0xE0, 0xDA, 0x92, 0xF8, 0x2B, 0xC9, 0xD7, 0xD7, 0x62, 0xA8, 0x35, 0xC0, 0x62, 0xBB, 0xEF, 0xD4
    };
}
}
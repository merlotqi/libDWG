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

class DwgAppInfoWriter : public DwgSectionIO
{
    IDwgStreamWriter* _writer;
    std::vector<unsigned char> _emptyArr;

public:
    std::string SectionName() const { return DwgSectionDefinition::AppInfo; }

    DwgAppInfoWriter(ACadVersion version, std::ostream* stream) : DwgSectionIO(version)
    {
        _emptyArr.resize(16);
        std::fill(_emptyArr, 0);
        _writer = DwgStreamWriterBase::GetStreamWriter(version, stream, Encoding::Unicode);
    }

    void Write()
    {
        std::string version;  // Assembly.GetExecutingAssembly().GetName().Version.ToString();
        //UInt32	4	class_version (default: 3)
		_writer->WriteInt(3);
		//String	2 + 2 * n + 2	App info name, ODA writes “AppInfoDataList”
		_writer->WriteTextUnicode("AppInfoDataList");
		//UInt32	4	num strings (default: 3)
		_writer->WriteInt(3);
		//Byte[]	16	Version data(checksum, ODA writes zeroes)
		_writer->WriteBytes(_emptyArr);
		//String	2 + 2 * n + 2	Version
		_writer->WriteTextUnicode(version);
		//Byte[]	16	Comment data(checksum, ODA writes zeroes)
		_writer->WriteBytes(_emptyArr);
		//String	2 + 2 * n + 2	Comment
		_writer->WriteTextUnicode("This is a comment from libDWG");
		//Byte[]	16	Product data(checksum, ODA writes zeroes)
		_writer->WriteBytes(_emptyArr);
		//String	2 + 2 * n + 2	Product
		_writer->WriteTextUnicode($"<ProductInformation name =\"libDWG\" build_version=\"{version}\" registry_version=\"{version}\" install_id_string=\"libDWG\" registry_localeID=\"1033\"/>");
    }
};


}
}
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

#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/readers/DwgAppInfoReader_p.h>
#include <dwg/io/dwg/readers/IDwgStreamReader_p.h>

namespace dwg {

DwgAppInfoReader::DwgAppInfoReader(ACadVersion version, IDwgStreamReader *reader) : DwgSectionIO(version), _reader(reader) {}

DwgAppInfoReader::~DwgAppInfoReader() {}

std::string DwgAppInfoReader::sectionName() const
{
    return DwgSectionDefinition::AppInfo;
}

void DwgAppInfoReader::read() 
{
    if (!R2007Plus)
    {
        readR18();
    }

    //UInt32	4	Unknown(ODA writes 2)
    int unknown1 = _reader->readInt();
    //String	2 + 2 * n + 2	App info name, ODA writes "AppInfoDataList"
    std::string infoname = _reader->readTextUtf8();
    //UInt32	4	Unknown(ODA writes 3)
    int unknown2 = _reader->readInt();
    //Byte[]	16	Version data(checksum, ODA writes zeroes)
    std::vector<unsigned char> bytes = _reader->readBytes(16);
    //String	2 + 2 * n + 2	Version
    std::string version = _reader->readTextUtf8();
    //Byte[]	16	Comment data(checksum, ODA writes zeroes)
    std::vector<unsigned char> comm = _reader->readBytes(16);

    if (!R2010Plus)
    {
        return;
    }

    //String	2 + 2 * n + 2	Comment
    std::string comment = _reader->readTextUtf8();
    //Byte[]	16	Product data(checksum, ODA writes zeroes)
    std::vector<unsigned char> product = _reader->readBytes(16);
    //String	2 + 2 * n + 2	Product
    std::string xml = _reader->readTextUtf8();
}

void DwgAppInfoReader::readR18() 
{
    //For this version the values don't match with the documentaiton

    //String	2 + 2 * n + 2	App info name, ODA writes "AppInfoDataList"
    std::string infoname = _reader->readVariableText();
    //UInt32	4	Unknown(ODA writes 2)
    int unknown2 = _reader->readInt();
    //Unknown, ODA writes "4001"
    std::string version = _reader->readVariableText();
    //String	2 + n App info product XML element, e.g. ODA writes "< ProductInformation name = "Teigha" build_version = "0.0" registry_version = "3.3" install_id_string = "ODA" registry_localeID = "1033" /> "
    std::string xml = _reader->readVariableText();
    //String	2 + n	App info version, e.g. ODA writes "2.7.2.0"
    std::string comment = _reader->readVariableText();
}

}// namespace dwg
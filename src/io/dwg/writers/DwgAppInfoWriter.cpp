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

#include "DwgAppInfoWriter.h"
#include "../DwgSectionIO.h"
#include "../fileheaders/DwgSectionDefinition.h"
#include "DwgStreamWriterBase.h"
#include "IDwgStreamWriter.h"
#include <dwg/utility/stringhelp.h>
#include <dwg/version.h>
#include <fmt/core.h>

namespace dwg {
namespace io {

std::string DwgAppInfoWriter::SectionName() const
{
    return DwgSectionDefinition::AppInfo;
}

DwgAppInfoWriter::DwgAppInfoWriter(ACadVersion version, std::ostream *stream)
    : DwgSectionIO(version)
{
    for (size_t i = 0; i < 16; ++i) _emptyArr.push_back(0);
    _writer = DwgStreamWriterBase::GetStreamWriter(version, stream, Encoding());
}

void DwgAppInfoWriter::Write()
{
    std::string version = LIBDWG_VERSION;
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
    std::string productInfo = fmt::format(
            "<ProductInformation name =\"libDWG\" build_version=\"{}\" "
            "registry_version=\"{}\" install_id_string=\"libDWG\" "
            "registry_localeID=\"1033\"/>",
            version, version);

    _writer->WriteTextUnicode(productInfo);
}

}// namespace io
}// namespace dwg
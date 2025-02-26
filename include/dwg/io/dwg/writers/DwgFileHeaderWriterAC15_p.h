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

#include <dwg/io/dwg/fileheaders/DwgSectionLocatorRecord_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterBase_p.h>
#include <vector>
#include <map>

namespace dwg {

class CadDocument;
class IDwgStreamWriter;
class DwgFileHeaderWriterAC15 : public DwgFileHeaderWriterBase
{
    std::map<std::string, std::pair<DwgSectionLocatorRecord, std::ostringstream *>> _records;
    static std::vector<unsigned char> _endSentinel;

public:
    DwgFileHeaderWriterAC15(std::ofstream *stream, Encoding encoding, CadDocument *model);
    void addSection(const std::string &name, std::ostream *stream, bool isCompressed, int decompsize = 0x7400) override;
    void writeFile() override;

protected:
    int handleSectionOffset() const override;
    int fileHeaderSize() const override;

private:
    void setRecordSeekers();
    void writeFileHeader();
    void writeRecord(IDwgStreamWriter *writer, const DwgSectionLocatorRecord &record);
    void writeRecordStreams();
};

}// namespace dwg
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

#include <dwg/CadDocument.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>

namespace dwg {

DwgObjectWriter::DwgObjectWriter(std::ostream *stream, CadDocument *document, Encoding encoding, bool writeXRecords,
                                 bool writeXData)
    : DwgSectionIO(document->header()->version())
{
}
DwgObjectWriter::~DwgObjectWriter() {}

std::string DwgObjectWriter::sectionName() const
{
    return std::string();
}

void DwgObjectWriter::write() {}

std::map<unsigned long long, long long> DwgObjectWriter::handleMap() const
{
    return std::map<unsigned long long, long long>();
}

bool DwgObjectWriter::writeXRecords() const
{
    return false;
}

bool DwgObjectWriter::writeXData() const
{
    return false;
}

void DwgObjectWriter::writeLTypeControlObject() {}

void DwgObjectWriter::writeBlockControl() {}

void DwgObjectWriter::writeTable() {}

void DwgObjectWriter::writeEntries() {}

void DwgObjectWriter::writeBlockEntities() {}

void DwgObjectWriter::writeAppId(AppId *app) {}

void DwgObjectWriter::writeBlockRecord(BlockRecord *blkRecord) {}

void DwgObjectWriter::writeBlockHeader(BlockRecord *record) {}

void DwgObjectWriter::writeBlockBegin(Block *block) {}

void DwgObjectWriter::writeBlockEnd(BlockEnd *blkEnd) {}

void DwgObjectWriter::writeLayer(Layer *layer) {}

void DwgObjectWriter::writeLineType(LineType *ltype) {}

void DwgObjectWriter::writeTextStyle(TextStyle *style) {}

void DwgObjectWriter::writeUCS(UCS *ucs) {}

void DwgObjectWriter::writeView(View *view) {}

void DwgObjectWriter::writeDimensionStyle(DimensionStyle *dimStyle) {}

void DwgObjectWriter::writeVPort(VPort *vport) {}

}// namespace dwg
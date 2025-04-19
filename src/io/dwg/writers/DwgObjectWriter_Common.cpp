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

#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>

namespace dwg {

void DwgObjectWriter::registerObject(CadObject *cadObject) {}
void DwgObjectWriter::writeSize(std::ostream stream, unsigned int size) {}
void DwgObjectWriter::writeSizeInBits(std::ostream *stream, unsigned long long size) {}
void DwgObjectWriter::writeXrefDependantBit(TableEntry *entry) {}
void DwgObjectWriter::writeCommonData(CadObject *cadObject) {}
void DwgObjectWriter::writeCommonNonEntityData(CadObject *cadObject) {}
void DwgObjectWriter::writeCommonEntityData(Entity *entity) {}
void DwgObjectWriter::writeEntityMode(Entity *entity) {}
void DwgObjectWriter::writeExtendedData(ExtendedDataDictionary *data) {}
void DwgObjectWriter::writeExtendedDataEntry(AppId *app, ExtendedData *entry) {}
void DwgObjectWriter::writeReactorsAndDictionaryHandle(CadObject *cadObject) {}
unsigned char DwgObjectWriter::getEntMode(Entity *entity)
{
    unsigned char ch = '0';
    return ch;
}

}// namespace dwg
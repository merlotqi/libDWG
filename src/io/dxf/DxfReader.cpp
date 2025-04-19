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

#include <dwg/io/dxf/DxfReader.h>

namespace dwg {

DxfReader::DxfReader(const std::string &filename) {}

DxfReader::DxfReader(std::ifstream *stream) {}

bool DxfReader::isBinary() const
{
    return false;
}

CadDocument *DxfReader::read()
{
    return nullptr;
}

CadHeader *DxfReader::readHeader()
{
    return nullptr;
}

CadDocument *DxfReader::readTables()
{
    return nullptr;
}

std::vector<Entity *> DxfReader::readEntities()
{
    return std::vector<Entity *>();
}

void DxfReader::readBlocks() {}

void DxfReader::readEntitiesPrivate() {}

void DxfReader::readObjects() {}

void DxfReader::readThumbnailImage() {}

IDxfStreamReader *DxfReader::getReader()
{
    return nullptr;
}

IDxfStreamReader *DxfReader::goToSection(const std::string &sectionName)
{
    return nullptr;
}

IDxfStreamReader *DxfReader::createReader(bool isBinary, bool isAC1009Format)
{
    return nullptr;
}

}// namespace dwg
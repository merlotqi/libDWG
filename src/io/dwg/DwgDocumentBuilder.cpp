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

#include <dwg/io/dwg/DwgDocumentBuilder_p.h>

namespace dwg {

DwgDocumentBuilder::DwgDocumentBuilder(ACadVersion version, CadDocument *document,
                                       const DwgReaderConfiguration &configuration)
    : CadDocumentBuilder(version, document), _configuration(configuration)
{
}

DwgDocumentBuilder::~DwgDocumentBuilder() {}

DwgReaderConfiguration DwgDocumentBuilder::configuration() const
{
    return _configuration;
}

DwgHeaderHandlesCollection DwgDocumentBuilder::headerHandles() const
{
    return _headerHandles;
}

void DwgDocumentBuilder::setHeaderHandles(const DwgHeaderHandlesCollection &headerHandles)
{
    _headerHandles = headerHandles;
}

std::vector<CadBlockRecordTemplate *> DwgDocumentBuilder::blockRecordTemplates() const
{
    return _blockRecordTemplates;
}

std::vector<CadBlockRecordTemplate *> &DwgDocumentBuilder::blockRecordTemplates()
{
    return _blockRecordTemplates;
}

void DwgDocumentBuilder::setBlockRecordTemplates(const std::vector<CadBlockRecordTemplate *> &value)
{
    _blockRecordTemplates = value;
}

std::vector<Entity *> DwgDocumentBuilder::paperSpaceEntities() const
{
    return _paperSpaceEntities;
}

std::vector<Entity *> &DwgDocumentBuilder::paperSpaceEntities()
{
    return _paperSpaceEntities;
}

std::vector<Entity *> DwgDocumentBuilder::modelSpaceEntities() const
{
    return _modelSpaceEntities;
}

std::vector<Entity *> &DwgDocumentBuilder::modelSpaceEntities()
{
    return _modelSpaceEntities;
}

bool DwgDocumentBuilder::keepUnknownEntities() const
{
    return _configuration.keepUnknownEntities();
}

bool DwgDocumentBuilder::keepUnknownNonGraphicalObjects() const
{
    return _configuration.keepUnknownNonGraphicalObjects();
}

void DwgDocumentBuilder::buildDocument() {}

}// namespace dwg
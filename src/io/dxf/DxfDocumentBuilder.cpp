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

#include <dwg/io/dxf/DxfDocumentBuilder_p.h>

namespace dwg {

DxfDocumentBuilder::DxfDocumentBuilder(ACadVersion version, CadDocument *document,
                                       const DxfReaderConfiguration &configuration)
    : CadDocumentBuilder(version, document), _configuration(configuration)
{
}

DxfDocumentBuilder::~DxfDocumentBuilder() {}

DxfReaderConfiguration DxfDocumentBuilder::configuration() const
{
    return _configuration;
}

bool DxfDocumentBuilder::keepUnknownEntities() const
{
    return _configuration.keepUnknownEntities();
}

bool DxfDocumentBuilder::keepUnknownNonGraphicalObjects() const
{
    return _configuration.keepUnknownNonGraphicalObjects();
}

std::set<unsigned long long> DxfDocumentBuilder::modelSpaceEntities() const
{
    return _modelSpaceEntities;
}

std::set<unsigned long long> &DxfDocumentBuilder::modelSpaceEntities()
{
    return _modelSpaceEntities;
}

void DxfDocumentBuilder::buildDocument() {}

std::vector<Entity *> DxfDocumentBuilder::buildEntities()
{
    return std::vector<Entity *>();
}

void DxfDocumentBuilder::assignOwner() {}

}// namespace dwg
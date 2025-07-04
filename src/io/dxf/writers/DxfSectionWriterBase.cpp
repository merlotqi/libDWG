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
#include <dwg/DxfFileToken_p.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dxf/writers/DxfSectionWriterBase_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>

namespace dwg {

DxfSectionWriterBase::DxfSectionWriterBase(IDxfStreamWriter *writer, CadDocument *document, CadObjectHolder *holder,
                                           DxfWriterConfiguration configuration)
    : _writer(writer), _document(document), _holder(holder), _configuration(configuration)
{
}

DxfSectionWriterBase::~DxfSectionWriterBase() {}

void DxfSectionWriterBase::write()
{
    _writer->write(DxfCode::Start, DxfFileToken::BeginSection);
    _writer->write(DxfCode::SymbolTableName, sectionName());

    writeSection();

    _writer->write(DxfCode::Start, DxfFileToken::EndSection);
}

ACadVersion DxfSectionWriterBase::version() const
{
    return _document->header()->version();
}

CadObjectHolder *DxfSectionWriterBase::holder()
{
    return _holder;
}

void DxfSectionWriterBase::writeCommonObjectData(CadObject *object) {}

void DxfSectionWriterBase::writeExtendedData(ExtendedDataDictionary *xdata) {}

void DxfSectionWriterBase::writeCommonEntityData(Entity *entity) {}

void DxfSectionWriterBase::writeLongTextValue(int code, int subcode, const std::string &text) {}

}// namespace dwg
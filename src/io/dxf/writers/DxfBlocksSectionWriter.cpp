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
#include <dwg/DxfCode.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/blocks/Block.h>
#include <dwg/blocks/BlockEnd.h>
#include <dwg/entities/collection/EntityCollection.h>
#include <dwg/io/dxf/CadObjectHolder_p.h>
#include <dwg/io/dxf/writers/DxfBlocksSectionWriter_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/Layer.h>

namespace dwg {

DxfBlocksSectionWriter::DxfBlocksSectionWriter(IDxfStreamWriter *writer, CadDocument *document,
                                               CadObjectHolder *objectHolder,
                                               const DxfWriterConfiguration &configuration)
    : DxfSectionWriterBase(writer, document, objectHolder, configuration)
{
}

DxfBlocksSectionWriter::~DxfBlocksSectionWriter() {}

std::string DxfBlocksSectionWriter::sectionName() const
{
    return DxfFileToken::BlocksSection;
}

void DxfBlocksSectionWriter::writeSection()
{
    auto &&brs = _document->blockRecords();
    // for (auto &&b: brs)
    // {
    //     writeBlock(b->blockEntity());
    //     processEntities(b);
    //     writeBlockEnd(b->blockEnd());
    // }
}

void DxfBlocksSectionWriter::writeBlock(Block *block) {}

void DxfBlocksSectionWriter::processEntities(BlockRecord *b)
{
    if (b->name() == BlockRecord::ModelSpaceName || b->name() == BlockRecord::PaperSpaceName)
    {
        for (auto it = b->entities()->begin(); it != b->entities()->end(); ++it)
        {
            _holder->entities().push(*it);
        }
    }
    else
    {
        for (auto it = b->entities()->begin(); it != b->entities()->end(); ++it)
        {
            writeEntity(*it);
        }
    }
}

void DxfBlocksSectionWriter::writeBlockEnd(BlockEnd *block)
{
    _writer->write(DxfCode::Start, block->objectName());
    writeCommonObjectData(block);
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::Entity);
    _writer->write(8, block->layer()->name());
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::BlockEnd);
}

}// namespace dwg
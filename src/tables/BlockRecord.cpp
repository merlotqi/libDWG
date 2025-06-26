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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/blocks/Block.h>
#include <dwg/blocks/BlockEnd.h>
#include <dwg/entities/collection/EntityCollection.h>
#include <dwg/objects/Layout.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/CadDocument.h>

namespace dwg {

BlockRecord::BlockRecord()
{
    _blockEntity = new Block(this);
    _blockEnd = new BlockEnd(this);
    _entities = new EntityCollection(this);
}

BlockRecord::BlockRecord(const std::string &name) : TableEntry(name)
{
    _blockEntity = new Block(this);
    _blockEnd = new BlockEnd(this);
    _entities = new EntityCollection(this);
}

BlockRecord *BlockRecord::ModelSpace()
{
    BlockRecord *record = new BlockRecord(ModelSpaceName);
    Layout *layout = new Layout();
    layout->setName(Layout::ModelLayoutName);
    layout->setAssociatedBlock(record);
    record->setLayout(layout);
    return record;
}

BlockRecord *BlockRecord::PaperSpace()
{
    BlockRecord *record = new BlockRecord(PaperSpaceName);
    Layout *layout = new Layout();
    layout->setName(Layout::PaperLayoutName);
    layout->setAssociatedBlock(record);
    record->setLayout(layout);
    return record;
}

ObjectType BlockRecord::objectType() const
{
    return ObjectType::BLOCK_HEADER;
}

std::string BlockRecord::objectName() const
{
    return DxfFileToken::TableBlockRecord;
}

std::string BlockRecord::subclassMarker() const
{
    return DxfSubclassMarker::BlockRecord;
}

BlockEnd *BlockRecord::blockEnd()
{
    return _blockEnd;
}

void BlockRecord::setBlockEnd(BlockEnd *) {}

Block *BlockRecord::blockEntity() const
{
    return _blockEntity;
}

void BlockRecord::setBlockEntity(Block *) {}

EvaluationGraph *BlockRecord::evaluationGraph() const
{
    return _evaluationGraph;
}

void BlockRecord::setEvaluationGraph(EvaluationGraph *) {}

UnitsType BlockRecord::units() const
{
    return _units;
}

void BlockRecord::setUnits(UnitsType units)
{
    _units = units;
}

BlockTypeFlags BlockRecord::flags() const
{
    return 0;
}

void BlockRecord::setFlags(BlockTypeFlags flags) {}

bool BlockRecord::isExplodable() const
{
    return _isExplodable;
}

void BlockRecord::setIsExplodable(bool explodable)
{
    _isExplodable = explodable;
}

bool BlockRecord::isDynamic() const
{
    return false;
}

bool BlockRecord::hasAttributes() const
{
    return false;
}

bool BlockRecord::canScale() const
{
    return false;
}

void BlockRecord::setCanScale(bool scaleable) {}

std::vector<unsigned char> BlockRecord::preview() const
{
    return _preview;
}

void BlockRecord::setPreview(const std::vector<unsigned char> &preview)
{
    _preview = preview;
}

Layout *BlockRecord::layout() const
{
    return _layout;
}

void BlockRecord::setLayout(Layout *layout)
{
    delete _layout;
    _layout = layout;
}

SortEntitiesTable *BlockRecord::sortEntitiesTable() const
{
    return _sortEntitiesTable;
}

void BlockRecord::setSortEntitiesTable(SortEntitiesTable *) {}

std::vector<Viewport *> BlockRecord::viewports() const
{
    return std::vector<Viewport *>();
}

void BlockRecord::assignDocument(CadDocument *doc) 
{
    TableEntry::assignDocument(doc);
    doc->registerCollection(_entities);
}

void BlockRecord::unassignDocument() {}

EntityCollection *BlockRecord::entities()
{
    return _entities;
}

}// namespace dwg
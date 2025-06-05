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

#include <dwg/blocks/BlockTypeFlags.h>
#include <dwg/entities/Entity.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/units/UnitsType.h>
#include <dwg/utils/Delegate.h>
#include <string>
#include <vector>

namespace dwg {

class Layout;
class Block;
class BlockEnd;
class Viewport;
class SortEntitiesTable;
class EvaluationGraph;
class LIBDWG_API BlockRecord : public TableEntry
{
    Block *_blockEntity = nullptr;
    BlockEnd *_blockEnd = nullptr;
    EvaluationGraph *_evaluationGraph = nullptr;
    UnitsType _units;
    BlockTypeFlags _flags;
    bool _isExplodable = false;
    std::vector<unsigned char> _preview;
    Layout *_layout = nullptr;
    SortEntitiesTable *_sortEntitiesTable = nullptr;
    std::vector<Entity *> _entities;

public:
    BlockRecord();
    BlockRecord(const std::string &name);

    static constexpr auto ModelSpaceName = "*Model_Space";
    static constexpr auto PaperSpaceName = "*Paper_Space";

    static BlockRecord *ModelSpace();
    static BlockRecord *PaperSpace();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    BlockEnd *blockEnd();
    void setBlockEnd(BlockEnd *);

    Block *blockEntity() const;
    void setBlockEntity(Block *);

    EvaluationGraph *evaluationGraph() const;
    void setEvaluationGraph(EvaluationGraph *);

    UnitsType units() const;
    void setUnits(UnitsType units);

    BlockTypeFlags flags() const;
    void setFlags(BlockTypeFlags flags);

    bool isExplodable() const;
    void setIsExplodable(bool explodable);

    bool isDynamic() const;
    bool hasAttributes() const;

    bool canScale() const;
    void setCanScale(bool scaleable);

    std::vector<unsigned char> preview() const;
    void setPreview(const std::vector<unsigned char> &preview);

    Layout *layout() const;
    void setLayout(Layout *layout);

    SortEntitiesTable *sortEntitiesTable() const;
    void setSortEntitiesTable(SortEntitiesTable *);

    std::vector<Viewport *> viewports() const;

public:
    std::vector<Entity *> entities() const;
    void addEntity(Entity *);
    void removeEntity(Entity *);
    Delegate<void(CadObject *)> OnAdd;
    Delegate<void(CadObject *)> OnRemove;
};

}// namespace dwg
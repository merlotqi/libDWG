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
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/View.h>
#include <dwg/tables/VPort.h>
#include <dwg/tables/collections/AppIdsTable.h>
#include <dwg/tables/collections/Table.h>
#include <dwg/tables/collections/VPortsTable.h>
#include <dwg/tables/collections/LineTypesTable.h>
#include <dwg/tables/collections/LayersTable.h>
#include <dwg/tables/collections/TextStylesTable.h>
#include <dwg/tables/collections/ViewsTable.h>
#include <dwg/tables/collections/UCSTable.h>
#include <dwg/tables/collections/DimensionStylesTable.h>
#include <dwg/tables/collections/BlockRecordsTable.h>
#include <dwg/CadDocument.h>
#include <dwg/io/dxf/writers/DxfTablesSectionWriter_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>
#include <dwg/objects/Layout.h>

namespace dwg {

DxfTablesSectionWriter::DxfTablesSectionWriter(IDxfStreamWriter *writer, CadDocument *document,
                                               CadObjectHolder *objectHolder,
                                               const DxfWriterConfiguration &configuration)
    : DxfSectionWriterBase(writer, document, objectHolder, configuration)
{
}

DxfTablesSectionWriter::~DxfTablesSectionWriter() {}

std::string DxfTablesSectionWriter::sectionName() const
{
    return DxfFileToken::TablesSection;
}

void DxfTablesSectionWriter::writeSection() 
{
    writeTable(_document->vports());
    writeTable(_document->lineTypes());
    writeTable(_document->layers());
    writeTable(_document->textStyles());
    writeTable(_document->views());
    writeTable(_document->UCSs());
    writeTable(_document->appIds());
    writeTable(_document->dimensionStyles(), DxfSubclassMarker::DimensionStyleTable);
    writeTable(_document->blockRecords());
}

void DxfTablesSectionWriter::writeTable(Table *table, const std::string &subclass) 
{
    _writer->write(DxfCode::Start, DxfFileToken::TableEntry_);
    _writer->write(DxfCode::SymbolTableName, table->objectName());

    writeCommonObjectData(table);

    _writer->write(DxfCode::Subclass, DxfSubclassMarker::Table);

    _writer->write(70, table->size());

    if (!subclass.empty())
    {
        _writer->write(DxfCode::Subclass, subclass);
    }

    for (auto it = table->begin(); it != table->end(); ++it)
    {
        writeEntry(it->second);
    }

    _writer->write(DxfCode::Start, DxfFileToken::EndTable);
}
    
void DxfTablesSectionWriter::writeEntry(TableEntry *entry) 
{
    _writer->write(DxfCode::Start, entry->objectName());

    writeCommonObjectData(entry);

    _writer->write(DxfCode::Subclass, DxfSubclassMarker::TableRecord);
    _writer->write(DxfCode::Subclass, entry->subclassMarker());

    auto ts = dynamic_cast<TextStyle *>(entry);
    if (ts && ts->isShapeFile())
    {
        _writer->write(DxfCode::SymbolTableName, std::string());
    }
    else
    {
        _writer->write(DxfCode::SymbolTableName, entry->name());
    }

    _writer->write(70, (int)entry->flags());

    BlockRecord *block = dynamic_cast<BlockRecord *>(entry);
    DimensionStyle *style = dynamic_cast<DimensionStyle *>(entry);
    Layer *layer = dynamic_cast<Layer *>(entry);
    LineType *ltype = dynamic_cast<LineType *>(entry);
    TextStyle *textStyle = dynamic_cast<TextStyle *>(entry);
    UCS *ucs = dynamic_cast<UCS *>(entry);
    View *view = dynamic_cast<View *>(entry);
    VPort *vport = dynamic_cast<VPort *>(entry);
    if (block)
    {
        writeBlockRecord(block, nullptr);
    }
    else if (style)
    {
        writeDimensionStyle(style, nullptr);
    }
    else if (layer)
    {
        writeLayer(layer, nullptr);
    }
    else if (ltype)
    {
        writeLineType(ltype, nullptr);
    }
    else if (textStyle)
    {
        writeTextStyle(textStyle, nullptr);
    }
    else if (ucs)
    {
        writeUcs(ucs, nullptr);
    }
    else if (view)
    {
        writeView(view, nullptr);
    }
    else if (vport)
    {
        writeVPort(vport, nullptr);
    }
    else
    {

    }

    writeExtendedData(entry->extendedData());
}
    
void DxfTablesSectionWriter::writeBlockRecord(BlockRecord *block, DxfClassMap *clsmap) 
{
    _writer->writeHandle(340, block->layout(), clsmap);

    _writer->write(70, (short) block->units(), clsmap);
    _writer->write(280, (unsigned char) (block->isExplodable() ? 1u : 0u), clsmap);
    _writer->write(281, (unsigned char) (block->canScale() ? 1u : 0u), clsmap);
}
    
void DxfTablesSectionWriter::writeDimensionStyle(DimensionStyle *style, DxfClassMap *clsmap) {}
    
void DxfTablesSectionWriter::writeLayer(Layer *layer, DxfClassMap *clsmap) {}
    
void DxfTablesSectionWriter::writeLineType(LineType *linetype, DxfClassMap *clsmap) {}
    
void DxfTablesSectionWriter::writeTextStyle(TextStyle *textStyle, DxfClassMap *clsmap) {}
    
void DxfTablesSectionWriter::writeUcs(UCS *ucs, DxfClassMap *clsmap) 
{
    _writer->write(10, ucs->origin().X, clsmap);
    _writer->write(20, ucs->origin().Y, clsmap);
    _writer->write(30, ucs->origin().Z, clsmap);

    _writer->write(11, ucs->xAxis().X, clsmap);
    _writer->write(21, ucs->xAxis().Y, clsmap);
    _writer->write(31, ucs->xAxis().Z, clsmap);

    _writer->write(12, ucs->yAxis().X, clsmap);
    _writer->write(22, ucs->yAxis().Y, clsmap);
    _writer->write(32, ucs->yAxis().Z, clsmap);

    _writer->write(71, ucs->orthographicType(), clsmap);
    _writer->write(79, ucs->orthographicViewType(), clsmap);
    _writer->write(146, ucs->elevation(), clsmap);
}
    
void DxfTablesSectionWriter::writeView(View *view, DxfClassMap *clsmap) {}
    
void DxfTablesSectionWriter::writeVPort(VPort *vport, DxfClassMap *clsmap) 
{
    _writer->write(10, vport->bottomLeft(), clsmap);

    _writer->write(11, vport->topRight(), clsmap);

    _writer->write(12, vport->center(), clsmap);

    _writer->write(13, vport->snapBasePoint(), clsmap);

    _writer->write(14, vport->snapSpacing(), clsmap);

    _writer->write(15, vport->gridSpacing(), clsmap);

    _writer->write(16, vport->direction(), clsmap);

    _writer->write(17, vport->target(), clsmap);

    _writer->write(40, vport->viewHeight());
    _writer->write(41, vport->aspectRatio());

    _writer->write(75, vport->snapOn() ? (short) 1 : (short) 0);
    _writer->write(76, vport->showGrid() ? (short) 1 : (short) 0);
}   

}// namespace dwg
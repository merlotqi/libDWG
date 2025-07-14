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

#include <dwg/io/dxf/writers/DxfSectionWriterBase_p.h>

namespace dwg {

class Table;
class TableEntry;
class DxfClassMap;
class BlockRecord;
class DimensionStyle;
class Layer;
class LineType;
class TextStyle;
class UCS;
class View;
class VPort;
class DxfTablesSectionWriter : public DxfSectionWriterBase
{
public:
    DxfTablesSectionWriter(IDxfStreamWriter *writer, CadDocument *document, CadObjectHolder *objectHolder,
                           const DxfWriterConfiguration &configuration);
    ~DxfTablesSectionWriter();

    std::string sectionName() const override;
    void writeSection() override;

private:
    void writeTable(Table *table, const std::string &subclass = std::string());
    void writeEntry(TableEntry *entry);
    void writeBlockRecord(BlockRecord *block, DxfClassMap *clsmap);
    void writeDimensionStyle(DimensionStyle *style, DxfClassMap *clsmap);
    void writeLayer(Layer *layer, DxfClassMap *clsmap);
    void writeLineType(LineType *linetype, DxfClassMap *clsmap);
    void writeTextStyle(TextStyle *textStyle, DxfClassMap *clsmap);
    void writeUcs(UCS *ucs, DxfClassMap *clsmap);
    void writeView(View *view, DxfClassMap *clsmap);
    void writeVPort(VPort *vport, DxfClassMap *clsmap);   
};

}// namespace dwg
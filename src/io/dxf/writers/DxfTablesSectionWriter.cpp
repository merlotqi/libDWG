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
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/io/dxf/writers/DxfTablesSectionWriter_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>
#include <dwg/objects/Layout.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/tables/TextStyle.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/VPort.h>
#include <dwg/tables/View.h>
#include <dwg/tables/collections/AppIdsTable.h>
#include <dwg/tables/collections/BlockRecordsTable.h>
#include <dwg/tables/collections/DimensionStylesTable.h>
#include <dwg/tables/collections/LayersTable.h>
#include <dwg/tables/collections/LineTypesTable.h>
#include <dwg/tables/collections/Table.h>
#include <dwg/tables/collections/TextStylesTable.h>
#include <dwg/tables/collections/UCSTable.h>
#include <dwg/tables/collections/VPortsTable.h>
#include <dwg/tables/collections/ViewsTable.h>
#include <dwg/utils/MathHelper.h>

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

    _writer->write(70, (int) entry->flags());

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

void DxfTablesSectionWriter::writeDimensionStyle(DimensionStyle *style, DxfClassMap *clsmap)
{
    _writer->write(3, style->postFix(), clsmap);
    _writer->write(4, style->alternateDimensioningSuffix(), clsmap);

    _writer->write(40, style->scaleFactor(), clsmap);
    _writer->write(41, style->arrowSize(), clsmap);
    _writer->write(42, style->extensionLineOffset(), clsmap);
    _writer->write(43, style->dimensionLineIncrement(), clsmap);
    _writer->write(44, style->extensionLineExtension(), clsmap);
    _writer->write(45, style->rounding(), clsmap);
    _writer->write(46, style->dimensionLineExtension(), clsmap);
    _writer->write(47, style->plusTolerance(), clsmap);
    _writer->write(48, style->minusTolerance(), clsmap);
    _writer->write(49, style->fixedExtensionLineLength(), clsmap);
    _writer->write(50, style->joggedRadiusDimensionTransverseSegmentAngle(), clsmap);

    if (style->textBackgroundFillMode() != DimensionTextBackgroundFillMode::NoBackground)
    {
        _writer->write(69, (short) style->textBackgroundFillMode(), clsmap);
        _writer->write(70, style->textBackgroundColor().index(), clsmap);
    }
    else
    {
        _writer->write(70, 0, clsmap);
    }

    if (style->arcLengthSymbolPosition() != ArcLengthSymbolPosition::AboveDimensionText)
    {
        _writer->write(90, (int) style->arcLengthSymbolPosition());
    }

    _writer->write(140, style->textHeight());
    _writer->write(141, style->centerMarkSize());
    _writer->write(142, style->tickSize());
    _writer->write(143, style->alternateUnitScaleFactor());
    _writer->write(144, style->linearScaleFactor());
    _writer->write(145, style->textVerticalPosition());
    _writer->write(146, style->toleranceScaleFactor());
    _writer->write(147, style->dimensionLineGap());
    _writer->write(148, style->alternateUnitRounding());

    _writer->write(71, (short) (style->generateTolerances() ? 1 : 0));
    _writer->write(72, (short) (style->limitsGeneration() ? 1 : 0));
    _writer->write(73, (short) (style->textInsideHorizontal() ? 1 : 0));
    _writer->write(74, (short) (style->textOutsideHorizontal() ? 1 : 0));
    _writer->write(75, (short) (style->suppressFirstExtensionLine() ? 1 : 0));
    _writer->write(76, (short) (style->suppressSecondExtensionLine() ? 1 : 0));
    _writer->write(77, (short) style->textVerticalAlignment());
    _writer->write(78, (short) style->zeroHandling());
    _writer->write(79, (short) style->angularZeroHandling());

    _writer->write(170, (short) (style->alternateUnitDimensioning() ? 1 : 0));
    _writer->write(171, style->alternateUnitDecimalPlaces());
    _writer->write(172, (short) (style->textOutsideExtensions() ? 1 : 0));
    _writer->write(173, (short) (style->separateArrowBlocks() ? 1 : 0));
    _writer->write(174, (short) (style->textInsideExtensions() ? 1 : 0));
    _writer->write(175, (short) (style->suppressOutsideExtensions() ? 1 : 0));

    _writer->write(176, style->dimensionLineColor().approxIndex(), clsmap);
    _writer->write(177, style->extensionLineColor().approxIndex(), clsmap);
    _writer->write(178, style->textColor().approxIndex(), clsmap);

    _writer->write(179, style->angularDecimalPlaces());

    _writer->write(271, style->decimalPlaces());
    _writer->write(272, style->toleranceDecimalPlaces());
    _writer->write(273, (short) style->alternateUnitFormat());
    _writer->write(274, style->alternateUnitToleranceDecimalPlaces());
    _writer->write(275, (short) style->angularUnit());
    _writer->write(276, (short) style->fractionFormat());
    _writer->write(277, (short) style->linearUnitFormat());
    _writer->write(278, (short) style->decimalSeparator());
    _writer->write(279, (short) style->textMovement());
    _writer->write(280, (unsigned char) style->textHorizontalAlignment());
    _writer->write(281, style->suppressFirstDimensionLine());
    _writer->write(282, style->suppressSecondDimensionLine());
    _writer->write(283, (unsigned char) style->toleranceAlignment());
    _writer->write(284, (unsigned char) style->toleranceZeroHandling());
    _writer->write(285, (unsigned char) style->alternateUnitZeroHandling());
    _writer->write(286, (unsigned char) style->alternateUnitToleranceZeroHandling());
    _writer->write(287, (unsigned char) style->dimensionFit());
    _writer->write(288, style->cursorUpdate());
    _writer->write(289, (unsigned char) style->dimensionTextArrowFit());
    _writer->write(290, style->isExtensionLineLengthFixed());

    _writer->writeHandle(340, style->style(), clsmap);
    _writer->writeHandle(341, style->leaderArrow(), clsmap);
    _writer->writeHandle(342, style->arrowBlock(), clsmap);
    _writer->writeHandle(343, style->dimArrow1(), clsmap);
    _writer->writeHandle(344, style->dimArrow2(), clsmap);

    _writer->write(371, (short) style->dimensionLineWeight());
    _writer->write(372, (short) style->extensionLineWeight());
}

void DxfTablesSectionWriter::writeLayer(Layer *layer, DxfClassMap *clsmap)
{
    int index = layer->color().isTrueColor() ? layer->color().approxIndex() : layer->color().index();
    if (layer->isOn())
    {
        _writer->write(62, index, clsmap);
    }
    else
    {
        _writer->write(62, -index, clsmap);
    }

    if (layer->color().isTrueColor())
    {
        _writer->write(420, (unsigned int) layer->color().trueColor(), clsmap);
    }

    _writer->write(6, layer->lineType()->name(), clsmap);

    _writer->write(290, layer->plotFlag(), clsmap);

    _writer->write(370, (short) layer->lineWeight(), clsmap);

    //_writer->write(390, layer.PlotStyleName(), clsmap);
    _writer->write(390, (unsigned long long) 0, clsmap);
}

void DxfTablesSectionWriter::writeLineType(LineType *linetype, DxfClassMap *clsmap)
{
    _writer->write(3, linetype->description(), clsmap);

    _writer->write(72, (short) linetype->alignment(), clsmap);
    _writer->write(73, (short) linetype->segments().size(), clsmap);
    _writer->write(40, linetype->patternLen());

    for (auto &&s: linetype->segments())
    {
        _writer->write(49, s.length);
        _writer->write(74, (short) s.shapeFlag);

        if (!s.shapeFlag.testFlag(LinetypeShapeFlag::None))
        {
            if (s.shapeFlag.testFlag(LinetypeShapeFlag::Shape))
            {
                _writer->write(75, s.shapeNumber);
            }
            if (s.shapeFlag.testFlag(LinetypeShapeFlag::Text))
            {
                _writer->write(75, (short) 0);
            }

            if (!s.style)
            {
                _writer->write(340, 0uL);
            }
            else
            {
                _writer->write(340, s.style->handle());
            }

            _writer->write(46, s.scale);
            _writer->write(50, MathHelper::RadToDeg(s.rotation));
            _writer->write(44, s.offset.X);
            _writer->write(45, s.offset.Y);
            _writer->write(9, s.text);
        }
    }
}

void DxfTablesSectionWriter::writeTextStyle(TextStyle *textStyle, DxfClassMap *clsmap)
{
    if (!textStyle->filename().empty())
    {
        _writer->write(3, textStyle->filename(), clsmap);
    }

    if (!textStyle->bigFontFilename().empty())
    {
        _writer->write(4, textStyle->bigFontFilename(), clsmap);
    }


    _writer->write(40, textStyle->height(), clsmap);
    _writer->write(41, textStyle->width(), clsmap);
    _writer->write(42, textStyle->lastHeight(), clsmap);
    _writer->write(50, textStyle->obliqueAngle(), clsmap);
    _writer->write(71, (short) textStyle->mirrorFlag(), clsmap);
}

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

    _writer->write(71, (int) ucs->orthographicType(), clsmap);
    _writer->write(79, (int) ucs->orthographicViewType(), clsmap);
    _writer->write(146, ucs->elevation(), clsmap);
}

void DxfTablesSectionWriter::writeView(View *view, DxfClassMap *clsmap)
{
    _writer->write(40, view->height(), clsmap);
    _writer->write(41, view->width(), clsmap);

    _writer->write(42, view->lensLength(), clsmap);
    _writer->write(43, view->frontClipping(), clsmap);
    _writer->write(44, view->backClipping(), clsmap);

    _writer->write(10, view->center(), clsmap);
    _writer->write(11, view->direction(), clsmap);
    _writer->write(12, view->target(), clsmap);

    _writer->write(50, view->angle(), clsmap);

    _writer->write(71, (short) view->viewMode());
    _writer->write(72, view->isUcsAssociated(), clsmap);
    _writer->write(79, (short) view->ucsOrthographicType());

    _writer->write(281, (unsigned char) view->renderMode());

    _writer->write(110, view->ucsOrigin());
    _writer->write(111, view->ucsXAxis());
    _writer->write(112, view->ucsYAxis());

    _writer->write(146, view->ucsElevation());
}

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

/**
 * libDWG - A C++ library for reading and writing DWG and DXF files : CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed : the hope that it will be useful,
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
#include <dwg/CadObject.h>
#include <dwg/DxfClassMap_p.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/io/dxf/CadObjectHolder_p.h>
#include <dwg/io/dxf/writers/DxfObjectsSectionWriter_p.h>
#include <dwg/io/dxf/writers/IDxfStreamWriter_p.h>
#include <dwg/objects/AcdbPlaceHolder.h>
#include <dwg/objects/BookColor.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/DictionaryVariable.h>
#include <dwg/objects/GeoData.h>
#include <dwg/objects/Group.h>
#include <dwg/objects/ImageDefinition.h>
#include <dwg/objects/ImageDefinitionReactor.h>
#include <dwg/objects/Layout.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/Material.h>
#include <dwg/objects/MultiLeaderAnnotContext.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/objects/PlotSettings.h>
#include <dwg/objects/Scale.h>
#include <dwg/objects/SortEntitiesTable.h>
#include <dwg/objects/UnknownNonGraphicalObject.h>
#include <dwg/objects/VisualStyle.h>
#include <dwg/objects/XRecord.h>
#include <dwg/objects/evaluations/EvaluationGraph.h>
#include <dwg/tables/LineType.h>
#include <dwg/utils/MathHelper.h>

namespace dwg {

DxfObjectsSectionWriter::DxfObjectsSectionWriter(IDxfStreamWriter *writer, CadDocument *document,
                                                 CadObjectHolder *objectHolder,
                                                 const DxfWriterConfiguration &configuration)
    : DxfSectionWriterBase(writer, document, objectHolder, configuration)
{
}

DxfObjectsSectionWriter::~DxfObjectsSectionWriter() {}

std::string DxfObjectsSectionWriter::sectionName() const
{
    return DxfFileToken::ObjectsSection;
}

void DxfObjectsSectionWriter::writeSection()
{
    while (!_holder->objects().empty())
    {
        CadObject *item = _holder->objects().front();
        _holder->objects().pop();
        writeObject(item);
    }
}

void DxfObjectsSectionWriter::writeObject(CadObject *co)
{
#define CHECK_OBJECT(T)                                        \
    if (!dynamic_cast<T *>(co))                                \
    {                                                          \
        notify(fmt::format("Object not implemented :{}", #T)); \
    }

    CHECK_OBJECT(AcdbPlaceHolder);
    CHECK_OBJECT(EvaluationGraph);
    CHECK_OBJECT(Material);
    CHECK_OBJECT(MultiLeaderAnnotContext);
    CHECK_OBJECT(VisualStyle);
    CHECK_OBJECT(ImageDefinitionReactor);
    CHECK_OBJECT(UnknownNonGraphicalObject);
    CHECK_OBJECT(XRecord);

#undef CHECK_OBJECT

    if (dynamic_cast<XRecord *>(co) && !_configuration.writeXRecords())
    {
        return;
    }

    _writer->write(DxfCode::Start, co->objectName());

    writeCommonObjectData(co);
    BookColor *bookColor = dynamic_cast<BookColor *>(co);
    CadDictionary *cadDictionary = dynamic_cast<CadDictionary *>(co);
    DictionaryVariable *dictvar = dynamic_cast<DictionaryVariable *>(co);
    GeoData *geodata = dynamic_cast<GeoData *>(co);
    Group *group = dynamic_cast<Group *>(co);
    ImageDefinition *imageDefinition = dynamic_cast<ImageDefinition *>(co);
    Layout *layout = dynamic_cast<Layout *>(co);
    MLineStyle *mlStyle = dynamic_cast<MLineStyle *>(co);
    MultiLeaderStyle *multiLeaderlStyle = dynamic_cast<MultiLeaderStyle *>(co);
    PlotSettings *plotSettings = dynamic_cast<PlotSettings *>(co);
    Scale *scale = dynamic_cast<Scale *>(co);
    SortEntitiesTable *sortensTable = dynamic_cast<SortEntitiesTable *>(co);
    XRecord *record = dynamic_cast<XRecord *>(co);
    if (bookColor)
    {
        writeBookColor(bookColor);
    }
    else if (cadDictionary)
    {
        writeDictionary(cadDictionary);
    }
    else if (dictvar)
    {
        writeDictionaryVariable(dictvar);
    }
    else if (geodata)
    {
        writeGeoData(geodata);
    }
    else if (group)
    {
        writeGroup(group);
    }
    else if (imageDefinition)
    {
        writeImageDefinition(imageDefinition);
    }
    else if (layout)
    {
        writeLayout(layout);
    }
    else if (mlStyle)
    {
        writeMLineStyle(mlStyle);
    }
    else if (multiLeaderlStyle)
    {
        writeMultiLeaderStyle(multiLeaderlStyle);
    }
    else if (plotSettings)
    {
        writePlotSettings(plotSettings);
    }
    else if (scale)
    {
        writeScale(scale);
    }
    else if (sortensTable)
    {
        writeSortentsTable(sortensTable);
    }
    else if (record)
    {
        writeXRecord(record);
    }
    else
    {
        throw std::runtime_error("Object not implemented");
    }

    writeExtendedData(co->extendedData());
}

void DxfObjectsSectionWriter::writeBookColor(BookColor *color)
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::DbColor);

    _writer->write(62, color->color().approxIndex());
    _writer->writeTrueColor(420, color->color());
    _writer->write(430, color->name());
}

void DxfObjectsSectionWriter::writeDictionary(CadDictionary *e) {}

void DxfObjectsSectionWriter::writeDictionaryVariable(DictionaryVariable *dictvar) {}

void DxfObjectsSectionWriter::writePlotSettings(PlotSettings *plot)
{
    DxfClassMap *clsmap = nullptr;

    _writer->write(100, DxfSubclassMarker::PlotSettings);

    _writer->write(1, plot->pageName(), clsmap);
    _writer->write(2, plot->systemPrinterName(), clsmap);

    _writer->write(4, plot->paperSize(), clsmap);

    _writer->write(6, plot->plotViewName(), clsmap);
    _writer->write(7, plot->styleSheet(), clsmap);

    _writer->write(40, plot->unprintableMargin().Left, clsmap);
    _writer->write(41, plot->unprintableMargin().Bottom, clsmap);
    _writer->write(42, plot->unprintableMargin().Right, clsmap);
    _writer->write(43, plot->unprintableMargin().Top, clsmap);
    _writer->write(44, plot->paperWidth(), clsmap);
    _writer->write(45, plot->paperHeight(), clsmap);
    _writer->write(46, plot->plotOriginX(), clsmap);
    _writer->write(47, plot->plotOriginY(), clsmap);
    _writer->write(48, plot->windowLowerLeftX(), clsmap);
    _writer->write(49, plot->windowLowerLeftY(), clsmap);

    _writer->write(140, plot->windowUpperLeftX(), clsmap);
    _writer->write(141, plot->windowUpperLeftY(), clsmap);
    _writer->write(142, plot->numeratorScale(), clsmap);
    _writer->write(143, plot->denominatorScale(), clsmap);

    _writer->write(70, (short) plot->flags(), clsmap);

    _writer->write(72, (short) plot->paperUnits(), clsmap);
    _writer->write(73, (short) plot->paperRotation(), clsmap);
    _writer->write(74, (short) plot->plotType(), clsmap);
    _writer->write(75, (int) plot->scaledFit(), clsmap);
    _writer->write(76, (short) plot->shadePlotMode(), clsmap);
    _writer->write(77, (short) plot->shadePlotResolutionMode(), clsmap);
    _writer->write(78, plot->shadePlotDPI(), clsmap);
    _writer->write(147, plot->printScale(), clsmap);

    _writer->write(148, plot->paperImageOrigin().X, clsmap);
    _writer->write(149, plot->paperImageOrigin().Y, clsmap);
}

void DxfObjectsSectionWriter::writeScale(Scale *scale)
{
    _writer->write(100, DxfSubclassMarker::Scale);

    _writer->write(70, 0);
    _writer->write(300, scale->name());
    _writer->write(140, scale->paperUnits());
    _writer->write(141, scale->drawingUnits());
    _writer->write(290, scale->isUnitScale() ? (short) 1 : (short) 0);
}

void DxfObjectsSectionWriter::writeGeoData(GeoData *geodata)
{
    DxfClassMap *clsmap = nullptr;

    _writer->write(100, DxfSubclassMarker::GeoData, clsmap);

    switch (version())
    {
        case ACadVersion::Unknown:
        case ACadVersion::MC0_0:
        case ACadVersion::AC1_2:
        case ACadVersion::AC1_4:
        case ACadVersion::AC1_50:
        case ACadVersion::AC2_10:
        case ACadVersion::AC1002:
        case ACadVersion::AC1003:
        case ACadVersion::AC1004:
        case ACadVersion::AC1006:
        case ACadVersion::AC1009:
        case ACadVersion::AC1012:
        case ACadVersion::AC1014:
        case ACadVersion::AC1015:
        case ACadVersion::AC1018:
        case ACadVersion::AC1021:
            _writer->write(90, 1, clsmap);
            break;
        case ACadVersion::AC1024:
            _writer->write(90, 2, clsmap);
            break;
        case ACadVersion::AC1027:
        case ACadVersion::AC1032:
            _writer->write(90, 3, clsmap);
            break;
    }

    if (geodata->hostBlock() != nullptr)
    {
        _writer->write(330, geodata->hostBlock()->handle(), clsmap);
    }

    _writer->write(70, (short) geodata->coordinatesType(), clsmap);

    if (version() <= ACadVersion::AC1021)
    {
        _writer->write(40, geodata->referencePoint().Y, clsmap);
        _writer->write(41, geodata->referencePoint().X, clsmap);
        _writer->write(42, geodata->referencePoint().Z, clsmap);
        _writer->write(91, (int) geodata->horizontalUnits(), clsmap);

        _writer->write(10, geodata->designPoint(), clsmap);
        _writer->write(11, XYZ::Zero, clsmap);

        _writer->write(210, geodata->upDirection(), clsmap);

        _writer->write(52, MathHelper::RadToDeg(M_PI / 2.0 - geodata->northDirection().angle()), clsmap);

        _writer->write(43, 1.0, clsmap);
        _writer->write(44, 1.0, clsmap);
        _writer->write(45, 1.0, clsmap);

        _writer->write(301, geodata->coordinateSystemDefinition(), clsmap);
        _writer->write(302, geodata->geoRssTag(), clsmap);

        _writer->write(46, geodata->userSpecifiedScaleFactor(), clsmap);

        _writer->write(303, "", clsmap);
        _writer->write(304, "", clsmap);

        _writer->write(305, geodata->observationFromTag(), clsmap);
        _writer->write(306, geodata->observationToTag(), clsmap);
        _writer->write(307, geodata->observationCoverageTag(), clsmap);

        _writer->write(93, geodata->points().size(), clsmap);
        for (auto &&pt: geodata->points())
        {
            _writer->write(12, pt.source, clsmap);
            _writer->write(13, pt.destination, clsmap);
        }
        _writer->write(96, geodata->faces().size(), clsmap);
        for (auto &&face: geodata->faces())
        {
            _writer->write(97, face.index1, clsmap);
            _writer->write(98, face.index2, clsmap);
            _writer->write(99, face.index3, clsmap);
        }
        _writer->write(3, "CIVIL3D_DATA_BEGIN", clsmap);

        _writer->write(292, false, clsmap);
        _writer->write(14, geodata->referencePoint().to2D(), clsmap);
        _writer->write(15, geodata->referencePoint().to2D(), clsmap);
        _writer->write(93, 0, clsmap);
        _writer->write(94, 0, clsmap);
        _writer->write(293, false, clsmap);

        _writer->write(16, XY::Zero, clsmap);
        _writer->write(17, XY::Zero, clsmap);

        _writer->write(54, MathHelper::RadToDeg(M_PI / 2.0 - geodata->northDirection().angle()), clsmap);
        _writer->write(140, M_PI / 2.0 - geodata->northDirection().angle(), clsmap);

        _writer->write(95, (int) geodata->scaleEstimationMethod(), clsmap);
        _writer->write(141, geodata->userSpecifiedScaleFactor(), clsmap);
        _writer->write(294, geodata->enableSeaLevelCorrection(), clsmap);
        _writer->write(142, geodata->seaLevelElevation(), clsmap);
        _writer->write(143, geodata->coordinateProjectionRadius(), clsmap);

        _writer->write(4, "CIVIL3D_DATA_END", clsmap);
    }
    else
    {
        _writer->write(10, geodata->designPoint(), clsmap);
        _writer->write(11, geodata->referencePoint(), clsmap);
        _writer->write(40, geodata->verticalUnitScale(), clsmap);
        _writer->write(91, (int) geodata->horizontalUnits(), clsmap);
        _writer->write(41, geodata->verticalUnitScale(), clsmap);
        _writer->write(92, (int) geodata->verticalUnits(), clsmap);

        _writer->write(210, geodata->upDirection(), clsmap);

        _writer->write(12, geodata->northDirection(), clsmap);

        _writer->write(95, (int) geodata->scaleEstimationMethod(), clsmap);
        _writer->write(141, geodata->userSpecifiedScaleFactor(), clsmap);
        _writer->write(294, geodata->enableSeaLevelCorrection(), clsmap);
        _writer->write(142, geodata->seaLevelElevation(), clsmap);
        _writer->write(143, geodata->coordinateProjectionRadius(), clsmap);

        writeLongTextValue(301, 303, geodata->coordinateSystemDefinition());

        _writer->write(302, geodata->geoRssTag(), clsmap);
        _writer->write(305, geodata->observationFromTag(), clsmap);
        _writer->write(306, geodata->observationToTag(), clsmap);
        _writer->write(307, geodata->observationCoverageTag(), clsmap);

        _writer->write(93, geodata->points().size(), clsmap);
        for (auto &&pt: geodata->points())
        {
            _writer->write(13, pt.source, clsmap);
            _writer->write(14, pt.destination, clsmap);
        }
        _writer->write(96, geodata->faces().size(), clsmap);
        for (auto &&face: geodata->faces())
        {
            _writer->write(97, face.index1, clsmap);
            _writer->write(98, face.index2, clsmap);
            _writer->write(99, face.index3, clsmap);
        }
    }
}

void DxfObjectsSectionWriter::writeGroup(Group *group)
{
    _writer->write(100, DxfSubclassMarker::Group);

    _writer->write(300, group->description());
    _writer->write(70, group->isUnnamed() ? (short) 1 : (short) 0);
    _writer->write(71, group->selectable() ? (short) 1 : (short) 0);

    for (auto &&entity: group->entities())
    {
        _writer->writeHandle(340, entity);
    }
}

void DxfObjectsSectionWriter::writeImageDefinition(ImageDefinition *definition)
{
    DxfClassMap *clsmap = nullptr;

    _writer->write(100, DxfSubclassMarker::RasterImageDef);

    _writer->write(90, definition->classVersion(), clsmap);
    _writer->write(1, definition->fileName(), clsmap);

    _writer->write(10, definition->size(), clsmap);

    _writer->write(280, definition->isLoaded() ? 1 : 0, clsmap);

    _writer->write(281, (unsigned char) definition->units(), clsmap);
}

void DxfObjectsSectionWriter::writeLayout(Layout *layout)
{
    DxfClassMap *clsmap = nullptr;

    writePlotSettings(layout);

    _writer->write(100, DxfSubclassMarker::Layout);

    _writer->write(1, layout->name(), clsmap);

    //_writer->write(70, (short) 1,clsmap);
    _writer->write(71, layout->tabOrder(), clsmap);

    _writer->write(10, layout->minLimits(), clsmap);
    _writer->write(11, layout->maxLimits(), clsmap);
    _writer->write(12, layout->insertionBasePoint(), clsmap);
    _writer->write(13, layout->origin(), clsmap);
    _writer->write(14, layout->minExtents(), clsmap);
    _writer->write(15, layout->maxExtents(), clsmap);
    _writer->write(16, layout->xAxis(), clsmap);
    _writer->write(17, layout->yAxis(), clsmap);

    _writer->write(146, layout->elevation(), clsmap);

    _writer->write(76, (short) 0, clsmap);

    _writer->writeHandle(330, layout->associatedBlock(), clsmap);
}

void DxfObjectsSectionWriter::writeMLineStyle(MLineStyle *style)
{
    DxfClassMap *clsmap = nullptr;

    _writer->write(100, DxfSubclassMarker::MLineStyle);

    _writer->write(2, style->name(), clsmap);

    _writer->write(70, (short) style->flags(), clsmap);

    _writer->write(3, style->description(), clsmap);

    _writer->write(62, style->fillColor().approxIndex(), clsmap);

    _writer->write(51, style->startAngle(), clsmap);
    _writer->write(52, style->endAngle(), clsmap);
    _writer->write(71, (short) style->elements().size(), clsmap);
    for (auto &&element: style->elements())
    {
        _writer->write(49, element.offset, clsmap);
        _writer->write(62, element.color.index(), clsmap);
        _writer->write(6, element.lineType->name(), clsmap);
    }
}

void DxfObjectsSectionWriter::writeMultiLeaderStyle(MultiLeaderStyle *style)
{
    DxfClassMap *clsmap = nullptr;

    _writer->write(100, DxfSubclassMarker::MLeaderStyle);

    _writer->write(179, 2);
    //	_writer->write(2, style->name(), clsmap);
    _writer->write(170, (short) style->contentType(), clsmap);
    _writer->write(171, (short) style->multiLeaderDrawOrder(), clsmap);
    _writer->write(172, (short) style->leaderDrawOrder(), clsmap);
    _writer->write(90, style->maxLeaderSegmentsPoints(), clsmap);
    _writer->write(40, style->firstSegmentAngleConstraint(), clsmap);
    _writer->write(41, style->secondSegmentAngleConstraint(), clsmap);
    _writer->write(173, (short) style->pathType(), clsmap);
    _writer->writeCmColor(91, style->lineColor(), clsmap);
    _writer->writeHandle(340, style->leaderLineType());
    _writer->write(92, (short) style->leaderLineWeight(), clsmap);
    _writer->write(290, style->enableLanding(), clsmap);
    _writer->write(42, style->landingGap(), clsmap);
    _writer->write(291, style->enableDogleg(), clsmap);
    _writer->write(43, style->landingDistance(), clsmap);
    _writer->write(3, style->description(), clsmap);
    _writer->writeHandle(341, style->arrowhead());
    _writer->write(44, style->arrowheadSize(), clsmap);
    _writer->write(300, style->defaultTextContents(), clsmap);
    _writer->writeHandle(342, style->textStyle());
    _writer->write(174, (short) style->textLeftAttachment(), clsmap);
    _writer->write(178, (short) style->textRightAttachment(), clsmap);
    _writer->write(175, (short) style->textAngle(), clsmap);
    _writer->write(176, (short) style->textAlignment(), clsmap);
    _writer->writeCmColor(93, style->textColor(), clsmap);
    _writer->write(45, style->textHeight(), clsmap);
    _writer->write(292, style->textFrame(), clsmap);
    _writer->write(297, style->textAlignAlwaysLeft(), clsmap);
    _writer->write(46, style->alignSpace(), clsmap);
    _writer->writeHandle(343, style->blockContent());
    _writer->writeCmColor(94, style->blockContentColor(), clsmap);

    //	Write 3 doubles since group codes do not conform vector group codes
    _writer->write(47, style->blockContentScale().X, clsmap);
    _writer->write(49, style->blockContentScale().Y, clsmap);
    _writer->write(140, style->blockContentScale().Z, clsmap);

    _writer->write(293, style->enableBlockContentScale(), clsmap);
    _writer->write(141, style->blockContentRotation(), clsmap);
    _writer->write(294, style->enableBlockContentRotation(), clsmap);
    _writer->write(177, (short) style->blockContentConnection(), clsmap);
    _writer->write(142, style->scaleFactor(), clsmap);
    _writer->write(295, style->overwritePropertyValue(), clsmap);
    _writer->write(296, style->isAnnotative(), clsmap);
    _writer->write(143, style->breakGapSize(), clsmap);
    _writer->write(271, (short) style->textAttachmentDirection(), clsmap);
    _writer->write(272, (short) style->textBottomAttachment(), clsmap);
    _writer->write(273, (short) style->textTopAttachment(), clsmap);
    _writer->write(298, false);//	undocumented
}

void DxfObjectsSectionWriter::writeSortentsTable(SortEntitiesTable *e)
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::SortentsTable);

    _writer->writeHandle(330, e->blockOwner());

    auto sorter = e->sorters();
    for (auto &&item: sorter)
    {
        _writer->writeHandle(331, item.entity);
        _writer->write(5, item.handle);
    }
}

void DxfObjectsSectionWriter::writeXRecord(XRecord *e)
{
    _writer->write(DxfCode::Subclass, DxfSubclassMarker::XRecord);

    for (auto &&item: e->entries())
    {
        _writer->write(item.code, item.value);
    }
}

}// namespace dwg
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
#include <dwg/CadSummaryInfo.h>
#include <dwg/IObservableCadCollection.h>
#include <dwg/ISeqendCollection.h>
#include <dwg/blocks/Block.h>
#include <dwg/blocks/BlockEnd.h>
#include <dwg/classes/DxfClassCollection.h>
#include <dwg/entities/Seqend.h>
#include <dwg/entities/collection/EntityCollection.h>
#include <dwg/header/CadHeader.h>
#include <dwg/objects/BookColor.h>
#include <dwg/objects/CadDictionary.h>
#include <dwg/objects/Group.h>
#include <dwg/objects/ImageDefinition.h>
#include <dwg/objects/Layout.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/MultiLeaderStyle.h>
#include <dwg/objects/Scale.h>
#include <dwg/objects/collections/ColorCollection.h>
#include <dwg/objects/collections/GroupCollection.h>
#include <dwg/objects/collections/ImageDefinitionCollection.h>
#include <dwg/objects/collections/LayoutCollection.h>
#include <dwg/objects/collections/MLeaderStyleCollection.h>
#include <dwg/objects/collections/MLineStyleCollection.h>
#include <dwg/objects/collections/ScaleCollection.h>
#include <dwg/tables/AppId.h>
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
#include <dwg/tables/collections/TextStylesTable.h>
#include <dwg/tables/collections/UCSTable.h>
#include <dwg/tables/collections/VPortsTable.h>
#include <dwg/tables/collections/ViewsTable.h>
#include <fmt/core.h>

namespace dwg {

CadDocument::CadDocument() : CadDocument(ACadVersion::AC1032) {}

CadDocument::CadDocument(ACadVersion version) : CadDocument(true)
{
    _header->setVersion(version);
}

CadDocument::~CadDocument() {}

void CadDocument::createDefaults()
{
    DxfClassCollection::UpdateDxfClasses(this);

    //Header and summary
    _header = new CadHeader(this);
    _summaryInfo = new CadSummaryInfo();

    //The order of the elements is relevant for the handles assignation

    //Initialize tables
    _blockRecords = new BlockRecordsTable(this);
    _layers = new LayersTable(this);
    _dimensionStyles = new DimensionStylesTable(this);
    _textStyles = new TextStylesTable(this);
    _lineTypes = new LineTypesTable(this);
    _views = new ViewsTable(this);
    _ucss = new UCSTable(this);
    _vports = new VPortsTable(this);
    _appIds = new AppIdsTable(this);


    //Root dictionary
    if (!_rootDictionary)
    {
        setRootDictionary(CadDictionary::CreateRoot());
    }
    else
    {
        CadDictionary::CreateDefaultEntries(_rootDictionary);
    }

    updateCollections(true);

    //Default variables
    _appIds->createDefaultEntries();
    _lineTypes->createDefaultEntries();
    _layers->createDefaultEntries();
    _textStyles->createDefaultEntries();
    _dimensionStyles->createDefaultEntries();
    _vports->createDefaultEntries();

    //Blocks
    if (!_blockRecords->contains(BlockRecord::ModelSpaceName))
    {
        BlockRecord *model = BlockRecord::ModelSpace();
        _layouts->add(model->layout());
    }

    if (!_blockRecords->contains(BlockRecord::PaperSpaceName))
    {
        BlockRecord *pspace = BlockRecord::PaperSpace();
        _layouts->add(pspace->layout());
    }
}

void CadDocument::updateCollections(bool createDictionaries)
{
    if (createDictionaries && !_rootDictionary)
    {
        _rootDictionary = CadDictionary::CreateRoot();
    }
    else if (!_rootDictionary)
    {
        return;
    }

    CadDictionary *layout = updateCollection(CadDictionary::AcadLayout, createDictionaries);
    if (layout)
    {
        _layouts = new LayoutCollection(layout);
    }
    CadDictionary *groups = updateCollection(CadDictionary::AcadGroup, createDictionaries);
    if (groups)
    {
        _groups = new GroupCollection(groups);
    }
    CadDictionary *scales = updateCollection(CadDictionary::AcadScaleList, createDictionaries);
    if (scales)
    {
        _scales = new ScaleCollection(scales);
    }
    CadDictionary *mlineStyles = updateCollection(CadDictionary::AcadMLineStyle, createDictionaries);
    if (mlineStyles)
    {
        _mlineStyles = new MLineStyleCollection(mlineStyles);
    }
    CadDictionary *mleaderStyles = updateCollection(CadDictionary::AcadMLeaderStyle, createDictionaries);
    if (mleaderStyles)
    {
        _mleaderStyles = new MLeaderStyleCollection(mleaderStyles);
    }
    CadDictionary *imageDefinitions = updateCollection(CadDictionary::AcadImageDict, createDictionaries);
    if (imageDefinitions)
    {
        _imageDefinitions = new ImageDefinitionCollection(imageDefinitions);
    }
    CadDictionary *colors = updateCollection(CadDictionary::AcadColor, createDictionaries);
    if (colors)
    {
        _colors = new ColorCollection(colors);
    }
}

unsigned long long CadDocument::handle() const
{
    return 0ULL;
}

CadHeader *CadDocument::header() const
{
    return _header;
}

void CadDocument::setHeader(CadHeader *value)
{
    delete _header;
    _header = value;
}

CadSummaryInfo *CadDocument::summaryInfo() const
{
    return _summaryInfo;
}

void CadDocument::setSummaryInfo(CadSummaryInfo *value)
{
    delete _summaryInfo;
    _summaryInfo = value;
}

DxfClassCollection *CadDocument::classes() const
{
    return _classes;
}

void CadDocument::setClasses(DxfClassCollection *value)
{
    delete _classes;
    _classes = value;
}

AppIdsTable *CadDocument::appIds() const
{
    return _appIds;
}

BlockRecordsTable *CadDocument::blockRecords() const
{
    return _blockRecords;
}

DimensionStylesTable *CadDocument::dimensionStyles() const
{
    return _dimensionStyles;
}

LayersTable *CadDocument::layers() const
{
    return _layers;
}

LineTypesTable *CadDocument::lineTypes() const
{
    return _lineTypes;
}

TextStylesTable *CadDocument::textStyles() const
{
    return _textStyles;
}

UCSTable *CadDocument::UCSs() const
{
    return _ucss;
}

ViewsTable *CadDocument::views() const
{
    return _views;
}

VPortsTable *CadDocument::vports() const
{
    return _vports;
}

ColorCollection *CadDocument::colors() const
{
    return _colors;
}

LayoutCollection *CadDocument::layouts() const
{
    return _layouts;
}

GroupCollection *CadDocument::groups() const
{
    return _groups;
}

ScaleCollection *CadDocument::scales() const
{
    return _scales;
}

MLineStyleCollection *CadDocument::mlineStyles() const
{
    return _mlineStyles;
}

ImageDefinitionCollection *CadDocument::imageDefinitions() const
{
    return _imageDefinitions;
}

MLeaderStyleCollection *CadDocument::mleaderStyles() const
{
    return _mleaderStyles;
}

CadDictionary *CadDocument::rootDictionary() const
{
    return _rootDictionary;
}

EntityCollection *CadDocument::entities()
{
    return modelSpace()->entities();
}

BlockRecord *CadDocument::modelSpace() const
{
    return _blockRecords->valueT<BlockRecord *>(BlockRecord::ModelSpaceName);
}

BlockRecord *CadDocument::paperSpace() const
{
    return _blockRecords->valueT<BlockRecord *>(BlockRecord::PaperSpaceName);
}

void CadDocument::registerCollection(IObservableCadCollection *collection)
{
    assert(collection);
    AppIdsTable *appIds = dynamic_cast<AppIdsTable *>(collection);
    if (appIds)
    {
        _appIds = appIds;
        _appIds->setOwner(this);
    }
    BlockRecordsTable *blockRecords = dynamic_cast<BlockRecordsTable *>(collection);
    if (blockRecords)
    {
        _blockRecords = blockRecords;
        _blockRecords->setOwner(this);
    }
    DimensionStylesTable *dimensionStyles = dynamic_cast<DimensionStylesTable *>(collection);
    if (dimensionStyles)
    {
        _dimensionStyles = dimensionStyles;
        _dimensionStyles->setOwner(this);
    }
    LayersTable *layers = dynamic_cast<LayersTable *>(collection);
    if (layers)
    {
        _layers = layers;
        _layers->setOwner(this);
    }
    LineTypesTable *lineTypes = dynamic_cast<LineTypesTable *>(collection);
    if (lineTypes)
    {
        _lineTypes = lineTypes;
        _lineTypes->setOwner(this);
    }
    TextStylesTable *textStyles = dynamic_cast<TextStylesTable *>(collection);
    if (textStyles)
    {
        _textStyles = textStyles;
        _textStyles->setOwner(this);
    }
    UCSTable *ucss = dynamic_cast<UCSTable *>(collection);
    if (ucss)
    {
        _ucss = ucss;
        _ucss->setOwner(this);
    }
    ViewsTable *views = dynamic_cast<ViewsTable *>(collection);
    if (views)
    {
        _views = views;
        _views->setOwner(this);
    }
    VPortsTable *vports = dynamic_cast<VPortsTable *>(collection);
    if (vports)
    {
        _vports = vports;
        _vports->setOwner(this);
    }

    collection->OnAdd.add(this, &CadDocument::onAdd);
    collection->OnRemove.add(this, &CadDocument::onRemove);

    CadObject *cadObject = dynamic_cast<CadObject *>(collection);
    if (cadObject)
    {
        addCadObject(cadObject);
    }

    ISeqendCollection *seqendColleciton = dynamic_cast<ISeqendCollection *>(collection);
    if (seqendColleciton)
    {
        seqendColleciton->OnSeqendAdded.add(this, &CadDocument::onAdd);
        seqendColleciton->OnSeqendRemoved.add(this, &CadDocument::onRemove);
        if (seqendColleciton->seqend() != 0)
        {
            addCadObject(seqendColleciton->seqend());
        }
    }

    auto &&items = collection->rawCadObjects();
    for (auto &&item: items)
    {
        CadDictionary *dictionary = dynamic_cast<CadDictionary *>(item);
        if (dictionary)
        {
            registerCollection(dictionary);
        }
        else
        {
            addCadObject(item);
        }
    }
}

void CadDocument::unregisterCollection(IObservableCadCollection *collection)
{
    assert(collection);
    AppIdsTable *appIds = dynamic_cast<AppIdsTable *>(collection);
    BlockRecordsTable *blockRecords = dynamic_cast<BlockRecordsTable *>(collection);
    DimensionStylesTable *dimensionStyles = dynamic_cast<DimensionStylesTable *>(collection);
    LayersTable *layers = dynamic_cast<LayersTable *>(collection);
    LineTypesTable *lineTypes = dynamic_cast<LineTypesTable *>(collection);
    TextStylesTable *textStyles = dynamic_cast<TextStylesTable *>(collection);
    UCSTable *ucss = dynamic_cast<UCSTable *>(collection);
    ViewsTable *views = dynamic_cast<ViewsTable *>(collection);
    VPortsTable *vports = dynamic_cast<VPortsTable *>(collection);
    if (appIds || blockRecords || dimensionStyles || layers || lineTypes || textStyles || ucss || views || vports)
    {
        throw std::runtime_error("The collection cannot be removed from a document.");
    }
    collection->OnAdd.remove(this, &CadDocument::onAdd);
    collection->OnRemove.remove(this, &CadDocument::onRemove);

    CadObject *cadObject = dynamic_cast<CadObject *>(collection);
    if (cadObject)
    {
        removeCadObject(cadObject);
    }

    ISeqendCollection *seqendCollection = dynamic_cast<ISeqendCollection *>(collection);
    if (seqendCollection)
    {
        seqendCollection->OnSeqendAdded.remove(this, &CadDocument::onAdd);
        seqendCollection->OnSeqendRemoved.remove(this, &CadDocument::onRemove);

        if (seqendCollection->seqend())
        {
            removeCadObject(seqendCollection->seqend());
        }
    }

    auto &&items = collection->rawCadObjects();
    for (auto &&item: items)
    {
        CadDictionary *dictionary = dynamic_cast<CadDictionary *>(item);
        if (dictionary)
        {
            unregisterCollection(dictionary);
        }
        else
        {
            removeCadObject(item);
        }
    }
}

CadDocument::CadDocument(bool createDefaults)
{
    _classes = new DxfClassCollection();
    _cadObjects.insert({handle(), this});
    if (createDefaults)
    {
        this->createDefaults();
    }
}

void CadDocument::setRootDictionary(CadDictionary *dic)
{
    _rootDictionary = dic;
    _rootDictionary->setOwner(this);
    registerCollection(_rootDictionary);
}

CadDictionary *CadDocument::updateCollection(const std::string &dictName, bool createDictionary)
{
    CadDictionary *dictionary = _rootDictionary->valueT<CadDictionary *>(dictName);
    if (dictionary)
    {
        return dictionary;
    }
    else if (createDictionary)
    {
        dictionary = new CadDictionary(dictName);
        _rootDictionary->add(dictName, dictionary);
    }
    return dictionary;
}

void CadDocument::addCadObject(CadObject *cadObject)
{
    if (cadObject->document())
    {
        throw std::runtime_error(
                fmt::format("The item with handle {} is already assigned to a document", cadObject->handle()));
    }

    if (cadObject->handle() == 0 || _cadObjects.find(cadObject->handle()) != _cadObjects.end())
    {
        unsigned long long nextHandle = _header->handleSeed();
        cadObject->setHandle(nextHandle);
        _header->setHandleSeed(nextHandle + 1);
    }
    else if (cadObject->handle() >= _header->handleSeed())
    {
        _header->setHandleSeed(cadObject->handle() + 1);
    }

    _cadObjects.insert({cadObject->handle(), cadObject});

    BlockRecord *record = dynamic_cast<BlockRecord *>(cadObject);
    if (record)
    {
        addCadObject(record->blockEntity());
        addCadObject(record->blockEnd());
    }
    cadObject->assignDocument(this);
}

void CadDocument::removeCadObject(CadObject *cadObject) {}

void CadDocument::onAdd(CadObject *item)
{
    assert(item);
    CadDictionary *dictionary = dynamic_cast<CadDictionary *>(item);
    if (dictionary)
    {
        registerCollection(dictionary);
    }
    else
    {
        addCadObject(item);
    }
}

void CadDocument::onRemove(CadObject *item)
{
    assert(item);
    CadDictionary *dictionary = dynamic_cast<CadDictionary *>(item);
    if (dictionary)
    {
        unregisterCollection(dictionary);
    }
    else
    {
        removeCadObject(item);
    }
}

}// namespace dwg
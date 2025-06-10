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
#include <dwg/classes/DxfClassCollection.h>
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

namespace dwg {

CadDocument::CadDocument() : CadDocument(ACadVersion::AC1018) {}

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
    if (createDictionaries && !this->_rootDictionary)
    {
        this->_rootDictionary = CadDictionary::CreateRoot();
    }
    else if (!this->_rootDictionary)
    {
        return;
    }

    CadDictionary *layout = nullptr;
    if (this->updateCollection(CadDictionary::AcadLayout, createDictionaries, &layout))
    {
        this->_layouts = new LayoutCollection(layout);
    }
    CadDictionary *groups = nullptr;
    if (this->updateCollection(CadDictionary::AcadGroup, createDictionaries, &groups))
    {
        this->_groups = new GroupCollection(groups);
    }
    CadDictionary *scales = nullptr;
    if (this->updateCollection(CadDictionary::AcadScaleList, createDictionaries, &scales))
    {
        this->_scales = new ScaleCollection(scales);
    }
    CadDictionary *mlineStyles = nullptr;
    if (this->updateCollection(CadDictionary::AcadMLineStyle, createDictionaries, &mlineStyles))
    {
        this->_mlineStyles = new MLineStyleCollection(mlineStyles);
    }
    CadDictionary *mleaderStyles = nullptr;
    if (this->updateCollection(CadDictionary::AcadMLeaderStyle, createDictionaries, &mleaderStyles))
    {
        this->_mleaderStyles = new MLeaderStyleCollection(mleaderStyles);
    }
    CadDictionary *imageDefinitions = nullptr;
    if (this->updateCollection(CadDictionary::AcadImageDict, createDictionaries, &imageDefinitions))
    {
        this->_imageDefinitions = new ImageDefinitionCollection(imageDefinitions);
    }
    CadDictionary *colors = nullptr;
    if (this->updateCollection(CadDictionary::AcadColor, createDictionaries, &colors))
    {
        this->_colors = new ColorCollection(colors);
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

void CadDocument::addEntity(Entity *) {}

void CadDocument::removeEntity(Entity *) {}

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

}

CadDocument::CadDocument(bool createDefaults)
{
    _classes = new DxfClassCollection();
    _cadObjects.insert({this->handle(), this});
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

void CadDocument::setAppIds(AppIdsTable *) {}

void CadDocument::setBlockRecords(BlockRecordsTable *) {}

void CadDocument::setDimensionStyles(DimensionStylesTable *) {}

void CadDocument::setLayers(LayersTable *) {}

void CadDocument::setLineTypes(LineTypesTable *) {}

void CadDocument::setTextStyles(TextStylesTable *) {}

void CadDocument::setUCSs(UCSTable *) {}

void CadDocument::setViews(ViewsTable *) {}

void CadDocument::setVPorts(VPortsTable *) {}

bool CadDocument::updateCollection(const std::string &dictName, bool createDictionary, CadDictionary **dictionary)
{
    if (_rootDictionary->tryGetEntryT<CadDictionary>(dictName, dictionary))
    {
        return true;
    }
    else if (createDictionary)
    {
        *dictionary = new CadDictionary(dictName);
        _rootDictionary->add(dictName, *dictionary);
    }
    return (*dictionary != nullptr);
}

void CadDocument::addCadObject(CadObject *cadObject) {}

void CadDocument::removeCadObject(CadObject *cadObject) {}

void CadDocument::onAdd(CadObject *) {}

void CadDocument::onRemove(CadObject *) {}

}// namespace dwg
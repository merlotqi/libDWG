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
#include <dwg/entities/Viewport.h>
#include <dwg/objects/Layout.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/UCS.h>
#include <dwg/tables/collections/BlockRecordsTable.h>
#include <dwg/objects/collections/LayoutCollection.h>

namespace dwg {

Layout::Layout(const std::string &name)
    : _layoutFlags(static_cast<int>(LayoutFlag::None)), _tabOrder(0), _minLimits(XY(-20.0, -7.5)),
      _maxLimits(XY(277.0, 202.5)), _insertionBasePoint(XYZ::Zero), _minExtents(XYZ(25.7, 19.5, 0.0)),
      _maxExtents(XYZ(231.3, 175.5, 0.0)), _elevation(0.0), _origin(XYZ::Zero), _xaxis(XYZ::AxisX), _yaxis(XYZ::AxisY),
      _ucsOrthographicType(OrthographicType::None), _associatedBlock(nullptr), _viewport(nullptr), _ucs(nullptr),
      _baseUCS(nullptr)
{
    _name = name;
}

ObjectType Layout::objectType() const
{
    return ObjectType::LAYOUT;
}

std::string Layout::objectName() const
{
    return DxfFileToken::ObjectLayout;
}

std::string Layout::subclassMarker() const
{
    return DxfSubclassMarker::Layout;
}

LayoutFlags Layout::layoutFlags() const
{
    return _layoutFlags;
}

void Layout::setLayoutFlags(LayoutFlags value)
{
    _layoutFlags = value;
}

int Layout::tabOrder() const
{
    return _tabOrder;
}

void Layout::setTabOrder(int value)
{
    _tabOrder = value;
}

XY Layout::minLimits() const
{
    return _minLimits;
}

void Layout::setMinLimits(const XY &value)
{
    _minLimits = value;
}

XY Layout::maxLimits() const
{
    return _maxLimits;
}

void Layout::setMaxLimits(const XY &value)
{
    _maxLimits = value;
}

XYZ Layout::insertionBasePoint() const
{
    return _insertionBasePoint;
}

void Layout::setInsertionBasePoint(const XYZ &value)
{
    _insertionBasePoint = value;
}

XYZ Layout::minExtents() const
{
    return _minExtents;
}

void Layout::setMinExtents(const XYZ &value)
{
    _minExtents = value;
}

XYZ Layout::maxExtents() const
{
    return _maxExtents;
}

void Layout::setMaxExtents(const XYZ &value)
{
    _maxExtents = value;
}

double Layout::elevation() const
{
    return _elevation;
}

void Layout::setElevation(double value)
{
    _elevation = value;
}

XYZ Layout::origin() const
{
    return _origin;
}

void Layout::setOrigin(const XYZ &value)
{
    _origin = value;
}

XYZ Layout::xAxis() const
{
    return _xaxis;
}

void Layout::setXAxis(const XYZ &value)
{
    _xaxis = value;
}

XYZ Layout::yAxis() const
{
    return _yaxis;
}

void Layout::setYAxis(const XYZ &value)
{
    _yaxis = value;
}

OrthographicType Layout::ucsOrthographicType() const
{
    return _ucsOrthographicType;
}

void Layout::setUcsOrthographicType(OrthographicType value)
{
    _ucsOrthographicType = value;
}

BlockRecord *Layout::associatedBlock() const
{
    return _associatedBlock;
}

void Layout::setAssociatedBlock(BlockRecord *value)
{
    _associatedBlock = value;
}

Viewport *Layout::viewport() const
{
    return _viewport;
}

void Layout::setViewport(Viewport *value)
{
    _viewport = value;
}

UCS *Layout::ucs() const
{
    return _ucs;
}

void Layout::setUCS(UCS *value)
{
    _ucs = value;
}

UCS *Layout::baseUCS() const
{
    return _baseUCS;
}

void Layout::setBaseUCS(UCS *value)
{
    _baseUCS = value;
}

bool Layout::isPaperSpace() const
{
    return false;
}

std::vector<Viewport *> Layout::viewports() const
{
    return std::vector<Viewport *>();
}

void Layout::assignDocument(CadDocument *doc) 
{
    PlotSettings::assignDocument(doc);
    if (_associatedBlock)
    {
        doc->blockRecords()->add(_associatedBlock);
        doc->blockRecords()->OnRemove.add(this, &Layout::onRemoveBlockRecord);
    }
}

void Layout::unassignDocument() {}

void Layout::onRemoveBlockRecord(CadObject *object) 
{
    if (_associatedBlock == object)
    {
        _document->layouts()->remove(_name);
    }
}

}// namespace dwg
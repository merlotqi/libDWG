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
#include <dwg/entities/Viewport.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/objects/Scale.h>
#include <dwg/CadDocument.h>
#include <dwg/objects/collections/ScaleCollection.h>

namespace dwg {

Viewport::Viewport() {}

Viewport::~Viewport() {}

ObjectType Viewport::objectType() const
{
    return ObjectType::VIEWPORT;
}

std::string Viewport::objectName() const
{
    return DxfFileToken::EntityViewport;
}

std::string Viewport::subclassMarker() const
{
    return DxfSubclassMarker::Viewport;
}

XYZ Viewport::center() const
{
    return _center;
}

void Viewport::setCenter(const XYZ &value)
{
    _center = value;
}

double Viewport::width() const
{
    return _width;
}

void Viewport::setWidth(double value)
{
    _width = value;
}

double Viewport::height() const
{
    return _height;
}

void Viewport::setHeight(double value)
{
    _height = value;
}

short Viewport::id() const
{
    IHandledCadObject *obj = owner();
    BlockRecord *record = dynamic_cast<BlockRecord *>(obj);
    if (record)
    {
        short id = 0;
    }
    return 0;
}

XY Viewport::viewCenter() const
{
    return _viewCenter;
}

void Viewport::setViewCenter(const XY &value)
{
    _viewCenter = value;
}

XY Viewport::snapBase() const
{
    return _snapBase;
}

void Viewport::setSnapBase(const XY &value)
{
    _snapBase = value;
}

XY Viewport::snapSpacing() const
{
    return _snapSpacing;
}

void Viewport::setSnapSpacing(const XY &value)
{
    _snapSpacing = value;
}

XY Viewport::gridSpacing() const
{
    return _gridSpacing;
}

void Viewport::setGridSpacing(const XY &value)
{
    _gridSpacing = value;
}

XYZ Viewport::viewDirection() const
{
    return _viewDirection;
}

void Viewport::setViewDirection(const XYZ &value)
{
    _viewDirection = value;
}

XY Viewport::viewTarget() const
{
    return _viewTarget;
}

void Viewport::setViewTarget(const XY &value)
{
    _viewTarget = value;
}

double Viewport::lensLength() const
{
    return _lensLength;
}

void Viewport::setLensLength(double value)
{
    _lensLength = value;
}

double Viewport::frontClipPlane() const
{
    return _frontClipPlane;
}

void Viewport::setFrontClipPlane(double value)
{
    _frontClipPlane = value;
}

double Viewport::backClipPlane() const
{
    return _backClipPlane;
}

void Viewport::setBackClipPlane(double value)
{
    _backClipPlane = value;
}

double Viewport::viewHeight() const
{
    return _viewHeight;
}

void Viewport::setViewHeight(double value)
{
    _viewHeight = value;
}

double Viewport::viewWidth() const
{
    return _viewHeight / _height * _width;
}

double Viewport::snapAngle() const
{
    return _snapAngle;
}

void Viewport::setSnapAngle(double value)
{
    _snapAngle = value;
}

double Viewport::twistAngle() const
{
    return _twistAngle;
}

void Viewport::setTwistAngle(double value)
{
    _twistAngle = value;
}

short Viewport::circleZoomPercent() const
{
    return _circleZoomPercent;
}

void Viewport::setCircleZoomPercent(short value)
{
    _circleZoomPercent = value;
}

std::vector<Layer *> Viewport::frozenLayers() const
{
    return _frozenLayers;
}

void Viewport::setFrozenLayers(const std::vector<Layer *> &value)
{
    _frozenLayers = value;
}

ViewportStatusFlags Viewport::status() const
{
    return _status;
}

void Viewport::setStatus(ViewportStatusFlags value)
{
    _status = value;
}

Entity *Viewport::boundary() const
{
    return _boundary;
}

void Viewport::setBoundary(Entity *value)
{
    _boundary = value;
}

std::string Viewport::styleSheetName() const
{
    return _styleSheetName;
}

void Viewport::setStyleSheetName(const std::string &value)
{
    _styleSheetName = value;
}

RenderMode Viewport::renderMode() const
{
    return _renderMode;
}

void Viewport::setRenderMode(RenderMode value)
{
    _renderMode = value;
}

bool Viewport::ucsPerViewport() const
{
    return _ucsPerViewport;
}

void Viewport::setUcsPerViewport(bool value)
{
    _ucsPerViewport = value;
}

bool Viewport::displayUcsIcon() const
{
    return _displayUcsIcon;
}

void Viewport::setDisplayUcsIcon(bool value)
{
    _displayUcsIcon = value;
}

XYZ Viewport::ucsOrigin() const
{
    return _ucsOrigin;
}

void Viewport::setUcsOrigin(const XYZ &value)
{
    _ucsOrigin = value;
}

XYZ Viewport::ucsXAxis() const
{
    return _ucsXAxis;
}

void Viewport::setUcsXAxis(const XYZ &value)
{
    _ucsXAxis = value;
}

XYZ Viewport::ucsYAxis() const
{
    return _ucsYAxis;
}

void Viewport::setUcsYAxis(const XYZ &value)
{
    _ucsYAxis = value;
}

OrthographicType Viewport::ucsOrthographicType() const
{
    return _ucsOrthographicType;
}

void Viewport::setUcsOrthographicType(OrthographicType value)
{
    _ucsOrthographicType = value;
}

double Viewport::elevation() const
{
    return _elevation;
}

void Viewport::setElevation(double value)
{
    _elevation = value;
}

ShadePlotMode Viewport::shadePlotMode() const
{
    return _shadePlotMode;
}

void Viewport::setShadePlotMode(ShadePlotMode value)
{
    _shadePlotMode = value;
}

short Viewport::majorGridLineFrequency() const
{
    return _majorGridLineFrequency;
}

void Viewport::setMajorGridLineFrequency(short value)
{
    _majorGridLineFrequency = value;
}

VisualStyle *Viewport::visualStyle() const
{
    return _visualStyle;
}

void Viewport::setVisualStyle(VisualStyle *value)
{
    _visualStyle = value;
}

bool Viewport::useDefaultLighting() const
{
    return _useDefaultLighting;
}

void Viewport::setUseDefaultLighting(bool value)
{
    _useDefaultLighting = value;
}

LightingType Viewport::defaultLightingType() const
{
    return _defaultLightingType;
}

void Viewport::setDefaultLightingType(LightingType value)
{
    _defaultLightingType = value;
}

double Viewport::brightness() const
{
    return _brightness;
}

void Viewport::setBrightness(double value)
{
    _brightness = value;
}

double Viewport::contrast() const
{
    return _contrast;
}

void Viewport::setContrast(double value)
{
    _contrast = value;
}

Color Viewport::ambientLightColor() const
{
    return _ambientLightColor;
}

void Viewport::setAmbientLightColor(const Color &value)
{
    _ambientLightColor = value;
}

Scale *Viewport::scale() const
{
    return _scale;
}

void Viewport::setScale(Scale *value)
{
    if (_document)
    {
        _scale = updateCollectionT<Scale *>(value, _document->scales());
    }
    else
    {
        _scale = value;
    }
}

double Viewport::scaleFactor() const
{
    return 1.0 / (_viewHeight / _height);
}

bool Viewport::representsPaper() const
{
    return id() == PaperViewId;
}

void Viewport::assignDocument(CadDocument* doc)
{
    Entity::assignDocument(doc);
    _scale = updateCollectionT<Scale *>(_scale, doc->scales());
    _document->scales()->OnRemove.add(this, &Viewport::scaleOnRemove);
}

void Viewport::unassignDocument()
{

}

void Viewport::scaleOnRemove(CadObject* object)
{

}

}// namespace dwg
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

#include <dwg/tables/VPort.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>

namespace dwg {

VPort::VPort() : _ambientColor(Color((short)0)) {}

VPort::VPort(const std::string &name) : TableEntry(name), _ambientColor(Color((short)0)) {}

VPort::~VPort() {}

VPort *VPort::Default() { return new VPort(DefaultName); }

ObjectType VPort::objectType() const { return ObjectType::VPORT; }

std::string VPort::objectName() const { return DxfFileToken::TableVport; }

std::string VPort::subclassMarker() const { return DxfSubclassMarker::VPort; }

XY VPort::bottomLeft() const { return _bottomLeft; }

void VPort::setBottomLeft(const XY &value) { _bottomLeft = value; }

XY VPort::topRight() const { return _topRight; }

void VPort::setTopRight(const XY &value) { _topRight = value; }

XY VPort::center() const { return _center; }

void VPort::setCenter(const XY &value) { _center = value; }

XY VPort::snapBasePoint() const { return _snapBasePoint; }

void VPort::setSnapBasePoint(const XY &value) { _snapBasePoint = value; }

XY VPort::snapSpacing() const { return _snapSpacing; }

void VPort::setSnapSpacing(const XY &value) {_snapSpacing =value; }

XY VPort::gridSpacing() const { return _gridSpacing; }

void VPort::setGridSpacing(const XY &value) { _gridSpacing = value; }

XYZ VPort::direction() const { return _direction; }

void VPort::setDirection(const XYZ &value) { _direction =value; }

XYZ VPort::target() const { return _target; }

void VPort::setTarget(const XYZ &value) { _target = value; }

double VPort::viewHeight() const { return _viewHeight; }

void VPort::setViewHeight(double value) { _viewHeight = value; }

double VPort::aspectRatio() const { return _aspectRatio; }

void VPort::setAspectRatio(double value) { _aspectRatio = value; }

double VPort::lensLength() const { return _lensLength; }

void VPort::setLensLength(double value) { _lensLength = value; }

double VPort::frontClippingPlane() const { return _frontClippingPlane; }

void VPort::setFrontClippingPlane(double value) { _frontClippingPlane = value; }

double VPort::backClippingPlane() const { return _backClippingPlane; }

void VPort::setBackClippingPlane(double value) { _backClippingPlane = value; }

double VPort::snapRotation() const { return _snapRotation; }

void VPort::setSnapRotation(double value) { _snapRotation = value; }

double VPort::twistAngle() const { return _twistAngle; }

void VPort::setTwistAngle(double value) { _twistAngle = value; }

short VPort::circleZoomPercent() const { return _circleZoomPercent; }

void VPort::setCircleZoomPercent(short value) { _circleZoomPercent = value; }

RenderMode VPort::renderMode() const { return _renderMode; }

void VPort::setRenderMode(RenderMode value) { _renderMode = value; }

ViewModeType VPort::viewMode() const { return _viewMode; }

void VPort::setViewMode(ViewModeType value) { _viewMode = value; }

UscIconType VPort::ucsIconDisplay() const { return _ucsIconDisplay; }

void VPort::setUcsIconDisplay(UscIconType value) { _ucsIconDisplay = value; }

bool VPort::snapOn() const { return _snapOn; }

void VPort::setSnapOn(bool value) { _snapOn = value; }

bool VPort::showGrid() const { return _showGrid; }

void VPort::setShowGrid(bool value) { _showGrid = value; }

bool VPort::isometricSnap() const { return _isometricSnap; }

void VPort::setIsometricSnap(bool value) { _isometricSnap = value; }

short VPort::snapIsoPair() const { return _snapIsoPair; }

void VPort::setSnapIsoPair(short value) { _snapIsoPair = value; }

XYZ VPort::origin() const { return _origin; }

void VPort::setOrigin(const XYZ &value) { _origin = value; }

XYZ VPort::xAxis() const { return _xAxis; }

void VPort::setXAxis(const XYZ &value) { _xAxis = value; }

XYZ VPort::yAxis() const { return _yAxis; }

void VPort::setYAxis(const XYZ &value) { _yAxis = value; }

UCS *VPort::namedUcs() const { return _namedUcs; }

void VPort::setNamedUcs(UCS *value) { _namedUcs = value; }

UCS *VPort::baseUcs() const { return _baseUcs; }

void VPort::setBaseUcs(UCS *value) { _baseUcs = value; }

OrthographicType VPort::orthographicType() const { return _orthographicType; }

void VPort::setOrthographicType(OrthographicType value) { _orthographicType = value; }

double VPort::elevation() const { return _elevation; }

void VPort::setElevation(double value) { _elevation = value; }

GridFlags VPort::gridFlags() const { return _gridFlags; }

void VPort::setGridFlags(GridFlags value) { _gridFlags = value; }

short VPort::minorGridLinesPerMajorGridLine() const { return _minorGridLinesPerMajorGridLine; }

void VPort::setMinorGridLinesPerMajorGridLine(short value) { _minorGridLinesPerMajorGridLine = value; }

VisualStyle *VPort::visualStyle() const { return _visualStyle; }

void VPort::setVisualStyle(VisualStyle *value) { _visualStyle = value; }

bool VPort::useDefaultLighting() const { return _useDefaultLighting; }

void VPort::setUseDefaultLighting(bool value) { _useDefaultLighting = value; }

DefaultLightingType VPort::defaultLighting() const { return _defaultLighting; }

void VPort::setDefaultLighting(DefaultLightingType value) { _defaultLighting = value; }

double VPort::brightness() const { return _brightness; }

void VPort::setBrightness(double value) { _brightness = value; }

double VPort::contrast() const { return _contrast; }

void VPort::setContrast(double value) { _contrast = value; }

Color VPort::ambientColor() const { return _ambientColor; }

void VPort::setAmbientColor(const Color &value) { _ambientColor = value;}

}// namespace dwg
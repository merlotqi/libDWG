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

#include <dwg/tables/View.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>

namespace dwg {

View::View(const std::string &name) : TableEntry(name) {}

View::~View() {}

ObjectType View::objectType() const { return ObjectType::VIEW; }

std::string View::objectName() const { return DxfFileToken::TableView; }

std::string View::subclassMarker() const { return DxfSubclassMarker::View; }

double View::height() const { return _height; }

void View::setHeight(double value) { _height = value; }

double View::width() const { return _width; }

void View::setWidth(double value) { _width = value; }

double View::lensLength() const { return _lensLength; }

void View::setLensLength(double value) { _lensLength = value; }

double View::frontClipping() const { return _frontClipping; }

void View::setFrontClipping(double value) { _frontClipping = value; }

double View::backClipping() const { return _backClipping; }

void View::setBackClipping(double value) { _backClipping = value; }

double View::angle() const { return _angle; }

void View::setAngle(double value) { _angle = value; }

ViewModeType View::viewMode() const { return _viewMode; }

void View::setViewMode(ViewModeType value) { _viewMode = value; }

bool View::isUcsAssociated() const { return _isUcsAssociated; }

void View::setIsUcsAssociated(bool value) { _isUcsAssociated = value; }

bool View::isPlottable() const { return _isPlottable; }

void View::setIsPlottable(bool value) { _isPlottable = value; }

RenderMode View::renderMode() const { return _renderMode; }

void View::setRenderMode(RenderMode value) { _renderMode = value; }

XY View::center() const { return _center; }

void View::setCenter(const XY &value) { _center = value; }

XYZ View::direction() const { return _direction; }

void View::setDirection(const XYZ &value) { _direction = value; }

XYZ View::target() const { return _target; }

void View::setTarget(const XYZ &value) { _target = value; }

VisualStyle *View::visualStyle() const { return _visualStyle; }

void View::setVisualStyle(VisualStyle *value) { _visualStyle = value; }

XYZ View::ucsOrigin() const { return _ucsOrigin; }

void View::setUcsOrigin(const XYZ &value) { _ucsOrigin = value; }

XYZ View::ucsXAxis() const { return _ucsXAxis; }

void View::setUcsXAxis(const XYZ &value) { _ucsXAxis = value; }

XYZ View::ucsYAxis() const { return _ucsYAxis; }

void View::setUcsYAxis(const XYZ &value) { _ucsYAxis = value; }

double View::ucsElevation() const { return _ucsElevation; }

void View::setUcsElevation(double value) { _ucsElevation =value; }

OrthographicType View::ucsOrthographicType() const { return _ucsOrthographicType; }

void View::setUcsOrthographicType(OrthographicType value) { _ucsOrthographicType = value; }

}// namespace dwg
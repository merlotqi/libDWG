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
#include <dwg/entities/LwPolyline.h>

namespace dwg {

LwPolyline::LwPolyline(){}

LwPolyline::~LwPolyline(){}

ObjectType LwPolyline::objectType() const{return ObjectType::LWPOLYLINE; }

std::string LwPolyline::objectName() const{ return DxfFileToken::EntityLwPolyline; }

std::string LwPolyline::subclassMarker() const{ return DxfSubclassMarker::LwPolyline; }

LwPolylineFlags LwPolyline::flags() const{ return _flags; }

void LwPolyline::setFlags(LwPolylineFlags value){ _flags = value; }

double LwPolyline::constantWidth() const{ return _constantWidth; }

void LwPolyline::setConstantWidth(double value){ _constantWidth = value; }

double LwPolyline::elevation() const{ return _elevation; }

void LwPolyline::setElevation(double value){ _elevation = value; }

double LwPolyline::thickness() const{ return _thickness; }

void LwPolyline::setThickness(double value){ _thickness = value; }

XYZ LwPolyline::normal() const{ return _normal; }

void LwPolyline::setNormal(const XYZ &value){ _normal = value; }

std::vector<LwPolyline::Vertex> LwPolyline::vertices() const{ return _vertices; }

void LwPolyline::setVertices(const std::vector<Vertex> &value){ _vertices =value; }

bool LwPolyline::isClosed() const{ return _isClosed; }

void LwPolyline::setIsClosed(bool value){ _isClosed = value; }

}// namespace dwg
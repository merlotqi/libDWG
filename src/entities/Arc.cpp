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

#include <dwg/entities/Arc.h>

namespace dwg {

DG_Arc::DG_Arc() : _startangle(0.0), _endangle(2 * M_PI) {}

DG_Arc::~DG_Arc() {}

DG_ObjectType DG_Arc::ObjectType() const { return DG_ObjectType::ARC; }

std::string DG_Arc::ObjectName() const { return DG_DxfFileToken::EntityArc; }

std::string DG_Arc::SubclassMarker() const { return DG_DxfSubclassMarker::Arc; }

double DG_Arc::StartAngle() const { return _startangle; }

double DG_Arc::EndAngle() const { return _endangle; }

void DG_Arc::StartAngle(double value) { _startangle = value; }

void DG_Arc::EndAngle(double value) { _endangle = value; }

}// namespace dwg

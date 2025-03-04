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

#include <dwg/objects/MLineStyle.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>

namespace dwg {

MLineStyle *MLineStyle::Default()
{
    return new MLineStyle(DefaultName);
}

MLineStyle::MLineStyle() : _startAngle(M_PI / 2.0), _endAngle(M_PI / 2.0), _flags(0) {}

MLineStyle::MLineStyle(const std::string &name) : _name(name) {}

ObjectType MLineStyle::objectType() const { return ObjectType::MLINESTYLE; }

std::string MLineStyle::objectName() const { return DxfFileToken::ObjectMLineStyle; }

std::string MLineStyle::subclassMarker() const { return DxfSubclassMarker::MLineStyle; }

MLineStyleFlags MLineStyle::flags() const { return _flags; }

void MLineStyle::setFlags(MLineStyleFlags value) { _flags = value; }

std::string MLineStyle::description() const { return _description; }

void MLineStyle::setDescription(const std::string &value) { _description = value; }

Color MLineStyle::fillColor() const { return _fillColor; }

void MLineStyle::setFillColor(const Color &value) { _fillColor = value; }

double MLineStyle::startAngle() const { return _startAngle; }

void MLineStyle::setStartAngle(double value) { _startAngle = value; }

double MLineStyle::endAngle() const { return _endAngle; }

void MLineStyle::setEndAngle(double value) { _endAngle = value; }

std::vector<Element> MLineStyle::elements() const { return _elements; }

std::vector<Element> &MLineStyle::elements() { return _elements; }

void MLineStyle::setElements(const std::vector<Element> &value) { _elements = value; }
    
}// namespace dwg
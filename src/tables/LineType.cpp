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
#include <dwg/tables/LineType.h>

namespace dwg {

LineType::LineType() {}

LineType::LineType(const std::string &name) : TableEntry(name) {}

LineType::~LineType() {}

LineType *LineType::ByLayer()
{
    return new LineType(ByLayerName);
}

LineType *LineType::ByBlock()
{
    return new LineType(ByBlockName);
}

LineType *LineType::Continuous()
{
    return new LineType(ContinuousName);
}

ObjectType LineType::objectType() const
{
    return ObjectType::LTYPE;
}

std::string LineType::objectName() const
{
    return DxfFileToken::TableLinetype;
}

std::string LineType::subclassMarker() const
{
    return DxfSubclassMarker::Linetype;
}

std::string LineType::description() const
{
    return _description;
}

void LineType::setDescription(const std::string &value)
{
    _description = value;
}

double LineType::patternLen() const
{
    double len = 0.0;
    for (auto &&seg: _segments)
    {
        len += seg.length;
    }
    return len;
}

char LineType::alignment() const
{
    return _alignment;
}

void LineType::setAlignment(char value)
{
    _alignment = value;
}

std::vector<LineType::Segment> LineType::segments() const
{
    return _segments;
}

std::vector<LineType::Segment> &LineType::segments()
{
    return _segments;
}

void LineType::setSegments(const std::vector<LineType::Segment> &value)
{
    _segments = value;
}

void LineType::addSegment(LineType::Segment value)
{
    if (value.lineType)
    {
        throw std::invalid_argument(fmt::format("Segment has already a LineType: {}", value.lineType->name()));
    }
    value.lineType = this;
    _segments.push_back(value);
}

LineType::Segment::Segment()
    : length(0.0), shapeFlag(0), shapeNumber(0), offset(XY::Zero), rotation(0.0), scale(1.0), style(nullptr),
      lineType(nullptr)
{
}

}// namespace dwg
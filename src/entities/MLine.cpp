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
#include <dwg/entities/MLine.h>
#include <dwg/objects/MLineStyle.h>
#include <dwg/objects/collections/MLineStyleCollection.h>

namespace dwg {

MLine::MLine() {}

MLine::~MLine() {}

ObjectType MLine::objectType() const
{
    return ObjectType::MLINE;
}

std::string MLine::objectName() const
{
    return DxfFileToken::EntityMLine;
}

std::string MLine::subclassMarker() const
{
    return DxfSubclassMarker::MLine;
}

MLineStyle *MLine::style() const
{
    return _style;
}

void MLine::setStyle(MLineStyle *style)
{
    if (_document)
    {
        _style = updateCollectionT<MLineStyle *>(_style, _document->mlineStyles());
    }
    else
    {
        _style = style;
    }
}

double MLine::scaleFactor() const
{
    return _scaleFactor;
}

void MLine::setScaleFactor(double scale)
{
    _scaleFactor = scale;
}

MLineJustification MLine::justification() const
{
    return _justification;
}

void MLine::setJustification(MLineJustification justification)
{
    _justification = justification;
}

MLineFlags MLine::flags() const
{
    return _flags;
}

void MLine::setFlags(MLineFlags flags)
{
    _flags = flags;
}

XYZ MLine::startPoint() const
{
    return _startPoint;
}

void MLine::setStartPoint(const XYZ &point)
{
    _startPoint = point;
}

XYZ MLine::normal() const
{
    return _normal;
}

void MLine::setNormal(const XYZ &normal)
{
    _normal = normal;
}

std::vector<MLine::Vertex> MLine::vertices() const
{
    return _vertices;
}

void MLine::setVertices(const std::vector<Vertex> &vertices)
{
    _vertices = vertices;
}

void MLine::assignDocument(CadDocument *doc)
{
    Entity::assignDocument(doc);
    _style = this->updateCollectionT<MLineStyle *>(_style, doc->mlineStyles());
    doc->mlineStyles()->OnRemove.add(this, &MLine::mLineStylesOnRemove);
}

void MLine::unassignDocument() {}

void MLine::mLineStylesOnRemove(CadObject *object) {}

}// namespace dwg
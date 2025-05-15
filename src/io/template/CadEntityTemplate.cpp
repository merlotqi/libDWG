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

#include <dwg/io/template/CadEntityTemplate_p.h>

namespace dwg {
    
CadEntityTemplate::CadEntityTemplate(Entity *v) : CadTemplateT<Entity *>(v) {}

void CadEntityTemplate::build(CadDocumentBuilder *builder) {}

void CadEntityTemplate::setUnlinkedReferences() {}

unsigned char CadEntityTemplate::entityMode() const
{
    return _entityMode;
}

void CadEntityTemplate::setEntityMode(unsigned char value)
{
    _entityMode = value;
}

std::optional<unsigned char> CadEntityTemplate::ltypeFlags() const
{
    return _ltypeFlags;
}

void CadEntityTemplate::setLtypeFlags(unsigned char value)
{
    _ltypeFlags = value;
}

std::optional<unsigned long long> CadEntityTemplate::layerHandle() const
{
    return _layerHandle;
}

void CadEntityTemplate::setLayerHandle(unsigned long long value)
{
    _layerHandle = value;
}

std::string CadEntityTemplate::layerName() const
{
    return _layerName;
}

void CadEntityTemplate::setLayerName(const std::string &value)
{
    _layerName = value;
}

std::optional<unsigned long long> CadEntityTemplate::lineTypeHandle() const
{
    return _lineTypeHandle;
}

void CadEntityTemplate::setLineTypeHandle(unsigned long long value)
{
    _lineTypeHandle = value;
}

std::string CadEntityTemplate::lineTypeName() const
{
    return _lineTypeName;
}

void CadEntityTemplate::setLineTypeName(const std::string &value)
{
    _lineTypeName = value;
}

std::optional<unsigned long long> CadEntityTemplate::prevEntity() const
{
    return _prevEntity;
}

void CadEntityTemplate::setPrevEntity(unsigned long long value)
{
    _prevEntity = value;
}

std::optional<unsigned long long> CadEntityTemplate::nextEntity() const
{
    return _nextEntity;
}

void CadEntityTemplate::setNextEntity(unsigned long long value)
{
    _nextEntity = value;
}

std::optional<unsigned long long> CadEntityTemplate::colorHandle() const
{
    return _colorHandle;
}

void CadEntityTemplate::setColorHandle(unsigned long long value)
{
    _colorHandle = value;
}

std::string CadEntityTemplate::bookColorName() const
{
    return _bookColorName;
}

void CadEntityTemplate::setBookColorName(const std::string &value)
{
    _bookColorName = value;
}

std::optional<unsigned long long> CadEntityTemplate::materialHandle() const
{
    return _materialHandle;
}

void CadEntityTemplate::setMaterialHandle(unsigned long long value)
{
    _materialHandle = value;
}

}// namespace dwg
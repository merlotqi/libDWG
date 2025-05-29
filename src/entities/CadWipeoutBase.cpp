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
#include <dwg/entities/CadWipeoutBase.h>
#include <fmt/core.h>

namespace dwg {

CadWipeoutBase::CadWipeoutBase()
    : _classVersion(0), _insertPoint(XYZ::Zero), _uvector(XYZ::AxisX), _vvector(XYZ::AxisY), _size(XY::Zero),
      _flags(ImageDisplayFlag::None), _clippingState(false), _brightness(50), _contrast(50), _fade(0),
      _clipMode(ClipMode::Outside), _clipType(ClipType::Rectangular), _definition(nullptr), _definitionReactor(nullptr)
{
}
CadWipeoutBase::~CadWipeoutBase() {}

int CadWipeoutBase::classVersion() const
{
    return _classVersion;
}

void CadWipeoutBase::setClassVersion(int version)
{
    _classVersion = version;
}

XYZ CadWipeoutBase::insertPoint() const
{
    return _insertPoint;
}

void CadWipeoutBase::setInsertPoint(const XYZ &point)
{
    _insertPoint = point;
}

XYZ CadWipeoutBase::UVector() const
{
    return _uvector;
}

void CadWipeoutBase::setUVector(const XYZ &vector)
{
    _uvector = vector;
}

XYZ CadWipeoutBase::VVector() const
{
    return _vvector;
}

void CadWipeoutBase::setVVector(const XYZ &vector)
{
    _vvector = vector;
}

XY CadWipeoutBase::size() const
{
    return _size;
}

void CadWipeoutBase::setSize(const XY &size)
{
    _size = size;
}

ImageDisplayFlags CadWipeoutBase::flags() const
{
    return _flags;
}

void CadWipeoutBase::setFlags(ImageDisplayFlags flags)
{
    _flags = flags;
}

bool CadWipeoutBase::showImage() const
{
    return _flags & ImageDisplayFlag::ShowImage;
}

void CadWipeoutBase::setShowImage(bool value)
{
    if (value)
        _flags |= ImageDisplayFlag::ShowImage;
    else
        _flags &= ~ImageDisplayFlag::ShowImage;
}

bool CadWipeoutBase::clippingState() const
{
    return _clippingState;
}

void CadWipeoutBase::setClippingState(bool state)
{
    _clippingState = state;
}

unsigned char CadWipeoutBase::brightness() const
{
    return _brightness;
}

void CadWipeoutBase::setBrightness(unsigned char value)
{
    if (value < 0 || value > 100)
        throw std::out_of_range(fmt::format("Brightness value must be between 0 and 100, got {}", value));
    _brightness = value;
}

unsigned char CadWipeoutBase::contrast() const
{
    return _contrast;
}

void CadWipeoutBase::setContrast(unsigned char value)
{
    if (value < 0 || value > 100)
        throw std::out_of_range(fmt::format("Contrast value must be between 0 and 100, got {}", value));
    _contrast = value;
}

unsigned char CadWipeoutBase::fade() const
{
    return _fade;
}

void CadWipeoutBase::setFade(unsigned char value)
{
    if (value < 0 || value > 100)
        throw std::out_of_range(fmt::format("Fade value must be between 0 and 100, got {}", value));
    _fade = value;
}

ClipMode CadWipeoutBase::clipMode() const
{
    return _clipMode;
}

void CadWipeoutBase::setClipMode(ClipMode mode)
{
    _clipMode = mode;
}

ClipType CadWipeoutBase::clipType() const
{
    return _clipType;
}

void CadWipeoutBase::setClipType(ClipType type)
{
    _clipType = type;
}

std::vector<XY> CadWipeoutBase::clipBoundaryVertices() const
{
    return _clipBoundaryVertices;
}

void CadWipeoutBase::setClipBoundaryVertices(const std::vector<XY> &vertices)
{
    _clipBoundaryVertices = vertices;
}

ImageDefinition *CadWipeoutBase::definition() const
{
    return _definition;
}

void CadWipeoutBase::setDefinition(ImageDefinition *definition)
{
    assert(definition);

    if (document())
    {
        // _definition = updateCollection(definition, document()->imageDefinitions());
    }

    _definition = definition;
}

ImageDefinitionReactor *CadWipeoutBase::definitionReactor() const
{
    return _definitionReactor;
}

void CadWipeoutBase::setDefinitionReactor(ImageDefinitionReactor *reactor)
{
    _definitionReactor = reactor;
}

}// namespace dwg
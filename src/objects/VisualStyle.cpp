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
#include <dwg/objects/VisualStyle.h>
namespace dwg {

VisualStyle::VisualStyle() {}

ObjectType VisualStyle::objectType() const
{
    return ObjectType::UNLISTED;
}

std::string VisualStyle::objectName() const
{
    return DxfFileToken::ObjectVisualStyle;
}

std::string VisualStyle::subclassMarker() const
{
    return DxfSubclassMarker::VisualStyle;
}

std::string VisualStyle::rasterFile() const
{
    return _rasterFile;
}

void VisualStyle::setRasterFile(const std::string &value)
{
    _rasterFile = value;
}

std::string VisualStyle::description() const
{
    return _description;
}

void VisualStyle::setDescription(const std::string &value)
{
    _description = value;
}

int VisualStyle::type() const
{
    return _type;
}

void VisualStyle::setType(int value)
{
    _type = value;
}

FaceLightingModelType VisualStyle::faceLightingModel() const
{
    return _faceLightingModel;
}

void VisualStyle::setFaceLightingModel(FaceLightingModelType value)
{
    _faceLightingModel = value;
}

FaceLightingQualityType VisualStyle::faceLightingQuality() const
{
    return _faceLightingQuality;
}

void VisualStyle::setFaceLightingQuality(FaceLightingQualityType value)
{
    _faceLightingQuality = value;
}

FaceColorMode VisualStyle::faceColorMode() const
{
    return _faceColorMode;
}

void VisualStyle::setFaceColorMode(FaceColorMode value)
{
    _faceColorMode = value;
}

FaceModifierType VisualStyle::faceModifiers() const
{
    return _faceModifiers;
}

void VisualStyle::setFaceModifiers(FaceModifierType value)
{
    _faceModifiers = value;
}

double VisualStyle::faceOpacityLevel() const
{
    return _faceOpacityLevel;
}

void VisualStyle::setFaceOpacityLevel(double value)
{
    _faceOpacityLevel = value;
}

double VisualStyle::faceSpecularLevel() const
{
    return _faceSpecularLevel;
}

void VisualStyle::setFaceSpecularLevel(double value)
{
    _faceSpecularLevel = value;
}

Color VisualStyle::color() const
{
    return _color;
}

void VisualStyle::setColor(const Color &value)
{
    _color = value;
}

Color VisualStyle::faceStyleMonoColor() const
{
    return _faceStyleMonoColor;
}

void VisualStyle::setFaceStyleMonoColor(const Color &value)
{
    _faceStyleMonoColor = value;
}

bool VisualStyle::precisionFlag() const
{
    return _precisionFlag;
}

void VisualStyle::setPrecisionFlag(bool value)
{
    _precisionFlag = value;
}

bool VisualStyle::internalFlag() const
{
    return _internalFlag;
}

void VisualStyle::setInternalFlag(bool value)
{
    _internalFlag = value;
}

}// namespace dwg
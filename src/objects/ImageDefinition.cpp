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

#include <dwg/objects/ImageDefinition.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>

namespace dwg {
    
ImageDefinition::ImageDefinition() {}

ImageDefinition::~ImageDefinition() {}

ObjectType ImageDefinition::objectType() const { return ObjecType::UNLISTED; }

std::string ImageDefinition::objectName() const { return DxfFileToken::ObjectImageDefinition; }

std::string ImageDefinition::subclassMarker() const { return DxfSubclassMarker::RasterImageDef; }

int ImageDefinition::classVersion() const { return _classVersion; }

void ImageDefinition::setClassVersion(int value) { _classVersion = value; }

std::string ImageDefinition::fileName() const { return _fileName; }

void ImageDefinition::setFileName(const std::string &value) { _fileName = value; }

XY ImageDefinition::size() const { return _size; }

void ImageDefinition::setSize(const XY &value) { _size =value; }

XY ImageDefinition::defaultSize() const { return _defaultSize; }

void ImageDefinition::setDefaultSize(const XY &value) { _defaultSize = value; }

bool ImageDefinition::isLoaded() const { return _isLoaded; }

void ImageDefinition::setIsLoaded(bool value) { _isLoaded = value; }

ResolutionUnit ImageDefinition::units() const { return _units; }

void ImageDefinition::setUnits(ResolutionUnit value) { _units = value; }

}// namespace dwg
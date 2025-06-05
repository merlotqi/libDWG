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
#include <dwg/entities/Hatch.h>

namespace dwg {

    Hatch::Hatch() {}
    Hatch::~Hatch() {}

    ObjectType Hatch::objectType() const { return ObjectType::HATCH; }

    std::string Hatch::objectName() const { return DxfFileToken::EntityHatch; }

    std::string Hatch::subclassMarker() const { return DxfSubclassMarker::Hatch; }

    double Hatch::elevation() const { return _elevation; }

    void Hatch::setElevation(double value) {_elevation = value; }

    XYZ Hatch::normal() const { return _normal; }

    void Hatch::setNormal(const XYZ &value) { _normal = value; }

    HatchPattern *Hatch::pattern() const { return _pattern; }

    void Hatch::setPattern(HatchPattern *value) { _pattern = value; }

    bool Hatch::isSolid() const { return _isSolid; }

    void Hatch::setIsSolid(bool value) { _isSolid = value; }

    bool Hatch::isAssociative() const { return _isAssociative; }

    void Hatch::setIsAssociative(bool value) { _isAssociative = value; }

    HatchStyleType Hatch::style() const { return _style; }

    void Hatch::setStyle(HatchStyleType value) { _style = value; }

    HatchPatternType Hatch::patternType() const { return _patternType; }

    void Hatch::setPatternType(HatchPatternType value) { _patternType = value; }

    double Hatch::patternAngle() const { return _patternAngle; }

    void Hatch::setPatternAngle(double value) { _patternAngle = value; }

    double Hatch::patternScale() const { return _patternScale; }

    void Hatch::setPatternScale(double value) { _patternScale = value; }

    bool Hatch::isDouble() const { return _isDouble; }

    void Hatch::setIsDouble(bool value) { _isDouble = value; }

    double Hatch::pixelSize() const { return _pixelSize; }

    void Hatch::setPixelSize(double value) { _pixelSize = value; }

    std::vector<XY> Hatch::seedPoints() const { return _seedPoints; }

    void Hatch::setSeedPoints(const std::vector<XY> &value) { _seedPoints = value; }

    HatchGradientPattern *Hatch::gradientColor() const { return _gradientColor; }

    void Hatch::setGradientColor(HatchGradientPattern *value) { _gradientColor = value; }

    std::vector<HatchBoundaryPath *> Hatch::paths() const { return _paths; }

    void Hatch::setPaths(const std::vector<HatchBoundaryPath *> &value) { _paths = value; }

}// namespace dwg
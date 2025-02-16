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

#include <dwg/entities/HatchGradientPattern.h>

namespace dwg {

HatchGradientPattern::HatchGradientPattern() : HatchGradientPattern("") {}

HatchGradientPattern::HatchGradientPattern(const std::string &name)
    : _enabled(false), _reserved(0), _angle(0), _shift(0), _singleColorGradient(false), _colorTint(0), _colors(),
      _name(name)
{
}

HatchGradientPattern::~HatchGradientPattern() {}

bool HatchGradientPattern::enabled() const { return _enabled; }

void HatchGradientPattern::setEnabled(bool enabled) { _enabled = enabled; }

int HatchGradientPattern::reserved() const { return _reserved; }

void HatchGradientPattern::setReserved(int reserved) { _reserved = reserved; }

double HatchGradientPattern::angle() const { return _angle; }

void HatchGradientPattern::setAngle(double angle) { _angle = angle; }

double HatchGradientPattern::shift() const { return _shift; }

void HatchGradientPattern::setShift(double shift) { _shift = shift; }

bool HatchGradientPattern::isSingleColorGradient() const { return _singleColorGradient; }

void HatchGradientPattern::setIsSingleColorGradient(bool singleColor) { _singleColorGradient = singleColor; }

double HatchGradientPattern::colorTint() const { return _colorTint; }

void HatchGradientPattern::setColorTint(double tint) { _colorTint = tint; }

const std::vector<GradientColor> &HatchGradientPattern::colors() const { return _colors; }

void HatchGradientPattern::setColors(const std::vector<GradientColor> &colors) { _colors = colors; }

std::string HatchGradientPattern::name() const { return _name; }

void HatchGradientPattern::setName(const std::string &name) { _name = name; }

}// namespace dwg
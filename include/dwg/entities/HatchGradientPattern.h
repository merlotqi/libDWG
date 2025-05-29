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

#pragma once

#include <dwg/entities/GradientColor.h>
#include <dwg/exports.h>
#include <string>
#include <vector>

namespace dwg {

class LIBDWG_API HatchGradientPattern
{
public:
    HatchGradientPattern();
    HatchGradientPattern(const std::string &name);
    ~HatchGradientPattern();

    bool enabled() const;
    void setEnabled(bool enabled);

    int reserved() const;
    void setReserved(int reserved);

    double angle() const;
    void setAngle(double angle);

    double shift() const;
    void setShift(double shift);

    bool isSingleColorGradient() const;
    void setIsSingleColorGradient(bool singleColor);

    double colorTint() const;
    void setColorTint(double tint);

    const std::vector<GradientColor> &colors() const;
    void setColors(const std::vector<GradientColor> &colors);

    std::string name() const;
    void setName(const std::string &name);

private:
    bool _enabled;
    int _reserved;
    double _angle;
    double _shift;
    bool _singleColorGradient;
    double _colorTint;
    std::vector<GradientColor> _colors;
    std::string _name;
};

}// namespace dwg
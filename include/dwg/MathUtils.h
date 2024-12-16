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

#include <math.h>
#include <dwg/Coordinate.h>

namespace dwg {

class MathUtils {
public:
    static constexpr double RadToDegFactor = (180.0 / M_PI);
    static constexpr double DegToRadFactor = (M_PI / 180.0);

    static constexpr double Epsilon = 1e-12;
    static constexpr double TwoPI = M_PI * 2;

    static bool IsZero(double number);
    static bool IsZero(double number, double threshold);
    static double FixZero(double number);
    static double FixZero(double number, double threshold);
    static double RadToDeg(double value);
    static double DegToRad(double value);

    static Util::XY GetCenter(Util::XY start, Util::XY end, double bulge);
    static Util::XY GetCenter(Util::XY start, Util::XY end, double bulge,
                              double &radius);
};

} // namespace dwg

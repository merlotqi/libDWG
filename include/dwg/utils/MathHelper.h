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

#include <dwg/exports.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

namespace dwg {

class LIBDWG_API MathHelper
{
public:
    /// Factor for converting an angle between degrees and gradians.
    static constexpr auto DegToGradFactor = 10.0 / 9.0;
    /// Factor for converting degrees to radians.
    static constexpr auto DegToRadFactor = (M_PI / 180);
    /// Default tolerance
    static constexpr auto Epsilon = 1e-12;
    /// Factor for converting an angle between gradians and degrees.
    static constexpr auto GradToDegFactor = 9.0 / 10.0;
    /// Factor for converting an angle between gradians and radians.
    static constexpr auto GradToRadFactor = M_PI / 200;
    /// Equivalent to 90 degrees.
    static constexpr auto HalfPI = M_PI / 2;
    /// Factor for converting radians to degrees.
    static constexpr auto RadToDegFactor = (180 / M_PI);
    /// Factor for converting radians to gradians.
    static constexpr auto RadToGradFactor = 200 / M_PI;
    /// Equivalent to 270 degrees.
    static constexpr auto ThreeHalfPI = 3 * M_PI * 0.5;

public:
    static double RadToDeg(double value, bool absolute = true);
    static double RadToGrad(double value);
    static double NormalizeAngle(double angle);
    static bool IsEqual(double a, double b);
    static bool IsEqual(double a, double b, double threshold);
    static bool IsZero(double number);
    static bool IsZero(double number, double threshold);
};

}// namespace dwg
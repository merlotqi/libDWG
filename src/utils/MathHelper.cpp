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

#include <dwg/utils/MathHelper.h>

namespace dwg {

double MathHelper::RadToDeg(double value, bool absolute)
{
    auto result = value * RadToDegFactor;
    return NormalizeAngle(result);
}

double MathHelper::RadToGrad(double value)
{
    return value * RadToGradFactor;
}

double MathHelper::NormalizeAngle(double angle)
{
    double normalized = fmod(angle, 360.0);
    if (IsZero(normalized) || IsEqual(fabs(normalized), 360.0))
    {
        return 0.0;
    }

    if (normalized < 0)
    {
        return 360.0 + normalized;
    }

    return normalized;
}

bool MathHelper::IsEqual(double a, double b)
{
    return IsEqual(a, b, Epsilon);
}

bool MathHelper::IsEqual(double a, double b, double threshold)
{
    return IsZero(a - b, threshold);
}

bool MathHelper::IsZero(double number)
{
    return IsZero(number, Epsilon);
}

bool MathHelper::IsZero(double number, double threshold)
{
    return number >= -threshold && number <= threshold;
}


}// namespace dwg

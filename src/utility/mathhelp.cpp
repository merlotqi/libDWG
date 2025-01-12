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

#include <dwg/Coordinate.h>
#include <stdexcept>

XYZ XYZ::Zero = XYZ(0, 0, 0);

XYZ XYZ::AxisX = XYZ(1, 0, 0);

XYZ XYZ::AxisY = XYZ(0, 1, 0);

XYZ XYZ::AxisZ = XYZ(0, 0, 1);

double XYZ::operator[](int index) const
{
    if (index > 2) throw std::out_of_range("Index out of range");
    return u[index];
}

double &XYZ::operator[](int index)
{
    if (index > 2) throw std::out_of_range("Index out of range");
    return u[index];
}

XY XY::Zero = XY(0, 0);

double XY::operator[](int index) const
{
    if (index > 1) throw std::out_of_range("Index out of range");
    return u[index];
}

double &XY::operator[](int index)
{
    if (index > 1) throw std::out_of_range("Index out of range");
    return u[index];
}

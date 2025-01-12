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

#include <array>
#include <stddef.h>

struct IVector
{
    size_t Dimension;
};


struct XYZ
{
    union
    {
        struct
        {
            double X;
            double Y;
            double Z;
        };
        double u[3];
    };

    static XYZ Zero;
    static XYZ AxisX;
    static XYZ AxisY;
    static XYZ AxisZ;

    XYZ() : X(0), Y(0), Z(0) {}
    XYZ(double x, double y, double z) : X(x), Y(y), Z(z) {}
    double operator[](int index) const;
    double &operator[](int index);
};

struct XY
{
    union
    {
        struct
        {
            double X;
            double Y;
        };
        double u[2];
    };

    static XY Zero;

    XY() : X(0), Y(0) {}
    XY(double x, double y) : X(x), Y(y) {}
    double operator[](int index) const;
    double &operator[](int index);
};


struct Matrix4
{
    double m00, m01, m02, m03;
    double m10, m11, m12, m13;
    double m20, m21, m22, m23;
    double m30, m31, m32, m33;
};

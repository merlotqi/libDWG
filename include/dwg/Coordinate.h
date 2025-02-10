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

namespace dwg {

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
    static XY AxisX;
    static XY AxisY;

    constexpr XY();
    constexpr XY(double x, double y);
    constexpr inline double operator[](int index) const;
    constexpr inline double &operator[](int index);

    constexpr inline XY &operator+=(const XY &p);
    constexpr inline XY &operator-=(const XY &p);

    constexpr inline XY &operator*=(float factor);
    constexpr inline XY &operator*=(double factor);
    constexpr inline XY &operator*=(int factor);

    constexpr inline XY &operator/=(double divisor);

    constexpr inline double distanceTo(const XY &rhs) const;
    constexpr inline double angleTo(const XY &rhs) const;
    constexpr inline bool fuzzyEqual(const XY &rhs) const;
    constexpr inline bool isParallel(const XY &rhs) const;

    friend constexpr inline bool operator==(const XY &, const XY &);
    friend constexpr inline bool operator!=(const XY &, const XY &);
    friend constexpr inline const XY operator+(const XY &, const XY &);
    friend constexpr inline const XY operator-(const XY &, const XY &);
    friend constexpr inline const XY operator*(double, const XY &);
    friend constexpr inline const XY operator*(const XY &, double);
    friend constexpr inline const XY operator/(const XY &, double);    
    friend constexpr inline const XY operator+(const XY &);
    friend constexpr inline const XY operator-(const XY &);
};

constexpr inline XY::XY() : X(0.0), Y(0.0) {}

constexpr inline XY::XY(double x, double y) : X(x), Y(y) {}

constexpr inline double XY::operator[](int index) const
{ return u[index]; }

constexpr inline double& XY::operator[](int index)
{ return u[index]; }

constexpr inline XY& XY::operator+=(const XY& p)
{ X += p.X; Y += p.Y; return *this; }

constexpr inline XY& XY::operator-=(const XY &p)
{ X -= p.X; Y -= p.Y; return *this; }

constexpr inline XY& XY::operator*=(float factor)
{ X = std::round(X * factor); Y = std::round(Y * factor); return *this; }

constexpr inline XY& XY::operator*=(double factor)
{ X = std::round(X * factor); Y = std::round(Y * factor); return *this; }

constexpr inline XY& XY::operator*=(int factor)
{ X = std::round(X * factor); Y = std::round(Y * factor); return *this; }

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

    constexpr XYZ();
    constexpr XYZ(double x, double y, double z);
    constexpr inline double operator[](int index) const;
    constexpr inline double &operator[](int index);

    constexpr inline double distanceTo(const XYZ &rhs) const;
    constexpr inline double angleTo(const XYZ &rhs) const;
    constexpr inline XY to2D() const;

    friend constexpr inline bool operator==(const XYZ &, const XYZ &);
    friend constexpr inline bool operator!=(const XYZ &, const XYZ &);
    friend constexpr inline const XYZ operator+(const XYZ &, const XYZ &);
    friend constexpr inline const XYZ operator-(const XYZ &, const XYZ &);
    friend constexpr inline const XYZ operator*(double, const XYZ &);
    friend constexpr inline const XYZ operator*(const XYZ &, double);
    friend constexpr inline const XYZ operator/(const XYZ &, double);    
    friend constexpr inline const XYZ operator+(const XYZ &);
    friend constexpr inline const XYZ operator-(const XYZ &);
};

struct Matrix4
{
    double m00, m01, m02, m03;
    double m10, m11, m12, m13;
    double m20, m21, m22, m23;
    double m30, m31, m32, m33;
};

}// namespace dwg

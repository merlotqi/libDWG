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

#include <assert.h>
#include <cmath>
#include <dwg/exports.h>

namespace dwg {

inline bool fuzzyIsNull(double d) noexcept
{
    return std::fabs(d) <= 0.000000000001;
}

struct LIBDWG_API XY
{
    union
    {
        double v[2];
        struct
        {
            double X;
            double Y;
        };
    };

    static XY Zero;
    static XY AxisX;
    static XY AxisY;

    constexpr XY() noexcept;
    constexpr XY(double xpos, double ypos) noexcept;

    constexpr double &operator[](int i);
    constexpr double operator[](int i) const;

    double length() const noexcept;
    constexpr double lengthSquared() const noexcept;

    XY normalized() const noexcept;
    void normalize() noexcept;

    double distanceToPoint(XY point) const noexcept;

    constexpr XY &operator+=(XY vector) noexcept;
    constexpr XY &operator-=(XY vector) noexcept;
    constexpr XY &operator*=(double factor) noexcept;
    constexpr XY &operator*=(XY vector) noexcept;
    constexpr XY &operator/=(double divisor);
    constexpr XY &operator/=(XY vector);

    static constexpr double dotProduct(XY v1, XY v2) noexcept;

    constexpr friend inline bool operator==(XY v1, XY v2) noexcept
    {
        return v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1];
    }

    constexpr friend inline bool operator!=(XY v1, XY v2) noexcept
    {
        return v1.v[0] != v2.v[0] || v1.v[1] != v2.v[1];
    }

    constexpr friend inline XY operator+(XY v1, XY v2) noexcept
    {
        return XY(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1]);
    }

    constexpr friend inline XY operator-(XY v1, XY v2) noexcept
    {
        return XY(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1]);
    }

    constexpr friend inline XY operator*(double factor, XY vector) noexcept
    {
        return XY(vector.v[0] * factor, vector.v[1] * factor);
    }

    constexpr friend inline XY operator*(XY vector, double factor) noexcept
    {
        return XY(vector.v[0] * factor, vector.v[1] * factor);
    }

    constexpr friend inline XY operator*(XY v1, XY v2) noexcept
    {
        return XY(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1]);
    }

    constexpr friend inline XY operator-(XY vector) noexcept
    {
        return XY(-vector.v[0], -vector.v[1]);
    }

    constexpr friend inline XY operator/(XY vector, double divisor)
    {
        assert(divisor < 0 || divisor > 0);
        return XY(vector.v[0] / divisor, vector.v[1] / divisor);
    }

    constexpr friend inline XY operator/(XY vector, XY divisor)
    {
        assert(divisor.v[0] < 0 || divisor.v[0] > 0);
        assert(divisor.v[1] < 0 || divisor.v[1] > 0);
        return XY(vector.v[0] / divisor.v[0], vector.v[1] / divisor.v[1]);
    }
};


struct LIBDWG_API XYZ
{
    union
    {
        double v[3];
        struct
        {
            double X;
            double Y;
            double Z;
        };
    };

    static XYZ Zero;
    static XYZ AxisX;
    static XYZ AxisY;
    static XYZ AxisZ;

    constexpr XYZ() noexcept;
    constexpr XYZ(const XY &v) noexcept;
    constexpr XYZ(double xpos, double ypos, double zpos) noexcept : v{xpos, ypos, zpos} {}

    constexpr double &operator[](int i);
    constexpr double operator[](int i) const;

    double length() const noexcept;
    constexpr double lengthSquared() const noexcept;

    XYZ normalized() const noexcept;
    void normalize() noexcept;

    constexpr XYZ &operator+=(XYZ vector) noexcept;
    constexpr XYZ &operator-=(XYZ vector) noexcept;
    constexpr XYZ &operator*=(double factor) noexcept;
    constexpr XYZ &operator*=(XYZ vector) noexcept;
    constexpr XYZ &operator/=(double divisor);
    constexpr XYZ &operator/=(XYZ vector);

    static constexpr double dotProduct(XYZ v1, XYZ v2) noexcept;
    static constexpr XYZ crossProduct(XYZ v1, XYZ v2) noexcept;

    static XYZ normal(XYZ v1, XYZ v2) noexcept;
    static XYZ normal(XYZ v1, XYZ v2, XYZ v3) noexcept;


    constexpr friend inline bool operator==(XYZ v1, XYZ v2) noexcept
    {
        return v1.v[0] == v2.v[0] && v1.v[1] == v2.v[1] && v1.v[2] == v2.v[2];
    }

    constexpr friend inline bool operator!=(XYZ v1, XYZ v2) noexcept
    {
        return v1.v[0] != v2.v[0] || v1.v[1] != v2.v[1] || v1.v[2] != v2.v[2];
    }

    double distanceToPoint(XYZ point) const noexcept;


    constexpr friend inline XYZ operator+(XYZ v1, XYZ v2) noexcept
    {
        return XYZ(v1.v[0] + v2.v[0], v1.v[1] + v2.v[1], v1.v[2] + v2.v[2]);
    }

    constexpr friend inline XYZ operator-(XYZ v1, XYZ v2) noexcept
    {
        return XYZ(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
    }

    constexpr friend inline XYZ operator*(double factor, XYZ vector) noexcept
    {
        return XYZ(vector.v[0] * factor, vector.v[1] * factor, vector.v[2] * factor);
    }

    constexpr friend inline XYZ operator*(XYZ vector, double factor) noexcept
    {
        return XYZ(vector.v[0] * factor, vector.v[1] * factor, vector.v[2] * factor);
    }

    constexpr friend inline XYZ operator*(XYZ v1, XYZ v2) noexcept
    {
        return XYZ(v1.v[0] * v2.v[0], v1.v[1] * v2.v[1], v1.v[2] * v2.v[2]);
    }

    constexpr friend inline XYZ operator-(XYZ vector) noexcept
    {
        return XYZ(-vector.v[0], -vector.v[1], -vector.v[2]);
    }

    constexpr friend inline XYZ operator/(XYZ vector, double divisor)
    {
        assert(divisor < 0 || divisor > 0);
        return XYZ(vector.v[0] / divisor, vector.v[1] / divisor, vector.v[2] / divisor);
    }

    constexpr friend inline XYZ operator/(XYZ vector, XYZ divisor)
    {
        assert(divisor.v[0] > 0 || divisor.v[0] < 0);
        assert(divisor.v[1] > 0 || divisor.v[1] < 0);
        assert(divisor.v[2] > 0 || divisor.v[2] < 0);
        return XYZ(vector.v[0] / divisor.v[0], vector.v[1] / divisor.v[1], vector.v[2] / divisor.v[2]);
    }
    constexpr XY to2D() const noexcept;
};


/***************************** XY *****************************/


constexpr inline XY::XY() noexcept : v{0.0, 0.0} {}

constexpr inline XY::XY(double xpos, double ypos) noexcept : v{xpos, ypos} {}

constexpr inline double &XY::operator[](int i)
{
    assert((unsigned int) (i) < 2u);
    return v[i];
}

constexpr inline double XY::operator[](int i) const
{
    assert((unsigned int) (i) < 2u);
    return v[i];
}

inline double XY::length() const noexcept
{
    return std::hypot(v[0], v[1]);
}

constexpr inline double XY::lengthSquared() const noexcept
{
    return v[0] * v[0] + v[1] * v[1];
}

inline XY XY::normalized() const noexcept
{
    const double len = length();
    return fuzzyIsNull(len - 1.0f) ? *this : fuzzyIsNull(len) ? XY() : XY(v[0] / len, v[1] / len);
}

inline void XY::normalize() noexcept
{
    const double len = length();
    if (fuzzyIsNull(len - 1.0f) || fuzzyIsNull(len))
        return;

    v[0] /= len;
    v[1] /= len;
}

inline double XY::distanceToPoint(XY point) const noexcept
{
    return (*this - point).length();
}

constexpr inline XY &XY::operator+=(XY vector) noexcept
{
    v[0] += vector.v[0];
    v[1] += vector.v[1];
    return *this;
}

constexpr inline XY &XY::operator-=(XY vector) noexcept
{
    v[0] -= vector.v[0];
    v[1] -= vector.v[1];
    return *this;
}

constexpr inline XY &XY::operator*=(double factor) noexcept
{
    v[0] *= factor;
    v[1] *= factor;
    return *this;
}

constexpr inline XY &XY::operator*=(XY vector) noexcept
{
    v[0] *= vector.v[0];
    v[1] *= vector.v[1];
    return *this;
}

constexpr inline XY &XY::operator/=(double divisor)
{
    assert(divisor < 0 || divisor > 0);
    v[0] /= divisor;
    v[1] /= divisor;
    return *this;
}

constexpr inline XY &XY::operator/=(XY vector)
{
    assert(vector.v[0] > 0 || vector.v[0] < 0);
    assert(vector.v[1] > 0 || vector.v[1] < 0);
    v[0] /= vector.v[0];
    v[1] /= vector.v[1];
    return *this;
}

constexpr inline double XY::dotProduct(XY v1, XY v2) noexcept
{
    return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1];
}

/***************************** XYZ *****************************/

constexpr inline XYZ::XYZ() noexcept : v{0.0, 0.0, 0.0} {}

inline constexpr XYZ::XYZ(const XY &pv) noexcept : v{pv.X, pv.Y, 0.0} {}

constexpr inline double &XYZ::operator[](int i)
{
    assert((unsigned int) (i) < 3u);
    return v[i];
}

constexpr inline double XYZ::operator[](int i) const
{
    assert((unsigned int) (i) < 3u);
    return v[i];
}

inline double XYZ::length() const noexcept
{
    return std::hypot(v[0], v[1], v[2]);
}

inline XYZ XYZ::normalized() const noexcept
{
    const double len = length();
    return fuzzyIsNull(len - 1.0f) ? *this : fuzzyIsNull(len) ? XYZ() : XYZ(v[0] / len, v[1] / len, v[2] / len);
}

inline void XYZ::normalize() noexcept
{
    const double len = length();
    if (fuzzyIsNull(len - 1.0f) || fuzzyIsNull(len))
        return;

    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

constexpr inline double XYZ::lengthSquared() const noexcept
{
    return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
}

constexpr inline XYZ &XYZ::operator+=(XYZ vector) noexcept
{
    v[0] += vector.v[0];
    v[1] += vector.v[1];
    v[2] += vector.v[2];
    return *this;
}

constexpr inline XYZ &XYZ::operator-=(XYZ vector) noexcept
{
    v[0] -= vector.v[0];
    v[1] -= vector.v[1];
    v[2] -= vector.v[2];
    return *this;
}

constexpr inline XYZ &XYZ::operator*=(double factor) noexcept
{
    v[0] *= factor;
    v[1] *= factor;
    v[2] *= factor;
    return *this;
}

constexpr inline XYZ &XYZ::operator*=(XYZ vector) noexcept
{
    v[0] *= vector.v[0];
    v[1] *= vector.v[1];
    v[2] *= vector.v[2];
    return *this;
}

constexpr inline XYZ &XYZ::operator/=(double divisor)
{
    assert(divisor < 0 || divisor > 0);
    v[0] /= divisor;
    v[1] /= divisor;
    v[2] /= divisor;
    return *this;
}

constexpr inline XYZ &XYZ::operator/=(XYZ vector)
{
    assert(vector.v[0] > 0 || vector.v[0] < 0);
    assert(vector.v[1] > 0 || vector.v[1] < 0);
    assert(vector.v[2] > 0 || vector.v[2] < 0);
    v[0] /= vector.v[0];
    v[1] /= vector.v[1];
    v[2] /= vector.v[2];
    return *this;
}

constexpr inline double XYZ::dotProduct(XYZ v1, XYZ v2) noexcept
{
    return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
}

constexpr inline XYZ XYZ::crossProduct(XYZ v1, XYZ v2) noexcept
{
    return XYZ(v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1], v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2],
               v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0]);
}

inline XYZ XYZ::normal(XYZ v1, XYZ v2) noexcept
{
    return crossProduct(v1, v2).normalized();
}

inline XYZ XYZ::normal(XYZ v1, XYZ v2, XYZ v3) noexcept
{
    return crossProduct((v2 - v1), (v3 - v1)).normalized();
}

inline double XYZ::distanceToPoint(XYZ point) const noexcept
{
    return (*this - point).length();
}

constexpr inline XY XYZ::to2D() const noexcept
{
    return XY(v[0], v[1]);
}


struct Matrix4
{
    double m00, m01, m02, m03;
    double m10, m11, m12, m13;
    double m20, m21, m22, m23;
    double m30, m31, m32, m33;
};

}// namespace dwg

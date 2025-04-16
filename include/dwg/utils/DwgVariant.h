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

#include <dwg/Coordinate.h>
#include <dwg/exports.h>
#include <string>
#include <variant>
#include <vector>

namespace dwg {

class LIBDWG_API DwgVariant
{
public:
    enum VarType
    {
        None,
        I8,
        U8,
        I16,
        U16,
        I32,
        U32,
        I64,
        U64,
        F32,
        F64,
        STRING,
        COORD2D,
        COORD3D,
        BLOB,
    };

    DwgVariant();

    VarType Type;

    union
    {
        char i8;
        unsigned char u8;
        short i16;
        unsigned short u16;
        int i32;
        unsigned int u32;
        long long i64;
        unsigned long long u64;
        float f32;
        double f64;
        std::string str;
        XY xy;
        XYZ xyz;
        std::vector<unsigned char> blob;
    };

    virtual ~DwgVariant();
    DwgVariant(char v);
    DwgVariant(unsigned char v);
    DwgVariant(short v);
    DwgVariant(unsigned short v);
    DwgVariant(int v);
    DwgVariant(unsigned int v);
    DwgVariant(long long v);
    DwgVariant(unsigned long long v);
    DwgVariant(float v);
    DwgVariant(double v);
    DwgVariant(bool v);
    DwgVariant(const char *v);
    DwgVariant(const std::string &str);
    DwgVariant(const XY &v);
    DwgVariant(const XYZ &v);
    DwgVariant(const std::vector<unsigned char> &blob);

    DwgVariant(const DwgVariant &rhs);
    DwgVariant(DwgVariant &&rhs) noexcept;
    DwgVariant(VarType type);


    DwgVariant &operator=(const DwgVariant &rhs);
    DwgVariant &operator=(char v);
    DwgVariant &operator=(unsigned char v);
    DwgVariant &operator=(short v);
    DwgVariant &operator=(unsigned short v);
    DwgVariant &operator=(int v);
    DwgVariant &operator=(unsigned int v);
    DwgVariant &operator=(long long v);
    DwgVariant &operator=(unsigned long long v);
    DwgVariant &operator=(float v);
    DwgVariant &operator=(double v);
    DwgVariant &operator=(bool v);
    DwgVariant &operator=(const std::string &str);
    DwgVariant &operator=(const XY &v);
    DwgVariant &operator=(const XYZ &v);
    DwgVariant &operator=(const std::vector<unsigned char> &blob);
    DwgVariant &operator=(std::vector<unsigned char> &&blob) noexcept;

    DwgVariant &operator=(DwgVariant &&v) noexcept;

    bool operator==(const DwgVariant &o) const;
    bool operator!=(const DwgVariant &o) const;

    void clear();

    char asChar() const;
    unsigned char asUChar() const;
    short asShort() const;
    unsigned short asUShort() const;
    int asInt() const;
    unsigned int asUInt() const;
    long long asLongLong() const;
    unsigned long long asULongLong() const;
    float asFloat() const;
    double asDouble() const;
    bool asBool() const;
    std::string asString() const;
    int asBlob(unsigned char *bBlob) const;
    XY asCoord2D() const;
    XYZ asCoord3D() const;
    const std::vector<unsigned char> &asBlob() const;

    operator char() const;
    operator unsigned char() const;
    operator short() const;
    operator unsigned short() const;
    operator int() const;
    operator unsigned int() const;
    operator long long() const;
    operator unsigned long long() const;
    operator bool() const;
    operator float() const;
    operator double() const;
    operator const std::string &() const;
    operator const XY &() const;
    operator const XYZ &() const;
    operator const std::vector<unsigned char> &() const;

    void swap(DwgVariant &rhs);

    static const DwgVariant &Empty();
};


}// namespace dwg
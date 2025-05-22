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

#include <dwg/utils/DwgVariant.h>

namespace dwg {

DwgVariant::DwgVariant() {}

DwgVariant::~DwgVariant() {}

DwgVariant::DwgVariant(char v)
{
    Type = VarType::I8;
    i8 = v;
}

DwgVariant::DwgVariant(unsigned char v)
{
    Type = VarType::U8;
    u8 = v;
}

DwgVariant::DwgVariant(short v)
{
    Type = VarType::I16;
    i16 = v;
}

DwgVariant::DwgVariant(unsigned short v)
{
    Type = VarType::U16;
    u16 = v;
}

DwgVariant::DwgVariant(int v)
{
    Type = VarType::I32;
    i32 = v;
}

DwgVariant::DwgVariant(unsigned int v)
{
    Type = VarType::U32;
    u32 = v;
}

DwgVariant::DwgVariant(long long v)
{
    Type = VarType::I64;
    i64 = v;
}

DwgVariant::DwgVariant(unsigned long long v)
{
    Type = VarType::U64;
    u64 = v;
}

DwgVariant::DwgVariant(float v)
{
    Type = VarType::F32;
    f32 = v;
}

DwgVariant::DwgVariant(double v)
{
    Type = VarType::F64;
    f64 = v;
}

DwgVariant::DwgVariant(bool v)
{
    Type = VarType::I32;
    i32 = v;
}

DwgVariant::DwgVariant(const char *v)
{
    Type = VarType::STRING;
    str = v;
}

DwgVariant::DwgVariant(const std::string &str)
{
    Type = VarType::STRING;
    this->str = str;
}

DwgVariant::DwgVariant(const XY &v)
{
    Type = VarType::COORD2D;
    xy = v;
}

DwgVariant::DwgVariant(const XYZ &v)
{
    Type = VarType::COORD3D;
    xyz = v;
}

DwgVariant::DwgVariant(const std::vector<unsigned char> &v)
{
    Type = VarType::BLOB;
    blob = v;
}

DwgVariant::DwgVariant(const DateTime &v)
{
    Type = VarType::DATETIME;
    time = v;
}

DwgVariant::DwgVariant(const Color &v)
{
    Type = VarType::COLOR;
    rgb = v;
}

DwgVariant::DwgVariant(const DwgVariant &rhs)
{
    Type = rhs.Type;
    *this = rhs;
}

DwgVariant::DwgVariant(DwgVariant &&rhs) noexcept
{
    Type = rhs.Type;
    *this = std::move(rhs);
}

DwgVariant::DwgVariant(VarType type)
{
    Type = type;
}

DwgVariant &DwgVariant::operator=(const DwgVariant &rhs)
{
    Type = rhs.Type;
    *this = rhs;
    return *this;
}

DwgVariant &DwgVariant::operator=(char v)
{
    Type = VarType::I8;
    i8 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(unsigned char v)
{
    Type = VarType::U8;
    u8 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(short v)
{
    Type = VarType::I16;
    i16 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(unsigned short v)
{
    Type = VarType::U16;
    u16 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(int v)
{
    Type = VarType::I32;
    i32 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(unsigned int v)
{
    Type = VarType::U32;
    u32 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(long long v)
{
    Type = VarType::I64;
    i64 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(unsigned long long v)
{
    Type = VarType::U64;
    u64 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(float v)
{
    Type = VarType::F32;
    f32 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(double v)
{
    Type = VarType::F64;
    f64 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(bool v)
{
    Type = VarType::I32;
    i32 = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(const std::string &v)
{
    Type = VarType::STRING;
    str = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(const XY &v)
{
    Type = VarType::COORD2D;
    xy = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(const XYZ &v)
{
    Type = VarType::COORD3D;
    xyz = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(const DateTime &v)
{
    Type = VarType::DATETIME;
    time = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(const Color &v)
{
    Type = VarType::COLOR;
    rgb = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(const std::vector<unsigned char> &v)
{
    Type = VarType::BLOB;
    blob = v;
    return *this;
}

DwgVariant &DwgVariant::operator=(std::vector<unsigned char> &&v) noexcept
{
    Type = VarType::BLOB;
    blob = std::move(v);
    return *this;
}


DwgVariant &DwgVariant::operator=(DwgVariant &&v) noexcept
{
    return *this;
}

bool DwgVariant::operator==(const DwgVariant &o) const
{
    return false;
}

bool DwgVariant::operator!=(const DwgVariant &o) const
{
    return false;
}

void DwgVariant::clear() {}

char DwgVariant::asChar() const
{
    assert(Type == VarType::I8);
    return i8;
}

unsigned char DwgVariant::asUChar() const
{
    assert(Type == VarType::U8);
    return u8;
}

short DwgVariant::asShort() const
{
    assert(Type == VarType::I16);
    return i16;
}

unsigned short DwgVariant::asUShort() const
{
    assert(Type == VarType::U16);
    return u16;
}

int DwgVariant::asInt() const
{
    assert(Type == VarType::I32);
    return i32;
}

unsigned int DwgVariant::asUInt() const
{
    assert(Type == VarType::U32);
    return u32;
}

long long DwgVariant::asLongLong() const
{
    assert(Type == VarType::I64);
    return i64;
}

unsigned long long DwgVariant::asULongLong() const
{
    assert(Type == VarType::U64);
    return u64;
}

float DwgVariant::asFloat() const
{
    assert(Type == VarType::F32);
    return f32;
}

double DwgVariant::asDouble() const
{
    assert(Type == VarType::F64);
    return f64;
}

bool DwgVariant::asBool() const
{
    assert(Type == VarType::I32);
    return i32;
}

std::string DwgVariant::asString() const
{
    assert(Type == VarType::STRING);
    return str;
}

int DwgVariant::asBlob(unsigned char *bBlob) const
{
    return 0;
}

XY DwgVariant::asCoord2D() const
{
    assert(Type == VarType::COORD2D);
    return xy;
}

XYZ DwgVariant::asCoord3D() const
{
    assert(Type == VarType::COORD3D);
    return xyz;
}

const std::vector<unsigned char> &DwgVariant::asBlob() const
{
    assert(Type == VarType::BLOB);
    return blob;
}

DateTime DwgVariant::asDateTime() const
{
    assert(Type == VarType::DATETIME);
    return time;
}

Color DwgVariant::asColor() const
{
    assert(Type == VarType::COLOR);
    return rgb;
}

DwgVariant::operator char() const
{
    assert(Type == VarType::I8);
    return i8;
}

DwgVariant::operator unsigned char() const
{
    assert(Type == VarType::U8);
    return u8;
}

DwgVariant::operator short() const
{
    assert(Type == VarType::I16);
    return i16;
}

DwgVariant::operator unsigned short() const
{
    assert(Type == VarType::U16);
    return u16;
}

DwgVariant::operator int() const
{
    assert(Type == VarType::I32);
    return i32;
}

DwgVariant::operator unsigned int() const
{
    assert(Type == VarType::U32);
    return u32;
}

DwgVariant::operator long long() const
{
    assert(Type == VarType::I64);
    return i64;
}

DwgVariant::operator unsigned long long() const
{
    assert(Type == VarType::U64);
    return u64;
}

DwgVariant::operator bool() const
{
    assert(Type == VarType::I32);
    return i32;
}

DwgVariant::operator float() const
{
    assert(Type == VarType::F32);
    return f32;
}

DwgVariant::operator double() const
{
    assert(Type == VarType::F64);
    return f64;
}

DwgVariant::operator const std::string &() const
{
    assert(Type == VarType::STRING);
    return str;
}

DwgVariant::operator const XY &() const
{
    assert(Type == VarType::COORD2D);
    return xy;
}

DwgVariant::operator const XYZ &() const
{
    assert(Type == VarType::COORD3D);
    return xyz;
}

DwgVariant::operator const DateTime &() const
{
    assert(Type == VarType::DATETIME);
    return time;
}

DwgVariant::operator const Color &() const
{
    assert(Type == VarType::COLOR);
    return rgb;
}

void DwgVariant::swap(DwgVariant &rhs) {}

const DwgVariant &DwgVariant::Empty()
{
    static DwgVariant empty(VarType::None);
    return empty;
}

}// namespace dwg
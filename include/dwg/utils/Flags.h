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

#include <type_traits>

namespace dwg {

class Flag
{
    int i;

public:
    constexpr inline Flag(int value) noexcept : i(value) {}
    constexpr inline operator int() const noexcept { return i; }

    constexpr inline Flag(unsigned int value) noexcept : i(int(value)) {}
    constexpr inline Flag(short value) noexcept : i(int(value)) {}
    constexpr inline Flag(unsigned short value) noexcept
        : i(int(unsigned int(value)))
    {
    }
    constexpr inline operator unsigned int() const noexcept
    {
        return unsigned int(i);
    }
};

template<typename Enum>
class Flags
{
    static_assert((sizeof(Enum) <= sizeof(int)),
                  "Flags uses an int as storage, so an enum with underlying "
                  "long long will overflow.");
    static_assert((std::is_enum<Enum>::value),
                  "Flags is only usable on enumeration types.");

public:
    typedef Enum enum_type;
    constexpr inline Flags() noexcept : i(0) {}
    constexpr inline Flags(Enum flags) noexcept : i(int(flags)) {}
    constexpr inline Flags(Flag flag) noexcept : i(flag) {}
    constexpr inline Flags &operator&=(int mask) noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline Flags &operator&=(uint mask) noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline Flags &operator&=(Enum mask) noexcept
    {
        i &= int(mask);
        return *this;
    }
    constexpr inline Flags &operator|=(Flags other) noexcept
    {
        i |= other.i;
        return *this;
    }
    constexpr inline Flags &operator|=(Enum other) noexcept
    {
        i |= int(other);
        return *this;
    }
    constexpr inline Flags &operator^=(Flags other) noexcept
    {
        i ^= other.i;
        return *this;
    }
    constexpr inline Flags &operator^=(Enum other) noexcept
    {
        i ^= int(other);
        return *this;
    }

    constexpr inline operator int() const noexcept { return i; }

    constexpr inline Flags operator|(Flags other) const noexcept
    {
        return Flags(Flag(i | other.i));
    }
    constexpr inline Flags operator|(Enum other) const noexcept
    {
        return Flags(Flag(i | int(other)));
    }
    constexpr inline Flags operator^(Flags other) const noexcept
    {
        return Flags(Flag(i ^ other.i));
    }
    constexpr inline Flags operator^(Enum other) const noexcept
    {
        return Flags(Flag(i ^ int(other)));
    }
    constexpr inline Flags operator&(int mask) const noexcept
    {
        return Flags(Flag(i & mask));
    }
    constexpr inline Flags operator&(uint mask) const noexcept
    {
        return Flags(Flag(i & mask));
    }
    constexpr inline Flags operator&(Enum other) const noexcept
    {
        return Flags(Flag(i & int(other)));
    }
    constexpr inline Flags operator~() const noexcept
    {
        return Flags(Flag(~i));
    }

    constexpr inline bool operator!() const noexcept { return !i; }

    constexpr inline bool testFlag(Enum flag) const noexcept
    {
        return (i & int(flag)) == int(flag) &&
               (int(flag) != 0 || i == int(flag));
    }
    constexpr inline Flags &setFlag(Enum flag, bool on = true) noexcept
    {
        return on ? (*this |= flag) : (*this &= ~int(flag));
    }

private:
    int i;
};

#define DECLARE_FLAGS(Flags, Enum) typedef Flags<Enum> Flags;

}// namespace dwg
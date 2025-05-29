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


/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#pragma once

#include <initializer_list>
#include <type_traits>

namespace dwg {

class QFlag
{
    int i;

public:
    constexpr inline QFlag(int value) noexcept : i(value) {}
    constexpr inline operator int() const noexcept
    {
        return i;
    }

    constexpr inline QFlag(unsigned int value) noexcept : i(int(value)) {}
    constexpr inline QFlag(short value) noexcept : i(int(value)) {}
    constexpr inline QFlag(unsigned short value) noexcept : i((int) (unsigned int) value) {}
    constexpr inline operator unsigned int() const noexcept
    {
        return (unsigned int) i;
    }
};


template<typename Enum>
class QFlags
{
    static_assert((sizeof(Enum) <= sizeof(int)), "QFlags uses an int as storage, so an enum with underlying "
                                                 "long long will overflow.");
    static_assert((std::is_enum<Enum>::value), "QFlags is only usable on enumeration types.");

    struct Private;
    typedef int(Private::*Zero);

public:
#if defined(_MSC_VER)
    typedef int Int;
#else
    typedef typename std::conditional<std::is_unsigned<typename std::underlying_type<Enum>::type>::value, unsigned int,
                                      signed int>::type Int;
#endif
    typedef Enum enum_type;

    constexpr inline QFlags(const QFlags &other)
    {
        i = other.i;
    }
    constexpr inline QFlags &operator=(const QFlags &other)
    {
        i = other.i;
        return *this;
    }
    constexpr inline QFlags(Enum flags) noexcept : i(Int(flags)) {}
    constexpr inline QFlags(Zero = nullptr) noexcept : i(0) {}
    constexpr inline QFlags(QFlag flag) noexcept : i(flag) {}

    constexpr inline QFlags(std::initializer_list<Enum> flags) noexcept
        : i(initializer_list_helper(flags.begin(), flags.end()))
    {
    }

    constexpr inline QFlags &operator&=(int mask) noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline QFlags &operator&=(unsigned int mask) noexcept
    {
        i &= mask;
        return *this;
    }
    constexpr inline QFlags &operator&=(Enum mask) noexcept
    {
        i &= Int(mask);
        return *this;
    }
    constexpr inline QFlags &operator|=(QFlags other) noexcept
    {
        i |= other.i;
        return *this;
    }
    constexpr inline QFlags &operator|=(Enum other) noexcept
    {
        i |= Int(other);
        return *this;
    }
    constexpr inline QFlags &operator^=(QFlags other) noexcept
    {
        i ^= other.i;
        return *this;
    }
    constexpr inline QFlags &operator^=(Enum other) noexcept
    {
        i ^= Int(other);
        return *this;
    }

    constexpr inline operator Int() const noexcept
    {
        return i;
    }

    constexpr inline QFlags operator|(QFlags other) const noexcept
    {
        return QFlags(QFlag(i | other.i));
    }
    constexpr inline QFlags operator|(Enum other) const noexcept
    {
        return QFlags(QFlag(i | Int(other)));
    }
    constexpr inline QFlags operator^(QFlags other) const noexcept
    {
        return QFlags(QFlag(i ^ other.i));
    }
    constexpr inline QFlags operator^(Enum other) const noexcept
    {
        return QFlags(QFlag(i ^ Int(other)));
    }
    constexpr inline QFlags operator&(int mask) const noexcept
    {
        return QFlags(QFlag(i & mask));
    }
    constexpr inline QFlags operator&(unsigned int mask) const noexcept
    {
        return QFlags(QFlag(i & mask));
    }
    constexpr inline QFlags operator&(Enum other) const noexcept
    {
        return QFlags(QFlag(i & Int(other)));
    }
    constexpr inline QFlags operator~() const noexcept
    {
        return QFlags(QFlag(~i));
    }

    constexpr inline bool operator!() const noexcept
    {
        return !i;
    }

    constexpr inline bool testFlag(Enum flag) const noexcept
    {
        return (i & Int(flag)) == Int(flag) && (Int(flag) != 0 || i == Int(flag));
    }
    constexpr inline QFlags &setFlag(Enum flag, bool on = true) noexcept
    {
        return on ? (*this |= flag) : (*this &= ~Int(flag));
    }

private:
    constexpr static inline Int
    initializer_list_helper(typename std::initializer_list<Enum>::const_iterator it,
                            typename std::initializer_list<Enum>::const_iterator end) noexcept
    {
        return (it == end ? Int(0) : (Int(*it) | initializer_list_helper(it + 1, end)));
    }

    Int i;
};

#define Q_DECLARE_FLAGS(Flags, Enum) typedef QFlags<Enum> Flags;

}// namespace dwg
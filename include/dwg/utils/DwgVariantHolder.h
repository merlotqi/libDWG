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
#include <dwg/utils/DateTime.h>
#include <dwg/Color.h>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <typeinfo>
#include <string_view>
#include <limits>
#include <type_traits>

namespace dwg {

class LIBDWG_API DwgVariantHolder
{
public:
    virtual ~DwgVariantHolder();
    virtual DwgVariantHolder clone() const = 0;
    virtual const std::type_info &type() const = 0;
    virtual void convert(char &) const = 0;
    virtual void convert(short &) const = 0;
    virtual void convert(int &) const = 0;
    virtual void convert(long long &) const = 0;
    virtual void convert(unsigned char &) const = 0;
    virtual void convert(unsigned short &) const = 0;
    virtual void convert(unsigned int &) const = 0;
    virtual void convert(unsigned long long &) const = 0;
    virtual void convert(DateTime &) const = 0;
    virtual void convert(Timestamp &) const = 0;
    virtual void convert(Color &) const = 0;
    virtual void convert(XY &) const = 0;
    virtual void convert(XYZ &) const = 0;
    virtual void convert(bool &) const = 0;
    virtual void convert(float &) const = 0;
    virtual void convert(double &) const = 0;
    virtual void convert(std::string &) const = 0;
    virtual void convert(std::wstring &) const = 0;

    virtual bool isArray() const = 0;
    virtual bool isVector() const = 0;
    virtual bool isList() const = 0;
    virtual bool isDeque() const = 0;
    virtual bool isInteger() const = 0;
    virtual bool isSigned() const = 0;
    virtual bool isNumeric() const = 0;
    virtual bool isBoolean() const = 0;
    virtual bool isString() const = 0;
    virtual bool isDateTime() const = 0;

protected:
	template <typename F, typename T,
		std::enable_if_t<(std::is_integral_v<F> && std::is_signed_v<F>) ||
			std::is_floating_point_v<F>, F>* = nullptr,
		std::enable_if_t<(std::is_integral_v<T> && std::is_signed_v<T>) ||
			std::is_floating_point_v<F>, T>* = nullptr>
    static void convert_to_smaller(const F &from, const T &to)
    {
        if constexpr ((std::is_integral_v<F>) && (std::is_floating_point_v<T>))
        {
            if (is_precision_lost<F, T>(from))
                throw std::out_of_range("");
        }
        check_upper_limit<F, T>(from);
        check_lower_limit<F, T>(from);
        to = static_cast<T>(from);
    }

	template <typename F, typename T,
		std::enable_if_t<std::is_same_v<F, bool>>* = nullptr,
		std::enable_if_t<std::is_floating_point_v<T>, T>* = nullptr>
    static void convert_to_smaller(const F &from, T &to)
    {
        to = static_cast<T>(from);
    }

	template <typename F, typename T,
		std::enable_if_t<std::is_integral_v<F> && !std::is_signed_v<F>, F>* = nullptr,
		std::enable_if_t<(std::is_integral_v<T> && !std::is_signed_v<T>) || std::is_floating_point_v<T>, T>* = nullptr>
    static void convert_to_smaller_unsigned(const F &from, T &to)
    {
        check_upper_limit<F, T>(from);
        to = static_cast<T>(from);
    }

	template <typename F, typename T,
		std::enable_if_t<std::is_integral_v<F> && std::is_signed_v<F>, F>* = nullptr,
		std::enable_if_t<std::is_integral_v<T> && !std::is_signed_v<T>, T>* = nullptr>
    static void convert_signed_to_unsigned(const F &from, T &to)
    {
        if (from < 0)
            throw std::out_of_range("");

            check_upper_limit<std::make_unsigned_t<F>, T>(from);
            to = static_cast<T>(from);
    }

	template <typename F, typename T, std::enable_if_t<std::is_floating_point_v<F>, bool> = true,
		std::enable_if_t<std::is_integral_v<T> && !std::is_signed_v<T>, T>* = nullptr>
    static void convert_signed_float_to_unsigned(const F &from, T &to)
    {
        if (from < 0)
            throw std::out_of_range("");
        
        check_upper_limit<F, T>(from);
        to = static_cast<T>(from);
    }

	template <typename F, typename T,
		std::enable_if_t<std::is_integral_v<F> && !std::is_signed_v<F>, F>* = nullptr,
		std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>, T>* = nullptr>
    static void convert_unsigned_to_signed(const F &from, T &to)
    {
        check_upper_limit<F, T>(from);
        to = static_cast<T>(from);
    }

    template <typename F, typename T, std::enable_if_t<std::is_signed_v<F> && std::is_signed_v<T> && (sizeof(F) <= sizeof(T))>* = nullptr>
    void convert_to_signed(const F &from, T &to) const
    {
        to = static_cast<T>(from);
    }
    
};

template<typename T>
class DwgVariantHolderT : public DwgVariantHolder
{
    T _val;
}

template<>
class DwgVariantHolderT<char> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<short> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<int> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<long long> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<unsigned char> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<unsigned short> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<unsigned int> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<unsigned long long> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<bool> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<float> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<double> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<std::string> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<std::wstring> : public DwgVariantHolder
{

};

template<typename T>
class DwgVariantHolderT<std::vector<T>> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<std::vector<unsigned char>> : public DwgVariantHolder
{

};

template<typename T>
class DwgVariantHolderT<std::list<T>> : public DwgVariantHolder
{

};

template<typename T>
class DwgVariantHolderT<std::deque<T>> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<DateTime> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<Timestamp> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<Color> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<XY> : public DwgVariantHolder
{

};

template<>
class DwgVariantHolderT<XYZ> : public DwgVariantHolder
{

};

}// namespace dwg
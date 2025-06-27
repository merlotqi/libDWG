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

#include <dwg/exports.h>
#include <string>
#include <vector>
#include <fmt/core.h>

namespace dwg {

class DwgVariantHolder;
class LIBDWG_API DwgVariant
{
public:
    DwgVariant();

    template<typename T>
    DwgVariant(const T &val)
    {
        construct(val);
    }

    DwgVariant(const DwgVariant &other);
    ~DwgVariant();

    void swap(DwgVariant &other);

    template<typename T>
    void convert(T &val) const
    {
        DwgVariantHolder *holder = content();
        if (!holder)
        {
            throw std::runtime_error("");
        }
        holder->convert(val);
    }

    template<typename T>
    T convert() const
    {
        DwgVariantHolder *holder = content();
        if (!holder)
        {
            throw std::runtime_error("");
        }

        if (typeid(T) == holder->type())
            return extract<T>();

        T r;
        holder->convert(r);
        return r;
    }

    template<typename T>
    operator T() const
    {
        DwgVariantHolder *holder = content();
        if(!holder)
            throw std::runtime_error("");
        if(typeid(T) == holder->type())
            return extract<T>();
        
        T r;
        holder->convert(r);
        return r;
    }

    template<typename T>
    const T &extract() const
    {
        DwgVariantHolder *holder = content();
        if (holder && holder->type() == typeid(T))
        {
            auto &&holderT = static_cast<DwgVariantHolderT<T> *>(holder);
            return holderT->value();
        }
        if(!holder)
            throw std::runtime_error("");
        else
            throw std::runtime_error(fmt::format("Can not convert {} to {}"), holder->type().name(), typeid(T).name());
    }

    template<typename T>
    DwgVariant &operator=(const T &other)
    {
        clear();
        construct(other);
        return *this;
    }

    bool operator!() const;
    
    DwgVariant operator=(const DwgVariant &other);
    
    const DwgVariant operator+(const DwgVariant &other) const;
    
    template<typename T>
    const DwgVariant operator+(const T &other) const
    {
        return convert<T>() + other;
    }

    DwgVariant &operator++();
    const DwgVariant operator++(int);
    DwgVariant &operator--();
    const DwgVariant operator--(int);

    template<typename T>
    DwgVariant &operator+=(const T &other)
    {
        return *this = convert<T>() + other;
    }

    DwgVariant &operator+=(const DwgVariant &other);

    template<typename T>
    DwgVariant &operator-=(const T &other)
    {
        return *this = convert<T>() - other;
    }

    DwgVariant &operator-=(const DwgVariant &other); 

    const DwgVariant operator*(const DwgVariant &other) const;
    
    template<typename T>
    const DwgVariant operator*(const T &other) const
    {
        return convert<T>() * other;
    }

    template<typename T>
    DwgVariant &operator*=(const T &other)
    {
        return *this = convert<T>() * other;
    }

    DwgVariant &operator*=(const DwgVariant &other);

    const DwgVariant operator/(const DwgVariant &other) const;
    
    template<typename T>
    const DwgVariant operator/(const T &other) const
    {
        return convert<T>() / other;
    }

    template<typename T>
    DwgVariant &operator/=(const T &other)
    {
        return *this = convert<T>() / other;
    }

    DwgVariant &operator/=(const DwgVariant &other);

	template <typename T>
	bool operator == (const T& other) const
    {
        if (isEmpty()) return false;
        return convert<T>() == other;
    }
    bool operator == (const DwgVariant& other) const;

	template <typename T>
	bool operator != (const T& other) const
    {
        if (isEmpty()) return true;
        return convert<T>() != other;
    }
    bool operator != (const DwgVariant& other) const;

    const std::type_info &type() const;
    
    void empty();
    void clear();
    bool isEmpty() const;
    bool isInteger() const;
    bool isSigned() const;
    bool isNumeric() const;
    bool isBoolean() const;
    bool isString() const;
    bool isDateTime() const;
    bool isColor() const;
    bool isCoordinate() const;

    std::string toString() const;

    static DwgVariant fromString(const std::strng &val);
    static std::string toString(const DwgVariant &var);

private:
    template<typename T>
    void construct(const T &v)
    {
        _holder.reset(new DwgVariantHolderT<T>(v));
    }

    DwgVariantHolder *content() const
    {
        return _holder.get();
    }

    std::unique_ptr<DwgVariantHolder> _holder;

};

}// namespace dwg
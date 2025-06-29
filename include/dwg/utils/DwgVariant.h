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
#include <dwg/utils/DwgVariantHolder.h>
#include <fmt/core.h>
#include <memory>
#include <string>
#include <vector>

namespace dwg {

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
            throw std::runtime_error("Can not convert empty value.");

        holder->convert(val);
    }

    template<typename T>
    T convert() const
    {
        DwgVariantHolder *holder = content();

        if (!holder)
            throw std::runtime_error("Can not convert empty value.");

        if (typeid(T) == holder->type())
            return extract<T>();

        T result;
        holder->convert(result);
        return result;
    }

    template<typename T>
    operator T() const
    {
        DwgVariantHolder *holder = content();

        if (!holder)
            throw std::runtime_error("Can not convert empty value.");

        if (typeid(T) == holder->type())
            return extract<T>();

        T result;
        holder->convert(result);
        return result;
    }

    template<typename T>
    const T &extract() const
    {
        DwgVariantHolder *holder = content();

        if ((holder != nullptr) && holder->type() == typeid(T))
        {
            auto *pHolderImpl = static_cast<DwgVariantHolderT<T> *>(holder);
            return pHolderImpl->value();
        }

        if (!holder)
            throw std::runtime_error("Can not extract empty value.");
        else
            throw std::runtime_error(fmt::format("Can not convert {} to {}.", std::string(holder->type().name()),
                                                 std::string(typeid(T).name())));
    }

    template<typename T>
    DwgVariant &operator=(const T &other)
    {
        clear();
        construct(other);
        return *this;
    }

    bool operator!() const;
    DwgVariant &operator=(const DwgVariant &other);

    template<typename T>
    const DwgVariant operator+(const T &other) const
    {
        return convert<T>() + other;
    }
    const DwgVariant operator+(const DwgVariant &other) const;

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
    const DwgVariant operator-(const T &other) const
    {
        return convert<T>() - other;
    }
    const DwgVariant operator-(const DwgVariant &other) const;

    template<typename T>
    DwgVariant &operator-=(const T &other)
    {
        return *this = convert<T>() - other;
    }
    DwgVariant &operator-=(const DwgVariant &other);

    template<typename T>
    const DwgVariant operator*(const T &other) const
    {
        return convert<T>() * other;
    }
    const DwgVariant operator*(const DwgVariant &other) const;

    template<typename T>
    DwgVariant &operator*=(const T &other)
    {
        return *this = convert<T>() * other;
    }
    DwgVariant &operator*=(const DwgVariant &other);

    template<typename T>
    const DwgVariant operator/(const T &other) const
    {
        return convert<T>() / other;
    }
    const DwgVariant operator/(const DwgVariant &other) const;

    template<typename T>
    DwgVariant &operator/=(const T &other)
    {
        return *this = convert<T>() / other;
    }
    DwgVariant &operator/=(const DwgVariant &other);

    template<typename T>
    bool operator==(const T &other) const
    {
        if (isEmpty())
            return false;
        return convert<T>() == other;
    }
    bool operator==(const DwgVariant &other) const;

    template<typename T>
    bool operator!=(const T &other) const
    {
        if (isEmpty())
            return true;
        return convert<T>() != other;
    }
    bool operator!=(const DwgVariant &other) const;

    template<typename T>
    bool operator<(const T &other) const
    {
        if (isEmpty())
            return false;
        return convert<T>() < other;
    }
    bool operator<(const DwgVariant &other) const;

    template<typename T>
    bool operator<=(const T &other) const
    {
        if (isEmpty())
            return false;
        return convert<T>() <= other;
    }
    bool operator<=(const DwgVariant &other) const;

    template<typename T>
    bool operator>(const T &other) const
    {
        if (isEmpty())
            return false;
        return convert<T>() > other;
    }
    bool operator>(const DwgVariant &other) const;

    template<typename T>
    bool operator>=(const T &other) const
    {
        if (isEmpty())
            return false;
        return convert<T>() >= other;
    }
    bool operator>=(const DwgVariant &other) const;

    template<typename T>
    bool operator||(const T &other) const
    {
        if (isEmpty())
            return false;
        return convert<bool>() || other;
    }
    bool operator||(const DwgVariant &other) const;

    template<typename T>
    bool operator&&(const T &other) const
    {
        if (isEmpty())
            return false;
        return convert<bool>() && other;
    }
    bool operator&&(const DwgVariant &other) const;

    const std::type_info &type() const;
    std::string typeName() const;

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
    std::size_t size() const;
    std::string toString() const;

private:
    template<typename T, typename E>
    DwgVariantHolderT<T> *holderImpl(const std::string errorMessage = "") const
    {
        DwgVariantHolder *holder = content();

        if (holder && holder->type() == typeid(T))
            return static_cast<DwgVariantHolderT<T> *>(holder);

        if (holder == nullptr)
            throw std::runtime_error("Can not access empty value.");
        else
            throw E(errorMessage);
    }

    template<typename T, typename N>
    DwgVariant &structIndexOperator(T *pStr, N n) const
    {
        return pStr->operator[](n);
    }

    DwgVariantHolder *content() const
    {
        return _placeholder.get();
    }

    template<typename ValueType>
    void construct(const ValueType &value)
    {
        _placeholder.reset(new DwgVariantHolderT<ValueType>(value));
    }

    template<typename T>
    T add(const DwgVariant &other) const
    {
        return convert<T>() + other.convert<T>();
    }

    template<typename T>
    T subtract(const DwgVariant &other) const
    {
        return convert<T>() - other.convert<T>();
    }

    template<typename T>
    T multiply(const DwgVariant &other) const
    {
        return convert<T>() * other.convert<T>();
    }

    template<typename T>
    T divide(const DwgVariant &other) const
    {
        return convert<T>() / other.convert<T>();
    }

    void construct(const DwgVariant &other);

    std::unique_ptr<DwgVariantHolder> _placeholder;
};

inline const DwgVariant operator+(const char *other, const DwgVariant &da)
{
    const std::string tmp = other;
    return tmp + da.convert<std::string>();
}

inline char operator+(const char &other, const DwgVariant &da)
{
    return other + da.convert<char>();
}

inline char operator-(const char &other, const DwgVariant &da)
{
    return other - da.convert<char>();
}

inline char operator*(const char &other, const DwgVariant &da)
{
    return other * da.convert<char>();
}

inline char operator/(const char &other, const DwgVariant &da)
{
    return other / da.convert<char>();
}

inline char operator+=(char &other, const DwgVariant &da)
{
    return other += da.convert<char>();
}

inline char operator-=(char &other, const DwgVariant &da)
{
    return other -= da.convert<char>();
}

inline char operator*=(char &other, const DwgVariant &da)
{
    return other *= da.convert<char>();
}

inline char operator/=(char &other, const DwgVariant &da)
{
    return other /= da.convert<char>();
}

inline bool operator==(const char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<char>();
}

inline bool operator!=(const char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<char>();
}

inline bool operator<(const char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<char>();
}

inline bool operator<=(const char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<char>();
}

inline bool operator>(const char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<char>();
}

inline bool operator>=(const char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<char>();
}

inline unsigned char operator+(const unsigned char &other, const DwgVariant &da)
{
    return other + da.convert<unsigned char>();
}

inline unsigned char operator-(const unsigned char &other, const DwgVariant &da)
{
    return other - da.convert<unsigned char>();
}

inline unsigned char operator*(const unsigned char &other, const DwgVariant &da)
{
    return other * da.convert<unsigned char>();
}

inline unsigned char operator/(const unsigned char &other, const DwgVariant &da)
{
    return other / da.convert<unsigned char>();
}

inline unsigned char operator+=(unsigned char &other, const DwgVariant &da)
{
    return other += da.convert<unsigned char>();
}

inline unsigned char operator-=(unsigned char &other, const DwgVariant &da)
{
    return other -= da.convert<unsigned char>();
}

inline unsigned char operator*=(unsigned char &other, const DwgVariant &da)
{
    return other *= da.convert<unsigned char>();
}

inline unsigned char operator/=(unsigned char &other, const DwgVariant &da)
{
    return other /= da.convert<unsigned char>();
}

inline bool operator==(const unsigned char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<unsigned char>();
}

inline bool operator!=(const unsigned char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<unsigned char>();
}

inline bool operator<(const unsigned char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<unsigned char>();
}

inline bool operator<=(const unsigned char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<unsigned char>();
}

inline bool operator>(const unsigned char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<unsigned char>();
}

inline bool operator>=(const unsigned char &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<unsigned char>();
}

inline short operator+(const short &other, const DwgVariant &da)
{
    return other + da.convert<short>();
}

inline short operator-(const short &other, const DwgVariant &da)
{
    return other - da.convert<short>();
}

inline short operator*(const short &other, const DwgVariant &da)
{
    return other * da.convert<short>();
}

inline short operator/(const short &other, const DwgVariant &da)
{
    return other / da.convert<short>();
}

inline short operator+=(short &other, const DwgVariant &da)
{
    return other += da.convert<short>();
}

inline short operator-=(short &other, const DwgVariant &da)
{
    return other -= da.convert<short>();
}

inline short operator*=(short &other, const DwgVariant &da)
{
    return other *= da.convert<short>();
}

inline short operator/=(short &other, const DwgVariant &da)
{
    return other /= da.convert<short>();
}

inline bool operator==(const short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<short>();
}

inline bool operator!=(const short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<short>();
}

inline bool operator<(const short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<short>();
}

inline bool operator<=(const short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<short>();
}

inline bool operator>(const short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<short>();
}

inline bool operator>=(const short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<short>();
}

inline unsigned short operator+(const unsigned short &other, const DwgVariant &da)
{
    return other + da.convert<unsigned short>();
}

inline unsigned short operator-(const unsigned short &other, const DwgVariant &da)
{
    return other - da.convert<unsigned short>();
}

inline unsigned short operator*(const unsigned short &other, const DwgVariant &da)
{
    return other * da.convert<unsigned short>();
}

inline unsigned short operator/(const unsigned short &other, const DwgVariant &da)
{
    return other / da.convert<unsigned short>();
}

inline unsigned short operator+=(unsigned short &other, const DwgVariant &da)
{
    return other += da.convert<unsigned short>();
}

inline unsigned short operator-=(unsigned short &other, const DwgVariant &da)
{
    return other -= da.convert<unsigned short>();
}

inline unsigned short operator*=(unsigned short &other, const DwgVariant &da)
{
    return other *= da.convert<unsigned short>();
}

inline unsigned short operator/=(unsigned short &other, const DwgVariant &da)
{
    return other /= da.convert<unsigned short>();
}

inline bool operator==(const unsigned short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<unsigned short>();
}

inline bool operator!=(const unsigned short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<unsigned short>();
}

inline bool operator<(const unsigned short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<unsigned short>();
}

inline bool operator<=(const unsigned short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<unsigned short>();
}

inline bool operator>(const unsigned short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<unsigned short>();
}

inline bool operator>=(const unsigned short &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<unsigned short>();
}

inline int operator+(const int &other, const DwgVariant &da)
{
    return other + da.convert<int>();
}

inline int operator-(const int &other, const DwgVariant &da)
{
    return other - da.convert<int>();
}

inline int operator*(const int &other, const DwgVariant &da)
{
    return other * da.convert<int>();
}

inline int operator/(const int &other, const DwgVariant &da)
{
    return other / da.convert<int>();
}

inline int operator+=(int &other, const DwgVariant &da)
{
    return other += da.convert<int>();
}

inline int operator-=(int &other, const DwgVariant &da)
{
    return other -= da.convert<int>();
}

inline int operator*=(int &other, const DwgVariant &da)
{
    return other *= da.convert<int>();
}

inline int operator/=(int &other, const DwgVariant &da)
{
    return other /= da.convert<int>();
}

inline bool operator==(const int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<int>();
}

inline bool operator!=(const int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<int>();
}

inline bool operator<(const int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<int>();
}

inline bool operator<=(const int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<int>();
}

inline bool operator>(const int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<int>();
}

inline bool operator>=(const int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<int>();
}

inline unsigned int operator+(const unsigned int &other, const DwgVariant &da)
{
    return other + da.convert<unsigned int>();
}

inline unsigned int operator-(const unsigned int &other, const DwgVariant &da)
{
    return other - da.convert<unsigned int>();
}

inline unsigned int operator*(const unsigned int &other, const DwgVariant &da)
{
    return other * da.convert<unsigned int>();
}

inline unsigned int operator/(const unsigned int &other, const DwgVariant &da)
{
    return other / da.convert<unsigned int>();
}

inline unsigned int operator+=(unsigned int &other, const DwgVariant &da)
{
    return other += da.convert<unsigned int>();
}

inline unsigned int operator-=(unsigned int &other, const DwgVariant &da)
{
    return other -= da.convert<unsigned int>();
}

inline unsigned int operator*=(unsigned int &other, const DwgVariant &da)
{
    return other *= da.convert<unsigned int>();
}

inline unsigned int operator/=(unsigned int &other, const DwgVariant &da)
{
    return other /= da.convert<unsigned int>();
}

inline bool operator==(const unsigned int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<unsigned int>();
}

inline bool operator!=(const unsigned int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<unsigned int>();
}

inline bool operator<(const unsigned int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<unsigned int>();
}

inline bool operator<=(const unsigned int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<unsigned int>();
}

inline bool operator>(const unsigned int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<unsigned int>();
}

inline bool operator>=(const unsigned int &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<unsigned int>();
}

inline long long operator+(const long long &other, const DwgVariant &da)
{
    return other + da.convert<long long>();
}

inline long long operator-(const long long &other, const DwgVariant &da)
{
    return other - da.convert<long long>();
}

inline long long operator*(const long long &other, const DwgVariant &da)
{
    return other * da.convert<long long>();
}

inline long long operator/(const long long &other, const DwgVariant &da)
{
    return other / da.convert<long long>();
}

inline long long operator+=(long long &other, const DwgVariant &da)
{
    return other += da.convert<long long>();
}

inline long long operator-=(long long &other, const DwgVariant &da)
{
    return other -= da.convert<long long>();
}

inline long long operator*=(long long &other, const DwgVariant &da)
{
    return other *= da.convert<long long>();
}

inline long long operator/=(long long &other, const DwgVariant &da)
{
    return other /= da.convert<long long>();
}

inline bool operator==(const long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<long long>();
}

inline bool operator!=(const long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<long long>();
}

inline bool operator<(const long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<long long>();
}

inline bool operator<=(const long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<long long>();
}

inline bool operator>(const long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<long long>();
}

inline bool operator>=(const long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<long long>();
}

inline unsigned long long operator+(const unsigned long long &other, const DwgVariant &da)
{
    return other + da.convert<unsigned long long>();
}

inline unsigned long long operator-(const unsigned long long &other, const DwgVariant &da)
{
    return other - da.convert<unsigned long long>();
}

inline unsigned long long operator*(const unsigned long long &other, const DwgVariant &da)
{
    return other * da.convert<unsigned long long>();
}

inline unsigned long long operator/(const unsigned long long &other, const DwgVariant &da)
{
    return other / da.convert<unsigned long long>();
}

inline unsigned long long operator+=(unsigned long long &other, const DwgVariant &da)
{
    return other += da.convert<unsigned long long>();
}

inline unsigned long long operator-=(unsigned long long &other, const DwgVariant &da)
{
    return other -= da.convert<unsigned long long>();
}

inline unsigned long long operator*=(unsigned long long &other, const DwgVariant &da)
{
    return other *= da.convert<unsigned long long>();
}

inline unsigned long long operator/=(unsigned long long &other, const DwgVariant &da)
{
    return other /= da.convert<unsigned long long>();
}

inline bool operator==(const unsigned long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<unsigned long long>();
}

inline bool operator!=(const unsigned long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<unsigned long long>();
}

inline bool operator<(const unsigned long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<unsigned long long>();
}

inline bool operator<=(const unsigned long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<unsigned long long>();
}

inline bool operator>(const unsigned long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<unsigned long long>();
}

inline bool operator>=(const unsigned long long &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<unsigned long long>();
}

inline float operator+(const float &other, const DwgVariant &da)
{
    return other + da.convert<float>();
}

inline float operator-(const float &other, const DwgVariant &da)
{
    return other - da.convert<float>();
}

inline float operator*(const float &other, const DwgVariant &da)
{
    return other * da.convert<float>();
}

inline float operator/(const float &other, const DwgVariant &da)
{
    return other / da.convert<float>();
}

inline float operator+=(float &other, const DwgVariant &da)
{
    return other += da.convert<float>();
}

inline float operator-=(float &other, const DwgVariant &da)
{
    return other -= da.convert<float>();
}

inline float operator*=(float &other, const DwgVariant &da)
{
    return other *= da.convert<float>();
}

inline float operator/=(float &other, const DwgVariant &da)
{
    return other /= da.convert<float>();
}

inline bool operator==(const float &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<float>();
}

inline bool operator!=(const float &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<float>();
}

inline bool operator<(const float &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<float>();
}

inline bool operator<=(const float &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<float>();
}

inline bool operator>(const float &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<float>();
}

inline bool operator>=(const float &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<float>();
}

inline double operator+(const double &other, const DwgVariant &da)
{
    return other + da.convert<double>();
}

inline double operator-(const double &other, const DwgVariant &da)
{
    return other - da.convert<double>();
}

inline double operator*(const double &other, const DwgVariant &da)
{
    return other * da.convert<double>();
}

inline double operator/(const double &other, const DwgVariant &da)
{
    return other / da.convert<double>();
}

inline double operator+=(double &other, const DwgVariant &da)
{
    return other += da.convert<double>();
}

inline double operator-=(double &other, const DwgVariant &da)
{
    return other -= da.convert<double>();
}

inline double operator*=(double &other, const DwgVariant &da)
{
    return other *= da.convert<double>();
}

inline double operator/=(double &other, const DwgVariant &da)
{
    return other /= da.convert<double>();
}

inline bool operator==(const double &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<double>();
}

inline bool operator!=(const double &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<double>();
}

inline bool operator<(const double &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other < da.convert<double>();
}

inline bool operator<=(const double &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other <= da.convert<double>();
}

inline bool operator>(const double &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other > da.convert<double>();
}

inline bool operator>=(const double &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other >= da.convert<double>();
}

inline bool operator==(const bool &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return false;
    return other == da.convert<bool>();
}

inline bool operator!=(const bool &other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return other != da.convert<bool>();
}

inline bool operator!=(const char *other, const DwgVariant &da)
{
    if (da.isEmpty())
        return true;
    return da.convert<std::string>() != other;
}

}// namespace dwg
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

#include <dwg/Color.h>
#include <dwg/Coordinate.h>
#include <dwg/exports.h>
#include <dwg/utils/DateTime.h>
#include <fmt/core.h>
#include <string_view>
#include <type_traits>
#include <typeinfo>
#include <vector>
#undef min
#undef max
#include <dwg/utils/Encoding.h>
#include <limits>
#include <stdexcept>

namespace dwg {

#define DWG_VARIANT_OUT_OF_RANGE(str, from)                                                                        \
    throw std::out_of_range(fmt::format("{} (({}/{}) {} > ({}/{}) {}).", std::string_view(#str), typeid(F).name(), \
                                        numValDigits(from), std::to_string(from), typeid(T).name(),                \
                                        numTypeDigits<T>(), std::to_string(static_cast<T>(from))))

class DwgVariant;
class LIBDWG_API DwgVariantHolder
{
public:
    virtual ~DwgVariantHolder();
    virtual DwgVariantHolder *clone() const = 0;
    virtual const std::type_info &type() const = 0;
    virtual void convert(char &val) const;
    virtual void convert(short &val) const;
    virtual void convert(int &val) const;
    virtual void convert(long long &val) const;
    virtual void convert(unsigned char &val) const;
    virtual void convert(unsigned short &val) const;
    virtual void convert(unsigned int &val) const;
    virtual void convert(unsigned long long &val) const;
    virtual void convert(DateTime &val) const;
    virtual void convert(Timestamp &val) const;
    virtual void convert(Color &val) const;
    virtual void convert(XY &val) const;
    virtual void convert(XYZ &val) const;
    virtual void convert(bool &val) const;
    virtual void convert(float &val) const;
    virtual void convert(double &val) const;
    virtual void convert(std::string &val) const;
    virtual void convert(std::wstring &val) const;
    virtual void convert(std::vector<unsigned char> &val) const;
    virtual bool isBlob() const;
    virtual bool isInteger() const;
    virtual bool isSigned() const;
    virtual bool isNumeric() const;
    virtual bool isBoolean() const;
    virtual bool isString() const;
    virtual bool isDateTime() const;
    virtual bool isColor() const;
    virtual bool isCoordinate() const;
    virtual std::size_t size() const;

protected:
    DwgVariantHolder();

    template<typename F, typename T,
             std::enable_if_t<(std::is_integral_v<F> && std::is_signed_v<F>) || std::is_floating_point_v<F>, F> * =
                     nullptr,
             std::enable_if_t<(std::is_integral_v<T> && std::is_signed_v<T>) || std::is_floating_point_v<F>, T> * =
                     nullptr>
    static void convertToSmaller(const F &from, T &to)
    {
        if constexpr ((std::is_integral_v<F>) && (std::is_floating_point_v<T>) )
        {
            if (isPrecisionLost<F, T>(from))
                DWG_VARIANT_OUT_OF_RANGE("Lost precision", from);
        }
        checkUpperLimit<F, T>(from);
        checkLowerLimit<F, T>(from);
        to = static_cast<T>(from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F> && std::is_signed_v<T>, F> * = nullptr,
             std::enable_if_t<std::is_floating_point_v<T>, T> * = nullptr>
    static void convertToSmaller(const F &from, T &to)
    {
        if (isPrecisionLost<F, T>(from))
            DWG_VARIANT_OUT_OF_RANGE("Lost precision", from);
        to = static_cast<T>(from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_same_v<F, bool>> * = nullptr,
             std::enable_if_t<std::is_floating_point_v<T>, T> * = nullptr>
    static void convertToSmaller(const F &from, T &to)
    {
        to = static_cast<T>(from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F> && !std::is_signed_v<F>, F> * = nullptr,
             std::enable_if_t<(std::is_integral_v<T> && !std::is_signed_v<T>) || std::is_floating_point_v<T>, T> * =
                     nullptr>
    static void convertToSmallerUnsigned(const F &from, T &to)
    {
        checkUpperLimit<F, T>(from);
        to = static_cast<T>(from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F> && std::is_signed_v<F>, F> * = nullptr,
             std::enable_if_t<std::is_integral_v<T> && !std::is_signed_v<T>, T> * = nullptr>
    static void convertSignedToUnsigned(const F &from, T &to)
    {
        if (from < 0)
            DWG_VARIANT_OUT_OF_RANGE("Value too small", from);
        checkUpperLimit<std::make_unsigned_t<F>, T>(from);
        to = static_cast<T>(from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_floating_point_v<F>, bool> = true,
             std::enable_if_t<std::is_integral_v<T> && !std::is_signed_v<T>, T> * = nullptr>
    static void convertSignedFloatToUnsigned(const F &from, T &to)
    {
        if (from < 0)
            DWG_VARIANT_OUT_OF_RANGE("Value too small", from);
        checkUpperLimit<F, T>(from);
        to = static_cast<T>(from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F> && !std::is_signed_v<F>, F> * = nullptr,
             std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>, T> * = nullptr>
    static void convertUnsignedToSigned(const F &from, T &to)
    {
        checkUpperLimit<F, T>(from);
        to = static_cast<T>(from);
    }

    template<typename F, typename T,
             std::enable_if_t<std::is_signed_v<F> && std::is_signed_v<T> && (sizeof(F) <= sizeof(T))> * = nullptr>
    void convertToSigned(const F &from, T &to) const
    {
        to = static_cast<T>(from);
    }

    template<typename F, typename T,
             std::enable_if_t<std::is_signed_v<F> && std::is_signed_v<T> && (sizeof(F) > sizeof(T))> * = nullptr>
    void convertToSigned(const F &from, T &to) const
    {
        convertToSmaller(from, to);
    }

    template<typename F, typename T, std::enable_if_t<!std::is_signed_v<F> && std::is_signed_v<T>> * = nullptr>
    void convertToSigned(const F &from, T &to) const
    {
        convertUnsignedToSigned(from, to);
    }

    template<typename F, typename T,
             std::enable_if_t<!std::is_signed_v<F> && !std::is_signed_v<T> && (sizeof(F) <= sizeof(T))> * = nullptr>
    void convertToUnsigned(const F &from, T &to) const
    {
        to = static_cast<T>(from);
    }

    template<typename F, typename T,
             std::enable_if_t<!std::is_signed_v<F> && !std::is_signed_v<T> && (sizeof(F) > sizeof(T))> * = nullptr>
    void convertToUnsigned(const F &from, T &to) const
    {
        convertToSmallerUnsigned(from, to);
    }

    template<typename F, typename T, std::enable_if_t<std::is_signed_v<F> && !std::is_signed_v<T>> * = nullptr>
    void convertToUnsigned(const F &from, T &to) const
    {
        convertSignedToUnsigned(from, to);
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F>, bool> = true,
             std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    static void convertToFP(F &from, T &to)
    {
        if (isPrecisionLost<F, T>(from))
            DWG_VARIANT_OUT_OF_RANGE("Lost precision", from);
        to = static_cast<T>(from);
    }

private:
    template<typename T>
    static constexpr T unpreserveSign(const T &value)
    {
        if constexpr (std::is_signed_v<T>)
        {
            return (value < 0) ? -value : value;
        }
        else
        {
            return value;
        }
    }

    template<typename T, std::enable_if_t<std::is_same_v<T, bool>, bool> = true>
    static constexpr int numValDigits(const T &value)
    {
        return 1;
    }

    template<typename T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>, bool> = true>
    static constexpr int numValDigits(const T &value)
    {
        using U = std::make_unsigned_t<T>;
        if (value == 0)
            return 0;
        int digitCount = 0;
        U locVal = static_cast<U>(unpreserveSign(value));
        while (locVal >>= 1) ++digitCount;
        return digitCount;
    }

    template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    static constexpr int numValDigits(T value)
    {
        return numValDigits<int64_t>(static_cast<int64_t>(value));
    }

    template<typename T, std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    static constexpr int numTypeDigits()
    {
        return std::numeric_limits<T>::digits;
    }

    template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
    static constexpr int numTypeDigits()
    {
        return numValDigits(std::numeric_limits<T>::max());
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F>, bool> = true,
             std::enable_if_t<std::is_floating_point_v<T>, bool> = true>
    static bool isPrecisionLost(const F &from)
    {
        return numValDigits(from) > numTypeDigits<T>();
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F>, bool> = true>
    static void checkUpperLimit(const F &from)
    {
        if (from > static_cast<F>(std::numeric_limits<T>::max()))
            DWG_VARIANT_OUT_OF_RANGE("Value too big", from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_integral_v<F>, bool> = true>
    static void checkLowerLimit(const F &from)
    {
        if (from < static_cast<F>(std::numeric_limits<T>::min()))
            DWG_VARIANT_OUT_OF_RANGE("Value too small", from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_floating_point_v<F>, bool> = true>
    static void checkUpperLimit(const F &from)
    {
        if ((from > static_cast<F>(std::numeric_limits<T>::max())))
            DWG_VARIANT_OUT_OF_RANGE("Value too big", from);
    }

    template<typename F, typename T, std::enable_if_t<std::is_floating_point_v<F>, bool> = true>
    static void checkLowerLimit(const F &from)
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            if (static_cast<F>(-std::numeric_limits<T>::max()) > from)
                DWG_VARIANT_OUT_OF_RANGE("Value too small", from);
        }
        else if (from < static_cast<F>(std::numeric_limits<T>::min()))
            DWG_VARIANT_OUT_OF_RANGE("Value too small", from);
    }
};


template<typename T>
class DwgVariantHolderT : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const T &val) : _val(val) {}
    ~DwgVariantHolderT() override = default;

    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;

    const std::type_info &type() const override
    {
        return typeid(T);
    }

    void convert(char &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToSigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(short &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToSigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(int &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToSigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(long long &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToSigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(unsigned char &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToUnsigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(unsigned short &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToUnsigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(unsigned int &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToUnsigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(unsigned long long &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            convertToUnsigned(std::underlying_type_t<T>(_val), val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(bool &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            val = (std::underlying_type_t<T>(_val) != 0);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(float &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            val = static_cast<float>(_val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(double &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            val = static_cast<double>(_val);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(std::string &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            val = fmt::format(std::underlying_type_t<T>(_val));
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    void convert(std::wstring &val) const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            std::string str = fmt::format(std::underlying_type_t<T>(_val));
            val = Encoding::Utf8().toUnicode(str);
        }
        else
        {
            DwgVariantHolder::convert(val);
        }
    }

    bool isInteger() const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            return std::numeric_limits<std::underlying_type_t<T>>::is_integer;
        }
        else
        {
            return DwgVariantHolder::isInteger();
        }
    }

    bool isSigned() const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            return std::numeric_limits<std::underlying_type_t<T>>::is_signed;
        }
        else
        {
            return DwgVariantHolder::isSigned();
        }
    }

    bool isNumeric() const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            return std::numeric_limits<std::underlying_type_t<T>>::is_specialized;
        }
        else
        {
            return DwgVariantHolder::isNumeric();
        }
    }

    bool isBoolean() const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            return false;
        }
        else
        {
            return DwgVariantHolder::isBoolean();
        }
    }

    bool isString() const override
    {
        if constexpr (std::is_enum_v<T>)
        {
            return false;
        }
        else
        {
            return DwgVariantHolder::isString();
        }
    }

    DwgVariantHolder *clone() const override
    {
        return new DwgVariantHolderT<T>(_val);
    }

    const T &value() const
    {
        return _val;
    }

private:
    T _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<char> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(char val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(std::wstring &val) const override;
    DwgVariantHolder *clone() const override;
    const char &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    char _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<short> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(short val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(std::wstring &val) const override;
    DwgVariantHolder *clone() const override;
    const short &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isString() const override;

private:
    short _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<int> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(int val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const int &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    int _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<long long> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(long long val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(DateTime &dt) const override;
    void convert(Timestamp &val) const override;
    DwgVariantHolder *clone() const override;
    const long long &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    long long _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<unsigned char> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(unsigned char val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const unsigned char &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    unsigned char _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<unsigned short> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(unsigned short val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const unsigned short &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    unsigned short _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<unsigned int> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(unsigned int val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const unsigned int &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    unsigned int _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<unsigned long long> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(unsigned long long val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(DateTime &dt) const override;
    void convert(Timestamp &val) const override;
    DwgVariantHolder *clone() const override;
    const unsigned long long &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    unsigned long long _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<bool> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(bool val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const bool &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    bool _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<float> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(float val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const float &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    float _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<double> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(double val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const double &value() const;
    bool isInteger() const override;
    bool isSigned() const override;
    bool isNumeric() const override;
    bool isBoolean() const override;
    bool isString() const override;

private:
    double _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<std::string> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const char *val);
    DwgVariantHolderT(const std::string &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(std::wstring &val) const override;
    void convert(DateTime &val) const override;
    void convert(Timestamp &ts) const override;
    DwgVariantHolder *clone() const override;
    const std::string &value() const;
    bool isString() const override;
    std::size_t size() const override;
    char &operator[](std::string::size_type n);
    const char &operator[](std::string::size_type n) const;

private:
    std::string _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<std::wstring> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const char *val);
    DwgVariantHolderT(const wchar_t *val);
    DwgVariantHolderT(const std::wstring &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::wstring &val) const override;
    void convert(std::string &val) const override;
    void convert(DateTime &val) const override;
    void convert(Timestamp &ts) const override;
    DwgVariantHolder *clone() const override;
    const std::wstring &value() const;
    bool isString() const override;
    std::size_t size() const override;
    wchar_t &operator[](std::wstring::size_type n);
    const wchar_t &operator[](std::wstring::size_type n) const;
    std::string toStdString() const;

private:
    std::wstring _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<std::vector<unsigned char>> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const std::vector<unsigned char> &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(std::string &val) const override;
    DwgVariantHolder *clone() const override;
    const std::vector<unsigned char> &value() const;
    bool isBlob() const override;
    std::size_t size() const override;
    unsigned char &operator[](typename std::vector<unsigned char>::size_type n);
    const unsigned char &operator[](typename std::vector<unsigned char>::size_type n) const;

private:
    std::vector<unsigned char> _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<DateTime> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const DateTime &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;

    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(std::string &val) const override;
    void convert(DateTime &val) const override;
    void convert(Timestamp &ts) const override;
    DwgVariantHolder *clone() const override;
    const DateTime &value() const;
    bool isDateTime() const override;

private:
    DateTime _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<Timestamp> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const Timestamp &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;

    const std::type_info &type() const override;
    void convert(long long &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(std::string &val) const override;
    void convert(DateTime &val) const override;
    void convert(Timestamp &ts) const override;
    DwgVariantHolder *clone() const override;
    const Timestamp &value() const;
    bool isDateTime() const override;

private:
    Timestamp _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<Color> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const Color &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(std::wstring &val) const override;
    void convert(DateTime &val) const override;
    void convert(Timestamp &ts) const override;
    DwgVariantHolder *clone() const override;
    const Color &value() const;
    bool isColor() const override;

private:
    Color _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<XY> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const XY &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(std::wstring &val) const override;
    void convert(DateTime &val) const override;
    void convert(Timestamp &ts) const override;
    DwgVariantHolder *clone() const override;
    const XY &value() const;
    bool isCoordinate() const override;

private:
    XY _val;
};


template<>
class LIBDWG_API DwgVariantHolderT<XYZ> : public DwgVariantHolder
{
public:
    DwgVariantHolderT(const XYZ &val);
    ~DwgVariantHolderT() override = default;
    DwgVariantHolderT() = delete;
    DwgVariantHolderT(const DwgVariantHolderT &) = delete;
    DwgVariantHolderT &operator=(const DwgVariantHolderT &) = delete;
    const std::type_info &type() const override;
    void convert(char &val) const override;
    void convert(short &val) const override;
    void convert(int &val) const override;
    void convert(long long &val) const override;
    void convert(unsigned char &val) const override;
    void convert(unsigned short &val) const override;
    void convert(unsigned int &val) const override;
    void convert(unsigned long long &val) const override;
    void convert(bool &val) const override;
    void convert(float &val) const override;
    void convert(double &val) const override;
    void convert(std::string &val) const override;
    void convert(std::wstring &val) const override;
    void convert(DateTime &val) const override;
    void convert(Timestamp &ts) const override;
    DwgVariantHolder *clone() const override;
    const XYZ &value() const;
    bool isCoordinate() const override;

private:
    XYZ _val;
};

#undef DWG_VARIANT_OUT_OF_RANGE

}// namespace  dwg

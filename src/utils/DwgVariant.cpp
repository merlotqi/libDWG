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

#include <algorithm>
#include <cctype>
#include <dwg/utils/DwgVariant.h>

namespace dwg {

DwgVariant::DwgVariant() {}

DwgVariant::DwgVariant(const DwgVariant &other)
{
    if ((this != &other) && !other.isEmpty())
        construct(other);
}

DwgVariant::~DwgVariant() {}

DwgVariant &DwgVariant::operator=(const DwgVariant &rhs)
{
    if (this == &rhs)
        return *this;
    clear();
    if (!rhs.isEmpty())
        construct(rhs);
    return *this;
}

const DwgVariant DwgVariant::operator+(const DwgVariant &other) const
{
    if (isInteger())
    {
        if (isSigned())
            return add<long long>(other);
        else
            return add<unsigned long long>(other);
    }
    else if (isNumeric())
        return add<double>(other);
    else if (isString())
        return add<std::string>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

DwgVariant &DwgVariant::operator+=(const DwgVariant &other)
{
    if (isInteger())
    {
        if (isSigned())
            return *this = add<long long>(other);
        else
            return *this = add<unsigned long long>(other);
    }
    else if (isNumeric())
        return *this = add<double>(other);
    else if (isString())
        return *this = add<std::string>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

const DwgVariant DwgVariant::operator-(const DwgVariant &other) const
{
    if (isInteger())
    {
        if (isSigned())
            return subtract<long long>(other);
        else
            return subtract<unsigned long long>(other);
    }
    else if (isNumeric())
        return subtract<double>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

DwgVariant &DwgVariant::operator-=(const DwgVariant &other)
{
    if (isInteger())
    {
        if (isSigned())
            return *this = subtract<long long>(other);
        else
            return *this = subtract<unsigned long long>(other);
    }
    else if (isNumeric())
        return *this = subtract<double>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

const DwgVariant DwgVariant::operator*(const DwgVariant &other) const
{
    if (isInteger())
    {
        if (isSigned())
            return multiply<long long>(other);
        else
            return multiply<unsigned long long>(other);
    }
    else if (isNumeric())
        return multiply<double>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

DwgVariant &DwgVariant::operator*=(const DwgVariant &other)
{
    if (isInteger())
    {
        if (isSigned())
            return *this = multiply<long long>(other);
        else
            return *this = multiply<unsigned long long>(other);
    }
    else if (isNumeric())
        return *this = multiply<double>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

const DwgVariant DwgVariant::operator/(const DwgVariant &other) const
{
    if (isInteger())
    {
        if (isSigned())
            return divide<long long>(other);
        else
            return divide<unsigned long long>(other);
    }
    else if (isNumeric())
        return divide<double>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

DwgVariant &DwgVariant::operator/=(const DwgVariant &other)
{
    if (isInteger())
    {
        if (isSigned())
            return *this = divide<long long>(other);
        else
            return *this = divide<unsigned long long>(other);
    }
    else if (isNumeric())
        return *this = divide<double>(other);
    else
        throw std::runtime_error("Invalid operation for this data type.");
}

DwgVariant &DwgVariant::operator++()
{
    if (!isInteger())
        throw std::runtime_error("Invalid operation for this data type.");

    return *this = *this + 1;
}

const DwgVariant DwgVariant::operator++(int)
{
    if (!isInteger())
        throw std::runtime_error("Invalid operation for this data type.");

    DwgVariant tmp(*this);
    *this += 1;
    return tmp;
}

DwgVariant &DwgVariant::operator--()
{
    if (!isInteger())
        throw std::runtime_error("Invalid operation for this data type.");

    return *this = *this - 1;
}

const DwgVariant DwgVariant::operator--(int)
{
    if (!isInteger())
        throw std::runtime_error("Invalid operation for this data type.");

    DwgVariant tmp(*this);
    *this -= 1;
    return tmp;
}

bool DwgVariant::operator==(const DwgVariant &other) const
{
    if (isEmpty() != other.isEmpty())
        return false;
    if (isEmpty() && other.isEmpty())
        return true;
    return convert<std::string>() == other.convert<std::string>();
}

bool DwgVariant::operator!=(const DwgVariant &other) const
{
    if (isEmpty() && other.isEmpty())
        return false;
    else if (isEmpty() || other.isEmpty())
        return true;

    return convert<std::string>() != other.convert<std::string>();
}

bool DwgVariant::operator<(const DwgVariant &other) const
{
    if (isEmpty() || other.isEmpty())
        return false;
    return convert<std::string>() < other.convert<std::string>();
}

bool DwgVariant::operator<=(const DwgVariant &other) const
{
    if (isEmpty() || other.isEmpty())
        return false;
    return convert<std::string>() <= other.convert<std::string>();
}

bool DwgVariant::operator>(const DwgVariant &other) const
{
    if (isEmpty() || other.isEmpty())
        return false;
    return convert<std::string>() > other.convert<std::string>();
}

bool DwgVariant::operator>=(const DwgVariant &other) const
{
    if (isEmpty() || other.isEmpty())
        return false;
    return convert<std::string>() >= other.convert<std::string>();
}

bool DwgVariant::operator||(const DwgVariant &other) const
{
    if (isEmpty() || other.isEmpty())
        return false;
    return convert<bool>() || other.convert<bool>();
}

bool DwgVariant::operator&&(const DwgVariant &other) const
{
    if (isEmpty() || other.isEmpty())
        return false;
    return convert<bool>() && other.convert<bool>();
}

void DwgVariant::clear()
{
    _placeholder.release();
}

std::string DwgVariant::toString() const
{
    DwgVariantHolder *holder = content();

    if (!holder)
        throw std::runtime_error("Can not convert empty value.");

    if (typeid(std::string) == holder->type())
        return extract<std::string>();
    else
    {
        std::string result;
        holder->convert(result);
        return result;
    }
}

void DwgVariant::construct(const DwgVariant &other)
{
    if (!other.isEmpty())
        _placeholder.reset(other.content()->clone());
}

void DwgVariant::swap(DwgVariant &other)
{
    if (this == &other)
        return;

    if (!_placeholder && !other._placeholder)
    {
        _placeholder.swap(other._placeholder);
    }
    else
    {
        const DwgVariant tmp(*this);
        try
        {
            construct(other);
            other = tmp;
        }
        catch (...)
        {
            construct(tmp);
            throw;
        }
    }
}

const std::type_info &DwgVariant::type() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->type() : typeid(void);
}

std::string DwgVariant::typeName() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->type().name() : std::string();
}

bool DwgVariant::operator!() const
{
    return !convert<bool>();
}

bool DwgVariant::isEmpty() const
{
    return nullptr == content();
}

bool DwgVariant::isInteger() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isInteger() : false;
}

bool DwgVariant::isSigned() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isSigned() : false;
}

bool DwgVariant::isNumeric() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isNumeric() : false;
}

bool DwgVariant::isBoolean() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isBoolean() : false;
}

bool DwgVariant::isString() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isString() : false;
}

bool DwgVariant::isDateTime() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isDateTime() : false;
}

bool DwgVariant::isColor() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isColor() : false;
}

bool DwgVariant::isCoordinate() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->isCoordinate() : false;
}

std::size_t DwgVariant::size() const
{
    DwgVariantHolder *holder = content();
    return (holder != nullptr) ? holder->size() : 0;
}

}// namespace dwg
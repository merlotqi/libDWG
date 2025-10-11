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

#include <dwg/units/UnitStyleFormat.h>
#include <stdexcept>

namespace dwg {

UnitStyleFormat::UnitStyleFormat()
    : _linearDecimalPlaces(2), _angularDecimalPlaces(0), _decimalSeparator("."), _feetInchesSeparator("-"),
      _degreesSymbol("°"), _minutesSymbol("\'"), _secondsSymbol("\""), _radiansSymbol("r"), _gradiansSymbol("g"),
      _feetSymbol("\'"), _inchesSymbol("\""), _fractionHeightScale(1.0), _fractionType(FractionFormat::Horizontal),
      _angularZeroHandling(ZeroHandling::SuppressDecimalTrailingZeroes),
      _linearZeroHandling(ZeroHandling::SuppressDecimalTrailingZeroes)
{
}

UnitStyleFormat::~UnitStyleFormat() = default;

short UnitStyleFormat::angularDecimalPlaces() const
{
    return _angularDecimalPlaces;
}

void UnitStyleFormat::setAngularDecimalPlaces(short value)
{
    if (value < 0)
    {
        throw std::out_of_range("The number of decimal places must be equals or greater than zero.");
    }
    _angularDecimalPlaces = value;
}

ZeroHandling UnitStyleFormat::angularZeroHandling() const
{
    return _angularZeroHandling;
}

void UnitStyleFormat::setAngularZeroHandling(ZeroHandling value)
{
    _angularZeroHandling = value;
}

const std::string &UnitStyleFormat::decimalSeparator() const
{
    return _decimalSeparator;
}

void UnitStyleFormat::DecimalSeparator(const std::string &value)
{
    _decimalSeparator = value;
}

const std::string &UnitStyleFormat::degreesSymbol() const
{
    return _degreesSymbol;
}

void UnitStyleFormat::setDegreesSymbol(const std::string &value)
{
    _degreesSymbol = value;
}

const std::string &UnitStyleFormat::feetInchesSeparator() const
{
    return _feetInchesSeparator;
}

void UnitStyleFormat::setFeetInchesSeparator(const std::string &value)
{
    _feetInchesSeparator = value;
}

const std::string &UnitStyleFormat::feetSymbol() const
{
    return _feetSymbol;
}

void UnitStyleFormat::setFeetSymbol(const std::string &value)
{
    _feetSymbol = value;
}

double UnitStyleFormat::fractionHeightScale() const
{
    return _fractionHeightScale;
}

void UnitStyleFormat::setFractionHeightScale(double value)
{
    if (value <= 0)
    {
        throw std::out_of_range("The fraction height scale must be greater than zero.");
    }
    _angularDecimalPlaces = value;
}

FractionFormat UnitStyleFormat::fractionType() const
{
    return _fractionType;
}

void UnitStyleFormat::setFractionType(FractionFormat value)
{
    _fractionType = value;
}

const std::string &UnitStyleFormat::gradiansSymbol() const
{
    return _gradiansSymbol;
}

void UnitStyleFormat::setGradiansSymbol(const std::string &value)
{
    _gradiansSymbol = value;
}

const std::string &UnitStyleFormat::inchesSymbol() const
{
    return _inchesSymbol;
}

void UnitStyleFormat::setInchesSymbol(const std::string &value)
{
    _inchesSymbol = value;
}

short UnitStyleFormat::linearDecimalPlaces() const
{
    return _linearDecimalPlaces;
}

void UnitStyleFormat::setLinearDecimalPlaces(short value)
{
    if (value < 0)
    {
        throw std::out_of_range("The number of decimal places must be equals or greater than zero.");
    }
    _linearDecimalPlaces = value;
}

ZeroHandling UnitStyleFormat::linearZeroHandling() const
{
    return _linearZeroHandling;
}

void UnitStyleFormat::setLinearZeroHandling(ZeroHandling value)
{
    _linearZeroHandling = value;
}

const std::string &UnitStyleFormat::minutesSymbol() const
{
    return _minutesSymbol;
}

void UnitStyleFormat::setMinutesSymbol(const std::string &value)
{
    _minutesSymbol = value;
}

const std::string &UnitStyleFormat::radiansSymbol() const
{
    return _radiansSymbol;
}

void UnitStyleFormat::setRadiansSymbol(const std::string &value)
{
    _radiansSymbol = value;
}

const std::string &UnitStyleFormat::secondsSymbol() const
{
    return _secondsSymbol;
}

void UnitStyleFormat::setSecondsSymbol(const std::string &value)
{
    _secondsSymbol = value;
}

bool UnitStyleFormat::suppressAngularLeadingZeros() const
{
    return _linearZeroHandling == ZeroHandling::SuppressDecimalLeadingZeroes ||
           _linearZeroHandling == ZeroHandling::SuppressDecimalLeadingAndTrailingZeroes;
}

bool UnitStyleFormat::suppressAngularTrailingZeros() const
{
    return _linearZeroHandling == ZeroHandling::SuppressDecimalTrailingZeroes ||
           _linearZeroHandling == ZeroHandling::SuppressDecimalLeadingAndTrailingZeroes;
}

bool UnitStyleFormat::suppressLinearLeadingZeros() const
{
    return _linearZeroHandling == ZeroHandling::SuppressDecimalLeadingZeroes ||
           _linearZeroHandling == ZeroHandling::SuppressDecimalLeadingAndTrailingZeroes;
}

bool UnitStyleFormat::suppressLinearTrailingZeros() const
{
    return _linearZeroHandling == ZeroHandling::SuppressDecimalTrailingZeroes ||
           _linearZeroHandling == ZeroHandling::SuppressDecimalLeadingAndTrailingZeroes;
}

bool UnitStyleFormat::suppressZeroFeet() const
{
    return _linearZeroHandling == ZeroHandling::SuppressZeroFeetAndInches ||
           _linearZeroHandling == ZeroHandling::SuppressZeroFeetShowZeroInches;
}

bool UnitStyleFormat::suppressZeroInches() const
{
    return _linearZeroHandling == ZeroHandling::SuppressZeroFeetAndInches ||
           _linearZeroHandling == ZeroHandling::ShowZeroFeetSuppressZeroInches;
}

std::string UnitStyleFormat::zeroHandlingFormat(bool isAngular)
{
    short decimalPlaces = linearDecimalPlaces();
    ZeroHandling handling;

    if (isAngular)
    {
        handling = angularZeroHandling();
    }
    else
    {
        handling = linearZeroHandling();
    }

    char leading = handling == ZeroHandling::SuppressDecimalLeadingZeroes ||
                                   handling == ZeroHandling::SuppressDecimalLeadingAndTrailingZeroes
                           ? '#'
                           : '0';

    char trailing = handling == ZeroHandling::SuppressDecimalTrailingZeroes ||
                                    handling == ZeroHandling::SuppressDecimalLeadingAndTrailingZeroes
                            ? '#'
                            : '0';

    std::string zeros;
    zeros += leading;
    zeros += ".";
    for (int i = 0; i < decimalPlaces; i++)
    {
        zeros += trailing;
    }
    return zeros;
}

std::string UnitStyleFormat::toArchitectural(double value)
{
    return std::string();
}

std::string UnitStyleFormat::toDecimal(double value, bool isAngular)
{
    return std::string();
}

std::string UnitStyleFormat::toDegreesMinutesSeconds(double angle)
{
    return std::string();
}

std::string UnitStyleFormat::toEngineering(double value)
{
    return std::string();
}

std::string UnitStyleFormat::toFractional(double value)
{
    return std::string();
}

std::string UnitStyleFormat::toGradians(double angle)
{
    return std::string();
}

std::string UnitStyleFormat::toRadians(double angle)
{
    return std::string();
}

std::string UnitStyleFormat::toScientific(double value)
{
    return std::string();
}

void UnitStyleFormat::getFraction(double number, int precision, int &numerator, int &denominator)
{


    numerator = static_cast<int>((number - (int) number) * precision);
    int commonFactor = getGCD(numerator, precision);
    if (commonFactor <= 0)
    {
        commonFactor = 1;
    }
    numerator = numerator / commonFactor;
    denominator = precision / commonFactor;
}

int UnitStyleFormat::getGCD(int number1, int number2)
{
    int a = number1;
    int b = number2;
    while (b != 0)
    {
        int count = a % b;
        a = b;
        b = count;
    }
    return a;
}

}// namespace dwg

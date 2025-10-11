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
#include <dwg/tables/FractionFormat.h>
#include <dwg/tables/ZeroHandling.h>
#include <string>

namespace dwg {

class LIBDWG_API UnitStyleFormat
{
public:
    UnitStyleFormat();
    ~UnitStyleFormat();

    short angularDecimalPlaces() const;
    void setAngularDecimalPlaces(short);

    ZeroHandling angularZeroHandling() const;
    void setAngularZeroHandling(ZeroHandling);

    const std::string &decimalSeparator() const;
    void DecimalSeparator(const std::string &);

    const std::string &degreesSymbol() const;
    void setDegreesSymbol(const std::string &);

    const std::string &feetInchesSeparator() const;
    void setFeetInchesSeparator(const std::string &);

    const std::string &feetSymbol() const;
    void setFeetSymbol(const std::string &);

    double fractionHeightScale() const;
    void setFractionHeightScale(double);

    FractionFormat fractionType() const;
    void setFractionType(FractionFormat);

    const std::string &gradiansSymbol() const;
    void setGradiansSymbol(const std::string &);

    const std::string &inchesSymbol() const;
    void setInchesSymbol(const std::string &);

    short linearDecimalPlaces() const;
    void setLinearDecimalPlaces(short);

    ZeroHandling linearZeroHandling() const;
    void setLinearZeroHandling(ZeroHandling);

    const std::string &minutesSymbol() const;
    void setMinutesSymbol(const std::string &);

    const std::string &radiansSymbol() const;
    void setRadiansSymbol(const std::string &);

    const std::string &secondsSymbol() const;
    void setSecondsSymbol(const std::string &);

    bool suppressAngularLeadingZeros() const;
    bool suppressAngularTrailingZeros() const;
    bool suppressLinearLeadingZeros() const;
    bool suppressLinearTrailingZeros() const;
    bool suppressZeroFeet() const;
    bool suppressZeroInches() const;

    std::string zeroHandlingFormat(bool isAngular = false);
    std::string toArchitectural(double value);
    std::string toDecimal(double value, bool isAngular = false);
    std::string toDegreesMinutesSeconds(double angle);
    std::string toEngineering(double value);
    std::string toFractional(double value);
    std::string toGradians(double angle);
    std::string toRadians(double angle);
    std::string toScientific(double value);
    static void getFraction(double number, int precision, int &numerator, int &denominator);

private:
    static int getGCD(int number1, int number2);

private:
    short _angularDecimalPlaces;
    ZeroHandling _angularZeroHandling;
    std::string _decimalSeparator;
    std::string _degreesSymbol;
    std::string _feetInchesSeparator;
    std::string _feetSymbol;
    double _fractionHeightScale;
    FractionFormat _fractionType;
    std::string _gradiansSymbol;
    std::string _inchesSymbol;
    short _linearDecimalPlaces;
    ZeroHandling _linearZeroHandling;
    std::string _minutesSymbol;
    std::string _radiansSymbol;
    std::string _secondsSymbol;
};

}// namespace dwg

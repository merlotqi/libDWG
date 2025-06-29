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

#include <dwg/utils/DwgVariantHolder.h>
#include <dwg/utils/Encoding.h>
#include <dwg/utils/StringHelp.h>
#include <string.h>

namespace dwg {

/* ---------------------------- DwgVariantHolder ---------------------------- */

DwgVariantHolder::~DwgVariantHolder() {}

void DwgVariantHolder::convert(char &) const
{
    throw std::runtime_error("Can not convert to char");
}

void DwgVariantHolder::convert(short &) const
{
    throw std::runtime_error("Can not convert to short");
}

void DwgVariantHolder::convert(int &) const
{
    throw std::runtime_error("Can not convert to int");
}

void DwgVariantHolder::convert(long long &) const
{
    throw std::runtime_error("Can not convert to long long");
}

void DwgVariantHolder::convert(unsigned char &) const
{
    throw std::runtime_error("Can not convert to unsigned char");
}

void DwgVariantHolder::convert(unsigned short &) const
{
    throw std::runtime_error("Can not convert to unsigned short");
}

void DwgVariantHolder::convert(unsigned int &) const
{
    throw std::runtime_error("Can not convert to unsigned int");
}

void DwgVariantHolder::convert(unsigned long long &) const
{
    throw std::runtime_error("Can not convert to unsigned long long");
}

void DwgVariantHolder::convert(DateTime &) const
{
    throw std::runtime_error("Can not convert to DateTime");
}

void DwgVariantHolder::convert(Timestamp &) const
{
    throw std::runtime_error("Can not convert to Timestamp");
}

void DwgVariantHolder::convert(Color &val) const
{
    throw std::runtime_error("Can not convert to Timestamp");
}

void DwgVariantHolder::convert(XY &val) const
{
    throw std::runtime_error("Can not convert to Timestamp");
}

void DwgVariantHolder::convert(XYZ &val) const
{
    throw std::runtime_error("Can not convert to Timestamp");
}

void DwgVariantHolder::convert(bool &) const
{
    throw std::runtime_error("Can not convert to bool");
}

void DwgVariantHolder::convert(float &) const
{
    throw std::runtime_error("Can not convert to float");
}

void DwgVariantHolder::convert(double &) const
{
    throw std::runtime_error("Can not convert to double");
}

void DwgVariantHolder::convert(std::string &) const
{
    throw std::runtime_error("Can not convert to std::string");
}

void DwgVariantHolder::convert(std::wstring &) const
{
    throw std::runtime_error("Can not convert to std::wstring");
}

void DwgVariantHolder::convert(std::vector<unsigned char> &val) const {}

bool DwgVariantHolder::isBlob() const
{
    return false;
}

bool DwgVariantHolder::isInteger() const
{
    return false;
}

bool DwgVariantHolder::isSigned() const
{
    return false;
}

bool DwgVariantHolder::isNumeric() const
{
    return false;
}

bool DwgVariantHolder::isBoolean() const
{
    return false;
}

bool DwgVariantHolder::isString() const
{
    return false;
}

bool DwgVariantHolder::isDateTime() const
{
    return false;
}

bool DwgVariantHolder::isColor() const
{
    return false;
}

bool DwgVariantHolder::isCoordinate() const
{
    return false;
}

std::size_t DwgVariantHolder::size() const
{
    return 1u;
}

DwgVariantHolder::DwgVariantHolder() {}

/* ------------------------- DwgVariantHolderT<char> ------------------------ */
DwgVariantHolderT<char>::DwgVariantHolderT(char val) : _val(val) {}


const std::type_info &DwgVariantHolderT<char>::type() const
{
    return typeid(char);
}

void DwgVariantHolderT<char>::convert(char &val) const
{
    val = _val;
}

void DwgVariantHolderT<char>::convert(short &val) const
{
    val = _val;
}

void DwgVariantHolderT<char>::convert(int &val) const
{
    val = _val;
}

void DwgVariantHolderT<char>::convert(long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<char>::convert(unsigned char &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<char>::convert(unsigned short &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<char>::convert(unsigned int &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<char>::convert(unsigned long long &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<char>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<char>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<char>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<char>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

void DwgVariantHolderT<char>::convert(std::wstring &val) const
{
    const std::string str = fmt::format("{}", _val);
    val = Encoding::Utf8().toUnicode(str);
}

DwgVariantHolder *DwgVariantHolderT<char>::clone() const
{
    return new DwgVariantHolderT<char>(_val);
}

const char &DwgVariantHolderT<char>::value() const
{
    return _val;
}

bool DwgVariantHolderT<char>::isInteger() const
{
    return std::numeric_limits<char>::is_integer;
}

bool DwgVariantHolderT<char>::isSigned() const
{
    return std::numeric_limits<char>::is_signed;
}

bool DwgVariantHolderT<char>::isNumeric() const
{
    return std::numeric_limits<char>::is_specialized;
}

bool DwgVariantHolderT<char>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<char>::isString() const
{
    return false;
}

/* ------------------------ DwgVariantHolderT<short> ------------------------ */
DwgVariantHolderT<short>::DwgVariantHolderT(short val) : _val(val) {}


const std::type_info &DwgVariantHolderT<short>::type() const
{
    return typeid(short);
}

void DwgVariantHolderT<short>::convert(char &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<short>::convert(short &val) const
{
    val = _val;
}

void DwgVariantHolderT<short>::convert(int &val) const
{
    val = _val;
}

void DwgVariantHolderT<short>::convert(long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<short>::convert(unsigned char &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<short>::convert(unsigned short &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<short>::convert(unsigned int &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<short>::convert(unsigned long long &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<short>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<short>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<short>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<short>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

void DwgVariantHolderT<short>::convert(std::wstring &val) const
{
    const std::string str = fmt::format("{}", _val);
    val = Encoding::Utf8().toUnicode(str);
}

DwgVariantHolder *DwgVariantHolderT<short>::clone() const
{
    return new DwgVariantHolderT<short>(_val);
}

const short &DwgVariantHolderT<short>::value() const
{
    return _val;
}

bool DwgVariantHolderT<short>::isInteger() const
{
    return std::numeric_limits<short>::is_integer;
}

bool DwgVariantHolderT<short>::isSigned() const
{
    return std::numeric_limits<short>::is_signed;
}

bool DwgVariantHolderT<short>::isNumeric() const
{
    return std::numeric_limits<short>::is_specialized;
}

bool DwgVariantHolderT<short>::isString() const
{
    return false;
}

/* ------------------------- DwgVariantHolderT<int> ------------------------- */

DwgVariantHolderT<int>::DwgVariantHolderT(int val) : _val(val) {}

const std::type_info &DwgVariantHolderT<int>::type() const
{
    return typeid(int);
}

void DwgVariantHolderT<int>::convert(char &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<int>::convert(short &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<int>::convert(int &val) const
{
    val = _val;
}

void DwgVariantHolderT<int>::convert(long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<int>::convert(unsigned char &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<int>::convert(unsigned short &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<int>::convert(unsigned int &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<int>::convert(unsigned long long &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<int>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<int>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<int>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<int>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

DwgVariantHolder *DwgVariantHolderT<int>::clone() const
{
    return new DwgVariantHolderT<int>(_val);
}

const int &DwgVariantHolderT<int>::value() const
{
    return _val;
}

bool DwgVariantHolderT<int>::isInteger() const
{
    return std::numeric_limits<int>::is_integer;
}

bool DwgVariantHolderT<int>::isSigned() const
{
    return std::numeric_limits<int>::is_signed;
}

bool DwgVariantHolderT<int>::isNumeric() const
{
    return std::numeric_limits<int>::is_specialized;
}

bool DwgVariantHolderT<int>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<int>::isString() const
{
    return false;
}

/* ---------------------- DwgVariantHolderT<long long> ---------------------- */

DwgVariantHolderT<long long>::DwgVariantHolderT(long long val) : _val(val) {}

const std::type_info &DwgVariantHolderT<long long>::type() const
{
    return typeid(long long);
}

void DwgVariantHolderT<long long>::convert(char &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<long long>::convert(short &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<long long>::convert(int &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<long long>::convert(long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<long long>::convert(unsigned char &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<long long>::convert(unsigned short &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<long long>::convert(unsigned int &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<long long>::convert(unsigned long long &val) const
{
    convertSignedToUnsigned(_val, val);
}

void DwgVariantHolderT<long long>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<long long>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<long long>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<long long>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

void DwgVariantHolderT<long long>::convert(DateTime &dt) const
{
    dt = Timestamp(_val);
}

void DwgVariantHolderT<long long>::convert(Timestamp &val) const
{
    val = Timestamp(_val);
}

DwgVariantHolder *DwgVariantHolderT<long long>::clone() const
{
    return new DwgVariantHolderT<long long>(_val);
}

const long long &DwgVariantHolderT<long long>::value() const
{
    return _val;
}

bool DwgVariantHolderT<long long>::isInteger() const
{
    return std::numeric_limits<long long>::is_integer;
}

bool DwgVariantHolderT<long long>::isSigned() const
{
    return std::numeric_limits<long long>::is_signed;
}

bool DwgVariantHolderT<long long>::isNumeric() const
{
    return std::numeric_limits<long long>::is_specialized;
}

bool DwgVariantHolderT<long long>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<long long>::isString() const
{
    return false;
}

/* -------------------- DwgVariantHolderT<unsigned char> -------------------- */

DwgVariantHolderT<unsigned char>::DwgVariantHolderT(unsigned char val) : _val(val) {}

const std::type_info &DwgVariantHolderT<unsigned char>::type() const
{
    return typeid(unsigned char);
}

void DwgVariantHolderT<unsigned char>::convert(char &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned char>::convert(short &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned char>::convert(int &val) const
{
    val = static_cast<int>(_val);
}

void DwgVariantHolderT<unsigned char>::convert(long long &val) const
{
    val = static_cast<long long>(_val);
}

void DwgVariantHolderT<unsigned char>::convert(unsigned char &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned char>::convert(unsigned short &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned char>::convert(unsigned int &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned char>::convert(unsigned long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned char>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<unsigned char>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned char>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned char>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

DwgVariantHolder *DwgVariantHolderT<unsigned char>::clone() const
{
    return new DwgVariantHolderT<unsigned char>(_val);
}

const unsigned char &DwgVariantHolderT<unsigned char>::value() const
{
    return _val;
}

bool DwgVariantHolderT<unsigned char>::isInteger() const
{
    return std::numeric_limits<unsigned char>::is_integer;
}

bool DwgVariantHolderT<unsigned char>::isSigned() const
{
    return std::numeric_limits<unsigned char>::is_signed;
}

bool DwgVariantHolderT<unsigned char>::isNumeric() const
{
    return std::numeric_limits<unsigned char>::is_specialized;
}

bool DwgVariantHolderT<unsigned char>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<unsigned char>::isString() const
{
    return false;
}

/* -------------------- DwgVariantHolderT<unsigned short> ------------------- */

DwgVariantHolderT<unsigned short>::DwgVariantHolderT(unsigned short val) : _val(val) {}

const std::type_info &DwgVariantHolderT<unsigned short>::type() const
{
    return typeid(unsigned short);
}

void DwgVariantHolderT<unsigned short>::convert(char &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned short>::convert(short &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned short>::convert(int &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned short>::convert(long long &val) const
{
    val = static_cast<long long>(_val);
}

void DwgVariantHolderT<unsigned short>::convert(unsigned char &val) const
{
    convertToSmallerUnsigned(_val, val);
}

void DwgVariantHolderT<unsigned short>::convert(unsigned short &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned short>::convert(unsigned int &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned short>::convert(unsigned long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned short>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<unsigned short>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned short>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned short>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

DwgVariantHolder *DwgVariantHolderT<unsigned short>::clone() const
{
    return new DwgVariantHolderT<unsigned short>(_val);
}

const unsigned short &DwgVariantHolderT<unsigned short>::value() const
{
    return _val;
}

bool DwgVariantHolderT<unsigned short>::isInteger() const
{
    return std::numeric_limits<unsigned short>::is_integer;
}

bool DwgVariantHolderT<unsigned short>::isSigned() const
{
    return std::numeric_limits<unsigned short>::is_signed;
}

bool DwgVariantHolderT<unsigned short>::isNumeric() const
{
    return std::numeric_limits<unsigned short>::is_specialized;
}

bool DwgVariantHolderT<unsigned short>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<unsigned short>::isString() const
{
    return false;
}

/* --------------------- DwgVariantHolderT<unsigned int> -------------------- */

DwgVariantHolderT<unsigned int>::DwgVariantHolderT(unsigned int val) : _val(val) {}

const std::type_info &DwgVariantHolderT<unsigned int>::type() const
{
    return typeid(unsigned int);
}

void DwgVariantHolderT<unsigned int>::convert(char &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(short &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(int &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(long long &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(unsigned char &val) const
{
    convertToSmallerUnsigned(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(unsigned short &val) const
{
    convertToSmallerUnsigned(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(unsigned int &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned int>::convert(unsigned long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned int>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<unsigned int>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned int>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

DwgVariantHolder *DwgVariantHolderT<unsigned int>::clone() const
{
    return new DwgVariantHolderT<unsigned int>(_val);
}

const unsigned int &DwgVariantHolderT<unsigned int>::value() const
{
    return _val;
}

bool DwgVariantHolderT<unsigned int>::isInteger() const
{
    return std::numeric_limits<unsigned int>::is_integer;
}

bool DwgVariantHolderT<unsigned int>::isSigned() const
{
    return std::numeric_limits<unsigned int>::is_signed;
}

bool DwgVariantHolderT<unsigned int>::isNumeric() const
{
    return std::numeric_limits<unsigned int>::is_specialized;
}

bool DwgVariantHolderT<unsigned int>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<unsigned int>::isString() const
{
    return false;
}

/* ------------------ DwgVariantHolderT<unsigned long long> ----------------- */

DwgVariantHolderT<unsigned long long>::DwgVariantHolderT(unsigned long long val) : _val(val) {}

const std::type_info &DwgVariantHolderT<unsigned long long>::type() const
{
    return typeid(unsigned long long);
}

void DwgVariantHolderT<unsigned long long>::convert(char &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(short &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(int &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(long long &val) const
{
    convertUnsignedToSigned(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(unsigned char &val) const
{
    convertToSmallerUnsigned(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(unsigned short &val) const
{
    convertToSmallerUnsigned(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(unsigned int &val) const
{
    convertToSmallerUnsigned(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(unsigned long long &val) const
{
    val = _val;
}

void DwgVariantHolderT<unsigned long long>::convert(bool &val) const
{
    val = (_val != 0);
}

void DwgVariantHolderT<unsigned long long>::convert(float &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(double &val) const
{
    convertToFP(_val, val);
}

void DwgVariantHolderT<unsigned long long>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

void DwgVariantHolderT<unsigned long long>::convert(DateTime &dt) const
{
    long long val;
    convertUnsignedToSigned(_val, val);
    dt = Timestamp(val);
}

void DwgVariantHolderT<unsigned long long>::convert(Timestamp &val) const
{
    long long tmp;
    convertUnsignedToSigned(_val, tmp);
    val = Timestamp(tmp);
}

DwgVariantHolder *DwgVariantHolderT<unsigned long long>::clone() const
{
    return new DwgVariantHolderT<unsigned long long>(_val);
}

const unsigned long long &DwgVariantHolderT<unsigned long long>::value() const
{
    return _val;
}

bool DwgVariantHolderT<unsigned long long>::isInteger() const
{
    return std::numeric_limits<unsigned long long>::is_integer;
}

bool DwgVariantHolderT<unsigned long long>::isSigned() const
{
    return std::numeric_limits<unsigned long long>::is_signed;
}

bool DwgVariantHolderT<unsigned long long>::isNumeric() const
{
    return std::numeric_limits<unsigned long long>::is_specialized;
}

bool DwgVariantHolderT<unsigned long long>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<unsigned long long>::isString() const
{
    return false;
}

/* ------------------------- DwgVariantHolderT<bool> ------------------------ */

DwgVariantHolderT<bool>::DwgVariantHolderT(bool val) : _val(val) {}

const std::type_info &DwgVariantHolderT<bool>::type() const
{
    return typeid(bool);
}

void DwgVariantHolderT<bool>::convert(char &val) const
{
    val = static_cast<char>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(short &val) const
{
    val = static_cast<short>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(int &val) const
{
    val = static_cast<int>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(long long &val) const
{
    val = static_cast<long long>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(unsigned char &val) const
{
    val = static_cast<unsigned char>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(unsigned short &val) const
{
    val = static_cast<unsigned short>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(unsigned int &val) const
{
    val = static_cast<unsigned int>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(unsigned long long &val) const
{
    val = static_cast<unsigned long long>(_val ? 1 : 0);
}

void DwgVariantHolderT<bool>::convert(bool &val) const
{
    val = _val;
}

void DwgVariantHolderT<bool>::convert(float &val) const
{
    val = (_val ? 1.0f : 0.0f);
}

void DwgVariantHolderT<bool>::convert(double &val) const
{
    val = (_val ? 1.0 : 0.0);
}

void DwgVariantHolderT<bool>::convert(std::string &val) const
{
    val = (_val ? "true" : "false");
}

DwgVariantHolder *DwgVariantHolderT<bool>::clone() const
{
    return new DwgVariantHolderT<bool>(_val);
}

const bool &DwgVariantHolderT<bool>::value() const
{
    return _val;
}

bool DwgVariantHolderT<bool>::isInteger() const
{
    return std::numeric_limits<bool>::is_integer;
}

bool DwgVariantHolderT<bool>::isSigned() const
{
    return std::numeric_limits<bool>::is_signed;
}

bool DwgVariantHolderT<bool>::isNumeric() const
{
    return std::numeric_limits<bool>::is_specialized;
}

bool DwgVariantHolderT<bool>::isBoolean() const
{
    return true;
}

bool DwgVariantHolderT<bool>::isString() const
{
    return false;
}

/* ------------------------ DwgVariantHolderT<float> ------------------------ */

DwgVariantHolderT<float>::DwgVariantHolderT(float val) : _val(val) {}

const std::type_info &DwgVariantHolderT<float>::type() const
{
    return typeid(float);
}

void DwgVariantHolderT<float>::convert(char &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<float>::convert(short &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<float>::convert(int &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<float>::convert(long long &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<float>::convert(unsigned char &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<float>::convert(unsigned short &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<float>::convert(unsigned int &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<float>::convert(unsigned long long &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<float>::convert(bool &val) const
{
    val = _val > std::numeric_limits<float>::min() || _val < -1 * std::numeric_limits<float>::min();
}

void DwgVariantHolderT<float>::convert(float &val) const
{
    val = _val;
}

void DwgVariantHolderT<float>::convert(double &val) const
{
    val = _val;
}

void DwgVariantHolderT<float>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

DwgVariantHolder *DwgVariantHolderT<float>::clone() const
{
    return new DwgVariantHolderT<float>(_val);
}

const float &DwgVariantHolderT<float>::value() const
{
    return _val;
}

bool DwgVariantHolderT<float>::isInteger() const
{
    return std::numeric_limits<float>::is_integer;
}

bool DwgVariantHolderT<float>::isSigned() const
{
    return std::numeric_limits<float>::is_signed;
}

bool DwgVariantHolderT<float>::isNumeric() const
{
    return std::numeric_limits<float>::is_specialized;
}

bool DwgVariantHolderT<float>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<float>::isString() const
{
    return false;
}

/* ------------------------ DwgVariantHolderT<double> ----------------------- */

DwgVariantHolderT<double>::DwgVariantHolderT(double val) : _val(val) {}

const std::type_info &DwgVariantHolderT<double>::type() const
{
    return typeid(double);
}

void DwgVariantHolderT<double>::convert(char &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<double>::convert(short &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<double>::convert(int &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<double>::convert(long long &val) const
{
    convertToSmaller(_val, val);
}

void DwgVariantHolderT<double>::convert(unsigned char &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<double>::convert(unsigned short &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<double>::convert(unsigned int &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<double>::convert(unsigned long long &val) const
{
    convertSignedFloatToUnsigned(_val, val);
}

void DwgVariantHolderT<double>::convert(bool &val) const
{
    val = _val > std::numeric_limits<double>::min() || _val < -1 * std::numeric_limits<double>::min();
}

void DwgVariantHolderT<double>::convert(float &val) const
{
    const double fMin = -1 * std::numeric_limits<float>::max();
    const double fMax = std::numeric_limits<float>::max();

    if (_val < fMin)
        throw std::out_of_range("Value too small.");
    if (_val > fMax)
        throw std::out_of_range("Value too large.");

    val = static_cast<float>(_val);
}

void DwgVariantHolderT<double>::convert(double &val) const
{
    val = _val;
}

void DwgVariantHolderT<double>::convert(std::string &val) const
{
    val = fmt::format("{}", _val);
}

DwgVariantHolder *DwgVariantHolderT<double>::clone() const
{
    return new DwgVariantHolderT<double>(_val);
}

const double &DwgVariantHolderT<double>::value() const
{
    return _val;
}

bool DwgVariantHolderT<double>::isInteger() const
{
    return std::numeric_limits<double>::is_integer;
}

bool DwgVariantHolderT<double>::isSigned() const
{
    return std::numeric_limits<double>::is_signed;
}

bool DwgVariantHolderT<double>::isNumeric() const
{
    return std::numeric_limits<double>::is_specialized;
}

bool DwgVariantHolderT<double>::isBoolean() const
{
    return false;
}

bool DwgVariantHolderT<double>::isString() const
{
    return false;
}

/* --------------------- DwgVariantHolderT<std::string> --------------------- */

DwgVariantHolderT<std::string>::DwgVariantHolderT(const char *pVal) : _val(pVal) {}

DwgVariantHolderT<std::string>::DwgVariantHolderT(const std::string &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<std::string>::type() const
{
    return typeid(std::string);
}

void DwgVariantHolderT<std::string>::convert(char &val) const
{
    const int v = StringHelp::parse(_val);
    convertToSmaller(v, val);
}

void DwgVariantHolderT<std::string>::convert(short &val) const
{
    const int v = StringHelp::parse(_val);
    convertToSmaller(v, val);
}

void DwgVariantHolderT<std::string>::convert(int &val) const
{
    val = StringHelp::parse(_val);
}

void DwgVariantHolderT<std::string>::convert(long long &val) const
{
    val = StringHelp::parse64(_val);
}

void DwgVariantHolderT<std::string>::convert(unsigned char &val) const
{
    const unsigned int v = StringHelp::parseUnsigned(_val);
    convertToSmallerUnsigned(v, val);
}

void DwgVariantHolderT<std::string>::convert(unsigned short &val) const
{
    const unsigned int v = StringHelp::parseUnsigned(_val);
    convertToSmallerUnsigned(v, val);
}

void DwgVariantHolderT<std::string>::convert(unsigned int &val) const
{
    val = StringHelp::parseUnsigned(_val);
}

void DwgVariantHolderT<std::string>::convert(unsigned long long &val) const
{
    val = StringHelp::parseUnsigned64(_val);
}

void DwgVariantHolderT<std::string>::convert(bool &val) const
{
    if (_val.empty())
    {
        val = false;
        return;
    }

    static const std::string VAL_FALSE("false");
    static const std::string VAL_INT_FALSE("0");
    val = (_val != VAL_INT_FALSE && (StringHelp::icompare(_val, VAL_FALSE) != 0));
}

void DwgVariantHolderT<std::string>::convert(float &val) const
{
    const double v = StringHelp::parseFloat(_val);
    convertToSmaller(v, val);
}

void DwgVariantHolderT<std::string>::convert(double &val) const
{
    val = StringHelp::parseFloat(_val);
}

void DwgVariantHolderT<std::string>::convert(std::string &val) const
{
    val = _val;
}

void DwgVariantHolderT<std::string>::convert(std::wstring &val) const
{
    val = Encoding::Utf8().toUnicode(_val);
}

void DwgVariantHolderT<std::string>::convert(DateTime &val) const
{
    int tzd = 0;
    if (!DateTime::FromString(DateTime::DateFormat::ISO8601, _val, val, tzd))
        throw std::runtime_error("string -> DateTime");
}

void DwgVariantHolderT<std::string>::convert(Timestamp &ts) const
{
    int tzd = 0;
    DateTime tmp;
    if (!DateTime::FromString(DateTime::DateFormat::ISO8601, _val, tmp, tzd))
        throw std::runtime_error("string -> Timestamp");

    ts = tmp.timestamp();
}

DwgVariantHolder *DwgVariantHolderT<std::string>::clone() const
{
    return new DwgVariantHolderT<std::string>(_val);
}

const std::string &DwgVariantHolderT<std::string>::value() const
{
    return _val;
}

bool DwgVariantHolderT<std::string>::isString() const
{
    return true;
}

std::size_t DwgVariantHolderT<std::string>::size() const
{
    return _val.length();
}

char &DwgVariantHolderT<std::string>::operator[](std::string::size_type n)
{
    if (n < size())
        return _val.operator[](n);

    throw std::out_of_range("String index out of range");
}

const char &DwgVariantHolderT<std::string>::operator[](std::string::size_type n) const
{
    if (n < size())
        return _val.operator[](n);

    throw std::out_of_range("String index out of range");
}

/* --------------------- DwgVariantHolderT<std::wstring> -------------------- */

DwgVariantHolderT<std::wstring>::DwgVariantHolderT(const char *pVal) : _val(Encoding::Utf8().toUnicode(pVal)) {}

DwgVariantHolderT<std::wstring>::DwgVariantHolderT(const std::wstring &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<std::wstring>::type() const
{
    return typeid(std::wstring);
}

void DwgVariantHolderT<std::wstring>::convert(char &val) const
{
    const int v = StringHelp::parse(toStdString());
    convertToSmaller(v, val);
}

void DwgVariantHolderT<std::wstring>::convert(short &val) const
{
    const int v = StringHelp::parse(toStdString());
    convertToSmaller(v, val);
}

void DwgVariantHolderT<std::wstring>::convert(int &val) const
{
    val = StringHelp::parse(toStdString());
}

void DwgVariantHolderT<std::wstring>::convert(long long &val) const
{
    val = StringHelp::parse64(toStdString());
}

void DwgVariantHolderT<std::wstring>::convert(unsigned char &val) const
{
    const unsigned int v = StringHelp::parseUnsigned(toStdString());
    convertToSmallerUnsigned(v, val);
}

void DwgVariantHolderT<std::wstring>::convert(unsigned short &val) const
{
    const unsigned int v = StringHelp::parseUnsigned(toStdString());
    convertToSmallerUnsigned(v, val);
}

void DwgVariantHolderT<std::wstring>::convert(unsigned int &val) const
{
    val = StringHelp::parseUnsigned(toStdString());
}

void DwgVariantHolderT<std::wstring>::convert(unsigned long long &val) const
{
    val = StringHelp::parseUnsigned64(toStdString());
}

void DwgVariantHolderT<std::wstring>::convert(bool &val) const
{
    static const std::string VAL_FALSE("false");
    static const std::string VAL_INT_FALSE("0");

    if (_val.empty())
        val = false;

    std::string str = Encoding::Utf8().fromUnicode(_val);
    val = (str != VAL_INT_FALSE && (StringHelp::icompare(str, VAL_FALSE) != 0));
}

void DwgVariantHolderT<std::wstring>::convert(float &val) const
{
    const double v = StringHelp::parseFloat(toStdString());
    convertToSmaller(v, val);
}

void DwgVariantHolderT<std::wstring>::convert(double &val) const
{
    val = StringHelp::parseFloat(toStdString());
}

void DwgVariantHolderT<std::wstring>::convert(std::wstring &val) const
{
    val = _val;
}

void DwgVariantHolderT<std::wstring>::convert(std::string &val) const
{
    val = Encoding::Utf8().fromUnicode(_val);
}

void DwgVariantHolderT<std::wstring>::convert(DateTime &val) const
{
    int tzd = 0;
    if (!DateTime::FromString(DateTime::DateFormat::ISO8601, toStdString(), val, tzd))
        throw std::runtime_error("string -> DateTime");
}

void DwgVariantHolderT<std::wstring>::convert(Timestamp &ts) const
{
    int tzd = 0;
    DateTime tmp;
    if (!DateTime::FromString(DateTime::DateFormat::ISO8601, toStdString(), tmp, tzd))
        throw std::runtime_error("string -> Timestamp");

    ts = tmp.timestamp();
}

DwgVariantHolder *DwgVariantHolderT<std::wstring>::clone() const
{
    return new DwgVariantHolderT<std::wstring>(_val);
}

const std::wstring &DwgVariantHolderT<std::wstring>::value() const
{
    return _val;
}

bool DwgVariantHolderT<std::wstring>::isString() const
{
    return true;
}

std::size_t DwgVariantHolderT<std::wstring>::size() const
{
    return _val.length();
}

wchar_t &DwgVariantHolderT<std::wstring>::operator[](std::wstring::size_type n)
{
    if (n < size())
        return _val.operator[](n);

    throw std::out_of_range("String index out of range");
}

const wchar_t &DwgVariantHolderT<std::wstring>::operator[](std::wstring::size_type n) const
{
    if (n < size())
        return _val.operator[](n);

    throw std::out_of_range("String index out of range");
}

std::string DwgVariantHolderT<std::wstring>::toStdString() const
{
    return Encoding::Utf8().fromUnicode(_val);
}

/* -------------- DwgVariantHolderT<std::vector<unsigned char>> ------------- */

DwgVariantHolderT<std::vector<unsigned char>>::DwgVariantHolderT(const std::vector<unsigned char> &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<std::vector<unsigned char>>::type() const
{
    return typeid(std::vector<unsigned char>);
}

void DwgVariantHolderT<std::vector<unsigned char>>::convert(std::string &val) const
{
    val = std::string(_val.begin(), _val.end());
}

DwgVariantHolder *DwgVariantHolderT<std::vector<unsigned char>>::clone() const
{
    return new DwgVariantHolderT<std::vector<unsigned char>>(_val);
}

const std::vector<unsigned char> &DwgVariantHolderT<std::vector<unsigned char>>::value() const
{
    return _val;
}

bool DwgVariantHolderT<std::vector<unsigned char>>::isBlob() const
{
    return true;
}

std::size_t DwgVariantHolderT<std::vector<unsigned char>>::size() const
{
    return _val.size();
}

unsigned char &
DwgVariantHolderT<std::vector<unsigned char>>::operator[](typename std::vector<unsigned char>::size_type n)
{
    if (n < size())
        return _val.operator[](n);

    throw std::out_of_range("List index out of range");
}

const unsigned char &
DwgVariantHolderT<std::vector<unsigned char>>::operator[](typename std::vector<unsigned char>::size_type n) const
{
    if (n < size())
        return _val.operator[](n);

    throw std::out_of_range("List index out of range");
}

/* ----------------------- DwgVariantHolderT<DateTime> ---------------------- */

DwgVariantHolderT<DateTime>::DwgVariantHolderT(const DateTime &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<DateTime>::type() const
{
    return typeid(DateTime);
}

void DwgVariantHolderT<DateTime>::convert(char &) const
{
    throw std::runtime_error("");
}

void DwgVariantHolderT<DateTime>::convert(short &) const
{
    throw std::runtime_error("");
}

void DwgVariantHolderT<DateTime>::convert(int &) const
{
    throw std::runtime_error("");
}

void DwgVariantHolderT<DateTime>::convert(long long &val) const
{
    val = _val.timestamp().epochMicroseconds();
}

void DwgVariantHolderT<DateTime>::convert(unsigned long long &val) const
{
    val = _val.timestamp().epochMicroseconds();
}

void DwgVariantHolderT<DateTime>::convert(std::string &val) const
{
    val = DateTime::ToString(_val, DateTime::DateFormat::ISO8601);
}

void DwgVariantHolderT<DateTime>::convert(DateTime &val) const
{
    val = _val;
}

void DwgVariantHolderT<DateTime>::convert(Timestamp &ts) const
{
    ts = _val.timestamp();
}

DwgVariantHolder *DwgVariantHolderT<DateTime>::clone() const
{
    return new DwgVariantHolderT<DateTime>(_val);
}

const DateTime &DwgVariantHolderT<DateTime>::value() const
{
    return _val;
}

bool DwgVariantHolderT<DateTime>::isDateTime() const
{
    return true;
}

/* ---------------------- DwgVariantHolderT<Timestamp> ---------------------- */

DwgVariantHolderT<Timestamp>::DwgVariantHolderT(const Timestamp &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<Timestamp>::type() const
{
    return typeid(Timestamp);
}

void DwgVariantHolderT<Timestamp>::convert(long long &val) const
{
    val = _val.epochMicroseconds();
}

void DwgVariantHolderT<Timestamp>::convert(unsigned long long &val) const
{
    val = _val.epochMicroseconds();
}

void DwgVariantHolderT<Timestamp>::convert(std::string &val) const
{
    val = DateTime::ToString(_val, DateTime::DateFormat::ISO8601);
}

void DwgVariantHolderT<Timestamp>::convert(DateTime &val) const
{
    val = _val;
}

void DwgVariantHolderT<Timestamp>::convert(Timestamp &ts) const
{
    ts = _val;
}

DwgVariantHolder *DwgVariantHolderT<Timestamp>::clone() const
{
    return new DwgVariantHolderT<Timestamp>(_val);
}

const Timestamp &DwgVariantHolderT<Timestamp>::value() const
{
    return _val;
}

bool DwgVariantHolderT<Timestamp>::isDateTime() const
{
    return true;
}

/* ------------------------ DwgVariantHolderT<Color> ------------------------ */

DwgVariantHolderT<Color>::DwgVariantHolderT(const Color &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<Color>::type() const
{
    return typeid(Color);
}

void DwgVariantHolderT<Color>::convert(char &val) const {}

void DwgVariantHolderT<Color>::convert(short &val) const {}

void DwgVariantHolderT<Color>::convert(int &val) const {}

void DwgVariantHolderT<Color>::convert(long long &val) const {}

void DwgVariantHolderT<Color>::convert(unsigned char &val) const {}

void DwgVariantHolderT<Color>::convert(unsigned short &val) const {}

void DwgVariantHolderT<Color>::convert(unsigned int &val) const {}

void DwgVariantHolderT<Color>::convert(unsigned long long &val) const {}

void DwgVariantHolderT<Color>::convert(bool &val) const {}

void DwgVariantHolderT<Color>::convert(float &val) const {}

void DwgVariantHolderT<Color>::convert(double &val) const {}

void DwgVariantHolderT<Color>::convert(std::string &val) const {}

void DwgVariantHolderT<Color>::convert(std::wstring &val) const {}

void DwgVariantHolderT<Color>::convert(DateTime &val) const {}

void DwgVariantHolderT<Color>::convert(Timestamp &ts) const {}

DwgVariantHolder *DwgVariantHolderT<Color>::clone() const
{
    return nullptr;
}

const Color &DwgVariantHolderT<Color>::value() const
{
    return _val;
}

bool DwgVariantHolderT<Color>::isColor() const
{
    return true;
}


/* -------------------------- DwgVariantHolderT<XY> ------------------------- */

DwgVariantHolderT<XY>::DwgVariantHolderT(const XY &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<XY>::type() const
{
    return typeid(XY);
}

void DwgVariantHolderT<XY>::convert(char &val) const {}

void DwgVariantHolderT<XY>::convert(short &val) const {}

void DwgVariantHolderT<XY>::convert(int &val) const {}

void DwgVariantHolderT<XY>::convert(long long &val) const {}

void DwgVariantHolderT<XY>::convert(unsigned char &val) const {}

void DwgVariantHolderT<XY>::convert(unsigned short &val) const {}

void DwgVariantHolderT<XY>::convert(unsigned int &val) const {}

void DwgVariantHolderT<XY>::convert(unsigned long long &val) const {}

void DwgVariantHolderT<XY>::convert(bool &val) const {}

void DwgVariantHolderT<XY>::convert(float &val) const {}

void DwgVariantHolderT<XY>::convert(double &val) const {}

void DwgVariantHolderT<XY>::convert(std::string &val) const {}

void DwgVariantHolderT<XY>::convert(std::wstring &val) const {}

void DwgVariantHolderT<XY>::convert(DateTime &val) const {}

void DwgVariantHolderT<XY>::convert(Timestamp &ts) const {}

DwgVariantHolder *DwgVariantHolderT<XY>::clone() const
{
    return nullptr;
}

const XY &DwgVariantHolderT<XY>::value() const
{
    return _val;
}

bool DwgVariantHolderT<XY>::isCoordinate() const
{
    return true;
}


/* ------------------------- DwgVariantHolderT<XYZ> ------------------------- */

DwgVariantHolderT<XYZ>::DwgVariantHolderT(const XYZ &val) : _val(val) {}

const std::type_info &DwgVariantHolderT<XYZ>::type() const
{
    return typeid(XYZ);
}

void DwgVariantHolderT<XYZ>::convert(char &val) const {}

void DwgVariantHolderT<XYZ>::convert(short &val) const {}

void DwgVariantHolderT<XYZ>::convert(int &val) const {}

void DwgVariantHolderT<XYZ>::convert(long long &val) const {}

void DwgVariantHolderT<XYZ>::convert(unsigned char &val) const {}

void DwgVariantHolderT<XYZ>::convert(unsigned short &val) const {}

void DwgVariantHolderT<XYZ>::convert(unsigned int &val) const {}

void DwgVariantHolderT<XYZ>::convert(unsigned long long &val) const {}

void DwgVariantHolderT<XYZ>::convert(bool &val) const {}

void DwgVariantHolderT<XYZ>::convert(float &val) const {}

void DwgVariantHolderT<XYZ>::convert(double &val) const {}

void DwgVariantHolderT<XYZ>::convert(std::string &val) const {}

void DwgVariantHolderT<XYZ>::convert(std::wstring &val) const {}

void DwgVariantHolderT<XYZ>::convert(DateTime &val) const {}

void DwgVariantHolderT<XYZ>::convert(Timestamp &ts) const {}

DwgVariantHolder *DwgVariantHolderT<XYZ>::clone() const
{
    return nullptr;
}

const XYZ &DwgVariantHolderT<XYZ>::value() const
{
    return _val;
}

bool DwgVariantHolderT<XYZ>::isCoordinate() const
{
    return true;
}

}// namespace dwg
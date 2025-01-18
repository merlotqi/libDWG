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

#include <cpl_ports.h>
#include <dwg/ACadVersion.h>
#include <dwg/LineWeightType.h>
#include <dwg/exports.h>
#include <map>

#include <vector>

namespace dwg {

class LIBDWG_API CadUtils
{
    static std::map<CPL::String, CPL::CodePageID> _dxfEncodingMap;
    static std::vector<LineweightType> _indexedValue;
    static std::vector<CPL::CodePageID> CadUtils::_pageCodes;

public:
    static LineweightType ToValue(unsigned char b);

    static unsigned char ToIndex(LineweightType value);

    static CPL::CodePageID GetCodePage(CPL::String &value);

    static CPL::String GetCodePageName(CPL::CodePageID value);

    static CPL::CodePageID GetCodePage(int value);

    static int GetCodeIndex(CPL::CodePageID code);

    static ACadVersion GetVersionFromName(const CPL::String &name);

    static CPL::String GetNameFromVersion(ACadVersion version);

    static double ToJulianCalendar(CPL::DateTime date);

    static CPL::DateTime FromJulianCalendar(double date);

    static CPL::Timespan EditingTime(double elapsed);

    static void DateToJulian(CPL::DateTime date, int &jdate, int &miliseconds);
};

}// namespace dwg

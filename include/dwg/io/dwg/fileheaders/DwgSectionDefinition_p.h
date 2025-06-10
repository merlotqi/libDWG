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

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace dwg {

class DwgSectionDefinition
{
public:
    static constexpr auto AcDbObjects = "AcDb:AcDbObjects";
    static constexpr auto AppInfo = "AcDb:AppInfo";
    static constexpr auto AuxHeader = "AcDb:AuxHeader";
    static constexpr auto Header = "AcDb:Header";
    static constexpr auto Classes = "AcDb:Classes";
    static constexpr auto Handles = "AcDb:Handles";
    static constexpr auto ObjFreeSpace = "AcDb:ObjFreeSpace";
    static constexpr auto Template = "AcDb:Template";
    static constexpr auto SummaryInfo = "AcDb:SummaryInfo";
    static constexpr auto FileDepList = "AcDb:FileDepList";
    static constexpr auto Preview = "AcDb:Preview";
    static constexpr auto RevHistory = "AcDb:RevHistory";

    static std::map<std::string, std::vector<unsigned char>> StartSentinels;
    static std::map<std::string, std::vector<unsigned char>> EndSentinels;

    /**
     * @brief Get the Section Locator By Name object
     * 
     * @param name 
     * @return std::tuple<int, bool> int is the section index, bool is true if the section is optional
     */
    static std::tuple<int, bool> GetSectionLocatorByName(const std::string &name);
};

}// namespace dwg
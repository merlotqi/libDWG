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
#include <string>
#include <vector>

namespace dwg {

class HatchPattern
{
public:
    struct Line
    {
        double Angle;                    /**< The angle of the hatch line. */
        XY BasePoint;                    /**< The base point of the hatch line. */
        XY Offset;                       /**< The offset between consecutive hatch lines. */
        std::vector<double> DashLengths; /**< The dash lengths for the hatch line. */
    };

public:
    HatchPattern();
    HatchPattern(const std::string &name);
    ~HatchPattern();

    static HatchPattern Solid();
    static std::vector<HatchPattern> LoadFrom(const std::string &filepath);
    static void SavePatterns(const std::string &filepath, const std::vector<HatchPattern> &patterns);

    std::string name() const;
    void setName(const std::string &name);

    std::string description() const;
    void setDescription(const std::string &description);

    std::vector<HatchPattern::Line> lines() const;
    void setLines(const std::vector<HatchPattern::Line> &lines);

private:
    std::string _name;
    std::string _description;
    std::vector<HatchPattern::Line> _lines;
};

}// namespace dwg

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
#include <dwg/Coordinate.h>
#include <vector>

namespace dwg {

/**
 * @class DG_HatchPattern
 * @brief Represents a hatch pattern used in DWG/DXF drawings.
 *
 * A hatch pattern consists of multiple lines, each defined by an angle, 
 * base point, offset, and dash lengths.
 */
class DG_HatchPattern
{
public:
    /**
     * @struct Line
     * @brief Represents a single line in a hatch pattern.
     *
     * A hatch pattern is made up of multiple lines, each with an angle,
     * base point, offset, and an optional dash pattern.
     */
    struct Line
    {
        double Angle;                    /**< The angle of the hatch line. */
        XY BasePoint;                    /**< The base point of the hatch line. */
        XY Offset;                       /**< The offset between consecutive hatch lines. */
        std::vector<double> DashLengths; /**< The dash lengths for the hatch line. */
    };

public:
    /**
     * @brief Constructs an empty hatch pattern.
     */
    DG_HatchPattern();

    /**
     * @brief Constructs a hatch pattern with a specified name.
     * @param name The name of the hatch pattern.
     */
    DG_HatchPattern(const std::string &name);

    /**
     * @brief Destroys the hatch pattern instance.
     */
    ~DG_HatchPattern();

    /**
     * @brief Returns a solid fill hatch pattern.
     * @return A pointer to a solid fill hatch pattern.
     */
    static DG_HatchPattern *Solid();

    /**
     * @brief Gets the name of the hatch pattern.
     * @return The name of the hatch pattern.
     */
    std::string Name() const;

    /**
     * @brief Sets the name of the hatch pattern.
     * @param name The name to set.
     */
    void Name(const std::string &name);

    /**
     * @brief Gets the description of the hatch pattern.
     * @return The description of the hatch pattern.
     */
    std::string Description() const;

    /**
     * @brief Sets the description of the hatch pattern.
     * @param description The description to set.
     */
    void Description(const std::string &description);

    /**
     * @brief Gets the list of hatch pattern lines.
     * @return A vector containing the hatch pattern lines.
     */
    std::vector<DG_HatchPattern::Line> Lines() const;

    /**
     * @brief Sets the lines of the hatch pattern.
     * @param lines A vector of hatch pattern lines.
     */
    void Lines(const std::vector<DG_HatchPattern::Line> &lines);
};

}// namespace dwg

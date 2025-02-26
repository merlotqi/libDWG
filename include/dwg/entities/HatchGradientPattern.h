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

#include <dwg/entities/GradientColor.h>
#include <dwg/exports.h>
#include <string>
#include <vector>

namespace dwg {

/**
 * @class HatchGradientPattern
 * @brief Represents a gradient pattern used in hatches for DWG/DXF drawings.
 *
 * This class defines a gradient pattern that can be applied to hatches.
 * It supports multiple colors, angle adjustments, and color tinting.
 */
class LIBDWG_API HatchGradientPattern
{
public:
    /**
     * @brief Constructs a default gradient pattern.
     */
    HatchGradientPattern();

    /**
     * @brief Constructs a gradient pattern with a given name.
     * @param name The name of the gradient pattern.
     */
    HatchGradientPattern(const std::string &name);

    /**
     * @brief Destroys the gradient pattern instance.
     */
    ~HatchGradientPattern();

    /**
     * @brief Checks if the gradient pattern is enabled.
     * @return True if enabled, false otherwise.
     */
    bool enabled() const;

    /**
     * @brief Enables or disables the gradient pattern.
     * @param enabled Set to true to enable, false to disable.
     */
    void setEnabled(bool enabled);

    /**
     * @brief Gets the reserved integer value.
     * @return The reserved integer value.
     */
    int reserved() const;

    /**
     * @brief Sets the reserved integer value.
     * @param reserved The reserved integer value.
     */
    void setReserved(int reserved);

    /**
     * @brief Gets the angle of the gradient pattern.
     * @return The angle in degrees.
     */
    double angle() const;

    /**
     * @brief Sets the angle of the gradient pattern.
     * @param angle The angle in degrees.
     */
    void setAngle(double angle);

    /**
     * @brief Gets the shift value of the gradient pattern.
     * @return The shift value.
     */
    double shift() const;

    /**
     * @brief Sets the shift value of the gradient pattern.
     * @param shift The shift value.
     */
    void setShift(double shift);

    /**
     * @brief Checks if the gradient is a single-color gradient.
     * @return True if it is a single-color gradient, false otherwise.
     */
    bool isSingleColorGradient() const;

    /**
     * @brief Sets whether the gradient should be a single-color gradient.
     * @param singleColor Set to true for single-color gradient.
     */
    void setIsSingleColorGradient(bool singleColor);

    /**
     * @brief Gets the color tint factor of the gradient.
     * @return The color tint factor.
     */
    double colorTint() const;

    /**
     * @brief Sets the color tint factor of the gradient.
     * @param tint The color tint factor.
     */
    void setColorTint(double tint);

    /**
     * @brief Gets the list of gradient colors.
     * @return A reference to the vector of gradient colors.
     */
    const std::vector<GradientColor> &colors() const;

    /**
     * @brief Sets the gradient colors.
     * @param colors A vector of gradient colors.
     */
    void setColors(const std::vector<GradientColor> &colors);

    /**
     * @brief Gets the name of the gradient pattern.
     * @return The name of the gradient pattern.
     */
    std::string name() const;

    /**
     * @brief Sets the name of the gradient pattern.
     * @param name The name of the gradient pattern.
     */
    void setName(const std::string &name);

private:
    bool _enabled;
    int _reserved;
    double _angle;
    double _shift;
    bool _singleColorGradient;
    double _colorTint;
    std::vector<GradientColor> _colors;
    std::string _name;
};

}// namespace dwg

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
#include <vector>

namespace dwg {

/**
 * @class DG_HatchGradientPattern
 * @brief Represents a gradient pattern used in hatches for DWG/DXF drawings.
 *
 * This class defines a gradient pattern that can be applied to hatches.
 * It supports multiple colors, angle adjustments, and color tinting.
 */
class LIBDWG_API DG_HatchGradientPattern
{
public:
    /**
     * @brief Constructs a default gradient pattern.
     */
    DG_HatchGradientPattern();

    /**
     * @brief Constructs a gradient pattern with a given name.
     * @param name The name of the gradient pattern.
     */
    DG_HatchGradientPattern(const std::string &name);

    /**
     * @brief Destroys the gradient pattern instance.
     */
    ~DG_HatchGradientPattern();

    /**
     * @brief Checks if the gradient pattern is enabled.
     * @return True if enabled, false otherwise.
     */
    bool Enabled() const;

    /**
     * @brief Enables or disables the gradient pattern.
     * @param enabled Set to true to enable, false to disable.
     */
    void Enabled(bool enabled);

    /**
     * @brief Gets the reserved integer value.
     * @return The reserved integer value.
     */
    int Reserved() const;

    /**
     * @brief Sets the reserved integer value.
     * @param reserved The reserved integer value.
     */
    void Reserved(int reserved);

    /**
     * @brief Gets the angle of the gradient pattern.
     * @return The angle in degrees.
     */
    double Angle() const;

    /**
     * @brief Sets the angle of the gradient pattern.
     * @param angle The angle in degrees.
     */
    void Angle(double angle);

    /**
     * @brief Gets the shift value of the gradient pattern.
     * @return The shift value.
     */
    double Shift() const;

    /**
     * @brief Sets the shift value of the gradient pattern.
     * @param shift The shift value.
     */
    void Shift(double shift);

    /**
     * @brief Checks if the gradient is a single-color gradient.
     * @return True if it is a single-color gradient, false otherwise.
     */
    bool IsSingleColorGradient() const;

    /**
     * @brief Sets whether the gradient should be a single-color gradient.
     * @param singleColor Set to true for single-color gradient.
     */
    void IsSingleColorGradient(bool singleColor);

    /**
     * @brief Gets the color tint factor of the gradient.
     * @return The color tint factor.
     */
    double ColorTint() const;

    /**
     * @brief Sets the color tint factor of the gradient.
     * @param tint The color tint factor.
     */
    void ColorTint(double tint);

    /**
     * @brief Gets the list of gradient colors.
     * @return A reference to the vector of gradient colors.
     */
    const std::vector<GradientColor> &Colors() const;

    /**
     * @brief Sets the gradient colors.
     * @param colors A vector of gradient colors.
     */
    void Colors(const std::vector<GradientColor> &colors);

    /**
     * @brief Gets the name of the gradient pattern.
     * @return The name of the gradient pattern.
     */
    std::string Name() const;

    /**
     * @brief Sets the name of the gradient pattern.
     * @param name The name of the gradient pattern.
     */
    void Name(const std::string &name);
};

}// namespace dwg

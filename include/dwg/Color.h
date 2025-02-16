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
#include <vector>

namespace dwg {

/**
 * @class Color
 * @brief Represents a color in the DWG/DXF format, supporting indexed and true colors.
 */
class LIBDWG_API Color
{
    /**
     * @brief Lookup table for indexed RGB colors.
     */
    static const std::vector<std::vector<unsigned char>> _indexRgb[][3];

    /**
     * @brief Maximum value for true color representation.
     */
    const int _maxTrueColor = 0b0001'0000'0000'0000'0000'0000'0000;

    /**
     * @brief Flag indicating a true color value.
     */
    const int _trueColorFlag = 0b0100'0000'0000'0000'0000'0000'0000'0000;

    /**
     * @brief Stores the color value, either as an index or true color.
     */
    unsigned int _color;

    /**
     * @brief Converts a byte array to a 24-bit integer.
     * @param array The input byte array containing RGB values.
     * @return The integer representation of the color.
     */
    static unsigned int getInt24(const std::vector<unsigned char> &array);

    /**
     * @brief Retrieves the RGB values of the color.
     * @return A vector containing R, G, and B values.
     */
    std::vector<unsigned char> getRgb() const;

    /**
     * @brief Constructs a Color instance from a true color value.
     * @param trueColor The 24-bit true color value.
     */
    Color(unsigned int trueColor);

public:
    Color(const Color &rhs);
    Color &operator=(const Color &rhs);

    /**
     * @brief Constructs a Color from an indexed color.
     * @param index The color index.
     */
    Color(short index);

    /**
     * @brief Constructs a Color from RGB values.
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     */
    Color(unsigned char r, unsigned char g, unsigned char b);

    /**
     * @brief Constructs a Color from an RGB vector.
     * @param rgb A vector containing R, G, and B values.
     */
    Color(const std::vector<unsigned char> &rgb);

    /**
     * @brief Predefined color representing ByLayer.
     */
    static Color ByLayer;

    /**
     * @brief Predefined color representing ByBlock.
     */
    static Color ByBlock;

    /**
     * @brief Predefined color representing ByEntity.
     */
    static Color ByEntity;

    /**
     * @brief Creates a Color from a true color integer value.
     * @param color The 24-bit true color value.
     * @return A Color instance representing the true color.
     */
    static Color fromTrueColor(unsigned int color);

    /**
     * @brief Approximates the closest indexed color for given RGB values.
     * @param r Red component.
     * @param g Green component.
     * @param b Blue component.
     * @return The closest indexed color.
     */
    static unsigned char approxIndex(unsigned char r, unsigned char g, unsigned char b);

    /**
     * @brief Checks if the color is ByLayer.
     * @return True if the color is ByLayer, otherwise false.
     */
    bool isByLayer() const;

    /**
     * @brief Checks if the color is ByBlock.
     * @return True if the color is ByBlock, otherwise false.
     */
    bool isByBlock() const;

    /**
     * @brief Retrieves the indexed color value.
     * @return The color index.
     */
    short index() const;

    /**
     * @brief Retrieves the true color value.
     * @return The 24-bit true color value.
     */
    int trueColor() const;

    /**
     * @brief Checks if the color is a true color.
     * @return True if it is a true color, otherwise false.
     */
    bool isTrueColor() const;

    /**
     * @brief Retrieves the red component of the color.
     * @return The red component.
     */
    unsigned char red() const;

    /**
     * @brief Retrieves the green component of the color.
     * @return The green component.
     */
    unsigned char green() const;

    /**
     * @brief Retrieves the blue component of the color.
     * @return The blue component.
     */
    unsigned char blue() const;

    /**
     * @brief Gets the approximate indexed color.
     * @return The closest indexed color.
     */
    unsigned char approxIndex() const;

    /**
     * @brief Equality operator for Color.
     * @param lhs Left-hand side color.
     * @param rhs Right-hand side color.
     * @return True if both colors are equal, otherwise false.
     */
    friend bool operator==(const Color &lhs, const Color &rhs);

    /**
     * @brief Inequality operator for Color.
     * @param lhs Left-hand side color.
     * @param rhs Right-hand side color.
     * @return True if the colors are different, otherwise false.
     */
    friend bool operator!=(const Color &lhs, const Color &rhs);
};

bool operator==(const Color &lhs, const Color &rhs) { return lhs._color == rhs._color; }

bool operator!=(const Color &lhs, const Color &rhs) { return !(lhs == rhs); }

}// namespace dwg
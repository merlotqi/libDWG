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

namespace dwg {

/**
 * @class DG_Transparency
 * @brief Represents the transparency properties of an object in LIBDWG.
 */
class LIBDWG_API DG_Transparency
{
    /**
     * @brief Stores the transparency value.
     */
    short _value;

public:
    /**
     * @brief Constructs a DG_Transparency object with a given transparency value.
     * @param value The transparency value.
     */
    DG_Transparency(short value);

    /**
     * @brief Checks if the transparency is set to "ByLayer".
     * @return True if transparency is "ByLayer", otherwise false.
     */
    bool IsByLayer() const;

    /**
     * @brief Checks if the transparency is set to "ByBlock".
     * @return True if transparency is "ByBlock", otherwise false.
     */
    bool IsByBlock() const;

    /**
     * @brief Retrieves the transparency value.
     * @return The transparency value.
     */
    short Value() const;

    /**
     * @brief Sets the transparency value.
     * @param value The new transparency value.
     */
    void Value(short value);

    /**
     * @brief Converts a DG_Transparency object to an alpha value.
     * @param transparency The DG_Transparency object.
     * @return The corresponding alpha value as an integer.
     */
    static int ToAlphaValue(DG_Transparency transparency);

    /**
     * @brief Creates a DG_Transparency object from an alpha value.
     * @param value The alpha value.
     * @return A DG_Transparency object representing the given alpha value.
     */
    static DG_Transparency FromAlphaValue(int value);

    /**
     * @brief Predefined DG_Transparency object representing "ByLayer" transparency.
     */
    static DG_Transparency ByLayer;

    /**
     * @brief Predefined DG_Transparency object representing "ByBlock" transparency.
     */
    static DG_Transparency ByBlock;

    /**
     * @brief Predefined DG_Transparency object representing fully opaque transparency.
     */
    static DG_Transparency Opaque;
};

}// namespace dwg

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

// The DG_Transparency struct represents the transparency properties of an object in LIBDWG.
// It provides methods to manage and convert transparency values.
struct LIBDWG_API DG_Transparency
{
    // Member variable to store the transparency value.
    short Value;

    // Constructor to initialize the transparency with a given value.
    DG_Transparency(short value);

    // Checks if the transparency is set to "ByLayer".
    bool IsByLayer() const;

    // Checks if the transparency is set to "ByBlock".
    bool IsByBlock() const;

    // Getter method to retrieve the transparency value.
    short Value() const;

    // Setter method to update the transparency value.
    void Value(short value);

    // Converts a DG_Transparency object to an alpha value (integer).
    static int ToAlphaValue(DG_Transparency transparency);

    // Creates a DG_Transparency object from an alpha value (integer).
    static DG_Transparency FromAlphaValue(int value);

    // Predefined DG_Transparency object representing "ByLayer" transparency.
    static DG_Transparency ByLayer;

    // Predefined DG_Transparency object representing "ByBlock" transparency.
    static DG_Transparency ByBlock;

    // Predefined DG_Transparency object representing fully opaque transparency.
    static DG_Transparency Opaque;
};

}// namespace dwg

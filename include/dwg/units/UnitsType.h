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

namespace dwg {

enum class UnitsType : short
{
    /// Unitless.
    Unitless = 0,
    /// Inches
    Inches = 1,
    /// Feet
    Feet = 2,
    /// Miles
    Miles = 3,
    /// Millimeters
    Millimeters = 4,
    /// Centimeters
    Centimeters = 5,
    /// Meters
    Meters = 6,
    /// Kilometers
    Kilometers = 7,
    /// Microinches
    Microinches = 8,
    /// Mils
    Mils = 9,
    /// Yards
    Yards = 10,
    /// Angstroms
    Angstroms = 11,
    /// Nanometers
    Nanometers = 12,
    /// Microns
    Microns = 13,
    /// Decimeters
    Decimeters = 14,
    /// Decameters
    Decameters = 15,
    /// Hectometers
    Hectometers = 16,
    /// Gigameters
    Gigameters = 17,
    /// Astronomical units
    AstronomicalUnits = 18,
    /// Light years
    LightYears = 19,
    /// Parsecs
    Parsecs = 20,
    /// US Survey Feet
    USSurveyFeet = 21,
    /// US Survey Inches
    USSurveyInches = 22,
    /// US Survey Yards
    USSurveyYards = 23,
    /// US Survey Miles
    USSurveyMiles = 24
};

}// namespace dwg
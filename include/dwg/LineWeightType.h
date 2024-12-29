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

enum LineweightType : short
{
    ByDIPs = -4,

    /// Default line weight.
    Default = -3,

    /// Line weight defined by block.
    ByBlock = -2,

    /// Line weight defined by layer.
    ByLayer = -1,

    /// Line weight value 0.00 mm (hairline).
    W0 = 0,

    /// Line weight value 0.05 mm.
    W5 = 5,

    /// Line weight value 0.09 mm.
    W9 = 9,
    /// Line weight value 0.13 mm.
    W13 = 13,
    /// Line weight value 0.15 mm.
    W15 = 15,
    /// Line weight value 0.18 mm.
    W18 = 18,
    /// Line weight value 0.20 mm.
    W20 = 20,
    /// Line weight value 0.25 mm.
    W25 = 25,
    /// Line weight value 0.30 mm.
    W30 = 30,
    /// Line weight value 0.35 mm.
    W35 = 35,
    /// Line weight value 0.40 mm.
    W40 = 40,
    /// Line weight value 0.50 mm.
    W50 = 50,
    /// Line weight value 0.53 mm.
    W53 = 53,
    /// Line weight value 0.60 mm.
    W60 = 60,
    /// Line weight value 0.70 mm.
    W70 = 70,
    /// Line weight value 0.80 mm.
    W80 = 80,
    /// Line weight value 0.90 mm.
    W90 = 90,
    /// Line weight value 1.00 mm.
    W100 = 100,
    /// Line weight value 1.06 mm.
    W106 = 106,
    /// Line weight value 1.20 mm.
    W120 = 120,
    /// Line weight value 1.40 mm.
    W140 = 140,
    /// Line weight value 1.58 mm.
    W158 = 158,
    /// Line weight value 2.00 mm.
    W200 = 200,
    /// Line weight value 2.11 mm.
    W211 = 211
};

}// namespace dwg

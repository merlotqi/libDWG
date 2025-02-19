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

enum class GroupCodeValueType
{
    None,

    /// \brief String
    /// \remarks Code range : 0-9
    String,

    /// \brief Double precision 3D point value
    /// \remarks Code range : 10-39
    Point3D,

    /// \brief Double-precision floating-point value
    /// \remarks Code range : 40-59 | 110-119 | 120-129 | 130-139 | 210-239
    Double,
    Byte,
    Int16,
    Int32,
    Int64,

    /// \brief String representing hexadecimal (hex) handle value
    /// \remarks Code range : 105
    Handle,
    ObjectId,
    Bool,
    Chunk,

    /// \brief Comment (string)
    /// \remarks Code range : 999
    Comment,

    ExtendedDataString,
    ExtendedDataChunk,
    ExtendedDataHandle,
    ExtendedDataDouble,
    ExtendedDataInt16,
    ExtendedDataInt32,
};

}// namespace dwg

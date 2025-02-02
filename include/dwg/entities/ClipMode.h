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

/**
 * @enum DG_ClipMode
 * @brief Defines the clipping modes for clipping operations in a DWG/DXF drawing.
 *
 * This enum specifies the two modes of clipping: Outside and Inside. It determines
 * how the clipping operation is applied to an object, either keeping the content 
 * outside the clipping boundary or only the content inside the boundary.
 */
enum DG_ClipMode : unsigned char
{
    Outside,///< Content outside the clipping boundary is kept.
    Inside, ///< Content inside the clipping boundary is kept.
};

}// namespace dwg
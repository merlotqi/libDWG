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
 * @enum DG_AttachmentPointType
 * @brief Defines the attachment points for multiline text in a DWG/DXF drawing.
 *
 * The attachment points determine where the text is positioned relative to its insertion point.
 * These points are used to control the alignment of text in both horizontal and vertical directions.
 */
enum DG_AttachmentPointType : short
{
    /// Top left.
    TopLeft = 1,
    /// Top center.
    TopCenter = 2,
    /// Top right.
    TopRight = 3,
    /// Middle left.
    MiddleLeft = 4,
    /// Middle center.
    MiddleCenter = 5,
    /// Middle right.
    MiddleRight = 6,
    /// Bottom left.
    BottomLeft = 7,
    /// Bottom center.
    BottomCenter = 8,
    /// Bottom right.
    BottomRight = 9,
};

}// namespace dwg
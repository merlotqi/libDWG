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

/// Enumeration for text attachment types.
enum TextAttachmentType : short
{
    /// Top of top text line.
    TopOfTopLine = 0,

    /// Middle of top text line.
    MiddleOfTopLine = 1,

    /// Middle of text.
    MiddleOfText = 2,

    /// Middle of bottom text line.
    MiddleOfBottomLine = 3,

    /// Bottom of bottom text line.
    BottomOfBottomLine = 4,

    /// Bottom text line.
    BottomLine = 5,

    /// Bottom of top text line. Underline bottom line.
    BottomOfTopLineUnderlineBottomLine = 6,

    /// Bottom of top text line. Underline top line.
    BottomOfTopLineUnderlineTopLine = 7,

    /// Bottom of top text line. Underline all content.
    BottomofTopLineUnderlineAll = 8,

    /// Center of text (y-coordinate only).
    CenterOfText = 9,

    /// Center of text (y-coordinate only), and overline top/underline
    /// bottom content.
    CenterOfTextOverline = 10,
};

}// namespace dwg
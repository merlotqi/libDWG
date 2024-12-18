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

class LIBDWG_API Color
{
    static const unsigned char indexRgb[][3];

    const int m_maxTrueColor = 0b0001'0000'0000'0000'0000'0000'0000;
    const int m_trueColorFlag = 0b0100'0000'0000'0000'0000'0000'0000'0000;

    unsigned int m_color;

    Color(unsigned int trueColor);

public:
    Color();
    Color(short index);
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(const std::vector<unsigned char> rgb);

    static Color ByLayer();
    static Color ByBlock();
    static Color ByEntity();
    static Color FromTrueColor(unsigned int color);
    static unsigned char ApproxIndex(unsigned char r, unsigned char g,
                                     unsigned char b);

    bool IsByLayer() const;
    bool IsByBlock() const;
    short Index() const;
    int TrueColor() const;
    bool IsTrueColor() const;
    unsigned char R() const;
    unsigned char G() const;
    unsigned char B() const;
    unsigned char GetApproxIndex() const;

    friend bool operator==(const Color &lhs, const Color &rhs);
    friend bool operator!=(const Color &lhs, const Color &rhs);
};

}// namespace dwg
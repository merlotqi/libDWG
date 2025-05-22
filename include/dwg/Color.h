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
    static const std::vector<std::vector<unsigned char>> _indexRgb;
    const int _maxTrueColor = 0b0001'0000'0000'0000'0000'0000'0000;
    const int _trueColorFlag = 0b0100'0000'0000'0000'0000'0000'0000'0000;
    unsigned int _color;
    static unsigned int getInt24(const std::vector<unsigned char> &array);

    std::vector<unsigned char> getRgb() const;
    Color(unsigned int trueColor);

public:
    Color();
    Color(short index);
    Color(unsigned char r, unsigned char g, unsigned char b);
    Color(const std::vector<unsigned char> &rgb);
    
    Color(const Color &rhs);
    Color &operator=(const Color &rhs);

    static Color ByLayer;
    static Color ByBlock;
    static Color ByEntity;

    static Color fromTrueColor(unsigned int color);
    static unsigned char approxIndex(unsigned char r, unsigned char g, unsigned char b);

    bool isByLayer() const;
    bool isByBlock() const;
    short index() const;
    int trueColor() const;
    bool isTrueColor() const;

    unsigned char red() const;
    unsigned char green() const;
    unsigned char blue() const;

    unsigned char approxIndex() const;

    friend bool operator==(const Color &lhs, const Color &rhs);
    friend bool operator!=(const Color &lhs, const Color &rhs);
};

inline bool operator==(const Color &lhs, const Color &rhs)
{
    return lhs._color == rhs._color;
}

inline bool operator!=(const Color &lhs, const Color &rhs)
{
    return !(lhs == rhs);
}

}// namespace dwg
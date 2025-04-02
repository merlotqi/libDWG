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

#include <dwg/Color.h>
#include <dwg/utils/EndianConverter.h>
#include <stdexcept>

namespace dwg {

const std::vector<std::vector<unsigned char>> Color::_indexRgb = {
        {  0,   0,   0}, //Dummy entry
        {255,   0,   0},
        {255, 255,   0},
        {  0, 255,   0},
        {  0, 255, 255},
        {  0,   0, 255},
        {255,   0, 255},
        {255, 255, 255},
        {128, 128, 128},
        {192, 192, 192},
        {255,   0,   0},
        {255, 127, 127},
        {165,   0,   0},
        {165,  82,  82},
        {127,   0,   0},
        {127,  63,  63},
        { 76,   0,   0},
        { 76,  38,  38},
        { 38,   0,   0},
        { 38,  19,  19},
        {255,  63,   0},
        {255, 159, 127},
        {165,  41,   0},
        {165, 103,  82},
        {127,  31,   0},
        {127,  79,  63},
        { 76,  19,   0},
        { 76,  47,  38},
        { 38,   9,   0},
        { 38,  28,  19},
        {255, 127,   0},
        {255, 191, 127},
        {165,  82,   0},
        {165, 124,  82},
        {127,  63,   0},
        {127,  95,  63},
        { 76,  38,   0},
        { 76,  57,  38},
        { 38,  19,   0},
        { 38,  28,  19},
        {255, 191,   0},
        {255, 223, 127},
        {165, 124,   0},
        {165, 145,  82},
        {127,  95,   0},
        {127, 111,  63},
        { 76,  57,   0},
        { 76,  66,  38},
        { 38,  28,   0},
        { 38,  33,  19},
        {255, 255,   0},
        {255, 255, 127},
        {165, 165,   0},
        {165, 165,  82},
        {127, 127,   0},
        {127, 127,  63},
        { 76,  76,   0},
        { 76,  76,  38},
        { 38,  38,   0},
        { 38,  38,  19},
        {191, 255,   0},
        {223, 255, 127},
        {124, 165,   0},
        {145, 165,  82},
        { 95, 127,   0},
        {111, 127,  63},
        { 57,  76,   0},
        { 66,  76,  38},
        { 28,  38,   0},
        { 33,  38,  19},
        {127, 255,   0},
        {191, 255, 127},
        { 82, 165,   0},
        {124, 165,  82},
        { 63, 127,   0},
        { 95, 127,  63},
        { 38,  76,   0},
        { 57,  76,  38},
        { 19,  38,   0},
        { 28,  38,  19},
        { 63, 255,   0},
        {159, 255, 127},
        { 41, 165,   0},
        {103, 165,  82},
        { 31, 127,   0},
        { 79, 127,  63},
        { 19,  76,   0},
        { 47,  76,  38},
        {  9,  38,   0},
        { 23,  38,  19},
        {  0, 255,   0},
        {125, 255, 127},
        {  0, 165,   0},
        { 82, 165,  82},
        {  0, 127,   0},
        { 63, 127,  63},
        {  0,  76,   0},
        { 38,  76,  38},
        {  0,  38,   0},
        { 19,  38,  19},
        {  0, 255,  63},
        {127, 255, 159},
        {  0, 165,  41},
        { 82, 165, 103},
        {  0, 127,  31},
        { 63, 127,  79},
        {  0,  76,  19},
        { 38,  76,  47},
        {  0,  38,   9},
        { 19,  88,  23},
        {  0, 255, 127},
        {127, 255, 191},
        {  0, 165,  82},
        { 82, 165, 124},
        {  0, 127,  63},
        { 63, 127,  95},
        {  0,  76,  38},
        { 38,  76,  57},
        {  0,  38,  19},
        { 19,  88,  28},
        {  0, 255, 191},
        {127, 255, 223},
        {  0, 165, 124},
        { 82, 165, 145},
        {  0, 127,  95},
        { 63, 127, 111},
        {  0,  76,  57},
        { 38,  76,  66},
        {  0,  38,  28},
        { 19,  88,  88},
        {  0, 255, 255},
        {127, 255, 255},
        {  0, 165, 165},
        { 82, 165, 165},
        {  0, 127, 127},
        { 63, 127, 127},
        {  0,  76,  76},
        { 38,  76,  76},
        {  0,  38,  38},
        { 19,  88,  88},
        {  0, 191, 255},
        {127, 223, 255},
        {  0, 124, 165},
        { 82, 145, 165},
        {  0,  95, 127},
        { 63, 111, 217},
        {  0,  57,  76},
        { 38,  66, 126},
        {  0,  28,  38},
        { 19,  88,  88},
        {  0, 127, 255},
        {127, 191, 255},
        {  0,  82, 165},
        { 82, 124, 165},
        {  0,  63, 127},
        { 63,  95, 127},
        {  0,  38,  76},
        { 38,  57, 126},
        {  0,  19,  38},
        { 19,  28,  88},
        {  0,  63, 255},
        {127, 159, 255},
        {  0,  41, 165},
        { 82, 103, 165},
        {  0,  31, 127},
        { 63,  79, 127},
        {  0,  19,  76},
        { 38,  47, 126},
        {  0,   9,  38},
        { 19,  23,  88},
        {  0,   0, 255},
        {127, 127, 255},
        {  0,   0, 165},
        { 82,  82, 165},
        {  0,   0, 127},
        { 63,  63, 127},
        {  0,   0,  76},
        { 38,  38, 126},
        {  0,   0,  38},
        { 19,  19,  88},
        { 63,   0, 255},
        {159, 127, 255},
        { 41,   0, 165},
        {103,  82, 165},
        { 31,   0, 127},
        { 79,  63, 127},
        { 19,   0,  76},
        { 47,  38, 126},
        {  9,   0,  38},
        { 23,  19,  88},
        {127,   0, 255},
        {191, 127, 255},
        {165,   0,  82},
        {124,  82, 165},
        { 63,   0, 127},
        { 95,  63, 127},
        { 38,   0,  76},
        { 57,  38, 126},
        { 19,   0,  38},
        { 28,  19,  88},
        {191,   0, 255},
        {223, 127, 255},
        {124,   0, 165},
        {142,  82, 165},
        { 95,   0, 127},
        {111,  63, 127},
        { 57,   0,  76},
        { 66,  38,  76},
        { 28,   0,  38},
        { 88,  19,  88},
        {255,   0, 255},
        {255, 127, 255},
        {165,   0, 165},
        {165,  82, 165},
        {127,   0, 127},
        {127,  63, 127},
        { 76,   0,  76},
        { 76,  38,  76},
        { 38,   0,  38},
        { 88,  19,  88},
        {255,   0, 191},
        {255, 127, 223},
        {165,   0, 124},
        {165,  82, 145},
        {127,   0,  95},
        {127,  63, 111},
        { 76,   0,  57},
        { 76,  38,  66},
        { 38,   0,  28},
        { 88,  19,  88},
        {255,   0, 127},
        {255, 127, 191},
        {165,   0,  82},
        {165,  82, 124},
        {127,   0,  63},
        {127,  63,  95},
        { 76,   0,  38},
        { 76,  38,  57},
        { 38,   0,  19},
        { 88,  19,  28},
        {255,   0,  63},
        {255, 127, 159},
        {165,   0,  41},
        {165,  82, 103},
        {127,   0,  31},
        {127,  63,  79},
        { 76,   0,  19},
        { 76,  38,  47},
        { 38,   0,   9},
        { 88,  19,  23},
        {  0,   0,   0},
        {101, 101, 101},
        {102, 102, 102},
        {153, 153, 153},
        {204, 204, 204},
        {255, 255, 255}
};

Color Color::ByBlock = Color((short) 0);

Color Color::ByLayer = Color((short) 256);

Color Color::ByEntity = Color((short) 257);

unsigned int Color::getInt24(const std::vector<unsigned char> &array)
{
    if constexpr (is_little_endian)
    {
        return (unsigned int) (array[0] | array[1] << 8 | array[2] << 16);
    }
    else
    {
        return (unsigned int) (array[0] << 16 | array[1] << 8 | array[2]);
    }
}

std::vector<unsigned char> Color::getRgb() const
{
    std::vector<unsigned char> rgb(3);
    if (isTrueColor())
    {
        rgb[0] = (unsigned char) (_color >> 16);
        rgb[1] = (unsigned char) (_color >> 8);
        rgb[2] = (unsigned char) _color;
    }
    else
    {
        return _indexRgb[_color];
    }
}

Color::Color(const Color &rhs)
{
    _color = rhs._color;
}

Color &Color::operator=(const Color &rhs)
{
    _color = rhs._color;
    return *this;
}

Color::Color(unsigned int trueColor)
{
    if (trueColor < 0 || trueColor > _maxTrueColor)
        throw new std::invalid_argument("True color must be a 24 bit color.");

    // Shift to set the 30th bit indicating a true color.
    _color = (unsigned int) (trueColor | _trueColorFlag);
}

Color::Color(short index)
{
    if (index < 0 || index > 257)
        throw new std::invalid_argument("True index must be a value between 0 and 257.");

    _color = (unsigned int) index;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b) : Color(std::vector<unsigned char>{r, g, b}) {}

Color::Color(const std::vector<unsigned char> &rgb)
{
    _color = getInt24(rgb);
}

Color Color::fromTrueColor(unsigned int color)
{
    return Color(color);
}

unsigned char Color::approxIndex(unsigned char r, unsigned char g, unsigned char b)
{
    int prevDist = -1;
    for (int i = 0; i < _indexRgb.size(); i++)
    {
        int dist = (r - _indexRgb[i][0]) + (g - _indexRgb[i][1]) + (b - _indexRgb[i][2]);
        if (dist == 0)
            return (unsigned char) i;

        if (dist < prevDist)
        {
            prevDist = dist;
            return (unsigned char) i;
        }
    }

    return 0;
}

bool Color::isByLayer() const
{
    return index() == 256;
}

bool Color::isByBlock() const
{
    return index() == 0;
}

short Color::index() const
{
    return isTrueColor() ? (short) -1 : (short) _color;
}

int Color::trueColor() const
{
    return isTrueColor() ? (int) (_color ^ (1 << 30)) : -1;
}

bool Color::isTrueColor() const
{
    return _color > 257 || _color < 0;
}

unsigned char Color::red() const
{
    return getRgb()[0];
}

unsigned char Color::green() const
{
    return getRgb()[1];
}

unsigned char Color::blue() const
{
    return getRgb()[2];
}

unsigned char Color::approxIndex() const
{
    if (isTrueColor())
    {
        return approxIndex(red(), green(), blue());
    }
    else
    {
        return (unsigned char) index();
    }
}

}// namespace dwg
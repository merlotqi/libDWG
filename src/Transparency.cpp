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

#include <dwg/Transparency.h>
#include <dwg/utils/EndianConverter.h>
#include <stdexcept>
#include <vector>

namespace dwg {

Transparency Transparency::ByLayer = Transparency(-1);

Transparency Transparency::ByBlock = Transparency(100);

Transparency Transparency::Opaque = Transparency(0);

Transparency::Transparency(short value)
{
    _value = -1;
    setValue(value);
}

bool Transparency::isByLayer() const { return _value == -1; }

bool Transparency::isByBlock() const { return _value == 100; }

short Transparency::value() const { return _value; }

void Transparency::setValue(short value)
{
    if (value == -1)
        _value = value;

    if (value == 100)
        _value = value;

    if (value < 0 || value > 90)
        throw std::invalid_argument("Transparency must be in range from 0 to 90.");

    _value = value;
}

int Transparency::ToAlphaValue(Transparency transparency)
{
    unsigned char alpha = (unsigned char) (255 * (100 - transparency.value()) / 100.0);
    std::vector<unsigned char> bytes = transparency.isByBlock() ? std::vector<unsigned char>{0, 0, 0, 1}
                                                                : std::vector<unsigned char>{alpha, 0, 0, 2};

    return LittleEndianConverter::instance()->toInt32(&bytes[0]);
}

Transparency Transparency::FromAlphaValue(int value)
{
    std::vector<unsigned char> bytes = LittleEndianConverter::instance()->bytes(value);
    short alpha = (short) (100 - (bytes[0] / 255.0) * 100);

    if (alpha == -1)
    {
        return Transparency::ByLayer;
    }

    if (alpha == 100)
    {
        return ByBlock;
    }

    if (alpha < 0)
    {
        return Transparency(0);
    }

    if (alpha > 90)
    {
        return Transparency(90);
    }

    return Transparency(alpha);
}

}// namespace dwg
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

#include <cpl_ports.h>
#include <dwg/Transparency.h>
#include <stdexcept>
#include <vector>

namespace dwg {

DG_Transparency DG_Transparency::ByLayer = DG_Transparency(-1);

DG_Transparency DG_Transparency::ByBlock = DG_Transparency(100);

DG_Transparency DG_Transparency::Opaque = DG_Transparency(0);

DG_Transparency::DG_Transparency(short value)
{
    _value = -1;
    Value(value);
}

bool DG_Transparency::IsByLayer() const { return _value == -1; }

bool DG_Transparency::IsByBlock() const { return _value == 100; }

short DG_Transparency::Value() const { return _value; }

void DG_Transparency::Value(short value)
{
    if (value == -1) _value = value;

    if (value == 100) _value = value;

    if (value < 0 || value > 90) throw std::invalid_argument("DG_Transparency must be in range from 0 to 90.");

    _value = value;
}

int DG_Transparency::ToAlphaValue(DG_Transparency transparency)
{
    unsigned char alpha = (unsigned char) (255 * (100 - transparency.Value()) / 100.0);
    std::vector<unsigned char> bytes = transparency.IsByBlock() ? std::vector<unsigned char>{0, 0, 0, 1}
                                                                : std::vector<unsigned char>{alpha, 0, 0, 2};

    return CPL::LittleEndianConverter::Instance()->ToInt32(&bytes[0]);
}

DG_Transparency DG_Transparency::FromAlphaValue(int value)
{
    std::vector<unsigned char> bytes = CPL::LittleEndianConverter::Instance()->GetBytes(value);
    short alpha = (short) (100 - (bytes[0] / 255.0) * 100);

    if (alpha == -1) { return DG_Transparency::ByLayer; }

    if (alpha == 100) { return ByBlock; }

    if (alpha < 0) { return DG_Transparency(0); }

    if (alpha > 90) { return DG_Transparency(90); }

    return DG_Transparency(alpha);
}

}// namespace dwg
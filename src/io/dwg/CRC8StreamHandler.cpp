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

#include <dwg/io/dwg/CRC8StreamHandler_p.h>

namespace dwg {

unsigned short CRC8StreamHandlerBase::GetCRCValue(unsigned short seed, const std::vector<unsigned char> &buffer,
                                                  long startPos, long endPos)
{
    unsigned short currValue = seed;
    int index = (int) startPos;

    while (endPos-- > 0)
    {
        currValue = CRC8StreamHandler::decode(currValue, buffer[index]);
        index++;
    }

    return currValue;
}

unsigned short CRC8StreamHandlerBase::Seed() const { return _seed; }

void CRC8StreamHandlerBase::Seed(unsigned short seed) { _seed = seed; }


unsigned short CRC8StreamHandlerBase::decode(unsigned short key, unsigned char value)
{
    int index = value ^ (unsigned char) key;
    key = (unsigned short) ((unsigned int) key >> 8 ^ CRC::CrcTable[index]);
    return key;
}

}// namespace dwg
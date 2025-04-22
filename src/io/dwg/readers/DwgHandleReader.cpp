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

#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/readers/DwgHandleReader_p.h>

namespace dwg {

DwgHandleReader::DwgHandleReader(ACadVersion version, IDwgStreamReader *sreader) : DwgSectionIO(version) {}

DwgHandleReader::~DwgHandleReader() {}

std::string DwgHandleReader::sectionName() const
{
    return DwgSectionDefinition::Handles;
}

std::map<unsigned long long, long long> DwgHandleReader::read()
{
    // Handle map, handle | loc
    std::map<unsigned long long, long long> objectMap;

    // Repeat until section size==2 (the last empty (except the CRC) section):
    while (true)
    {//Set the "last handle" to all 0 and the "last loc" to 0L;
        unsigned long long lasthandle = 0;
        long lastloc = 0;

        //Short: size of this section. Note this is in BIGENDIAN order (MSB first)
        int size = _sreader->readShortT<BigEndianConverter>();

        if (size == 2)
            break;

        long startPos = _sreader->position();
        int maxSectionOffset = size - 2;
        //Note that each section is cut off at a maximum length of 2032.
        if (maxSectionOffset > 2032)
            maxSectionOffset = 2032;

        long lastPosition = startPos + maxSectionOffset;

        //Repeat until out of data for this section:
        while (_sreader->position() < lastPosition)
        {
            //offset of this handle from last handle as modular char.
            unsigned long long offset = _sreader->readModularChar();
            lasthandle += offset;

            //offset of location in file from last loc as modular char. (note
            //that location offsets can be negative, if the terminating byte
            //has the 4 bit set).
            lastloc += _sreader->readSignedModularChar();

            if (offset > 0)
            {
                objectMap[lasthandle] = lastloc;
            }
            else
            {
                //0 offset, wrong reference
                // this.notify($ "Negative offset: {offset} for the handle: {lasthandle}", NotificationType.Warning);
            }
        }

        //CRC (most significant byte followed by least significant byte)
        unsigned int crc = ((unsigned int) _sreader->readByte() << 8) + _sreader->readByte();
    };

    return objectMap;
}

}// namespace dwg
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

#include <dwg/io/dwg/DwgSectionIO.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter.h>

namespace dwg {
namespace io {

class DwgHandleWriter : public DwgSectionIO
{
    IDwgStreamWriter *_writer;
    std::vector<unsigned char> _emptyArr;
    std::ostringstream *_stream;
    std::map<unsigned long long, long long> _handleMap;

public:
    std::string SectionName() const { return DwgSectionDefinition::Handles; }

    DwgAppInfoWriter(ACadVersion version, std::ostringstream *stream,
                     const std::map<unsigned long long, long long> &handlemap)
        : DwgSectionIO(version)
    {
        _stream = stream;
        _handleMap = handlemap;
    }

    void Write(int sectionOffset = 0)
    {
        byte[] array = new byte[10];
        byte[] array2 = new byte[5];

        ulong offset = 0uL;
        long initialLoc = 0L;

        long lastPosition = this._stream.Position;

        this._stream.WriteByte(0);
        this._stream.WriteByte(0);

        foreach (var pair in this._handleMap)
        {
            ulong handleOff = pair.Key - offset;
            long lastLoc = (long) pair.Value + sectionOffset;
            long locDiff = lastLoc - initialLoc;

            int offsetSize = modularShortToValue(handleOff, array);
            int locSize = signedModularShortToValue((int) locDiff, array2);

            if (this._stream.Position - lastPosition + (offsetSize + locSize) >
                2032)
            {
                this.processPosition(lastPosition);
                offset = 0uL;
                initialLoc = 0L;
                lastPosition = this._stream.Position;
                this._stream.WriteByte(0);
                this._stream.WriteByte(0);
                offset = 0uL;
                initialLoc = 0L;
                handleOff = pair.Key - offset;

                if (handleOff == 0) { throw new System.Exception(); }

                locDiff = lastLoc - initialLoc;
                offsetSize = modularShortToValue(handleOff, array);
                locSize = signedModularShortToValue((int) locDiff, array2);
            }

            this._stream.Write(array, 0, offsetSize);
            this._stream.Write(array2, 0, locSize);
            offset = pair.Key;
            initialLoc = lastLoc;
        }

        this.processPosition(lastPosition);
        lastPosition = this._stream.Position;
        this._stream.WriteByte(0);
        this._stream.WriteByte(0);
        this.processPosition(lastPosition);
    }

private:
    int modularShortToValue(ulong value, byte[] arr)
    {
        int i = 0;
        while (value >= 0b10000000)
        {
            arr[i] = (byte) ((value & 0b1111111) | 0b10000000);
            i++;
            value >>= 7;
        }
        arr[i] = (byte) value;
        return i + 1;
    }

    int signedModularShortToValue(int value, byte[] arr)
    {
        int i = 0;
        if (value < 0)
        {
            for (value = -value; value >= 64; value >>= 7)
            {
                arr[i] = (byte) (((uint) value & 0x7Fu) | 0x80u);
                i++;
            }
            arr[i] = (byte) ((uint) value | 0x40u);
            return i + 1;
        }

        while (value >= 0b1000000)
        {
            arr[i] = (byte) (((uint) value & 0x7Fu) | 0x80u);
            i++;
            value >>= 7;
        }

        arr[i] = (byte) value;
        return i + 1;
    }

    void processPosition(long pos)
    {
        ushort diff = (ushort) (this._stream.Position - pos);
        long streamPos = this._stream.Position;
        this._stream.Position = pos;
        this._stream.WriteByte((byte) (diff >> 8));
        this._stream.WriteByte((byte) (diff & 0b11111111));
        this._stream.Position = streamPos;

        ushort crc =
                CRC8StreamHandler.GetCRCValue(0xC0C1, this._stream.GetBuffer(),
                                              pos, this._stream.Length - pos);
        this._stream.WriteByte((byte) (crc >> 8));
        this._stream.WriteByte((byte) (crc & 0b11111111));
    }
};


}// namespace io
}// namespace dwg
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

#include <dwg/io/dwg/readers/DwgLZ77AC18Decompressor_p.h>
#include <dwg/utils/StreamWrapper.h>

namespace dwg {

void DwgLZ77AC18Decompressor::Decompress(std::istream *compressed, long long decompressedSize, std::istream *out) {}

void DwgLZ77AC18Decompressor::DecompressToDest(std::istream *src, std::ostream *dst) {}

void DwgLZ77AC18Decompressor::decompress(std::istream *src, std::ostream *dst) {}

unsigned char DwgLZ77AC18Decompressor::copy(int count, std::istream *src, std::ostream *dst)
{
    InputStreamWrapper src_wrapper(src);
    OutputStreamWrapper dst_wrapper(dst);
    for (int i = 0; i < count; ++i)
    {
        unsigned char b = (unsigned char) src_wrapper.readByte();
        dst_wrapper.writeByte(b);
    }

    return (unsigned char) src_wrapper.readByte();
}

int DwgLZ77AC18Decompressor::literalCount(int code, std::istream *src)
{
    InputStreamWrapper wrapper(src);
    int lowbits = code & 0b1111;
    // 0x00 : Set the running total to 0x0F, and read the next byte. From this point on, a 0x00 byte adds 0xFF to the running total,
    // and a non-zero byte adds that value to the running total and terminates the process. Add 3 to the final result.
    if (lowbits == 0)
    {
        unsigned char lastByte;
        for (lastByte = (unsigned char) wrapper.readByte(); lastByte == 0;
             lastByte = (unsigned char) wrapper.readByte())
            lowbits += UCHAR_MAX;

        lowbits += 0xF + lastByte;
    }
    return lowbits;
}

int DwgLZ77AC18Decompressor::readCompressedBytes(int opcode1, int validBits, std::istream *compressed)
{
    InputStreamWrapper wrapper(compressed);

    int compressedBytes = opcode1 & validBits;

    if (compressedBytes == 0)
    {
        unsigned char lastByte;

        for (lastByte = (unsigned char) wrapper.readByte(); lastByte == 0;
             lastByte = (unsigned char) wrapper.readByte())
            compressedBytes += UCHAR_MAX;

        compressedBytes += lastByte + validBits;
    }

    return compressedBytes + 2;
}

int DwgLZ77AC18Decompressor::twoByteOffset(int &offset, int addedValue, std::istream *stream)
{
    InputStreamWrapper wrapper(stream);
    int firstByte = wrapper.readByte();

    offset |= firstByte >> 2;
    offset |= wrapper.readByte() << 6;
    offset += addedValue;

    return firstByte;
}

}// namespace dwg
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
 * GNU General Public License for more dstails.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#include <dwg/io/dwg/readers/DwgLZ77AC21Decompressor_p.h>

namespace dwg {

unsigned int DwgLZ77AC21Decompressor::_sourceOffset = 0;
unsigned int DwgLZ77AC21Decompressor::_length = 0;
unsigned int DwgLZ77AC21Decompressor::_sourceIndex = 0;
unsigned int DwgLZ77AC21Decompressor::_opCode = 0;

std::vector<DwgLZ77AC21Decompressor::copyDelegate> DwgLZ77AC21Decompressor::_copyMethods = {
    [](const std::vector<unsigned char> &, unsigned int, std::vector<unsigned char> &, unsigned int) {},
    [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex)  {copy1b(src, srcIndex, dst, dstIndex); },
    [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex)  {copy2b(src, srcIndex, dst, dstIndex); },
    [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex)  {copy3b(src, srcIndex, dst, dstIndex); },
    [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex)  {copy4b(src, srcIndex, dst, dstIndex); },
    [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 4U, dst, dstIndex);
	  copy4b(src, srcIndex, dst, dstIndex + 1U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 5U, dst, dstIndex);
	  copy4b(src, srcIndex + 1U, dst, dstIndex + 1U);
	  copy1b(src, srcIndex, dst, dstIndex + 5U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy2b(src, srcIndex + 5U, dst, dstIndex);
	  copy4b(src, srcIndex + 1U, dst, dstIndex + 2U);
	  copy1b(src, srcIndex, dst, dstIndex + 6U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 8U, dst, dstIndex);
	  copy8b(src, srcIndex, dst, dstIndex + 1U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 9U, dst, dstIndex);
	  copy8b(src, srcIndex + 1U, dst, dstIndex + 1U);
	  copy1b(src, srcIndex, dst, dstIndex + 9U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy2b(src, srcIndex + 9U, dst, dstIndex);
	  copy8b(src, srcIndex + 1U, dst, dstIndex + 2U);
	  copy1b(src, srcIndex, dst, dstIndex + 10U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy4b(src, srcIndex + 8U, dst, dstIndex);
	  copy8b(src, srcIndex, dst, dstIndex + 4U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 12U, dst, dstIndex);
	  copy4b(src, srcIndex + 8U, dst, dstIndex + 1U);
	  copy8b(src, srcIndex, dst, dstIndex + 5U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 13U, dst, dstIndex);
	  copy4b(src, srcIndex + 9U, dst, dstIndex + 1U);
	  copy8b(src, srcIndex + 1U, dst, dstIndex + 5U);
	  copy1b(src, srcIndex, dst, dstIndex + 13U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy2b(src, srcIndex + 13U, dst, dstIndex);
	  copy4b(src, srcIndex + 9U, dst, dstIndex + 2U);
	  copy8b(src, srcIndex + 1U, dst, dstIndex + 6U);
	  copy1b(src, srcIndex, dst, dstIndex + 14U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy8b(src, srcIndex + 9U, dst, dstIndex);
	  copy1b(src, srcIndex + 8U, dst, dstIndex + 8U);
	  copy8b(src, srcIndex, dst, dstIndex + 9U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 17U, dst, dstIndex);
	  copy16b(src, srcIndex + 1U, dst, dstIndex + 1U);
	  copy1b(src, srcIndex, dst, dstIndex + 17U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy3b(src, srcIndex + 16U, dst, dstIndex);
	  copy16b(src, srcIndex, dst, dstIndex + 3U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy4b(src, srcIndex + 16U, dst, dstIndex);
	  copy8b(src, srcIndex + 8U, dst, dstIndex + 4U);
	  copy8b(src, srcIndex, dst, dstIndex + 12U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 20U, dst, dstIndex);
	  copy4b(src, srcIndex + 16U, dst, dstIndex + 1U);
	  copy8b(src, srcIndex + 8U, dst, dstIndex + 5U);
	  copy8b(src, srcIndex, dst, dstIndex + 13U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy2b(src, srcIndex + 20U, dst, dstIndex);
	  copy4b(src, srcIndex + 16U, dst, dstIndex + 2U);
	  copy8b(src, srcIndex + 8U, dst, dstIndex + 6U);
	  copy8b(src, srcIndex, dst, dstIndex + 14U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy3b(src, srcIndex + 20U, dst, dstIndex);
	  copy4b(src, srcIndex + 16U, dst, dstIndex + 3U);
	  copy8b(src, srcIndex + 8U, dst, dstIndex + 7U);
	  copy8b(src, srcIndex, dst, dstIndex + 15U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy8b(src, srcIndex + 16U, dst, dstIndex);
	  copy16b(src, srcIndex, dst, dstIndex + 8U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy8b(src, srcIndex + 17U, dst, dstIndex);
	  copy1b(src, srcIndex + 16U, dst, dstIndex + 8U);
	  copy16b(src, srcIndex, dst, dstIndex + 9U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 25U, dst, dstIndex);
	  copy8b(src, srcIndex + 17U, dst, dstIndex + 1U);
	  copy1b(src, srcIndex + 16U, dst, dstIndex + 9U);
	  copy16b(src, srcIndex, dst, dstIndex + 10U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy2b(src, srcIndex + 25U, dst, dstIndex);
	  copy8b(src, srcIndex + 17U, dst, dstIndex + 2U);
	  copy1b(src, srcIndex + 16U, dst, dstIndex + 10U);
	  copy16b(src, srcIndex, dst, dstIndex + 11U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy4b(src, srcIndex + 24U, dst, dstIndex);
	  copy8b(src, srcIndex + 16U, dst, dstIndex + 4U);
	  copy8b(src, srcIndex + 8U, dst, dstIndex + 12U);
	  copy8b(src, srcIndex, dst, dstIndex + 20U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 28U, dst, dstIndex);
	  copy4b(src, srcIndex + 24U, dst, dstIndex + 1U);
	  copy8b(src, srcIndex + 16U, dst, dstIndex + 5U);
	  copy8b(src, srcIndex + 8U, dst, dstIndex + 13U);
	  copy8b(src, srcIndex, dst, dstIndex + 21U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy2b(src, srcIndex + 28U, dst, dstIndex);
	  copy4b(src, srcIndex + 24U, dst, dstIndex + 2U);
	  copy8b(src, srcIndex + 16U, dst, dstIndex + 6U);
	  copy8b(src, srcIndex + 8U, dst, dstIndex + 14U);
	  copy8b(src, srcIndex, dst, dstIndex + 22U);
	},
	 [](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex) 
	{
	  copy1b(src, srcIndex + 30U, dst, dstIndex);
	  copy4b(src, srcIndex + 26U, dst, dstIndex + 1U);
	  copy8b(src, srcIndex + 18U, dst, dstIndex + 5U);
	  copy8b(src, srcIndex + 10U, dst, dstIndex + 13U);
	  copy8b(src, srcIndex + 2U, dst, dstIndex + 21U);
	  copy2b(src, srcIndex, dst, dstIndex + 29U);
	}
};

void DwgLZ77AC21Decompressor::Decompress(const std::vector<unsigned char> &source, unsigned int initialOffset,
                                         unsigned int length, std::vector<unsigned char> &buffer)
{
    _sourceOffset = 0;
    _length = 0;
    _sourceIndex = initialOffset;
    _opCode = source[_sourceIndex];

    unsigned int destIndex = 0;
    unsigned int endIndex = _sourceIndex + length;

    ++_sourceIndex;

    if (_sourceIndex >= endIndex)
        return;

        if (((int) _opCode & 240) == 32)
        {
            _sourceIndex += 3U;
            _length = source[_sourceIndex - 1];
            _length &= 7U;
        }
    
        while (_sourceIndex < endIndex)
        {
            nextIndex(source, buffer, destIndex);
    
            if (_sourceIndex >= endIndex)
            break;

        destIndex = copyDecompressedChunks(source, endIndex, buffer, destIndex);
    }
}

void DwgLZ77AC21Decompressor::nextIndex(const std::vector<unsigned char> &source, std::vector<unsigned char> &dest,
                                        unsigned int &index)
{
	if (_length == 0U)
		readLiteralLength(source);

    copy(source, _sourceIndex, dest, index, _length);
	_sourceIndex += _length;
	index += _length;
}

unsigned int DwgLZ77AC21Decompressor::copyDecompressedChunks(const std::vector<unsigned char> &src,
                                                             unsigned int endIndex, std::vector<unsigned char> &dst,
                                                             unsigned int destIndex)
{
    _length = 0U;
    _opCode = src[_sourceIndex];
    ++_sourceIndex;

    readInstructions(src);

    while (true)
    {
        copyBytes(dst, destIndex, _length, _sourceOffset);

        destIndex += _length;

        _length = _opCode & 0x07;

        if (_length != 0U || _sourceIndex >= endIndex)
            break;

        _opCode = src[_sourceIndex];
        ++_sourceIndex;

        if (_opCode >> 4 == 0)
            break;

        if (_opCode >> 4 == 15)
            _opCode &= 15;

        readInstructions(src);
    }
    return destIndex;
}

void DwgLZ77AC21Decompressor::readInstructions(const std::vector<unsigned char> &buffer) 
{
    switch (_opCode >> 4)
    {
        case 0:
            _length = (_opCode & 0xF) + 0x13;
            _sourceOffset = buffer[_sourceIndex];
            ++_sourceIndex;
            _opCode = buffer[_sourceIndex];
            ++_sourceIndex;
            _length = (_opCode >> 3 & 0x10) + _length;
            _sourceOffset = ((_opCode & 0x78) << 5) + 1 + _sourceOffset;
            break;
        case 1:
            _length = (_opCode & 0xF) + 3;
            _sourceOffset = buffer[_sourceIndex];
            ++_sourceIndex;
            _opCode = buffer[_sourceIndex];
            ++_sourceIndex;
            _sourceOffset = ((_opCode & 248) << 5) + 1 + _sourceOffset;
            break;
        case 2:
            _sourceOffset = buffer[_sourceIndex];
            ++_sourceIndex;
            _sourceOffset = (unsigned int)(buffer[_sourceIndex] << 8 & 0xFF00) | _sourceOffset;
            ++_sourceIndex;
            _length = _opCode & 7U;
            if ((_opCode & 8) == 0)
            {
                _opCode = buffer[_sourceIndex];
                ++_sourceIndex;
                _length = (_opCode & 0xF8) + _length;

            }
            else
            {
                ++_sourceOffset;
                _length = (unsigned int)((buffer[_sourceIndex] << 3) + _length);
                ++_sourceIndex;
                _opCode = buffer[_sourceIndex];
                ++_sourceIndex;
                _length = ((_opCode & 0xF8) << 8) + _length + 0x100;
            }
            break;
        default:
            _length = _opCode >> 4;
            _sourceOffset = _opCode & 15U;
            _opCode = buffer[_sourceIndex];
            ++_sourceIndex;
            _sourceOffset = ((_opCode & 0xF8) << 1) + _sourceOffset + 1;
            break;
    }
}

void DwgLZ77AC21Decompressor::readLiteralLength(const std::vector<unsigned char> &buffer) 
{
    _length = _opCode + 8;
    if (_length == 0x17)
    {
        unsigned int n = buffer[_sourceIndex];
        ++_sourceIndex;
        _length += n;

        if (n == 0xFF)
        {
            do
            {
                n = buffer[_sourceIndex];
                ++_sourceIndex;
                n |= (unsigned int)buffer[_sourceIndex] << 8;
                ++_sourceIndex;
                _length += n;

            } while (n == 0xFFFF);
        }
    }
}

void DwgLZ77AC21Decompressor::copyBytes(std::vector<unsigned char> &dst, unsigned int dstIndex, unsigned int length,
                                        unsigned int srcOffset)
{
    unsigned int initialIndex = dstIndex - srcOffset;
    unsigned int maxIndex = initialIndex + length;

    while (initialIndex < maxIndex) dst[(int) dstIndex++] = dst[(int) initialIndex++];
}

void DwgLZ77AC21Decompressor::copy(const std::vector<unsigned char> &src, unsigned int srcIndex,
                                   std::vector<unsigned char> &dst, unsigned int dstIndex, unsigned int length)
{
    for (; length >= 32U; length -= 32U)
    {
        copy4b(src, srcIndex + 24U, dst, dstIndex);
        copy4b(src, srcIndex + 28U, dst, dstIndex + 4U);
        copy4b(src, srcIndex + 16U, dst, dstIndex + 8U);
        copy4b(src, srcIndex + 20U, dst, dstIndex + 12U);
        copy4b(src, srcIndex + 8U, dst, dstIndex + 16U);
        copy4b(src, srcIndex + 12U, dst, dstIndex + 20U);
        copy4b(src, srcIndex, dst, dstIndex + 24U);
        copy4b(src, srcIndex + 4U, dst, dstIndex + 28U);

        srcIndex += 32U;
        dstIndex += 32U;
    }
    if (length <= 0U)
        return;

	_copyMethods[(int)length][](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex);
}

void DwgLZ77AC21Decompressor::copy1b(const std::vector<unsigned char> &src, unsigned int srcIndex,
                                     std::vector<unsigned char> &dst, unsigned int dstIndex)
{
    dst[(int) dstIndex] = src[(int) srcIndex];
}

void DwgLZ77AC21Decompressor::copy2b(const std::vector<unsigned char> &src, unsigned int srcIndex,
                                     std::vector<unsigned char> &dst, unsigned int dstIndex)
{
    dst[(int) dstIndex] = src[(int) srcIndex + 1];
    dst[(int) dstIndex + 1] = src[(int) srcIndex];
}

void DwgLZ77AC21Decompressor::copy3b(const std::vector<unsigned char> &src, unsigned int srcIndex,
                                     std::vector<unsigned char> &dst, unsigned int dstIndex)
{
    dst[(int) dstIndex] = src[(int) srcIndex + 2];
    dst[(int) dstIndex + 1] = src[(int) srcIndex + 1];
    dst[(int) dstIndex + 2] = src[(int) srcIndex];
}

void DwgLZ77AC21Decompressor::copy4b(const std::vector<unsigned char> &src, unsigned int srcIndex,
                                     std::vector<unsigned char> &dst, unsigned int dstIndex)
{
    dst[(int) dstIndex] = src[(int) srcIndex];
    dst[(int) dstIndex + 1] = src[(int) srcIndex + 1];
    dst[(int) dstIndex + 2] = src[(int) srcIndex + 2];
    dst[(int) dstIndex + 3] = src[(int) srcIndex + 3];
}

void DwgLZ77AC21Decompressor::copy8b(const std::vector<unsigned char> &src, unsigned int srcIndex,
                                     std::vector<unsigned char> &dst, unsigned int dstIndex) 
{
    copy4b[](const std::vector<unsigned char> &src, unsigned int srcIndex, std::vector<unsigned char> &dst, unsigned int dstIndex);
    copy4b(src, srcIndex + 4U, dst, dstIndex + 4U);
}

void DwgLZ77AC21Decompressor::copy16b(const std::vector<unsigned char> &src, unsigned int srcIndex,
                                      std::vector<unsigned char> &dst, unsigned int dstIndex)
{
    copy8b(src, srcIndex + 8U, dst, dstIndex);
    copy8b(src, srcIndex, dst, dstIndex + 8U);
}

}// namespace dwg
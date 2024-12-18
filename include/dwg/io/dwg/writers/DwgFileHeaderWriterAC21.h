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

#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC18.h>
#include <dwg/io/dwg/writers/DwgLZ77AC21Compressor.h>

namespace dwg {
namespace io {

class DwgFileHeaderWriterAC21 : DwgFileHeaderWriterAC18
{
protected:
    int _fileHeaderSize() const override { return 0x480; }

    void craeteLocalSection(const DwgSectionDescriptor &descriptor,
                            const std::vector<unsigned char> &buffer,
                            int decompressedSize, ulong offset, int totalSize,
                            bool isCompressed) override
    {
        std::ostringstream descriptorStream = applyCompression(
                buffer, decompressedSize, offset, totalSize, isCompressed);
        writeMagicNumber();
    }

public
    DwgFileHeaderWriterAC21(std::ostream *stream, Encoding encoding,
                            CadDocument *model)
        : DwgFileHeaderWriterAC18(stream, encoding, model)
    {
        compressor = new DwgLZ77AC21Compressor();
    }
}

}// namespace io
}// namespace dwg
/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General  License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General  License for more details.
 *
 * You should have received a copy of the GNU General  License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include "IDwgFileHeaderWriter.h"
#include <assert.h>
#include <dwg/CadDocument.h>
#include <dwg/ACadVersion.h>
#include <base.h>
#include <fstream>
#include <sstream>

namespace dwg {
namespace io {

class DwgFileHeaderWriterBase : public IDwgFileHeaderWriter
{
protected:
    ACadVersion _version;
    Encoding _encoding;
    std::ofstream *_stream;
    CadDocument *_document;

    virtual int HandleSectionOffset() const = 0;
    virtual int _fileHeaderSize() const = 0;

public:
    DwgFileHeaderWriterBase(std::ofstream *stream, Encoding encoding,
                            CadDocument *model);
    unsigned short getFileCodePage();
    void applyMask(std::vector<unsigned char> &buffer, int offset, int length);
    bool checkEmptyBytes(const std::vector<unsigned char> &buffer,
                         unsigned long long offset,
                         unsigned long long spearBytes) const;
    void writeMagicNumber();
    void applyMagicSequence(std::ostringstream *stream);
};

}// namespace io
}// namespace dwg
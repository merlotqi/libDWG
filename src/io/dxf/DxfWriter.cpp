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

#include <dwg/CadDocument.h>
#include <dwg/DxfCode.h>
#include <dwg/DxfFileToken_p.h>
#include <dwg/io/dxf/CadObjectHolder_p.h>
#include <dwg/io/dxf/DxfWriter.h>
#include <dwg/io/dxf/writers/DxfAsciiWriter_p.h>
#include <dwg/io/dxf/writers/DxfBinaryWriter_p.h>
#include <dwg/io/dxf/writers/DxfBlocksSectionWriter_p.h>
#include <dwg/io/dxf/writers/DxfClassesSectionWriter_p.h>
#include <dwg/io/dxf/writers/DxfEntitiesSectionWriter_p.h>
#include <dwg/io/dxf/writers/DxfHeaderSectionWriter_p.h>
#include <dwg/io/dxf/writers/DxfObjectsSectionWriter_p.h>
#include <dwg/io/dxf/writers/DxfTablesSectionWriter_p.h>
#include <dwg/objects/CadDictionary.h>

namespace dwg {

DxfWriter::DxfWriter(const std::string &filename, CadDocument *document, bool binary)
    : DxfWriter(new std::fstream(filename, binary ? std::ios::out | std::ios::binary : std::ios::out), document,
                binary)
{
}

DxfWriter::DxfWriter(std::fstream *stream, CadDocument *document, bool binary)
    : CadWriterBase<DxfWriterConfiguration>(stream, document), _binary(binary)
{
    _objectHolder = new CadObjectHolder();
}

DxfWriter::~DxfWriter() {}

void DxfWriter::write()
{
    CadWriterBase::write();
    createStreamWriter();
    _objectHolder->objects().push(_document->rootDictionary());
    writeHeader();
    writeDxfClasses();
    writeTables();
    writeBlocks();
    writeEntities();
    writeObjects();
    writeACDSData();
    _writer->write(DxfCode::Start, DxfFileToken::EndOfFile);
    _writer->flush();
    if (closeStream())
    {
        _writer->close();
    }
}

bool DxfWriter::isBinaray() const
{
    return _binary;
}

void DxfWriter::createStreamWriter()
{
    if (_binary)
    {
        _writer = new DxfBinaryWriter(_stream, Encoding(CodePage::Utf8));
    }
    else
    {
        _writer = new DxfAsciiWriter(_stream, Encoding(CodePage::Utf8));
    }
}

void DxfWriter::writeHeader()
{
    auto &&writer = std::make_unique<DxfHeaderSectionWriter>(_writer, _document, _objectHolder, *this);
    writer->write();
}

void DxfWriter::writeDxfClasses()
{
    auto &&writer = std::make_unique<DxfClassesSectionWriter>(_writer, _document, _objectHolder, *this);
    writer->write();
}

void DxfWriter::writeTables()
{
    auto &&writer = std::make_unique<DxfTablesSectionWriter>(_writer, _document, _objectHolder, *this);
    writer->write();
}

void DxfWriter::writeBlocks()
{
    auto &&writer = std::make_unique<DxfBlocksSectionWriter>(_writer, _document, _objectHolder, *this);
    writer->write();
}

void DxfWriter::writeEntities()
{
    auto &&writer = std::make_unique<DxfEntitiesSectionWriter>(_writer, _document, _objectHolder, *this);
    writer->write();
}

void DxfWriter::writeObjects()
{
    auto &&writer = std::make_unique<DxfObjectsSectionWriter>(_writer, _document, _objectHolder, *this);
    writer->write();
}

void DxfWriter::writeACDSData() {}

}// namespace dwg
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

#include <dwg/enums/ACadVersion.h>
#include <dwg/io/CadWriterBase.h>
#include <dwg/io/CadWriterConfiguration.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeader.h>
#include <dwg/io/dwg/writers/IDwgFileHeaderWriter.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC15.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC18.h>

#include <sstream>
#include <stdexcept>

namespace dwg {
namespace io {

class DwgWriter : public CadWriterBase<CadWriterConfiguration>
{
private:
    ACadVersion _version;
    DwgFileHeader *_fileHeader;
    IDwgFileHeaderWriter *_fileHeaderWriter;

public:
    DwgWriter(std::ofstream *stream, CadDocument *document)
        : CadWriterBase(stream, document)
    {
        _version = document->Header.Version;
        _fileHeader = DwgFileHeader::CreateFileHeader(_version);
    }

    void Write() override
    {
        CadWriterBase::Write();
        getFileHeaderWriter();
        writeHeader();
        writeClasses();
        writeSummaryInfo();
        writePreview();
        writeAppInfo();
        writeFileDepList();
        writeRevHistory();
        // writeSecurity();
        writeAuxHeader();
        writeObjects();
        writeObjFreeSpace();
        writeTemplate();
        // writePrototype();

        // Write in the last place to avoid conflicts with versions < AC1018
        writeHandles();

        _fileHeaderWriter->writeFile();

        _stream->flush();
        if (Configuration.CloseStream) { _stream->clear(); }
    }

private:
    void getFileHeaderWriter()
    {
        switch (_document->Header.Version)
        {
            case ACadVersion::MC0_0:
            case ACadVersion::AC1_2:
            case ACadVersion::AC1_4:
            case ACadVersion::AC1_50:
            case ACadVersion::AC2_10:
            case ACadVersion::AC1002:
            case ACadVersion::AC1003:
            case ACadVersion::AC1004:
            case ACadVersion::AC1006:
            case ACadVersion::AC1009:
            case ACadVersion::AC1012:
                throw new std::runtime_error("");
            case ACadVersion::AC1014:
            case ACadVersion::AC1015:
                _fileHeaderWriter =
                        new DwgFileHeaderWriterAC15(_stream, _document);
                break;
            case ACadVersion::AC1018:
                _fileHeaderWriter =
                        new DwgFileHeaderWriterAC18(_stream, _document);
                break;
            case ACadVersion::AC1021:
                throw new std::runtime_error("");
            case ACadVersion::AC1024:
            case ACadVersion::AC1027:
            case ACadVersion::AC1032:
                _fileHeaderWriter =
                        new DwgFileHeaderWriterAC18(_stream, _document);
                break;
            default:
                throw new std::runtime_error("");
        };
    }

    void writeHeader() {}

    void writeClasses() {}

    void writeSummaryInfo()
    {
        std::ostringstream *stream = new std::ostringstream();
        IDwgStreamWriter *writer =
                DwgStreamWriterBase::GetStreamWriter(_version, stream);
        CadSummaryInfo info = m_document->getSummaryInfo();
        writer->WriteTextUnicode(info.getTitle());

        _fileHeaderWriter->addSection(DwgSectionDefinition::SummaryInfo, stream,
                                      false, 0x100);
    }

    void writePreview()
    {
        std::ostringstream *stream = new std::ostringstream();
        // previewWriter;
        _fileHeaderWriter->addSection(DwgSectionDefinition::Preview, stream,
                                      false, 0x400);
    }

    void writeAppInfo()
    {
        if (_fileHeader->Version < ACadVersion::AC1018) return;

        std::ostringstream *stream = new std::ostringstream();
        DwgAppInfoWriter *writer = new DwgAppInfoWriter(_version, stream);
    }

    void writeFileDepList();
    void writeRevHistory();
    void writeAuxHeader();
    void writeObjects();
    void writeObjFreeSpace();
    void writeTemplate();
    void writeHandles();
};


}
}
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
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition.h>
#include <dwg/io/dwg/writers/DwgAppInfoWriter.h>
#include <dwg/io/dwg/writers/DwgClassesWriter.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC15.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC18.h>
#include <dwg/io/dwg/writers/DwgHeaderWriter.h>
#include <dwg/io/dwg/writers/DwgPreviewWriter.h>
#include <dwg/io/dwg/writers/IDwgFileHeaderWriter.h>
#include <dwg/io/dwg/writers/DwgAuxHeaderWriter.h>
#include <dwg/io/dwg/writers/DwgObjectWriter.h>

#include <sstream>
#include <stdexcept>

namespace dwg {
namespace io {

class DwgWriter : public CadWriterBase
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

        _fileHeaderWriter->WriteFile();

        _stream->flush();
        if (_configuration->CloseStream) { _stream->clear(); }
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
                _fileHeaderWriter = new DwgFileHeaderWriterAC15(
                        _stream, _encoding, _document);
                break;
            case ACadVersion::AC1018:
                _fileHeaderWriter = new DwgFileHeaderWriterAC18(
                        _stream, _encoding, _document);
                break;
            case ACadVersion::AC1021:
                throw new std::runtime_error("");
            case ACadVersion::AC1024:
            case ACadVersion::AC1027:
            case ACadVersion::AC1032:
                _fileHeaderWriter = new DwgFileHeaderWriterAC18(
                        _stream, _encoding, _document);
                break;
            default:
                throw new std::runtime_error("");
        };
    }

    void writeHeader()
    {
        std::ostringstream *stream = new std::ostringstream();
        DwgHeaderWriter *writer =
                new DwgHeaderWriter(stream, _document, _encoding);
        writer->Write();

        _fileHeaderWriter->AddSection(DwgSectionDefinition::Header, stream,
                                      true);
    }

    void writeClasses()
    {
        std::ostringstream *stream = new std::ostringstream();
        DwgClassesWriter *writer =
                new DwgClassesWriter(stream, _document, _encoding);
        writer->Write();
        _fileHeaderWriter->AddSection(DwgSectionDefinition::Classes, stream,
                                      false);
    }

    void writeSummaryInfo()
    {
        std::ostringstream *stream = new std::ostringstream();
        IDwgStreamWriter *writer = DwgStreamWriterBase::GetStreamWriter(
                _version, stream, _encoding);
        CadSummaryInfo info = _document->SummaryInfo;
        writer->WriteTextUnicode(info.getTitle());
        _fileHeaderWriter->AddSection(DwgSectionDefinition::SummaryInfo, stream,
                                      false, 0x100);
    }

    void writePreview()
    {
        std::ostringstream *stream = new std::ostringstream();
        DwgPreviewWriter *writer = new DwgPreviewWriter(_version, stream);
        writer->Write();
        _fileHeaderWriter->AddSection(DwgSectionDefinition::Preview, stream,
                                      false, 0x400);
    }

    void writeAppInfo()
    {
        if (_fileHeader->Version < ACadVersion::AC1018) return;

        std::ostringstream *stream = new std::ostringstream();
        DwgAppInfoWriter *writer = new DwgAppInfoWriter(_version, stream);
    }

    void writeFileDepList()
    {
        if (_fileHeader->Version < ACadVersion::AC1018) return;

        std::ostringstream *stream = new std::ostringstream();   
        OutputStream swriter(stream, false, false);
        swriter.Write<unsigned int>(0);//Int32	4	Feature count(ftc)

        //String32	ftc * (4 + n)	Feature name list.A feature name is one of the following:
        /*
    * “Acad: XRef” (for block table record)
    * “Acad: Image” (for image definition)
    * “Acad: PlotConfig” (for plotsetting)
    * “Acad: Text” (for text style)
    */

        //Int32	4	File count
        swriter.Write<unsigned int>(0);

        //Then follows an array of features(repeated file count times). The feature name + the full filename constitute the lookup key of a file dependency:

        //String32	4 + n	Full filename
        //String32	4 + n	Found path, path at which file was found
        //String32	4 + n	Fingerprint GUID(applies to xref’s only)
        //String32	4 + n	Version GUID(applies to xref’s only)
        //Int32	4	Feature index in the feature list above.
        //Int32	4	Timestamp(Seconds since 1 / 1 / 1980)
        //Int32	4	Filesize
        //Int16	2	Affects graphics(1 = true, 0 = false)
        //Int32	4	Reference count

        _fileHeaderWriter->AddSection(DwgSectionDefinition::FileDepList, stream,
                                      false, 0x80);
    }
    void writeRevHistory()
    {
        	if (_fileHeader->Version < ACadVersion::AC1018)
				return;
            std::ostringstream* stream = new std::ostringstream();
            unsigned int v = 0;
            stream->write((char*)&v, sizeof(v));
            stream->write((char*)&v, sizeof(v));
            stream->write((char*)&v, sizeof(v));
			_fileHeaderWriter->AddSection(DwgSectionDefinition::RevHistory, stream, true);
    }
    void writeAuxHeader()
    {
        	std::ostringstream* stream = new std::ostringstream();
			DwgAuxHeaderWriter* writer = new DwgAuxHeaderWriter(stream, _encoding, _document->Header);
			writer->Write();

			_fileHeaderWriter->AddSection(DwgSectionDefinition::AuxHeader, stream, true);
    }
    void writeObjects()
    {
        	std::ostringstream* stream = new std::ostringstream();
			DwgObjectWriter* writer = new DwgObjectWriter(stream, _document, _encoding, false);
			writer->Write();

			_handlesMap = writer->Map();

			_fileHeaderWriter->AddSection(DwgSectionDefinition::AcDbObjects, stream, true);
    }
    void writeObjFreeSpace()
    {
        std::ostringstream* stream = new std::ostringstream();
        			MemoryStream stream = new MemoryStream();
			StreamIO writer = new StreamIO(stream);

			//Int32	4	0
			writer.Write<int>(0);
			//UInt32	4	Approximate number of objects in the drawing(number of handles).
			writer.Write<uint>((uint)this._handlesMap.Count);

			//Julian datetime	8	If version > R14 then system variable TDUPDATE otherwise TDUUPDATE.
			if (this._version >= ACadVersion.AC1015)
			{
				CadUtils.DateToJulian(this._document.Header.UniversalUpdateDateTime, out int jdate, out int mili);
				writer.Write<int>(jdate);
				writer.Write<int>(mili);
			}
			else
			{
				CadUtils.DateToJulian(this._document.Header.UpdateDateTime, out int jdate, out int mili);
				writer.Write<int>(jdate);
				writer.Write<int>(mili);
			}

			//UInt32	4	Offset of the objects section in the stream.
			writer.Write<uint>(0);  //It may be the cause of failure for version AC1024

			//UInt8	1	Number of 64 - bit values that follow(ODA writes 4).
			writer.Stream.WriteByte(4);
			//UInt32	4	ODA writes 0x00000032
			writer.Write<uint>(0x00000032);
			//UInt32	4	ODA writes 0x00000000
			writer.Write<uint>(0x00000000);
			//UInt32	4	ODA writes 0x00000064
			writer.Write<uint>(0x00000064);
			//UInt32	4	ODA writes 0x00000000
			writer.Write<uint>(0x00000000);
			//UInt32	4	ODA writes 0x00000200
			writer.Write<uint>(0x00000200);
			//UInt32	4	ODA writes 0x00000000
			writer.Write<uint>(0x00000000);
			//UInt32	4	ODA writes 0xffffffff
			writer.Write<uint>(0xffffffff);
			//UInt32	4	ODA writes 0x00000000
			writer.Write<uint>(0x00000000);

			this._fileHeaderWriter.AddSection(DwgSectionDefinition.ObjFreeSpace, stream, true);
    }
    void writeTemplate()
    {
        			MemoryStream stream = new MemoryStream();
			StreamIO writer = new StreamIO(stream);

			//Int16	2	Template description string length in bytes(the ODA always writes 0 here).
			writer.Write<short>(0);
			//UInt16	2	MEASUREMENT system variable(0 = English, 1 = Metric).
			writer.Write<ushort>((ushort)1);

			this._fileHeaderWriter.AddSection(DwgSectionDefinition.Template, stream, true);
    }
    void writeHandles()
    {
        			MemoryStream stream = new MemoryStream();
			DwgHandleWriter writer = new DwgHandleWriter(this._version, stream, this._handlesMap);
			writer.Write(this._fileHeaderWriter.HandleSectionOffset);

			this._fileHeaderWriter.AddSection(DwgSectionDefinition.Handles, stream, true);
    }
};


}// namespace io
}// namespace dwg
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
#include <dwg/CadSummaryInfo.h>
#include <dwg/CadUtils.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/DwgWriter.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeader_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/DwgAppInfoWriter_p.h>
#include <dwg/io/dwg/writers/DwgAuxHeaderWriter_p.h>
#include <dwg/io/dwg/writers/DwgClassesWriter_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC15_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC18_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterBase_p.h>
#include <dwg/io/dwg/writers/DwgHandleWriter_p.h>
#include <dwg/io/dwg/writers/DwgHeaderWriter_p.h>
#include <dwg/io/dwg/writers/DwgObjectWriter_p.h>
#include <dwg/io/dwg/writers/DwgPreviewWriter_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/io/dwg/writers/IDwgFileHeaderWriter_p.h>
#include <dwg/utils/StreamWrapper.h>
#include <fmt/core.h>
#include <sstream>
#include <stdexcept>

namespace dwg {

DwgWriter::DwgWriter(const std::string &filename, CadDocument *document)
    : DwgWriter(new std::fstream(filename, std::ios::binary), document)
{
}

DwgWriter::DwgWriter(std::fstream *stream, CadDocument *document)
    : CadWriterBase(stream, document), _fileHeaderWriter(nullptr)
{
    _version = document->header()->version();
    _fileHeader = DwgFileHeader::CreateFileHeader(_version);
}

void DwgWriter::write()
{
    CadWriterBase::write();
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
    if (closeStream())
    {
        _stream->clear();
    }
}


void DwgWriter::getFileHeaderWriter()
{
    auto &&version = _document->header()->version();
    switch (version)
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
            throw std::runtime_error(
                    fmt::format("File version not supported:{}", CadUtils::GetNameFromVersion(version)));
        case ACadVersion::AC1014:
        case ACadVersion::AC1015:
            _fileHeaderWriter = new DwgFileHeaderWriterAC15(_stream, _encoding, _document);
            break;
        case ACadVersion::AC1018:
            _fileHeaderWriter = new DwgFileHeaderWriterAC18(_stream, _encoding, _document);
            break;
        case ACadVersion::AC1021:
            throw std::runtime_error(
                    fmt::format("File version not supported:{}", CadUtils::GetNameFromVersion(version)));
        case ACadVersion::AC1024:
        case ACadVersion::AC1027:
        case ACadVersion::AC1032:
            _fileHeaderWriter = new DwgFileHeaderWriterAC18(_stream, _encoding, _document);
            break;
        default:
            throw std::runtime_error(
                    fmt::format("File version not supported:{}", CadUtils::GetNameFromVersion(version)));
    };
}

void DwgWriter::writeHeader()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    std::unique_ptr<DwgHeaderWriter> writer = std::make_unique<DwgHeaderWriter>(stream.get(), _document, _encoding);
    writer->write();

    _fileHeaderWriter->addSection(DwgSectionDefinition::Header, stream.release(), true);
}

void DwgWriter::writeClasses()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    std::unique_ptr<DwgClassesWriter> writer = std::make_unique<DwgClassesWriter>(stream.get(), _document, _encoding);
    writer->write();

    _fileHeaderWriter->addSection(DwgSectionDefinition::Classes, stream.release(), false);
}

void DwgWriter::writeSummaryInfo()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    IDwgStreamWriter *writer = DwgStreamWriterBase::GetStreamWriter(_version, stream.get(), _encoding);
    CadSummaryInfo *info = _document->summaryInfo();
    writer->writeTextUtf8(info->title());
    writer->writeTextUtf8(info->subject());
    writer->writeTextUtf8(info->author());
    writer->writeTextUtf8(info->keywords());
    writer->writeTextUtf8(info->comments());
    writer->writeTextUtf8(info->lastSavedBy());
    writer->writeTextUtf8(info->revisionNumber());
    writer->writeTextUtf8(info->hyperlinkBase());

    //?	8	Total editing time(ODA writes two zero Int32's)
    writer->writeInt(0);
    writer->writeInt(0);

    writer->write8BitJulianDate(info->createdDate());
    writer->write8BitJulianDate(info->modifiedDate());

    //Int16	2 + 2 * (2 + n)	Property count, followed by PropertyCount key/value string pairs.
    auto &&properties = info->properties();
    writer->writeRawShort((unsigned short) properties.size());
    for (auto it = properties.begin(); it != properties.end(); ++it)
    {
        writer->writeTextUtf8(it->first);
        writer->writeTextUtf8(it->second);
    }

    writer->writeInt(0);
    writer->writeInt(0);

    _fileHeaderWriter->addSection(DwgSectionDefinition::SummaryInfo, stream.release(), false, 0x100);
    delete writer;
    writer = nullptr;
}

void DwgWriter::writePreview()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    std::unique_ptr<DwgPreviewWriter> writer = std::make_unique<DwgPreviewWriter>(_version, stream.get());
    writer->write();

    _fileHeaderWriter->addSection(DwgSectionDefinition::Preview, stream.release(), false, 0x400);
}

void DwgWriter::writeAppInfo()
{
    if (_fileHeader->version() < ACadVersion::AC1018)
        return;

    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    std::unique_ptr<DwgAppInfoWriter> writer = std::make_unique<DwgAppInfoWriter>(_version, stream.get());
    writer->write();

    _fileHeaderWriter->addSection(DwgSectionDefinition::AppInfo, stream.release(), false, 0x80);
}

void DwgWriter::writeFileDepList()
{
    if (_fileHeader->version() < ACadVersion::AC1018)
        return;

    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    StreamWrapper swriter(stream.get());
    swriter.write<unsigned int>(0);//Int32	4	Feature count(ftc)

    //String32	ftc * (4 + n)	Feature name list.A feature name is one of the following:
    /*
    * "Acad: XRef" (for block table record)
    * "Acad: Image" (for image definition)
    * "Acad: PlotConfig" (for plotsetting)
    * "Acad: Text" (for text style)
    */

    //Int32	4	File count
    swriter.write<unsigned int>(0);

    //Then follows an array of features(repeated file count times). The feature name + the full filename constitute the lookup key of a file dependency:

    //String32	4 + n	Full filename
    //String32	4 + n	Found path, path at which file was found
    //String32	4 + n	Fingerprint GUID(applies to xref's only)
    //String32	4 + n	Version GUID(applies to xref's only)
    //Int32	4	Feature index in the feature list above.
    //Int32	4	Timestamp(Seconds since 1 / 1 / 1980)
    //Int32	4	Filesize
    //Int16	2	Affects graphics(1 = true, 0 = false)
    //Int32	4	Reference count

    _fileHeaderWriter->addSection(DwgSectionDefinition::FileDepList, stream.release(), false, 0x80);
}
void DwgWriter::writeRevHistory()
{
    if (_fileHeader->version() < ACadVersion::AC1018)
        return;
    std::stringstream *stream = new std::stringstream();
    unsigned int v = 0;
    stream->write((char *) &v, sizeof(v));
    stream->write((char *) &v, sizeof(v));
    stream->write((char *) &v, sizeof(v));
    _fileHeaderWriter->addSection(DwgSectionDefinition::RevHistory, stream, true);
}
void DwgWriter::writeAuxHeader()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    std::unique_ptr<DwgAuxHeaderWriter> writer =
            std::make_unique<DwgAuxHeaderWriter>(stream.get(), _encoding, _document->header());
    writer->write();

    _fileHeaderWriter->addSection(DwgSectionDefinition::AuxHeader, stream.release(), true);
}
void DwgWriter::writeObjects()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    std::unique_ptr<DwgObjectWriter> writer =
            std::make_unique<DwgObjectWriter>(stream.get(), _document, _encoding, false);
    writer->write();

    _handlesMap = writer->handleMap();

    _fileHeaderWriter->addSection(DwgSectionDefinition::AcDbObjects, stream.release(), true);
}

void DwgWriter::writeObjFreeSpace()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    StreamWrapper writer(stream.get());

    //Int32	4	0
    writer.write<int>(0);
    //UInt32	4	Approximate number of objects in the drawing(number of handles).
    writer.write<unsigned int>((unsigned int) _handlesMap.size());

    //Julian datetime	8	If version > R14 then system variable TDUPDATE otherwise TDUUPDATE.
    if (_version >= ACadVersion::AC1015)
    {
        int jdate;
        int mili;
        CadUtils::DateToJulian(_document->header()->universalUpdateDateTime(), jdate, mili);
        writer.write<int>(jdate);
        writer.write<int>(mili);
    }
    else
    {
        int jdate;
        int mili;
        CadUtils::DateToJulian(_document->header()->updateDateTime(), jdate, mili);
        writer.write<int>(jdate);
        writer.write<int>(mili);
    }

    //UInt32	4	Offset of the objects section in the stream.
    writer.write<unsigned int>(0);//It may be the cause of failure for version AC1024

    //UInt8	1	Number of 64 - bit values that follow(ODA writes 4).
    writer.write<unsigned char>(4);
    //UInt32	4	ODA writes 0x00000032
    writer.write<unsigned int>(0x00000032);
    //UInt32	4	ODA writes 0x00000000
    writer.write<unsigned int>(0x00000000);
    //UInt32	4	ODA writes 0x00000064
    writer.write<unsigned int>(0x00000064);
    //UInt32	4	ODA writes 0x00000000
    writer.write<unsigned int>(0x00000000);
    //UInt32	4	ODA writes 0x00000200
    writer.write<unsigned int>(0x00000200);
    //UInt32	4	ODA writes 0x00000000
    writer.write<unsigned int>(0x00000000);
    //UInt32	4	ODA writes 0xffffffff
    writer.write<unsigned int>(0xffffffff);
    //UInt32	4	ODA writes 0x00000000
    writer.write<unsigned int>(0x00000000);

    _fileHeaderWriter->addSection(DwgSectionDefinition::ObjFreeSpace, stream.release(), true);
}

void DwgWriter::writeTemplate()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    StreamWrapper writer(stream.get());

    //Int16	2	Template description string length in bytes(the ODA always writes 0 here).
    writer.write<short>(0);
    //UInt16	2	MEASUREMENT system variable(0 = English, 1 = Metric).
    writer.write<unsigned short>((unsigned short) 1);

    _fileHeaderWriter->addSection(DwgSectionDefinition::Template, stream.release(), true);
}

void DwgWriter::writeHandles()
{
    std::unique_ptr<std::stringstream> stream = std::make_unique<std::stringstream>();
    std::unique_ptr<DwgHandleWriter> writer = std::make_unique<DwgHandleWriter>(_version, stream.get(), _handlesMap);
    writer->write(_fileHeaderWriter->handleSectionOffset());

    _fileHeaderWriter->addSection(DwgSectionDefinition::Handles, stream.release(), true);
}

}// namespace dwg
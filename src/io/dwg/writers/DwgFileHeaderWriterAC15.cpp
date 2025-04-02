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

#include <sstream>
#include <array>
#include <dwg/CadDocument.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/DwgFileHeaderWriterAC15_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>

namespace dwg {

std::vector<unsigned char> DwgFileHeaderWriterAC15::_endSentinel = {0x95, 0xA0, 0x4E, 0x28, 0x99, 0x82, 0x1A, 0xE5,
                                                                    0x5E, 0x41, 0xE0, 0x5F, 0x9D, 0x3A, 0x4D, 0x00};

int DwgFileHeaderWriterAC15::handleSectionOffset() const
{
    size_t offset = fileHeaderSize();

    // for (auto &&item: _records)
    // {
    //     if (item.first == DwgSectionDefinition::AcDbObjects)
    //         break;

    //     offset += istream_length(item.second.second);
    // }

    return (int) offset;
}

int DwgFileHeaderWriterAC15::fileHeaderSize() const { return 0x61; }

DwgFileHeaderWriterAC15::DwgFileHeaderWriterAC15(std::ofstream *stream, Encoding encoding, CadDocument *model)
    : DwgFileHeaderWriterBase(stream, encoding, model)
{
    _records = {
            {      DwgSectionDefinition::Header,    {DwgSectionLocatorRecord(0), nullptr}},
            {     DwgSectionDefinition::Classes,    {DwgSectionLocatorRecord(1), nullptr}},
            {DwgSectionDefinition::ObjFreeSpace,    {DwgSectionLocatorRecord(3), nullptr}},
            {    DwgSectionDefinition::Template,    {DwgSectionLocatorRecord(4), nullptr}},
            {   DwgSectionDefinition::AuxHeader,    {DwgSectionLocatorRecord(5), nullptr}},
            { DwgSectionDefinition::AcDbObjects, {DwgSectionLocatorRecord(NULL), nullptr}},
            {     DwgSectionDefinition::Handles,    {DwgSectionLocatorRecord(2), nullptr}},
            {     DwgSectionDefinition::Preview, {DwgSectionLocatorRecord(NULL), nullptr}},
    };
}

void DwgFileHeaderWriterAC15::addSection(const std::string &name, std::ostream *stream, bool isCompressed,
                                         int decompsize)
{
    // _records[name].first.Size = ostream_length(stream);
    // _records[name] = {_records[name].first, stream};
}

void DwgFileHeaderWriterAC15::writeFile()
{
    setRecordSeekers();
    writeFileHeader();
    writeRecordStreams();
}

void DwgFileHeaderWriterAC15::setRecordSeekers()
{
    // long currOffset = fileHeaderSize();
    // for (auto it = _records.begin(); it != _records.end(); ++it)
    // {
    //     it->second.first.setSeeker(currOffset);
    //     currOffset += ostream_length(it->second.second);
    // }
}


void DwgFileHeaderWriterAC15::writeFileHeader()
{
    // std::ostringstream memoryStream;

    // //0x00	6	“ACXXXX” version string
    // IDwgStreamWriter *writer = DwgStreamWriterBase::GetStreamWriter(_version, &memoryStream, _encoding);
    // writer->WriteBytes(
    //         Encoding::ASCII.GetBytes(_document.Header.VersionString));
    // //The next 7 starting at offset 0x06 are to be six bytes of 0
    // //(in R14, 5 0’s and the ACADMAINTVER variable) and a byte of 1.
    // writer->WriteBytes({0, 0, 0, 0, 0, 15, 1});
    // //At 0x0D is a seeker (4 byte long absolute address) for the beginning sentinel of the image data.
    // writer->WriteRawLong(
    //         _records[DwgSectionDefinition::Preview].first.Seeker);

    // writer->WriteByte(0x1B);
    // writer->WriteByte(0x19);

    // //Bytes at 0x13 and 0x14 are a raw short indicating the value of the code page for this drawing file.

    // writer->WriteBytes(
    //         LittleEndianConverter::Instance()->GetBytes(getFileCodePage()));
    // writer->WriteBytes(LittleEndianConverter::Instance()->GetBytes(6));

    // foreach (var item in this._records.Values.Select(r = > r.Item1))
    // {
    //     if (!item.Number.HasValue) continue;

    //     this.writeRecord(writer, item);
    // }

    // //CRC
    // writer->WriteSpearShift();
    // writer->WriteRawShort((short) CRC8StreamHandler.GetCRCValue(
    //         0xC0C1, memoryStream.GetBuffer(), 0L, memoryStream.Length));

    // //0x95,0xA0,0x4E,0x28,0x99,0x82,0x1A,0xE5,0x5E,0x41,0xE0,0x5F,0x9D,0x3A,0x4D,0x00
    // writer->WriteBytes(_endSentinel);

    // _stream->write(memoryStream.str().c_str(), memoryStream.str().size());
    // delete writer;
}

void DwgFileHeaderWriterAC15::writeRecord(IDwgStreamWriter *writer, const DwgSectionLocatorRecord &record)
{
    //Record number (raw byte) | Seeker (raw long) | Size (raw long)
    // writer->WriteByte((unsigned char) record.Number.Value);
    // writer->WriteRawLong(record.Seeker);
    // writer->WriteRawLong(record.Size);
}

void DwgFileHeaderWriterAC15::writeRecordStreams()
{
    for (auto it = _records.begin(); it != _records.end(); ++it)
    {
        auto ss = it->second.second;
        if (ss)
        {
            std::string data = ss->str();
            std::size_t len = data.size();
            _stream->write(data.c_str(), len);
        }
    }
}

}// namespace dwg
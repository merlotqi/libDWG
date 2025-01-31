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


#include "DwgClassesWriter.h"

namespace dwg {
namespace io {


std::string DwgClassesWriter::SectionName() const
{
    return DwgSectionDefinition::Classes;
}

DwgClassesWriter::DwgClassesWriter(std::ostream *stream, CadDocument *document,
                                   Encoding encoding)
    : DwgSectionIO(document->Header().Version)
{
    _document = document;
    _startWriter =
            DwgStreamWriterBase.GetStreamWriter(_version, stream, encoding);

    _writer = DwgStreamWriterBase::GetStreamWriter(_version, &_sectionStream,
                                                   encoding);

    _startSentinel = {0x8D, 0xA1, 0xC4, 0xB8, 0xC4, 0xA9, 0xF8, 0xC5,
                      0xC0, 0xDC, 0xF4, 0x5F, 0xE7, 0xCF, 0xB6, 0x8A};
    _endSentinel = {0x72, 0x5E, 0x3B, 0x47, 0x3B, 0x56, 0x07, 0x3A,
                    0x3F, 0x23, 0x0B, 0xA0, 0x18, 0x30, 0x49, 0x75};
}

void DwgClassesWriter::Write()
{
    if (R2007Plus) { _writer->SavePositonForSize(); }

    short maxClassNumber = 0;
    if (_document.Classes.Any())
    {
        maxClassNumber = _document.Classes.Max(c = > c.ClassNumber);
    }

    if (R2004Plus)
    {
        //BS : Maxiumum class number
        _writer->WriteBitShort(maxClassNumber);
        //RC: 0x00
        _writer->WriteByte(0);
        //RC: 0x00
        _writer->WriteByte(0);
        //B : true
        _writer->WriteBit(true);
    }

    foreach (var c in _document.Classes)
    {
        //BS : classnum
        _writer->WriteBitShort(c.ClassNumber);
        //BS : version – in R14, becomes a flag indicating whether objects can be moved, edited, etc.
        _writer->WriteBitShort((short) c.ProxyFlags);
        //TV : appname
        _writer->WriteVariableText(c.ApplicationName);
        //TV: cplusplusclassname
        _writer->WriteVariableText(c.CppClassName);
        //TV : classdxfname
        _writer->WriteVariableText(c.DxfName);
        //B : wasazombie
        _writer->WriteBit(c.WasZombie);
        //BS : itemclassid -- 0x1F2 for classes which produce entities, 0x1F3 for classes which produce objects.
        _writer->WriteBitShort(c.ItemClassId);

        if (R2004Plus)
        {
            //BL : Number of objects created of this type in the current DB(DXF 91).
            _writer->WriteBitLong(c.InstanceCount);
            //BS : Dwg Version
            _writer->WriteBitShort((short) _document.Header.Version);
            //BS : Maintenance release version.
            _writer->WriteBitShort(_document.Header.MaintenanceVersion);
            //BL : Unknown(normally 0L)
            _writer->WriteBitLong(0);
            //BL : Unknown(normally 0L)
            _writer->WriteBitLong(0);
        }
    }

    _writer->WriteSpearShift();

    writeSizeAndCrc();
}
void DwgClassesWriter::writeSizeAndCrc()
{
    //SN : 0x8D 0xA1 0xC4 0xB8 0xC4 0xA9 0xF8 0xC5 0xC0 0xDC 0xF4 0x5F 0xE7 0xCF 0xB6 0x8A
    _startWriter.WriteBytes(_startSentinel);

    CRC8StreamHandler crc = new CRC8StreamHandler(_startWriter.Stream, 0xC0C1);
    StreamIO swriter = new StreamIO(crc);

    //RL : size of class data area.
    swriter.Write((int) _sectionStream.Length);

    if (_document.Header.Version >= ACadVersion.AC1024 &&
                _document.Header.MaintenanceVersion > 3 ||
        _document.Header.Version > ACadVersion.AC1027)
    {
        //RL : unknown, possibly the high 32 bits of a 64-bit size?
        swriter.Write((int) 0);//TODO: Define endian order!!!
    }

    //Write the section
    swriter.Stream.Write(_sectionStream.GetBuffer(), 0,
                         (int) _sectionStream.Length);

    //RS: CRC
    _startWriter.WriteRawShort(crc.Seed);

    _startWriter.WriteBytes(_endSentinel);

    if (R2004Plus)
    {
        //For R18 and later 8 unknown bytes follow. The ODA writes 0 bytes.
        _startWriter.WriteRawLong(0);
        _startWriter.WriteRawLong(0);
    }
}


}// namespace io
}// namespace dwg
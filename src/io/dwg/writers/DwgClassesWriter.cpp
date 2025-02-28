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
#include <dwg/classes/DxfClass.h>
#include <dwg/classes/DxfClassCollection.h>
#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/CRC8StreamHandler_p.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/DwgClassesWriter_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>
#include <dwg/io/dwg/writers/IDwgStreamWriter_p.h>

namespace dwg {

DwgClassesWriter::DwgClassesWriter(std::ostream *stream, CadDocument *document, Encoding encoding)
    : DwgSectionIO(document->header()->version())
{
    _document = document;
    _startWriter = DwgStreamWriterBase::GetStreamWriter(_version, stream, encoding);

    _sectionStream = std::make_unique<std::stringstream>();
    _writer = DwgStreamWriterBase::GetStreamWriter(_version, _sectionStream.get(), encoding);

    _startSentinel = {0x8D, 0xA1, 0xC4, 0xB8, 0xC4, 0xA9, 0xF8, 0xC5, 0xC0, 0xDC, 0xF4, 0x5F, 0xE7, 0xCF, 0xB6, 0x8A};
    _endSentinel = {0x72, 0x5E, 0x3B, 0x47, 0x3B, 0x56, 0x07, 0x3A, 0x3F, 0x23, 0x0B, 0xA0, 0x18, 0x30, 0x49, 0x75};
}

DwgClassesWriter::~DwgClassesWriter()
{
    delete _startWriter;
    _startWriter = nullptr;

    delete _writer;
    _writer = nullptr;
}

std::string DwgClassesWriter::sectionName() const { return DwgSectionDefinition::Classes; }

void DwgClassesWriter::write()
{
    if (R2007Plus) { _writer->savePositonForSize(); }

    short maxClassNumber = 0;
    auto classes = _document->classes();
    if (classes)
    {
        for (auto it = classes->begin(); it != classes->end(); ++it)
        {
            if (it->second->classNumber() >= maxClassNumber) { maxClassNumber = it->second->classNumber(); }
        }
    }

    if (R2004Plus)
    {
        //BS : Maxiumum class number
        _writer->writeBitShort(maxClassNumber);
        //RC: 0x00
        _writer->writeByte(0);
        //RC: 0x00
        _writer->writeByte(0);
        //B : true
        _writer->writeBit(true);
    }

    for (auto it = classes->begin(); it != classes->end(); ++it)
    {
        //BS : classnum
        _writer->writeBitShort(it->second->classNumber());
        //BS : version - in R14, becomes a flag indicating whether objects can be moved, edited, etc.
        _writer->writeBitShort((short) it->second->proxyFlags());
        //TV : appname
        _writer->writeVariableText(it->second->applicationName());
        //TV: cplusplusclassname
        _writer->writeVariableText(it->second->cppClassName());
        //TV : classdxfname
        _writer->writeVariableText(it->second->dxfName());
        //B : wasazombie
        _writer->writeBit(it->second->wasZombie());
        //BS : itemclassid -- 0x1F2 for classes which produce entities, 0x1F3 for classes which produce objects.
        _writer->writeBitShort(it->second->itemClassId());

        if (R2004Plus)
        {
            //BL : Number of objects created of this type in the current DB(DXF 91).
            _writer->writeBitLong(it->second->instanceCount());
            //BS : Dwg Version
            _writer->writeBitShort((short) _document->header()->version());
            //BS : Maintenance release version.
            _writer->writeBitShort(_document->header()->maintenanceVersion());
            //BL : Unknown(normally 0L)
            _writer->writeBitLong(0);
            //BL : Unknown(normally 0L)
            _writer->writeBitLong(0);
        }
    }

    _writer->writeSpearShift();

    writeSizeAndCrc();
}
void DwgClassesWriter::writeSizeAndCrc()
{
    //SN : 0x8D 0xA1 0xC4 0xB8 0xC4 0xA9 0xF8 0xC5 0xC0 0xDC 0xF4 0x5F 0xE7 0xCF 0xB6 0x8A
    _startWriter->writeBytes(_startSentinel);

    CRC8OutputStreamHandler swriter(_startWriter->stream(), 0xC0C1);

    //RL : size of class data area.
    swriter.write((int) _sectionStream->str().length());

    if (_document->header()->version() >= ACadVersion::AC1024 && _document->header()->maintenanceVersion() > 3 ||
        _document->header()->version() > ACadVersion::AC1027)
    {
        //RL : unknown, possibly the high 32 bits of a 64-bit size?
        swriter.write((int) 0);//TODO: Define endian order!!!
    }

    //Write the section
    std::string buf = _sectionStream->str();
    swriter.write(std::vector<unsigned char>(buf.begin(), buf.end()), 0, (int) buf.length());

    //RS: CRC
    _startWriter->writeRawShort(swriter.seed());

    _startWriter->writeBytes(_endSentinel);

    if (R2004Plus)
    {
        //For R18 and later 8 unknown bytes follow. The ODA writes 0 bytes.
        _startWriter->writeRawLong(0);
        _startWriter->writeRawLong(0);
    }
}

}// namespace dwg
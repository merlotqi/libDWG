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

#include <dwg/header/CadHeader.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/writers/DwgAuxHeaderWriter_p.h>
#include <dwg/io/dwg/writers/DwgStreamWriterBase_p.h>

namespace dwg {

DwgAuxHeaderWriter::DwgAuxHeaderWriter(std::ostream *stream, Encoding encoding, CadHeader *header)
    : DwgSectionIO(header->version())
{
    _header = header;
    _writer = DwgStreamWriterBase::GetStreamWriter(_version, stream, encoding);
}

DwgAuxHeaderWriter::~DwgAuxHeaderWriter()
{
    delete _writer;
    _writer = nullptr;
    _header = nullptr;
}

std::string DwgAuxHeaderWriter::sectionName() const { return DwgSectionDefinition::AuxHeader; }

void DwgAuxHeaderWriter::write()
{
    //RC: 0xff 0x77 0x01
    _writer->writeByte(0xFF);
    _writer->writeByte(0x77);
    _writer->writeByte(0x01);

    //RS: DWG version:
    //AC1010 = 17,
    //AC1011 = 18,
    //AC1012 = 19,
    //AC1013 = 20,
    //AC1014 = 21,
    //AC1015(beta) = 22,
    //AC1015 = 23,
    //AC1018(beta) = 24,
    //AC1018 = 25,
    //AC1021(beta) = 26,
    //AC1021 = 27,
    //AC1024(beta) = 28,
    //AC1024 = 29
    //AC1027(beta) = 30,
    //AC1027 = 31,
    //AC1032(beta) = 32,
    //AC1032 = 33
    _writer->writeRawShort((short) _version);

    //RS: Maintenance version
    _writer->writeRawShort(_header->maintenanceVersion());

    //RL: Number of saves (starts at 1)
    _writer->writeRawLong(1);
    //RL: -1
    _writer->writeRawLong(-1);

    //RS: Number of saves part 1( = Number of saves – number of saves part 2)
    _writer->writeRawShort(1);
    //RS: Number of saves part 2( = Number of saves – 0x7fff if Number of saves > 0x7fff, otherwise 0)
    _writer->writeRawShort(0);

    //RL: 0
    _writer->writeRawLong(0);
    //RS: DWG version string
    _writer->writeRawShort((short) _version);
    //RS : Maintenance version
    _writer->writeRawShort((short) _header->maintenanceVersion());
    //RS: DWG version string
    _writer->writeRawShort((short) _version);
    //RS : Maintenance version
    _writer->writeRawShort((short) _header->maintenanceVersion());

    //RS: 0x0005
    _writer->writeRawShort(0x5);
    //RS: 0x0893
    _writer->writeRawShort(2195);
    //RS: 0x0005
    _writer->writeRawShort(5);
    //RS: 0x0893
    _writer->writeRawShort(2195);
    //RS: 0x0000
    _writer->writeRawShort(0);
    //RS: 0x0001
    _writer->writeRawShort(1);
    //RL: 0x0000
    _writer->writeRawLong(0);
    //RL: 0x0000
    _writer->writeRawLong(0);
    //RL: 0x0000
    _writer->writeRawLong(0);
    //RL: 0x0000
    _writer->writeRawLong(0);
    //RL: 0x0000
    _writer->writeRawLong(0);

    //TD: TDCREATE(creation datetime)
    _writer->write8BitJulianDate(_header->createDateTime());

    //TD: TDUPDATE(update datetime)
    _writer->write8BitJulianDate(_header->updateDateTime());

    int handseed = -1;
    if (_header->handleSeed() <= 0x7FFFFFFF) { handseed = (int) _header->handleSeed(); }

    //RL: HANDSEED(Handle seed) if < 0x7fffffff, otherwise - 1.
    _writer->writeRawLong(handseed);
    //RL : Educational plot stamp(default value is 0)
    _writer->writeRawLong(0);
    //RS: 0
    _writer->writeRawShort(0);
    //RS: Number of saves part 1 – number of saves part 2
    _writer->writeRawShort(1);
    //RL: 0
    _writer->writeRawLong(0);
    //RL: 0
    _writer->writeRawLong(0);
    //RL: 0
    _writer->writeRawLong(0);
    //RL: Number of saves
    _writer->writeRawLong(1);
    //RL : 0
    _writer->writeRawLong(0);
    //RL: 0
    _writer->writeRawLong(0);
    //RL: 0
    _writer->writeRawLong(0);
    //RL: 0
    _writer->writeRawLong(0);

    //R2018 +
    if (R2018Plus)
    {
        //RS : 0
        _writer->writeRawShort(0);
        //RS : 0
        _writer->writeRawShort(0);
        //RS : 0
        _writer->writeRawShort(0);
    }
}

}// namespace dwg
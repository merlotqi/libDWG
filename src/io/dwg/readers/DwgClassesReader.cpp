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

#include <dwg/classes/DxfClass.h>
#include <dwg/classes/DxfClassCollection.h>
#include <dwg/io/dwg/fileheaders/DwgSectionDefinition_p.h>
#include <dwg/io/dwg/readers/DwgClassesReader_p.h>
#include <dwg/io/dwg/readers/IDwgStreamReader_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderBase_p.h>
#include <dwg/io/dwg/readers/DwgMergedReader_p.h>
#include <dwg/io/dwg/fileheaders/DwgFileHeader_p.h>

namespace dwg {

DwgClassesReader::DwgClassesReader(ACadVersion version, IDwgStreamReader *sreader, DwgFileHeader *fileheader)
    : DwgSectionIO(version), _sreader(sreader), _fileHeader(fileheader)
{
}

DwgClassesReader::~DwgClassesReader() {}

std::string DwgClassesReader::sectionName() const
{
    return DwgSectionDefinition::Classes;
}

DxfClassCollection *DwgClassesReader::read() 
{
    DxfClassCollection *classes = new DxfClassCollection();

    //SN : 0x8D 0xA1 0xC4 0xB8 0xC4 0xA9 0xF8 0xC5 0xC0 0xDC 0xF4 0x5F 0xE7 0xCF 0xB6 0x8A
    checkSentinel(_sreader, DwgSectionDefinition::StartSentinels[sectionName()]);

    //RL : size of class data area
    long size = _sreader->readRawLong();
    long endSection = _sreader->position() + size;

    //R2010+ (only present if the maintenance version is greater than 3!)
    if (_fileHeader->version() >= ACadVersion::AC1024
        && _fileHeader->acadMaintenanceVersion() > 3
        || _fileHeader->version() > ACadVersion::AC1027)
    {
        //RL : unknown, possibly the high 32 bits of a 64-bit size?
        long unknown = _sreader->readRawLong();
    }

    long flagPos = 0;
    //+R2007 Only:
    if (R2007Plus)
    {
        //Setup readers
        flagPos = _sreader->positionInBits() + _sreader->readRawLong() - 1L;
        long savedOffset = _sreader->positionInBits();
        endSection = _sreader->setPositionByFlag(flagPos);

        _sreader->setPositionInBits(savedOffset);

        //Setup the text reader for versions 2007 and above
        IDwgStreamReader *textReader = DwgStreamReaderBase::GetStreamHandler(_version,
            //Create a copy of the stream
            new StreamIO(_sreader.Stream, true).Stream);
        //Set the position and use the flag
        textReader->setPositionInBits(endSection);

        _sreader = new DwgMergedReader(_sreader, textReader, nullptr);

        //BL: 0x00
        _sreader->readBitLong();
        //B : flag - to find the data string at the end of the section
        _sreader->readBit();
    }

    if (_fileHeader->version() == ACadVersion::AC1018)
    {
        //BS : Maximum class number
        _sreader->readBitShort();
        //RC: 0x00
        _sreader->readRawChar();
        //RC: 0x00
        _sreader->readRawChar();
        //B : true
        _sreader->readBit();
    }

    //We read sets of these until we exhaust the data.
    while (getCurrPos(_sreader) < endSection)
    {
        DxfClass *dxfClass = new DxfClass();
        //BS : classnum
        dxfClass->setClassNumber(_sreader->readBitShort());
        //BS : version – in R14, becomes a flag indicating whether objects can be moved, edited, etc.
        dxfClass->setProxyFlags((ProxyFlags)_sreader->readBitShort());

        //TV : appname
        dxfClass->setApplicationName(_sreader->readVariableText());
        //TV: cplusplusclassname
        dxfClass->setCppClassName(_sreader->readVariableText());
        //TV : classdxfname
        dxfClass->setDxfName(_sreader->readVariableText());

        //B : wasazombie
        dxfClass->setWasZombie(_sreader->readBit());
        //BS : itemclassid -- 0x1F2 for classes which produce entities, 0x1F3 for classes which produce objects.
        dxfClass->setItemClassId(_sreader->readBitShort());
        if (dxfClass->itemClassId() == 0x1F2)
        {
            dxfClass->setIsAnEntity(true);
        }
        else if (dxfClass->itemClassId() == 0x1F3)
        {
            dxfClass->setIsAnEntity(false);
        }
        else
        {
            // this.notify($"Invalid DxfClass id value: {dxfClass.ItemClassId} for {dxfClass.CppClassName}", NotificationType.Error);
        }

        if (R2004Plus)
        {
            //BL : Number of objects created of this type in the current DB(DXF 91).
            dxfClass->setInstanceCount(_sreader->readBitLong());

            //BS : Dwg Version
            dxfClass->setDwgVersion((ACadVersion)_sreader->readBitLong());
            //BS : Maintenance release version.
            dxfClass->setMaintenanceVersion((short)_sreader->readBitLong());

            //BL : Unknown(normally 0L)
            _sreader->readBitLong();
            //BL : Unknown(normally 0L)
            _sreader->readBitLong();
        }

        classes->addOrUpdate(dxfClass);
    }

    if (R2007Plus)
    {
        _sreader->setetPositionInBits(flagPos + 1);
    }

    //RS: CRC
    _sreader->resetShift();

    //0x72,0x5E,0x3B,0x47,0x3B,0x56,0x07,0x3A,0x3F,0x23,0x0B,0xA0,0x18,0x30,0x49,0x75
    checkSentinel(_sreader, DwgSectionDefinition::EndSentinels[sectionName()]);

    return classes;
}

long long DwgClassesReader::getCurrPos(IDwgStreamReader *sreader)
{
    if (R2007Plus)
    {
        return sreader->positionInBits();
    }
    else
    {
        return sreader->position();
    }
}

}// namespace dwg
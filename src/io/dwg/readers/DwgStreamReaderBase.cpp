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

#include <dwg/io/dwg/readers/DwgStreamReaderAC12_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC15_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC18_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC21_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderAC24_p.h>
#include <dwg/io/dwg/readers/DwgStreamReaderBase_p.h>
#include <stdexcept>


namespace dwg {

DwgStreamReaderBase::DwgStreamReaderBase(std::istream *stream, bool resetPosition) {}

DwgStreamReaderBase::~DwgStreamReaderBase() {}

IDwgStreamReader *DwgStreamReaderBase::GetStreamHandler(ACadVersion version, std::istream *stream, Encoding encoding,
                                                        bool resetPosition)
{
    IDwgStreamReader *reader = nullptr;

    switch (version)
    {
        case ACadVersion::Unknown:
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
            throw std::runtime_error("Not supported DWG version");
        case ACadVersion::AC1012:
        case ACadVersion::AC1014:
            reader = new DwgStreamReaderAC12(stream, resetPosition);
            break;
        case ACadVersion::AC1015:
            reader = new DwgStreamReaderAC15(stream, resetPosition);
            break;
        case ACadVersion::AC1018:
            reader = new DwgStreamReaderAC18(stream, resetPosition);
            break;
        case ACadVersion::AC1021:
            reader = new DwgStreamReaderAC21(stream, resetPosition);
            break;
        case ACadVersion::AC1024:
        case ACadVersion::AC1027:
        case ACadVersion::AC1032:
            reader = new DwgStreamReaderAC24(stream, resetPosition);
            break;
        default:
            throw std::runtime_error("Not supported DWG version");
    }

    if (encoding.codePage() != CodePage::Unknown)
    {
        reader->setEncoding(encoding);
    }
    return reader;
}

Encoding DwgStreamReaderBase::encoding() const
{
    return Encoding();
}

void DwgStreamReaderBase::setEncoding(Encoding value) {}

std::istream *DwgStreamReaderBase::stream()
{
    return nullptr;
}

int DwgStreamReaderBase::bitShift() const
{
    return 1;
}

long long DwgStreamReaderBase::position() const
{
    return 0LL;
}

void DwgStreamReaderBase::setBitShift(int) {}

void DwgStreamReaderBase::setPosition(long long) {}

bool DwgStreamReaderBase::isEmpty() const
{
    return false;
}

void DwgStreamReaderBase::setEmpty(bool) {}

unsigned char DwgStreamReaderBase::readByte()
{
    return (unsigned char) (1);
}

short DwgStreamReaderBase::readShort()
{
    return short(0);
}

long long DwgStreamReaderBase::setPositionByFlag(long long)
{
    return 0LL;
}

int DwgStreamReaderBase::readInt()
{
    return 0;
}

unsigned int DwgStreamReaderBase::readUInt()
{
    return 0;
}

double DwgStreamReaderBase::readDouble()
{
    return 0.0;
}

std::vector<unsigned char> DwgStreamReaderBase::readBytes(int length)
{
    return std::vector<unsigned char>();
}

bool DwgStreamReaderBase::readBit()
{
    return false;
}

short DwgStreamReaderBase::readBitAsShort()
{
    return short(0);
}

unsigned char DwgStreamReaderBase::read2Bits()
{
    return (unsigned char) (0);
}

short DwgStreamReaderBase::readBitShort()
{
    return short(0);
}

bool DwgStreamReaderBase::readBitShortAsBool()
{
    return false;
}

int DwgStreamReaderBase::readBitLong()
{
    return 0;
}

long long DwgStreamReaderBase::readBitLongLong()
{
    return 0LL;
}

double DwgStreamReaderBase::readBitDouble()
{
    return 0.0;
}

XY DwgStreamReaderBase::read2BitDouble()
{
    return XY(0, 0);
}

XYZ DwgStreamReaderBase::read3BitDouble()
{
    return XYZ(0, 0, 0);
}

char DwgStreamReaderBase::readRawChar()
{
    return char(0);
}

long long DwgStreamReaderBase::readRawLong()
{
    return 0LL;
}

unsigned long long DwgStreamReaderBase::readRawULong()
{
    return 0ULL;
}

XYZ DwgStreamReaderBase::read2RawDouble()
{
    return XYZ(0, 0, 0);
}

XYZ DwgStreamReaderBase::read3RawDouble()
{
    return XYZ(0, 0, 0);
}

unsigned long long DwgStreamReaderBase::readModularChar()
{
    return 0ULL;
}

int DwgStreamReaderBase::readSignedModularChar()
{
    return 0;
}

int DwgStreamReaderBase::readModularShort()
{
    return 0;
}

unsigned long long DwgStreamReaderBase::handleReference(unsigned long long referenceHandle)
{
    return 0ULL;
}

unsigned long long DwgStreamReaderBase::handleReference(unsigned long long referenceHandle, DwgReferenceType &reference)
{
    return 0ULL;
}

std::string DwgStreamReaderBase::readTextUtf8()
{
    return std::string();
}

std::string DwgStreamReaderBase::readVariableText()
{
    return std::string();
}

std::vector<unsigned char> DwgStreamReaderBase::readSentinel()
{
    return std::vector<unsigned char>();
}

XY DwgStreamReaderBase::read2BitDoubleWithDefault(const XY &)
{
    return XY(0, 0);
}

XYZ DwgStreamReaderBase::read3BitDoubleWithDefault(const XYZ &)
{
    return XYZ(0, 0, 0);
}

Color DwgStreamReaderBase::readCmColor()
{
    return Color(short(0));
}

Color DwgStreamReaderBase::readEnColor(Transparency &, bool &flag)
{
    return Color(short(0));
}

Color DwgStreamReaderBase::readColorByIndex()
{
    return Color(short(0));
}

ObjectType DwgStreamReaderBase::readObjectType()
{
    return ObjectType::UNLISTED;
}

XYZ DwgStreamReaderBase::readBitExtrusion()
{
    return XYZ(0, 0, 0);
}

double DwgStreamReaderBase::readBitDoubleWithDefault(double def)
{
    return 0.0;
}

double DwgStreamReaderBase::readBitThickness()
{
    return 0.0;
}

DateTime DwgStreamReaderBase::read8BitJulianDate()
{
    return DateTime();
}

DateTime DwgStreamReaderBase::readDateTime()
{
    return DateTime();
}

double DwgStreamReaderBase::readTimeSpan()
{
    return 0.0;
}

long long DwgStreamReaderBase::positionInBits()
{
    return 0LL;
}

void DwgStreamReaderBase::setPositionInBits(long long positon) {}

void DwgStreamReaderBase::advanceByte() {}

void DwgStreamReaderBase::advance(int offset) {}

unsigned short DwgStreamReaderBase::resetShift()
{
    return (unsigned short) (0);
}

std::string DwgStreamReaderBase::readString(size_t length, Encoding encoding)
{
    return std::string();
}

}// namespace dwg
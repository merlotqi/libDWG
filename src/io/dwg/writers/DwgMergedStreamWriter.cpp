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

#include <dwg/io/dwg/writers/DwgMergedStreamWriter_p.h>
#include <dwg/utils/StreamWrapper.h>

namespace dwg {

DwgMergedStreamWriter::DwgMergedStreamWriter(std::iostream *stream, IDwgStreamWriter *main, IDwgStreamWriter *textwriter,
                                             IDwgStreamWriter *handlewriter)
    : _stream(stream), _main(main), _textWriter(textwriter), _handleWriter(handlewriter), _savedPosition(0),
      _savedPositionInBits(0), _positionInBits(0)
{
}

DwgMergedStreamWriter::~DwgMergedStreamWriter() {}

std::iostream *DwgMergedStreamWriter::stream()
{
    return _stream;
}

Encoding DwgMergedStreamWriter::encoding()
{
    return _main->encoding();
}

IDwgStreamWriter *DwgMergedStreamWriter::main()
{
    return _main;
}

long long DwgMergedStreamWriter::positionInBits() const
{
    return _positionInBits;
}

long long DwgMergedStreamWriter::savedPositionInBits() const
{
    return _savedPositionInBits;
}

void DwgMergedStreamWriter::writeBytes(const std::vector<unsigned char> &bytes)
{
    _main->writeBytes(bytes);
}

void DwgMergedStreamWriter::writeBytes(const std::vector<unsigned char> &bytes, std::size_t offset, std::size_t length)
{
    _main->writeBytes(bytes, offset, length);
}

void DwgMergedStreamWriter::writeInt(int value)
{
    _main->writeInt(value);
}

void DwgMergedStreamWriter::writeObjectType(short value)
{
    _main->writeObjectType(value);
}

void DwgMergedStreamWriter::writeObjectType(ObjectType value)
{
    _main->writeObjectType(value);
}

void DwgMergedStreamWriter::writeRawLong(long long value)
{
    _main->writeRawLong(value);
}

void DwgMergedStreamWriter::writeBitDouble(double value)
{
    _main->writeBitDouble(value);
}

void DwgMergedStreamWriter::writeBitLong(int value)
{
    _main->writeBitLong(value);
}

void DwgMergedStreamWriter::writeBitLongLong(long long value)
{
    _main->writeBitLongLong(value);
}

void DwgMergedStreamWriter::writeVariableText(const std::string &value)
{
    _main->writeVariableText(value);
}

void DwgMergedStreamWriter::writeTextUtf8(const std::string &value)
{
    _main->writeTextUtf8(value);
}

void DwgMergedStreamWriter::writeBit(bool value)
{
    _main->writeBit(value);
}

void DwgMergedStreamWriter::write2Bits(unsigned char value)
{
    _main->write2Bits(value);
}

void DwgMergedStreamWriter::writeBitShort(short value)
{
    _main->writeBitShort(value);
}

void DwgMergedStreamWriter::writeDateTime(const DateTime &value)
{
    _main->writeDateTime(value);
}

void DwgMergedStreamWriter::write8BitJulianDate(const DateTime &value)
{
    _main->write8BitJulianDate(value);
}

void DwgMergedStreamWriter::writeTimeSpan(const Timespan &value)
{
    _main->writeTimeSpan(value);
}

void DwgMergedStreamWriter::writeCmColor(const Color &value) {}

void DwgMergedStreamWriter::writeEnColor(const Color &color, const Transparency &transparency) {}

void DwgMergedStreamWriter::writeEnColor(const Color &color, const Transparency &transparency, bool isBookColor) {}

void DwgMergedStreamWriter::write2BitDouble(const XY &value) {}

void DwgMergedStreamWriter::write3BitDouble(const XYZ &value) {}

void DwgMergedStreamWriter::write2RawDouble(const XY &value) {}

void DwgMergedStreamWriter::writeByte(unsigned char value) {}

void DwgMergedStreamWriter::handleReference(IHandledCadObject *cadObject)
{
    _handleWriter->handleReference(cadObject);
}

void DwgMergedStreamWriter::handleReference(DwgReferenceType type, IHandledCadObject *cadObject)
{
    _handleWriter->handleReference(type, cadObject);
}

void DwgMergedStreamWriter::handleReference(unsigned long long handle)
{
    _handleWriter->handleReference(handle);
}

void DwgMergedStreamWriter::handleReference(DwgReferenceType type, unsigned long long handle)
{
    _handleWriter->handleReference(type, handle);
}

void DwgMergedStreamWriter::writeSpearShift() 
{
    long long mainSizeBits = _main->positionInBits();
    long long textSizeBits = _textWriter->positionInBits();

    _main->writeSpearShift();

    if (_savedPosition)
    {
        int mainTextTotalBits = (int) (mainSizeBits + textSizeBits + 1);
        if (textSizeBits > 0)
        {
            mainTextTotalBits += 16;
            if (textSizeBits >= 0x8000)
            {
                mainTextTotalBits += 16;
                if (textSizeBits >= 0x40000000)
                {
                    mainTextTotalBits += 16;
                }
            }
        }

		_main->setPositionInBits(positionInBits());
        //Write the total size in bits
        _main->writeRawLong(mainTextTotalBits);
        _main->writeShiftValue();
    }

    if (textSizeBits > 0)
    {
        _textWriter->writeSpearShift();

        StreamWrapper wrapper(_textWriter->stream());
        _main->writeBytes(wrapper.buffer(), 0, (int) wrapper.length());
        _main->writeSpearShift();
        _main->setPositionInBits(mainSizeBits + textSizeBits);
        _main->setPositionByFlag(textSizeBits);
        _main->writeBit(true);
    }
    else
    {
        _main->writeBit(false);
    }

    _handleWriter->writeSpearShift();
    _savedPositionInBits = _main->positionInBits();
    StreamWrapper wrapper(_handleWriter->stream());
    _main->writeBytes(wrapper.buffer(), 0, (int) wrapper.length());
    _main->writeSpearShift();
}

void DwgMergedStreamWriter::writeRawShort(short value)
{
    _main->writeRawShort(value);
}

void DwgMergedStreamWriter::writeRawUShort(unsigned short value)
{
    _main->writeRawUShort(value);
}

void DwgMergedStreamWriter::writeRawDouble(double value) 
{
    _main->writeRawDouble(value);
}

void DwgMergedStreamWriter::writeBitThickness(double thickness) 
{
    _main->writeBitThickness(thickness);
}

void DwgMergedStreamWriter::writeBitExtrusion(const XYZ &normal) 
{
    _main->writeBitExtrusion(normal);
}

void DwgMergedStreamWriter::writeBitDoubleWithDefault(double def, double value) 
{
    _main->writeBitDoubleWithDefault(def, value);
}

void DwgMergedStreamWriter::write2BitDoubleWithDefault(const XY &def, const XY &value) 
{
    _main->write2BitDoubleWithDefault(def, value);
}

void DwgMergedStreamWriter::write3BitDoubleWithDefault(const XYZ &def, const XYZ &value) 
{
    _main->write3BitDoubleWithDefault(def, value);
}

void DwgMergedStreamWriter::resetStream() 
{
    _main->resetStream();
    _textWriter->resetStream();
    _handleWriter->resetStream();
}

void DwgMergedStreamWriter::savePositonForSize() 
{
    _savedPosition = true;
    _positionInBits = _main->positionInBits();
    //Save this position for the size in bits
    _main->writeRawLong(0);
}

void DwgMergedStreamWriter::setPositionInBits(long long posInBits) 
{
    throw std::runtime_error("Not implemented");
}

void DwgMergedStreamWriter::setPositionByFlag(long long pos) 
{
    throw std::runtime_error("Not implemented");
}

void DwgMergedStreamWriter::writeShiftValue() 
{
    throw std::runtime_error("Not implemented");
}

}// namespace dwg
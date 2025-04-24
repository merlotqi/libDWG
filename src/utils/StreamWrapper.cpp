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

#include <assert.h>
#include <dwg/utils/StreamWrapper.h>
#include <stdexcept>


namespace dwg {

InputStreamWrapper::InputStreamWrapper(std::istream *stream) : _stream(stream), _encoding(Encoding(CodePage::Utf8))
{
    if (!_stream || !_stream->good())
    {
        throw std::bad_alloc();
    }
}

InputStreamWrapper::~InputStreamWrapper() {}

std::istream *InputStreamWrapper::stream()
{
    return _stream;
}

std::size_t InputStreamWrapper::length() const
{
    return 0;
}

std::size_t InputStreamWrapper::pos() const
{
    return 0;
}

void InputStreamWrapper::seek(std::size_t pos) {}

Encoding InputStreamWrapper::encoding() const
{
    return _encoding;
}

void InputStreamWrapper::setEncoding(Encoding encoding)
{
    _encoding = encoding;
}

char InputStreamWrapper::readChar()
{
    char ch;
    _stream->read(&ch, sizeof(ch));
    return ch;
}

unsigned char InputStreamWrapper::readByte()
{
    unsigned char ch;
    _stream->read(reinterpret_cast<char *>(&ch), sizeof(unsigned char));
    return ch;
}

std::vector<unsigned char> InputStreamWrapper::readBytes(std::size_t length)
{
    std::vector<unsigned char> buffer(length, 0);
    _stream->read(reinterpret_cast<char *>(buffer.data()), length);
    return buffer;
}

short InputStreamWrapper::readShort()
{
    return readT<short, LittleEndianConverter>();
}

unsigned short InputStreamWrapper::readUShort()
{
    return readT<unsigned short, LittleEndianConverter>();
}

int InputStreamWrapper::readInt()
{
    return readT<int, LittleEndianConverter>();
}

unsigned int InputStreamWrapper::readUInt()
{
    return readT<unsigned int, LittleEndianConverter>();
}

long long InputStreamWrapper::readLong()
{
    return readT<long long, LittleEndianConverter>();
}

unsigned long long InputStreamWrapper::readULong()
{
    return readT<unsigned long long, LittleEndianConverter>();
}

float InputStreamWrapper::readFloat()
{
    return readT<float, LittleEndianConverter>();
}

double InputStreamWrapper::readDouble()
{
    return readT<double, LittleEndianConverter>();
}

std::string InputStreamWrapper::readString(int length)
{
    return readString(length, _encoding);
}

std::string InputStreamWrapper::readString(int length, Encoding encoding)
{
    std::vector<unsigned char> buffer = readBytes(length);
    return encoding.toUtf8(reinterpret_cast<const char *>(buffer.data()));
}

std::string InputStreamWrapper::readUntil(char match)
{
    return std::string();
}


/* --------------------------- OutputStreamWrapper -------------------------- */

OutputStreamWrapper::OutputStreamWrapper(std::ostream *stream) : _stream(stream) {}

OutputStreamWrapper ::~OutputStreamWrapper() {}

std::ostream *OutputStreamWrapper::stream()
{
    return _stream;
}

std::size_t OutputStreamWrapper::length() const
{
    assert(_stream);
    std::streampos cur = _stream->tellp();
    _stream->seekp(0, std::ios::end);
    std::streampos len = _stream->tellp();
    _stream->seekp(cur);
    return len;
}

std::size_t OutputStreamWrapper::pos() const
{
    return _stream->tellp();
}

void OutputStreamWrapper::seek(std::size_t pos)
{
    _stream->seekp(pos);
}

void OutputStreamWrapper::flush() {}

Encoding OutputStreamWrapper::encoding() const
{
    return _encoding;
}

void OutputStreamWrapper::setEncoding(Encoding encoding)
{
    _encoding = encoding;
}

std::vector<unsigned char> OutputStreamWrapper::buffer()
{
    return std::vector<unsigned char>();
}

void OutputStreamWrapper::write(const std::vector<unsigned char> &buffer, size_t offset, size_t length)
{
    assert(offset >= 0 && length >= 0);
    assert(offset + length <= buffer.size());
    _stream->write(reinterpret_cast<const char *>(buffer.data() + offset), length);
}

void OutputStreamWrapper::write(const std::string &) {}

void OutputStreamWrapper::write(const std::string &, Encoding) {}

void OutputStreamWrapper::writeByte(unsigned char b)
{
    _stream->write(reinterpret_cast<const char *>(&b), 1);
}

}// namespace dwg
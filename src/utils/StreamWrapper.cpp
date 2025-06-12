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
#include <fstream>
#include <sstream>
#include <stdexcept>


namespace dwg {

StreamWrapper::StreamWrapper(std::iostream *stream) : _stream(stream), _encoding(Encoding(CodePage::Utf8))
{
    if (!_stream || !_stream->good())
    {
        throw std::bad_alloc();
    }
}


StreamWrapper::StreamWrapper(const std::vector<unsigned char> &buffer)
{
    _stream = new std::stringstream(std::ios::in | std::ios::out | std::ios::binary);
    _stream->write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    _owned = true;
    _stream->seekp(std::ios::beg);
    _stream->seekg(std::ios::beg);
}

StreamWrapper::StreamWrapper(const StreamWrapper &other)
{
    _stream = other._stream;
    _encoding = other._encoding;
    _owned = other._owned;
}

StreamWrapper &StreamWrapper::operator=(const StreamWrapper &other)
{
    _stream = other._stream;
    _encoding = other._encoding;
    _owned = other._owned;
    return *this;
}

StreamWrapper::~StreamWrapper()
{
    if (_owned)
    {
        delete _stream;
    }
}

StreamWrapper::~StreamWrapper() {}

std::iostream *StreamWrapper::stream()
{
    return _stream;
}

std::streampos StreamWrapper::tell() const
{
    return _stream->tellg();
}

void StreamWrapper::seek(std::streampos pos)
{
    _stream->seekg(pos);
    _stream->seekp(pos);
}

Encoding StreamWrapper::encoding() const
{
    return _encoding;
}

void StreamWrapper::setEncoding(Encoding encoding)
{
    _encoding = encoding;
}

char StreamWrapper::readChar()
{
    char ch;
    _stream->read(&ch, sizeof(ch));
    _stream->seekp(_stream->tellg());
    return ch;
}

unsigned char StreamWrapper::readByte()
{
    unsigned char ch;
    _stream->read(reinterpret_cast<char *>(&ch), sizeof(unsigned char));
    _stream->seekp(_stream->tellg());
    return ch;
}

std::vector<unsigned char> StreamWrapper::readBytes(std::size_t length)
{
    std::vector<unsigned char> buffer(length, 0);
    _stream->read(reinterpret_cast<char *>(buffer.data()), length);
    _stream->seekp(_stream->tellg());
    return buffer;
}

short StreamWrapper::readShort()
{
    return readT<short, LittleEndianConverter>();
}

unsigned short StreamWrapper::readUShort()
{
    return readT<unsigned short, LittleEndianConverter>();
}

int StreamWrapper::readInt()
{
    return readT<int, LittleEndianConverter>();
}

unsigned int StreamWrapper::readUInt()
{
    return readT<unsigned int, LittleEndianConverter>();
}

long long StreamWrapper::readLong()
{
    return readT<long long, LittleEndianConverter>();
}

unsigned long long StreamWrapper::readULong()
{
    return readT<unsigned long long, LittleEndianConverter>();
}

float StreamWrapper::readFloat()
{
    return readT<float, LittleEndianConverter>();
}

double StreamWrapper::readDouble()
{
    return readT<double, LittleEndianConverter>();
}

std::string StreamWrapper::readString(int length)
{
    return readString(length, _encoding);
}

std::string StreamWrapper::readString(int length, Encoding encoding)
{
    std::vector<unsigned char> buffer = readBytes(length);
    return encoding.toUtf8(reinterpret_cast<const char *>(buffer.data()));
}

std::string StreamWrapper::readUntil(char match)
{
    return std::string();
}

void StreamWrapper::flush()
{
    std::fstream *fs = dynamic_cast<std::fstream *>(_stream);
    if (fs)
    {
        fs->flush();
    }
}

std::vector<unsigned char> StreamWrapper::buffer() const
{
    return std::vector<unsigned char>();
}

void StreamWrapper::write(const std::vector<unsigned char> &buffer, size_t offset, size_t length)
{
    assert(offset >= 0 && length >= 0);
    assert(offset + length <= buffer.size());
    _stream->write(reinterpret_cast<const char *>(buffer.data() + offset), length);
    _stream->seekg(_stream->tellp());
}

void StreamWrapper::write(const std::string &) {}

void StreamWrapper::write(const std::string &, Encoding) {}

void StreamWrapper::writeByte(unsigned char b)
{
    _stream->write(reinterpret_cast<const char *>(&b), 1);
}

}// namespace dwg
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

#pragma once

#include <iostream>
#include <vector>

namespace dwg {

class InputStreamWrapper
{
    std::istream *_stream;
    Encoding _encoding;

public:
    InputStreamWrapper(std::istream *stream);
    virtual ~InputStreamWrapper();

    std::istream *stream();
    
    std::size_t length() const;
    std::size_t pos() const;
    void seek(std::size_t pos);
    
    Encoding encoding() const;
    void setEncoding(Encoding encoding);

    char readChar();
    unsigned char readByte();
    std::vector<unsigned char> readBytes(int length);
    short readShort();
    unsigned short readUShort();
    int readInt();
    unsigned int readUInt();
    long long readLong();
    unsigned long long readULong();
    float readFloat();
    double readDouble();
    std::string readString(int length);
    std::string readString(int length, Encoding encoding);

    template<class T, class E>
    T readT()
    {
        T t = 0;
        size_t sz = sizeof(T);
        std::vector<unsigned int> buffer = readBytes(sz);
        auto converter = E::instance();
        return converter->fromBytesT<T>(buffer.data());
    }

    std::string readUntil(char match);
};

class OutputStreamWrapper
{
    std::ostream *_stream;
    Encoding _encoding;

public:
    OutputStreamWrapper(std::ostream *stream);
    virtual ~OutputStreamWrapper();

    std::ostream *stream();
    
    std::size_t length() const;
    std::size_t pos() const;
    void seek(std::size_t pos);
    
    Encoding encoding() const;
    void setEncoding(Encoding encoding);

    template<class T>
    void write(const T &value)
    {
        write<T, LittleEndianConverter>(value);
    }

    template<class T, class E>
    void write(const T& value)
    {
        auto convert = E::instance();
        std::vector<unsigned char> buffer = converter->bytesT<T>(value);
        write(buffer, 0, buffer.size());
    }

    virtual void write(const std::vector<unsigned char> &buffer, int offset, int length);
    virtual void write(const std::string &);
    virtual void write(const std::string &, Encoding);
};

}// namespace dwg
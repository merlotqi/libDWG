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

#include <dwg/exports.h>
#include <dwg/utils/Encoding.h>
#include <dwg/utils/EndianConverter.h>
#include <iostream>
#include <sstream>
#include <vector>

namespace dwg {

class LIBDWG_API StreamWrapper
{
    std::iostream *_stream;
    Encoding _encoding;
    bool _owned;

public:
    StreamWrapper(std::iostream *stream);
    StreamWrapper(const std::vector<unsigned char> &buffer);
    StreamWrapper(const StreamWrapper &other);
    StreamWrapper &operator=(const StreamWrapper &other);
    ~StreamWrapper();

    std::iostream *stream();
    Encoding encoding() const;
    void setEncoding(Encoding encoding);

    std::streampos tell() const;
    void seek(std::streampos pos);

    void flush();
    void clear();

public:
    char readChar();
    unsigned char readByte();
    std::vector<unsigned char> readBytes(std::size_t length);
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

    template<typename T, typename E>
    T readT()
    {
        T t = 0;
        size_t sz = sizeof(T);
        std::vector<unsigned char> buffer = readBytes(sz);
        auto converter = E::instance();
        return converter->template fromBytesT<T>(buffer.data());
    }

    std::string readUntil(char match);

public:
    std::vector<unsigned char> buffer() const;

    template<typename T>
    void write(const T &value)
    {
        write<T, LittleEndianConverter>(value);
    }

    template<typename T, typename E>
    void write(const T &value)
    {
        auto convert = E::instance();
        std::vector<unsigned char> buffer = convert->template bytesT<T>(value);
        write(buffer, 0, buffer.size());
    }

    virtual void write(const std::vector<unsigned char> &buffer, size_t offset, size_t length);
    virtual void write(const std::string &);
    virtual void write(const std::string &, Encoding);
    void writeByte(unsigned char b);
};

}// namespace dwg
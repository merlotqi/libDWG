#ifndef LIBDWG_STREAMIO_H
#define LIBDWG_STREAMIO_H

#include <dwg/exports.h>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <type_traits>


namespace dwg {
namespace utils {

class EndianConverter;

enum StreamOptions
{
    None = 0,
    CreateCopy = 1,
    ResetPosition = 2,
};

class LIBDWG_API InputStream
{
    std::unique_ptr<std::istream> m_stream;

public:
    InputStream(const std::string &name, int mode);
    InputStream(std::istream *stream, StreamOptions options);
    InputStream(const unsigned char *buffer, size_t length);

    std::unique_ptr<unsigned char[]> ReadBytes(size_t length) const;
    unsigned char ReadByte() const;
    char ReadChar() const;
    int16_t ReadInt16() const;
    uint16_t ReadUInt16() const;
    int32_t ReadInt32() const;
    uint32_t ReadUInt32() const;
    int64_t ReadInt64() const;
    uint64_t ReadUInt64() const;
    float ReadFloat() const;
    double ReadDouble() const;
    std::string ReadString(size_t length) const;

    template<class T>
    int16_t ReadInt16() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(2);
        return converter->ToInt16(buffer.get());
    }

    template<class T>
    uint16_t ReadUInt16() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(2);
        return converter->ToUInt16(buffer.get());
    }

    template<class T>
    int32_t ReadInt32() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(4);
        return converter->ToInt32(buffer.get());
    }

    template<class T>
    uint32_t ReadUInt32() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(4);
        return converter->ToUInt32(buffer.get());
    }

    template<class T>
    int64_t ReadInt64() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(8);
        return converter->ToInt64(buffer.get());
    }

    template<class T>
    uint64_t ReadUInt64() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(8);
        return converter->ToUInt64(buffer.get());
    }

    template<class T>
    float ReadFloat() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(4);
        return converter->ToFloat(buffer.get());
    }

    template<class T>
    double ReadDouble() const
    {
        static_assert(std::is_base_of_v<EndianConverter, T>, "");
        auto &&converter = T::Instance();

        auto &&buffer = ReadBytes(8);
        return converter->ToDouble(buffer.get());
    }
};

class LIBDWG_API OutputStream
{
    std::ostream *m_stream;

public:
    OutputStream(const std::string &name, int mode);
    OutputStream(std::istream *stream, bool createCopy, bool resetPosition);
};

}// namespace utils
}// namespace dwg

#endif// LIBDWG_STREAMIO_H
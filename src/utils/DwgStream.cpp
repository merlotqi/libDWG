#include "DwgStream.h"
#include <dwg/utils/EndianConverter.h>



namespace dwg {
namespace utils {

InputStream::InputStream(const std::string &name, int mode)
{
    m_stream = std::make_unique<std::ifstream>(name,
                                               std::ios_base::openmode(mode));
}

InputStream::InputStream(std::istream *stream, StreamOptions options)
{
    if (!stream) throw std::invalid_argument("Input stream cannot be null");

    std::streampos initialPosition = stream->tellg();

    if (options & CreateCopy)
    {

        stream->seekg(0, std::ios::end);
        std::streamoff length = stream->tellg();
        stream->seekg(0, std::ios::beg);

        if (length < 0)
            throw std::runtime_error("Failed to determine stream length");

        std::string buffer(static_cast<size_t>(length), '\0');
        stream->read(buffer.data(), length);

        if (!stream->good())
            throw std::runtime_error("Failed to read from stream");

        m_stream = std::make_unique<std::istringstream>(buffer);
    }
    else { m_stream.reset(stream); }

    if (options & ResetPosition) m_stream->seekg(0, std::ios::beg);

    stream->seekg(initialPosition);
}

InputStream::InputStream(const unsigned char *buffer, size_t length)
{
    if (!buffer || length == 0)
    {
        throw std::invalid_argument(
                "Buffer cannot be null and length must be greater than 0");
    }

    std::string_view view =
            std::string_view(reinterpret_cast<const char *>(buffer), length);
    m_stream = std::make_unique<std::istringstream>(std::string(view));
}

std::unique_ptr<unsigned char[]> InputStream::ReadBytes(size_t length) const
{
    if (m_stream) throw std::runtime_error("");
    std::unique_ptr<unsigned char[]> buffer(new unsigned char[length]);
    m_stream->read(reinterpret_cast<char *>(buffer.get()),
                   (std::streamsize) length);
    if (!m_stream->good() ||
        m_stream->gcount() < static_cast<std::streamsize>(length))
        throw std::runtime_error("");

    return buffer;
}

unsigned char InputStream::ReadByte() const
{
    unsigned char byte;
    m_stream->read(reinterpret_cast<char *>(&byte), 1);
    if (!m_stream->good()) throw std::runtime_error("");

    return byte;
}

char InputStream::ReadChar() const { return (char) ReadByte(); }

int16_t InputStream::ReadInt16() const
{
    return ReadInt16<LittleEndianConverter>();
}

uint16_t InputStream::ReadUInt16() const
{
    return ReadUInt16<LittleEndianConverter>();
}

int32_t InputStream::ReadInt32() const
{
    return ReadInt32<LittleEndianConverter>();
}

uint32_t InputStream::ReadUInt32() const
{
    return ReadUInt32<LittleEndianConverter>();
}

int64_t InputStream::ReadInt64() const
{
    return ReadInt64<LittleEndianConverter>();
}

uint64_t InputStream::ReadUInt64() const
{
    return ReadUInt64<LittleEndianConverter>();
}

float InputStream::ReadFloat() const
{
    return ReadFloat<LittleEndianConverter>();
}

double InputStream::ReadDouble() const
{
    return ReadDouble<LittleEndianConverter>();
}

std::string InputStream::ReadString(size_t length) const
{
    auto &&numArray = ReadBytes(length);
    if (!numArray) return std::string();
    return std::string(reinterpret_cast<const char *>(numArray.get()), length);
}

}// namespace utils
}// namespace dwg
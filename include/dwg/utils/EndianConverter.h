#ifndef LIBDWG_ENDIANCONVERTER_H
#define LIBDWG_ENDIANCONVERTER_H

#include <memory>
#include <dwg/exports.h>

namespace dwg {

class LIBDWG_API EndianConverter {
public:
    EndianConverter() = default;
    virtual std::vector<unsigned char> GetBytes(char value) = 0;
    virtual std::vector<unsigned char> GetBytes(short value) = 0;
    virtual std::vector<unsigned char> GetBytes(unsigned short value) = 0;
    virtual std::vector<unsigned char> GetBytes(int value) = 0;
    virtual std::vector<unsigned char> GetBytes(unsigned int value) = 0;
    virtual std::vector<unsigned char> GetBytes(long long value) = 0;
    virtual std::vector<unsigned char> GetBytes(unsigned long long value) = 0;
    virtual std::vector<unsigned char> GetBytes(double value) = 0;
    virtual std::vector<unsigned char> GetBytes(float value) = 0;

    virtual char ToChar(unsigned char *bytes) = 0;
    virtual short ToInt16(unsigned char *bytes) = 0;
    virtual unsigned short ToUInt16(unsigned char *bytes) = 0;
    virtual int ToInt32(unsigned char *bytes) = 0;
    virtual unsigned int ToUint32(unsigned char *bytes) = 0;
    virtual long long ToInt64(unsigned char *bytes) = 0;
    virtual unsigned long long ToUInt64(unsigned char *bytes) = 0;
};

class BigEndianConverter : public EndianConverter {
public:
    BigEndianConverter();
    static std::shared_ptr<EndianConverter> Instance();
};

class LittleEndianConverter : public EndianConverter {
public:
    LittleEndianConverter();
    static std::shared_ptr<EndianConverter> Instance();
};

} // namespace dwg

#endif // LIBDWG_ENDIANCONVERTER_H
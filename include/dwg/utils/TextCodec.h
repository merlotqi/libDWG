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

#include <string>
#include <dwg/utils/CodePages.h>

namespace dwg {

class EncodingConverter;

class TextCodec
{
public:
    TextCodec();
    ~TextCodec();
    std::string fromUtf8(std::string s);
    std::string toUtf8(std::string s);
    int getVersion() { return version; }
    void setVersion(std::string *v, bool dxfFormat);
    void setVersion(int v, bool dxfFormat);
    void setCodePage(std::string *c, bool dxfFormat);
    void setCodePage(std::string c, bool dxfFormat)
    {
        setCodePage(&c, dxfFormat);
    }
    std::string getCodePage() { return cp; }

private:
    std::string correctCodePage(const std::string &s);

private:
    int version;
    std::string cp;
    EncodingConverter *conv;
};

class EncodingConverter
{
public:
    EncodingConverter(const int *t, int l)
    {
        table = t;
        cpLenght = l;
    }
    virtual ~EncodingConverter() {}
    virtual std::string fromUtf8(std::string *s) { return *s; }
    virtual std::string toUtf8(std::string *s);
    std::string encodeText(std::string stmp);
    std::string decodeText(int c);
    std::string encodeNum(int c);
    int decodeNum(std::string s, int *b);
    const int *table;
    int cpLenght;
};

class DRW_ConvUTF16 : public EncodingConverter
{
public:
    DRW_ConvUTF16() : EncodingConverter(NULL, 0) {}
    virtual std::string fromUtf8(std::string *s);
    virtual std::string toUtf8(std::string *s);
};

class DRW_ConvTable : public EncodingConverter
{
public:
    DRW_ConvTable(const int *t, int l) : EncodingConverter(t, l) {}
    virtual std::string fromUtf8(std::string *s);
    virtual std::string toUtf8(std::string *s);
};

class DRW_ConvDBCSTable : public EncodingConverter
{
public:
    DRW_ConvDBCSTable(const int *t, const int *lt, const int dt[][2], int l)
        : EncodingConverter(t, l)
    {
        leadTable = lt;
        doubleTable = dt;
    }

    virtual std::string fromUtf8(std::string *s);
    virtual std::string toUtf8(std::string *s);

private:
    const int *leadTable;
    const int (*doubleTable)[2];
};

class DRW_Conv932Table : public EncodingConverter
{
public:
    DRW_Conv932Table(const int *t, const int *lt, const int dt[][2], int l)
        : EncodingConverter(t, l)
    {
        leadTable = lt;
        doubleTable = dt;
    }

    virtual std::string fromUtf8(std::string *s);
    virtual std::string toUtf8(std::string *s);

private:
    const int *leadTable;
    const int (*doubleTable)[2];
};

class ExtConverter : public EncodingConverter
{
public:
    ExtConverter(const char *enc) : EncodingConverter(NULL, 0)
    {
        encoding = enc;
    }
    virtual std::string fromUtf8(std::string *s);
    virtual std::string toUtf8(std::string *s);

private:
    const char *encoding;
    std::string convertByiconv(const char *in_encode, const char *out_encode,
                               const std::string *s);
};

}// namespace dwg


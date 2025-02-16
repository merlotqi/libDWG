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

#include <dwg/utils/Encoding_p.h>
#include <iconv.h>
#include <map>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace dwg {

static std::map<CodePage, std::string> s_codepage_iconvid_mapping = {
        {               Ibm037,                    "IBM037"},
        {               Ibm437,                    "IBM437"},
        {              Asmo708,                   "ASMO708"},
        {               Dos720,                    "DOS720"},
        {               Ibm737,                    "IBM737"},
        {               Ibm775,                    "IBM775"},
        {               Ibm850,                    "IBM850"},
        {               Ibm852,                    "IBM852"},
        {               Ibm855,                    "IBM855"},
        {               Ibm857,                    "IBM857"},
        {               Ibm860,                    "IBM860"},
        {               Ibm861,                    "IBM861"},
        {               Dos862,                    "DOS862"},
        {               Ibm863,                    "IBM863"},
        {               Ibm864,                    "IBM864"},
        {               Ibm865,                    "IBM865"},
        {                Cp866,                     "CP866"},
        {               Ibm869,                    "IBM869"},
        {               Ibm870,                    "IBM870"},
        {           Windows874,               "Windows-874"},
        {                Cp875,                     "CP875"},
        {            Shift_jis,                 "Shift-JIS"},
        {               Gb2312,                    "GB2312"},
        {              Ksc5601,            "KS_C_5601-1987"},
        {                 big5,                      "BIG5"},
        {              Ibm1026,                   "IBM1026"},
        {             Ibm01047,                  "IBM01047"},
        {             Ibm01140,                  "IBM01140"},
        {             Ibm01141,                  "IBM01141"},
        {             Ibm01142,                  "IBM01142"},
        {             Ibm01143,                  "IBM01143"},
        {             Ibm01144,                  "IBM01144"},
        {             Ibm01145,                  "IBM01145"},
        {             Ibm01146,                  "IBM01146"},
        {             Ibm01147,                  "IBM01147"},
        {             Ibm01148,                  "IBM01148"},
        {             Ibm01149,                  "IBM01149"},
        {                Utf16,                    "UTF-16"},
        {          UnicodeFFFE,                  "UTF-16BE"},
        {          Windows1250,              "Windows-1250"},
        {          Windows1251,              "Windows-1251"},
        {          Windows1252,              "Windows-1252"},
        {          Windows1253,              "Windows-1253"},
        {          Windows1254,              "Windows-1254"},
        {          Windows1255,              "Windows-1255"},
        {          Windows1256,              "Windows-1256"},
        {          Windows1257,              "Windows-1257"},
        {          Windows1258,              "Windows-1258"},
        {                Johab,                     "JOHAB"},
        {            Macintosh,                 "MACINTOSH"},
        {         Xmacjapanese,            "X-MAC-JAPANESE"},
        {      Xmacchinesetrad, "X-MAC-CHINESE-TRADITIONAL"},
        {           Xmackorean,              "X-MAC-KOREAN"},
        {           Xmacarabic,              "X-MAC-ARABIC"},
        {           Xmachebrew,              "X-MAC-HEBREW"},
        {            Xmacgreek,               "X-MAC-GREEK"},
        {         Xmaccyrillic,            "X-MAC-CYRILLIC"},
        {      Xmacchinesesimp,  "X-MAC-CHINESE-SIMPLIFIED"},
        {         Xmacromanian,            "X-MAC-ROMANIAN"},
        {        Xmacukrainian,           "X-MAC-UKRAINIAN"},
        {             Xmacthai,                "X-MAC-THAI"},
        {               Xmacce,                  "X-MAC-CE"},
        {        Xmacicelandic,           "X-MAC-ICELANDIC"},
        {          Xmacturkish,             "X-MAC-TURKISH"},
        {         Xmaccroatian,            "X-MAC-CROATIAN"},
        {                Utf32,                    "UTF-32"},
        {              Utf32BE,                  "UTF-32BE"},
        {          XChineseCNS,             "X-CHINESE-CNS"},
        {             Xcp20001,                 "X-CP20001"},
        {         XChineseEten,            "X-CHINESE-ETEN"},
        {             Xcp20003,                 "X-CP20003"},
        {             Xcp20004,                 "X-CP20004"},
        {             Xcp20005,                 "X-CP20005"},
        {                 XIA5,                      "XIA5"},
        {           XIA5German,                "XIA5GERMAN"},
        {          XIA5Swedish,               "XIA5SWEDISH"},
        {        XIA5Norwegian,             "XIA5NORWEGIAN"},
        {              Usascii,                  "US-ASCII"},
        {             Xcp20261,                 "X-CP20261"},
        {             Xcp20269,                 "X-CP20269"},
        {               Ibm273,                    "IBM273"},
        {               Ibm277,                    "IBM277"},
        {               Ibm278,                    "IBM278"},
        {               Ibm280,                    "IBM280"},
        {               Ibm284,                    "IBM284"},
        {               Ibm285,                    "IBM285"},
        {               Ibm290,                    "IBM290"},
        {               Ibm297,                    "IBM297"},
        {               Ibm420,                    "IBM420"},
        {               Ibm423,                    "IBM423"},
        {               Ibm424,                    "IBM424"},
        {XEBCDICKoreanExtended,     "XEBCDICKOREANEXTENDED"},
        {              IbmThai,                   "IBMTHAI"},
        {                Koi8r,                    "KOI8-R"},
        {               Ibm871,                    "IBM871"},
        {               Ibm880,                    "IBM880"},
        {               Ibm905,                    "IBM905"},
        {             Ibm00924,                  "IBM00924"},
        {                EUCJP,                    "EUC-JP"},
        {             Xcp20936,                 "X-CP20936"},
        {             Xcp20949,                 "X-CP20949"},
        {               Cp1025,                    "CP1025"},
        {                Koi8u,                    "KOI8-U"},
        {             Iso88591,                "ISO-8859-1"},
        {             Iso88592,                "ISO-8859-2"},
        {             Iso88593,                "ISO-8859-3"},
        {             Iso88594,                "ISO-8859-4"},
        {             Iso88595,                "ISO-8859-5"},
        {             Iso88596,                "ISO-8859-6"},
        {             Iso88597,                "ISO-8859-7"},
        {             Iso88598,                "ISO-8859-8"},
        {             Iso88599,                "ISO-8859-9"},
        {            Iso885910,               "ISO-8859-10"},
        {            Iso885913,               "ISO-8859-13"},
        {            Iso885915,               "ISO-8859-15"},
        {              XEuropa,                  "X-EUROPA"},
        {            Iso88598i,               "ISO-8859-8I"},
        {            Iso2022jp,               "ISO-2022-JP"},
        {          CsISO2022JP,              "CS-ISO2022JP"},
        {        Iso2022jp_jis,           "ISO-2022-JP-JIS"},
        {            Iso2022kr,               "ISO-2022-KR"},
        {             Xcp50227,                 "X-CP50227"},
        {                Eucjp,                    "EUC-JP"},
        {                EUCCN,                    "EUC-CN"},
        {                Euckr,                    "EUC-KR"},
        {             Hzgb2312,                 "HZ-GB2312"},
        {              Gb18030,                   "GB18030"},
        {             Xisciide,          "ISCII-DEVENAGARI"},
        {             Xisciibe,             "ISCII-BENGALI"},
        {             Xisciita,               "ISCII-TAMIL"},
        {             Xisciite,              "ISCII-TELEGU"},
        {             Xisciias,            "ISCII-ASSAMESE"},
        {             Xisciior,               "ISCII-ORIYA"},
        {             Xisciika,             "ISCII-KANNADA"},
        {             Xisciima,           "ISCII-MALAYALAM"},
        {             Xisciigu,            "ISCII-GUJARATI"},
        {             Xisciipa,             "ISCII-PUNJABI"},
        {                 Utf7,                     "UTF-7"},
        {                 Utf8,                     "UTF-8"}
};


Encoding::Encoding() : cp(Utf8) {}

Encoding::Encoding(CodePage codePage) : cp(codePage) {}

std::string Encoding::toUtf8(const char *str) noexcept(false)
{
    if (cp == Utf8) { return str; }

    std::string to = s_codepage_iconvid_mapping[cp];

    iconv_t cd = iconv_open("UTF-8", to.c_str());
    if (cd == (iconv_t) -1) { throw std::runtime_error("iconv_open failed"); }

    size_t inBytesLeft = strlen(str);
    size_t outBytesLeft = inBytesLeft * 4 + 4;
    std::vector<char> outputBuffer(outBytesLeft);

    char *inBuf = const_cast<char *>(str);
    char *outBuf = outputBuffer.data();
    char *outBufStart = outBuf;

    if (iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft) == (size_t) -1)
    {
        iconv_close(cd);
        throw std::runtime_error("iconv conversion failed");
    }

    iconv_close(cd);
    return std::string(outBufStart, outBuf - outBufStart);
}

std::string Encoding::toUtf8(const std::string &str) noexcept(false)
{
    if (cp == Utf8) { return str; }

    return toUtf8(str.c_str());
}

std::string Encoding::fromUtf8(const std::string &str) noexcept(false)
{
    if (cp == Utf8) { return str; }

    std::string to = s_codepage_iconvid_mapping[cp];
    iconv_t cd = iconv_open(to.c_str(), "UTF-8");
    if (cd == (iconv_t) -1) { throw std::runtime_error("iconv_open failed"); }

    size_t inSize = str.size();
    size_t outSize = inSize * 4;
    std::vector<char> outBuffer(outSize);

    char *inBuf = const_cast<char *>(str.data());
    char *outBuf = outBuffer.data();
    size_t inBytesLeft = inSize;
    size_t outBytesLeft = outSize;

    if (iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft) == (size_t) -1)
    {
        iconv_close(cd);
        throw std::runtime_error("iconv_open failed");
    }

    iconv_close(cd);
    return std::string(outBuffer.data(), outSize - outBytesLeft);
}

std::wstring Encoding::toUnicode(const std::string &str) noexcept(false)
{
    if (str.empty()) { return std::wstring(); }

#ifdef _WIN32
    int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    if (len == 0) { throw std::runtime_error("Failed to convert UTF-8 to Unicode (MultiByteToWideChar failed)"); }

    std::vector<wchar_t> buffer(len);
    if (MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer.data(), len) == 0)
    {
        throw std::runtime_error("Failed to convert UTF-8 to Unicode (MultiByteToWideChar failed)");
    }

    return std::wstring(buffer.data());

#else
    iconv_t cd = iconv_open("WCHAR_T", "UTF-8");
    if (cd == (iconv_t) -1) { throw std::runtime_error("Failed to initialize iconv"); }

    size_t inSize = str.size();
    size_t outSize = inSize * sizeof(wchar_t);
    std::vector<char> outBuffer(outSize);

    char *inBuf = const_cast<char *>(str.data());
    char *outBuf = outBuffer.data();
    size_t inBytesLeft = inSize;
    size_t outBytesLeft = outSize;

    if (iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft) == (size_t) -1)
    {
        iconv_close(cd);
        throw std::runtime_error("Failed to convert UTF-8 to Unicode (iconv failed)");
    }

    iconv_close(cd);
    return std::wstring(reinterpret_cast<wchar_t *>(outBuffer.data()), (outSize - outBytesLeft) / sizeof(wchar_t));
#endif
}

std::string Encoding::fromUnicode(const std::wstring &wstr) noexcept(false)
{
    if (wstr.empty()) { return std::string(); }

#ifdef _WIN32
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (len == 0) { throw std::runtime_error("Failed to convert Unicode to UTF-8 (WideCharToMultiByte failed)"); }

    std::vector<char> buffer(len);
    if (WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, buffer.data(), len, nullptr, nullptr) == 0)
    {
        throw std::runtime_error("Failed to convert Unicode to UTF-8 (WideCharToMultiByte failed)");
    }

    return std::string(buffer.data());

#else
    iconv_t cd = iconv_open("UTF-8", "WCHAR_T");
    if (cd == (iconv_t) -1) { throw std::runtime_error("Failed to initialize iconv"); }

    size_t inSize = wstr.size() * sizeof(wchar_t);
    size_t outSize = inSize * 4;
    std::vector<char> outBuffer(outSize);

    char *inBuf = reinterpret_cast<char *>(const_cast<wchar_t *>(wstr.data()));
    char *outBuf = outBuffer.data();
    size_t inBytesLeft = inSize;
    size_t outBytesLeft = outSize;

    if (iconv(cd, &inBuf, &inBytesLeft, &outBuf, &outBytesLeft) == (size_t) -1)
    {
        iconv_close(cd);
        throw std::runtime_error("Failed to convert Unicode to UTF-8 (iconv failed)");
    }

    iconv_close(cd);
    return std::string(outBuffer.data(), outSize - outBytesLeft);
#endif
}

CodePage Encoding::codePage() const { return cp; }

}// namespace dwg
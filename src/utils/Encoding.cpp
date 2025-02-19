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
        {               CodePage::Ibm037,                    "IBM037"},
        {               CodePage::Ibm437,                    "IBM437"},
        {              CodePage::Asmo708,                   "ASMO708"},
        {               CodePage::Dos720,                    "DOS720"},
        {               CodePage::Ibm737,                    "IBM737"},
        {               CodePage::Ibm775,                    "IBM775"},
        {               CodePage::Ibm850,                    "IBM850"},
        {               CodePage::Ibm852,                    "IBM852"},
        {               CodePage::Ibm855,                    "IBM855"},
        {               CodePage::Ibm857,                    "IBM857"},
        {               CodePage::Ibm860,                    "IBM860"},
        {               CodePage::Ibm861,                    "IBM861"},
        {               CodePage::Dos862,                    "DOS862"},
        {               CodePage::Ibm863,                    "IBM863"},
        {               CodePage::Ibm864,                    "IBM864"},
        {               CodePage::Ibm865,                    "IBM865"},
        {                CodePage::Cp866,                     "CP866"},
        {               CodePage::Ibm869,                    "IBM869"},
        {               CodePage::Ibm870,                    "IBM870"},
        {           CodePage::Windows874,               "Windows-874"},
        {                CodePage::Cp875,                     "CP875"},
        {            CodePage::Shift_jis,                 "Shift-JIS"},
        {               CodePage::Gb2312,                    "GB2312"},
        {              CodePage::Ksc5601,            "KS_C_5601-1987"},
        {                 CodePage::big5,                      "BIG5"},
        {              CodePage::Ibm1026,                   "IBM1026"},
        {             CodePage::Ibm01047,                  "IBM01047"},
        {             CodePage::Ibm01140,                  "IBM01140"},
        {             CodePage::Ibm01141,                  "IBM01141"},
        {             CodePage::Ibm01142,                  "IBM01142"},
        {             CodePage::Ibm01143,                  "IBM01143"},
        {             CodePage::Ibm01144,                  "IBM01144"},
        {             CodePage::Ibm01145,                  "IBM01145"},
        {             CodePage::Ibm01146,                  "IBM01146"},
        {             CodePage::Ibm01147,                  "IBM01147"},
        {             CodePage::Ibm01148,                  "IBM01148"},
        {             CodePage::Ibm01149,                  "IBM01149"},
        {                CodePage::Utf16,                    "UTF-16"},
        {          CodePage::UnicodeFFFE,                  "UTF-16BE"},
        {          CodePage::Windows1250,              "Windows-1250"},
        {          CodePage::Windows1251,              "Windows-1251"},
        {          CodePage::Windows1252,              "Windows-1252"},
        {          CodePage::Windows1253,              "Windows-1253"},
        {          CodePage::Windows1254,              "Windows-1254"},
        {          CodePage::Windows1255,              "Windows-1255"},
        {          CodePage::Windows1256,              "Windows-1256"},
        {          CodePage::Windows1257,              "Windows-1257"},
        {          CodePage::Windows1258,              "Windows-1258"},
        {                CodePage::Johab,                     "JOHAB"},
        {            CodePage::Macintosh,                 "MACINTOSH"},
        {         CodePage::Xmacjapanese,            "X-MAC-JAPANESE"},
        {      CodePage::Xmacchinesetrad, "X-MAC-CHINESE-TRADITIONAL"},
        {           CodePage::Xmackorean,              "X-MAC-KOREAN"},
        {           CodePage::Xmacarabic,              "X-MAC-ARABIC"},
        {           CodePage::Xmachebrew,              "X-MAC-HEBREW"},
        {            CodePage::Xmacgreek,               "X-MAC-GREEK"},
        {         CodePage::Xmaccyrillic,            "X-MAC-CYRILLIC"},
        {      CodePage::Xmacchinesesimp,  "X-MAC-CHINESE-SIMPLIFIED"},
        {         CodePage::Xmacromanian,            "X-MAC-ROMANIAN"},
        {        CodePage::Xmacukrainian,           "X-MAC-UKRAINIAN"},
        {             CodePage::Xmacthai,                "X-MAC-THAI"},
        {               CodePage::Xmacce,                  "X-MAC-CE"},
        {        CodePage::Xmacicelandic,           "X-MAC-ICELANDIC"},
        {          CodePage::Xmacturkish,             "X-MAC-TURKISH"},
        {         CodePage::Xmaccroatian,            "X-MAC-CROATIAN"},
        {                CodePage::Utf32,                    "UTF-32"},
        {              CodePage::Utf32BE,                  "UTF-32BE"},
        {          CodePage::XChineseCNS,             "X-CHINESE-CNS"},
        {             CodePage::Xcp20001,                 "X-CP20001"},
        {         CodePage::XChineseEten,            "X-CHINESE-ETEN"},
        {             CodePage::Xcp20003,                 "X-CP20003"},
        {             CodePage::Xcp20004,                 "X-CP20004"},
        {             CodePage::Xcp20005,                 "X-CP20005"},
        {                 CodePage::XIA5,                      "XIA5"},
        {           CodePage::XIA5German,                "XIA5GERMAN"},
        {          CodePage::XIA5Swedish,               "XIA5SWEDISH"},
        {        CodePage::XIA5Norwegian,             "XIA5NORWEGIAN"},
        {              CodePage::Usascii,                  "US-ASCII"},
        {             CodePage::Xcp20261,                 "X-CP20261"},
        {             CodePage::Xcp20269,                 "X-CP20269"},
        {               CodePage::Ibm273,                    "IBM273"},
        {               CodePage::Ibm277,                    "IBM277"},
        {               CodePage::Ibm278,                    "IBM278"},
        {               CodePage::Ibm280,                    "IBM280"},
        {               CodePage::Ibm284,                    "IBM284"},
        {               CodePage::Ibm285,                    "IBM285"},
        {               CodePage::Ibm290,                    "IBM290"},
        {               CodePage::Ibm297,                    "IBM297"},
        {               CodePage::Ibm420,                    "IBM420"},
        {               CodePage::Ibm423,                    "IBM423"},
        {               CodePage::Ibm424,                    "IBM424"},
        {CodePage::XEBCDICKoreanExtended,     "XEBCDICKOREANEXTENDED"},
        {              CodePage::IbmThai,                   "IBMTHAI"},
        {                CodePage::Koi8r,                    "KOI8-R"},
        {               CodePage::Ibm871,                    "IBM871"},
        {               CodePage::Ibm880,                    "IBM880"},
        {               CodePage::Ibm905,                    "IBM905"},
        {             CodePage::Ibm00924,                  "IBM00924"},
        {                CodePage::EUCJP,                    "EUC-JP"},
        {             CodePage::Xcp20936,                 "X-CP20936"},
        {             CodePage::Xcp20949,                 "X-CP20949"},
        {               CodePage::Cp1025,                    "CP1025"},
        {                CodePage::Koi8u,                    "KOI8-U"},
        {             CodePage::Iso88591,                "ISO-8859-1"},
        {             CodePage::Iso88592,                "ISO-8859-2"},
        {             CodePage::Iso88593,                "ISO-8859-3"},
        {             CodePage::Iso88594,                "ISO-8859-4"},
        {             CodePage::Iso88595,                "ISO-8859-5"},
        {             CodePage::Iso88596,                "ISO-8859-6"},
        {             CodePage::Iso88597,                "ISO-8859-7"},
        {             CodePage::Iso88598,                "ISO-8859-8"},
        {             CodePage::Iso88599,                "ISO-8859-9"},
        {            CodePage::Iso885910,               "ISO-8859-10"},
        {            CodePage::Iso885913,               "ISO-8859-13"},
        {            CodePage::Iso885915,               "ISO-8859-15"},
        {              CodePage::XEuropa,                  "X-EUROPA"},
        {            CodePage::Iso88598i,               "ISO-8859-8I"},
        {            CodePage::Iso2022jp,               "ISO-2022-JP"},
        {          CodePage::CsISO2022JP,              "CS-ISO2022JP"},
        {        CodePage::Iso2022jp_jis,           "ISO-2022-JP-JIS"},
        {            CodePage::Iso2022kr,               "ISO-2022-KR"},
        {             CodePage::Xcp50227,                 "X-CP50227"},
        {                CodePage::Eucjp,                    "EUC-JP"},
        {                CodePage::EUCCN,                    "EUC-CN"},
        {                CodePage::Euckr,                    "EUC-KR"},
        {             CodePage::Hzgb2312,                 "HZ-GB2312"},
        {              CodePage::Gb18030,                   "GB18030"},
        {             CodePage::Xisciide,          "ISCII-DEVENAGARI"},
        {             CodePage::Xisciibe,             "ISCII-BENGALI"},
        {             CodePage::Xisciita,               "ISCII-TAMIL"},
        {             CodePage::Xisciite,              "ISCII-TELEGU"},
        {             CodePage::Xisciias,            "ISCII-ASSAMESE"},
        {             CodePage::Xisciior,               "ISCII-ORIYA"},
        {             CodePage::Xisciika,             "ISCII-KANNADA"},
        {             CodePage::Xisciima,           "ISCII-MALAYALAM"},
        {             CodePage::Xisciigu,            "ISCII-GUJARATI"},
        {             CodePage::Xisciipa,             "ISCII-PUNJABI"},
        {                 CodePage::Utf7,                     "UTF-7"},
        {                 CodePage::Utf8,                     "UTF-8"}
};


Encoding::Encoding() : cp(CodePage::Utf8) {}

Encoding::Encoding(CodePage codePage) : cp(codePage) {}

std::string Encoding::toUtf8(const char *str) noexcept(false)
{
    if (cp == CodePage::Utf8) { return str; }

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
    if (cp == CodePage::Utf8) { return str; }

    return toUtf8(str.c_str());
}

std::string Encoding::fromUtf8(const std::string &str) noexcept(false)
{
    if (cp == CodePage::Utf8) { return str; }

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
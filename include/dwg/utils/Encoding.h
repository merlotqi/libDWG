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
#include <string>
#include <vector>

namespace dwg {

/// Source: https://docs.microsoft.com/en-us/dotnet/api/system.text.encoding?view=net-5.0
enum class CodePage
{
    Unknown = 0x00000000,         /// Unknown code page
    Ibm037 = 37,                  /// IBM EBCDIC (US-Canada)
    Ibm437 = 437,                 /// OEM United States
    Asmo708 = 708,                /// Arabic (ASMO 708)
    Dos720 = 720,                 /// Arabic (DOS)
    Ibm737 = 737,                 /// Greek (DOS)
    Ibm775 = 775,                 /// Baltic (DOS)
    Ibm850 = 850,                 /// Western European (DOS)
    Ibm852 = 852,                 /// Central European (DOS)
    Ibm855 = 855,                 /// OEM Cyrillic
    Ibm857 = 857,                 /// Turkish (DOS)
    Ibm860 = 860,                 /// Portuguese (DOS)
    Ibm861 = 861,                 /// Icelandic (DOS)
    Dos862 = 862,                 /// Hebrew (DOS)
    Ibm863 = 863,                 /// French Canadian (DOS)
    Ibm864 = 864,                 /// Arabic (864)
    Ibm865 = 865,                 /// Nordic (DOS)
    Cp866 = 866,                  /// Cyrillic (DOS)
    Ibm869 = 869,                 /// Greek, Modern (DOS)
    Ibm870 = 870,                 /// IBM EBCDIC (Multilingual Latin-2)
    Windows874 = 874,             /// Thai (Windows)
    Cp875 = 875,                  /// IBM EBCDIC (Greek Modern)
    Shift_jis = 932,              /// Japanese (Shift-JIS)
    Gb2312 = 936,                 /// Chinese simplified code page (GB2312)
    Ksc5601 = 949,                /// Korean
    big5 = 950,                   /// Chinese Traditional (Big5)
    Ibm1026 = 1026,               /// IBM EBCDIC (Turkish Latin-5)
    Ibm01047 = 1047,              /// IBM Latin-1
    Ibm01140 = 1140,              /// IBM EBCDIC (US-Canada-Euro)
    Ibm01141 = 1141,              /// IBM EBCDIC (Germany-Euro)
    Ibm01142 = 1142,              /// IBM EBCDIC (Denmark-Norway-Euro)
    Ibm01143 = 1143,              /// IBM EBCDIC (Finland-Sweden-Euro)
    Ibm01144 = 1144,              /// IBM EBCDIC (Italy-Euro)
    Ibm01145 = 1145,              /// IBM EBCDIC (Spain-Euro)
    Ibm01146 = 1146,              /// IBM EBCDIC (UK-Euro)
    Ibm01147 = 1147,              /// IBM EBCDIC (France-Euro)
    Ibm01148 = 1148,              /// IBM EBCDIC (International-Euro)
    Ibm01149 = 1149,              /// IBM EBCDIC (Icelandic-Euro)
    Utf16 = 1200,                 /// Unicode
    UnicodeFFFE = 1201,           /// Unicode (Big endian)
    Windows1250 = 1250,           /// Central European (Windows)
    Windows1251 = 1251,           /// Cyrillic (Windows)
    Windows1252 = 1252,           /// Western European (Windows)
    Windows1253 = 1253,           /// Greek (Windows)
    Windows1254 = 1254,           /// Turkish (Windows)
    Windows1255 = 1255,           /// Hebrew (Windows)
    Windows1256 = 1256,           /// Arabic (Windows)
    Windows1257 = 1257,           /// Baltic (Windows)
    Windows1258 = 1258,           /// Vietnamese (Windows)
    Johab = 1361,                 /// Korean (Johab)
    Macintosh = 10000,            /// Western European (Mac)
    Xmacjapanese = 10001,         /// Japanese (Mac)
    Xmacchinesetrad = 10002,      /// Chinese Traditional (Mac)
    Xmackorean = 10003,           /// Korean (Mac)
    Xmacarabic = 10004,           /// Arabic (Mac)
    Xmachebrew = 10005,           /// Hebrew (Mac)
    Xmacgreek = 10006,            /// Greek (Mac)
    Xmaccyrillic = 10007,         /// Cyrillic (Mac)
    Xmacchinesesimp = 10008,      /// Chinese Simplified (Mac)
    Xmacromanian = 10010,         /// Romanian (Mac)
    Xmacukrainian = 10017,        /// Ukrainian (Mac)
    Xmacthai = 10021,             /// Thai (Mac)
    Xmacce = 10029,               /// Central European (Mac)
    Xmacicelandic = 10079,        /// Icelandic (Mac)
    Xmacturkish = 10081,          /// Turkish (Mac)
    Xmaccroatian = 10082,         /// Croatian (Mac)
    Utf32 = 12000,                /// Unicode (UTF-32)
    Utf32BE = 12001,              /// Unicode (UTF-32 Big endian)
    XChineseCNS = 20000,          /// Chinese Traditional (CNS)
    Xcp20001 = 20001,             /// TCA Taiwan
    XChineseEten = 20002,         /// Chinese Traditional (Eten)
    Xcp20003 = 20003,             /// IBM5550 Taiwan
    Xcp20004 = 20004,             /// TeleText Taiwan
    Xcp20005 = 20005,             /// Wang Taiwan
    XIA5 = 20105,                 /// Western European (IA5)
    XIA5German = 20106,           /// German (IA5)
    XIA5Swedish = 20107,          /// Swedish (IA5)
    XIA5Norwegian = 20108,        /// Norwegian (IA5)
    Usascii = 20127,              /// US-ASCII
    Xcp20261 = 20261,             /// T.61
    Xcp20269 = 20269,             /// ISO-6937
    Ibm273 = 20273,               /// IBM EBCDIC (Germany)
    Ibm277 = 20277,               /// IBM EBCDIC (Denmark-Norway)
    Ibm278 = 20278,               /// IBM EBCDIC (Finland-Sweden)
    Ibm280 = 20280,               /// IBM EBCDIC (Italy)
    Ibm284 = 20284,               /// IBM EBCDIC (Spain)
    Ibm285 = 20285,               /// IBM EBCDIC (UK)
    Ibm290 = 20290,               /// IBM EBCDIC (Japanese katakana)
    Ibm297 = 20297,               /// IBM EBCDIC (France)
    Ibm420 = 20420,               /// IBM EBCDIC (Arabic)
    Ibm423 = 20423,               /// IBM EBCDIC (Greek)
    Ibm424 = 20424,               /// IBM EBCDIC (Hebrew)
    XEBCDICKoreanExtended = 20833,/// IBM EBCDIC (Korean Extended)
    IbmThai = 20838,              /// IBM EBCDIC (Thai)
    Koi8r = 20866,                /// Cyrillic (KOI8-R)
    Ibm871 = 20871,               /// IBM EBCDIC (Icelandic)
    Ibm880 = 20880,               /// IBM EBCDIC (Cyrillic Russian)
    Ibm905 = 20905,               /// IBM EBCDIC (Turkish)
    Ibm00924 = 20924,             /// IBM Latin-1
    EUCJP = 20932,                /// Japanese (JIS 0208-1990 and 0212-1990)
    Xcp20936 = 20936,             /// Chinese Simplified (GB2312-80)
    Xcp20949 = 20949,             /// Korean Wansung
    Cp1025 = 21025,               /// IBM EBCDIC (Cyrillic Serbian-Bulgarian)
    Koi8u = 21866,                /// Cyrillic (KOI8-U)
    Iso88591 = 28591,             /// Western European (ISO)
    Iso88592 = 28592,             /// Central European (ISO)
    Iso88593 = 28593,             /// Latin 3 (ISO)
    Iso88594 = 28594,             /// Baltic (ISO)
    Iso88595 = 28595,             /// Cyrillic (ISO)
    Iso88596 = 28596,             /// Arabic (ISO)
    Iso88597 = 28597,             /// Greek (ISO)
    Iso88598 = 28598,             /// Hebrew (ISO-Visual)
    Iso88599 = 28599,             /// Turkish (ISO)
    Iso885910 = 28600,            /// Latin-6 (ISO)
    Iso885913 = 28603,            /// Estonian (ISO)
    Iso885915 = 28605,            /// Latin 9 (ISO)
    XEuropa = 29001,              /// Europa
    Iso88598i = 38598,            /// Hebrew (ISO-Logical)
    Iso2022jp = 50220,            /// Japanese (JIS)
    CsISO2022JP = 50221,          /// Japanese (JIS-Allow 1 byte Kana)
    Iso2022jp_jis = 50222,        /// Japanese (JIS-Allow 1 byte Kana - SO/SI)
    Iso2022kr = 50225,            /// Korean (ISO)
    Xcp50227 = 50227,             /// Chinese Simplified (ISO-2022)
    Eucjp = 51932,                /// Japanese (EUC)
    EUCCN = 51936,                /// Chinese Simplified (EUC)
    Euckr = 51949,                /// Korean (EUC)
    Hzgb2312 = 52936,             /// Chinese Simplified (HZ)
    Gb18030 = 54936,              /// Chinese Simplified (GB18030)
    Xisciide = 57002,             /// ISCII Devanagari
    Xisciibe = 57003,             /// ISCII Bengali
    Xisciita = 57004,             /// ISCII Tamil
    Xisciite = 57005,             /// ISCII Telugu
    Xisciias = 57006,             /// ISCII Assamese
    Xisciior = 57007,             /// ISCII Oriya
    Xisciika = 57008,             /// ISCII Kannada
    Xisciima = 57009,             /// ISCII Malayalam
    Xisciigu = 57010,             /// ISCII Gujarati
    Xisciipa = 57011,             /// ISCII Punjabi
    Utf7 = 65000,                 /// Unicode (UTF-7)
    Utf8 = 65001,                 /// Unicode (UTF-8)
};

class LIBDWG_API Encoding
{
    CodePage cp;

public:
    Encoding();
    Encoding(CodePage codePage);

    std::vector<unsigned char> bytes(const std::string &str) const;
    std::string toUtf8(const char *str) noexcept(false);
    std::string toUtf8(const std::string &str) noexcept(false);
    std::string fromUtf8(const std::string &str) noexcept(false);
    std::wstring toUnicode(const std::string &wstr) noexcept(false);
    std::string fromUnicode(const std::wstring &wstr) noexcept(false);
    CodePage codePage() const;
};

}// namespace dwg
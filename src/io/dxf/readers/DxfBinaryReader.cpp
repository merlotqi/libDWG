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

#include <dwg/io/dxf/readers/DxfBinaryReader_p.h>

namespace dwg {

std::string DxfBinaryReader::Sentinel = "AutoCAD Binary DXF\r\n\u001a\0";

DxfBinaryReader::DxfBinaryReader(std::istream *stream) : DxfBinaryReader(stream, Encoding(CodePage::Usascii)) {}

DxfBinaryReader::DxfBinaryReader(std::istream *stream, Encoding encoding) {}

DxfBinaryReader::~DxfBinaryReader() {}

void DxfBinaryReader::start() {}

std::string DxfBinaryReader::readStringLine() { return std::string(); }

DxfCode DxfBinaryReader::readCode() { return DxfCode::Invalid; }

bool DxfBinaryReader::lineAsBool() { return false; }

double DxfBinaryReader::lineAsDouble() { return 0.0; }

short DxfBinaryReader::lineAsShort() { return 0; }

int DxfBinaryReader::lineAsInt() { return 0; }

long long DxfBinaryReader::lineAsLong() { return 0LL; }

unsigned long long DxfBinaryReader::lineAsHandle() { return 0ULL; }

std::vector<unsigned char> DxfBinaryReader::lineAsBinaryChunk() { return std::vector<unsigned char>(); }

}// namespace dwg
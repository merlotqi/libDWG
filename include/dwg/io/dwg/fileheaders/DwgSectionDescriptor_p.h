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

#include <dwg/io/dwg/fileheaders/DwgLocalSectionMap_p.h>
#include <optional>
#include <string>
#include <vector>

namespace dwg {

class DwgSectionDescriptor
{
    int _pageType;
    std::string _name;
    unsigned long long _compressedSize;
    int _pageCount;
    unsigned long long _decompressedSize;
    int _compressedCode;
    int _compressed;
    int _sectionId;
    int _encrypted;
    std::vector<DwgLocalSectionMap> _localSections;
    std::optional<unsigned long long> _hashCode;
    std::optional<unsigned long long> _encoding;

public:
    DwgSectionDescriptor();

    DwgSectionDescriptor(const std::string &name);

    long pageType() const;

    std::string name() const;
    void setName(const std::string &name);

    unsigned long long compressedSize() const;
    void setCompressedSize(unsigned long long);

    int pageCount() const;
    void setPageCount(int);

    unsigned long long decompressedSize() const;
    void setDecompressedSize(unsigned long long);

    int compressedCode() const;
    void setCompressedCode(int);

    bool isCompressed() const;

    int sectionId() const;
    void setSectionId(int);

    int encrypted() const;
    void setEncrypted(int);

    unsigned long long hashCode(bool *ok = nullptr) const;
    void setHashCode(unsigned long long);

    unsigned long long encoding(bool *ok = nullptr) const;
    void setEncoding(unsigned long long);

    std::vector<DwgLocalSectionMap> localSections() const;
    std::vector<DwgLocalSectionMap> &localSections();
    void setLocalSections(const std::vector<DwgLocalSectionMap> &);
};

}// namespace dwg
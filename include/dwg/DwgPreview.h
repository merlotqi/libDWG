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

class LIBDWG_API DwgPreview
{
public:
    enum PreviewType
    {
        Unknown,
        Bmp = 2,
        Wmf = 3,
        Png = 6,
    };

    DwgPreview();
    DwgPreview(PreviewType code, const std::vector<unsigned char> &rawHeader, const std::vector<unsigned char> &rawImage);
    ~DwgPreview();

    PreviewType code() const;
    std::vector<unsigned char> rawHeader() const;
    std::vector<unsigned char> rawImage() const;

    void save(const std::string &path);

private:
    PreviewType _code;
    std::vector<unsigned char> _rawHeader;
    std::vector<unsigned char> _rawImage;
};

}// namespace dwg
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

#include <dwg/DwgPreview.h>
#include <fstream>
#include <fmt/format.h>

namespace dwg {

DwgPreview::DwgPreview() : _code(DwgPreview::PreviewType::Unknown) {}

DwgPreview::DwgPreview(PreviewType code, const std::vector<unsigned char> &rawHeader,
                       const std::vector<unsigned char> &rawImage)
    : _code(code), _rawHeader(rawHeader), _rawImage(rawImage)
{
}

DwgPreview::~DwgPreview() {}

DwgPreview::PreviewType DwgPreview::code() const
{
    return _code;
}

std::vector<unsigned char> DwgPreview::rawHeader() const
{
    return _rawHeader;
}

std::vector<unsigned char> DwgPreview::rawImage() const
{
    return _rawImage;
}

void DwgPreview::save(const std::string &path) 
{
    bool writeHeader = false;
    if (_code == PreviewType::Bmp || _code == PreviewType::Wmf || _code == PreviewType::Png)
    {
        writeHeader = false;
    }
    else
    {
        throw std::runtime_error(fmt::format("Preview with code {} not supported.", (int)_code));
    }

    std::ofstream ofs(path);
    if (writeHeader)
    {
        ofs.wirte(reinterpret_cast<const char *>(_rawHeader.data()), _rawHeader.size());
    }
    ofs.wirte(reinterpret_cast<const char *>(_rawImage.data()), _rawImage.size());
    ofs.flush();
    ofs.close();
}

}// namespace dwg
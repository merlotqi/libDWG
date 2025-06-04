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
#include <map>

namespace dwg {

class AppId;
class ExtendedData;
class CadObject;

class LIBDWG_API ExtendedDataDictionary
{
    std::map<AppId *, ExtendedData *> _data;

public:
    ExtendedDataDictionary(CadObject *owner);
    void add(AppId *app);
    void add(AppId *app, ExtendedData *extendedData);

    using iterator = std::map<AppId *, ExtendedData *>::iterator;
    using const_iterator = std::map<AppId *, ExtendedData *>::const_iterator;

    // clang-format off
    iterator begin() { return _data.begin(); }
    iterator end() { return _data.end(); }
    const_iterator begin() const { return _data.begin(); }
    const_iterator end() const { return _data.end(); }
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    // clang-format on
};

}// namespace dwg
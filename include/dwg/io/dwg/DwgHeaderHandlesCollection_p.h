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

#include <map>
#include <optional>
#include <string>

namespace dwg {

class DwgHeaderHandlesCollection
{
    std::map<std::string, unsigned long long> _handles;

public:
#define HANDLE_METHOD(handle)                        \
    std::optional<unsigned long long> handle() const \
    {                                                \
        return getHandle(#handle);                   \
    }                                                \
    void handle(unsigned long long value)            \
    {                                                \
        setHandle(#handle, value);                   \
    }

    HANDLE_METHOD(CMATERIAL)
    HANDLE_METHOD(CLAYER)
    HANDLE_METHOD(TEXTSTYLE)
    HANDLE_METHOD(CELTYPE)
    HANDLE_METHOD(DIMSTYLE)
    HANDLE_METHOD(CMLSTYLE)
    HANDLE_METHOD(UCSNAME_PSPACE)
    HANDLE_METHOD(UCSNAME_MSPACE)
    HANDLE_METHOD(PUCSORTHOREF)
    HANDLE_METHOD(PUCSBASE)
    HANDLE_METHOD(UCSORTHOREF)
    HANDLE_METHOD(DIMTXSTY)
    HANDLE_METHOD(DIMLDRBLK)
    HANDLE_METHOD(DIMBLK)
    HANDLE_METHOD(DIMBLK1)
    HANDLE_METHOD(DIMBLK2)
    HANDLE_METHOD(DICTIONARY_LAYOUTS)
    HANDLE_METHOD(DICTIONARY_PLOTSETTINGS)
    HANDLE_METHOD(DICTIONARY_PLOTSTYLES)
    HANDLE_METHOD(CPSNID)
    HANDLE_METHOD(PAPER_SPACE)
    HANDLE_METHOD(MODEL_SPACE)
    HANDLE_METHOD(BYLAYER)
    HANDLE_METHOD(BYBLOCK)
    HANDLE_METHOD(CONTINUOUS)
    HANDLE_METHOD(DIMLTYPE)
    HANDLE_METHOD(DIMLTEX1)
    HANDLE_METHOD(DIMLTEX2)
    HANDLE_METHOD(VIEWPORT_ENTITY_HEADER_CONTROL_OBJECT)
    HANDLE_METHOD(DICTIONARY_ACAD_GROUP)
    HANDLE_METHOD(DICTIONARY_ACAD_MLINESTYLE)
    HANDLE_METHOD(DICTIONARY_NAMED_OBJECTS)
    HANDLE_METHOD(BLOCK_CONTROL_OBJECT)
    HANDLE_METHOD(LAYER_CONTROL_OBJECT)
    HANDLE_METHOD(STYLE_CONTROL_OBJECT)
    HANDLE_METHOD(LINETYPE_CONTROL_OBJECT)
    HANDLE_METHOD(VIEW_CONTROL_OBJECT)
    HANDLE_METHOD(UCS_CONTROL_OBJECT)
    HANDLE_METHOD(VPORT_CONTROL_OBJECT)
    HANDLE_METHOD(APPID_CONTROL_OBJECT)
    HANDLE_METHOD(DIMSTYLE_CONTROL_OBJECT)
    HANDLE_METHOD(DICTIONARY_MATERIALS)
    HANDLE_METHOD(DICTIONARY_COLORS)
    HANDLE_METHOD(DICTIONARY_VISUALSTYLE)
    HANDLE_METHOD(INTERFEREOBJVS)
    HANDLE_METHOD(INTERFEREVPVS)
    HANDLE_METHOD(DRAGVS)
    HANDLE_METHOD(UCSBASE)

private:
    std::optional<unsigned long long> getHandle(const std::string &) const;
    void setHandle(const std::string &, unsigned long long);
};


}// namespace dwg
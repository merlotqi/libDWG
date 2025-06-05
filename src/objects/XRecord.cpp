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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/objects/XRecord.h>

namespace dwg {

    XRecord::XRecord() {}

    XRecord::XRecord(const std::string &name) : NonGraphicalObject(name) {}

    XRecord::~XRecord() {}

    ObjectType XRecord::objectType() const { return ObjectType::XRECORD; }

    std::string XRecord::objectName() const { return DxfFileToken::ObjectXRecord; }

    std::string XRecord::subclassMarker() const { return DxfSubclassMarker::XRecord; }

    DictionaryCloningFlags XRecord::cloningFlags() const { return _cloningFlags; }

    void XRecord::setCloningFlags(DictionaryCloningFlags value)  {_cloningFlags = value; } 

    std::vector<XRecord::Entry> XRecord::entries() const { return _entries; }
    
    void XRecord::createEntry(int code, DwgVariant value) {}

}// namespace dwg
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

#include <dwg/GroupCodeValueType.h>
#include <dwg/objects/DictionaryCloningFlags.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <vector>

namespace dwg {

class LIBDWG_API DG_XRecord : public DG_NonGraphicalObject
{
public:
    struct Entry
    {
        int Code;
        CPL::Any Value;
        DG_GroupCodeValueType GroupCode;
        bool HasLinkedObject;
        DG_XRecord *Owner;
    };

public:
    DG_XRecord();

    DG_XRecord(const std::string &);

    DG_ObjectType objectType() const override;

    std::string objectName() const override;

    std::string subclassMarker() const override;

    DG_DictionaryCloningFlags CloningFlags() const;

    void CloningFlags(DG_DictionaryCloningFlags);

    std::vector<Entry> Entries() const;

    void CreateEntry(int code, CPL::Any value);
};

}// namespace dwg
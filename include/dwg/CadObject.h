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

#include <dwg/DxfFileToken.h>
#include <dwg/DxfSubclassMarker.h>
#include <dwg/IHandledCadObject.h>
#include <dwg/ObjectType.h>
#include <dwg/objects//CadDictionary.h>
#include <string>

namespace dwg {

class CadObject : public IHandledCadObject
{
protected:
    unsigned long long _handle;

public:
    CadObject() = default;
    virtual ~CadObject() = default;

    virtual dwg::ObjectType ObjectType() const = 0;
    virtual std::string ObjectName() const = 0;
    virtual std::string SubclassMarker() const = 0;
    unsigned long long Handle() const { return _handle; }

    unsigned long long OwnerHandle; // 330

protected:
    void Handle(unsigned long long value) { _handle = value; }
};


}// namespace dwg

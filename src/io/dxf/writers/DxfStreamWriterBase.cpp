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

#include <dwg/GroupCodeValue.h>
#include <dwg/IHandledCadObject.h>
#include <dwg/INamedCadObject.h>
#include <dwg/io/dxf/writers/DxfStreamWriterBase_p.h>
#include <dwg/utils/EndianConverter.h>
#include <dwg/DxfClassMap_p.h>
#include <dwg/utils/StringHelp.h>

namespace dwg {

DxfStreamWriterBase::DxfStreamWriterBase() {}

DxfStreamWriterBase::~DxfStreamWriterBase() {}

bool DxfStreamWriterBase::writeOptional() const
{
    return _writeOptional;
}

void DxfStreamWriterBase::write(DxfCode code, DwgVariant value, DxfClassMap *clsmap) 
{
    write((int) code, value, clsmap);
}

void DxfStreamWriterBase::write(int code, DwgVariant value, DxfClassMap *clsmap) 
{
    if (value.isEmpty())
    {
        return;
    }

    DxfProperty prop;
    if (clsmap && clsmap->dxfProperty(code, prop))
    {
       
    }

    writeDxfCode(code);

    if (value.Type == DwgVariant::STRING)
    {
        std::string s = value.asString();
        s = StringHelp::replace(s, "^", "^ ");
        s = StringHelp::replace(s, "\n", "^J");
        s = StringHelp::replace(s, "\r", "^M");
        s = StringHelp::replace(s, "\t", "^I");
        writeValue(code, s);
    }
    else
    {
        writeValue(code, value);
    }
}

void DxfStreamWriterBase::writeTrueColor(int code, const Color &color, DxfClassMap *clsmap) 
{
    unsigned char arr[4] = {0};
    arr[0] = (unsigned char) color.blue();
    arr[1] = (unsigned char) color.green();
    arr[2] = (unsigned char) color.red();
    arr[3] = 0;
    write(code, LittleEndianConverter::instance()->toInt32(arr), clsmap);
}

void DxfStreamWriterBase::writeCmColor(int code, const Color &color, DxfClassMap *clsmap)
{
    if (GroupCodeValue::transformValue(code) == GroupCodeValueType::Int16)
    {
        write(code, (short) color.approxIndex());
    }
    else
    {
        std::vector<unsigned char> arr(4, 0);
        if (color.isTrueColor())
        {
            arr[0] = (unsigned char) color.blue();
            arr[1] = (unsigned char) color.green();
            arr[2] = (unsigned char) color.red();
            arr[3] = 0b11000010;// 0xC2
        }
        else
        {
            arr[3] = 0b11000001;
            arr[0] = (unsigned char) color.index();
        }
        write(code, LittleEndianConverter::instance()->toInt32(arr.data()), clsmap);
    }
}

void DxfStreamWriterBase::writeHandle(int code, IHandledCadObject *value, DxfClassMap *clsmap)
{
    if (value)
    {
        write(code, value->handle(), clsmap);
    }
}

void DxfStreamWriterBase::writeName(int code, INamedCadObject *value, DxfClassMap *clsmap)
{
    if (value)
    {
        write(code, value->name(), clsmap);
    }
}

}// namespace dwg
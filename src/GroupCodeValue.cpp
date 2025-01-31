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

namespace dwg {

DG_GroupCodeValueType DG_GroupCodeValue::TransformValue(int code)
{
    if (code >= 0 && code <= 4) return DG_GroupCodeValueType::String;
    if (code == 5) return DG_GroupCodeValueType::Handle;
    if (code >= 6 && code <= 9) return DG_GroupCodeValueType::String;
    if (code >= 10 && code <= 39) return DG_GroupCodeValueType::Point3D;
    if (code >= 40 && code <= 59) return DG_GroupCodeValueType::Double;
    if (code >= 60 && code <= 79) return DG_GroupCodeValueType::Int16;
    if (code >= 90 && code <= 99) return DG_GroupCodeValueType::Int32;
    if (code == 100) return DG_GroupCodeValueType::String;
    if (code == 101) return DG_GroupCodeValueType::String;
    if (code == 102) return DG_GroupCodeValueType::String;
    if (code == 105) return DG_GroupCodeValueType::Handle;

    if (code >= 110 && code <= 119) return DG_GroupCodeValueType::Double;
    if (code >= 120 && code <= 129) return DG_GroupCodeValueType::Double;
    if (code >= 130 && code <= 139) return DG_GroupCodeValueType::Double;
    if (code >= 140 && code <= 149) return DG_GroupCodeValueType::Double;

    if (code >= 160 && code <= 169) return DG_GroupCodeValueType::Int64;

    if (code >= 170 && code <= 179) return DG_GroupCodeValueType::Int16;

    if (code >= 210 && code <= 239) return DG_GroupCodeValueType::Double;

    if (code >= 270 && code <= 279) return DG_GroupCodeValueType::Int16;

    if (code >= 280 && code <= 289) return DG_GroupCodeValueType::Byte;

    if (code >= 290 && code <= 299) return DG_GroupCodeValueType::Bool;

    if (code >= 300 && code <= 309) return DG_GroupCodeValueType::String;

    if (code >= 310 && code <= 319) return DG_GroupCodeValueType::Chunk;

    if (code >= 320 && code <= 329) return DG_GroupCodeValueType::Handle;

    if (code >= 330 && code <= 369) return DG_GroupCodeValueType::ObjectId;

    if (code >= 370 && code <= 379) return DG_GroupCodeValueType::Int16;
    if (code >= 380 && code <= 389) return DG_GroupCodeValueType::Int16;

    if (code >= 390 && code <= 399) return DG_GroupCodeValueType::ObjectId;

    if (code >= 400 && code <= 409) return DG_GroupCodeValueType::Int16;
    if (code >= 410 && code <= 419) return DG_GroupCodeValueType::String;
    if (code >= 420 && code <= 429) return DG_GroupCodeValueType::Int32;
    if (code >= 430 && code <= 439) return DG_GroupCodeValueType::String;
    if (code >= 440 && code <= 449) return DG_GroupCodeValueType::Int32;
    if (code >= 450 && code <= 459) return DG_GroupCodeValueType::Int32;
    if (code >= 460 && code <= 469) return DG_GroupCodeValueType::Double;
    if (code >= 470 && code <= 479) return DG_GroupCodeValueType::String;
    if (code >= 480 && code <= 481) return DG_GroupCodeValueType::Handle;

    if (code == 999) return DG_GroupCodeValueType::Comment;

    if (code >= 1000 && code <= 1003)
        return DG_GroupCodeValueType::ExtendedDataString;
    if (code == 1004) return DG_GroupCodeValueType::ExtendedDataChunk;
    if (code >= 1005 && code <= 1009)
        return DG_GroupCodeValueType::ExtendedDataHandle;
    if (code >= 1010 && code <= 1059)
        return DG_GroupCodeValueType::ExtendedDataDouble;
    if (code >= 1060 && code <= 1070)
        return DG_GroupCodeValueType::ExtendedDataInt16;
    if (code == 1071) return DG_GroupCodeValueType::ExtendedDataInt32;

    return DG_GroupCodeValueType::None;
}

}// namespace dwg
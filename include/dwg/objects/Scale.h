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

#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/base/Coordinate.h>
#include <type_traits>

namespace dwg {

class Scale : public NonGraphicalObject
{
public:
    static Scale Default;
    Scale() = default;
    Scale(const CPL::String &name);
    Scale(const CPL::String &name, double paperUnits, double drawingUnits,
          bool isUnitScale)
        : NonGraphicalObject(name), PaperUnits(paperUnits),
          DrawingUnits(drawingUnits), IsUnitScale(isUnitScale)
    {
    }

    dwg::ObjectType ObjectType() const { return ObjectType::UNLISTED; }
    CPL::String ObjectName() const { return DxfFileToken::ObjectScale; }
    CPL::String SubclassMarker() const { return DxfSubclassMarker::Scale; }

    // 140)]
    double PaperUnits;
    // 141)]
    double DrawingUnits;
    // 290)]
    bool IsUnitScale;

    double ScaleFactor() const { return PaperUnits / DrawingUnits; }


    double ApplyTo(double value) { return value * ScaleFactor(); }

    template<class T>
    T ApplyTo(T value)
    {
        T result;
        static_assert(std::is_base_of<IVector>::value, "");
        for (size_t i = 0; i < value.Dimension; ++i)
        {
            result[i] = ApplyTo(value[i]);
        }
        return result;
    }
};

Scale Scale::Default = Scale("1:1", 1.0, 1.0, true);
}// namespace dwg
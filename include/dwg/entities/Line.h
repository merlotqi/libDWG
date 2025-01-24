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

#include <dwg/entities/Entity.h>

namespace dwg {

class LIBDWG_API Line : public Entity
{
    XYZ _normal = XYZ::AxisZ;
    XYZ _startPoint = XYZ::Zero;
    XYZ _endPoint = XYZ::Zero;
    double _thickness = 0.0;

public:
    Line();
    
    ~Line();

    dwg::ObjectType ObjectType() const override;

    CPL::String ObjectName() const override;

    CPL::String SubclassMarker() const override;

    XYZ Normal() const;

    void Normal(const XYZ &);

    XYZ StartPoint() const;

    void StartPoint(const XYZ &);

    XYZ EndPoint() const;

    void EndPoint(const XYZ &);

    double Thickness() const;

    void Thickness(double);
};
CPL_SMARTER_PTR(Line)

}// namespace dwg

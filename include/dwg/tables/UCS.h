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

#include <dwg/Coordinate.h>
#include <dwg/OrthographicType.h>
#include <dwg/tables/TableEntry.h>

namespace dwg {

class LIBDWG_API UCS : public TableEntry
{
public:
    UCS();
    UCS(const std::string &name);
    ~UCS();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    XYZ origin() const;
    void setOrigin(const XYZ &);

    XYZ xAxis() const;
    void setXAxis(const XYZ &);

    XYZ yAxis() const;
    void setYAxis(const XYZ &);

    OrthographicType orthographicType() const;
    void setOrthographicType(OrthographicType);

    OrthographicType orthographicViewType() const;
    void setOrthographicViewType(OrthographicType);

    double elevation() const;
    void setElevation(double);

private:
    XYZ _origin = XYZ::Zero;
    XYZ _xAxis = XYZ::Zero;
    XYZ _yAxis = XYZ::Zero;
    OrthographicType _orthographicType = OrthographicType::None;
    OrthographicType _orthographicViewType = OrthographicType::None;
    double _elevation = 0.0;
};

}// namespace dwg
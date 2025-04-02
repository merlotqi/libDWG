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

#include <dwg/entities/Dimension.h>

namespace dwg {

class LIBDWG_API DimensionAligned : public Dimension
{
    XYZ _firstPoint;        // The first point of the aligned dimension
    XYZ _secondPoint;       // The second point of the aligned dimension
    double _extLineRotation;// Rotation angle for the extension lines of the aligned dimension

public:
    DimensionAligned();
    ~DimensionAligned();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    XYZ firstPoint() const;
    void setFirstPoint(const XYZ &value);

    XYZ secondPoint() const;
    void setSecondPoint(const XYZ &value);

    double extLineRotation() const;
    void setExtLineRotation(double value);

    virtual double measurement() const override;

protected:
    DimensionAligned(DimensionType type);
};

}// namespace dwg
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
#include <dwg/entities/UnderlayDisplayFlags.h>

namespace dwg {

class UnderlayDefinition;

class LIBDWG_API UnderlayEntity : public Entity
{
    XYZ _normal;
    XYZ _insertPoint;
    double _xscale;
    double _yscale;
    double _zscale;
    double _rotation;
    UnderlayDisplayFlags _flags;
    unsigned char _contrast;
    unsigned char _fade;
    UnderlayDefinition *_definition;

public:
    UnderlayEntity();
    ~UnderlayEntity();

    std::string subclassMarker() const override;

    XYZ normal() const;
    void setNormal(const XYZ &);

    XYZ insertPoint() const;
    void setInsertPoint(const XYZ &);

    double xScale() const;
    void setXScale(double);

    double yScale() const;
    void setYScale(double);

    double zScale() const;
    void setZScale(double);

    double rotation() const;
    void setRotation(double);

    UnderlayDisplayFlags flags() const;
    void setFlags(UnderlayDisplayFlags);

    unsigned char contrast() const;
    void setContrast(unsigned char);

    unsigned char fade() const;
    void setFade(unsigned char);

    UnderlayDefinition *definition() const;
    void setDefinition(UnderlayDefinition *);
};

}// namespace dwg
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

class DG_UnderlayDefinition;
CPL_SMARTER_PTR(DG_UnderlayDefinition)

class LIBDWG_API DG_UnderlayEntity : public DG_Entity
{
    XYZ _normal;
    XYZ _insertPoint;
    double _xscale;
    double _yscale;
    double _zscale;
    double _rotation;
    DG_UnderlayDisplayFlags _flags;
    unsigned char _contrast;
    unsigned char _fade;
    DG_UnderlayDefinitionWPtr _definition;

public:
    DG_UnderlayEntity();
    ~DG_UnderlayEntity();

    CPL::String SubclassMarker() const;

    XYZ Normal() const;
    void Normal(const XYZ &);

    XYZ InsertPoint() const;
    void InsertPoint(const XYZ &);

    double XScale() const;
    void XScale(double);

    double YScale() const;
    void YScale(double);

    double ZScale() const;
    void ZScale(double);

    double Rotation() const;
    void Rotation(double);

    DG_UnderlayDisplayFlags Flags() const;
    void Flags(DG_UnderlayDisplayFlags);

    unsigned char Contrast() const;
    void Contrast(unsigned char);

    unsigned char Fade() const;
    void Fade(unsigned char);

    DG_UnderlayDefinitionPtr Definition() const;
    void Definition(DG_UnderlayDefinition *);
};
CPL_SMARTER_PTR(DG_UnderlayEntity)

}// namespace dwg

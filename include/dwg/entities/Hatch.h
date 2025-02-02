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

#include <dwg/Color.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/HatchPatternType.h>
#include <dwg/entities/HatchStyleType.h>

namespace dwg {

class DG_HatchPattern;
class DG_HatchBoundaryPath;
class DG_HatchGradientPattern;
class LIBDWG_API DG_Hatch : public DG_Entity
{
public:
    DG_Hatch();
    ~DG_Hatch();
    // Override to return the object type of the Arc
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual std::string ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string SubclassMarker() const override;

    double Elevation() const;
    void Elevation(double elevation);

    XYZ Normal() const;
    void Normal(const XYZ &);

    DG_HatchPattern *Pattern() const;
    void Pattern(DG_HatchPattern *);

    bool IsSolid() const;
    void IsSolid(bool);

    bool IsAssociative() const;
    void IsAssociative(bool);

    DG_HatchStyleType Style() const;
    void Style(DG_HatchStyleType);

    DG_HatchPatternType PatternType() const;
    void PatternType(DG_HatchPatternType);

    double PatternAngle() const;
    void PatternAngle(double);

    double PatternScale() const;
    void PatternScale(double);

    bool IsDouble() const;
    void IsDouble(bool);

    double PixelSize() const;
    void PixelSize(double);

    std::vector<XY> SeedPoints() const;
    void SeedPoints(const std::vector<XY> &);

    DG_HatchGradientPattern *GradientColor() const;
    void GradientColor(DG_HatchGradientPattern *);

    std::vector<DG_HatchBoundaryPath *> Paths() const;
    void Paths(const std::vector<DG_HatchBoundaryPath *> &);
};

}// namespace dwg

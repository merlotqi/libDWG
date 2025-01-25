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
#include <dwg/entities/MLineFlags.h>
#include <dwg/entities/MLineJustification.h>
#include <dwg/entities/Vertex.h>

namespace dwg {

class DG_MLineStyle;
CPL_SMARTER_PTR(DG_MLineStyle);

class LIBDWG_API DG_MLine : public DG_Entity
{
    DG_MLineStyleWPtr _style;
    double _scaleFactor;
    DG_MLineJustification _justification;
    DG_MLineFlags _flags;
    XYZ _startPoint;
    XYZ _normal;

public:
    struct Segment
    {
        std::vector<double> Parameters;
        std::vector<double> AreaFillParameters;
    };

    struct Vertex
    {
        XYZ Position;
        XYZ Direction;
        XYZ Miter;
        std::vector<Segment> Segments;
    };

public:
    DG_MLine();
    ~DG_MLine();

    // Override to return the object type of the Arc
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    DG_MLineStylePtr Style() const;
    void Style(DG_MLineStyle *);

    double ScaleFactor() const;
    void ScaleFactor(double);

    DG_MLineJustification Justification() const;
    void Justification(DG_MLineJustification);

    DG_MLineFlags Flags() const;
    void Flags(DG_MLineFlags);

    XYZ StartPoint() const;
    void StartPoint(const XYZ &);

    XYZ Normal() const;
    void Normal(const XYZ &);

    std::vector<Vertex> Vertices() const;
    void Vertices(const std::vector<Vertex> &);

private:
    std::vector<Vertex> _vertices;
};
CPL_SMARTER_PTR(DG_MLine)

}// namespace dwg

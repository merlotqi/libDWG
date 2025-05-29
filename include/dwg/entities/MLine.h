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

class MLineStyle;

class LIBDWG_API MLine : public Entity
{
    MLineStyle *_style;               ///< Pointer to the multiline style.
    double _scaleFactor;              ///< Scale factor for the multiline.
    MLineJustification _justification;///< Justification of the multiline.
    MLineFlags _flags;                ///< Flags indicating properties of the multiline.
    XYZ _startPoint;                  ///< Start point of the multiline.
    XYZ _normal;                      ///< Normal vector defining the plane of the multiline.

public:
    struct Segment
    {
        std::vector<double> Parameters;        ///< Parameters defining segment positions.
        std::vector<double> AreaFillParameters;///< Parameters for area fill.
    };

    struct Vertex
    {
        XYZ Position;                 ///< Position of the vertex.
        XYZ Direction;                ///< Direction vector at the vertex.
        XYZ Miter;                    ///< Mitering vector for joint handling.
        std::vector<Segment> Segments;///< Segments associated with the vertex.
    };

public:
    MLine();
    ~MLine();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    MLineStyle *style() const;
    void setStyle(MLineStyle *style);

    double scaleFactor() const;
    void setScaleFactor(double scale);

    MLineJustification justification() const;
    void setJustification(MLineJustification justification);

    MLineFlags flags() const;
    void setFlags(MLineFlags flags);

    XYZ startPoint() const;
    void setStartPoint(const XYZ &point);

    XYZ normal() const;
    void setNormal(const XYZ &normal);

    std::vector<Vertex> vertices() const;
    void setVertices(const std::vector<Vertex> &vertices);

private:
    std::vector<Vertex> _vertices;///< List of vertices defining the multiline.
};

}// namespace dwg
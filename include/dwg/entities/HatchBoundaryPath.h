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

#include <dwg/entities/BoundaryPathFlags.h>
#include <dwg/entities/Entity.h>
#include <vector>

namespace dwg {

class HatchBoundaryPath
{
public:
    HatchBoundaryPath();
    ~HatchBoundaryPath();

    bool isPolyline();

    // 92
    BoundaryPathFlags flags() const;
    void flags(BoundaryPathFlags value);


    enum EdgeType
    {
        Polyline = 0,
        Line = 1,
        CircularArc = 2,
        EllipticArc = 3,
        Spline = 4,
    };

    class Edge
    {
    public:
        Edge();
        ~Edge();

        EdgeType Type() const;
        Edge *clone() const;
    };

    // 93
    std::vector<Edge *> Edges;
    std::vector<Entity *> entities;

    class Arc : Edge
    {
    public:
        Arc();
        ~Arc();
        EdgeType Type() const { return EdgeType::CircularArc; }
        XY center;            // 10, 20
        double radius;        // 40
        double startAngle;    // 50
        double endAngle;      // 51
        bool counterClockWise;// 73
    };

    class Ellipse : Edge
    {
    public:
        Ellipse();
        ~Ellipse();

        EdgeType Type() const { return EdgeType::EllipticArc; }
        XY center;               // 10, 20
        XY majorAxisEndPoint;    // 11, 21
        double minorToMajorRatio;// 40
        double startAngle;       // 50
        double endAngle;         // 51
        bool counterClockWise;   // 73
    };

    class Line : Edge
    {
    public:
        Line();
        ~Line();
        EdgeType Type() const { return EdgeType::Line; }
        XY start;// 10, 20
        XY end;  // 11, 21
    };

    class Polyline : Edge
    {
    public:
        Polyline();
        ~Polyline();
        EdgeType Type() const { return EdgeType::Polyline; }

        bool hasBulge;             // 72
        bool isClosed;             // 73
        std::vector<XYZ> vertices; // count 93
        std::vector<double> bulges;// 42
    };

    class Spline : Edge
    {
    public:
        Spline();
        ~Spline();

        int degree;                    // 94
        bool rational;                 // 73
        bool periodic;                 // 74
        std::vector<double> knots;     // 95
        std::vector<XYZ> controlPoints;// 96

        std::vector<XY> fitPoints;// 97
        XY startTangent;          // 12, 22
        XY endTangent;            // 13, 23
    };
};

}// namespace dwg

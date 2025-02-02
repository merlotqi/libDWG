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
#include <dwg/entities/BoundaryPathFlags.h>
#include <dwg/exports.h>
#include <vector>

namespace dwg {

class DG_Entity;
/**
 * @class DG_HatchBoundaryPath
 * @brief Represents a hatch boundary path in a DWG/DXF drawing.
 *
 * This class defines a hatch boundary, which consists of multiple edge types such as lines,
 * arcs, polylines, splines, and ellipses. These boundaries are used to define hatch areas.
 */
class LIBDWG_API DG_HatchBoundaryPath
{
public:
    /**
     * @enum HBP_EdgeType
     * @brief Defines the types of edges in a hatch boundary path.
     */
    enum class HBP_EdgeType
    {
        HBP_Polyline,   ///< A polyline edge.
        HBP_Line,       ///< A straight line edge.
        HBP_CircularArc,///< A circular arc edge.
        HBP_EllipticArc,///< An elliptic arc edge.
        HBP_Spline      ///< A spline edge.
    };

    /**
     * @class HBP_Edge
     * @brief Base class representing an edge in a hatch boundary path.
     */
    class LIBDWG_API HBP_Edge
    {
    public:
        HBP_Edge();
        virtual ~HBP_Edge();

        /**
         * @brief Gets the edge type.
         * @return The type of the edge.
         */
        virtual HBP_EdgeType Type() const = 0;

        /**
         * @brief Clones the edge.
         * @return A pointer to the cloned edge.
         */
        virtual HBP_Edge *Clone() const;
    };

public:
    DG_HatchBoundaryPath();
    ~DG_HatchBoundaryPath();

    /**
     * @brief Checks if the boundary path is a polyline.
     * @return True if the boundary path is a polyline, false otherwise.
     */
    bool IsPolyline() const;

    /**
     * @brief Gets the boundary path flags.
     * @return The boundary path flags.
     */
    DG_BoundaryPathFlags Flags() const;

    /**
     * @brief Sets the boundary path flags.
     * @param flags The boundary path flags to set.
     */
    void Flags(DG_BoundaryPathFlags);

    /**
     * @brief Gets the list of edges in the boundary path.
     * @return A vector of edge pointers.
     */
    std::vector<HBP_Edge *> Edges() const;

    /**
     * @brief Sets the edges in the boundary path.
     * @param edges The vector of edge pointers to set.
     */
    void Edges(const std::vector<HBP_Edge *> &edges);

    /**
     * @brief Gets the list of entities in the boundary path.
     * @return A vector of entity pointers.
     */
    std::vector<DG_Entity *> Entities() const;

    /**
     * @brief Sets the entities in the boundary path.
     * @param entities The vector of entity pointers to set.
     */
    void Entities(const std::vector<DG_Entity *> &entities);

public:
    /**
     * @class HBP_Arc
     * @brief Represents an arc edge in a hatch boundary path.
     */
    class LIBDWG_API HBP_Arc : public HBP_Edge
    {
        XY _center;
        double _radius;
        double _startAngle;
        double _endAngle;
        bool _counterClockWise;

    public:
        HBP_Arc();
        ~HBP_Arc();
        HBP_EdgeType Type() const;

        XY Center() const;
        void Center(const XY &);

        double Radius() const;
        void Radius(double);

        double StartAngle() const;
        void StartAngle(double);

        double EndAngle() const;
        void EndAngle(double);

        bool CounterClockWise() const;
        void CounterClockWise(bool);
    };

    /**
     * @class HBP_Ellipse
     * @brief Represents an elliptical arc edge in a hatch boundary path.
     */
    class LIBDWG_API HBP_Ellipse : public HBP_Edge
    {
        XY _center;
        XY _majorAxisEndPoint;
        double _minorToMajorRatio;
        double _startAngle;
        double _endAngle;
        bool _counterClockWise;

    public:
        HBP_Ellipse();
        ~HBP_Ellipse();

        HBP_EdgeType Type() const;

        XY Center() const;
        void Center(const XY &);

        XY MajorAxisEndPoint() const;
        void MajorAxisEndPoint(const XY &);

        double MinorToMajorRatio() const;
        void MinorToMajorRatio(double);

        double StartAngle() const;
        void StartAngle(double);

        double EndAngle() const;
        void EndAngle(double);

        bool CounterClockWise() const;
        void CounterClockWise(bool);
    };

    /**
     * @class HBP_Line
     * @brief Represents a line edge in a hatch boundary path.
     */
    class LIBDWG_API HBP_Line : public HBP_Edge
    {
        XY _start;
        XY _end;

    public:
        HBP_Line();
        ~HBP_Line();
        HBP_EdgeType Type() const;

        XY Start() const;
        void Start(const XY &);

        XY End() const;
        void End(const XY &);
    };

    /**
     * @class HBP_Polyline
     * @brief Represents a polyline edge in a hatch boundary path.
     */
    class LIBDWG_API HBP_Polyline : public HBP_Edge
    {
        bool _closed;
        std::vector<XYZ> _vertices;
        std::vector<double> _bulges;

    public:
        HBP_Polyline();
        ~HBP_Polyline();
        HBP_EdgeType Type() const;

        bool HasBulge() const;

        bool IsClosed() const;
        void IsClosed(bool);

        std::vector<XYZ> Vertices() const;
        void Vertices(const std::vector<XYZ> &);

        std::vector<double> Bulges() const;
        void Bulges(const std::vector<double> &);
    };

    /**
     * @class HBP_Spline
     * @brief Represents a spline edge in a hatch boundary path.
     */
    class LIBDWG_API HBP_Spline : public HBP_Edge
    {
        int _degree;
        bool _rational;
        bool _periodic;
        std::vector<double> _knots;
        std::vector<XYZ> _controlPoints;
        std::vector<XY> _fitPoints;
        XY _startTangent;
        XY _endTangent;

    public:
        HBP_Spline();
        ~HBP_Spline();
        HBP_EdgeType Type() const;

        int Degree() const;
        void Degree(int);

        bool Rational() const;
        void Rational(bool);

        bool Periodic() const;
        void Periodic(bool);

        std::vector<double> Knots() const;
        void Knots(const std::vector<double> &);

        std::vector<XYZ> ControlPoints() const;
        void ControlPoints(const std::vector<XYZ> &);

        std::vector<XY> FitPoints() const;
        void FitPoints(const std::vector<XY> &);

        XY StartTangent() const;
        void StartTangent(const XY &);

        XY EndTangent() const;
        void EndTangent(const XY &);
    };
};

}// namespace dwg

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

class Entity;
/**
 * @class HatchBoundaryPath
 * @brief Represents a hatch boundary path in a DWG/DXF drawing.
 *
 * This class defines a hatch boundary, which consists of multiple edge types such as lines,
 * arcs, polylines, splines, and ellipses. These boundaries are used to define hatch areas.
 */
class LIBDWG_API HatchBoundaryPath
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
        virtual HBP_EdgeType type() const = 0;

        /**
         * @brief Clones the edge.
         * @return A pointer to the cloned edge.
         */
        virtual HBP_Edge *clone() const;
    };

public:
    HatchBoundaryPath();
    ~HatchBoundaryPath();

    /**
     * @brief Checks if the boundary path is a polyline.
     * @return True if the boundary path is a polyline, false otherwise.
     */
    bool isPolyline() const;

    /**
     * @brief Gets the boundary path flags.
     * @return The boundary path flags.
     */
    BoundaryPathFlags flags() const;

    /**
     * @brief Sets the boundary path flags.
     * @param flags The boundary path flags to set.
     */
    void setFlags(BoundaryPathFlags);

    /**
     * @brief Gets the list of edges in the boundary path.
     * @return A vector of edge pointers.
     */
    std::vector<HBP_Edge *> edges() const;

    /**
     * @brief Sets the edges in the boundary path.
     * @param edges The vector of edge pointers to set.
     */
    void setEdges(const std::vector<HBP_Edge *> &edges);

    /**
     * @brief Gets the list of entities in the boundary path.
     * @return A vector of entity pointers.
     */
    std::vector<Entity *> entities() const;

    /**
     * @brief Sets the entities in the boundary path.
     * @param entities The vector of entity pointers to set.
     */
    void setEntities(const std::vector<Entity *> &entities);

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
        HBP_EdgeType type() const;

        XY center() const;
        void setCenter(const XY &);

        double radius() const;
        void setRadius(double);

        double startAngle() const;
        void setStartAngle(double);

        double endAngle() const;
        void setEndAngle(double);

        bool counterClockWise() const;
        void setCounterClockWise(bool);
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

        HBP_EdgeType type() const;

        XY center() const;
        void setCenter(const XY &);

        XY majorAxisEndPoint() const;
        void setMajorAxisEndPoint(const XY &);

        double minorToMajorRatio() const;
        void setMinorToMajorRatio(double);

        double startAngle() const;
        void setStartAngle(double);

        double endAngle() const;
        void setEndAngle(double);

        bool counterClockWise() const;
        void setCounterClockWise(bool);
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
        HBP_EdgeType type() const;

        XY start() const;
        void setStart(const XY &);

        XY end() const;
        void setEnd(const XY &);
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
        HBP_EdgeType type() const;

        bool hasBulge() const;

        bool isClosed() const;
        void setIsClosed(bool);

        std::vector<XYZ> vertices() const;
        void setVertices(const std::vector<XYZ> &);

        std::vector<double> bulges() const;
        void setBulges(const std::vector<double> &);
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
        HBP_EdgeType type() const;

        int degree() const;
        void setDegree(int);

        bool rational() const;
        void setRational(bool);

        bool periodic() const;
        void setPeriodic(bool);

        std::vector<double> knots() const;
        void setKnots(const std::vector<double> &);

        std::vector<XYZ> controlPoints() const;
        void setControlPoints(const std::vector<XYZ> &);

        std::vector<XY> fitPoints() const;
        void setFitPoints(const std::vector<XY> &);

        XY startTangent() const;
        void setStartTangent(const XY &);

        XY endTangent() const;
        void setEndTangent(const XY &);
    };
};

}// namespace dwg

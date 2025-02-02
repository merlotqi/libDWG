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

namespace dwg {

/**
 * @class DG_Mesh
 * @brief Represents a mesh entity in a DWG/DXF drawing.
 *
 * A mesh is a collection of vertices, edges, and faces that define a 3D shape.
 * It supports features like subdivision levels and crease blending for smooth surfaces.
 */
class LIBDWG_API DG_Mesh : public DG_Entity
{
public:
    /**
     * @struct Edge
     * @brief Represents an edge in the mesh.
     *
     * An edge connects two vertices and can have a crease value 
     * to control smoothness in subdivision surfaces.
     */
    struct Edge
    {
        int Start;    ///< Index of the starting vertex.
        int End;      ///< Index of the ending vertex.
        double Crease;///< Crease value for subdivision (default: 0.0).

        /**
         * @brief Constructs an Edge with given start and end vertices.
         * @param start Index of the starting vertex.
         * @param end Index of the ending vertex.
         */
        Edge(int start, int end);
    };

public:
    /**
     * @brief Constructs a DG_Mesh object.
     */
    DG_Mesh();

    /**
     * @brief Destroys the DG_Mesh object.
     */
    virtual ~DG_Mesh();

    /**
     * @brief Gets the version of the mesh format.
     * @return The version as a short integer.
     */
    short Version() const;

    /**
     * @brief Sets the version of the mesh format.
     * @param version The version as a short integer.
     */
    void Version(short version);

    /**
     * @brief Checks if blend crease is enabled.
     * @return True if blend crease is enabled, false otherwise.
     */
    bool BlendCrease() const;

    /**
     * @brief Enables or disables blend crease.
     * @param blend True to enable blend crease, false to disable.
     */
    void BlendCrease(bool blend);

    /**
     * @brief Gets the subdivision level of the mesh.
     * @return The subdivision level as an integer.
     */
    int SubdivisionLevel() const;

    /**
     * @brief Sets the subdivision level of the mesh.
     * @param level The subdivision level as an integer.
     */
    void SubdivisionLevel(int level);

    /**
     * @brief Gets the list of vertices in the mesh.
     * @return A vector of XYZ representing the vertices.
     */
    std::vector<XYZ> Vertices() const;

    /**
     * @brief Sets the list of vertices in the mesh.
     * @param vertices A vector of XYZ representing the vertices.
     */
    void Vertices(const std::vector<XYZ> &vertices);

    /**
     * @brief Gets the list of faces in the mesh.
     *
     * Each face is represented as a vector of vertex indices.
     * @return A vector of faces, where each face is a vector of int.
     */
    std::vector<std::vector<int>> Faces() const;

    /**
     * @brief Sets the list of faces in the mesh.
     * @param faces A vector of faces, where each face is a vector of int.
     */
    void Faces(const std::vector<std::vector<int>> &faces);

    /**
     * @brief Gets the list of edges in the mesh.
     * @return A vector of DG_Mesh::Edge objects.
     */
    std::vector<DG_Mesh::Edge> Edges() const;

    /**
     * @brief Sets the list of edges in the mesh.
     * @param edges A vector of DG_Mesh::Edge objects.
     */
    void Edges(const std::vector<DG_Mesh::Edge> &edges);
};

}// namespace dwg

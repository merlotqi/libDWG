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

#include <dwg/objects/NonGraphicalObject.h>
#include <vector>

namespace dwg {

class EvaluationExpression;
class LIBDWG_API EvaluationGraph : public NonGraphicalObject
{
public:
    struct Node
    {
        int Index;            
        int NextNodeIndex;    
        Node *Next;      
        int Flags;            
        int Data1;            
        int Data2;            
        int Data3;            
        int Data4;            
        CadObject *NodeObject;
        EvaluationExpression *Expression;
    };

    struct Edge
    {

    };

public:
    static constexpr auto DictionaryEntryName = "ACAD_ENHANCEDBLOCK";

    EvaluationGraph();
    ~EvaluationGraph();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    int value96() const;
    void setValue96(int);

    int value97() const;
    void setValue97(int);

    std::vector<Node> nodes() const;
    void setNodes(const std::vector<Node> &);

    std::vector<Edge> edges() const;
    void setEdges(const std::vector<Edge> &);
};

}// namespace dwg
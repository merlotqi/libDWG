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

#include <dwg/objects/evaluations/Block1PtParameter.h>
#include <vector>

namespace dwg {

class Entity;
class LIBDWG_API BlockVisibilityParameter : public Block1PtParameter
{
public:
    struct State
    {
        std::string Name;
        std::vector<Entity *> Entities;
        std::vector<EvaluationExpression *> Expressions;
    };

public:
    BlockVisibilityParameter();
    ~BlockVisibilityParameter();

    std::string subclassMarker() const override;

    std::vector<Entity *> entities() const;
    void setEntities(const std::vector<Entity *> &);

    std::vector<State> states() const;
    void setStates(const std::vector<State> &);

    std::string name() const;
    void setName(const std::string &);

    std::string description() const;
    void setDescription(const std::string &);

    bool value91() const;
    void setValue91(bool);
};

}// namespace dwg
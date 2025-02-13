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

#include <dwg/CadObject.h>

namespace dwg {

class LIBDWG_API EvaluationExpression : public CadObject
{
public:
    EvaluationExpression();
    virtual ~EvaluationExpression();

    ObjectType objectType() const override;
    std::string subclassMarker() const override;

    int value90() const;
    void setValue90(int value) const;

    int value98() const;
    void setValue98(int value);

    int value99() const;
    void setValue99(int value);
};

class LIBDWG_API BlockElement : public EvaluationExpression
{
public:
    BlockElement();
    virtual ~BlockElement();

    std::string subclassMarker() const override;

    std::string elementName() const;
    void setElementName(const std::string &name);

    int value1071() const;
    void setValue1071(int value);
};

class LIBDWG_API BlockParameter : public BlockElement
{
public:
    BlockParameter();
    virtual ~BlockParameter();

    std::string subclassMarker() const override;

    bool value280() const;
    void setValue280(bool);

    bool value281() const;
    void setValue281(bool);
};

class LIBDWG_API Block1PtParameter : public BlockParameter
{
public:
    Block1PtParameter();
    virtual ~Block1PtParameter();

    std::string subclassMarker() const override;

    XYZ location() const;
    void setLocation(const XYZ &value);

    long long value93() const;
    void setValue93(long long value);

    short value170() const;
    void setValue170(short value);

    short value171() const;
    void setValue171(short value);
};

class LIBDWG_API Block2PtParameter : public BlockParameter
{
public:
    Block2PtParameter();
    virtual ~Block2PtParameter();

    std::string subclassMarker() const override;

    XYZ firstPoint() const;
    void setFirstPoint(const XYZ &);

    XYZ secondPoint() const;
    void setSecondPoint(const XYZ &);
};

class LIBDWG_API BlockLinearParameter : public Block2PtParameter
{
public:
    BlockLinearParameter();
    virtual ~BlockLinearParameter();

    ObjectType objectType() const override;
    std::string subclassMarker() const override;
    std::string subclassMarker() const override;

    std::string label() const;
    void setLabel(const std::string &);

    std::string description() const;
    void setDescription(const std::string &);

    double labelOffset() const;
    void setLabelOffset(double);
};

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
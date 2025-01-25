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
#include <dwg/Color.h>
#include <dwg/Coordinate.h>
#include <dwg/LineWeightType.h>
#include <dwg/Transparency.h>

namespace dwg {

class DG_Layer;
CPL_SMARTER_PTR(DG_Layer)

class DG_LineType;
CPL_SMARTER_PTR(DG_LineType)

class DG_BookColor;
CPL_SMARTER_PTR(DG_BookColor)

class LIBDWG_API DG_Entity : public DG_CadObject
{
    DG_LayerWPtr _layer;
    DG_Color _color;
    DG_LineweightType _lineweight;
    double _linetypeScale;
    bool _isInvisible;
    DG_Transparency _transparency;
    DG_LineTypeWPtr _linetype;
    DG_BookColorWPtr _bookColor;

public:
    DG_Entity();

    virtual ~DG_Entity();

    CPL::String SubclassMarker() const;

    virtual DG_LayerPtr Layer() const;

    virtual void Layer(DG_Layer *);

    virtual DG_Color Color() const;

    virtual void Color(const DG_Color &);

    virtual DG_LineweightType Lineweight() const;

    virtual void Lineweight(DG_LineweightType);

    virtual double LinetypeScale() const;

    virtual void LinetypeScale(double);

    virtual bool IsInvisible() const;

    virtual void IsInvisible(bool);

    virtual DG_Transparency Transparency() const;

    virtual void Transparency(DG_Transparency);

    virtual DG_LineTypePtr LineType() const;

    virtual void LineType(DG_LineType *) const;

    virtual void MatchProperties(DG_Entity *entity);
};
CPL_SMARTER_PTR(DG_Entity)

}// namespace dwg

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

#include <dwg/tables/Layer.h>
#include <dwg/tables/LineType.h>
#include <dwg/Color.h>
#include <dwg/LineweightType.h>
#include <dwg/Transparency.h>
#include <dwg/IHandleCadObject.h>

namespace dwg {

class LIBDWG_API IEntity : public IHandledCadObject
{
public:
    virtual LayerPtr Layer() const = 0;
    virtual void Layer(Layer*) = 0;
    virtual dwg::Color Color() const = 0;
    virtual void Color(dwg::Color) = 0;
    virtual LineweightType Lineweight() const = 0;
    virtual void Lineweight(LineweightType) = 0;
    virtual double LinetypeScale() const = 0;
    virtual void LinetypeScale(double) = 0;
    virtual bool IsInvisible() const = 0;
    virtual void IsInvisible(bool ) = 0;
    virtual dwg::Transparency Transparency() const = 0;
    virtual void Transparency(dwg::Transparency) = 0;
    virtual LineTypePtr LineType() const = 0;
    virtual void LineType(dwg::LineType* ) const = 0;
    // Material object (present if not BYLAYER)
    // virtual MaterialPtr Material() const = 0;
    // virtual void Material(dwg::Material*) = 0;
    virtual void MatchProperties(IEntity* entity) = 0;
};
SMARTER_PTR(IEntity)

}
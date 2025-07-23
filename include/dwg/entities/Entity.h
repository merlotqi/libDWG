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

class Layer;
class LineType;
class BookColor;
class Material;

class LIBDWG_API Entity : public CadObject
{
    RTTR_ENABLE(CadObject)

public:
    Entity();
    virtual ~Entity();

    std::string subclassMarker() const override;

    virtual BookColor *bookColor() const;
    virtual void setBookColor(BookColor *);

    virtual Color color() const;
    virtual void setColor(const Color &);

    virtual bool isInvisible() const;
    virtual void setIsInvisible(bool);

    virtual Layer *layer() const;
    virtual void setLayer(Layer *);

    virtual LineType *lineType() const;
    virtual void setLineType(LineType *);

    virtual double linetypeScale() const;
    virtual void setLinetypeScale(double);

    virtual LineweightType lineweight() const;
    virtual void setLineweight(LineweightType);

    virtual Material *material() const;
    virtual void setMaterial(Material *);

    virtual Transparency transparency() const;
    virtual void setTransparency(const Transparency &);

    virtual void matchProperties(Entity *entity);

    void assignDocument(CadDocument *doc) override;
    void unassignDocument() override;

protected:
    void tableOnRemove(CadObject *item);

private:
    Layer *_layer;
    Color _color;
    LineweightType _lineweight;
    double _linetypeScale;
    bool _isInvisible;
    Transparency _transparency;
    LineType *_linetype;
    BookColor *_bookColor;
    Material *_material;
};

}// namespace dwg
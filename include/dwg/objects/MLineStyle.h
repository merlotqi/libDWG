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

#include <dwg/Color.h>
#include <dwg/objects/MLineStyleFlags.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/objects/ObjectDictionaryCollection.h>

namespace dwg {

class LineType;
class CadDictionary;

class LIBDWG_API MLineStyle : public NonGraphicalObject
{
public:
    struct Element
    {
        double offset;
        Color color;
        LineType *lineType;
    };

public:
    MLineStyle();
    MLineStyle(const std::string &name);

    static constexpr auto DefaultName = "Standard";
    static MLineStyle *Default();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    MLineStyleFlags flags() const;
    void setFlags(MLineStyleFlags);

    std::string description() const;
    void setDescription(const std::string &);

    Color fillColor() const;
    void setFillColor(const Color &);

    double startAngle() const;
    void setStartAngle(double);

    double endAngle() const;
    void setEndAngle(double);

    std::vector<Element> elements() const;
    std::vector<Element> &elements();
    void setElements(const std::vector<Element> &);

private:
    MLineStyleFlags _flags;
    std::string _description;
    Color _fillColor = Color::ByLayer;
    double _startAngle;
    double _endAngle;
    std::vector<Element> _elements;
};

class LIBDWG_API MLineStyleCollection : ObjectDictionaryCollection<MLineStyle>
{
public:
    MLineStyleCollection(CadDictionary *);
};

}// namespace dwg
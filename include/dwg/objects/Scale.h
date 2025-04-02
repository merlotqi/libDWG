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
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/objects/ObjectDictionaryCollection.h>

namespace dwg {

class CadDictionary;
class LIBDWG_API Scale : public NonGraphicalObject
{
public:
    Scale() = default;
    Scale(const std::string &name);
    Scale(const std::string &name, double paperUnits, double drawingUnits, bool isUnitScale);

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    double paperUnits() const;
    void setPaperUnits(double);

    double drawingUnits() const;
    void setDrawingUnits(double);

    bool isUnitScale() const;
    void setIsUnitScale(bool);

    double scaleFactor() const;
    double applyTo(double value);

    XYZ applyTo(const XYZ &);
    XY applyTo(const XY &);
};

class LIBDWG_API ScaleCollection : public ObjectDictionaryCollection<Scale>
{
public:
    ScaleCollection(CadDictionary *);
};

}// namespace dwg
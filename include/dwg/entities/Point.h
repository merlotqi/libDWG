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

class LIBDWG_API Point : public Entity
{
    XYZ _location;
    XYZ _normal;
    double _thickness;
    double _rotation;

public:
    Point();
    ~Point();

    // Override to return the object type of the Arc
    virtual ObjectType objectType() const override;

    // Override to return the name of the object
    virtual std::string objectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string subclassMarker() const override;

    XYZ location() const;
    void setLocation(const XYZ &);

    XYZ normal() const;
    void setNormal(const XYZ &);

    double thickness() const;
    void setThickness(double);

    double rotation() const;
    void setRotation(double);
};

}// namespace dwg

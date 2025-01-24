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
#include <dwg/entities/InvisibleEdgeFlags.h>

namespace dwg {

class LIBDWG_API Face3D : public Entity
{
    XYZ _firstCorner; 
    XYZ _secondCorner;
    XYZ _thirdCorner; 
    XYZ _fourthCorner;
    InvisibleEdgeFlags _flags;// 70
public:
    Face3D();

    virtual ~Face3D();

    // Override to return the object type of the Arc
    virtual dwg::ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

	XYZ FirstCorner() const;
	void FirstCorner(const XYZ &) const;

	XYZ SecondCorner() const;
	void SecondCorner(const XYZ &) const;

	XYZ ThirdCorner() const;
	void ThirdCorner(const XYZ &) const;

	XYZ FourthCorner() const;
	void FourthCorner(const XYZ &) const;

	InvisibleEdgeFlags Flags() const;
	void Flags(InvisibleEdgeFlags) const;
};
CPL_SMARTER_PTR(Face3D)

}// namespace dwg

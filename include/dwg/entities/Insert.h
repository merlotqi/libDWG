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

#include <dwg/CadObjectCollection.h>
#include <dwg/entities/AttributeEntity.h>
#include <dwg/entities/Entity.h>

namespace dwg {

class DG_BlockRecord;

class LIBDWG_API DG_Insert : public DG_Entity
{
public:
    DG_Insert(DG_BlockRecord *);

    // Override to return the object type of the Arc
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual std::string ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string SubclassMarker() const override;

    DG_BlockRecord *Block() const;
    void Block(DG_BlockRecord *);

    XYZ InsertPoint() const;
    void InsertPoint(const XYZ &);

    double XScale() const;
    void XScale(double);

    double YScale() const;
    void YScale(double);

    double ZScale() const;
    void ZScale(double);

    double Rotation() const;
    void Rotation(double);

    XYZ Normal() const;
    void Normal(const XYZ &);

    unsigned short ColumnCount() const;
    void ColumnCount(unsigned short);

    unsigned short RowCount() const;
    void RowCount(unsigned short);

    double ColumnSpacing() const;
    void ColumnSpacing(double);

    double RowSpacing() const;
    void RowSpacing(double);

    bool HasAttributes() const;

    DG_CadObjectCollection<DG_AttributeEntity> attributes;
};


}// namespace dwg

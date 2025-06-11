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

#include <dwg/entities/AttributeEntity.h>
#include <dwg/entities/Entity.h>
#include <dwg/utils/Delegate.h>

namespace dwg {

class AttributeEntitySeqendCollection;
class BlockRecord;

class LIBDWG_API Insert : public Entity
{
public:
    Insert();
    Insert(BlockRecord *);
    ~Insert();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    BlockRecord *block() const;
    void setBlock(BlockRecord *);

    unsigned short columnCount() const;
    void setColumnCount(unsigned short count);

    double columnSpacing() const;
    void setColumnSpacing(double spacing);

    bool hasAttributes() const;

    bool hasDynamicSubclass() const override;

    XYZ insertPoint() const;
    void setInsertPoint(const XYZ &point);

    bool isMultiple() const;

    XYZ normal() const;
    void setNormal(const XYZ &normal);

    double rotation() const;
    void setRotation(double angle);

    unsigned short rowCount() const;
    void setRowCount(unsigned short count);

    double rowSpacing() const;
    void setRowSpacing(double spacing);

    double XScale() const;
    void setXScale(double scale);

    double YScale() const;
    void setYScale(double scale);

    double ZScale() const;
    void setZScale(double scale);

    // seqend
public:
    AttributeEntitySeqendCollection *attributes();

    void assignDocument(CadDocument *doc) override;
    void unassignDocument() override;

private:
    BlockRecord *_block;
    XYZ _insertPoint;
    double _xscale = 1;
    double _yscale = 1;
    double _zscale = 1;
    double _rotation;
    XYZ _normal;
    unsigned short _columnCount;
    unsigned short _rowCount;
    double _columnSpacing;
    double _rowSpacing;
    AttributeEntitySeqendCollection *_attributes;
};

}// namespace dwg
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
#include <dwg/entities/AttachmentPointType.h>
#include <dwg/entities/DimensionType.h>
#include <dwg/entities/LineSpacingStyleType.h>
#include <dwg/tables/BlockRecord.h>
#include <dwg/tables/DimensionStyle.h>

namespace dwg {

class Dimension : public Entity
{
public:
    Dimension();

public:
    unsigned char version;                // 280
    BlockRecord *block;           // 2, name
    XYZ definitionPoint;                  // 10, 20, 30
    XYZ textMiddlePoint;                  // 11, 21, 31
    XYZ insertionPoint;                   // 12, 22, 32
    XYZ normal;                           // 210, 220, 230
    DimensionType flags;                  // 70
    AttachmentPointType attachmentPoint;  // 71
    LineSpacingStyleType lineSpacingStyle;// 72 optional
    double lineSpacingFactor;             // 41, optional
    bool flipArrow1;                      // 74
    bool flipArrow2;                      // 75
    CPL::String text;                     // 1, optional
    double textRotation;                  // 53, optional
    double horizontalDirection;           // 51, optional
    DimensionStyle *dimStyle;     // 3, name

    virtual double measurement() const = 0;// 42, optional

public:
    bool IsTextUserDefinedLocation() const;
    void IsTextUserDefinedLocation(bool value);
};

class DimensionAligned : public Dimension
{
public:
    DimensionAligned();
    ~DimensionAligned();

    XYZ firstPoint;        // 13, 23, 33
    XYZ secondPoint;       // 14, 24, 34
    double extLineRotation;// 52, optional

    virtual double measurement() const override;// 42, optional
};


class DimensionAngular2Line : public Dimension
{
public:
    DimensionAngular2Line();
    ~DimensionAngular2Line();

    XYZ firstPoint;  // 13, 23, 33
    XYZ secondPoint; // 14, 24, 34
    XYZ angleVertex; // 15, 25, 35
    XYZ dimensionArc;// 16, 26, 36

    virtual double measurement() const override;// 42, optional
};

class DimensionAngular3Pt : public Dimension
{
public:
    DimensionAngular3Pt();
    ~DimensionAngular3Pt();

    XYZ firstPoint; // 13, 23, 33
    XYZ secondPoint;// 14, 24, 34
    XYZ angleVertex;// 15, 25, 35

    virtual double measurement() const override;// 42, optional
};

class DimensionDiameter : public Dimension
{
public:
    DimensionDiameter();
    ~DimensionDiameter();

    XYZ angleVertex;    // 15, 25, 35
    double leaderLength;// 40

    virtual double measurement() const override;// 42, optional
};

class DimensionLinear : public DimensionAligned
{
public:
    DimensionLinear();
    ~DimensionLinear();

    double rotation;// 50
};

class DimensionOrdinate : public Dimension
{
public:
    DimensionOrdinate();
    ~DimensionOrdinate();

    XYZ featureLocation;// 13, 23, 33
    XYZ leaderEndpoint; // 14, 24, 34


    virtual double measurement() const override;// 42, optional

    bool IsOrdinateTypeX() const;
    void IsOrdinateTypeX(bool value);
};

class DimensionRadius : public Dimension
{
public:
    DimensionRadius();
    ~DimensionRadius();

    XYZ angleVertex;                            // 15, 25, 35
    double leaderLength;                        // 40
    virtual double measurement() const override;// 42, optional
};


}// namespace dwg
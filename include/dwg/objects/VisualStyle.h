/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General  License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General  License for more details.
 *
 * You should have received a copy of the GNU General  License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once


#include <dwg/Color.h>
#include <dwg/objects/FaceColorMode.h>
#include <dwg/objects/FaceLightingModelType.h>
#include <dwg/objects/FaceLightingQualityType.h>
#include <dwg/objects/FaceModifierType.h>
#include <dwg/objects/NonGraphicalObject.h>

namespace dwg {

class DG_VisualStyle : public DG_NonGraphicalObject
{
public:
    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;

    // 1
    CPL::String RasterFile;
    // 2
    CPL::String Description;
    // 70
    int Type;
    // 71
    DG_FaceLightingModelType FaceLightingModel;
    // 72
    DG_FaceLightingQualityType FaceLightingQuality;
    // 73
    DG_FaceColorMode FaceColorMode;
    // 90
    DG_FaceModifierType FaceModifiers;
    // 40
    double FaceOpacityLevel;
    // 41
    double FaceSpecularLevel;
    // 62, 63
    DG_Color color;
    // 421
    DG_Color FaceStyleMonoColor;

    //74
    //Edge style model
    //0 = No edges
    //1 = Isolines
    //2 = Facet edges

    //91

    //Edge style

    //64

    //Edge intersection color

    //65

    //Edge obscured color

    //75

    //Edge obscured linetype

    //175

    //Edge intersection linetype

    //42

    //Edge crease angle

    //92

    //Edge modifiers

    //66

    //Edge color

    //43

    //Edge opacity level

    //76

    //Edge width

    //77

    //Edge overhang

    //78

    //Edge jitter

    //67

    //Edge silhouette color

    //79

    //Edge silhouette width

    //170

    //Edge halo gap

    //171

    //Number of edge isolines

    //174

    //Edge style apply flag

    //93

    //Display style display settings

    //44	Brightness

    //173	Shadow type
    // 290
    bool PrecisionFlag;
    // 291
    bool InternalFlag;
};

}// namespace dwg
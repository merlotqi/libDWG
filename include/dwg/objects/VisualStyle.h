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

class LIBDWG_API DG_VisualStyle : public DG_NonGraphicalObject
{
public:
    VisualStyle();

    DG_ObjectType ObjectType() const override;
    CPL::String ObjectName() const override;
    CPL::String SubclassMarker() const override;

    CPL::String RasterFile() const;
    void RasterFile(const char *);

    CPL::String Description() const;
    void Description(const char *);

    int Type() const;
    void Type(int);

    DG_FaceLightingModelType FaceLightingModel() const;
    void FaceLightingModel(DG_FaceLightingModelType);

    DG_FaceLightingQualityType FaceLightingQuality() const;
    void FaceLightingQuality(DG_FaceLightingQualityType);

    DG_FaceColorMode FaceColorMode() const;
    void FaceColorMode(DG_FaceColorMode);

    FaceModifierType FaceModifiers() const;
    void FaceModifiers(FaceModifierType);

    double FaceOpacityLevel() const;
    void FaceOpacityLevel(double);

    double FaceSpecularLevel() const;
    void FaceSpecularLevel(double);

    DG_Color Color() const;
    void Color(const DG_Color &);

    DG_Color FaceStyleMonoColor() const;
    void FaceStyleMonoColor(const DG_Color &);

    bool PrecisionFlag() const;
    void PrecisionFlag(bool);

    bool InternalFlag() const;
    void InternalFlag(bool);
};
CPL_SMARTER_PTR(DG_XRecord)

}// namespace dwg
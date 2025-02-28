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

class LIBDWG_API VisualStyle : public NonGraphicalObject
{
public:
    VisualStyle();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    std::string rasterFile() const;
    void setRasterFile(const std::string &);

    std::string description() const;
    void setDescription(const std::string &);

    int type() const;
    void setType(int);

    FaceLightingModelType faceLightingModel() const;
    void setFaceLightingModel(FaceLightingModelType);

    FaceLightingQualityType faceLightingQuality() const;
    void setFaceLightingQuality(FaceLightingQualityType);

    FaceColorMode faceColorMode() const;
    void setFaceColorMode(FaceColorMode);

    FaceModifierType faceModifiers() const;
    void setFaceModifiers(FaceModifierType);

    double faceOpacityLevel() const;
    void setFaceOpacityLevel(double);

    double faceSpecularLevel() const;
    void setFaceSpecularLevel(double);

    Color color() const;
    void setColor(const Color &);

    Color faceStyleMonoColor() const;
    void setFaceStyleMonoColor(const Color &);

    bool precisionFlag() const;
    void setPrecisionFlag(bool);

    bool internalFlag() const;
    void setInternalFlag(bool);
};

}// namespace dwg
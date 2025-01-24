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
#include <dwg/OrthographicType.h>
#include <dwg/RenderMode.h>
#include <dwg/entities/Entity.h>
#include <dwg/entities/LightingType.h>
#include <dwg/entities/ViewportStatusFlags.h>

namespace dwg {

class LIBDWG_API Viewport : public Entity
{
public:
    static constexpr int PaperViewId = 1;
    static constexpr auto ASDK_XREC_ANNOTATION_SCALE_INFO =
            "ASDK_XREC_ANNOTATION_SCALE_INFO";

public:
    Viewport();

    ~Viewport();

    // Override to return the object type of the Arc
    virtual dwg::ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual CPL::String ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual CPL::String SubclassMarker() const override;

    XYZ Center() const;
    void Center(const XYZ &);

    double Width() const;
    void Width(double);

    double Height() const;
    void Height() const;

    short Id() const;

    XY ViewCenter() const;
    void ViewCenter(const XY &);

    XY SnapBase() const;
    void SnapBase(const XY &);

    XY SnapSpacing() const;
    void SnapSpacing(const XY &);

    XY GridSpacing() const;
    void GridSpacing(const XY &);

    XYZ ViewDirection() const;
    void ViewDirection(const XYZ &);

    XY ViewTarget() const;
    void ViewTarget(const XY &);

    double LensLength() const;
    void LensLength(double);

    double FrontClipPlane() const;
    void FrontClipPlane(double);

    double BackClipPlane() const;
    void BackClipPlane(double);

    double ViewHeight() const;
    void ViewHeight(double);

    double ViewWidth() const;

    double SnapAngle() const;
    void SnapAngle(double);

    double TwistAngle() const;
    void TwistAngle(double);

    short CircleZoomPercent() const;
    void CircleZoomPercent(short);

    std::vector<LayerPtr> FrozenLayers() const;
    void FrozenLayers(const std::vector<LayerPtr> &);

    ViewportStatusFlags Status() const;
    void Status(ViewportStatusFlags);

    CPL::SmarterPtr<Entity> Boundary() const;
    void Boundary(Entity *);

    CPL::String StyleSheetName() const;
    void StyleSheetName(const char*);

    dwg::RenderMode RenderMode() const;
    void RenderMode(dwg::RenderMode);

    bool UcsPerViewport() const;
    void UcsPerViewport(bool);

    bool DisplayUcsIcon() const;
    void DisplayUcsIcon(bool);

    XYZ UcsOrigin() const;
    void UcsOrigin(const XYZ &);

    XYZ UcsXAxis() const;
    void UcsXAxis(const XYZ &);

    XYZ UcsYAxis() const;
    void UcsYAxis(const XYZ &);

    OrthographicType UcsOrthographicType() const;
    void UcsOrthographicType(OrthographicType);

    double Elevation() const;
    void Elevation(double);

    dwg::ShadePlotMode ShadePlotMode() const;
    void ShadePlotMode(dwg::ShadePlotMode);

    short MajorGridLineFrequency() const;
    void MajorGridLineFrequency(short);

    dwg::VisualStyle VisualStyle() const;
    void VisualStyle(dwg::VisualStyle);

    bool UseDefaultLighting() const;
    void UseDefaultLighting(bool);

    LightingType DefaultLightingType() const;
    void DefaultLightingType(LightingType);

    double Brightness() const;
    void Brightness(double);

    double Contrast() const;
    void Contrast(double);

    Color AmbientLightColor() const;
    void AmbientLightColor(const Color &);

    ScalePtr Scale() const;
    void Scale(dwg::Scale *);

    double ScaleFactor() const;

    bool RepresentsPaper() const;
};
CPL_SMARTER_PTR(Viewport)

}// namespace dwg

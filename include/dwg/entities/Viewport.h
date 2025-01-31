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
#include <dwg/objects/ShadePlotMode.h>

namespace dwg {

class DG_Layer;
class DG_Scale;
class DG_VisualStyle;

class LIBDWG_API DG_Viewport : public DG_Entity
{
public:
    static constexpr int PaperViewId = 1;
    static constexpr auto ASDK_XREC_ANNOTATION_SCALE_INFO =
            "ASDK_XREC_ANNOTATION_SCALE_INFO";

public:
    DG_Viewport();

    ~DG_Viewport();

    // Override to return the object type of the Arc
    virtual DG_ObjectType ObjectType() const override;

    // Override to return the name of the object
    virtual std::string ObjectName() const override;

    // Override to return the subclass marker associated with this object
    virtual std::string SubclassMarker() const override;

    XYZ Center() const;
    void Center(const XYZ &);

    double Width() const;
    void Width(double);

    double Height() const;
    void Height(double) const;

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

    std::vector<DG_Layer *> FrozenLayers() const;
    void FrozenLayers(const std::vector<DG_Layer *> &);

    DG_ViewportStatusFlags Status() const;
    void Status(DG_ViewportStatusFlags);

    DG_Entity* Boundary() const;
    void Boundary(DG_Entity *);

    std::string StyleSheetName() const;
    void StyleSheetName(const std::string &);

    DG_RenderMode RenderMode() const;
    void RenderMode(DG_RenderMode);

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

    DG_OrthographicType UcsOrthographicType() const;
    void UcsOrthographicType(DG_OrthographicType);

    double Elevation() const;
    void Elevation(double);

    DG_ShadePlotMode ShadePlotMode() const;
    void ShadePlotMode(DG_ShadePlotMode);

    short MajorGridLineFrequency() const;
    void MajorGridLineFrequency(short);

    DG_VisualStyle *VisualStyle() const;
    void VisualStyle(DG_VisualStyle *);

    bool UseDefaultLighting() const;
    void UseDefaultLighting(bool);

    DG_LightingType DefaultLightingType() const;
    void DefaultLightingType(DG_LightingType);

    double Brightness() const;
    void Brightness(double);

    double Contrast() const;
    void Contrast(double);

    DG_Color AmbientLightColor() const;
    void AmbientLightColor(const DG_Color &);

    DG_Scale *Scale() const;
    void Scale(DG_Scale *);

    double ScaleFactor() const;

    bool RepresentsPaper() const;
};

}// namespace dwg

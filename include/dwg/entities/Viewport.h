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

class Layer;
class Scale;
class VisualStyle;

class LIBDWG_API Viewport : public Entity
{
public:
    static constexpr int PaperViewId = 1;
    static constexpr auto ASDK_XREC_ANNOTATION_SCALE_INFO = "ASDK_XREC_ANNOTATION_SCALE_INFO";

public:
    Viewport();
    ~Viewport();

    virtual ObjectType objectType() const override;
    virtual std::string objectName() const override;
    virtual std::string subclassMarker() const override;

    XYZ center() const;
    void setCenter(const XYZ &);

    double width() const;
    void setWidth(double);

    double height() const;
    void setHeight(double);

    short id() const;

    XY viewCenter() const;
    void setViewCenter(const XY &);

    XY snapBase() const;
    void setSnapBase(const XY &);

    XY snapSpacing() const;
    void setSnapSpacing(const XY &);

    XY gridSpacing() const;
    void setGridSpacing(const XY &);

    XYZ viewDirection() const;
    void setViewDirection(const XYZ &);

    XY viewTarget() const;
    void setViewTarget(const XY &);

    double lensLength() const;
    void setLensLength(double);

    double frontClipPlane() const;
    void setFrontClipPlane(double);

    double backClipPlane() const;
    void setBackClipPlane(double);

    double viewHeight() const;
    void setViewHeight(double);

    double viewWidth() const;

    double snapAngle() const;
    void setSnapAngle(double);

    double twistAngle() const;
    void setTwistAngle(double);

    short circleZoomPercent() const;
    void setCircleZoomPercent(short);

    std::vector<Layer *> frozenLayers() const;
    void setFrozenLayers(const std::vector<Layer *> &);

    ViewportStatusFlags status() const;
    void setStatus(ViewportStatusFlags);

    Entity *boundary() const;
    void setBoundary(Entity *);

    std::string styleSheetName() const;
    void setStyleSheetName(const std::string &);

    RenderMode renderMode() const;
    void setRenderMode(RenderMode);

    bool ucsPerViewport() const;
    void setUcsPerViewport(bool);

    bool displayUcsIcon() const;
    void setDisplayUcsIcon(bool);

    XYZ ucsOrigin() const;
    void setUcsOrigin(const XYZ &);

    XYZ ucsXAxis() const;
    void setUcsXAxis(const XYZ &);

    XYZ ucsYAxis() const;
    void setUcsYAxis(const XYZ &);

    OrthographicType ucsOrthographicType() const;
    void setUcsOrthographicType(OrthographicType);

    double elevation() const;
    void setElevation(double);

    ShadePlotMode shadePlotMode() const;
    void setShadePlotMode(ShadePlotMode);

    short majorGridLineFrequency() const;
    void setMajorGridLineFrequency(short);

    VisualStyle *visualStyle() const;
    void setVisualStyle(VisualStyle *);

    bool useDefaultLighting() const;
    void setUseDefaultLighting(bool);

    LightingType defaultLightingType() const;
    void setDefaultLightingType(LightingType);

    double brightness() const;
    void setBrightness(double);

    double contrast() const;
    void setContrast(double);

    Color ambientLightColor() const;
    void setAmbientLightColor(const Color &);

    Scale *scale() const;
    void setScale(Scale *);

    double scaleFactor() const;

    bool representsPaper() const;

private:
    XYZ _center;
    double _width;
    double _height;
    XY _viewCenter;
    XY _snapBase;
    XY _snapSpacing;
    XY _gridSpacing;
    XYZ _viewDirection;
    XY _viewTarget;
    double _lensLength;
    double _frontClipPlane;
    double _backClipPlane;
    double _viewHeight;
    double _snapAngle;
    double _twistAngle;
    short _circleZoomPercent;
    std::vector<Layer *> _frozenLayers;
    ViewportStatusFlags _status;
    Entity *_boundary;
    std::string _styleSheetName;
    RenderMode _renderMode;
    bool _ucsPerViewport;
    bool _displayUcsIcon;
    XYZ _ucsOrigin;
    XYZ _ucsXAxis;
    XYZ _ucsYAxis;
    OrthographicType _ucsOrthographicType;
    double _elevation;
    ShadePlotMode _shadePlotMode;
    short _majorGridLineFrequency;
    VisualStyle *_visualStyle;
    bool _useDefaultLighting;
    LightingType _defaultLightingType;
    double _brightness;
    double _contrast;
    Color _ambientLightColor = Color((short)0);
    Scale *_scale;
};

}// namespace dwg

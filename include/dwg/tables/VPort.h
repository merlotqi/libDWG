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
#include <dwg/Coordinate.h>
#include <dwg/OrthographicType.h>
#include <dwg/RenderMode.h>
#include <dwg/tables/DefaultLightingType.h>
#include <dwg/tables/GridFlags.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/UscIconType.h>
#include <dwg/tables/ViewModeType.h>

namespace dwg {

class VisualStyle;
class UCS;

class LIBDWG_API VPort : public TableEntry
{
public:
    VPort();
    VPort(const std::string &name);
    ~VPort();

    static constexpr auto DefaultName = "*Active";

    static VPort *Default();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    XY bottomLeft() const;
    void setBottomLeft(const XY &);

    XY topRight() const;
    void setTopRight(const XY &);

    XY center() const;
    void setCenter(const XY &);

    XY snapBasePoint() const;
    void setSnapBasePoint(const XY &);

    XY snapSpacing() const;
    void setSnapSpacing(const XY &);

    XY gridSpacing() const;
    void setGridSpacing(const XY &);

    XYZ direction() const;
    void setDirection(const XYZ &);

    XYZ target() const;
    void setTarget(const XYZ &);

    double viewHeight() const;
    void setViewHeight(double);

    double aspectRatio() const;
    void setAspectRatio(double);

    double lensLength() const;
    void setLensLength(double);

    double frontClippingPlane() const;
    void setFrontClippingPlane(double);

    double backClippingPlane() const;
    void setBackClippingPlane(double);

    double snapRotation() const;
    void setSnapRotation(double);

    double twistAngle() const;
    void setTwistAngle(double);

    short circleZoomPercent() const;
    void setCircleZoomPercent(short);

    ViewModeTypes renderMode() const;
    void setRenderMode(ViewModeTypes);

    ViewModeTypes viewMode() const;
    void setViewMode(ViewModeTypes);

    UscIconTypes ucsIconDisplay() const;
    void setUcsIconDisplay(UscIconTypes);

    bool snapOn() const;
    void setSnapOn(bool);

    bool showGrid() const;
    void setShowGrid(bool);

    bool isometricSnap() const;
    void setIsometricSnap(bool);

    short snapIsoPair() const;
    void setSnapIsoPair(short);

    XYZ origin() const;
    void setOrigin(const XYZ &);

    XYZ xAxis() const;
    void setXAxis(const XYZ &);

    XYZ yAxis() const;
    void setYAxis(const XYZ &);

    UCS *namedUcs() const;
    void setNamedUcs(UCS *);

    UCS *baseUcs() const;
    void setBaseUcs(UCS *);

    OrthographicType orthographicType() const;
    void setOrthographicType(OrthographicType);

    double elevation() const;
    void setElevation(double);

    GridFlags gridFlags() const;
    void setGridFlags(GridFlags);

    short minorGridLinesPerMajorGridLine() const;
    void setMinorGridLinesPerMajorGridLine(short);

    VisualStyle *visualStyle() const;
    void setVisualStyle(VisualStyle *);

    bool useDefaultLighting() const;
    void setUseDefaultLighting(bool);

    DefaultLightingType defaultLighting() const;
    void setDefaultLighting(DefaultLightingType);

    double brightness() const;
    void setBrightness(double);

    double contrast() const;
    void setContrast(double);

    Color ambientColor() const;
    void setAmbientColor(const Color &);

private:
    XY _bottomLeft;
    XY _topRight;
    XY _center;
    XY _snapBasePoint;
    XY _snapSpacing;
    XY _gridSpacing;
    XYZ _direction;
    XYZ _target;
    double _viewHeight;
    double _aspectRatio;
    double _lensLength;
    double _frontClippingPlane;
    double _backClippingPlane;
    double _snapRotation;
    double _twistAngle;
    short _circleZoomPercent;
    RenderMode _renderMode;
    ViewModeType _viewMode;
    UscIconType _ucsIconDisplay;
    bool _snapOn;
    bool _showGrid;
    bool _isometricSnap;
    short _snapIsoPair;
    XYZ _origin;
    XYZ _xAxis;
    XYZ _yAxis;
    UCS *_namedUcs = nullptr;
    UCS *_baseUcs = nullptr;
    OrthographicType _orthographicType;
    double _elevation;
    GridFlags _gridFlags;
    short _minorGridLinesPerMajorGridLine;
    VisualStyle *_visualStyle = nullptr;
    bool _useDefaultLighting;
    DefaultLightingType _defaultLighting;
    double _brightness;
    double _contrast;
    Color _ambientColor;
};

}// namespace dwg

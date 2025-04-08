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

#include <dwg/Coordinate.h>
#include <dwg/OrthographicType.h>
#include <dwg/RenderMode.h>
#include <dwg/tables/TableCollection.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/ViewModeType.h>

namespace dwg {

class VisualStyle;
class LIBDWG_API View : public TableEntry
{
public:
    View() = default;
    View(const std::string &name);
    ~View();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    double height() const;
    void setHeight(double);

    double width() const;
    void setWidth(double);

    double lensLength() const;
    void setLensLength(double);

    double frontClipping() const;
    void setFrontClipping(double);

    double backClipping() const;
    void setBackClipping(double);

    double angle() const;
    void setAngle(double);

    ViewModeType viewMode() const;
    void setViewMode(ViewModeType);

    bool isUcsAssociated() const;
    void setIsUcsAssociated(bool);

    bool isPlottable() const;
    void setIsPlottable(bool);

    RenderMode renderMode() const;
    void setRenderMode(RenderMode);

    XY center() const;
    void setCenter(const XY &);

    XYZ direction() const;
    void setDirection(const XYZ &);

    XYZ target() const;
    void setTarget(const XYZ &);

    VisualStyle *visualStyle() const;
    void setVisualStyle(VisualStyle *);

    XYZ ucsOrigin() const;
    void setUcsOrigin(const XYZ &);

    XYZ ucsXAxis() const;
    void setUcsXAxis(const XYZ &);

    XYZ ucsYAxis() const;
    void setUcsYAxis(const XYZ &);

    double ucsElevation() const;
    void setUcsElevation(double);

    OrthographicType ucsOrthographicType() const;
    void setUcsOrthographicType(OrthographicType);

private:
    double _height = 0.0;
    double _width = 0.0;
    double _lensLength = 0.0;
    double _frontClipping = 0.0;
    double _backClipping = 0.0;
    double _angle = 0.0;
    ViewModeType _viewMode = ViewModeType::Off;
    bool _isUcsAssociated = false;
    bool _isPlottable = false;
    RenderMode _renderMode = RenderMode::Optimized2D;
    XY _center = XY::Zero;
    XYZ _direction = XYZ::Zero;
    XYZ _target = XYZ::Zero;
    VisualStyle *_visualStyle = nullptr;
    XYZ _ucsOrigin = XYZ::Zero;
    XYZ _ucsXAxis = XYZ::Zero;
    XYZ _ucsYAxis = XYZ::Zero;
    double _ucsElevation = 0.0;
    OrthographicType _ucsOrthographicType;
};

class LIBDWG_API ViewsTable : public Table<View>
{
public:
    ViewsTable();
    ViewsTable(CadDocument *document);
    ObjectType objectType() const override;
    std::string objectName() const override;

protected:
    std::vector<std::string> defaultEntries() const override;
};

}// namespace dwg
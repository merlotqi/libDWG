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

#include <dwg/OrthographicType.h>
#include <dwg/objects/LayoutFlags.h>
#include <dwg/objects/PlotSettings.h>

namespace dwg {

class UCS;
class Viewport;
class BlockRecord;
class CadDictionary;

class LIBDWG_API Layout : public PlotSettings
{
public:
    Layout() = default;
    Layout(const std::string &name);
    ~Layout() = default;

    static constexpr auto ModelLayoutName = "Model";
    static constexpr auto PaperLayoutName = "Layout1";

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    LayoutFlags layoutFlags() const;
    void setLayoutFlags(LayoutFlags);

    int tabOrder() const;
    void setTabOrder(int);

    XY minLimits() const;
    void setMinLimits(const XY &);

    XY maxLimits() const;
    void setMaxLimits(const XY &);

    XYZ insertionBasePoint() const;
    void setInsertionBasePoint(const XYZ &);

    XYZ minExtents() const;
    void setMinExtents(const XYZ &);

    XYZ maxExtents() const;
    void setMaxExtents(const XYZ &);

    double elevation() const;
    void setElevation(double);

    XYZ origin() const;
    void setOrigin(const XYZ &);

    XYZ xAxis() const;
    void setXAxis(const XYZ &);

    XYZ yAxis() const;
    void setYAxis(const XYZ &);

    OrthographicType ucsOrthographicType() const;
    void setUcsOrthographicType(OrthographicType);

    BlockRecord *associatedBlock() const;
    void setAssociatedBlock(BlockRecord *);

    Viewport *viewport() const;
    void setViewport(Viewport *);

    UCS *ucs() const;
    void setUCS(UCS *);

    UCS *baseUCS() const;
    void setBaseUCS(UCS *);

    bool isPaperSpace() const;

    std::vector<Viewport *> viewports() const;

private:
    LayoutFlags _layoutFlags;
    int _tabOrder;
    XY _minLimits;
    XY _maxLimits;
    XYZ _insertionBasePoint;
    XYZ _minExtents;
    XYZ _maxExtents;
    double _elevation;
    XYZ _origin;
    XYZ _xaxis;
    XYZ _yaxis;
    OrthographicType _ucsOrthographicType;
    BlockRecord *_associatedBlock;
    Viewport *_viewport;
    UCS *_ucs;
    UCS *_baseUCS;
};

}// namespace dwg
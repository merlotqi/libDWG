/**
 * libDWG - A C++ library for reading and writing DWG and DXF files in CAD.
 *
 * This file is part of libDWG.
 *
 * libDWG is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * libDWG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General License for more details.
 *
 * You should have received a copy of the GNU General License
 * along with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * For more information, visit the project's homepage or contact the author.
 */

#pragma once

#include <dwg/Coordinate.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/objects/PaperMargin.h>
#include <dwg/objects/PlotFlags.h>
#include <dwg/objects/PlotPaperUnits.h>
#include <dwg/objects/PlotRotation.h>
#include <dwg/objects/PlotType.h>
#include <dwg/objects/ScaledType.h>
#include <dwg/objects/ShadePlotMode.h>
#include <dwg/objects/ShadePlotResolutionMode.h>

namespace dwg {

class LIBDWG_API PlotSettings : public NonGraphicalObject
{
public:
    PlotSettings();
    ~PlotSettings();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    std::string pageName() const;
    void setPageName(const std::string &);

    std::string systemPrinterName() const;
    void setSystemPrinterName(const std::string &);

    std::string paperSize() const;
    void setPaperSize(const std::string &);

    std::string plotViewName() const;
    void setPlotViewName(const std::string &);

    PaperMargin unprintableMargin() const;
    void setUnprintableMargin(PaperMargin);

    double paperWidth() const;
    void setPaperWidth(double);

    double paperHeight() const;
    void setPaperHeight(double);

    double plotOriginX() const;
    void setPlotOriginX(double);

    double plotOriginY() const;
    void setPlotOriginY(double);

    double windowLowerLeftX() const;
    void setWindowLowerLeftX(double);

    double windowLowerLeftY() const;
    void setWindowLowerLeftY(double);

    double windowUpperLeftX() const;
    void setWindowUpperLeftX(double);

    double windowUpperLeftY() const;
    void setWindowUpperLeftY(double);

    double printScale() const;

    double numeratorScale() const;
    void setNumeratorScale(double);

    double denominatorScale() const;
    void setDenominatorScale(double);

    PlotFlags flags() const;
    void setFlags(PlotFlags);

    PlotPaperUnits paperUnits() const;
    void setPaperUnits(PlotPaperUnits);

    PlotRotation paperRotation() const;
    void setPaperRotation(PlotRotation);

    PlotType plotType() const;
    void setPlotType(PlotType);

    std::string styleSheet() const;
    void setStyleSheet(const std::string &);

    ScaledType scaledFit() const;
    void setScaledFit(ScaledType);

    ShadePlotMode shadePlotMode() const;
    void setShadePlotMode(ShadePlotMode);

    ShadePlotResolutionMode shadePlotResolutionMode() const;
    void setShadePlotResolutionMode(ShadePlotResolutionMode);

    short shadePlotDPI() const;
    void setShadePlotDPI(short);

    double standardScale() const;
    void setStandardScale(double);

    XY paperImageOrigin() const;
    void setPaperImageOrigin(const XY &);

    double paperImageOriginX() const;
    void setPaperImageOriginX(double);

    double paperImageOriginY() const;
    void setPaperImageOriginY(double);

    unsigned long long shadePlotIDHandle() const;
    void setShadePlotIDHandle(unsigned long long);

private:
    std::string _pageName;
    std::string _systemPrinterName;
    std::string _paperSize;
    std::string _plotViewName;
    PaperMargin _unprintableMargin;
    double _paperWidth;
    double _paperHeight;
    double _plotOriginX;
    double _plotOriginY;
    double _windowLowerLeftX;
    double _windowLowerLeftY;
    double _windowUpperLeftX;
    double _windowUpperLeftY;
    double _numeratorScale;
    double _denominatorScale;
    PlotFlags _flags;
    PlotPaperUnits _paperUnits;
    PlotRotation _paperRotation;
    PlotType _plotType;
    std::string _styleSheet;
    ScaledType _scaledFit;
    ShadePlotMode _shadePlotMode;
    ShadePlotResolutionMode _shadePlotResolutionMode;
    short _shadePlotDPI = 300;
    double _standardScale = 1.0;
    XY _paperImageOrigin = XY::Zero;
    double _paperImageOriginX = 0.0;
    double _paperImageOriginY = 0.0;
    unsigned long long _shadePlotIDHandle = 0ULL;
};

}// namespace dwg
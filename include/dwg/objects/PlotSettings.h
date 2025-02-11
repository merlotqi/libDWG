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
    void setWindowUpperLeftY();

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
};

}// namespace dwg
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

    std::string PageName() const;
    void PageName(const std::string &);

    std::string SystemPrinterName() const;
    void SystemPrinterName(const std::string &);

    std::string PaperSize() const;
    void PaperSize(const std::string &);

    std::string PlotViewName() const;
    void PlotViewName(const std::string &);

    PaperMargin UnprintableMargin() const;
    void UnprintableMargin(PaperMargin);

    double PaperWidth() const;
    void PaperWidth(double);

    double PaperHeight() const;
    void PaperHeight(double);

    double PlotOriginX() const;
    void PlotOriginX(double);

    double PlotOriginY() const;
    void PlotOriginY(double);

    double WindowLowerLeftX() const;
    void WindowLowerLeftX(double);

    double WindowLowerLeftY() const;
    void WindowLowerLeftY(double);

    double WindowUpperLeftX() const;
    void WindowUpperLeftX(double);

    double WindowUpperLeftY() const;
    void WindowUpperLeftY();

    double PrintScale() const;

    double NumeratorScale() const;
    void NumeratorScale(double);

    double DenominatorScale() const;
    void DenominatorScale(double);

    PlotFlags Flags() const;
    void Flags(PlotFlags);

    PlotPaperUnits PaperUnits() const;
    void PaperUnits(PlotPaperUnits);

    PlotRotation PaperRotation() const;
    void PaperRotation(PlotRotation);

    PlotType PlotType() const;
    void PlotType(PlotType);

    std::string StyleSheet() const;
    void StyleSheet(const std::string &);

    ScaledType ScaledFit() const;
    void ScaledFit(ScaledType);

    ShadePlotMode ShadePlotMode() const;
    void ShadePlotMode(ShadePlotMode);

    ShadePlotResolutionMode ShadePlotResolutionMode() const;
    void ShadePlotResolutionMode(ShadePlotResolutionMode);

    short ShadePlotDPI() const;
    void ShadePlotDPI(short);

    double StandardScale() const;
    void StandardScale(double);

    XY PaperImageOrigin() const;
    void PaperImageOrigin(const XY &);

    double PaperImageOriginX() const;
    void PaperImageOriginX(double);

    double PaperImageOriginY() const;
    void PaperImageOriginY(double);

    unsigned long long ShadePlotIDHandle() const;
    void ShadePlotIDHandle(unsigned long long);
};

}// namespace dwg
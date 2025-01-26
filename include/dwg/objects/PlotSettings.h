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

class LIBDWG_API DG_PlotSettings : public DG_NonGraphicalObject
{
public:
    DG_PlotSettings();

    DG_ObjectType ObjectType() const override;

    CPL::String ObjectName() const override;

    CPL::String SubclassMarker() const override;

    CPL::String PageName() const;
    void PageName(const char *);
    
    CPL::String SystemPrinterName() const;
    void SystemPrinterName(const char *);
    
    CPL::String PaperSize() const;
    void PaperSize(const char *);
    
    CPL::String PlotViewName() const;
    void PlotViewName(const char *);
    
    DG_PaperMargin UnprintableMargin() const;
    void UnprintableMargin(DG_PaperMargin);
    
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
    
    DG_PlotFlags Flags() const;
    void Flags(DG_PlotFlags);
    
    DG_PlotPaperUnits PaperUnits() const;
    void PaperUnits(DG_PlotPaperUnits);

    DG_PlotRotation PaperRotation() const;
    void PaperRotation(DG_PlotRotation);
    
    DG_PlotType PlotType() const;
    void PlotType(DG_PlotType);
    
    CPL::String StyleSheet() const;
    void StyleSheet(const char *);
    
    DG_ScaledType ScaledFit() const;
    void ScaledFit(DG_ScaledType);
    
    DG_ShadePlotMode ShadePlotMode() const;
    void ShadePlotMode(DG_ShadePlotMode);
    
    DG_ShadePlotResolutionMode ShadePlotResolutionMode() const;
    void ShadePlotResolutionMode(DG_ShadePlotResolutionMode);
    
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
CPL_SMARTER_PTR(DG_PlotSettings)

}// namespace dwg
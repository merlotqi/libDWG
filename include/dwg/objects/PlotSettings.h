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

#include <dwg/objects/PlotFlags.h>
#include <dwg/objects/PlotPaperUnits.h>
#include <dwg/objects/PlotRotation.h>
#include <dwg/objects/PlotType.h>
#include <dwg/objects/ScaledType.h>
#include <dwg/objects/ShadePlotMode.h>
#include <dwg/objects/ShadePlotResolutionMode.h>
#include <dwg/objects/NonGraphicalObject.h>
#include <dwg/objects/PaperMargin.h>
#include <dwg/base/Coordinate.h>

namespace dwg {

class PlotSettings : public NonGraphicalObject
{
public:
    PlotSettings();

    dwg::ObjectType ObjectType() const { return ObjectType::INVALID; }
    CPL::String ObjectName() const { return DxfFileToken::ObjectPlotSettings; }
    CPL::String SubclassMarker() const
    {
        return DxfSubclassMarker::PlotSettings;
    }

    // 1
    CPL::String PageName = "none_device";
    // 2
    CPL::String SystemPrinterName;
    // 4
    CPL::String PaperSize = "ISO_A4_(210.00_x_297.00_MM)";
    // 6
    CPL::String PlotViewName;
    // 40, 41, 42, 43
    PaperMargin UnprintableMargin;
    // 44
    double PaperWidth;
    // 45
    double PaperHeight;
    // 46
    double PlotOriginX;
    // 47
    double PlotOriginY;
    // 48
    double WindowLowerLeftX;
    // 49
    double WindowLowerLeftY;
    // 140
    double WindowUpperLeftX;
    // 141
    double WindowUpperLeftY;


    double PrintScale() const { return NumeratorScale / DenominatorScale; }

    // 142
    double NumeratorScale = 1.0;

    // 143
    double DenominatorScale = 1.0;
    // 70
    PlotFlags
            Flags;// = PlotFlags.DrawViewportsFirst | PlotFlags.PrintLineweights | PlotFlags.PlotPlotStyles | PlotFlags.UseStandardScale;
    // 72
    PlotPaperUnits PaperUnits = PlotPaperUnits::Milimeters;
    // 73
    PlotRotation PaperRotation;
    // 74
    PlotType PlotType = PlotType::DrawingExtents;
    // 7
    CPL::String StyleSheet;
    // 75
    ScaledType ScaledFit;
    // 76
    ShadePlotMode ShadePlotMode;
    // 77
    ShadePlotResolutionMode ShadePlotResolutionMode;
    // 78
    short ShadePlotDPI = 300;
    // 147
    double StandardScale = 1.0;

    XY PaperImageOrigin;
    // 148
    double PaperImageOriginX;
    // 149
    double PaperImageOriginY;
    // 333
    unsigned long long ShadePlotIDHandle;
};
}// namespace dwg
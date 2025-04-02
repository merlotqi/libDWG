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

#include <dwg/DxfFileToken_p.h>
#include <dwg/DxfSubclassMarker_p.h>
#include <dwg/objects/PlotSettings.h>
#include <stdexcept>

namespace dwg {

PlotSettings::PlotSettings() {}

PlotSettings::~PlotSettings() {}

ObjectType PlotSettings::objectType() const
{
    return ObjectType::INVALID;
}

std::string PlotSettings::objectName() const
{
    return DxfFileToken::ObjectPlotSettings;
}

std::string PlotSettings::subclassMarker() const
{
    return DxfSubclassMarker::PlotSettings;
}

std::string PlotSettings::pageName() const
{
    return _pageName;
}

void PlotSettings::setPageName(const std::string &value)
{
    _pageName = value;
}

std::string PlotSettings::systemPrinterName() const
{
    return _systemPrinterName;
}

void PlotSettings::setSystemPrinterName(const std::string &value)
{
    _systemPrinterName = value;
}

std::string PlotSettings::paperSize() const
{
    return _paperSize;
}

void PlotSettings::setPaperSize(const std::string &value)
{
    _paperSize = value;
}

std::string PlotSettings::plotViewName() const
{
    return _plotViewName;
}

void PlotSettings::setPlotViewName(const std::string &value)
{
    _plotViewName = value;
}

PaperMargin PlotSettings::unprintableMargin() const
{
    return _unprintableMargin;
}

void PlotSettings::setUnprintableMargin(PaperMargin value)
{
    _unprintableMargin = value;
}

double PlotSettings::paperWidth() const
{
    return _paperWidth;
}

void PlotSettings::setPaperWidth(double value)
{
    _paperWidth = value;
}

double PlotSettings::paperHeight() const
{
    return _paperHeight;
}

void PlotSettings::setPaperHeight(double value)
{
    _paperHeight = value;
}

double PlotSettings::plotOriginX() const
{
    return _plotOriginX;
}

void PlotSettings::setPlotOriginX(double value)
{
    _plotOriginX = value;
}

double PlotSettings::plotOriginY() const
{
    return _plotOriginY;
}

void PlotSettings::setPlotOriginY(double value)
{
    _plotOriginY = value;
}

double PlotSettings::windowLowerLeftX() const
{
    return _windowLowerLeftX;
}

void PlotSettings::setWindowLowerLeftX(double value)
{
    _windowLowerLeftX = value;
}

double PlotSettings::windowLowerLeftY() const
{
    return _windowLowerLeftY;
}

void PlotSettings::setWindowLowerLeftY(double value)
{
    _windowLowerLeftY = value;
}

double PlotSettings::windowUpperLeftX() const
{
    return _windowUpperLeftX;
}

void PlotSettings::setWindowUpperLeftX(double value)
{
    _windowUpperLeftX = value;
}

double PlotSettings::windowUpperLeftY() const
{
    return _windowUpperLeftY;
}

void PlotSettings::setWindowUpperLeftY(double value)
{
    _windowUpperLeftY = value;
}

double PlotSettings::printScale() const
{
    return _numeratorScale / _denominatorScale;
}

double PlotSettings::numeratorScale() const
{
    return _numeratorScale;
}

void PlotSettings::setNumeratorScale(double value)
{
    if (value <= 0.0)
        throw new std::out_of_range("Value must be greater than zero");
    _numeratorScale = value;
}

double PlotSettings::denominatorScale() const
{
    return _denominatorScale;
}

void PlotSettings::setDenominatorScale(double value)
{
    if (value <= 0.0)
        throw new std::out_of_range("Value must be greater than zero");
    _denominatorScale = value;
}

PlotFlags PlotSettings::flags() const
{
    return _flags;
}

void PlotSettings::setFlags(PlotFlags value)
{
    _flags = value;
}

PlotPaperUnits PlotSettings::paperUnits() const
{
    return _paperUnits;
}

void PlotSettings::setPaperUnits(PlotPaperUnits value)
{
    _paperUnits = value;
}

PlotRotation PlotSettings::paperRotation() const
{
    return _paperRotation;
}

void PlotSettings::setPaperRotation(PlotRotation value)
{
    _paperRotation = value;
}

PlotType PlotSettings::plotType() const
{
    return _plotType;
}

void PlotSettings::setPlotType(PlotType value)
{
    _plotType = value;
}

std::string PlotSettings::styleSheet() const
{
    return _styleSheet;
}

void PlotSettings::setStyleSheet(const std::string &value)
{
    _styleSheet = value;
}

ScaledType PlotSettings::scaledFit() const
{
    return _scaledFit;
}

void PlotSettings::setScaledFit(ScaledType value)
{
    _scaledFit = value;
}

ShadePlotMode PlotSettings::shadePlotMode() const
{
    return _shadePlotMode;
}

void PlotSettings::setShadePlotMode(ShadePlotMode value)
{
    _shadePlotMode = value;
}

ShadePlotResolutionMode PlotSettings::shadePlotResolutionMode() const
{
    return _shadePlotResolutionMode;
}

void PlotSettings::setShadePlotResolutionMode(ShadePlotResolutionMode value)
{
    _shadePlotResolutionMode = value;
}

short PlotSettings::shadePlotDPI() const
{
    return _shadePlotDPI;
}

void PlotSettings::setShadePlotDPI(short value)
{
    _shadePlotDPI = value;
}

double PlotSettings::standardScale() const
{
    return _standardScale;
}

void PlotSettings::setStandardScale(double value)
{
    _standardScale = value;
}

XY PlotSettings::paperImageOrigin() const
{
    return _paperImageOrigin;
}

void PlotSettings::setPaperImageOrigin(const XY &value)
{
    _paperImageOrigin = value;
}

double PlotSettings::paperImageOriginX() const
{
    return _paperImageOriginX;
}

void PlotSettings::setPaperImageOriginX(double value)
{
    _paperImageOriginX = value;
}

double PlotSettings::paperImageOriginY() const
{
    return _paperImageOriginY;
}

void PlotSettings::setPaperImageOriginY(double value)
{
    _paperImageOriginY = value;
}

unsigned long long PlotSettings::shadePlotIDHandle() const
{
    return _shadePlotIDHandle;
}

void PlotSettings::setShadePlotIDHandle(unsigned long long value)
{
    _shadePlotIDHandle = value;
}

}// namespace dwg
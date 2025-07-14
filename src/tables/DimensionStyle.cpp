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
#include <dwg/tables/DimensionStyle.h>
#include <dwg/tables/LineType.h>

namespace dwg {

DimensionStyle *DimensionStyle::Default()
{
    return new DimensionStyle(DefaultName);
}

DimensionStyle::DimensionStyle() {}

DimensionStyle::DimensionStyle(const std::string &name) : TableEntry(name) {}

DimensionStyle::~DimensionStyle() {}

ObjectType DimensionStyle::objectType() const
{
    return ObjectType::DIMSTYLE;
}

std::string DimensionStyle::objectName() const
{
    return DxfFileToken::TableDimstyle;
}

std::string DimensionStyle::subclassMarker() const
{
    return DxfSubclassMarker::DimensionStyle;
}

std::string DimensionStyle::postFix() const
{
    return _postFix;
}

void DimensionStyle::setPostFix(const std::string &value)
{
    _postFix = value;
}

std::string DimensionStyle::alternateDimensioningSuffix() const
{
    return _alternateDimensioningSuffix;
}

void DimensionStyle::setAlternateDimensioningSuffix(const std::string &value)
{
    _alternateDimensioningSuffix = value;
}

bool DimensionStyle::generateTolerances() const
{
    return _generateTolerances;
}

void DimensionStyle::setGenerateTolerances(bool value)
{
    _generateTolerances = value;
}

bool DimensionStyle::limitsGeneration() const
{
    return _limitsGeneration;
}

void DimensionStyle::setLimitsGeneration(bool value)
{
    _limitsGeneration = value;
}

bool DimensionStyle::textInsideHorizontal() const
{
    return _textInsideHorizontal;
}

void DimensionStyle::setTextInsideHorizontal(bool value)
{
    _textInsideHorizontal = value;
}

bool DimensionStyle::textOutsideHorizontal() const
{
    return _textOutsideHorizontal;
}

void DimensionStyle::setTextOutsideHorizontal(bool value)
{
    _textOutsideHorizontal = value;
}

bool DimensionStyle::suppressFirstExtensionLine() const
{
    return _suppressFirstExtensionLine;
}

void DimensionStyle::setSuppressFirstExtensionLine(bool value)
{
    _suppressFirstExtensionLine = value;
}

bool DimensionStyle::suppressSecondExtensionLine() const
{
    return _suppressSecondExtensionLine;
}

void DimensionStyle::setSuppressSecondExtensionLine(bool value)
{
    _suppressSecondExtensionLine = value;
}

DimensionTextVerticalAlignment DimensionStyle::textVerticalAlignment() const
{
    return _textVerticalAlignment;
}

void DimensionStyle::setTextVerticalAlignment(DimensionTextVerticalAlignment value)
{
    _textVerticalAlignment = value;
}

ZeroHandling DimensionStyle::zeroHandling() const
{
    return _zeroHandling;
}

void DimensionStyle::setZeroHandling(ZeroHandling value)
{
    _zeroHandling = value;
}

bool DimensionStyle::alternateUnitDimensioning() const
{
    return _alternateUnitDimensioning;
}

void DimensionStyle::setAlternateUnitDimensioning(bool value)
{
    _alternateUnitDimensioning = value;
}

short DimensionStyle::alternateUnitDecimalPlaces() const
{
    return _alternateUnitDecimalPlaces;
}

void DimensionStyle::setAlternateUnitDecimalPlaces(short value)
{
    _alternateUnitDecimalPlaces = value;
}

bool DimensionStyle::textOutsideExtensions() const
{
    return _textOutsideExtensions;
}

void DimensionStyle::setTextOutsideExtensions(bool value)
{
    _textOutsideExtensions = value;
}

bool DimensionStyle::separateArrowBlocks() const
{
    return _separateArrowBlocks;
}

void DimensionStyle::setSeparateArrowBlocks(bool value)
{
    _separateArrowBlocks = value;
}

bool DimensionStyle::textInsideExtensions() const
{
    return _textInsideExtensions;
}

void DimensionStyle::setTextInsideExtensions(bool value)
{
    _textInsideExtensions = value;
}

bool DimensionStyle::suppressOutsideExtensions() const
{
    return _suppressOutsideExtensions;
}

void DimensionStyle::setSuppressOutsideExtensions(bool value)
{
    _suppressOutsideExtensions = value;
}

short DimensionStyle::angularDecimalPlaces() const
{
    return _angularDecimalPlaces;
}

void DimensionStyle::setAngularDecimalPlaces(short value)
{
    _angularDecimalPlaces = value;
}

DimensionTextHorizontalAlignment DimensionStyle::textHorizontalAlignment() const
{
    return _textHorizontalAlignment;
}

void DimensionStyle::setTextHorizontalAlignment(DimensionTextHorizontalAlignment value)
{
    _textHorizontalAlignment = value;
}

bool DimensionStyle::suppressFirstDimensionLine() const
{
    return _suppressFirstDimensionLine;
}

void DimensionStyle::setSuppressFirstDimensionLine(bool value)
{
    _suppressFirstDimensionLine = value;
}

bool DimensionStyle::suppressSecondDimensionLine() const
{
    return _suppressSecondDimensionLine;
}

void DimensionStyle::setSuppressSecondDimensionLine(bool value)
{
    _suppressSecondDimensionLine = value;
}

ToleranceAlignment DimensionStyle::toleranceAlignment() const
{
    return _toleranceAlignment;
}

void DimensionStyle::setToleranceAlignment(ToleranceAlignment value)
{
    _toleranceAlignment = value;
}

ZeroHandling DimensionStyle::toleranceZeroHandling() const
{
    return _toleranceZeroHandling;
}

void DimensionStyle::setToleranceZeroHandling(ZeroHandling value)
{
    _toleranceZeroHandling = value;
}

ZeroHandling DimensionStyle::alternateUnitZeroHandling() const
{
    return _alternateUnitZeroHandling;
}

void DimensionStyle::setAlternateUnitZeroHandling(ZeroHandling value)
{
    _alternateUnitZeroHandling = value;
}

short DimensionStyle::dimensionFit() const
{
    return _dimensionFit;
}

void DimensionStyle::setDimensionFit(short value)
{
    _dimensionFit = value;
}

bool DimensionStyle::cursorUpdate() const
{
    return _cursorUpdate;
}

void DimensionStyle::setCursorUpdate(bool value)
{
    _cursorUpdate = value;
}

ZeroHandling DimensionStyle::alternateUnitToleranceZeroHandling() const
{
    return _alternateUnitToleranceZeroHandling;
}

void DimensionStyle::setAlternateUnitToleranceZeroHandling(ZeroHandling value)
{
    _alternateUnitToleranceZeroHandling = value;
}

short DimensionStyle::dimensionUnit() const
{
    return _dimensionUnit;
}

void DimensionStyle::setDimensionUnit(short value)
{
    _dimensionUnit = value;
}

AngularUnitFormat DimensionStyle::angularUnit() const
{
    return _angularUnit;
}

void DimensionStyle::setAngularUnit(AngularUnitFormat value)
{
    _angularUnit = value;
}

short DimensionStyle::decimalPlaces() const
{
    return _decimalPlaces;
}

void DimensionStyle::setDecimalPlaces(short value)
{
    _decimalPlaces = value;
}

short DimensionStyle::toleranceDecimalPlaces() const
{
    return _toleranceDecimalPlaces;
}

void DimensionStyle::setToleranceDecimalPlaces(short value)
{
    _toleranceDecimalPlaces = value;
}

LinearUnitFormat DimensionStyle::alternateUnitFormat() const
{
    return _alternateUnitFormat;
}

void DimensionStyle::setAlternateUnitFormat(LinearUnitFormat value)
{
    _alternateUnitFormat = value;
}

short DimensionStyle::alternateUnitToleranceDecimalPlaces() const
{
    return _alternateUnitToleranceDecimalPlaces;
}

void DimensionStyle::setAlternateUnitToleranceDecimalPlaces(short value)
{
    _alternateUnitToleranceDecimalPlaces = value;
}

double DimensionStyle::scaleFactor() const
{
    return _scaleFactor;
}

void DimensionStyle::setScaleFactor(double value)
{
    _scaleFactor = value;
}

double DimensionStyle::arrowSize() const
{
    return _arrowSize;
}

void DimensionStyle::setArrowSize(double value)
{
    _arrowSize = value;
}

double DimensionStyle::extensionLineOffset() const
{
    return _extensionLineOffset;
}

void DimensionStyle::setExtensionLineOffset(double value)
{
    _extensionLineOffset = value;
}

double DimensionStyle::dimensionLineIncrement() const
{
    return _dimensionLineIncrement;
}

void DimensionStyle::setDimensionLineIncrement(double value)
{
    _dimensionLineIncrement = value;
}

double DimensionStyle::extensionLineExtension() const
{
    return _extensionLineExtension;
}

void DimensionStyle::setExtensionLineExtension(double value)
{
    _extensionLineExtension = value;
}

double DimensionStyle::rounding() const
{
    return _rounding;
}

void DimensionStyle::setRounding(double value)
{
    _rounding = value;
}

double DimensionStyle::dimensionLineExtension() const
{
    return _dimensionLineExtension;
}

void DimensionStyle::setDimensionLineExtension(double value)
{
    _dimensionLineExtension = value;
}

double DimensionStyle::plusTolerance() const
{
    return _plusTolerance;
}

void DimensionStyle::setPlusTolerance(double value)
{
    _plusTolerance = value;
}

double DimensionStyle::minusTolerance() const
{
    return _minusTolerance;
}

void DimensionStyle::setMinusTolerance(double value)
{
    _minusTolerance = value;
}

double DimensionStyle::fixedExtensionLineLength() const
{
    return _fixedExtensionLineLength;
}

void DimensionStyle::setFixedExtensionLineLength(double value)
{
    _fixedExtensionLineLength = value;
}

double DimensionStyle::joggedRadiusDimensionTransverseSegmentAngle() const
{
    return _joggedRadiusDimensionTransverseSegmentAngle;
}

void DimensionStyle::setJoggedRadiusDimensionTransverseSegmentAngle(double value)
{
    _joggedRadiusDimensionTransverseSegmentAngle = value;
}

DimensionTextBackgroundFillMode DimensionStyle::textBackgroundFillMode() const
{
    return _textBackgroundFillMode;
}

void DimensionStyle::setTextBackgroundFillMode(DimensionTextBackgroundFillMode value)
{
    _textBackgroundFillMode = value;
}

Color DimensionStyle::textBackgroundColor() const
{
    return _textBackgroundColor;
}

void DimensionStyle::setTextBackgroundColor(const Color &value)
{
    _textBackgroundColor = value;
}

ZeroHandling DimensionStyle::angularZeroHandling() const
{
    return _angularZeroHandling;
}

void DimensionStyle::setAngularZeroHandling(ZeroHandling value)
{
    _angularZeroHandling = value;
}

ArcLengthSymbolPosition DimensionStyle::arcLengthSymbolPosition() const
{
    return _arcLengthSymbolPosition;
}

void DimensionStyle::setArcLengthSymbolPosition(ArcLengthSymbolPosition value)
{
    _arcLengthSymbolPosition = value;
}

double DimensionStyle::textHeight() const
{
    return _textHeight;
}

void DimensionStyle::setTextHeight(double value)
{
    _textHeight = value;
}

double DimensionStyle::centerMarkSize() const
{
    return _centerMarkSize;
}

void DimensionStyle::setCenterMarkSize(double value)
{
    _centerMarkSize = value;
}

double DimensionStyle::tickSize() const
{
    return _tickSize;
}

void DimensionStyle::setTickSize(double value)
{
    _tickSize = value;
}

double DimensionStyle::alternateUnitScaleFactor() const
{
    return _alternateUnitScaleFactor;
}

void DimensionStyle::setAlternateUnitScaleFactor(double value)
{
    _alternateUnitScaleFactor = value;
}

double DimensionStyle::linearScaleFactor() const
{
    return _linearScaleFactor;
}

void DimensionStyle::setLinearScaleFactor(double value)
{
    _linearScaleFactor = value;
}

double DimensionStyle::textVerticalPosition() const
{
    return _textVerticalPosition;
}

void DimensionStyle::setTextVerticalPosition(double value)
{
    _textVerticalPosition = value;
}

double DimensionStyle::toleranceScaleFactor() const
{
    return _toleranceScaleFactor;
}

void DimensionStyle::setToleranceScaleFactor(double value)
{
    _toleranceScaleFactor = value;
}

double DimensionStyle::dimensionLineGap() const
{
    return _dimensionLineGap;
}

void DimensionStyle::setDimensionLineGap(double value)
{
    _dimensionLineGap = value;
}

double DimensionStyle::alternateUnitRounding() const
{
    return _alternateUnitRounding;
}

void DimensionStyle::setAlternateUnitRounding(double value)
{
    _alternateUnitRounding = value;
}

Color DimensionStyle::dimensionLineColor() const
{
    return _dimensionLineColor;
}

void DimensionStyle::setDimensionLineColor(const Color &value)
{
    _dimensionLineColor = value;
}

Color DimensionStyle::extensionLineColor() const
{
    return _extensionLineColor;
}

void DimensionStyle::setExtensionLineColor(const Color &value)
{
    _extensionLineColor = value;
}

Color DimensionStyle::textColor() const
{
    return _textColor;
}

void DimensionStyle::setTextColor(const Color &value)
{
    _textColor = value;
}

FractionFormat DimensionStyle::fractionFormat() const
{
    return _fractionFormat;
}

void DimensionStyle::setFractionFormat(FractionFormat value)
{
    _fractionFormat = value;
}

LinearUnitFormat DimensionStyle::linearUnitFormat() const
{
    return _linearUnitFormat;
}

void DimensionStyle::setLinearUnitFormat(LinearUnitFormat value)
{
    _linearUnitFormat = value;
}

char DimensionStyle::decimalSeparator() const
{
    return _decimalSeparator;
}

void DimensionStyle::setDecimalSeparator(char value)
{
    _decimalSeparator = value;
}

TextMovement DimensionStyle::textMovement() const
{
    return _textMovement;
}

void DimensionStyle::setTextMovement(TextMovement value)
{
    _textMovement = value;
}

bool DimensionStyle::isExtensionLineLengthFixed() const
{
    return _isExtensionLineLengthFixed;
}

void DimensionStyle::setIsExtensionLineLengthFixed(bool value)
{
    _isExtensionLineLengthFixed = value;
}

TextDirection DimensionStyle::textDirection() const
{
    return _textDirection;
}

void DimensionStyle::setTextDirection(TextDirection value)
{
    _textDirection = value;
}

LineweightType DimensionStyle::dimensionLineWeight() const
{
    return _dimensionLineWeight;
}

void DimensionStyle::setDimensionLineWeight(LineweightType value)
{
    _dimensionLineWeight = value;
}

LineweightType DimensionStyle::extensionLineWeight() const
{
    return _extensionLineWeight;
}

void DimensionStyle::setExtensionLineWeight(LineweightType value)
{
    _extensionLineWeight = value;
}

TextArrowFitType DimensionStyle::dimensionTextArrowFit() const
{
    return _dimensionTextArrowFit;
}

void DimensionStyle::setDimensionTextArrowFit(TextArrowFitType value)
{
    _dimensionTextArrowFit = value;
}

TextStyle *DimensionStyle::style() const
{
    return _style;
}

void DimensionStyle::setStyle(TextStyle *value)
{
    _style = value; /*updateTable*/
}

BlockRecord *DimensionStyle::leaderArrow() const
{
    return _leaderArrow;
}

void DimensionStyle::setLeaderArrow(BlockRecord *value)
{
    _leaderArrow = value;
}

BlockRecord *DimensionStyle::arrowBlock() const
{
    return _arrowBlock;
}

void DimensionStyle::setArrowBlock(BlockRecord *value)
{
    _arrowBlock = value;
}

BlockRecord *DimensionStyle::dimArrow1() const
{
    return _dimArrow1;
}

void DimensionStyle::setDimArrow1(BlockRecord *value)
{
    _dimArrow1 = value;
}

BlockRecord *DimensionStyle::dimArrow2() const
{
    return _dimArrow2;
}

void DimensionStyle::setDimArrow2(BlockRecord *value)
{
    _dimArrow2 = value;
}

std::string DimensionStyle::altMzs() const
{
    return _altMzs;
}

void DimensionStyle::setAltMzs(const std::string &value)
{
    _altMzs = value;
}

std::string DimensionStyle::mzs() const
{
    return _mzs;
}

void DimensionStyle::setMzs(const std::string &value)
{
    _mzs = value;
}

double DimensionStyle::altMzf() const
{
    return _altMzf;
}

void DimensionStyle::setAltMzf(double value)
{
    _altMzf = value;
}

double DimensionStyle::mzf() const
{
    return _mzf;
}

void DimensionStyle::setMzf(double value)
{
    _mzf = value;
}

LineType *DimensionStyle::lineType() const
{
    return _lineType;
}

void DimensionStyle::setLineType(LineType *) {}

LineType *DimensionStyle::lineTypeExt1() const
{
    return _lineTypeExt1;
}

void DimensionStyle::setLineTypeExt1(LineType *) {}

LineType *DimensionStyle::lineTypeExt2() const
{
    return _lineTypeExt2;
}

void DimensionStyle::setLineTypeExt2(LineType *) {}

void DimensionStyle::assignDocument(CadDocument *doc) {}

void DimensionStyle::unassignDocument() {}

std::vector<std::string> DimensionStyle::getDimStylePrefixAndSuffix(const std::string &text, char start, char end,
                                                                    std::string &prefix, std::string &suffix)
{
    int index = -1;// first occurrence of '<>' or '[]'
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == start)
        {
            if (i + 1 < text.size())
            {
                if (text[i + 1] == end)
                {
                    index = i;
                    break;
                }
            }
        }
    }

    if (index < 0)
    {
        prefix = std::string();
        suffix = text;
    }
    else
    {
        prefix = text.substr(0, index);
        suffix = text.substr(index + 2, text.size() - (index + 2));
    }

    return {prefix, suffix};
}

}// namespace dwg
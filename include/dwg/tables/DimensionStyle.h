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
#include <dwg/LineWeightType.h>
#include <dwg/tables/ArcLengthSymbolPosition.h>
#include <dwg/tables/DimensionTextBackgroundFillMode.h>
#include <dwg/tables/DimensionTextHorizontalAlignment.h>
#include <dwg/tables/DimensionTextVerticalAlignment.h>
#include <dwg/tables/FractionFormat.h>
#include <dwg/tables/TableCollection.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/TextArrowFitType.h>
#include <dwg/tables/TextDirection.h>
#include <dwg/tables/TextMovement.h>
#include <dwg/tables/ToleranceAlignment.h>
#include <dwg/tables/ZeroHandling.h>
#include <dwg/units/AngularUnitFormat.h>
#include <dwg/units/LinearUnitFormat.h>
#include <string>

namespace dwg {

class BlockRecord;
class TextStyle;
class LIBDWG_API DimensionStyle : public TableEntry
{
public:
    /** Default name for the dimension style. */
    static constexpr auto DefaultName = "Standard";
    static DimensionStyle *Default();

public:
    DimensionStyle();
    DimensionStyle(const std::string &name);
    ~DimensionStyle();

    ObjectType objectType() const override;
    std::string objectName() const override;
    std::string subclassMarker() const override;

    std::string postFix() const;
    void setPostFix(const std::string &postFix);

    std::string alternateDimensioningSuffix() const;
    void setAlternateDimensioningSuffix(const std::string &);

    bool generateTolerances() const;
    void setGenerateTolerances(bool);

    bool limitsGeneration() const;
    void setLimitsGeneration(bool);

    bool textInsideHorizontal() const;
    void setTextInsideHorizontal(bool);

    bool textOutsideHorizontal() const;
    void setTextOutsideHorizontal(bool);

    bool suppressFirstExtensionLine() const;
    void setSuppressFirstExtensionLine(bool);

    bool suppressSecondExtensionLine() const;
    void setSuppressSecondExtensionLine(bool);

    DimensionTextVerticalAlignment textVerticalAlignment() const;
    void setTextVerticalAlignment(DimensionTextVerticalAlignment);

    ZeroHandling zeroHandling() const;
    void setZeroHandling(ZeroHandling);

    bool alternateUnitDimensioning() const;
    void setAlternateUnitDimensioning(bool);

    short alternateUnitDecimalPlaces() const;
    void setAlternateUnitDecimalPlaces(short);

    bool textOutsideExtensions() const;
    void setTextOutsideExtensions(bool);

    bool separateArrowBlocks() const;
    void setSeparateArrowBlocks(bool);

    bool textInsideExtensions() const;
    void setTextInsideExtensions(bool);

    bool suppressOutsideExtensions() const;
    void setSuppressOutsideExtensions(bool);

    short angularDimensionDecimalPlaces() const;
    void setAngularDimensionDecimalPlaces(short);

    DimensionTextHorizontalAlignment textHorizontalAlignment() const;
    void setTextHorizontalAlignment(DimensionTextHorizontalAlignment);

    bool suppressFirstDimensionLine() const;
    void setSuppressFirstDimensionLine(bool);

    bool suppressSecondDimensionLine() const;
    void setSuppressSecondDimensionLine(bool);

    ToleranceAlignment toleranceAlignment() const;
    void setToleranceAlignment(ToleranceAlignment);

    ZeroHandling toleranceZeroHandling() const;
    void setToleranceZeroHandling(ZeroHandling);

    ZeroHandling alternateUnitZeroHandling() const;
    void setAlternateUnitZeroHandling(ZeroHandling);

    short dimensionFit() const;
    void setDimensionFit(short);

    bool cursorUpdate() const;
    void setCursorUpdate(bool);

    ZeroHandling alternateUnitToleranceZeroHandling() const;
    void setAlternateUnitToleranceZeroHandling(ZeroHandling);

    short dimensionUnit() const;
    void setDimensionUnit(short);

    AngularUnitFormat angularUnit() const;
    void setAngularUnit(AngularUnitFormat);

    short decimalPlaces() const;
    void setDecimalPlaces(short);

    short toleranceDecimalPlaces() const;
    void setToleranceDecimalPlaces(short);

    LinearUnitFormat alternateUnitFormat() const;
    void setAlternateUnitFormat(LinearUnitFormat);

    short alternateUnitToleranceDecimalPlaces() const;
    void setAlternateUnitToleranceDecimalPlaces(short);

    double scaleFactor() const;
    void setScaleFactor(double);

    double arrowSize() const;
    void setArrowSize(double);

    double extensionLineOffset() const;
    void setExtensionLineOffset(double);

    double dimensionLineIncrement() const;
    void setDimensionLineIncrement(double);

    double extensionLineExtension() const;
    void setExtensionLineExtension(double);

    double rounding() const;
    void setRounding(double);

    double dimensionLineExtension() const;
    void setDimensionLineExtension(double);

    double plusTolerance() const;
    void setPlusTolerance(double);

    double minusTolerance() const;
    void setMinusTolerance(double);

    double fixedExtensionLineLength() const;
    void setFixedExtensionLineLength(double);

    double joggedRadiusDimensionTransverseSegmentAngle() const;
    void setJoggedRadiusDimensionTransverseSegmentAngle(double);

    DimensionTextBackgroundFillMode textBackgroundFillMode() const;
    void setTextBackgroundFillMode(DimensionTextBackgroundFillMode);

    Color textBackgroundColor() const;
    void setTextBackgroundColor(const Color &);

    ZeroHandling angularZeroHandling() const;
    void setAngularZeroHandling(ZeroHandling);

    ArcLengthSymbolPosition arcLengthSymbolPosition() const;
    void setArcLengthSymbolPosition(ArcLengthSymbolPosition);

    double textHeight() const;
    void setTextHeight(double);

    double centerMarkSize() const;
    void setCenterMarkSize(double);

    double tickSize() const;
    void setTickSize(double);

    double alternateUnitScaleFactor() const;
    void setAlternateUnitScaleFactor(double);

    double linearScaleFactor() const;
    void setLinearScaleFactor(double);

    double textVerticalPosition() const;
    void setTextVerticalPosition(double);

    double toleranceScaleFactor() const;
    void setToleranceScaleFactor(double);

    double dimensionLineGap() const;
    void setDimensionLineGap(double);

    double alternateUnitRounding() const;
    void setAlternateUnitRounding(double);

    Color dimensionLineColor() const;
    void setDimensionLineColor(const Color &);

    Color extensionLineColor() const;
    void setExtensionLineColor(const Color &);

    Color textColor() const;
    void setTextColor(const Color &);

    FractionFormat fractionFormat() const;
    void setFractionFormat(FractionFormat);

    LinearUnitFormat linearUnitFormat() const;
    void setLinearUnitFormat(LinearUnitFormat);

    char decimalSeparator() const;
    void setDecimalSeparator(char);

    TextMovement textMovement() const;
    void setTextMovement(TextMovement);

    bool isExtensionLineLengthFixed() const;
    void setIsExtensionLineLengthFixed(bool);

    TextDirection textDirection() const;
    void setTextDirection(TextDirection);

    LineweightType dimensionLineWeight() const;
    void setDimensionLineWeight(LineweightType);

    LineweightType extensionLineWeight() const;
    void setExtensionLineWeight(LineweightType);

    TextArrowFitType dimensionTextArrowFit() const;
    void setDimensionTextArrowFit(TextArrowFitType);

    TextStyle *style() const;
    void setStyle(TextStyle *);

    BlockRecord *leaderArrow() const;
    void setLeaderArrow(BlockRecord *);

    BlockRecord *arrowBlock() const;
    void setArrowBlock(BlockRecord *);

    BlockRecord *dimArrow1() const;
    void setDimArrow1(BlockRecord *);

    BlockRecord *dimArrow2() const;
    void setDimArrow2(BlockRecord *);

    std::string altMzs() const;
    void setAltMzs(const std::string &);

    std::string mzs() const;
    void setMzs(const std::string &);

    double altMzf() const;
    void setAltMzf(double);

    double mzf() const;
    void setMzf(double);
};

class LIBDWG_API DimensionStylesTable : public Table<DimensionStyle>
{
public:
    DimensionStylesTable();

    ObjectType objectType() const override;
    std::string objectName() const override;

protected:
    std::vector<std::string> defaultEntries() const;
};

}// namespace dwg
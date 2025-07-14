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
#include <dwg/tables/TableEntry.h>
#include <dwg/tables/TextArrowFitType.h>
#include <dwg/tables/TextDirection.h>
#include <dwg/tables/TextMovement.h>
#include <dwg/tables/ToleranceAlignment.h>
#include <dwg/tables/ZeroHandling.h>
#include <dwg/units/AngularUnitFormat.h>
#include <dwg/units/LinearUnitFormat.h>
#include <math.h>
#include <string>

namespace dwg {

class BlockRecord;
class TextStyle;
class LineType;
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

    std::string alternateDimensioningSuffix() const;
    void setAlternateDimensioningSuffix(const std::string &);

    short alternateUnitDecimalPlaces() const;
    void setAlternateUnitDecimalPlaces(short);

    bool alternateUnitDimensioning() const;
    void setAlternateUnitDimensioning(bool);

    LinearUnitFormat alternateUnitFormat() const;
    void setAlternateUnitFormat(LinearUnitFormat);

    double alternateUnitRounding() const;
    void setAlternateUnitRounding(double);

    double alternateUnitScaleFactor() const;
    void setAlternateUnitScaleFactor(double);

    short alternateUnitToleranceDecimalPlaces() const;
    void setAlternateUnitToleranceDecimalPlaces(short);

    ZeroHandling alternateUnitToleranceZeroHandling() const;
    void setAlternateUnitToleranceZeroHandling(ZeroHandling);

    ZeroHandling alternateUnitZeroHandling() const;
    void setAlternateUnitZeroHandling(ZeroHandling);

    short angularDecimalPlaces() const;
    void setAngularDecimalPlaces(short);

    AngularUnitFormat angularUnit() const;
    void setAngularUnit(AngularUnitFormat);

    ZeroHandling angularZeroHandling() const;
    void setAngularZeroHandling(ZeroHandling);

    ArcLengthSymbolPosition arcLengthSymbolPosition() const;
    void setArcLengthSymbolPosition(ArcLengthSymbolPosition);

    BlockRecord *arrowBlock() const;
    void setArrowBlock(BlockRecord *);

    double arrowSize() const;
    void setArrowSize(double);

    double centerMarkSize() const;
    void setCenterMarkSize(double);

    bool cursorUpdate() const;
    void setCursorUpdate(bool);

    short decimalPlaces() const;
    void setDecimalPlaces(short);

    char decimalSeparator() const;
    void setDecimalSeparator(char);

    BlockRecord *dimArrow1() const;
    void setDimArrow1(BlockRecord *);

    BlockRecord *dimArrow2() const;
    void setDimArrow2(BlockRecord *);

    short dimensionFit() const;
    void setDimensionFit(short);

    Color dimensionLineColor() const;
    void setDimensionLineColor(const Color &);

    double dimensionLineExtension() const;
    void setDimensionLineExtension(double);

    double dimensionLineGap() const;
    void setDimensionLineGap(double);

    double dimensionLineIncrement() const;
    void setDimensionLineIncrement(double);

    LineweightType dimensionLineWeight() const;
    void setDimensionLineWeight(LineweightType);

    TextArrowFitType dimensionTextArrowFit() const;
    void setDimensionTextArrowFit(TextArrowFitType);

    short dimensionUnit() const;
    void setDimensionUnit(short);

    Color extensionLineColor() const;
    void setExtensionLineColor(const Color &);

    double extensionLineExtension() const;
    void setExtensionLineExtension(double);

    double extensionLineOffset() const;
    void setExtensionLineOffset(double);

    LineweightType extensionLineWeight() const;
    void setExtensionLineWeight(LineweightType);

    double fixedExtensionLineLength() const;
    void setFixedExtensionLineLength(double);

    FractionFormat fractionFormat() const;
    void setFractionFormat(FractionFormat);

    bool generateTolerances() const;
    void setGenerateTolerances(bool);

    bool isExtensionLineLengthFixed() const;
    void setIsExtensionLineLengthFixed(bool);

    double joggedRadiusDimensionTransverseSegmentAngle() const;
    void setJoggedRadiusDimensionTransverseSegmentAngle(double);

    BlockRecord *leaderArrow() const;
    void setLeaderArrow(BlockRecord *);

    bool limitsGeneration() const;
    void setLimitsGeneration(bool);

    double linearScaleFactor() const;
    void setLinearScaleFactor(double);

    LinearUnitFormat linearUnitFormat() const;
    void setLinearUnitFormat(LinearUnitFormat);

    LineType *lineType() const;
    void setLineType(LineType *);

    LineType *lineTypeExt1() const;
    void setLineTypeExt1(LineType *);

    LineType *lineTypeExt2() const;
    void setLineTypeExt2(LineType *);

    double minusTolerance() const;
    void setMinusTolerance(double);

    double plusTolerance() const;
    void setPlusTolerance(double);

    std::string postFix() const;
    void setPostFix(const std::string &);

    std::string prefix() const;
    void setPrefix(const std::string &);

    double rounding() const;
    void setRounding(double);

    double scaleFactor() const;
    void setScaleFactor(double);

    bool separateArrowBlocks() const;
    void setSeparateArrowBlocks(bool);

    TextStyle *style() const;
    void setStyle(TextStyle *);

    std::string suffix() const;
    void setSuffix(const std::string &);

    bool suppressFirstDimensionLine() const;
    void setSuppressFirstDimensionLine(bool);

    bool suppressFirstExtensionLine() const;
    void setSuppressFirstExtensionLine(bool);

    bool suppressOutsideExtensions() const;
    void setSuppressOutsideExtensions(bool);

    bool suppressSecondDimensionLine() const;
    void setSuppressSecondDimensionLine(bool);

    bool suppressSecondExtensionLine() const;
    void setSuppressSecondExtensionLine(bool);

    Color textBackgroundColor() const;
    void setTextBackgroundColor(const Color &);

    DimensionTextBackgroundFillMode textBackgroundFillMode() const;
    void setTextBackgroundFillMode(DimensionTextBackgroundFillMode);

    Color textColor() const;
    void setTextColor(const Color &);

    TextDirection textDirection() const;
    void setTextDirection(TextDirection);

    double textHeight() const;
    void setTextHeight(double);

    DimensionTextHorizontalAlignment textHorizontalAlignment() const;
    void setTextHorizontalAlignment(DimensionTextHorizontalAlignment);

    bool textInsideExtensions() const;
    void setTextInsideExtensions(bool);

    bool textInsideHorizontal() const;
    void setTextInsideHorizontal(bool);

    TextMovement textMovement() const;
    void setTextMovement(TextMovement);

    bool textOutsideExtensions() const;
    void setTextOutsideExtensions(bool);

    bool textOutsideHorizontal() const;
    void setTextOutsideHorizontal(bool);

    DimensionTextVerticalAlignment textVerticalAlignment() const;
    void setTextVerticalAlignment(DimensionTextVerticalAlignment);

    double textVerticalPosition() const;
    void setTextVerticalPosition(double);

    double tickSize() const;
    void setTickSize(double);

    ToleranceAlignment toleranceAlignment() const;
    void setToleranceAlignment(ToleranceAlignment);

    short toleranceDecimalPlaces() const;
    void setToleranceDecimalPlaces(short);

    double toleranceScaleFactor() const;
    void setToleranceScaleFactor(double);

    ZeroHandling toleranceZeroHandling() const;
    void setToleranceZeroHandling(ZeroHandling);

    ZeroHandling zeroHandling() const;
    void setZeroHandling(ZeroHandling);

    double altMzf() const;
    void setAltMzf(double);

    std::string altMzs() const;
    void setAltMzs(const std::string &);

    double mzf() const;
    void setMzf(double);

    std::string mzs() const;
    void setMzs(const std::string &);

    void assignDocument(CadDocument *doc) override;
    void unassignDocument() override;

private:
    std::vector<std::string> getDimStylePrefixAndSuffix(const std::string &text, char start, char end, std::string &prefix, std::string &suffix);

private:
    std::string _postFix = "<>";
    std::string _alternateDimensioningSuffix = "[]";
    bool _generateTolerances = false;
    bool _limitsGeneration = false;
    bool _textInsideHorizontal = false;
    bool _textOutsideHorizontal = false;
    bool _suppressFirstExtensionLine = false;
    bool _suppressSecondExtensionLine = false;
    DimensionTextVerticalAlignment _textVerticalAlignment = DimensionTextVerticalAlignment::Above;
    ZeroHandling _zeroHandling = ZeroHandling::SuppressDecimalTrailingZeroes;
    bool _alternateUnitDimensioning = false;
    short _alternateUnitDecimalPlaces = 3;
    bool _textOutsideExtensions = false;
    bool _separateArrowBlocks = true;
    bool _textInsideExtensions = false;
    bool _suppressOutsideExtensions = false;
    short _angularDecimalPlaces = 0;
    DimensionTextHorizontalAlignment _textHorizontalAlignment = DimensionTextHorizontalAlignment::Centered;
    bool _suppressFirstDimensionLine = false;
    bool _suppressSecondDimensionLine = false;
    ToleranceAlignment _toleranceAlignment = ToleranceAlignment::Bottom;
    ZeroHandling _toleranceZeroHandling = ZeroHandling::SuppressDecimalTrailingZeroes;
    ZeroHandling _alternateUnitZeroHandling = ZeroHandling::SuppressZeroFeetAndInches;
    short _dimensionFit = 0;
    bool _cursorUpdate = false;
    ZeroHandling _alternateUnitToleranceZeroHandling = ZeroHandling::SuppressZeroFeetAndInches;
    short _dimensionUnit = 2;
    AngularUnitFormat _angularUnit = AngularUnitFormat::DecimalDegrees;
    short _decimalPlaces = 2;
    short _toleranceDecimalPlaces = 2;
    LinearUnitFormat _alternateUnitFormat = LinearUnitFormat::Decimal;
    short _alternateUnitToleranceDecimalPlaces = 3;
    double _scaleFactor = 1.0;
    double _arrowSize = 0.18;
    double _extensionLineOffset = 0.6250;
    double _dimensionLineIncrement = 3.75;
    double _extensionLineExtension = 1.2500;
    double _rounding = 0.0;
    double _dimensionLineExtension = 0.0;
    double _plusTolerance = 0.0;
    double _minusTolerance = 0.0;
    double _fixedExtensionLineLength = 1.0;
    double _joggedRadiusDimensionTransverseSegmentAngle = M_PI / 4.0;
    DimensionTextBackgroundFillMode _textBackgroundFillMode = DimensionTextBackgroundFillMode::NoBackground;
    Color _textBackgroundColor = Color::ByBlock;
    ZeroHandling _angularZeroHandling = ZeroHandling::SuppressZeroFeetAndInches;
    ArcLengthSymbolPosition _arcLengthSymbolPosition = ArcLengthSymbolPosition::BeforeDimensionText;
    double _textHeight = 0.18;
    double _centerMarkSize = 1.5;
    double _tickSize = 0.0;
    double _alternateUnitScaleFactor = 25.4;
    double _linearScaleFactor = 1.0;
    double _textVerticalPosition = 0.0;
    double _toleranceScaleFactor = 1.0;
    double _dimensionLineGap = 0.6250;
    double _alternateUnitRounding = 0.0;
    Color _dimensionLineColor = Color::ByBlock;
    Color _extensionLineColor = Color::ByBlock;
    Color _textColor = Color::ByBlock;
    FractionFormat _fractionFormat = FractionFormat::Horizontal;
    LinearUnitFormat _linearUnitFormat = LinearUnitFormat::Decimal;
    char _decimalSeparator = '.';
    TextMovement _textMovement = TextMovement::MoveLineWithText;
    bool _isExtensionLineLengthFixed = false;
    TextDirection _textDirection = TextDirection::LeftToRight;
    LineweightType _dimensionLineWeight = LineweightType::ByBlock;
    LineweightType _extensionLineWeight = LineweightType::ByBlock;
    TextArrowFitType _dimensionTextArrowFit = TextArrowFitType::BestFit;
    TextStyle *_style = nullptr;
    BlockRecord *_leaderArrow = nullptr;
    BlockRecord *_arrowBlock = nullptr;
    BlockRecord *_dimArrow1 = nullptr;
    BlockRecord *_dimArrow2 = nullptr;
    std::string _altMzs;
    std::string _mzs;
    double _altMzf = 0.0;
    double _mzf = 0.0;
    LineType *_lineType = nullptr;
    LineType *_lineTypeExt1 = nullptr;
    LineType *_lineTypeExt2 = nullptr;
};

}// namespace dwg
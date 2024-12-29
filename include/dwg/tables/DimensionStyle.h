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

#include <dwg/DxfSubclassMarker.h>
#include <dwg/LineweightType.h>
#include <dwg/tables/ArcLengthSymbolPosition.h>
#include <dwg/tables/DimensionTextBackgroundFillMode.h>
#include <dwg/tables/DimensionTextHorizontalAlignment.h>
#include <dwg/tables/DimensionTextVerticalAlignment.h>
#include <dwg/tables/FractionFormat.h>
#include <dwg/tables/TextArrowFitType.h>
#include <dwg/tables/TextDirection.h>
#include <dwg/tables/TextMovement.h>
#include <dwg/tables/ToleranceAlignment.h>
#include <dwg/tables/ZeroHandling.h>
#include <dwg/units/AngularUnitFormat.h>
#include <dwg/units/LinearUnitFormat.h>
#include <dwg/tables/TableEntry.h>
#include <dwg/base/Color.h>


namespace dwg {


class DimensionStyle : public TableEntry
{
public:
    static constexpr auto DefaultName = "Standard";
    static DimensionStyle *Default() { return new DimensionStyle(DefaultName); }

    dwg::ObjectType ObjectType() const { return ObjectType::DIMSTYLE; }
    std::string ObjectName() const { return DxfFileToken::TableDimstyle; }
    std::string SubclassMarker() const
    {
        return DxfSubclassMarker::DimensionStyle;
    }

    DimensionStyle(const std::string &name) : TableEntry(name) {}

    // 3
    std::string PostFix = "<>";
    // 3
    std::string AlternateDimensioningSuffix = "[]";
    // 71
    bool GenerateTolerances = false;
    // 72
    bool LimitsGeneration = false;
    // 73
    bool TextInsideHorizontal = false;
    // 74
    bool TextOutsideHorizontal = false;
    // 75
    bool SuppressFirstExtensionLine = false;
    // 76
    bool SuppressSecondExtensionLine = false;
    // 77
    DimensionTextVerticalAlignment TextVerticalAlignment =
            DimensionTextVerticalAlignment::Above;
    // 78
    ZeroHandling ZeroHandling =
            ZeroHandling::SuppressDecimalTrailingZeroes;
    // 170
    bool AlternateUnitDimensioning = false;
    // 171
    short AlternateUnitDecimalPlaces = 3;
    // 172
    bool TextOutsideExtensions = 0;
    // 173
    bool SeparateArrowBlocks = true;
    // 174
    bool TextInsideExtensions = false;
    // 175
    bool SuppressOutsideExtensions = false;
    // 179
    short AngularDimensionDecimalPlaces = 0;
    // 280
    DimensionTextHorizontalAlignment TextHorizontalAlignment =
            DimensionTextHorizontalAlignment::Centered;
    // 281
    bool SuppressFirstDimensionLine = false;
    // 282
    bool SuppressSecondDimensionLine = false;
    // 283
    ToleranceAlignment ToleranceAlignment = ToleranceAlignment::Bottom;
    // 284
    ZeroHandling ToleranceZeroHandling =
            ZeroHandling::SuppressDecimalTrailingZeroes;
    // 285
    ZeroHandling AlternateUnitZeroHandling =
            ZeroHandling::SuppressZeroFeetAndInches;
    // 287
    short DimensionFit;
    // 288
    bool CursorUpdate = false;
    // 286
    ZeroHandling AlternateUnitToleranceZeroHandling =
            ZeroHandling::SuppressZeroFeetAndInches;
    // 270
    short DimensionUnit = 2;
    // 275
    AngularUnitFormat AngularUnit =
            AngularUnitFormat::DecimalDegrees;
    // 271
    short DecimalPlaces = 2;
    // 272
    short ToleranceDecimalPlaces = 2;
    // 273
    LinearUnitFormat AlternateUnitFormat =
            LinearUnitFormat::Decimal;
    // 274
    short AlternateUnitToleranceDecimalPlaces = 3;
    // 40
    double ScaleFactor = 1.0;
    // 41
    double ArrowSize = 0.18;
    // 42
    double ExtensionLineOffset = 0.6250;
    // 43
    double DimensionLineIncrement = 3.75;
    // 44
    double ExtensionLineExtension = 1.2500;
    // 45
    double Rounding = 0.0;
    // 46
    double DimensionLineExtension = 0.0;
    // 47
    double PlusTolerance = 0.0;
    // 48
    double MinusTolerance = 0.0;
    // 49
    double FixedExtensionLineLength = 1.0;
    // 50
    double JoggedRadiusDimensionTransverseSegmentAngle = M_PI / 4.0;
    // 69
    DimensionTextBackgroundFillMode TextBackgroundFillMode =
            DimensionTextBackgroundFillMode::NoBackground;
    // 70
    Color TextBackgroundColor = Color::ByBlock;
    // 79
    ZeroHandling AngularZeroHandling = ZeroHandling::SuppressZeroFeetAndInches;
    // 90
    ArcLengthSymbolPosition ArcLengthSymbolPosition =
            ArcLengthSymbolPosition::BeforeDimensionText;
    // 140
    double TextHeight = 0.18;
    // 141
    double CenterMarkSize = 2.5;
    // 142
    double TickSize = 0.0;
    // 143
    double AlternateUnitScaleFactor = 25.4;
    // 144
    double LinearScaleFactor = 1.0;
    // 145
    double TextVerticalPosition = 0.0;
    // 146
    double ToleranceScaleFactor = 1.0;
    // 147
    double DimensionLineGap = 0.6250;

    // 148
    double AlternateUnitRounding = 0.0;
    // 176
    Color DimensionLineColor = Color::ByBlock;
    // 177
    Color ExtensionLineColor = Color::ByBlock;

    // 178
    Color TextColor = Color::ByBlock;

    // 176
    FractionFormat FractionFormat = FractionFormat::Horizontal;

    // 277
    LinearUnitFormat LinearUnitFormat = LinearUnitFormat::Decimal;

    // 278
    char DecimalSeparator = '.';

    // 279
    TextMovement TextMovement = TextMovement::MoveLineWithText;

    // 290
    bool IsExtensionLineLengthFixed = false;

    // 295
    TextDirection TextDirection = TextDirection::LeftToRight;

    // 371
    LineweightType DimensionLineWeight = LineweightType::ByBlock;

    // 372
    LineweightType ExtensionLineWeight = LineweightType::ByBlock;

    // 289
    TextArrowFitType DimensionTextArrowFit = TextArrowFitType::BestFit;

    // 340,Handle
    unsigned long long TextStyleHandle;
    // 341,Handle
    unsigned long long LeaderArrow;
    // 342, Handle
    unsigned long long ArrowBlock;
    // 343 Handle
    unsigned long long DimArrow1;
    // 344, Handle
    unsigned long long DimArrow2;


protected:
    std::string AltMzs;
    std::string Mzs;
    double AltMzf;
    double Mzf;
};

class DimensionStylesTable : public Table<DimensionStyle>
{
public:
    DimensionStylesTable();

    dwg::ObjectType ObjectType() const override
    {
        return dwg::ObjectType::DIMSTYLE_CONTROL_OBJ;
    }
    std::string ObjectName() const override
    {
        return DxfFileToken::TableDimstyle;
    }

protected:
    std::vector<std::string> defaultEntries() const
    {
        return {DimensionStyle::DefaultName};
    }
};

}// namespace dwg